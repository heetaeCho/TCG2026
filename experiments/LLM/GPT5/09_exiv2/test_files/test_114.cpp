#include <gtest/gtest.h>
#include <string>
#include <stdexcept>

namespace Exiv2 {
namespace Internal {

// The provided function definition
std::string indent(size_t i) {
    return std::string(2 * i, ' ');
}

} // namespace Internal
} // namespace Exiv2

// Test Suite for Exiv2::Internal::indent function
class IndentTest_114 : public ::testing::Test {};

// Test for normal operation
TEST_F(IndentTest_114, NormalOperation_114) {
    EXPECT_EQ(Exiv2::Internal::indent(0), "");
    EXPECT_EQ(Exiv2::Internal::indent(1), "  ");
    EXPECT_EQ(Exiv2::Internal::indent(3), "      ");
    EXPECT_EQ(Exiv2::Internal::indent(5), "          ");
}

// Test for boundary conditions
TEST_F(IndentTest_114, BoundaryConditions_114) {
    // Test for large number input
    EXPECT_EQ(Exiv2::Internal::indent(100), std::string(200, ' '));

    // Test for zero input
    EXPECT_EQ(Exiv2::Internal::indent(0), "");
}

// Test for exceptional or error cases
TEST_F(IndentTest_114, ExceptionalCases_114) {
    // The function does not throw exceptions for non-negative integers
    // Test that calling with a negative number should not compile or result in undefined behavior
    // This would require the function to handle size_t (which is unsigned) to not allow negative values
    // Thus, no test case is needed here for negative values as it's not valid.
}