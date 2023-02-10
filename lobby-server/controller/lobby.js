const { state } = require('../databases/mysql');
const { mysqlService, redisService } = require('../services/dbservice');

const lobbyctrl = {

    login: async (Nick) => {
        const dbuser = await mysqlService.getnick(Nick)
        try {
            if (dbuser.nickname === Nick) {
                const state = await redisService.getstate(Nick)
                if (state === "inlobby" || state === "gaming") {
                    console.log("정상적인 접근이 아닙니다. loginctrl")
                    // throw new Error("정상적인 접근이 아닙니다.");
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

    logout: async (Nick) => {

        const state = await redisService.getstate(Nick)
        if (state === "inlobby" || state === "gaming") {
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


}


const storectrl = {

    buyitem: async (Nick, itemcode) => {
        console.log("연결성공")

        const state = await redisService.getstate(Nick)
        try {
            await connection.beginTransaction();
            if (state === 'inlobby') {
                const price = await mysqlService.getprice(itemcode);
                await connection.commit();
                const cash = await mysqlService.getcash(Nick);
                if (price > cash) {
                    return "캐시가 부족합니다."
                }
                console.log(`item price : ${price} // user cash : ${cash}`);
                cash -= price
                console.log(cash)
                await mysqlService.upcash(cash)
                const userprimekey = await mysqlService.getprimekey(Nick)
                await mysqlService.buyitem(userprimekey, itemcode);

                return await mysqlService.getdata(Nick)
            }

        } catch (err) {
            await connection.rollback();
            console.error(err)
        } finally {
            connection.release();
        }





    },

    sellitem: async (Nick, itemcode) => {
        try {
            await connection.beginTransaction();
            if (valid === 'inlobby') {
                const price = await mysqlService.getprice(itemcode);
                await connection.commit();
                const cash = await mysqlService.getcash(Nick);
                cash += price
                console.log(cash)
                mysqlService.upcash(cash)

                //회원의 inventory에 아이템 삭제

                return await mysqlService.getdata(Nick)
            }

        } catch (err) {
            await connection.rollback();
            console.error(err)
        } finally {
            connection.release();
        }

    }



}

const inventoryctrl = {
    fititem: async (Nick, itemcode) => {
        const primeKey = await mysqlService.getprimekey(Nick)
        const listnum = await mysqlService.getfitstate(primeKey, itemcode)
        const fit = 1
        await mysqlService.upfitinfo(listnum, fit)
        return await mysqlService.getinveninfo(primeKey)
    },

    unfititem: async (Nick, itemcode) => {
        const primeKey = await mysqlService.getprimekey(Nick)
        const listnum = await mysqlService.getfitstate(primeKey, itemcode)
        const fit = 0
        await mysqlService.upfitinfo(listnum, fit)
        return await mysqlService.getinveninfo(primeKey)
    }


}

module.exports = {
    lobbyctrl,
    storectrl
}
