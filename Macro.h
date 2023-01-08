#pragma once

#define COMMA ,

// stringification macros
#define _S(s) #s
#define S(s) _S(s)

#define COPY_CONSTRUCTOR(TypeName, default_or_delete)           \
    TypeName(const TypeName &) = default_or_delete;             \
    TypeName &operator=(const TypeName &) = default_or_delete;

#define MOVE_CONSTRUCTOR(TypeName, default_or_delete)       \
    TypeName(TypeName &&) = default_or_delete;              \
    TypeName &operator=(TypeName &&) = default_or_delete;

#define COPY_MOVE_CONSTRUCTORS(TypeName, copy_default_or_delete, move_default_or_delete)    \
    TypeName(const TypeName &) = copy_default_or_delete;                                    \
    TypeName &operator=(const TypeName &) = copy_default_or_delete;                         \
    TypeName(TypeName &&) = move_default_or_delete;                                         \
    TypeName &operator=(TypeName &&) = move_default_or_delete;