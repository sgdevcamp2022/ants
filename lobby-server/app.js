const net = require('net');
const jwt = require("jsonwebtoken");
const EventEmitter = require('events');
const protobuf = require('protobufjs');
const { lobbyctrl, storectrl } = require('./controller/lobby')
const dotenv = require('dotenv');
dotenv.config();

const emitter = new EventEmitter();

protobuf.load("messages.proto", (err, root) => {
    if (err) {
        throw err;
    }
    const log = root.lookupType('log');
    const customerList = root.lookupType('CustomerList');


    const server = net.createServer(function (socket) {
        console.log(socket.address().address + " connected.");



        socket.on('data', function (data) {
            try {
                const message = log.decode(data);
                const command = message.cd;
                const cl_data = message.token;

                if (command === 0) {
                    emitter.emit('login', cl_data)
                } else if (command === 1) {
                    emitter.emit('buyitem', cl_data)
                } else if (command === 2) {
                    emitter.emit('sellitem', cl_data)
                }
                else if (command === 3) {
                    emitter.emit('logout', cl_data)
                }
                else if (command === 4) {
                    emitter.emit('fiteqip', cl_data)
                }
                else if (command === 5) {
                    emitter.emit('unfiteqip', cl_data)
                }

            } catch (err) {
                console.error(err);
            }
        });

        socket.on('close', async function (data) {

            console.log('client disconnted.');
        });


        emitter.on('login', async (cl_data) => {
            // const req = socket.request;
            // const ip = req.headers['x-forwarded-for'] || req.socket.remoteAddress;
            console.log("새로운 클라이언트 접속========> ");
            try {
                const token = cl_data;
                const payload = jwt.verify(token, process.env.JWT_KEY);
                const Nick = payload.sub
                const userdata = await lobbyctrl.login(Nick)

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
            const userdata = await storectrl.buyitem(Nick)
            const response = customerList.encode({
                nickname: userdata.nickname,
                level: userdata.level,
                exp: userdata.exp,
                cash: userdata.cash
            }).finish();
            socket.write(response);
        })


        emitter.on('sellitem', async (cl_data) => {
            const userdata = await storectrl.sellitem(Nick)
            console.log(userdata)
            const response = customerList.encode({
                nickname: userdata.nickname,
                level: userdata.level,
                exp: userdata.exp,
                cash: userdata.cash
            }).finish();
            socket.write(response);
        })

        emitter.on('logout', async (cl_data) => {
            const Nick = cl_data
            await lobbyctrl.logout(Nick)

        })

        emitter.on('fiteqip', async (cl_data) => {
            console.log(cl_data)

        })
        emitter.on('unfiteqip', async (cl_data) => {

        })


    });




    server.on('error', function (err) {
        console.log('err' + err);
    });


    server.listen(8005, function () {
        console.log('linsteing on 8005..');
    });
});