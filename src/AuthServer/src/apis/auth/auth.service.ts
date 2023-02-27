import { MailerService } from "@nestjs-modules/mailer/dist";
import { Injectable, UnauthorizedException } from "@nestjs/common";
import { JwtService } from "@nestjs/jwt/dist";
import 'dotenv/config';



@Injectable()
export class AuthService {
    constructor(
        private readonly mailerService: MailerService,
        private readonly jwtService: JwtService,
    ) { }

    async checkValidationEmail({ email }) {
        if (email === undefined || !email.includes("@")) {
            throw new UnauthorizedException("이메일 형식이 맞지 않습니다.")
        } else {
            return true
        }
    }

    async emailCode() {
        const mycount = 6
        const result = await String(Math.floor(Math.random() * 10 ** mycount)).padStart(mycount, "0")
        return result
    }

    async sendCode({ email, eToken, res }) {
        try {
            await this.mailerService.sendMail({
                to: email,
                from: 'wlgnstls0413@naver.com',
                subject: '이메일 인증 요청 메일입니다.',
                html: '6자리 인증 코드 : ' + `<b> ${eToken}</b>`,
            });

            const hashedeToken = this.jwtService.sign(
                { email: email, sub: eToken },
                { secret: process.env.EMAIL_JWT_KEY, expiresIn: '2m' }
            );

            return { result: true, authNum: hashedeToken }
        } catch (err) {
            return { result: false }
        }
    }


    getAccessToken({ user }) {
        return this.jwtService.sign(
            { email: user.email, sub: user.nickname },
            { secret: process.env.AUTH_JWT_KEY, expiresIn: '1w' },
        );
    }

}
