import { Context, Resolver } from "@nestjs/graphql";
import { Mutation, Args } from "@nestjs/graphql"
import * as bcrypt from 'bcrypt';
import { UserService } from "../users/users.service";
import { AuthService } from "./auth.service";
import { UnprocessableEntityException } from '@nestjs/common/exceptions'

@Resolver()
export class AuthResolver {
    constructor(
        private readonly authService: AuthService,
        private readonly userService: UserService,
    ) { }

    @Mutation(() => String)
    async login(
        @Args('email') email: string,
        @Args('psword') psword: string,
        @Context() context: any,  //cookie 관련된거
    ) {
        const user = await this.userService.findOne({ email })
        if (!user) {
            throw new UnprocessableEntityException('이메일이 존재하지 않습니다.')
        }
        const isAuth = await bcrypt.compare(psword, user.psword)
        if (!isAuth) {
            throw new UnprocessableEntityException('암호가 틀렸습니다.')
        }
        return this.authService.getAccessToken({ user })


    }

    @Mutation(() => String)
    async sendEmail(
        @Args('email') email: string,
    ) {
        const eToken = await this.authService.emailCode()
        const test = await this.authService.sendCode({ email, eToken })
        console.log(test.authNum)
        return test.result

    }

    // @Mutation(() => Boolean)
    // async checkEmail(
    //     @Args('eToken') eToken: string,
    // ) {
    //     //============================쿠키에 있는 hashedeToken 비교===============
    //     // const valid = await bcrypt.compare(eToken,);
    //     //=============================================================
    // }


}