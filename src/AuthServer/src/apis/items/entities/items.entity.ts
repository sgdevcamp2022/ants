import { Field, Int, ObjectType } from '@nestjs/graphql'
import { ItemSort } from 'src/apis/itemsort/entities/itemsort.entity'
import { Column, Entity, JoinColumn, ManyToOne, PrimaryColumn } from 'typeorm'


@Entity()
@ObjectType()
export class Items {

    @PrimaryColumn()
    @Field(() => String)
    code: string

    @Column()
    @Field(() => String)
    itemname: string

    @Column()
    @Field(() => Int)
    itemprice: number

    @JoinColumn()
    @ManyToOne(() => ItemSort)
    itemsort: ItemSort
}