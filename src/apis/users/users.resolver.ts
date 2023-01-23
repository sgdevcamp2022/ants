import { Resolver } from "@nestjs/graphql";
import { Mutation, Args } from "@nestjs/graphql"
import { User } from "./entities/users.entity";
import { UserService } from "./users.service";
import * as bcrypt from 'bcrypt';

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
        //this.userService.emailToken()

        return this.userService.create({ email, hashedPsword, name, nickname, regDate })
    }

}