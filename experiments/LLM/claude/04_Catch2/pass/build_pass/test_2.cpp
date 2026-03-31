#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "catch2/internal/catch_reusable_string_stream.hpp"

class ReusableStringStreamTest_2 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that default construction creates a valid stream
TEST_F(ReusableStringStreamTest_2, DefaultConstruction_2) {
    Catch::ReusableStringStream rss;
    // Should not throw, and str() should return empty string
    EXPECT_EQ(rss.str(), "");
}

// Test that get() returns a valid ostream reference
TEST_F(ReusableStringStreamTest_2, GetReturnsValidOstream_2) {
    Catch::ReusableStringStream rss;
    std::ostream& os = rss.get();
    EXPECT_TRUE(os.good());
}

// Test writing a simple string and reading it back
TEST_F(ReusableStringStreamTest_2, WriteStringAndReadBack_2) {
    Catch::ReusableStringStream rss;
    rss << "hello world";
    EXPECT_EQ(rss.str(), "hello world");
}

// Test writing an integer
TEST_F(ReusableStringStreamTest_2, WriteInteger_2) {
    Catch::ReusableStringStream rss;
    rss << 42;
    EXPECT_EQ(rss.str(), "42");
}

// Test writing a floating point number
TEST_F(ReusableStringStreamTest_2, WriteDouble_2) {
    Catch::ReusableStringStream rss;
    rss << 3.14;
    std::string result = rss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

// Test writing multiple values via chaining
TEST_F(ReusableStringStreamTest_2, ChainedWrites_2) {
    Catch::ReusableStringStream rss;
    rss << "value=" << 100 << " end";
    EXPECT_EQ(rss.str(), "value=100 end");
}

// Test str(const std::string&) sets the content
TEST_F(ReusableStringStreamTest_2, SetStrResetsContent_2) {
    Catch::ReusableStringStream rss;
    rss << "initial";
    EXPECT_EQ(rss.str(), "initial");
    rss.str("");
    EXPECT_EQ(rss.str(), "");
}

// Test str() sets to a specific string
TEST_F(ReusableStringStreamTest_2, SetStrToSpecificValue_2) {
    Catch::ReusableStringStream rss;
    rss.str("preset value");
    EXPECT_EQ(rss.str(), "preset value");
}

// Test writing via get() ostream reference
TEST_F(ReusableStringStreamTest_2, WriteViaGetOstream_2) {
    Catch::ReusableStringStream rss;
    std::ostream& os = rss.get();
    os << "via get";
    EXPECT_EQ(rss.str(), "via get");
}

// Test empty string after construction
TEST_F(ReusableStringStreamTest_2, EmptyAfterConstruction_2) {
    Catch::ReusableStringStream rss;
    std::string result = rss.str();
    EXPECT_TRUE(result.empty());
}

// Test clearing and rewriting
TEST_F(ReusableStringStreamTest_2, ClearAndRewrite_2) {
    Catch::ReusableStringStream rss;
    rss << "first";
    EXPECT_EQ(rss.str(), "first");
    rss.str("");
    rss << "second";
    EXPECT_EQ(rss.str(), "second");
}

// Test writing a boolean
TEST_F(ReusableStringStreamTest_2, WriteBoolean_2) {
    Catch::ReusableStringStream rss;
    rss << true;
    std::string result = rss.str();
    EXPECT_FALSE(result.empty());
}

// Test writing a char
TEST_F(ReusableStringStreamTest_2, WriteChar_2) {
    Catch::ReusableStringStream rss;
    rss << 'A';
    EXPECT_EQ(rss.str(), "A");
}

// Test writing negative number
TEST_F(ReusableStringStreamTest_2, WriteNegativeNumber_2) {
    Catch::ReusableStringStream rss;
    rss << -123;
    EXPECT_EQ(rss.str(), "-123");
}

// Test writing an empty string
TEST_F(ReusableStringStreamTest_2, WriteEmptyString_2) {
    Catch::ReusableStringStream rss;
    rss << "";
    EXPECT_EQ(rss.str(), "");
}

// Test writing a long string
TEST_F(ReusableStringStreamTest_2, WriteLongString_2) {
    Catch::ReusableStringStream rss;
    std::string longStr(10000, 'x');
    rss << longStr;
    EXPECT_EQ(rss.str(), longStr);
}

// Test multiple instances are independent
TEST_F(ReusableStringStreamTest_2, MultipleInstancesIndependent_2) {
    Catch::ReusableStringStream rss1;
    Catch::ReusableStringStream rss2;
    rss1 << "stream1";
    rss2 << "stream2";
    EXPECT_EQ(rss1.str(), "stream1");
    EXPECT_EQ(rss2.str(), "stream2");
}

// Test str setter with non-empty then read
TEST_F(ReusableStringStreamTest_2, SetStrThenAppend_2) {
    Catch::ReusableStringStream rss;
    rss.str("start");
    // After setting str, writing should append or replace depending on implementation
    // We just verify str() returns what was set
    EXPECT_EQ(rss.str(), "start");
}

// Test writing zero
TEST_F(ReusableStringStreamTest_2, WriteZero_2) {
    Catch::ReusableStringStream rss;
    rss << 0;
    EXPECT_EQ(rss.str(), "0");
}

// Test writing newline characters
TEST_F(ReusableStringStreamTest_2, WriteNewline_2) {
    Catch::ReusableStringStream rss;
    rss << "line1\nline2";
    EXPECT_EQ(rss.str(), "line1\nline2");
}

// Test destruction doesn't cause issues (scope-based)
TEST_F(ReusableStringStreamTest_2, DestructionIsSafe_2) {
    {
        Catch::ReusableStringStream rss;
        rss << "temporary";
        EXPECT_EQ(rss.str(), "temporary");
    }
    // If we get here without crash, destruction was safe
    SUCCEED();
}
