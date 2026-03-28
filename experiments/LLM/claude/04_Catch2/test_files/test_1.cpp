#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include "catch2/internal/catch_reusable_string_stream.hpp"

// Test fixture for ReusableStringStream
class ReusableStringStreamTest_1 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Default construction results in an empty string
TEST_F(ReusableStringStreamTest_1, DefaultConstructionYieldsEmptyString_1) {
    Catch::ReusableStringStream rss;
    EXPECT_EQ(rss.str(), "");
}

// Test: Streaming a simple string and retrieving it
TEST_F(ReusableStringStreamTest_1, StreamStringAndRetrieve_1) {
    Catch::ReusableStringStream rss;
    rss << "hello";
    EXPECT_EQ(rss.str(), "hello");
}

// Test: Streaming an integer value
TEST_F(ReusableStringStreamTest_1, StreamInteger_1) {
    Catch::ReusableStringStream rss;
    rss << 42;
    EXPECT_EQ(rss.str(), "42");
}

// Test: Streaming a floating point value
TEST_F(ReusableStringStreamTest_1, StreamDouble_1) {
    Catch::ReusableStringStream rss;
    rss << 3.14;
    std::string result = rss.str();
    EXPECT_FALSE(result.empty());
    // Verify it contains "3.14" (exact format may vary)
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

// Test: Chaining multiple stream operations
TEST_F(ReusableStringStreamTest_1, ChainingStreamOperations_1) {
    Catch::ReusableStringStream rss;
    rss << "value=" << 10 << " flag=" << true;
    std::string result = rss.str();
    EXPECT_NE(result.find("value="), std::string::npos);
    EXPECT_NE(result.find("10"), std::string::npos);
}

// Test: Streaming a character
TEST_F(ReusableStringStreamTest_1, StreamCharacter_1) {
    Catch::ReusableStringStream rss;
    rss << 'A';
    EXPECT_EQ(rss.str(), "A");
}

// Test: Streaming an empty string
TEST_F(ReusableStringStreamTest_1, StreamEmptyString_1) {
    Catch::ReusableStringStream rss;
    rss << "";
    EXPECT_EQ(rss.str(), "");
}

// Test: Setting string via str(const std::string&) resets content
TEST_F(ReusableStringStreamTest_1, SetStringResetsContent_1) {
    Catch::ReusableStringStream rss;
    rss << "initial content";
    EXPECT_EQ(rss.str(), "initial content");
    rss.str("");
    EXPECT_EQ(rss.str(), "");
}

// Test: Setting string and then streaming appends to the set string
TEST_F(ReusableStringStreamTest_1, SetStringThenStream_1) {
    Catch::ReusableStringStream rss;
    rss.str("");
    rss << "new content";
    EXPECT_EQ(rss.str(), "new content");
}

// Test: Streaming a negative integer
TEST_F(ReusableStringStreamTest_1, StreamNegativeInteger_1) {
    Catch::ReusableStringStream rss;
    rss << -99;
    EXPECT_EQ(rss.str(), "-99");
}

// Test: Streaming a boolean true
TEST_F(ReusableStringStreamTest_1, StreamBoolTrue_1) {
    Catch::ReusableStringStream rss;
    rss << true;
    std::string result = rss.str();
    // Depending on stream settings, could be "1" or "true"
    EXPECT_FALSE(result.empty());
}

// Test: Streaming a boolean false
TEST_F(ReusableStringStreamTest_1, StreamBoolFalse_1) {
    Catch::ReusableStringStream rss;
    rss << false;
    std::string result = rss.str();
    EXPECT_FALSE(result.empty());
}

// Test: get() returns a valid ostream reference
TEST_F(ReusableStringStreamTest_1, GetReturnsValidOstream_1) {
    Catch::ReusableStringStream rss;
    std::ostream& os = rss.get();
    os << "via get";
    EXPECT_EQ(rss.str(), "via get");
}

// Test: Multiple instances are independent
TEST_F(ReusableStringStreamTest_1, MultipleInstancesAreIndependent_1) {
    Catch::ReusableStringStream rss1;
    Catch::ReusableStringStream rss2;
    rss1 << "first";
    rss2 << "second";
    EXPECT_EQ(rss1.str(), "first");
    EXPECT_EQ(rss2.str(), "second");
}

// Test: Streaming a long string
TEST_F(ReusableStringStreamTest_1, StreamLongString_1) {
    Catch::ReusableStringStream rss;
    std::string longStr(10000, 'x');
    rss << longStr;
    EXPECT_EQ(rss.str(), longStr);
}

// Test: Streaming a const char*
TEST_F(ReusableStringStreamTest_1, StreamConstCharPtr_1) {
    Catch::ReusableStringStream rss;
    const char* msg = "test message";
    rss << msg;
    EXPECT_EQ(rss.str(), "test message");
}

// Test: Streaming a std::string object
TEST_F(ReusableStringStreamTest_1, StreamStdString_1) {
    Catch::ReusableStringStream rss;
    std::string s = "std string";
    rss << s;
    EXPECT_EQ(rss.str(), "std string");
}

// Test: Streaming unsigned integer
TEST_F(ReusableStringStreamTest_1, StreamUnsignedInt_1) {
    Catch::ReusableStringStream rss;
    unsigned int val = 4294967295u;
    rss << val;
    EXPECT_EQ(rss.str(), "4294967295");
}

// Test: str() setter with non-empty string
TEST_F(ReusableStringStreamTest_1, SetStringWithNonEmpty_1) {
    Catch::ReusableStringStream rss;
    rss.str("preset");
    // After setting, str() should reflect the set value or stream from it
    // The exact behavior depends on implementation, but we test observable outcome
    std::string result = rss.str();
    // It should either be "preset" or empty depending on implementation
    // Most std::ostringstream implementations: str("preset") sets the buffer
    EXPECT_EQ(result, "preset");
}

// Test: Reset and reuse
TEST_F(ReusableStringStreamTest_1, ResetAndReuse_1) {
    Catch::ReusableStringStream rss;
    rss << "first";
    EXPECT_EQ(rss.str(), "first");
    rss.str("");
    rss << "second";
    EXPECT_EQ(rss.str(), "second");
}

// Test: Streaming zero
TEST_F(ReusableStringStreamTest_1, StreamZero_1) {
    Catch::ReusableStringStream rss;
    rss << 0;
    EXPECT_EQ(rss.str(), "0");
}

// Test: Operator<< returns reference to self for chaining
TEST_F(ReusableStringStreamTest_1, OperatorReturnsReference_1) {
    Catch::ReusableStringStream rss;
    Catch::ReusableStringStream& ref = (rss << "test");
    EXPECT_EQ(&ref, &rss);
}
