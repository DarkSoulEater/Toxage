/* This code is generated automatically!
*
*/

// Wolf types
#include "core/WolfCore.hpp"

// Wolf Rules
wToken wParser::GetProgram() {
    InitRule(Program);

    View(None);
    switch (token.type) {
    case wTokenType::wGotBored:
    case wTokenType::wBool:
    case wTokenType::wInt:
    {
        while (View(GotBored)) { // [ ]*
            View(None);
            switch (token.type) {
            case wTokenType::wGotBored:
            {
                Get(Function);
                {
                    InsertNode();
                }
            } break;

            default:{error("");}
            }

        }
        Get(MainFunction);
        {
            InsertNode();
        }
    } break;

    default:{error("");}
    }

    Success();
}

wToken wParser::GetFunction() {
    InitRule(Function);

    View(None);
    switch (token.type) {
    case wTokenType::wGotBored:
    {
        Get(Start);
        {
            InsertNode();
        }
        Get(Block);
        {
            InsertNode();
        }
        Get(End);
        {
            InsertNode();
        }
    } break;

    default:{error("");}
    }

    Success();
}

wToken wParser::GetStart() {
    InitRule(Start);

    View(None);
    switch (token.type) {
    case wTokenType::wGotBored:
    {
        Get(GotBored);
        Get(Sym46);
        Get(Type);
        {
            InsertNode();
        }
        Get(ID);
        {
            InsertToken();
        }
        Get(Open);
        Get(ID);
        {
            InsertToken();
        }
        if (View(WithFriends)) { // [ ]~
            View(None);
            switch (token.type) {
            case wTokenType::wWithFriends:
            {
                Get(WithFriends);
                Get(Type);
                {
                    InsertNode();
                }
                Get(ID);
                {
                    InsertToken();
                }
                while (View(Sym44)) { // [ ]*
                    View(None);
                    switch (token.type) {
                    case wTokenType::wSym44:
                    {
                        Get(Sym44);
                        Get(Type);
                        {
                            InsertNode();
                        }
                        Get(ID);
                        {
                            InsertToken();
                        }
                    } break;

                    default:{error("");}
                    }

                }
            } break;

            default:{error("");}
            }

        }
        Get(Sym46);
        Get(ID);
        {
            InsertToken();
        }
        Get(Botaet);
        Get(Sym46);
    } break;

    default:{error("");}
    }

    Success();
}

wToken wParser::GetMainFunction() {
    InitRule(MainFunction);

    View(None);
    switch (token.type) {
    case wTokenType::wBool:
    case wTokenType::wInt:
    {
        Get(MainStart);
        {
            InsertNode();
        }
        Get(Block);
        {
            InsertNode();
        }
        Get(End);
        {
            InsertNode();
        }
    } break;

    default:{error("");}
    }

    Success();
}

wToken wParser::GetMainStart() {
    InitRule(MainStart);

    View(None);
    switch (token.type) {
    case wTokenType::wBool:
    case wTokenType::wInt:
    {
        Get(Type);
        {
            InsertNode();
        }
        Get(ID);
        {
            InsertToken();
        }
        Get(Enter);
        Get(ID);
        {
            InsertToken();
        }
        Get(Sym46);
        Get(ID);
        {
            InsertToken();
        }
        Get(Botaet);
        Get(Sym46);
    } break;

    default:{error("");}
    }

    Success();
}

wToken wParser::GetType() {
    InitRule(Type);

    View(None);
    switch (token.type) {
    case wTokenType::wBool:
    case wTokenType::wInt:
    {
        View(None);
        switch (token.type) { // [ ]?
        case wTokenType::wBool:
        {
            Get(Bool);
        } break;

        case wTokenType::wInt:
        {
            Get(Int);
        } break;

        default:{error("");}
        }

        {
            InsertToken();
        }
    } break;

    default:{error("");}
    }

    Success();
}

wToken wParser::GetEnd() {
    InitRule(End);

    View(None);
    switch (token.type) {
    case wTokenType::wID:
    {
        Get(ID);
        {
            InsertToken();
        }
        Get(Died);
        Get(Sym46);
    } break;

    default:{error("");}
    }

    Success();
}

wToken wParser::GetBlock() {
    InitRule(Block);

    View(None);
    switch (token.type) {
    case wTokenType::wIf:
    case wTokenType::wOneDay:
    case wTokenType::wSometimes:
    case wTokenType::wWhile:
    {
        if (!(View(If) || View(OneDay) || View(Sometimes) || View(While))) // [ ]+
            error("");
        while (View(If) || View(OneDay) || View(Sometimes) || View(While)) { // [ ]*
            View(None);
            switch (token.type) {
            case wTokenType::wIf:
            case wTokenType::wOneDay:
            case wTokenType::wSometimes:
            case wTokenType::wWhile:
            {
                View(None);
                switch (token.type) { // [ ]?
                case wTokenType::wOneDay:
                {
                    Get(VarDecl);
                    {
                        InsertNode();
                    }
                } break;

                case wTokenType::wIf:
                case wTokenType::wWhile:
                {
                    View(None);
                    switch (token.type) { // [ ]?
                    case wTokenType::wWhile:
                    {
                        Get(While);
                    } break;

                    case wTokenType::wIf:
                    {
                        Get(If);
                    } break;

                    default:{error("");}
                    }

                    {
                        InsertToken();
                    }
                    Get(LogicExp);
                    {
                        ret_val.value.node->kids_[ret_val.value.node->kids_.Size() - 1]->Insert(token.value.node);
                    }
                    Get(Sym58);
                    Get(Block);
                    {
                        ret_val.value.node->kids_[ret_val.value.node->kids_.Size() - 1]->Insert(token.value.node);
                    }
                    Get(Sym33);
                } break;

                case wTokenType::wSometimes:
                {
                    Get(Sometimes);
                    Get(ID);
                    {
                        InsertToken();
                    }
                    View(None);
                    switch (token.type) { // [ ]?
                    case wTokenType::wReturn:
                    {
                        Get(Return);
                        {
                            InsertToken();
                        }
                    } break;

                    case wTokenType::wWatchesAs:
                    {
                        Get(WatchesAs);
                        {
                            InsertToken();
                        }
                        Get(SumExp);
                        {
                            InsertNode();
                        }
                    } break;

                    case wTokenType::wIsBullying:
                    {
                        Get(IsBullying);
                        {
                            InsertToken();
                        }
                        Get(LogicExp);
                        {
                            InsertNode();
                        }
                    } break;

                    case wTokenType::wCallFunc:
                    {
                        Get(CallFunc);
                        {
                            InsertToken();
                        }
                        Get(ID);
                        {
                            InsertToken();
                        }
                        if (View(And)) { // [ ]~
                            View(None);
                            switch (token.type) {
                            case wTokenType::wAnd:
                            {
                                Get(And);
                                Get(Trow);
                                Get(ID);
                                {
                                    InsertToken();
                                }
                                while (View(Sym44)) { // [ ]*
                                    View(None);
                                    switch (token.type) {
                                    case wTokenType::wSym44:
                                    {
                                        Get(Sym44);
                                        Get(ID);
                                        {
                                            InsertToken();
                                        }
                                    } break;

                                    default:{error("");}
                                    }

                                }
                            } break;

                            default:{error("");}
                            }

                        }
                    } break;

                    case wTokenType::wRead:
                    {
                        Get(Read);
                        {
                            InsertToken();
                        }
                    } break;

                    case wTokenType::wWrite:
                    {
                        Get(Write);
                        {
                            InsertToken();
                        }
                        Get(Text);
                        {
                            InsertToken();
                        }
                    } break;

                    default:{error("");}
                    }

                } break;

                default:{error("");}
                }

                Get(Sym46);
            } break;

            default:{error("");}
            }

        }
    } break;

    default:{error("");}
    }

    Success();
}

wToken wParser::GetSumExp() {
    InitRule(SumExp);

    View(None);
    switch (token.type) {
    case wTokenType::wID:
    case wTokenType::wSym44:
    {
        Get(MulExp);
        {
            InsertNode();
        }
        while (View(Sym43) || View(Sym45)) { // [ ]*
            View(None);
            switch (token.type) {
            case wTokenType::wSym43:
            case wTokenType::wSym45:
            {
                View(None);
                switch (token.type) { // [ ]?
                case wTokenType::wSym43:
                {
                    Get(Sym43);
                } break;

                case wTokenType::wSym45:
                {
                    Get(Sym45);
                } break;

                default:{error("");}
                }

                {
                    InsertToken();
                }
                Get(MulExp);
                {
                    InsertNode();
                }
            } break;

            default:{error("");}
            }

        }
    } break;

    default:{error("");}
    }

    Success();
}

wToken wParser::GetMulExp() {
    InitRule(MulExp);

    View(None);
    switch (token.type) {
    case wTokenType::wID:
    case wTokenType::wSym44:
    {
        Get(Exp);
        {
            InsertNode();
        }
        while (View(Sym42) || View(Sym47)) { // [ ]*
            View(None);
            switch (token.type) {
            case wTokenType::wSym42:
            case wTokenType::wSym47:
            {
                View(None);
                switch (token.type) { // [ ]?
                case wTokenType::wSym42:
                {
                    Get(Sym42);
                } break;

                case wTokenType::wSym47:
                {
                    Get(Sym47);
                } break;

                default:{error("");}
                }

                {
                    InsertToken();
                }
                Get(Exp);
                {
                    InsertNode();
                }
            } break;

            default:{error("");}
            }

        }
    } break;

    default:{error("");}
    }

    Success();
}

wToken wParser::GetExp() {
    InitRule(Exp);

    View(None);
    switch (token.type) {
    case wTokenType::wID:
    {
        Get(ID);
        {
            InsertToken();
        }
    } break;


    case wTokenType::wSym44:
    {
        Get(Sym44);
        Get(SumExp);
        {
            InsertNode();
        }
        Get(Sym46);
    } break;

    default:{error("");}
    }

    Success();
}

wToken wParser::GetIntExp() {
    InitRule(IntExp);

    View(None);
    switch (token.type) {
    case wTokenType::wID:
    {
        Get(ID);
        {
            InsertToken();
        }
    } break;


    case wTokenType::wSym44:
    {
        Get(Sym44);
        {
            InsertToken();
        }
        Get(IntExp);
        {
            InsertNode();
        }
        View(None);
        switch (token.type) { // [ ]?
        case wTokenType::wSym43:
        {
            Get(Sym43);
        } break;

        case wTokenType::wSym45:
        {
            Get(Sym45);
        } break;

        case wTokenType::wSym42:
        {
            Get(Sym42);
        } break;

        case wTokenType::wSym47:
        {
            Get(Sym47);
        } break;

        default:{error("");}
        }

        {
            InsertToken();
        }
        Get(IntExp);
        {
            InsertNode();
        }
        Get(Sym46);
        {
            InsertToken();
        }
    } break;

    default:{error("");}
    }

    Success();
}

wToken wParser::GetOrExp() {
    InitRule(OrExp);

    View(None);
    switch (token.type) {
    case wTokenType::wID:
    case wTokenType::wSym44:
    {
        Get(AndExp);
        {
            InsertNode();
        }
        while (View(Or)) { // [ ]*
            View(None);
            switch (token.type) {
            case wTokenType::wOr:
            {
                Get(Or);
                {
                    InsertToken();
                }
                Get(AndExp);
                {
                    InsertNode();
                }
            } break;

            default:{error("");}
            }

        }
    } break;

    default:{error("");}
    }

    Success();
}

wToken wParser::GetAndExp() {
    InitRule(AndExp);

    View(None);
    switch (token.type) {
    case wTokenType::wID:
    case wTokenType::wSym44:
    {
        Get(LogicExp);
        {
            InsertNode();
        }
        while (View(And)) { // [ ]*
            View(None);
            switch (token.type) {
            case wTokenType::wAnd:
            {
                Get(And);
                {
                    InsertToken();
                }
                Get(LogicExp);
                {
                    InsertNode();
                }
            } break;

            default:{error("");}
            }

        }
    } break;

    default:{error("");}
    }

    Success();
}

wToken wParser::GetLogicExp() {
    InitRule(LogicExp);

    View(None);
    switch (token.type) {
    case wTokenType::wID:
    {
        Get(ID);
        {
            InsertToken();
        }
        View(None);
        switch (token.type) { // [ ]?
        case wTokenType::wLess:
        case wTokenType::wMore:
        case wTokenType::wNotLess:
        case wTokenType::wNotMore:
        {
            View(None);
            switch (token.type) { // [ ]?
            case wTokenType::wMore:
            {
                Get(More);
            } break;

            case wTokenType::wNotMore:
            {
                Get(NotMore);
            } break;

            case wTokenType::wLess:
            {
                Get(Less);
            } break;

            case wTokenType::wNotLess:
            {
                Get(NotLess);
            } break;

            default:{error("");}
            }

            {
                InsertToken();
            }
            Get(ID);
            {
                InsertToken();
            }
        } break;

        case wTokenType::wLogEq:
        {
            Get(LogEq);
            {
                InsertToken();
            }
            Get(Digit);
            {
                InsertToken();
            }
        } break;

        case wTokenType::wIsNotToxic:
        case wTokenType::wIsToxic:
        {
            View(None);
            switch (token.type) { // [ ]?
            case wTokenType::wIsToxic:
            {
                Get(IsToxic);
            } break;

            case wTokenType::wIsNotToxic:
            {
                Get(IsNotToxic);
            } break;

            default:{error("");}
            }

            {
                InsertToken();
            }
        } break;

        default:{error("");}
        }

    } break;


    case wTokenType::wSym44:
    {
        Get(Sym44);
        Get(OrExp);
        Get(Sym46);
    } break;

    default:{error("");}
    }

    Success();
}

wToken wParser::GetVarDecl() {
    InitRule(VarDecl);

    View(None);
    switch (token.type) {
    case wTokenType::wOneDay:
    {
        Get(OneDay);
        Get(ID);
        {
            InsertToken();
        }
        Get(Meets);
        Get(Type);
        {
            InsertNode();
        }
        Get(ID);
        {
            InsertToken();
        }
        if (View(DefVal)) { // [ ]~
            View(None);
            switch (token.type) {
            case wTokenType::wDefVal:
            {
                Get(DefVal);
                {
                    InsertToken();
                }
                Get(Digit);
                {
                    InsertToken();
                }
            } break;

            default:{error("");}
            }

        }
    } break;

    default:{error("");}
    }

    Success();
}

// The main wolf parser function
wToken wParser::StartParse() {
    auto res_parse = GetProgram();
    auto token = lexer_.ViewToken();

    if (syntax_state_ == false || token.type != wTokenType::wEOF)
        return wToken(wTokenType::wFail);

    return res_parse;
}

// Prints all tokens up to EOF
void wParser::TestLexer() {
    for (auto tk = lexer_.GetToken(); tk.type != wTokenType::wEOF; tk = lexer_.GetToken()) {
        tk.Print();
    }
}
