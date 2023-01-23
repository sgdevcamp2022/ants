import { Module } from "@nestjs/common";
import { TypeOrmModule } from "@nestjs/typeorm";
import { User } from "../users/entities/users.entity";
import { UserService } from "../users/users.service";
import { AuthResolver } from "./auth.resolver";
import { AuthService } from "./auth.service";

@Module({
    imports: [
        TypeOrmModule.forFeature([User])
    ],
    providers: [
        AuthResolver,
        AuthService,
        UserService,
    ],
})
export class AuthModule { }