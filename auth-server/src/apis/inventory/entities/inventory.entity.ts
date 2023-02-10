import { Field, Int, ObjectType } from '@nestjs/graphql'
import { Items } from 'src/apis/items/entities/items.entity'
import { User } from 'src/apis/users/entities/users.entity'
import { Column, Entity, JoinColumn, ManyToMany, ManyToOne, PrimaryColumn, PrimaryGeneratedColumn } from 'typeorm'


@Entity()
@ObjectType()
export class Inventory {

    @PrimaryGeneratedColumn('uuid')
    listnum: string

    @ManyToOne(() => User)
    user: User

    @ManyToOne(() => Items)
    item: Items

    @Column()
    @Field(() => String)
    fit: string

    @Column()
    @Field(() => Int)
    location: number


}