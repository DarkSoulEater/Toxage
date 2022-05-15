#include <iostream>
#include <Buffer.hpp>
#include "Parser.hpp"

void ParseArgs(const int argc, const char* argv[]);

#include <map>

#define SkipString()                    \
    while (std::isalpha(*data_)) {      \
        c = Getc();                     \
    }

#define DeclWord(TEXT) TEXT,
enum class Word {
        #include "Word.decl"
        not_,
        and_,
        or_,
        new_,
};   

std::pair<int, Word> GetWord_(std::map<std::string, Word>& map, char* data) {
    std::pair<int, Word> res = {0, Word::NONE};
    char* save_data = data;
    while (std::isalpha(*data)) {
        ++res.first;
        ++data;
    }
    auto fres = map.find(std::string(save_data, res.first));
    if (fres != map.end()) {
        res.second = fres->second;
    }
    return res;
}

#define GetWord(WORD) {                 \
    auto res = GetWord_(map, data_ - 1);\
    if (res.second == Word::WORD) {     \
        state = true;                   \
        while (--res.first) {           \
            c = Getc();                 \
        }                               \
                                        \
        while (std::isspace(*data_))    \
            c = Getc();                 \
                                        \
    } else {                            \
        state = false;                  \
    }                                   \
                                        }

#define CheckState(TEXT)                        \
    if (!state) {                               \
        wLogger.PrintError(TEXT);               \
        ReturnToken(wLexerError);               \
                                                }
// Lexical analysis
wToken wLexer::Lex() {
    #define DeclWord(TEXT) {#TEXT, Word::TEXT},
    static std::map<std::string, Word> map = {
        #include "Word.decl"
        {"not", Word::not_},
        {"or", Word::or_},
        {"and", Word::and_},
        {"new", Word::new_},
    };

    char c = 0;
    while (std::isspace(c = Getc())) 
        ;

    wToken token(line_, column_, wTokenType::wEOF);

    if (std::isdigit(c)) {
        int64_t dig = c - '0';
        while (std::isdigit(*data_)) {
            c = Getc();
            dig = dig * 10 + c - '0';
        }
        //token.value.value = dig;
        ReturnToken(wDigit);
    }

    if (std::isalpha(c)) {
        bool state = false;

        GetWord(The);
        bool sv_state = state;
        GetWord(the);
        if (state | sv_state) {
            c = Getc();
            GetWord(student);
            if (state) {
                ReturnToken(wInt);
            }

            GetWord(not_)
            if (state) {
                // TODO: Set def Val
                c = Getc();
            }
            GetWord(toxic);
            if (state) {
                ReturnToken(wBool);
            }

            wLogger.PrintError("Expected \"student\" or \"toxic\"");
            ReturnToken(wLexerError);
        }

        // div
        GetWord(debug);
        if (state) {
            c = Getc();
            GetWord(the);
            CheckState("Expected \"the\"");

            c = Getc();
            GetWord(program);
            CheckState("Expected \"program\"");

            ReturnToken(wSym47);
        }

        // *
        GetWord(learn);
        if (state) {
            c = Getc();
            GetWord(mathan);
            CheckState("Expected \"mathan\"");

            c = Getc();
            GetWord(with);
            CheckState("Expected \"with\"");

            ReturnToken(wSym42);
        }

        // + or -
        GetWord(find);
        if (state) {
            c = Getc();
            GetWord(a);
            if (!state) {
                wLogger.PrintError("Expected \"a\"");
                ReturnToken(wLexerError);
            }
            // TODO:
            // 2- or 2-
            c = Getc();
            if (!std::isdigit(c)) {
                wLogger.PrintError("Expected number");
                ReturnToken(wLexerError);
            }
            int num = 0;
            while (std::isdigit(c)) {
                num = num * 10 + c - '0';
                c = Getc();
            }
            
            c = Getc();
            GetWord(aligned);
            if (!state) {
                wLogger.PrintError("Expected \"aligned\"");
                ReturnToken(wLexerError);
            }

            c = Getc();
            GetWord(pointer);
            if (!state) {
                wLogger.PrintError("Expected \"pointer\"");
                ReturnToken(wLexerError);
            }

            c = Getc();
            GetWord(in);
            if (!state) {
                wLogger.PrintError("Expected \"in\"");
                ReturnToken(wLexerError);
            }

            c = Getc();
            GetWord(code);
            if (!state) {
                wLogger.PrintError("Expected \"code\"");
                ReturnToken(wLexerError);
            }

            if (num % 2 == 1) {
                ReturnToken(wSym43);
            } else {
                ReturnToken(wSym45);
            }
        }

        // More toxic
        GetWord(more);
        if (state) {
            c = Getc();
            GetWord(toxic);
            CheckState("know the toxic!!!");
            ReturnToken(wMore);
        }

        // Less toxic
        GetWord(less);
        if (state) {
            c = Getc();
            GetWord(toxic);
            CheckState("know the toxic!!!");
            ReturnToken(wLess);
        }

        // Not more toxic OR Not less toxic
        GetWord(not_);
        if (state) {
            c = Getc();
            GetWord(more);
            bool is_more = state;
            if (!state) {
                GetWord(less);
                CheckState("Expected \"more\" OR \"less\"");
            }

            c = Getc();
            GetWord(toxic);
            CheckState("know the toxic!!!");
            if (is_more) {
                ReturnToken(wMore);
            } else {
                ReturnToken(wLess);
            }
        }

        // toxicity is
        GetWord(toxicity);
        if (state) {
            c = Getc();
            GetWord(is);
            CheckState("Expected \"is\"");
            ReturnToken(wLogEq);
        }

        // Is toxic OR Is not toxic OR is bullying
        GetWord(is);
        if (state) {
            c = Getc();
            GetWord(bullying);
            if (state) {
                ReturnToken(wIsBullying);
            }   

            GetWord(not_);
            bool with_not = state;
            if (state) {
                c = Getc();
            }

            GetWord(toxic);
            CheckState("know the toxic or bullying!!!");
            if (with_not) {
                ReturnToken(wIsNotToxic);
            } else {
                ReturnToken(wIsToxic);
            }
        }

        // And
        GetWord(and_);
        if (state) {
            ReturnToken(wAnd);
        }

        // Or
        GetWord(or_);
        if (state) {
            ReturnToken(wOr);
        }

        // watches as
        GetWord(watches);
        if (state) {
            c = Getc();
            GetWord(as);
            if (!state) {
                wLogger.PrintError("Expected \"as\"");
                ReturnToken(wLexerError);   
            }

            ReturnToken(wWatchesAs);
        }

        // out the window (return)
        GetWord(out);
        if (state) {
            c = Getc();
            GetWord(the);
            if (!state) {
                wLogger.PrintError("Expected \"the\"");
                ReturnToken(wLexerError);
            }

            c = Getc();
            GetWord(window);
            if (!state) {
                wLogger.PrintError("Expected \"window\"");
                ReturnToken(wLexerError);
            }
            ReturnToken(wReturn);
        }

        // Got bored (NEW FUNCTION)
        GetWord(Got);
        if (state) {
            c = Getc();
            GetWord(bored);
            CheckState("Expected \"bored\"");
            ReturnToken(wGotBored);
        }

        // Open new frame
        GetWord(open);
        if (state) {
            c = Getc();
            GetWord(new_);
            CheckState("Expected \"new\"");

            c = Getc();
            GetWord(frame);
            CheckState("Expected \"frame\"");

            ReturnToken(wOpen);
        }

        // With
        GetWord(with);
        if (state) {
            c = Getc();
            GetWord(friends);
            if (state) {
                ReturnToken(wWithFriends);
            }
            GetWord(toxicity);
            if (state) {
                ReturnToken(wDefVal);
            }
            
            CheckState("Expected \"friends\" OR \"toxicity\"");
        }

        // Sometimes
        GetWord(Sometimes);
        if (state) {
            ReturnToken(wSometimes);
        }

        // While
        GetWord(While);
        if (state) {
            ReturnToken(wWhile);
        }

        // If
        GetWord(If);
        if (state) {
            ReturnToken(wIf);
        }

        // Enter to...
        GetWord(enter);
        if (state) {
            c = Getc();
            GetWord(to);
            if (state) {
                ReturnToken(wEnter);
            }

            wLogger.PrintError("Expected \"to\"");
            ReturnToken(wLexerError);
        }
        
        // Botaet
        GetWord(botaet);
        if (state) {
            ReturnToken(wBotaet);
        }

        // One
        GetWord(One);
        if (state) {
            c = Getc();
            GetWord(day); // One day
            if (!state) {
                wLogger.PrintError("May be day?");
                ReturnToken(wLexerError);
            }

            ReturnToken(wOneDay);
        }

        // meets...
        GetWord(meets);
        if (state) {
            ReturnToken(wMeets);
        }

        GetWord(died);
        if (state) {
            ReturnToken(wDied);
        }

        while (std::isalpha(*data_)) {
            c = Getc();
        }   
        ReturnToken(wID);
    }

    switch (c) {
    case '\0':
        ReturnToken(wEOF);
        break;

    case '.':
        ReturnToken(wSym46);
        break;

    case ':':
        ReturnToken(wSym58);
        break;

    case ',':
        ReturnToken(wSym44);
        break;

    case '!':
        ReturnToken(wSym33);
        break;
    
    default:
        ReturnToken(wLexerError);
        break;
    }
}

int main(const int argc, const char* argv[]) {
    ParseArgs(argc, argv);
    const char* file_name = "C:/Users/eleno/C++/Toxage/test/test_1.txt";
    Buffer buf(file_name);

    if (buf.GetData() == nullptr) {
        wLogger.LogError("File not found. Break");
        return 0;
    }

    wParser parser(buf.GetData(), file_name);
    //parser.TestLexer(); return 0;
    auto tk = parser.StartParse();

    if (tk.type != wTokenType::wFail) {
        wLogger.Log("Ok grammar");
        tk.value.node->GraphicsDump();
        wLogger.Log("Ok dump");
    } else {
        wLogger.PrintError("Failed grammar");
    }
    return 0;
}

void ParseArgs(const int argc, const char* argv[]) {
    for (int i = 0; i < argc; ++i) {
        printf("%s ", argv[i]);
    }
    printf("\n\n");
}