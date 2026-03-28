#include <gtest/gtest.h>
#include <string>
#include <sstream>

// Include the header under test
#include "catch2/catch_message.hpp"

class MessageStreamTest_106 : public ::testing::Test {
protected:
    Catch::MessageStream stream;
};

// Test that operator<< returns a reference to the same MessageStream (chaining)
TEST_F(MessageStreamTest_106, OperatorReturnsReference_106) {
    auto& result = (stream << "hello");
    EXPECT_EQ(&result, &stream);
}

// Test inserting a string literal
TEST_F(MessageStreamTest_106, InsertStringLiteral_106) {
    stream << "hello world";
    std::string output = stream.m_stream.str();
    EXPECT_EQ(output, "hello world");
}

// Test inserting an integer
TEST_F(MessageStreamTest_106, InsertInteger_106) {
    stream << 42;
    std::string output = stream.m_stream.str();
    EXPECT_EQ(output, "42");
}

// Test inserting a negative integer
TEST_F(MessageStreamTest_106, InsertNegativeInteger_106) {
    stream << -100;
    std::string output = stream.m_stream.str();
    EXPECT_EQ(output, "-100");
}

// Test inserting a floating point number
TEST_F(MessageStreamTest_106, InsertDouble_106) {
    stream << 3.14;
    std::string output = stream.m_stream.str();
    EXPECT_FALSE(output.empty());
    // The output should contain "3.14" at minimum
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

// Test inserting a char
TEST_F(MessageStreamTest_106, InsertChar_106) {
    stream << 'A';
    std::string output = stream.m_stream.str();
    EXPECT_EQ(output, "A");
}

// Test chaining multiple insertions
TEST_F(MessageStreamTest_106, ChainingMultipleInsertions_106) {
    stream << "value=" << 42 << " done";
    std::string output = stream.m_stream.str();
    EXPECT_EQ(output, "value=42 done");
}

// Test inserting a std::string
TEST_F(MessageStreamTest_106, InsertStdString_106) {
    std::string msg = "test message";
    stream << msg;
    std::string output = stream.m_stream.str();
    EXPECT_EQ(output, "test message");
}

// Test inserting an empty string
TEST_F(MessageStreamTest_106, InsertEmptyString_106) {
    stream << "";
    std::string output = stream.m_stream.str();
    EXPECT_EQ(output, "");
}

// Test inserting a boolean value
TEST_F(MessageStreamTest_106, InsertBoolTrue_106) {
    stream << true;
    std::string output = stream.m_stream.str();
    // Could be "1" or "true" depending on stream flags
    EXPECT_FALSE(output.empty());
}

// Test inserting a boolean false value
TEST_F(MessageStreamTest_106, InsertBoolFalse_106) {
    stream << false;
    std::string output = stream.m_stream.str();
    EXPECT_FALSE(output.empty());
}

// Test inserting zero
TEST_F(MessageStreamTest_106, InsertZero_106) {
    stream << 0;
    std::string output = stream.m_stream.str();
    EXPECT_EQ(output, "0");
}

// Test inserting a long value
TEST_F(MessageStreamTest_106, InsertLong_106) {
    long val = 1234567890L;
    stream << val;
    std::string output = stream.m_stream.str();
    EXPECT_EQ(output, "1234567890");
}

// Test inserting a pointer (nullptr)
TEST_F(MessageStreamTest_106, InsertNullptr_106) {
    const void* ptr = nullptr;
    stream << ptr;
    std::string output = stream.m_stream.str();
    EXPECT_FALSE(output.empty());
}

// Test multiple sequential insertions accumulate
TEST_F(MessageStreamTest_106, MultipleInsertionsAccumulate_106) {
    stream << "A";
    stream << "B";
    stream << "C";
    std::string output = stream.m_stream.str();
    EXPECT_EQ(output, "ABC");
}

// Test inserting unsigned int
TEST_F(MessageStreamTest_106, InsertUnsignedInt_106) {
    unsigned int val = 4294967295U;
    stream << val;
    std::string output = stream.m_stream.str();
    EXPECT_EQ(output, "4294967295");
}

// Test chaining returns correct reference at each step
TEST_F(MessageStreamTest_106, ChainingReferencesConsistent_106) {
    auto& ref1 = (stream << "first");
    auto& ref2 = (ref1 << "second");
    EXPECT_EQ(&ref1, &stream);
    EXPECT_EQ(&ref2, &stream);
}
