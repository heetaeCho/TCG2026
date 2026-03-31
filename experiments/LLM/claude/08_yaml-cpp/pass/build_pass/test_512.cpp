#include <gtest/gtest.h>
#include <sstream>
#include "indentation.h"
#include "yaml-cpp/ostream_wrapper.h"

namespace YAML {

// Helper: operator<< for char to ostream_wrapper (assumed to exist or we use write)
// We need a way to check col() after operations. Let's use the public interface.

class IndentToTest_512 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that IndentTo with n=0 does not add any spaces when col is already 0
TEST_F(IndentToTest_512, IndentToZeroFromColZero_512) {
    ostream_wrapper out;
    IndentTo indent(0);
    out << indent;
    EXPECT_EQ(out.col(), 0u);
    // No characters should have been written
    EXPECT_EQ(out.pos(), 0u);
}

// Test that IndentTo adds spaces to reach the desired column from col 0
TEST_F(IndentToTest_512, IndentToNFromColZero_512) {
    ostream_wrapper out;
    IndentTo indent(4);
    out << indent;
    EXPECT_EQ(out.col(), 4u);
    // 4 spaces should have been written
    std::string result(out.str(), out.pos());
    EXPECT_EQ(result, "    ");
}

// Test that IndentTo does nothing when col is already at the indent level
TEST_F(IndentToTest_512, IndentToNWhenAlreadyAtN_512) {
    ostream_wrapper out;
    // Write 3 characters to advance col to 3
    out.write("abc", 3);
    EXPECT_EQ(out.col(), 3u);
    
    IndentTo indent(3);
    out << indent;
    EXPECT_EQ(out.col(), 3u);
    // No additional spaces
    std::string result(out.str(), out.pos());
    EXPECT_EQ(result, "abc");
}

// Test that IndentTo does nothing when col is already past the indent level
TEST_F(IndentToTest_512, IndentToNWhenPastN_512) {
    ostream_wrapper out;
    // Write 5 characters to advance col to 5
    out.write("abcde", 5);
    EXPECT_EQ(out.col(), 5u);
    
    IndentTo indent(3);
    out << indent;
    // col should remain 5, no spaces added
    EXPECT_EQ(out.col(), 5u);
    std::string result(out.str(), out.pos());
    EXPECT_EQ(result, "abcde");
}

// Test IndentTo with n=1 from col 0
TEST_F(IndentToTest_512, IndentToOneFromColZero_512) {
    ostream_wrapper out;
    IndentTo indent(1);
    out << indent;
    EXPECT_EQ(out.col(), 1u);
    std::string result(out.str(), out.pos());
    EXPECT_EQ(result, " ");
}

// Test that operator<< returns the ostream_wrapper reference (chaining)
TEST_F(IndentToTest_512, OperatorReturnsSameStream_512) {
    ostream_wrapper out;
    IndentTo indent(2);
    ostream_wrapper& ref = (out << indent);
    EXPECT_EQ(&ref, &out);
}

// Test IndentTo with a larger value
TEST_F(IndentToTest_512, IndentToLargeValue_512) {
    ostream_wrapper out;
    IndentTo indent(10);
    out << indent;
    EXPECT_EQ(out.col(), 10u);
    std::string result(out.str(), out.pos());
    EXPECT_EQ(result, "          ");  // 10 spaces
}

// Test IndentTo after writing some content (partial indent)
TEST_F(IndentToTest_512, IndentToPartialFromExistingCol_512) {
    ostream_wrapper out;
    out.write("ab", 2);  // col = 2
    EXPECT_EQ(out.col(), 2u);
    
    IndentTo indent(5);
    out << indent;
    EXPECT_EQ(out.col(), 5u);
    std::string result(out.str(), out.pos());
    EXPECT_EQ(result, "ab   ");  // 3 spaces added
}

// Test IndentTo after a newline resets col
TEST_F(IndentToTest_512, IndentToAfterNewline_512) {
    ostream_wrapper out;
    out.write("abc\n", 4);  // col should be 0 after newline
    EXPECT_EQ(out.col(), 0u);
    
    IndentTo indent(3);
    out << indent;
    EXPECT_EQ(out.col(), 3u);
}

// Test IndentTo with stream-based ostream_wrapper
TEST_F(IndentToTest_512, IndentToWithStreamWrapper_512) {
    std::stringstream ss;
    ostream_wrapper out(ss);
    IndentTo indent(4);
    out << indent;
    EXPECT_EQ(out.col(), 4u);
    EXPECT_EQ(ss.str(), "    ");
}

// Test multiple consecutive IndentTo operations
TEST_F(IndentToTest_512, MultipleIndentToOperations_512) {
    ostream_wrapper out;
    IndentTo indent2(2);
    IndentTo indent5(5);
    
    out << indent2;
    EXPECT_EQ(out.col(), 2u);
    
    out << indent5;
    EXPECT_EQ(out.col(), 5u);
    
    std::string result(out.str(), out.pos());
    EXPECT_EQ(result, "     ");  // 2 spaces + 3 spaces = 5 spaces total
}

// Test IndentTo struct construction
TEST_F(IndentToTest_512, IndentToConstruction_512) {
    IndentTo indent(7);
    EXPECT_EQ(indent.n, 7u);
}

// Test IndentTo with n=0 when col is already > 0
TEST_F(IndentToTest_512, IndentToZeroWhenColPositive_512) {
    ostream_wrapper out;
    out.write("x", 1);
    EXPECT_EQ(out.col(), 1u);
    
    IndentTo indent(0);
    out << indent;
    // Should not add any spaces, col stays at 1
    EXPECT_EQ(out.col(), 1u);
}

}  // namespace YAML
