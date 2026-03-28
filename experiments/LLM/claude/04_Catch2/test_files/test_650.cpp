#include <gtest/gtest.h>
#include <string>
#include <sstream>

#include "catch2/internal/catch_reusable_string_stream.hpp"

class ReusableStringStreamTest_650 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default construction and empty string
TEST_F(ReusableStringStreamTest_650, DefaultConstructionYieldsEmptyString_650) {
    Catch::ReusableStringStream rss;
    EXPECT_EQ(rss.str(), "");
}

// Test str setter and getter
TEST_F(ReusableStringStreamTest_650, SetAndGetString_650) {
    Catch::ReusableStringStream rss;
    rss.str("hello world");
    EXPECT_EQ(rss.str(), "hello world");
}

// Test setting empty string
TEST_F(ReusableStringStreamTest_650, SetEmptyString_650) {
    Catch::ReusableStringStream rss;
    rss.str("some content");
    EXPECT_EQ(rss.str(), "some content");
    rss.str("");
    EXPECT_EQ(rss.str(), "");
}

// Test streaming an integer
TEST_F(ReusableStringStreamTest_650, StreamInteger_650) {
    Catch::ReusableStringStream rss;
    rss << 42;
    EXPECT_EQ(rss.str(), "42");
}

// Test streaming a string
TEST_F(ReusableStringStreamTest_650, StreamString_650) {
    Catch::ReusableStringStream rss;
    rss << "test string";
    EXPECT_EQ(rss.str(), "test string");
}

// Test streaming multiple values
TEST_F(ReusableStringStreamTest_650, StreamMultipleValues_650) {
    Catch::ReusableStringStream rss;
    rss << "value: " << 100 << " end";
    EXPECT_EQ(rss.str(), "value: 100 end");
}

// Test streaming a floating point value
TEST_F(ReusableStringStreamTest_650, StreamFloatingPoint_650) {
    Catch::ReusableStringStream rss;
    rss << 3.14;
    std::string result = rss.str();
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

// Test get() returns a valid ostream reference
TEST_F(ReusableStringStreamTest_650, GetReturnsValidOstream_650) {
    Catch::ReusableStringStream rss;
    std::ostream& os = rss.get();
    os << "via get";
    EXPECT_EQ(rss.str(), "via get");
}

// Test overwriting content with str()
TEST_F(ReusableStringStreamTest_650, OverwriteContentWithStr_650) {
    Catch::ReusableStringStream rss;
    rss << "original";
    EXPECT_EQ(rss.str(), "original");
    rss.str("replaced");
    EXPECT_EQ(rss.str(), "replaced");
}

// Test chaining operator<<
TEST_F(ReusableStringStreamTest_650, ChainingOperator_650) {
    Catch::ReusableStringStream rss;
    auto& ref = (rss << "a");
    ref << "b";
    std::string result = rss.str();
    EXPECT_EQ(result, "ab");
}

// Test multiple ReusableStringStream instances are independent
TEST_F(ReusableStringStreamTest_650, MultipleInstancesAreIndependent_650) {
    Catch::ReusableStringStream rss1;
    Catch::ReusableStringStream rss2;
    rss1 << "first";
    rss2 << "second";
    EXPECT_EQ(rss1.str(), "first");
    EXPECT_EQ(rss2.str(), "second");
}

// Test streaming a character
TEST_F(ReusableStringStreamTest_650, StreamCharacter_650) {
    Catch::ReusableStringStream rss;
    rss << 'X';
    EXPECT_EQ(rss.str(), "X");
}

// Test streaming a boolean
TEST_F(ReusableStringStreamTest_650, StreamBoolean_650) {
    Catch::ReusableStringStream rss;
    rss << std::boolalpha << true;
    EXPECT_EQ(rss.str(), "true");
}

// Test streaming negative number
TEST_F(ReusableStringStreamTest_650, StreamNegativeNumber_650) {
    Catch::ReusableStringStream rss;
    rss << -999;
    EXPECT_EQ(rss.str(), "-999");
}

// Test setting a very long string
TEST_F(ReusableStringStreamTest_650, SetLongString_650) {
    Catch::ReusableStringStream rss;
    std::string longStr(10000, 'A');
    rss.str(longStr);
    EXPECT_EQ(rss.str(), longStr);
}

// Test str reset clears previous streamed content
TEST_F(ReusableStringStreamTest_650, StrResetClearsPreviousContent_650) {
    Catch::ReusableStringStream rss;
    rss << "some data" << 123;
    rss.str("");
    EXPECT_EQ(rss.str(), "");
}

// Test special characters in string
TEST_F(ReusableStringStreamTest_650, SpecialCharactersInString_650) {
    Catch::ReusableStringStream rss;
    std::string special = "tab\there\nnewline\0null";
    rss.str(special);
    EXPECT_EQ(rss.str(), special);
}

// Test operator<< returns reference to same object
TEST_F(ReusableStringStreamTest_650, OperatorReturnsReferenceToSelf_650) {
    Catch::ReusableStringStream rss;
    Catch::ReusableStringStream& ref = (rss << "test");
    EXPECT_EQ(&ref, &rss);
}
