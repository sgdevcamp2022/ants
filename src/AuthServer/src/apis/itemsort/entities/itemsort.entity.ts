import { Field, Int, ObjectType } from '@nestjs/graphql'
import { Items } from 'src/apis/items/entities/items.entity'
import { Column, Entity, JoinColumn, ManyToOne, PrimaryColumn } from 'typeorm'


@Entity()
@ObjectType()
export class ItemSort {

    @PrimaryColumn()
    @Field(() => String)
    code: string

    @Column()
    @Field(() => String)
    sortname: string

}