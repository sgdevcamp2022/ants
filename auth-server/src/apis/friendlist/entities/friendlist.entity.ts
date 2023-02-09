import { Field, ObjectType } from '@nestjs/graphql'
import { User } from 'src/apis/users/entities/users.entity'
import { Column, Entity, JoinColumn, ManyToOne, PrimaryColumn, PrimaryGeneratedColumn } from 'typeorm'


@Entity()
@ObjectType()
export class FriendList {

    @PrimaryGeneratedColumn('uuid')
    listnum: string

    @Column()
    @Field(() => String)
    friendNick: string

    @ManyToOne(() => User)
    user: User

}