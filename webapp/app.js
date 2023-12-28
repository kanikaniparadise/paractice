/* 1. expressモジュールをロードし、インスタンス化してappに代入。*/
var hoge = "<p>hello</p>"
var express = require("express");
const crypto = require('crypto')//md5ハッシュ化の前提

const fs=require("fs");
var app = express();
var jwt = require('jsonwebtoken');//tokenの発行関係
app.use(express.urlencoded({extended:true}))
var cookies = require("cookie-parser");
const bcrypt = require('bcrypt');
app.use(cookies());

/* 2. listen()メソッドを実行して3000番ポートで待ち受け。*/
var server = app.listen(3000, function(){
    console.log("Node.js is listening to PORT:" + server.address().port);
});

//mysqlとの接続関係
const mysql = require('mysql');

const con = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: 'mysql',
});

con.connect(function (err) {
    console.log('Connected');
    const sql = 'select * from webapp.name_pass where name = "a"';
    con.query(sql, function (err, result, fields) {
	if (err) {throw err;}
    });
    
});
//クッキーからtoken を持って来てあってるか確かめる関数
function check_token (cookie){
    
    if (cookie.token==null){return false};
    token=cookie.token;
    var token_value = jwt.verify(token, 'my_secret');
    var hantei = "kai"
    var text = fs.readFileSync("./name_token.txt","utf-8");
    var sql = "select * from webapp.name_token where token = ?";
    return new Promise((resolve,reject)=>{
	con.query(sql,token,function(err,result,fields){
	    if(result.length !=0){
				  resolve(true)

				 }
	    else{
		console.log("nooooo")
		resolve(false)
	    }

	})
    })
}

//md5にハッシュ化する関数
function to_md5(text){
    const md5 = crypto.createHash('md5')
    return md5.update(text).digest('hex')
}

// View EngineにEJSを指定。
app.set('view engine', 'ejs');
//新規登録
app.get("/newaccount",function(req,res,next){
    res.render("newaccount",{})
})



app.post("/newaccount",function(req,res,next){

    var form = req.body;
    var output = [];
    const sql = 'insert into webapp.name_pass set ?';
    console.log (form)
    output  = {name : form.name,pass : to_md5(form.pass)}
    console.log(output)
    con.query(sql,output, function (err, result, fields) {
    	
	console.log(err);
    });
    
    
    res.render("madeaccount",{})
    
})
var tokenok=0;
// "/"へのGETリクエストでindex.ejsを表示する。トークンがあればそのトークンを確認、homeに遷移する
app.get("/", async function(req, res, next){		//パスワード確認ページを表示する処理
    const cookies = req.cookies;
    if(await check_token(cookies)){
	var sql = "select name from webapp.name_token where token = ?"
	console.log(req.cookies.token)
	con.query(sql,req.cookies.token,function(err,result_name,fields){
	    var name = result_name[0].name;
	    console.log(err)
	    console.log(name)
	    const today = new Date();
	    const mon = ("0"+(today.getDate() - today.getDay())).slice(-2);
	    
	    const sunday = today.getFullYear()+"-"+("0"+(today.getMonth()+1)).slice(-2)+"-"+mon;
	    console.log("uni")
	    console.log(sunday)
	    var sql ="select * from webapp.shift where ena = 0 and date>? order by date asc , case name when ? then 1 else 2 end , name asc";
	    con.query(sql,[sunday,name], function(err,result,fields){
		//result.unshift(null)
		console.log(err)
		console.log(result)
		res.render("home",{ data: result,name: name,change: undefined});
	    })
	})
    }

    else{res.render("index",{})}
});
app.post("/", function(req, res, next){		//送られてきたパスワードとユーザ名を確かめる
    var sql = 'select * from webapp.name_pass where name = ? and pass = ?';
    var data = "name = 'aa'"
    con.query(sql,[req.body.name,to_md5(req.body.pass)], function (err, result, fields) {
	console.log(err)
	if (result.length!=0){
	    const token = jwt.sign({ name: req.body.name}, 'my_secret', {});
	    var sql = "insert into webapp.name_token values(?,?)";
	    con.query(sql,[req.body.name,token ],function(err,result,fields){console.log(err);})
    	    res.cookie("token",token)			//cookieにtokenを渡す
	    res.redirect("../");
	}
	else{
	    res.render("index",{})
	}
    });
    
});


//		ログアウト

app.get("/delcookie",(req,res)=>{
    var sql="delete from webapp.name_token where token = ?"
    con.query(sql,req.cookies.token ,function(err,result,fields){console.log(err);})
    res.clearCookie("token")
    res.send("<a href='../'>ログイン画面へ行く</a>")
})

//指定されたデータを削除する
app.post("/deldata",async function(req,res){
    if(await check_token(req.cookies)){
	console.log(req.body)
	if(req.body.updateno!=undefined){
	    var sql = "select name from webapp.name_token where token = ?"
	    console.log(req.cookies.token)
	    con.query(sql,req.cookies.token,function(err,result_name,fields){
		var name = result_name[0].name;
		console.log(err)
		console.log(name)
		const today = new Date();
		const mon = ("0"+(today.getDate() - today.getDay())).slice(-2);

		const sunday = today.getFullYear()+"-"+("0"+(today.getMonth()+1)).slice(-2)+"-"+mon;
		console.log(sunday)
		var sql ="select * from webapp.shift where ena = 0 and date>? order by date asc , case name when ? then 1 else 2 end , name asc";
		con.query(sql,[sunday,name], function(err,result,fields){
		    //result.unshift(null)
		    res.render("home",{ data: result,name: name,change: req.body.updateno});
		    
		})
	    })
	    return 0;
	}
	if(req.body.changeid!=undefined){
	    var sql = "update webapp.shift set date = ?,intime = ?,outtime = ?,comment = ? where id = ?"
	    var datas= [req.body.date,req.body.intime,req.body.outtime,req.body.comment,req.body.changeid]
	    con.query(sql,datas,function(err,result,fields){console.log(datas)})
	}
	console.log(req.body)
	if(req.body.delno!=undefined){
	    var sql = "update webapp.shift set ena=true where id = ?"
	    con.query(sql,req.body.delno,function(err,result,fields){console.log(err);})
	}
    }
    
    res.redirect("../")
})
app.post('/send_kinmu', async function(req, res){		//送られてきた勤務の情報をテキストに書き込み、リロードさせる
    if(await check_token(req.cookies)){
	var form = req.body;
	var output = [];
	var sql="select name from webapp.name_token where token = ?;"
	con.query(sql,req.cookies.token ,function(err,result,fields){
	    console.log(err);
	    output  = [0,result[0].name,form.day,form.start,form.fin,form.coment,0]
	    sql = "insert into webapp.shift values(?,?,?,?,?,?,?)"
	    console.log(form.day)
	    con.query(sql,output,function(err,resu,fields){
		console.log(err)
	    })
	    res.redirect("../");
	})
    }
    else{
	res.render("error",{});
    }  
})

app.use(function(req, res, next){
    res.status(404);
    res.render("error",{});
})
