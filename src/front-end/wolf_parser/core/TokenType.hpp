#ifndef WOLF_TOKEN_TYPE_HPP_
#define WOLF_TOKEN_TYPE_HPP_

#include "Tree.hpp"

enum wTokenType {
    wNone,
    wLexerError,
    wFail,
    wEOF,
    wID,
    wDigit,
    wInt,
    wBool,
    wStudent,
    wEnter,
    wBotaet,
    wOneDay,
    wMeets,
    wDied,
    wWhile,
    wIf,
    wReturn,
    wOr,
    wAnd,
    wMore,
    wNotMore,
    wLess,
    wNotLess,
    wLogEq,
    wIsToxic,
    wIsNotToxic,
    wWatchesAs,
    wIsBullying,
    wSometimes,
    wGotBored,
    wOpen,
    wWithFriends,
    wCallFunc,
    wTrow,
    wRead,
    wWrite,
    wText,
    wDefVal,
    wSym46,
    wSym44,
    wSym58,
    wSym33,
    wSym43,
    wSym45,
    wSym42,
    wSym47,
    wProgram,
    wFunction,
    wStart,
    wMainFunction,
    wMainStart,
    wType,
    wEnd,
    wBlock,
    wSumExp,
    wMulExp,
    wExp,
    wIntExp,
    wOrExp,
    wAndExp,
    wLogicExp,
    wVarDecl,
};

union wTokenUnion {
    char* id;
    wNode* node;
    int64_t value;
};

static const char* TokenTypeGetName(wTokenType type) {
    switch (type) {
    case wTokenType::wID:
         return "ID";

    case wTokenType::wDigit:
         return "Digit";

    case wTokenType::wInt:
         return "Int";

    case wTokenType::wBool:
         return "Bool";

    case wTokenType::wStudent:
         return "Student";

    case wTokenType::wEnter:
         return "Enter";

    case wTokenType::wBotaet:
         return "Botaet";

    case wTokenType::wOneDay:
         return "OneDay";

    case wTokenType::wMeets:
         return "Meets";

    case wTokenType::wDied:
         return "Died";

    case wTokenType::wWhile:
         return "While";

    case wTokenType::wIf:
         return "If";

    case wTokenType::wReturn:
         return "Return";

    case wTokenType::wOr:
         return "Or";

    case wTokenType::wAnd:
         return "And";

    case wTokenType::wMore:
         return "More";

    case wTokenType::wNotMore:
         return "NotMore";

    case wTokenType::wLess:
         return "Less";

    case wTokenType::wNotLess:
         return "NotLess";

    case wTokenType::wLogEq:
         return "LogEq";

    case wTokenType::wIsToxic:
         return "IsToxic";

    case wTokenType::wIsNotToxic:
         return "IsNotToxic";

    case wTokenType::wWatchesAs:
         return "WatchesAs";

    case wTokenType::wIsBullying:
         return "IsBullying";

    case wTokenType::wSometimes:
         return "Sometimes";

    case wTokenType::wGotBored:
         return "GotBored";

    case wTokenType::wOpen:
         return "Open";

    case wTokenType::wWithFriends:
         return "WithFriends";

    case wTokenType::wCallFunc:
         return "CallFunc";

    case wTokenType::wTrow:
         return "Trow";

    case wTokenType::wRead:
         return "Read";

    case wTokenType::wWrite:
         return "Write";

    case wTokenType::wText:
         return "Text";

    case wTokenType::wDefVal:
         return "DefVal";

    case wTokenType::wSym46:
         return ".";

    case wTokenType::wSym44:
         return ",";

    case wTokenType::wSym58:
         return ":";

    case wTokenType::wSym33:
         return "!";

    case wTokenType::wSym43:
         return "+";

    case wTokenType::wSym45:
         return "-";

    case wTokenType::wSym42:
         return "*";

    case wTokenType::wSym47:
         return "/";

    case wTokenType::wProgram:
         return "Program";

    case wTokenType::wFunction:
         return "Function";

    case wTokenType::wStart:
         return "Start";

    case wTokenType::wMainFunction:
         return "MainFunction";

    case wTokenType::wMainStart:
         return "MainStart";

    case wTokenType::wType:
         return "Type";

    case wTokenType::wEnd:
         return "End";

    case wTokenType::wBlock:
         return "Block";

    case wTokenType::wSumExp:
         return "SumExp";

    case wTokenType::wMulExp:
         return "MulExp";

    case wTokenType::wExp:
         return "Exp";

    case wTokenType::wIntExp:
         return "IntExp";

    case wTokenType::wOrExp:
         return "OrExp";

    case wTokenType::wAndExp:
         return "AndExp";

    case wTokenType::wLogicExp:
         return "LogicExp";

    case wTokenType::wVarDecl:
         return "VarDecl";

    default:{}
    }
}
#endif // WOLF_TOKEN_TYPE_HPP_
