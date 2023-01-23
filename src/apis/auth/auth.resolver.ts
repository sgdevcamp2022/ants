import { Context, Resolver } from "@nestjs/graphql";
import { Mutation, Args } from "@nestjs/graphql"
import * as bcrypt from 'bcrypt';
import { User } from "../users/entities/users.entity";
import { UserService } from "../users/users.service";
import { AuthService } from "./auth.service";

@Resolver()
export class AuthResolver {
    constructor(
        //private readonly authService: AuthService,
        private readonly userService: UserService,
    ) { }

    @Mutation(() => User)
    async login(
        @Args('email') email: string,
        @Args('psword') psword: string,
        @Context() context: any,  //cookie 관련된거
    ) {
        const user = await this.userService.findOne({ email })
        if (user) {
            const isMatch = await bcrypt.compare(psword, user.psword);
            console.log(isMatch)

            if (isMatch) {
                return user
                //accesstoken
            }
        }

    }


}