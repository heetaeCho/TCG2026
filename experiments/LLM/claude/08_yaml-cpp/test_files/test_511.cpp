#include "gtest/gtest.h"
#include "yaml-cpp/ostream_wrapper.h"
#include "indentation.h"
#include <sstream>
#include <string>

namespace YAML {

class IndentationTest_511 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that zero indentation produces no spaces
TEST_F(IndentationTest_511, ZeroIndentation_511) {
    ostream_wrapper out;
    Indentation indent(0);
    out << indent;
    // With zero indentation, nothing should be written
    EXPECT_EQ(out.pos(), 0u);
    std::string result(out.str(), out.pos());
    EXPECT_EQ(result, "");
}

// Test that indentation of 1 produces a single space
TEST_F(IndentationTest_511, SingleSpaceIndentation_511) {
    ostream_wrapper out;
    Indentation indent(1);
    out << indent;
    EXPECT_EQ(out.pos(), 1u);
    std::string result(out.str(), out.pos());
    EXPECT_EQ(result, " ");
}

// Test that indentation of 2 produces two spaces
TEST_F(IndentationTest_511, TwoSpaceIndentation_511) {
    ostream_wrapper out;
    Indentation indent(2);
    out << indent;
    EXPECT_EQ(out.pos(), 2u);
    std::string result(out.str(), out.pos());
    EXPECT_EQ(result, "  ");
}

// Test that indentation of 4 produces four spaces
TEST_F(IndentationTest_511, FourSpaceIndentation_511) {
    ostream_wrapper out;
    Indentation indent(4);
    out << indent;
    EXPECT_EQ(out.pos(), 4u);
    std::string result(out.str(), out.pos());
    EXPECT_EQ(result, "    ");
}

// Test larger indentation
TEST_F(IndentationTest_511, LargeIndentation_511) {
    ostream_wrapper out;
    Indentation indent(10);
    out << indent;
    EXPECT_EQ(out.pos(), 10u);
    std::string result(out.str(), out.pos());
    EXPECT_EQ(result, std::string(10, ' '));
}

// Test that operator<< returns the ostream_wrapper reference (chaining)
TEST_F(IndentationTest_511, ReturnsSameStream_511) {
    ostream_wrapper out;
    Indentation indent(3);
    ostream_wrapper& ref = (out << indent);
    EXPECT_EQ(&ref, &out);
}

// Test multiple indentations applied sequentially
TEST_F(IndentationTest_511, MultipleIndentationsSequential_511) {
    ostream_wrapper out;
    Indentation indent1(2);
    Indentation indent2(3);
    out << indent1 << indent2;
    EXPECT_EQ(out.pos(), 5u);
    std::string result(out.str(), out.pos());
    EXPECT_EQ(result, "     ");
}

// Test indentation with ostream_wrapper wrapping an actual std::ostream
TEST_F(IndentationTest_511, IndentationWithOstream_511) {
    std::stringstream ss;
    ostream_wrapper out(ss);
    Indentation indent(3);
    out << indent;
    EXPECT_EQ(ss.str(), "   ");
}

// Test that indentation only writes space characters
TEST_F(IndentationTest_511, OnlySpaceCharacters_511) {
    ostream_wrapper out;
    Indentation indent(5);
    out << indent;
    std::string result(out.str(), out.pos());
    for (char c : result) {
        EXPECT_EQ(c, ' ');
    }
}

// Test that column position is updated correctly after indentation
TEST_F(IndentationTest_511, ColumnPositionUpdated_511) {
    ostream_wrapper out;
    Indentation indent(4);
    out << indent;
    EXPECT_EQ(out.col(), 4u);
}

// Test that row remains zero after indentation (spaces don't create newlines)
TEST_F(IndentationTest_511, RowRemainsZero_511) {
    ostream_wrapper out;
    Indentation indent(5);
    out << indent;
    EXPECT_EQ(out.row(), 0u);
}

// Test Indentation struct initialization
TEST_F(IndentationTest_511, IndentationStructInit_511) {
    Indentation indent(7);
    EXPECT_EQ(indent.n, 7u);
}

// Test Indentation struct with zero
TEST_F(IndentationTest_511, IndentationStructZero_511) {
    Indentation indent(0);
    EXPECT_EQ(indent.n, 0u);
}

// Test with a moderately large indentation value
TEST_F(IndentationTest_511, ModeratelyLargeIndentation_511) {
    ostream_wrapper out;
    std::size_t size = 100;
    Indentation indent(size);
    out << indent;
    EXPECT_EQ(out.pos(), size);
    std::string result(out.str(), out.pos());
    EXPECT_EQ(result, std::string(size, ' '));
}

}  // namespace YAML
