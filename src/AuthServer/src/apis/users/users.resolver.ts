import { Resolver, Mutation, Args } from "@nestjs/graphql";
import { UserService } from "./users.service";
import * as bcrypt from 'bcrypt';
import { UnprocessableEntityException } from '@nestjs/common'

@Resolver()
export class UserResolver {
    constructor(
        private readonly userService: UserService
    ) { }

    @Mutation(() => String)
    async createUser(
        @Args('email') email: string,
        @Args('psword') psword: string,
        @Args('nickname') nickname: string,
    ) {
        const emailcheck = await this.userService.findOne({ email })
        if (emailcheck) {
            throw new UnprocessableEntityException('이메일이 중복되어있습니다.')
        }
        const nickcheck = await this.userService.findNick({ nickname })
        if (nickcheck) {
            throw new UnprocessableEntityException('닉네임이 중복되어있습니다.')
        }
        const hashedPsword = await bcrypt.hash(psword, 10);

        const regDate = new Date();

        const save = await this.userService.create({ email, hashedPsword, nickname, regDate })
        console.log(save)
        return save.nickname
    }

    @Mutation(() => String)
    async deleteUser(
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

        await this.userService.delete({ email })
        return true
    }

    // @Query(() => String)
    // fetchUser(
    //     @CurrentUser() currentUser: any,
    // ) {
    //     console.log(currentUser)
    //     return "aasad"
    // }

}