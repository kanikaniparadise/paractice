/* 1. expressモジュールをロードし、インスタンス化してappに代入。*/
var express = require("express");
const fs=require("fs");
var app = express();
var jwt = require('jsonwebtoken');
app.use(express.urlencoded({extended:true}))
var cookies = require("cookie-parser");
app.use(cookies());

/* 2. listen()メソッドを実行して3000番ポートで待ち受け。*/
var server = app.listen(3000, function(){
    console.log("Node.js is listening to PORT:" + server.address().port);
});

/* 3. 以後、アプリケーション固有の処理 */

// View EngineにEJSを指定。
app.set('view engine', 'ejs');

// "/"へのGETリクエストでindex.ejsを表示する。トークンがあればそのトークンを確認、homeに遷移する
app.get("/", function(req, res, next){		//パスワード確認ページを表示する処理
    var tokenlist=[]
    var namelist=[]
    var text = fs.readFileSync("./name_token.txt","utf-8");
    text = text.split("\n");
    text.forEach(function(gyou){
	sliced = gyou.split(",");
	namelist.push(sliced[0])
	tokenlist.push(sliced[1])
    })
    const cookies = req.cookies;
    var tokenok=0
    if(cookies.token!=null){
	var token = jwt.verify(cookies.token, 'my_secret');
	console.log(token);
	console.log(namelist)
	num = namelist.lastIndexOf(token.username);
	if(num!=-1 && tokenlist[num]==cookies.token){
	    tokenok=1
    	    res.render("home",{});
    	}
    }
    if(tokenok==0){
    	res.render("index", {});
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
    var number=namelist.indexOf(req.body.username)
    if (number !=-1){
	if(passlist[number]==req.body.userpass){
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
    text.splice(num,1);
    fs.writeFileSync("name_token.txt", text);
    res.send("<a href='../'>ログイン画面へ行く</a>")
})


app.post('/send_kinmu', (req, res) => {		//送られてきた勤務の情報をテキストに書き込み、リロードさせる
    var form = req.body;
    var output = [];
    output  = [form.username,form.day,form.start,form.fin,form.coment]
    var nozomi=req.body.username;
    fs.appendFileSync( "output.txt" , output+"\n")
    res.render("home",{});
})



app.use(function(req, res, next){
    res.status(404);
    res.send("<html><h1>存在しないURLか不正なアクセス方法です</h1><br><h2><a href = '../../../../'>ホームへ戻る</a></h2></html>");
})
