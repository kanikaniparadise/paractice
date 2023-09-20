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
app.get("/", function(req, res, next){
    res.render("index", {});
});

app.post("/pl", function(req, res, next){
    var passlist=[]
    var namelist=[]
    var text = fs.readFileSync("./name_pass.txt","utf-8");
    text = text.split("\n");
    text.forEach(function(gyou){
	sliced = gyou.split(",");
	namelist.push(sliced[0])
	passlist.push(sliced[1])
    })
    var number=namelist.indexOf(req.body[0])
    if (number !=-1){
	if(passlist[number]==req.body[1]){
	    res.sendfile("output.txt");
	}
    }
});

app.post('/', (req, res) => {
    var form = req.body;
    var output = [];
    output  = [form.username,form.day,form.start,form.fin,form.coment]
    var nozomi=req.body.username;
    res.render("index",{});
    fs.appendFileSync( "output.txt" , output+"\n")

})

