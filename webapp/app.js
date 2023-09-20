/* 1. expressモジュールをロードし、インスタンス化してappに代入。*/
var express = require("express");
const fs=require("fs");
var app = express();

app.use(express.urlencoded({extended:true}))

/* 2. listen()メソッドを実行して3000番ポートで待ち受け。*/
var server = app.listen(3000, function(){
    console.log("Node.js is listening to PORT:" + server.address().port);
});

/* 3. 以後、アプリケーション固有の処理 */

// View EngineにEJSを指定。
app.set('view engine', 'ejs');

// "/"へのGETリクエストでindex.ejsを表示する。拡張子（.ejs）は省略されていることに注意。
app.get("/", function(req, res, next){		//パスワード確認ページを表示する処理
    res.render("index", {});
});

app.post("/", function(req, res, next){		//送られてきたパスワードとユーザ名を確かめる
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
	    res.render("home", {});
	}
    }
});

app.get('/send_kinmu', (req, res) => {		//送られてきた勤務の情報をテキストに書き込み、リロードさせる
    var form = req.body;
    var output = [];
    output  = [form.username,form.day,form.start,form.fin,form.coment]
    var nozomi=req.body.username;
    fs.appendFileSync( "output.txt" , output+"\n")
    res.render("home",{});
})

