import { Module } from "@nestjs/common";
import { JwtModule } from "@nestjs/jwt";
import { TypeOrmModule } from "@nestjs/typeorm";
import { User } from "../users/entities/users.entity";
import { UserService } from "../users/users.service";
import { AuthResolver } from "./auth.resolver";
import { AuthService } from "./auth.service";

@Module({
    imports: [
        TypeOrmModule.forFeature([User]),
        JwtModule.register({

        })
    ],
    providers: [
        AuthResolver,
        AuthService,
        UserService,
    ],
})
export class AuthModule { }