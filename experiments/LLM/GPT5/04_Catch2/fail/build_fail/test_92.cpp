// File: convert_array_to_string_tests_92.cpp

#include <gtest/gtest.h>
#include <string>

// Include the header under test
// Adjust the include path if your project structure differs.
#include "catch2/catch_tostring.hpp"

// We will define a lightweight type inside namespace Catch and
// provide a custom rangeToString overload for arrays of this type.
// This lets us observe that Catch::convert calls rangeToString with
// the correct array (and size), without re-implementing any internal logic.

namespace Catch {

// A simple tag type to route ADL and provide a predictable rangeToString.
struct TestTag_92 { int dummy{0}; };

// Overload for arrays of TestTag_92. The size is part of the observable behavior
// we can assert on, while keeping convert() a black box.
template <std::size_t N>
std::string rangeToString(TestTag_92 const (&)[N]) {
    return "TestTag_92_Array[N=" + std::to_string(N) + "]";
}

} // namespace Catch

// -----------------------------
// Test suite
// -----------------------------

// Normal operation: array of 3 elements should cause convert to delegate to our
// array overload of rangeToString and thus return the expected string.
TEST(ConvertArrayToString_92, DelegatesToRangeToString_Size3_92) {
    Catch::TestTag_92 arr[3]{};
    const std::string out = Catch::convert(arr);
    EXPECT_EQ(out, "TestTag_92_Array[N=3]");
}

// Boundary condition: smallest valid C-style array (size 1).
TEST(ConvertArrayToString_92, DelegatesToRangeToString_Size1_92) {
    Catch::TestTag_92 arr[1]{};
    const std::string out = Catch::convert(arr);
    EXPECT_EQ(out, "TestTag_92_Array[N=1]");
}

// Another normal case with a larger size to ensure size forwarding is consistent.
TEST(ConvertArrayToString_92, DelegatesToRangeToString_Size5_92) {
    Catch::TestTag_92 arr[5]{};
    const std::string out = Catch::convert(arr);
    EXPECT_EQ(out, "TestTag_92_Array[N=5]");
}

// Const-correctness: array is const-qualified; signature is T const (&)[SZ].
// Ensure convert still delegates properly.
TEST(ConvertArrayToString_92, DelegatesToRangeToString_ConstArray_92) {
    const Catch::TestTag_92 arr[2]{};
    const std::string out = Catch::convert(arr);
    EXPECT_EQ(out, "TestTag_92_Array[N=2]");
}
