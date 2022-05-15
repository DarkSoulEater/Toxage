#ifndef WOLF_TOKEN_HPP
#define WOLF_TOKEN_HPP

#include <cstddef>
#include "TokenType.hpp"

struct wToken {
    wTokenType type;
    
    size_t line   = 0;
    size_t column = 0;

    wTokenUnion value;

    wToken(wTokenType type) : line(0), column(0), type(type) {} 

    wToken(size_t line, size_t column, wTokenType type) 
        : line(line), column(column), type(type) {}

    const char* GetTypeName() const {
        return TokenTypeGetName(type);
    }

    void Print() const {
        std::cout << "TOKEN(" << line << ":" << column << ") : " << GetTypeName() << "\n";
    }
};

//using wToken = Token<wTokenType, wTokenUnion>

#endif // WOLF_TOKEN_HPP