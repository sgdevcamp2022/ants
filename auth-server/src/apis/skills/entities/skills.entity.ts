import { Field, Int, ObjectType } from '@nestjs/graphql'
import { Jobs } from 'src/apis/jobs/entities/jobs.entity'
import { Column, Entity, JoinColumn, ManyToOne, PrimaryColumn } from 'typeorm'


@Entity()
@ObjectType()
export class Skills {

    @PrimaryColumn()
    @Field(() => String)
    code: string

    @Column()
    @Field(() => String)
    skillname: string

    @JoinColumn()
    @ManyToOne(() => Jobs)
    jobs: Jobs
}