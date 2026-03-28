// TokenStream_operator_arrow_tests_359.cpp
#include <gtest/gtest.h>

#include <catch2/internal/catch_clara.hpp>  // Uses the real interface

using Catch::Clara::Detail::TokenStream;
using Catch::Clara::Detail::Args;
using Catch::Clara::Detail::TokenType;

// A small helper to assert current token (through operator->) without
// inferring any internal logic beyond the public Token fields.
static void ExpectTokenIs(const TokenStream& ts,
                          TokenType expectedType,
                          const std::string& expectedLexeme) {
    auto ptr = ts.operator->(); // explicit use to test operator->
    ASSERT_NE(ptr, nullptr);
    EXPECT_EQ(ptr->type, expectedType);
    EXPECT_EQ(ptr->token, expectedLexeme);
}

// Normal operation: option with inline argument (“--opt=value”)
// Verifies that operator-> returns a non-null pointer to the current token
// and that it reflects the same data as operator*.
TEST(TokenStreamOperatorArrow_359, OptionThenArgument_FromCombinedForm_359) {
    Args args{ "app", "--opt=value" };
    TokenStream ts(args);

    // First token should be the option part
    ASSERT_TRUE(static_cast<bool>(ts));
    auto p1 = ts.operator->();
    ASSERT_NE(p1, nullptr);
    auto byValue1 = *ts; // operator*
    EXPECT_EQ(p1->type, byValue1.type);
    EXPECT_EQ(p1->token, byValue1.token);
    ExpectTokenIs(ts, TokenType::Option, "--opt");

    // Advance: second token should be the associated argument ("value")
    ++ts;
    ASSERT_TRUE(static_cast<bool>(ts));
    auto p2 = ts.operator->();
    ASSERT_NE(p2, nullptr);
    auto byValue2 = *ts; // operator*
    EXPECT_EQ(p2->type, byValue2.type);
    EXPECT_EQ(p2->token, byValue2.token);
    ExpectTokenIs(ts, TokenType::Argument, "value");

    // Calling operator-> repeatedly without advancing should be stable
    auto p2_again = ts.operator->();
    EXPECT_EQ(p2, p2_again);
}

// Normal operation: clustered short options (“-abc”)
// Verifies pointer targets each split option in sequence through increments.
TEST(TokenStreamOperatorArrow_359, ClusteredShortOptions_StepThrough_359) {
    Args args{ "app", "-abc" };
    TokenStream ts(args);

    ASSERT_TRUE(static_cast<bool>(ts));
    ExpectTokenIs(ts, TokenType::Option, "-a");
    ++ts;
    ASSERT_TRUE(static_cast<bool>(ts));
    ExpectTokenIs(ts, TokenType::Option, "-b");
    ++ts;
    ASSERT_TRUE(static_cast<bool>(ts));
    ExpectTokenIs(ts, TokenType::Option, "-c");
}

// Normal operation: bare argument (no leading '-' or '/')
// Ensures operator-> points to an Argument token.
TEST(TokenStreamOperatorArrow_359, BareArgument_FirstTokenIsArgument_359) {
    Args args{ "app", "file.txt" };
    TokenStream ts(args);

    ASSERT_TRUE(static_cast<bool>(ts));
    ExpectTokenIs(ts, TokenType::Argument, "file.txt");
}

// Boundary / exceptional case: empty token stream
// operator-> is specified with an assertion on non-empty buffer.
// We validate that invoking it on an empty stream triggers a death (if supported).
TEST(TokenStreamOperatorArrow_359, EmptyStream_OperatorArrowAsserts_359) {
    Args args{ "app" }; // no arguments => empty token stream
    TokenStream ts(args);

    EXPECT_FALSE(static_cast<bool>(ts));

#if GTEST_HAS_DEATH_TEST
    // The implementation uses assert(!m_tokenBuffer.empty()) in operator->.
    EXPECT_DEATH_IF_SUPPORTED(
        {
            // Cast to void to avoid unused warnings; we expect a crash/assert.
            (void)ts.operator->();
        },
        ""); // message regex left empty to be implementation-agnostic
#else
    GTEST_SKIP() << "Death tests not supported on this platform/build.";
#endif
}

// Sanity: operator-> and operator* stay in sync for the same position.
// Confirms observable consistency without relying on internals.
TEST(TokenStreamOperatorArrow_359, PointerAndValueConsistency_359) {
    Args args{ "app", "--flag" };
    TokenStream ts(args);

    ASSERT_TRUE(static_cast<bool>(ts));
    auto p = ts.operator->();
    ASSERT_NE(p, nullptr);
    auto v = *ts;
    EXPECT_EQ(p->type, v.type);
    EXPECT_EQ(p->token, v.token);
}
