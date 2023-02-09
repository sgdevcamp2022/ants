import { Field, ObjectType } from '@nestjs/graphql'
import { Column, Entity, PrimaryColumn } from 'typeorm'


@Entity()
@ObjectType()
export class Jobs {

    @PrimaryColumn()
    @Field(() => String)
    jobcode: string

    @Column()
    @Field(() => String)
    jobname: string

}