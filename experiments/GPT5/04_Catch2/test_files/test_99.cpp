// tests/catch_symbol_test_99.cpp
#include <gtest/gtest.h>
#include <type_traits>

// Include the provided header (adjust the include path if your build differs)
#include "catch2/catch_tostring.hpp"

// Test suite name includes TEST_ID as requested.
class CatchSymbolTest_99 : public ::testing::Test {};

// [Normal operation] It returns the documented/observable symbol.
TEST_F(CatchSymbolTest_99, ReturnsExpectedSymbol_99) {
    EXPECT_EQ('m', Catch::symbol());
}

// [Type contract] The function returns a char (interface-level guarantee).
TEST_F(CatchSymbolTest_99, ReturnTypeIsChar_99) {
    // Using decltype on the call expression to verify the return type.
    bool is_char = std::is_same<decltype(Catch::symbol()), char>::value;
    EXPECT_TRUE(is_char);
}

// [Exception safety at interface] Calling the function should not throw.
TEST_F(CatchSymbolTest_99, NoThrowOnCall_99) {
    EXPECT_NO_THROW({
        volatile char c = Catch::symbol(); // volatile to prevent over-optimization
        (void)c;
    });
}

// [Name resolution / interface isolation] Using `using namespace Catch;` still
// refers to the free function and is not ambiguous with any template members.
TEST_F(CatchSymbolTest_99, UnqualifiedLookupResolvesFunction_99) {
    using namespace Catch;
    // If there were any ambiguity with other `symbol` declarations (e.g., in templates),
    // this call would fail to compile; reaching here validates resolution at the interface level.
    EXPECT_EQ('m', symbol());
}
