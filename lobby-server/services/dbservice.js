const redisClient = require('../databases/redis');
const mysqlDB = require('../databases/mysql');

const redisCli = redisClient.v4;


const mysqlService = {
    buyitem: (userPrimkey, itemcode) => {
        sql = `INSERT INTO inventory (userPrimKey, itemItemcode) VALUES (${userPrimkey}, ${itemcode})`;
        mysqlDB.query(sql, (err, data) => {
            if (err) { console.log('error') }
            else { console.log("update info") }
        });
    },

    sellitem: (userPrimkey, itemcode) => {
        // sql = 
        // mysqlDB.query(sql, (err, data) => {
        //     if (err) { console.log('error') }
        //     else { console.log("update info") }
        // });
    },



    getnick: (Nick) => {
        return new Promise((resolve, reject) => {
            const sql = `SELECT nickname FROM user WHERE nickname = ?`
            mysqlDB.query(sql, [Nick], (err, data) => {
                if (err) { console.log('error') }
                else { resolve(data[0]) }
            });
        })

    },

    getdata: (Nick) => {
        return new Promise((resolve, reject) => {
            const sql = `SELECT nickname, exp, level, cash FROM user WHERE nickname = ?`;
            mysqlDB.query(sql, [Nick], (err, data) => {
                if (err) { console.log('error') }
                else { resolve(data[0]); }
            })
        })

    },
    //
    getcash: (Nick) => {
        return new Promise((resolve, reject) => {
            const sql = `SELECT cash FROM USER WHERE email = ?`;
            mysqlDB.query(sql, [Nick], (err, data) => {
                if (err) { console.log('error') }
                else { resolve(data[0]); }
            })
        })
    },

    getprimekey: (Nick) => {
        return new Promise((resolve, reject) => {
            const sql = `SELECT primKey FROM user WHERE nickname = ?`
            mysqlDB.query(sql, [Nick], (err, data) => {
                if (err) { console.log('error') }
                else { resolve(data[0]) }
            });
        })
    },
    getfitkey: (primKey, itemcode) => {
        return new Promise((resolve, reject) => {
            const sql = `SELECT listnum FROM USER WHERE userPrimKey = ${primkey} AND itemItemcode = ${itemcode}`;
            mysqlDB.query(sql, (err, data) => {
                if (err) { console.log('error') }
                else { resolve(data[0]); }
            })
        })
    },

    getprice: (itemcode) => {
        return new Promise((resolve, reject) => {
            const sql = `SELECT itemprice FROM ITEM WHERE itemname = ?`;
            mysqlDB.query(sql, [itemcode], (err, data) => {
                if (err) { console.log('error') }
                else { resolve(data[0]); }
            })
        })

    },

    getinveninfo: (primKey) => {
        return new Promise((resolve, reject) => {
            const sql = `SELECT itemItemcode FROM INVENTORY WHERE primKey = ?`;
            mysqlDB.query(sql, [primKey], (err, data) => {
                if (err) { console.log('error') }
                else { resolve(data[0]); }
            })
        })
    },


    //
    upcash: (cash) => {
        mysqlDB.query(`UPDATE USER SET cash = ${cash} `)
    },

    upfitinfo: (listnum, fit) => {
        mysqlDB.query(`UPDATE inventory WHERE listnum = ${listnum} SET fit = ${fit}`)
    },


    //








}

const redisService = {

    //
    getstate: (Nick) => {
        return new Promise((resolve, reject) => {
            redisCli.get(Nick, (err, value) => {
                resolve(value)
            });
        })
    },

    //
    setstate: (Nick) => {
        redisCli.set(Nick, 'inlobby')
    },

    //
    upstate: (Nick, newstate) => {
        redisCli.set(Nick, newstate)
    }



}

module.exports = {
    mysqlService,
    redisService,
}