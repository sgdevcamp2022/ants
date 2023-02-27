"use strict"

const mysqlDB = require('../databases/mysql');
const { mysqlService, redisService, anotherService } = require('../services/dbservice');

const lobbyctrl = {

    login: async (Nick, clientId) => {
        await redisService.saveclientId(clientId, Nick)
        const dbuser = await mysqlService.getnick(Nick)
        try {
            if (dbuser.nickname === Nick) {
                const state = await redisService.getstate(Nick)
                if (state === "inlobby" || state === "gaming") {
                    throw new Error("정상적인 접근이 아닙니다.");
                }
                if (state === null) {
                    await redisService.setstate(Nick)

                } else {
                    const newstate = "inlobby"
                    await redisService.upstate(Nick, newstate)
                }
                return await mysqlService.getdata(Nick)
            }
        }
        catch (error) {
            console.error(error)
        }
    },

    logout: async (Nick, clientId) => {

        const state = await redisService.getstate(Nick)
        if (state === "inlobby" || state === "gaming") {
            await redisService.delclientId(clientId)
            const newstate = "logout"
            await redisService.upstate(Nick, newstate)


        } else {
            throw new Error("유저상태 오류발생")
        }
        const laststate = await redisService.getstate(Nick)
        if (laststate === "logout") {
            return true
        }

    },

    playgame: async (Nick) => {

        const state = await redisService.getstate(Nick)
        if (state === "inlobby") {
            const newstate = "gaming"
            await redisService.upstate(Nick, newstate)
            //인벤토리 정보 리턴
            return true
        } else {
            throw new Error("유저상태 오류발생")
        }
    },

    inlobby: async (Nick) => {

        const state = await redisService.getstate(Nick)
        if (state === "gaming") {
            const newstate = "inlobby"
            await redisService.upstate(Nick, newstate)
            return await mysqlService.getdata(Nick)
        } else {
            throw new Error("유저상태 오류발생")
        }
    },

    disconnected: async (clientId) => {
        const nick = await redisService.getnick(clientId)
        await redisService.delclientId(clientId)
        const newstate = 'logout'
        await redisService.upstate(nick, newstate);
    }


}


const storectrl = {

    getstash: async (Nick) => {
        const primeKey = await mysqlService.getprimekey(Nick)
        return await mysqlService.getstash(primeKey.primKey)
    },


    buyitem: async (Nick, itemcode) => {
        try {
            //await mysqlDB.beginTransaction()
            const state = await redisService.getstate(Nick)
            if (state === 'inlobby') {
                const price = await mysqlService.getprice(itemcode);

                //  await mysqlDB.commit();
                const cash = await mysqlService.getcash(Nick);
                if (price.itemprice > cash.cash) {
                    return "캐시가 부족합니다."
                }
                cash.cash -= price.itemprice
                await mysqlService.upcash(Nick, cash.cash)
                const userprimekey = await mysqlService.getprimekey(Nick)
                const uuid = await anotherService.createuuid()
                const empty = await mysqlService.getemptyslot(userprimekey.primKey)
                const location = await anotherService.findempty(empty)

                await mysqlService.buyitem(userprimekey.primKey, uuid, itemcode, location);

                const usercash = await mysqlService.getcash(Nick)
                return usercash.cash
                //유저캐시 아이템코드
            }

        } catch (err) {
            //await mysqlDB.rollback();
            console.error(err)
        } finally {
            //mysqlDB.release();
        }





    },

    sellitem: async (listnum) => {
        try {
            const data = await mysqlService.getsellinfo(listnum) //primkey, itemcode, 

            const Nick = await mysqlService.getusernick()//primkey 넣어서 닉네임 가져오기
            //await mysqlDB.beginTransaction();
            const state = await redisService.getstate(Nick)

            if (state === 'inlobby') {
                const price = await mysqlService.getprice(itemcode);
                // await mysqlDB.commit();
                const cash = await mysqlService.getcash(Nick);
                cash += price
                console.log(cash)
                mysqlService.upcash(Nick, cash)

                //회원의 inventory에 아이템 삭제
                await mysqlService.sellitem(listnum)

                return await mysqlService.getdata(Nick)
            }

        } catch (err) {
            //  await mysqlDB.rollback();
            console.error(err)
        } finally {
            // mysqlDB.release();
        }

    }
}


const inventoryctrl = {
    upitem: async (data) => {
        const Nick = data[0].nickname
        const state = await redisService.getstate(Nick)
        if (state === "inlobby") {
            for (var i = 0; i < data.length; i++) {
                const listnum = data[i].listnum
                const slotnum = data[i].location
                const fit = data[i].fit
                mysqlService.upinveninfo(listnum, slotnum, fit)
            }
            return true
        } else {
            throw new Error("유저의 상태가 이상합니다")
        }
    },

    getinven: async (Nick) => {
        const primeKey = await mysqlService.getprimekey(Nick)
        return await mysqlService.getinveninfo(primeKey.primKey)
    },

}

const gamectrl = {
    sendmatching: async (Nick) => {
        const state = await redisService.getstate(Nick)
        if (state === 'inlobby') {
            const rownum = await mysqlService.getrownum(Nick)
            console.log('ingamectrl row number: ' + rownum)
            return rownum

        }
    },

    upwinner: async (winner) => {
        const Nick = await mysqlService.getrownick(winner)
        const userdata = await mysqlService.getdata(Nick.nickname)
        const exp = userdata.exp + 30
        const level = userdata.level
        if (exp >= 100) {
            const upexp = exp - 100;
            const uplevel = level + 1;
            await mysqlService.uplevel(Nick.nickname, upexp, uplevel)

        } else {
            await mysqlService.upexp(Nick.nickname, exp)
        }
    },

    upuser: async (user) => {
        console.log(user.length)
        for (var i = 0; i < user.length; i++) {
            const Nick = await mysqlService.getrownick(user[i])
            const newstate = 'inlobby'
            await redisService.upstate(Nick.nickname, newstate);
        }

    },

    ingame: async (rownum) => {
        //게임들어가는 유저는 상태 적용
        const newstate = 'gaming'
        await redisService.upstate(Nick, newstate);
    }

}

module.exports = {
    lobbyctrl,
    storectrl,
    inventoryctrl,
    gamectrl
}
