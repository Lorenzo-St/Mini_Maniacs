#pragma once
#include <stdexcept>
#define PARENS ()
#define __PRETTY_FUNCTION__ __FUNCSIG__


#define FOR_EACH(macro, ...) __VA_OPT__(CHAIN1(macro, __VA_ARGS__))
#define END(a) a

#define CHAIN1(macro, var1, ...) macro(var1) __VA_OPT__(CHAIN2(macro, __VA_ARGS__)) 
#define CHAIN2(macro, var1, ...) macro(var1) __VA_OPT__(CHAIN3(macro, __VA_ARGS__)) 
#define CHAIN3(macro, var1, ...) macro(var1) __VA_OPT__(CHAIN4(macro, __VA_ARGS__)) 
#define CHAIN4(macro, var1, ...) macro(var1) __VA_OPT__(CHAIN5(macro, __VA_ARGS__)) 
#define CHAIN5(macro, var1, ...) macro(var1) __VA_OPT__(CHAIN6(macro, __VA_ARGS__)) 
#define CHAIN6(macro, var1, ...) macro(var1) __VA_OPT__(CHAIN7(macro, __VA_ARGS__)) 
#define CHAIN7(macro, var1, ...) macro(var1) __VA_OPT__(CHAIN8(macro, __VA_ARGS__)) 
#define CHAIN8(macro, var1, ...) macro(var1) __VA_OPT__(CHAIN9(macro, __VA_ARGS__)) 
#define CHAIN9(macro, var1, ...) macro(var1) __VA_OPT__(CHAIN10(macro, __VA_ARGS__)) 
#define CHAIN10(macro, var1, ...) macro(var1) __VA_OPT__(CHAIN11(macro, __VA_ARGS__)) 
#define CHAIN11(macro, var1, ...) macro(var1) __VA_OPT__(CHAIN12(macro, __VA_ARGS__)) 
#define CHAIN12(macro, var1, ...) macro(var1) __VA_OPT__(CHAIN13(macro, __VA_ARGS__)) 
#define CHAIN13(macro, var1, ...) macro(var1) __VA_OPT__(CHAIN14(macro, __VA_ARGS__)) 
#define CHAIN14(macro, var1, ...) macro(var1) __VA_OPT__(CHAIN15(macro, __VA_ARGS__)) 
#define CHAIN15(...) END("ERROR!!!")


#define CASE_NAME(name) case name: return #name;
#define IF_NAME(name) if(string == #name) return name;
#define IF_TYPE(name) if(typeid(t) == typeid(::##name)) return name;

#define CREATE_ENUM(name,...)              \
namespace name##Enum{                      \
enum name {reserved = 0,  __VA_ARGS__};    \
constexpr const char* toString(name _t) {  \
using enum name;                           \
switch (_t) {                              \
     case reserved:throw std::logic_error("Non-Existant Enum Type"); \
    FOR_EACH(CASE_NAME, __VA_ARGS__)       \
default:                                   \
    throw std::logic_error("Non-Existant Enum Type");\
  }                                        \
}                                          \
constexpr name toEnum(std::string& string){\
FOR_EACH(IF_NAME, __VA_ARGS__ )            \
throw std::logic_error("Non-Existant Enum Type");\
}                                          \
template<typename t>                       \
constexpr name typeToEnum(){               \
FOR_EACH(IF_TYPE, __VA_ARGS__)             \
throw std::logic_error("Non-Existant Enum Type");\
}                                          \
}



