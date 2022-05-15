#ifndef TOXAGE_GENERATOR_HPP
#define TOXAGE_GENERATOR_HPP

#include "WolfCore.hpp"
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <string.h>

class Generator {
private:
    wNode* root;

    std::ofstream lst;
    std::ofstream out;
public:
    Generator(wNode* node) : root(node) {}

    void Generate(const char* file_name) {
        lst.open("res/lst.txt");
        out.open(file_name);

        size_t i = 0; 
        for (; i < root->kids_.Size(); ++i) {
            if (root->kids_[i]->data_.type == wTokenType::wFunction) {
                GenerateFunc(root->kids_[i]);
            }
        }
        GenerateFunc(root->kids_[i - 1]);

        wLogger.LogDebug("All functions:");
        for (const auto& func : funcs) {
            std::cout << "    " << func.first << "\n";
        }

        lst.close();
        out.close();
    }

private:
    bool generate_state = true;
    enum class Type {
        Bool,
        Int
    };

    #define GetType(TOKEN) (TOKEN->data_.type == wTokenType::wBool ? Type::Bool : Type::Int)

    struct FuncInfo {
        Type ret_type;
        const char* ret_name;
        const char* func_name;
        std::vector<Type> params;

        FuncInfo(Type ret_type_, const char* ret_name_, const char* func_name_, const std::vector<Type>& params_)
        : ret_type(ret_type_)
        , ret_name(ret_name_)
        , func_name(func_name_)
        , params(params_)
         {}
    }; 

    struct VarInfo {
        std::string name;
        Type type;
        size_t address;
    };
    
    #define PrintLST(TEXT) {lst << "    " << TEXT << "\n";}
    
    std::unordered_map<std::string, FuncInfo> funcs;

    void GenerateFunc(wNode* node) {
        // Start
        wNode* start_node = node->kids_[0];
        auto res = funcs.find(start_node->kids_[2]->data_.value.id);
        if (res != funcs.end()) {
            wLogger.PrintError("Two buildings (%s and %s) with the same name. not enough imagination?", start_node->kids_[2]->data_.value, res->first);
            generate_state = false;
        }

        Type ret_type = (start_node->kids_[0]->data_.type == wTokenType::wBool ? Type::Bool : Type::Int);
        std::vector<Type> params;

        std::unordered_map<std::string, VarInfo> vars;
        vars.insert({
            std::string(start_node->kids_[1]->data_.value.id),
            {
                std::string(start_node->kids_[1]->data_.value.id)
            ,   start_node->kids_[0]->data_.type == wTokenType::wBool ? Type::Bool : Type::Int
            ,   0
            }
        });
        std::cout << vars.begin()->first << "\n";

        for (size_t i = 3; i < start_node->kids_.Size() - 1; i += 2) {
            params.push_back(start_node->kids_[i]->data_.type == wTokenType::wBool ? Type::Bool : Type::Int);
            vars.insert({
                std::string(start_node->kids_[i + 1]->data_.value.id),
                {
                    std::string(start_node->kids_[i + 1]->data_.value.id)
                ,   start_node->kids_[i]->data_.type == wTokenType::wBool ? Type::Bool : Type::Int
                ,   vars.size() * 8
                }
            });
        }

        FuncInfo func_info = { ret_type
                            ,  start_node->kids_[1]->data_.value.id
                            ,  start_node->kids_[2]->data_.value.id
                            ,  params
                            };
    
        funcs.insert({std::string(start_node->kids_[2]->data_.value.id), func_info});

        if (strcmp(start_node->kids_[start_node->kids_.Size() - 1]->data_.value.id, start_node->kids_[1]->data_.value.id) != 0) {
            wLogger.LogError("Who botaet?");
            generate_state = false;
        }

        // Block
        wLogger.LogDebug("Params var:");
        for (const auto& v : vars) {
            std::cout << "    " << v.first << "\n";
        }
        std::cout << "\n";

        lst << func_info.func_name << ":\n";

        wNode* block_node = node->kids_[1];
        for (size_t i = 0; i < block_node->kids_.Size(); ++i) {
            GenerateBlock(block_node->kids_[i], vars, func_info);
        }

        lst << "\n\n";


        // End
        wNode* end_node = node->kids_[2];
        if (strcmp(end_node->kids_[0]->data_.value.id, start_node->kids_[1]->data_.value.id) != 0) {
            wLogger.LogError("Who died?");
            generate_state = false;
        }
    }

    void GenerateBlock(wNode* node, std::unordered_map<std::string, VarInfo>& vars, FuncInfo& func_info) {
        switch (node->data_.type) {
        case wTokenType::wVarDecl: {
            if (strcmp(node->kids_[0]->data_.value.id, func_info.ret_name) != 0) {
                wLogger.PrintError("Who is %s", node->kids_[0]->data_.value.id);
                generate_state = false;
                return;
            }

            vars.insert({
                std::string(node->kids_[2]->data_.value.id),
                {
                    std::string(node->kids_[2]->data_.value.id)
                ,   GetType(node->kids_[1])
                ,   vars.size() * 8
                }
            });

            wNode* def_val = node->kids_[node->kids_.Size() - 1];
            if (def_val->data_.type == wTokenType::wDefVal) {
                lst << "    " << "mov [bp + " << (vars.size() - 1) * 8 << "], " << def_val->kids_[0]->data_.value.value << "\n";
                //PrintLST("mov [bp + " << (vars.size() - 1) * 8 << "], " << def_val->kids_[0]->data_.value.value);
            }
        } break;

        case wTokenType::wWhile: {
            
        } break;

        case wTokenType::wIf: {
            
        } break;

        case wTokenType::wSometimes: {
            
        } break;
        
        default:
            wLogger.PrintDebug("Undefined token %s", node->data_.GetTypeName());
            break;
        }
    }
};

#endif // TOXAGE_GENERATOR_HPP