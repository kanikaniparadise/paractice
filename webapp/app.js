/* 1. expressモジュールをロードし、インスタンス化してappに代入。*/
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
  if (err) throw new Error(err);
  console.log('Connected');
  const sql = 'select * from webapp.name_pass';
  con.query(sql, function (err, result, fields) {
    if (err) {throw err;}	
    console.log(result);
  });
});



//クッキーからtoken を持って来てあってるか確かめる関数
function check_token (cookie){
    if (cookie.token==null){return false};
    token=cookie.token;
    var tokenlist=[]
    var namelist=[]
    var tokenok=0;
    var token_value = jwt.verify(token, 'my_secret');
    var text = fs.readFileSync("./name_token.txt","utf-8");
    text = text.split("\n");
    text.forEach(function(gyou){
	sliced = gyou.split(",");
	namelist.push(sliced[0])
	tokenlist.push(sliced[1])
    }) 
    console.log(token);
    console.log(namelist)
    num = tokenlist.lastIndexOf(token);
    if(num!=-1 && namelist[num]==token_value.username){
    	return true
    }
    else{
    	return false;
    }
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

// "/"へのGETリクエストでindex.ejsを表示する。トークンがあればそのトークンを確認、homeに遷移する
app.get("/", function(req, res, next){		//パスワード確認ページを表示する処理
    
    

    const cookies = req.cookies;
    var tokenok=0
    if(check_token(cookies)){
    	res.render("home", {});
    }
    else{
	res.render("index",{});
    }
});
app.get("/get_kinmu", function(req, res, next){		//勤務表のデータを送る
    res.sendfile("output.txt");
});

app.post("/", function(req, res, next){		//送られてきたパスワードとユーザ名を確かめる
    var passok=0;
    var passlist=[]
    var namelist=[]
    var text = fs.readFileSync("./name_pass.txt","utf-8");
    text = text.split("\n");
    text.forEach(function(gyou){
	sliced = gyou.split(",");
	namelist.push(sliced[0])
	passlist.push(sliced[1])
    })
     const sql = 'select * from webapp.name_pass where ?';
  con.query(sql, function (err, result, fields) {
    if (err) {throw err;}	
    console.log(result);
  });
    var number=namelist.indexOf(req.body.username)
    if (number !=-1){
	if(passlist[number]==to_md5(req.body.userpass)){
	    const token = jwt.sign({ username: req.body.username}, 'my_secret', { expiresIn: '1h' });
    	    res.cookie("token",token)			//cookieにtokenを渡す
	    res.render("home", {});
	    passok=1;
	    var output=[req.body.username,token]
	    fs.appendFileSync( "name_token.txt" , output+"\n")
	}
    }
    if(passok==0){  	
    	res.render("index",{})
    }
});

//		ログアウト

app.get("/delcookie",(req,res)=>{
    res.clearCookie("token")
    var tokenlist=[]
    var text = fs.readFileSync("./name_token.txt","utf-8");
    text = text.split("\n");
    text.forEach(function(gyou){
	sliced = gyou.split(",");
	tokenlist.push(sliced[1])
    })
    num=tokenlist.indexOf(req.cookies.token);
    console.log(text)
    text.splice(num,1);
    console.log(text);
    text = text.map(function(a){
  return a+"\n";
});
text.splice(text.length-1,1)
    fs.writeFileSync("name_token.txt", text);
    res.send("<a href='../'>ログイン画面へ行く</a>")
})


app.post('/send_kinmu', (req, res) => {		//送られてきた勤務の情報をテキストに書き込み、リロードさせる
    if(check_token(req.cookies)){
	var form = req.body;
	var output = [];
	output  = [form.username,form.day,form.start,form.fin,form.coment]
	var nozomi=req.body.username;
	fs.appendFileSync( "output.txt" , output+"\n")
	res.render("home",{});
    }
    else{
	res.render("error",{});
    }
    
})



app.use(function(req, res, next){
    res.status(404);
    res.render("error",{});
})
