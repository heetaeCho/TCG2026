#include "catch2/internal/catch_xmlwriter.hpp"
#include <gtest/gtest.h>
#include <cstdint>

using namespace Catch;

class XmlFormattingTest_16 : public ::testing::Test {
protected:
};

// Test that ANDing a value with itself returns the same value
TEST_F(XmlFormattingTest_16, AndWithSelfReturnsSelf_16) {
    XmlFormatting val = XmlFormatting::Newline;
    XmlFormatting result = val & val;
    EXPECT_EQ(static_cast<std::uint8_t>(result), static_cast<std::uint8_t>(val));
}

// Test that ANDing with None (zero) returns None
TEST_F(XmlFormattingTest_16, AndWithNoneReturnsNone_16) {
    XmlFormatting val = XmlFormatting::Newline;
    XmlFormatting result = val & XmlFormatting::None;
    EXPECT_EQ(static_cast<std::uint8_t>(result), static_cast<std::uint8_t>(XmlFormatting::None));
}

// Test that None AND None is None
TEST_F(XmlFormattingTest_16, NoneAndNoneIsNone_16) {
    XmlFormatting result = XmlFormatting::None & XmlFormatting::None;
    EXPECT_EQ(static_cast<std::uint8_t>(result), 0u);
}

// Test AND of Newline and Indent
TEST_F(XmlFormattingTest_16, NewlineAndIndentBitwiseAnd_16) {
    XmlFormatting result = XmlFormatting::Newline & XmlFormatting::Indent;
    // These are separate flags, so AND should yield 0 (None)
    EXPECT_EQ(static_cast<std::uint8_t>(result), 
              static_cast<std::uint8_t>(XmlFormatting::Newline) & static_cast<std::uint8_t>(XmlFormatting::Indent));
}

// Test that operator& is constexpr usable
TEST_F(XmlFormattingTest_16, ConstexprUsage_16) {
    constexpr XmlFormatting result = XmlFormatting::Newline & XmlFormatting::Newline;
    EXPECT_EQ(static_cast<std::uint8_t>(result), static_cast<std::uint8_t>(XmlFormatting::Newline));
}

// Test AND with combined flags (Newline | Indent) and Newline extracts Newline
TEST_F(XmlFormattingTest_16, AndExtractsFlag_16) {
    // XmlFormatting::Both should be Newline | Indent if it exists, otherwise construct manually
    XmlFormatting combined = static_cast<XmlFormatting>(
        static_cast<std::uint8_t>(XmlFormatting::Newline) | static_cast<std::uint8_t>(XmlFormatting::Indent));
    XmlFormatting result = combined & XmlFormatting::Newline;
    EXPECT_EQ(static_cast<std::uint8_t>(result), static_cast<std::uint8_t>(XmlFormatting::Newline));
}

// Test AND with combined flags and Indent extracts Indent
TEST_F(XmlFormattingTest_16, AndExtractsIndentFlag_16) {
    XmlFormatting combined = static_cast<XmlFormatting>(
        static_cast<std::uint8_t>(XmlFormatting::Newline) | static_cast<std::uint8_t>(XmlFormatting::Indent));
    XmlFormatting result = combined & XmlFormatting::Indent;
    EXPECT_EQ(static_cast<std::uint8_t>(result), static_cast<std::uint8_t>(XmlFormatting::Indent));
}

// Test commutativity: a & b == b & a
TEST_F(XmlFormattingTest_16, AndIsCommutative_16) {
    XmlFormatting a = XmlFormatting::Newline;
    XmlFormatting b = XmlFormatting::Indent;
    EXPECT_EQ(static_cast<std::uint8_t>(a & b), static_cast<std::uint8_t>(b & a));
}

// Test that AND of all bits set with None is None
TEST_F(XmlFormattingTest_16, AllBitsAndNoneIsNone_16) {
    XmlFormatting allBits = static_cast<XmlFormatting>(0xFF);
    XmlFormatting result = allBits & XmlFormatting::None;
    EXPECT_EQ(static_cast<std::uint8_t>(result), 0u);
}

// Test that AND of all bits set with a specific flag returns that flag
TEST_F(XmlFormattingTest_16, AllBitsAndSpecificFlagReturnsFlag_16) {
    XmlFormatting allBits = static_cast<XmlFormatting>(0xFF);
    XmlFormatting result = allBits & XmlFormatting::Newline;
    EXPECT_EQ(static_cast<std::uint8_t>(result), static_cast<std::uint8_t>(XmlFormatting::Newline));
}
