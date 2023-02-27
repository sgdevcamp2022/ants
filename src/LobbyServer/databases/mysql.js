"use strict";

const mysql = require('mysql');
const dotenv = require('dotenv');
dotenv.config();

const conn = {  // mysql 접속 설정
    host: '127.0.0.1',
    port: '3306',
    user: process.env.MYSQL_ID,
    password: process.env.MYSQL_PASSWORD,
    database: process.env.MYSQL_DATABASE,
};

const mysqlDB = mysql.createConnection(conn);
mysqlDB.connect();

module.exports = mysqlDB


//==========================test code======================
// let sql = "INSERT INTO `jobs` (`jobcode`,`jobname`) VALUES ('j1','궁수');";

// mysqlDB.query(sql, function (err, results, fields) {
//     if (err) {
//         console.log(err);
//     }
//     console.log(results);
// });

// sql = "SELECT * FROM jobs";

// mysqlDB.query(sql, function (err, results, fields) {
//     if (err) {
//         console.log(err);
//     }
//     console.log(results);
// });

//==========================test code======================
