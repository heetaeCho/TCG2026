// File: catch_tostring_symbol_test_95.cpp

#include <gtest/gtest.h>
#include <string>
#include <type_traits>

#include "Catch2/src/catch2/catch_tostring.hpp"

// Compile-time verification of the return type (interface-level contract).
static_assert(std::is_same<decltype(Catch::symbol()), char>::value,
              "Catch::symbol() must return a char by value.");

class CatchToStringTest_95 : public ::testing::Test {};

// [Normal operation] Should return the fixed symbol character.
TEST_F(CatchToStringTest_95, SymbolReturnsFixedCharF_95) {
    EXPECT_EQ('f', Catch::symbol());
}

// [Idempotence / stability] Multiple calls must yield the same observable result.
TEST_F(CatchToStringTest_95, SymbolIsStableAcrossRepeatedCalls_95) {
    char first = Catch::symbol();
    char second = Catch::symbol();
    EXPECT_EQ(first, second);
    EXPECT_EQ('f', first);
}

// [External interaction] Returned value should integrate cleanly with standard APIs.
TEST_F(CatchToStringTest_95, SymbolIntegratesWithStdString_95) {
    std::string s;
    s.push_back(Catch::symbol());
    EXPECT_EQ("f", s);
}
