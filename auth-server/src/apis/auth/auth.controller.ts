import { Controller, Get, UseGuards } from "@nestjs/common";
import { AuthGuard } from "@nestjs/passport";
import { UserService } from "../users/users.service";
import { AuthService } from "./auth.service";
import { Req, Res } from '@nestjs/common'
import { Request, Response } from "express";
import { User } from "../users/entities/users.entity";
import { UnprocessableEntityException } from '@nestjs/common/exceptions'
import { Args } from "@nestjs/graphql";

interface IOAuthUser {
    user: Pick<User, "email" | "psword" | "nickname">
}

@Controller()
export class AuthController {
    constructor(
        private readonly userService: UserService,
        private readonly authService: AuthService,
    ) { }

    @Get('/')
    dummypage() {
        return `
        <!DOCTYPE html>
        <html lang="en">

        <head>
        <title>로그인 서버</title>
        </head>

        <body>
            
           
        </body>

        </html>
        `
    }


    @Get('/login/google')
    @UseGuards(AuthGuard('google'))
    async loginGoogle(
        @Req() req: Request & IOAuthUser,
        @Res() res: Response
    ) {
        let user = await this.userService.findOne({ email: req.user.email })

        if (!user) {
            throw new UnprocessableEntityException('이메일이 존재하지 않습니다.')
        }

        // this.authService.getRefreshToken({ user, res })

        res.redirect("http://localhost:5500/src/social.html")



    }

    @Get('/login/google')
    @UseGuards(AuthGuard('google'))
    async createGoogle(
        @Args('nickname') nickname: string,
        @Req() req: Request & IOAuthUser,
        @Res() res: Response
    ) {
        let user = await this.userService.findOne({ email: req.user.email })

        let nick = await this.userService.findNick({ nickname })

        if (!user && !nick) {
            user = await this.userService.create({
                email: req.user.email,
                hashedPsword: req.user.psword,
                nickname: nick,
                regDate: "2023-01-26",
            })
        }

        res.redirect("http://localhost:5500/src/social.html")

    }



}