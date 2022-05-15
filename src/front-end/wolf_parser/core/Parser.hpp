#ifndef WOLF_PARSER_HPP
#define WOLF_PARSER_HPP

#include <iostream>
#include "Token.hpp"
#include "Logger.hpp"
#include "Lexer.hpp"
#include "Tree.hpp"
#include "Vector.hpp"

#pragma GCC diagnostic ignored "-Wswitch-enum"

class wParser {
private:
    wLexer lexer_;

    const char* file_name_;
public:
    wParser(void* data, const char* file_name) : lexer_(data, file_name_), file_name_(file_name) {}
    ~wParser() {}

#ifndef DeclLexerTarget
    #define DeclLexerTarget(NAME)                       \
        wToken Get##NAME() {                            \
            wToken ret(0, 0, wTokenType::w##NAME);      \
            wToken token = lexer_.GetToken();           \
                                                        \
            if (token.type != wTokenType::w##NAME){     \
                Error(ret, token, "");                 }\
            return token;                               \
        }
#endif

    #include "ParserToken.decl"

#ifndef InitRule
    #define InitRule(RULE_NAME)                                 \
        wToken ret_val(0ull, 0ull, wTokenType::w##RULE_NAME);   \
        ret_val.value.node = new wNode(ret_val);                \
        wToken token = lexer_.ViewToken();
#endif  

#ifndef Succes
    #define Success() return ret_val; 
#endif

    #define Get(TYPE)                       \
        token = Get##TYPE();                \

    #define View(TYPE) ((token = lexer_.ViewToken()).type == wTokenType::w##TYPE)
    #define error(TEXT) Error(ret_val, token, TEXT)

    #define SaveLocation() {                                \
        ret_val.value.node->data_.line = token.line;        \
        ret_val.value.node->data_.column = token.column;    }

    #define ValNode ret_val.value.node
    #define RetVal ret_val.value
    #define TokenVal token.value
    #define TokenNode token.value.node

    #define InsertToken() ret_val.value.node->Insert(token)
    #define InsertNode() ret_val.value.node->Insert(token.value.node)
    #define InsertKids() ret_val.value.node->InsertKid(token.value.node)

    #include "ParserRule.decl"
    
    wToken StartParse();
    void TestLexer();

private:
    bool syntax_state_ = true;

    wToken Error(wToken& ret, wToken& token, const char* text) {
        if (text[0] == '\0')
            wLogger.PrintError(file_name_, token.line, token.column, "expected %s, but find %s", ret.GetTypeName(), token.GetTypeName());
        else 
            wLogger.PrintError(file_name_, token.line, token.column, text, token.GetTypeName());

        syntax_state_ = false;
    }
};

#endif // WOLF_PARSER_HPP