"use strict"

const net = require('net');
const jwt = require("jsonwebtoken");
const EventEmitter = require('events');
const protobuf = require('protobufjs');
const { lobbyctrl, storectrl, inventoryctrl, gamectrl } = require('./controller/lobby')
const dotenv = require('dotenv');

const clients = new Map();//
dotenv.config();

const emitter = new EventEmitter();

protobuf.load("messages.proto", (err, root) => {
    if (err) {
        throw err;
    }
    const log = root.lookupType('log');
    const customerList = root.lookupType('CustomerList');
    const getinven = root.lookupType('Getinven');
    const getstash = root.lookupType('Getstash');
    const invenarray = root.lookupType('Getinven.Result');
    const stasharray = root.lookupType('Getstash.Result');
    const upinven = root.lookupType('Upinven');
    const sendbuyitem = root.lookupType('Buyitem');
    const endgame = root.lookupType('Endgame')

    const server = net.createServer(function (socket) {
        const clientId = generateClientId();
        clients.set(clientId, socket);
        console.log(`Client connected with ID: ${clientId}`);



        socket.on('data', function (data) {
            const clientSocket = this;
            const clientId = getClientId(clientSocket);
            console.log(`Received data from client with ID ${clientId}`);

            try {
                const message = log.decode(data);
                const command = message.cd;
                const cl_data = message.token;
                const cl_data2 = message.buy;

                if (command === 0) {
                    emitter.emit('login', { cl_data, clientId })
                }
                else if (command === 1) {
                    emitter.emit('buyitem', { cl_data, cl_data2 })
                }
                else if (command === 2) {
                    emitter.emit('sellitem', cl_data)
                }
                else if (command === 3) {
                    emitter.emit('logout', cl_data)
                }
                else if (command === 4) {
                    const inven = upinven.decode(data)
                    emitter.emit('upitem', inven.inventory)
                }
                else if (command === 5) {
                    emitter.emit('getinven', cl_data)
                }
                else if (command === 6) {
                    emitter.emit('getstash', cl_data)
                }
                else if (command === 7) {
                    const win = endgame.decode(data)
                    console.log(win)
                    emitter.emit('endgame', win)
                }
                else if (command === 8) {
                    emitter.emit('senduserrow', cl_data)
                }
                else if (command === 9) {
                    emitter.emit('startgame', cl_data)//게임에 들어가는 유저정보 받기
                }


            } catch (err) {
                console.error(err);
            }
        });

        socket.setKeepAlive(true);

        socket.on('close', async function (data) {
            const clientId = getClientId(socket);
            lobbyctrl.disconnected(clientId)
            clients.delete(clientId);
            console.log(`Client disconnected with ID: ${clientId}`);
        });

        emitter.setMaxListeners(30);

        emitter.on('login', async (cl_data) => {
            try {
                const token = cl_data.cl_data;
                const clientId = cl_data.clientId;
                const payload = jwt.verify(token, process.env.JWT_KEY);
                const Nick = payload.sub
                const userdata = await lobbyctrl.login(Nick, clientId)
                console.log(userdata.nickname)
                const response = customerList.encode({
                    nickname: userdata.nickname,
                    level: userdata.level,
                    exp: userdata.exp,
                    cash: userdata.cash
                }).finish();
                socket.write(response);
            } catch (error) {
                throw new Error("정상적인 접근이 아닙니다.1")
            }

        })

        emitter.on('buyitem', async (cl_data) => {
            const Nick = cl_data.cl_data
            const itemcode = cl_data.cl_data2
            const userdata = await storectrl.buyitem(Nick, itemcode)
            const response = sendbuyitem.encode({
                cash: userdata,
                itemcode: itemcode,
            }).finish();
            socket.write(response);
        })

        emitter.on('sellitem', async (cl_data) => {
            const userdata = await storectrl.sellitem(cl_data)
            console.log(userdata)
            const response = customerList.encode({
                nickname: userdata.nickname,
                level: userdata.level,
                exp: userdata.exp,
                cash: userdata.cash
            }).finish();
            // socket.write(response);
        })

        emitter.on('logout', async (cl_data) => {
            const clientId = getClientId(socket);
            const Nick = cl_data
            await lobbyctrl.logout(Nick, clientId)

        })

        emitter.on('upitem', async (cl_data) => {
            await inventoryctrl.upitem(cl_data)
        })

        emitter.on('getinven', async (cl_data) => {
            const item = await inventoryctrl.getinven(cl_data)
            if (item.length === 0) {
                const result = []
                result[0] = invenarray.create({
                    listnum: "null",
                    fit: 'null',
                    location: 0,
                    itemcode: "null",
                })
                const sendinvennull = getinven.create({ result });
                const responsenull = getinven.encode(sendinvennull).finish();
                socket.write(responsenull)
            }

            else {
                const result = []
                for (var i = 0; i < item.length; i++) {
                    result[i] = invenarray.create({
                        listnum: item[i].listnum,
                        fit: item[i].fit,
                        location: item[i].location,
                        itemcode: item[i].itemCode,
                    })
                }
                const sendinven = getinven.create({ result });

                const response = getinven.encode(sendinven).finish();

                socket.write(response);
            }

        })

        emitter.on('getstash', async (cl_data) => {
            const stash = await storectrl.getstash(cl_data)
            if (stash.length === 0) {
                const result = []
                result[0] = stasharray.create({
                    listnum: "null",
                    itemcode: "null",
                })
                const sendstash = getstash.create({ result });
                const response = getstash.encode(sendstash).finish();
                socket.write(response);
            } else {
                const result = []
                for (var i = 0; i < stash.length; i++) {
                    result[i] = stasharray.create({
                        listnum: stash[i].listnum,
                        itemcode: stash[i].itemCode,
                    })
                }
                const sendstash = getstash.create({ result });
                const response = getstash.encode(sendstash).finish();

                socket.write(response);
            }
        })

        emitter.on('endgame', async (cl_data) => {
            await gamectrl.upwinner(cl_data.rownum)
            await gamectrl.upuser(cl_data.user)
        })

        emitter.on('senduserrow', async (cl_data) => {
            const rownum = await gamectrl.sendmatching(cl_data)
            // socket.write(rownum)
        })
        emitter.on('startgame', async (cl_data) => {
            // await gamectrl.ingame(cl_data)
            // 데이터 보내기
        })
    });

    server.on('error', function (err) {
        console.log('err' + err);
    });


    server.listen(8005, function () {
        console.log('linsteing on 8005..');
    });
});






function generateClientId() {
    return Math.floor(Math.random() * 900000) + 100000;
}

function getClientId(socket) {
    for (const [clientId, clientSocket] of clients) {
        if (clientSocket === socket) {
            return clientId;
        }
    }
    return null;
}