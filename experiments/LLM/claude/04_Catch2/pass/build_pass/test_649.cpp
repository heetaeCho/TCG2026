#include <gtest/gtest.h>
#include <string>
#include <sstream>

// Include the header for the class under test
#include "catch2/internal/catch_reusable_string_stream.hpp"

class ReusableStringStreamTest_649 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a newly constructed ReusableStringStream returns an empty string
TEST_F(ReusableStringStreamTest_649, DefaultConstructionReturnsEmptyString_649) {
    Catch::ReusableStringStream rss;
    EXPECT_EQ(rss.str(), "");
}

// Test that streaming a string and retrieving it works
TEST_F(ReusableStringStreamTest_649, StreamStringAndRetrieve_649) {
    Catch::ReusableStringStream rss;
    rss << "Hello, World!";
    EXPECT_EQ(rss.str(), "Hello, World!");
}

// Test that streaming an integer works
TEST_F(ReusableStringStreamTest_649, StreamIntegerAndRetrieve_649) {
    Catch::ReusableStringStream rss;
    rss << 42;
    EXPECT_EQ(rss.str(), "42");
}

// Test that streaming a floating point number works
TEST_F(ReusableStringStreamTest_649, StreamFloatingPointAndRetrieve_649) {
    Catch::ReusableStringStream rss;
    rss << 3.14;
    std::string result = rss.str();
    EXPECT_FALSE(result.empty());
    // Verify it contains "3.14" at minimum
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

// Test that multiple streams concatenate correctly
TEST_F(ReusableStringStreamTest_649, MultipleStreamsConcat_649) {
    Catch::ReusableStringStream rss;
    rss << "Hello" << " " << "World";
    EXPECT_EQ(rss.str(), "Hello World");
}

// Test that streaming mixed types works
TEST_F(ReusableStringStreamTest_649, StreamMixedTypes_649) {
    Catch::ReusableStringStream rss;
    rss << "Value: " << 100 << " and " << true;
    std::string result = rss.str();
    EXPECT_NE(result.find("Value: "), std::string::npos);
    EXPECT_NE(result.find("100"), std::string::npos);
}

// Test that str(const std::string&) sets the content
TEST_F(ReusableStringStreamTest_649, SetStrResetsContent_649) {
    Catch::ReusableStringStream rss;
    rss << "Initial content";
    rss.str("");
    EXPECT_EQ(rss.str(), "");
}

// Test that str(const std::string&) replaces the content
TEST_F(ReusableStringStreamTest_649, SetStrReplacesContent_649) {
    Catch::ReusableStringStream rss;
    rss << "First";
    rss.str("Second");
    EXPECT_EQ(rss.str(), "Second");
}

// Test that get() returns a valid ostream reference
TEST_F(ReusableStringStreamTest_649, GetReturnsValidOstream_649) {
    Catch::ReusableStringStream rss;
    std::ostream& os = rss.get();
    os << "Via get()";
    EXPECT_EQ(rss.str(), "Via get()");
}

// Test streaming an empty string
TEST_F(ReusableStringStreamTest_649, StreamEmptyString_649) {
    Catch::ReusableStringStream rss;
    rss << "";
    EXPECT_EQ(rss.str(), "");
}

// Test that multiple ReusableStringStream instances don't interfere
TEST_F(ReusableStringStreamTest_649, MultipleInstancesIndependent_649) {
    Catch::ReusableStringStream rss1;
    Catch::ReusableStringStream rss2;
    rss1 << "Stream1";
    rss2 << "Stream2";
    EXPECT_EQ(rss1.str(), "Stream1");
    EXPECT_EQ(rss2.str(), "Stream2");
}

// Test streaming a char
TEST_F(ReusableStringStreamTest_649, StreamChar_649) {
    Catch::ReusableStringStream rss;
    rss << 'A';
    EXPECT_EQ(rss.str(), "A");
}

// Test streaming negative integer
TEST_F(ReusableStringStreamTest_649, StreamNegativeInteger_649) {
    Catch::ReusableStringStream rss;
    rss << -123;
    EXPECT_EQ(rss.str(), "-123");
}

// Test that after setting str to empty, new content can be streamed
TEST_F(ReusableStringStreamTest_649, ResetAndStreamAgain_649) {
    Catch::ReusableStringStream rss;
    rss << "First pass";
    rss.str("");
    rss << "Second pass";
    EXPECT_EQ(rss.str(), "Second pass");
}

// Test streaming a long string
TEST_F(ReusableStringStreamTest_649, StreamLongString_649) {
    Catch::ReusableStringStream rss;
    std::string longStr(10000, 'x');
    rss << longStr;
    EXPECT_EQ(rss.str(), longStr);
}

// Test that chaining operator<< returns a reference to the same object
TEST_F(ReusableStringStreamTest_649, ChainingReturnsSameObject_649) {
    Catch::ReusableStringStream rss;
    auto& ref = (rss << "test");
    EXPECT_EQ(&ref, &rss);
}

// Test that the destructor can be called (object goes out of scope without issues)
TEST_F(ReusableStringStreamTest_649, DestructionIsClean_649) {
    {
        Catch::ReusableStringStream rss;
        rss << "temporary";
    }
    // If we reach here, destruction was clean
    SUCCEED();
}

// Test streaming zero
TEST_F(ReusableStringStreamTest_649, StreamZero_649) {
    Catch::ReusableStringStream rss;
    rss << 0;
    EXPECT_EQ(rss.str(), "0");
}

// Test streaming a boolean false
TEST_F(ReusableStringStreamTest_649, StreamBoolFalse_649) {
    Catch::ReusableStringStream rss;
    rss << false;
    std::string result = rss.str();
    // false is typically "0" unless boolalpha is set
    EXPECT_FALSE(result.empty());
}

// Test creating and destroying multiple instances sequentially
TEST_F(ReusableStringStreamTest_649, SequentialInstanceReuse_649) {
    for (int i = 0; i < 10; ++i) {
        Catch::ReusableStringStream rss;
        rss << "Iteration " << i;
        std::string expected = "Iteration " + std::to_string(i);
        EXPECT_EQ(rss.str(), expected);
    }
}
