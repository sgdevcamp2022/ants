"use strict"

const redisClient = require('../databases/redis');
const mysqlDB = require('../databases/mysql');
const { v4 } = require('uuid');
v4();

const redisCli = redisClient.v4;


const mysqlService = {
    buyitem: (userPrimkey, uuid, itemcode, location) => {
        const sql = `INSERT INTO inventory (listnum, fit, location, userPrimKey, itemCode) VALUES ('${uuid}','s','${location}','${userPrimkey}','${itemcode}')`
        mysqlDB.query(sql, (err, data) => {
            if (err) { console.log('error') }
            else { console.log("update info") }
        });
    },

    sellitem: (listnum) => {
        sql = `DELETE FROM inventory WHERE listnum= ?`
        mysqlDB.query(sql, [listnum], (err, data) => {
            if (err) { console.log('error') }
            else { console.log("update info") }
        });
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

    getusernick: (primKey) => {
        return new Promise((resolve, reject) => {
            const sql = `SELECT nickname FROM user WHERE primKey = ?`
            mysqlDB.query(sql, [primKey], (err, data) => {
                if (err) { console.log('error') }
                else { resolve(data[0]) }
            });
        })
    },

    getrownick: (rownum) => {

        return new Promise((resolve, reject) => {
            const sql = `SELECT nickname
            FROM (
              SELECT ROW_NUMBER() OVER (ORDER BY regDate) AS ROWNUM, nickname
              FROM user
            ) u
            WHERE u.ROWNUM = ${rownum};`
            mysqlDB.query(sql, (err, data) => {
                if (err) { console.log('error') }
                else {
                    resolve(data[0])
                }
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
            const sql = `SELECT cash FROM user WHERE nickname = ?`;
            mysqlDB.query(sql, [Nick], (err, data) => {
                if (err) { console.log('error') }
                else {
                    resolve(data[0]);
                }
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
            const sql = `SELECT itemprice FROM items WHERE code = ?`;
            mysqlDB.query(sql, [itemcode], (err, data) => {
                if (err) { console.log('error') }
                else { resolve(data[0]); }
            })
        })

    },

    getinveninfo: (primKey) => {
        return new Promise((resolve, reject) => {
            const sql = `SELECT listnum, fit, location, itemCode FROM inventory WHERE userPrimKey = ?`;
            mysqlDB.query(sql, [primKey], (err, data) => {
                if (err) { console.log('error') }
                else {
                    resolve(data);
                }
            })
        })
    },

    getstash: (primKey) => {
        return new Promise((resolve, reject) => {
            const sql = `SELECT listnum, itemCode FROM inventory WHERE userPrimKey = '${primKey}' AND fit = 's' ORDER BY location ASC`;
            mysqlDB.query(sql, (err, data) => {
                if (err) { console.log('error') }
                else {
                    resolve(data);
                }
            })
        })
    },



    upcash: (Nick, cash) => {
        mysqlDB.query(`UPDATE user SET cash = '${cash}' WHERE nickname = '${Nick}'`)
    },

    uplevel: (Nick, exp, level) => {
        mysqlDB.query(`UPDATE user SET exp = '${exp}' , level='${level}' WHERE nickname = '${Nick}'`)
    },
    upexp: (Nick, exp) => {
        mysqlDB.query(`UPDATE user SET exp = '${exp}' WHERE nickname = '${Nick}'`)
    },

    upinveninfo: (listnum, slotnum, fit) => {
        mysqlDB.query(`UPDATE inventory SET fit = '${fit}', location = ${slotnum} WHERE listnum = '${listnum}'`, (err, data) => {
        })
    },

    getemptyslot: (userprimkey) => {
        return new Promise((resolve, reject) => {
            mysqlDB.query(`SELECT location FROM inventory WHERE userPrimKey = '${userprimkey}' AND fit = 's' ORDER BY location ASC`,
                (err, data) => {
                    if (err) { console.log('error') }
                    else { resolve(data); }
                })
        })
    },

    getrownum: (Nick) => {
        return new Promise((resolve, reject) => {
            const sql = `SELECT rownum
            FROM (
              SELECT ROW_NUMBER() OVER (ORDER BY regDate) AS ROWNUM, nickname
              FROM user
            ) u
            WHERE nickname= '${Nick}';`
            mysqlDB.query(sql, (err, data) => {
                if (err) { console.log('error') }
                else {
                    resolve(data[0])
                }
            });
        })
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
    },

    saveclientId: (clientId, Nick) => {
        redisCli.set(clientId, Nick)
    },

    getnick: (clientId) => {
        return new Promise((resolve, reject) => {
            redisCli.get(clientId, (err, value) => {
                resolve(value)
            });
        })
    },
    delclientId: (clientId) => {
        redisCli.del(clientId)
    }



}

const anotherService = {
    createuuid: () => {
        const uuid = v4();
        return uuid
    },

    findempty: async (empty) => {
        if (empty.length === 16) {
            throw new Error("stash가 가득 찼습니다.")
        } else if (empty.length === 0) {
            return 1;
        }
        for (var i = 0; i < 16; i++) {
            const emptyslot = i + 1;
            const slot = await empty[i].location
            if (emptyslot !== slot) {
                return emptyslot;
            }
            if (emptyslot === empty.length) {
                return empty.length + 1;
            }
        }
    }

}


module.exports = {
    mysqlService,
    redisService,
    anotherService,
}