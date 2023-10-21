const mysql = require('mysql');
const con = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: 'mysql',
});
var sql="select * from webapp.name_pass"
con.query(sql, function (err, result, fields) {
	console.log(result[0].name);
})
