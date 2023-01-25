import { Module } from '@nestjs/common';
import { ApolloDriver, ApolloDriverConfig } from '@nestjs/apollo';
import { GraphQLModule } from '@nestjs/graphql';
import { TypeOrmModule } from '@nestjs/typeorm';
import { UserModule } from './apis/users/users.module';
import { FooResolver } from './app.resolver';
import { AuthModule } from './apis/auth/auth.module';
import { MailerModule } from '@nestjs-modules/mailer';
import { HandlebarsAdapter } from '@nestjs-modules/mailer/dist/adapters/handlebars.adapter'
import 'dotenv/config';

@Module({
  imports: [
    UserModule,
    AuthModule,
    MailerModule.forRoot({
      transport: {
        service: 'Naver',
        host: 'smtp.naver.com',
        port: 587,
        auth: {
          user: process.env.NAVER_ID, // 네이버 아이디
          pass: process.env.NAVER_PW, // 네이버 비밀번호
        },
      },
      template: {
        dir: process.cwd() + '/template/',
        adapter: new HandlebarsAdapter(), // or new PugAdapter()
        options: {
          strict: true,
        },
      },
    }),
    GraphQLModule.forRoot<ApolloDriverConfig>({
      driver: ApolloDriver,
      autoSchemaFile: "src/commons/graphql/schema.gql",
      context: ({ req, res }) => ({ req, res })
    }),
    TypeOrmModule.forRoot({
      type: "mysql",
      host: "localhost",
      port: 3306,
      username: process.env.DB_USERNAME,
      password: process.env.DB_PSWORD,
      database: "AntsTeam",
      entities: [__dirname + "/apis/**/*.entity.*"],
      synchronize: false,
      logging: true,

    })
  ],
  providers: [
    FooResolver
  ],
})
export class AppModule { }
