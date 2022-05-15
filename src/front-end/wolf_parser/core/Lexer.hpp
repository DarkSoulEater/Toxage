#ifndef WOLF_LEXER_HPP
#define WOLF_LEXER_HPP

#include <cctype>
#include <assert.h>
#include "Token.hpp"
#include "Logger.hpp"
#include "Vector.hpp"

class wLexer {
private:
    Vector<wToken> tokens_;

    size_t active_token_;

    const char* file_name_;

public:
    wLexer(void* data, const char* file_name) : active_token_(0), line_(1), column_(0), data_((char*)data), file_name_(file_name) {}

    ~wLexer() {}

    wToken GetToken() {
        assert(active_token_ <= tokens_.Size());
        if (active_token_ == tokens_.Size()) tokens_.PushBack(Lex());
        return tokens_[active_token_++];
    }

    wToken ViewToken() {
        assert(active_token_ <= tokens_.Size());
        if (active_token_ == tokens_.Size()) tokens_.PushBack(Lex());
        return tokens_[active_token_];
    }

    void UngetToken() {
        assert(active_token_);
        --active_token_;
    }

    #define ReturnToken(TYPE)           \
        token.type = wTokenType::TYPE;  \
        return token;     

    wToken Lex();

private: 
    size_t line_;
    size_t column_;

    char* data_;

    char Getc() {
        char*& c = data_;
        if (*c == '\0') return *c;
        if (*c == '\r') ++c;

        ++column_;
        if (*c == '\n') {
            column_ = 0;
            line_  += 1;
        }

        return *c++;
    }
};

#endif // WOLF_LEXER_HPP