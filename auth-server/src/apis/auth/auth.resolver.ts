import { Context, Resolver } from "@nestjs/graphql";
import { Mutation, Args } from "@nestjs/graphql"
import * as bcrypt from 'bcrypt';
import { UserService } from "../users/users.service";
import { AuthService } from "./auth.service";
import { UnprocessableEntityException } from '@nestjs/common/exceptions'
import { JwtService } from "@nestjs/jwt";

@Resolver()
export class AuthResolver {
    constructor(
        private readonly authService: AuthService,
        private readonly userService: UserService,
        private readonly jwtService: JwtService,
    ) { }

    @Mutation(() => String)
    async login(
        @Args('email') email: string,
        @Args('psword') psword: string,
    ) {
        const user = await this.userService.findOne({ email })
        if (!user) {
            throw new UnprocessableEntityException('이메일이 존재하지 않습니다.')
        }
        const isAuth = await bcrypt.compare(psword, user.psword)
        if (!isAuth) {
            throw new UnprocessableEntityException('암호가 틀렸습니다.')
        }

        const loginDate = new Date()
        await this.userService.uplogin({ email, loginDate })

        return this.authService.getAccessToken({ user })




    }

    @Mutation(() => String)
    async sendEmail(
        @Args('email') email: string,
        @Context() context: any,
    ) {
        await this.authService.checkValidationEmail({ email })
        const dbemail = await this.userService.findOne({ email })
        if (dbemail) {
            throw new UnprocessableEntityException("사용중인 이메일입니다.")
        }

        const eToken = await this.authService.emailCode()
        const result = await this.authService.sendCode({ email, eToken, res: context.req.res })
        return result.authNum
    }



    @Mutation(() => String)
    async checkEmail(
        @Args('eToken') eToken: String,
        @Args('hashedToken') hashedToken: String,
    ) {

        if (typeof eToken === 'string' && typeof hashedToken === 'string') {
            const result = await this.jwtService.decode(hashedToken)


            if (eToken === result.sub) {
                return true
            }
            return false
        }
    }


    @Mutation(() => String)
    async checkNick(
        @Args('nick') nick: String,
    ) {
        const nickvalid = await this.userService.findNick({ nickname: nick })
        if (!nickvalid) {
            return true
        }
        return false
    }



}