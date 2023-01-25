import { MailerService } from "@nestjs-modules/mailer/dist";
import { Injectable } from "@nestjs/common";
import { JwtService } from "@nestjs/jwt/dist";
import * as bcrypt from 'bcrypt';
import 'dotenv/config';



@Injectable()
export class AuthService {
    constructor(
        private readonly mailerService: MailerService,
        private readonly jwtService: JwtService,
    ) { }

    async emailCode() {
        const mycount = 6
        const result = await String(Math.floor(Math.random() * 10 ** mycount)).padStart(mycount, "0")
        return result
    }

    async sendCode({ email, eToken }) {
        try {
            await this.mailerService.sendMail({
                to: email, // list of receivers
                from: 'wlgnstls0413@naver.com',
                subject: '이메일 인증 요청 메일입니다.',
                html: '6자리 인증 코드 : ' + `<b> ${eToken}</b>`,
            });
            const hashedeToken = await bcrypt.hash(eToken, 10);

            //============================hashedeToken 쿠키로 보내기===============
            //  res.cookie('authNum', hashedeToken, {path: '/', expires: new Date(Date.now()+300000)}); // 쿠키생성
            //============================쿠키보내기===============
            return { result: true, authNum: hashedeToken }
        } catch (err) {
            return { result: false }
        }
    }

    getAccessToken({ user }) {
        return this.jwtService.sign(
            { email: user.email, sub: user.nickname },
            { secret: "myAccessKey", expiresIn: '1h' },
        );
    }
}
