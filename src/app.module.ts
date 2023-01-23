import { Module } from '@nestjs/common';
import { ApolloDriver, ApolloDriverConfig } from '@nestjs/apollo';
import { GraphQLModule } from '@nestjs/graphql';
import { TypeOrmModule } from '@nestjs/typeorm';
import { UserModule } from './apis/users/users.module';
import { FooResolver } from './app.resolver';
import { AuthModule } from './apis/auth/auth.module';

@Module({
  imports: [
    UserModule,
    AuthModule,
    GraphQLModule.forRoot<ApolloDriverConfig>({
      driver: ApolloDriver,
      autoSchemaFile: "src/commons/graphql/schema.gql",
      context: ({ req, res }) => ({ req, res })
    }),
    TypeOrmModule.forRoot({
      type: "mysql",
      host: "localhost",
      port: 3306,
      username: "root",
      password: "tjdfud*01",
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
