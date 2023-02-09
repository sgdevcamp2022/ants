import { PassportStrategy } from '@nestjs/passport'
import { Strategy } from 'passport-google-oauth20'

export class JwtGoogleStrategy extends PassportStrategy(Strategy, 'google') {
    constructor() {
        super({
            clientID: "559937059255-3tc69bfg2oets1lectmlqm5l82olpuf6.apps.googleusercontent.com",
            clientSecret: "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",
            callbackURL: 'http://localhost:3000/login/google',
            scope: ['email', 'profile'],

        });
    }

    validate(accessToken, refreshToken, profile) {
        console.log(accessToken)
        console.log(refreshToken)
        console.log(profile)
        return {
            email: profile.emails[0].value,
            psword: "0000",
            name: profile.displayName,
            nickname: "newOne"
        }
    }
}