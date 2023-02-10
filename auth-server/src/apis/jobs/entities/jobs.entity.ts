import { Field, ObjectType } from '@nestjs/graphql'
import { Column, Entity, PrimaryColumn } from 'typeorm'


@Entity()
@ObjectType()
export class Jobs {

    @PrimaryColumn()
    @Field(() => String)
    code: string

    @Column()
    @Field(() => String)
    jobname: string

}