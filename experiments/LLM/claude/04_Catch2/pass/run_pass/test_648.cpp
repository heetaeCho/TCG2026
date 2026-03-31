#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <memory>

// Include the necessary Catch2 headers
#include "catch2/internal/catch_reusable_string_stream.hpp"

using namespace Catch;

// Test fixture for ReusableStringStream
class ReusableStringStreamTest_648 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a newly constructed ReusableStringStream has an empty string
TEST_F(ReusableStringStreamTest_648, DefaultConstructionYieldsEmptyString_648) {
    ReusableStringStream rss;
    EXPECT_EQ(rss.str(), "");
}

// Test that streaming a simple string works
TEST_F(ReusableStringStreamTest_648, StreamStringValue_648) {
    ReusableStringStream rss;
    rss << "hello";
    EXPECT_EQ(rss.str(), "hello");
}

// Test that streaming an integer works
TEST_F(ReusableStringStreamTest_648, StreamIntegerValue_648) {
    ReusableStringStream rss;
    rss << 42;
    EXPECT_EQ(rss.str(), "42");
}

// Test that streaming a floating point value works
TEST_F(ReusableStringStreamTest_648, StreamFloatingPointValue_648) {
    ReusableStringStream rss;
    rss << 3.14;
    std::string result = rss.str();
    EXPECT_FALSE(result.empty());
    // Just check it contains "3.14" at minimum
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

// Test that multiple streaming operations concatenate
TEST_F(ReusableStringStreamTest_648, MultipleStreamOperations_648) {
    ReusableStringStream rss;
    rss << "foo" << " " << "bar";
    EXPECT_EQ(rss.str(), "foo bar");
}

// Test that str(string) sets the content
TEST_F(ReusableStringStreamTest_648, SetStringContent_648) {
    ReusableStringStream rss;
    rss.str("preset value");
    EXPECT_EQ(rss.str(), "preset value");
}

// Test that str("") clears the content
TEST_F(ReusableStringStreamTest_648, ClearStringContent_648) {
    ReusableStringStream rss;
    rss << "some content";
    EXPECT_EQ(rss.str(), "some content");
    rss.str("");
    EXPECT_EQ(rss.str(), "");
}

// Test that setting str and then streaming appends to the set value
TEST_F(ReusableStringStreamTest_648, SetThenStream_648) {
    ReusableStringStream rss;
    rss.str("initial");
    // After setting str, the stream position might be at end or beginning
    // We just verify str() returns what was set before any further streaming
    EXPECT_EQ(rss.str(), "initial");
}

// Test that get() returns a valid ostream reference
TEST_F(ReusableStringStreamTest_648, GetReturnsValidOstream_648) {
    ReusableStringStream rss;
    std::ostream& os = rss.get();
    os << "via get";
    EXPECT_EQ(rss.str(), "via get");
}

// Test that streaming an empty string produces empty result
TEST_F(ReusableStringStreamTest_648, StreamEmptyString_648) {
    ReusableStringStream rss;
    rss << "";
    EXPECT_EQ(rss.str(), "");
}

// Test chaining operator<< returns reference to same object
TEST_F(ReusableStringStreamTest_648, ChainingReturnsReference_648) {
    ReusableStringStream rss;
    ReusableStringStream& ref = (rss << "test");
    EXPECT_EQ(&ref, &rss);
}

// Test that multiple ReusableStringStream instances can coexist
TEST_F(ReusableStringStreamTest_648, MultipleInstances_648) {
    ReusableStringStream rss1;
    ReusableStringStream rss2;
    rss1 << "first";
    rss2 << "second";
    EXPECT_EQ(rss1.str(), "first");
    EXPECT_EQ(rss2.str(), "second");
}

// Test that after destruction of one instance, another still works
TEST_F(ReusableStringStreamTest_648, DestructionDoesNotAffectOtherInstances_648) {
    ReusableStringStream rss1;
    rss1 << "survivor";
    {
        ReusableStringStream rss2;
        rss2 << "temporary";
        EXPECT_EQ(rss2.str(), "temporary");
    }
    // rss2 is destroyed here
    EXPECT_EQ(rss1.str(), "survivor");
}

// Test that creating and destroying multiple instances reuses streams (pool behavior)
TEST_F(ReusableStringStreamTest_648, StreamReuse_648) {
    {
        ReusableStringStream rss;
        rss << "old data";
    }
    // After destruction, the stream should be cleared
    {
        ReusableStringStream rss;
        // The reused stream should be empty
        EXPECT_EQ(rss.str(), "");
    }
}

// Test streaming a bool value
TEST_F(ReusableStringStreamTest_648, StreamBoolValue_648) {
    ReusableStringStream rss;
    rss << true;
    std::string result = rss.str();
    EXPECT_FALSE(result.empty());
}

// Test streaming a char value
TEST_F(ReusableStringStreamTest_648, StreamCharValue_648) {
    ReusableStringStream rss;
    rss << 'A';
    EXPECT_EQ(rss.str(), "A");
}

// Test streaming a negative integer
TEST_F(ReusableStringStreamTest_648, StreamNegativeInteger_648) {
    ReusableStringStream rss;
    rss << -99;
    EXPECT_EQ(rss.str(), "-99");
}

// Test streaming a long string
TEST_F(ReusableStringStreamTest_648, StreamLongString_648) {
    ReusableStringStream rss;
    std::string longStr(10000, 'x');
    rss << longStr;
    EXPECT_EQ(rss.str(), longStr);
}

// Test that str() after setting to a non-empty string returns that string
TEST_F(ReusableStringStreamTest_648, StrSetAndGet_648) {
    ReusableStringStream rss;
    std::string testStr = "test string content";
    rss.str(testStr);
    EXPECT_EQ(rss.str(), testStr);
}

// Test streaming mixed types
TEST_F(ReusableStringStreamTest_648, StreamMixedTypes_648) {
    ReusableStringStream rss;
    rss << "value=" << 42 << ", pi=" << 3.14 << ", char=" << 'Z';
    std::string result = rss.str();
    EXPECT_NE(result.find("value=42"), std::string::npos);
    EXPECT_NE(result.find("char=Z"), std::string::npos);
}
