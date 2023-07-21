#pragma once

#define EXPANDER(...)  EXPANDER1(EXPANDER1(EXPANDER1(EXPANDER1(__VA_ARGS__))))
#define EXPANDER1(...) EXPANDER2(EXPANDER2(EXPANDER2(EXPANDER2(__VA_ARGS__))))
#define EXPANDER2(...) EXPANDER3(EXPANDER3(EXPANDER3(EXPANDER4(__VA_ARGS__))))
#define EXPANDER3(...) EXPANDER4(EXPANDER4(EXPANDER4(EXPANDER4(__VA_ARGS__))))
#define EXPANDER4(...) __VA_ARGS__

#define PARENS ()
#define GO_AGAIN() HELPER
#define HELPER(macro, a1, ...)                  \
macro(a1)                                       \
__VA_OPT__(GO_AGAIN PARENS (macro, __VA_ARGS__)

#define FOR_EACH(macro, ...) __VA_OPT__(EXPAND(HELPER(macro, __VA_ARGS__)))


#define CASE_NAME(name) case name: return #name;

#define CREATE_ENUM(name,...)enum name {__VA_ARGS__}; \
constexpr const char* toString(name _t) { \
using enum name;                          \
switch (_t) {                             \
    FOR_EACH(CASE_NAME, __VA_ARGS__)      \
default:                                  \
    throw std::logic_error("Non-Existant Enum Type");\
  }                                       \
}                                         \





