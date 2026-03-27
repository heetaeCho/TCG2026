// SymbolTests_98.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <cctype>

// Include the provided header with the implementation under test
#include "Catch2/src/catch2/catch_tostring.hpp"

// For convenience in tests
using Catch::symbol;

// Test suite name carries TEST_ID as requested.
class SymbolTest_98 : public ::testing::Test {};

// [Normal operation] The function should return the documented/observable character.
TEST_F(SymbolTest_98, ReturnsLowercaseU_98) {
    EXPECT_EQ('u', symbol());
}

// [Normal operation] Repeated calls should consistently return the same value.
TEST_F(SymbolTest_98, MultipleCallsConsistent_98) {
    const char first = symbol();
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(first, symbol());
    }
}

// [Type property] Return type should be char (based on the function signature).
TEST_F(SymbolTest_98, ReturnTypeIsChar_98) {
    // Checked at compile time via decltype; asserted in test for visibility.
    EXPECT_TRUE((std::is_same<decltype(symbol()), char>::value));
}

// [Boundary-ish/robustness] The returned character should be printable ASCII.
TEST_F(SymbolTest_98, IsPrintableAscii_98) {
    unsigned char c = static_cast<unsigned char>(symbol());
    EXPECT_TRUE(std::isprint(c));
}

// [Additional observable check] The numeric value matches the ASCII code for 'u'.
TEST_F(SymbolTest_98, MatchesAsciiCodeForU_98) {
    EXPECT_EQ(117, static_cast<unsigned char>(symbol())); // 'u' == 117
}
