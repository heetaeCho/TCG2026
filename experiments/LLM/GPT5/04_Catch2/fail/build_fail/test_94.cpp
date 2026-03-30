// catch_tostring_symbol_test_94.cpp
#include <gtest/gtest.h>

// Include the provided header under test
#include "catch2/catch_tostring.hpp"

// Test suite name includes TEST_ID as requested.
class CatchToStringTest_94 : public ::testing::Test {};

// Normal operation: verify the documented observable behavior.
TEST_F(CatchToStringTest_94, SymbolReturnsLowercaseA_94) {
    // Expect the function to return 'a' exactly.
    EXPECT_EQ(Catch::symbol(), 'a');
}

// Idempotence / repeatability: multiple calls yield the same observable result.
TEST_F(CatchToStringTest_94, SymbolIsStableAcrossCalls_94) {
    const char first = Catch::symbol();
    const char second = Catch::symbol();
    const char third = Catch::symbol();

    EXPECT_EQ(first, 'a');
    EXPECT_EQ(second, 'a');
    EXPECT_EQ(third, 'a');
    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
}

// Type/encoding sanity: confirm it’s the ASCII 'a' (97), without inferring internals.
TEST_F(CatchToStringTest_94, SymbolAsciiCodeIs97_94) {
    const unsigned char code = static_cast<unsigned char>(Catch::symbol());
    EXPECT_EQ(code, static_cast<unsigned char>('a'));
    EXPECT_EQ(code, 97u);
}
