// File: tests/catch_tostring_symbol_test_97.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <cctype>

// Include the header under test exactly as provided
#include "Catch2/src/catch2/catch_tostring.hpp"

// Compile-time verification of the interface (return type only).
static_assert(std::is_same<decltype(Catch::symbol()), char>::value,
              "Catch::symbol() must return char");

// ----- Test Suite -----

// [97] Normal operation: returns the expected, concrete character.
TEST(CatchToStringTest_97, ReturnsExpectedChar_97) {
    EXPECT_EQ('n', Catch::symbol());
}

// [97] Stability: repeated calls yield the same observable result.
TEST(CatchToStringTest_97, ConsistentAcrossMultipleCalls_97) {
    const char first = Catch::symbol();
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(first, Catch::symbol());
    }
}

// [97] Boundary-ish observable checks: not NUL and is printable ASCII.
// These do not assume internal logic; they only check the returned value's properties.
TEST(CatchToStringTest_97, NonNullAndPrintable_97) {
    const unsigned char uc = static_cast<unsigned char>(Catch::symbol());
    EXPECT_NE('\0', static_cast<char>(uc));
    EXPECT_NE(0, std::isprint(uc));  // nonzero => printable
}

// [97] Exception safety for a simple call path (observable: no throw).
TEST(CatchToStringTest_97, DoesNotThrow_97) {
    EXPECT_NO_THROW({
        volatile char c = Catch::symbol();
        (void)c;
    });
}
