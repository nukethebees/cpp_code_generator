// b should be counter
// ## disables expansion so we need to pass __LINE__ through a layer
// of macro invocations that doesn't contain a ## before it expands to the integer
#define _CCG_PREFIX_VARIABLE_NAME_3(a, b, c) a##b##_##c
#define CCG_PREFIX_VARIABLE_NAME_3(a, b, c) _CCG_PREFIX_VARIABLE_NAME_3(a, b, c)
#define CCG_DEFINE_MAYBE_NAME(a) CCG_PREFIX_VARIABLE_NAME_3(maybe_, __LINE__, a)

// Assign or propagate error
#define TRY_ASSIGN(MAC_VAR_NAME, MAC_EXPR_TO_TEST)                   \
    auto MAC_VAR_NAME{MAC_EXPR_TO_TEST};                             \
    do {                                                             \
        if (!MAC_VAR_NAME) {                                         \
            return std::unexpected(std::move(MAC_VAR_NAME.error())); \
        }                                                            \
    } while (0)

// Only checking for errors
#define TRY(MAC_EXPR_TO_TEST)                                        \
    do {                                                             \
        auto MAC_ERR_NAME{MAC_EXPR_TO_TEST};                         \
        if (!MAC_ERR_NAME) {                                         \
            return std::unexpected(std::move(MAC_ERR_NAME.error())); \
        }                                                            \
    } while (0)

#define TRY_UNWRAP(MAC_VAR_NAME, MAC_TEST_EXPR)                                         \
    auto CCG_DEFINE_MAYBE_NAME(MAC_VAR_NAME){MAC_TEST_EXPR};                            \
    if (!CCG_DEFINE_MAYBE_NAME(MAC_VAR_NAME)) {                                         \
        return std::unexpected(std::move(CCG_DEFINE_MAYBE_NAME(MAC_VAR_NAME).error())); \
    }                                                                                   \
    auto& MAC_VAR_NAME {                                                                \
        *CCG_DEFINE_MAYBE_NAME(MAC_VAR_NAME)                                            \
    }

#define TRY_MOVE(MAC_VAR_NAME, MAC_TEST_EXPR)                                           \
    auto CCG_DEFINE_MAYBE_NAME(MAC_VAR_NAME){MAC_TEST_EXPR};                            \
    if (!CCG_DEFINE_MAYBE_NAME(MAC_VAR_NAME)) {                                         \
        return std::unexpected(std::move(CCG_DEFINE_MAYBE_NAME(MAC_VAR_NAME).error())); \
    }                                                                                   \
    auto MAC_VAR_NAME {                                                                 \
        std::move(*CCG_DEFINE_MAYBE_NAME(MAC_VAR_NAME))                                 \
    }
