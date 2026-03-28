// ParserRefImpl_isOptional_tests_389.cpp
#include <gtest/gtest.h>

// Include the real class under test.
// Adjust include path if your project layout differs.
#include "catch2/internal/catch_clara.hpp"

using Catch::Clara::Detail::ParserRefImpl;

//
// NOTE:
// We treat ParserRefImpl as a black box and only validate observable behavior
// through its public interface (isOptional, required, optional). We do NOT
// access any private/protected state.
//

// 1) Default: object should be optional.
TEST(ParserRefImplTest_389, DefaultIsOptional_389) {
    ParserRefImpl parser;  // default construction via the real header
    EXPECT_TRUE(parser.isOptional());
}

// 2) Calling required() should make it non-optional (observable via isOptional()).
TEST(ParserRefImplTest_389, RequiredMakesNonOptional_389) {
    ParserRefImpl parser;
    parser.required();
    EXPECT_FALSE(parser.isOptional());
}

// 3) Calling optional() after required() should make it optional again.
TEST(ParserRefImplTest_389, OptionalThenRequiredThenOptional_Toggles_389) {
    ParserRefImpl parser;

    // Start: default optional
    EXPECT_TRUE(parser.isOptional());

    // After required(): not optional
    parser.required();
    EXPECT_FALSE(parser.isOptional());

    // After optional(): optional again
    parser.optional();
    EXPECT_TRUE(parser.isOptional());

    // Re-applying required() should flip back to non-optional
    parser.required();
    EXPECT_FALSE(parser.isOptional());
}

// 4) isOptional() should be callable on a const object (const-correctness).
TEST(ParserRefImplTest_389, IsOptionalConstCorrectness_389) {
    ParserRefImpl parser;
    parser.required();

    const ParserRefImpl& cref = parser;
    EXPECT_FALSE(cref.isOptional());

    // Flip back to optional and check again
    parser.optional();
    EXPECT_TRUE(cref.isOptional());
}
