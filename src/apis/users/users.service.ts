import { Injectable } from "@nestjs/common";
import { ConflictException } from "@nestjs/common/exceptions";
import { InjectRepository } from "@nestjs/typeorm";
import { Repository } from "typeorm";
import { User } from "./entities/users.entity";

@Injectable()
export class UserService {
    constructor(
        @InjectRepository(User)
        private readonly userRepository: Repository<User>
    ) { }





    async create({ email, hashedPsword: psword, name, nickname, regDate }) {
        const user = await this.userRepository.findOneBy({ email })
        if (user) {

            throw new ConflictException('이미 등록된 이메일 입니다.')
        }
        return await this.userRepository.save({ email, psword, name, nickname, regDate })
    }


    async findOne({ email }) {
        return await this.userRepository.findOneBy({ email })
    }

    async delete() {

    }

}