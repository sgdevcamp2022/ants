import { Query, Resolver, Mutation, Args } from "@nestjs/graphql";
import { User } from "./entities/users.entity";
import { UserService } from "./users.service";
import * as bcrypt from 'bcrypt';
import { UseGuards } from '@nestjs/common'
import { GqlAuthAccessGuard } from "src/commons/auth/gql-auth.guard";
import { CurrentUser } from "src/commons/auth/gql-user.param";

@Resolver()
export class UserResolver {
    constructor(
        private readonly userService: UserService
    ) { }

    @Mutation(() => User)
    async createUser(
        @Args('email') email: string,
        @Args('psword') psword: string,
        @Args('name') name: string,
        @Args('nickname') nickname: string,
        @Args('regDate') regDate: Date,
    ) {

        const hashedPsword = await bcrypt.hash(psword, 10);

        return this.userService.create({ email, hashedPsword, name, nickname, regDate })
    }

    @UseGuards(GqlAuthAccessGuard)
    @Mutation(() => Boolean)
    async deleteUser(
        @Args('email') email: string,
    ) {
        this.userService.delete()
        //부드러운 삭제 구현하기
    }

    @UseGuards(GqlAuthAccessGuard)
    @Query(() => String)
    fetchUser(
        @CurrentUser() currentUser: any,
    ) {
        console.log(currentUser)
        return "aasad"
    }

}