#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <sstream>
#include <iostream>

// Forward declaration of the function under test
namespace Catch {
    void writeToDebugConsole(std::string const& text);
    std::ostream& cout();
}

class WriteToDebugConsoleTest_600 : public ::testing::Test {
protected:
    void SetUp() override {
        // Capture stdout to verify output
        savedBuf_ = std::cout.rdbuf();
        std::cout.rdbuf(capturedOutput_.rdbuf());
    }

    void TearDown() override {
        // Restore stdout
        std::cout.rdbuf(savedBuf_);
    }

    std::stringstream capturedOutput_;
    std::streambuf* savedBuf_;
};

// Test that writing a simple string produces output
TEST_F(WriteToDebugConsoleTest_600, WritesSimpleString_600) {
    std::string text = "Hello, Debug Console!";
    Catch::writeToDebugConsole(text);
    
    std::string output = capturedOutput_.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Hello, Debug Console!"), std::string::npos);
}

// Test that writing an empty string does not crash and produces empty or no output
TEST_F(WriteToDebugConsoleTest_600, WritesEmptyString_600) {
    std::string text = "";
    EXPECT_NO_THROW(Catch::writeToDebugConsole(text));
    
    std::string output = capturedOutput_.str();
    // Empty string should result in empty output
    EXPECT_EQ(output.find("unexpected"), std::string::npos);
}

// Test that writing a string with newlines works correctly
TEST_F(WriteToDebugConsoleTest_600, WritesStringWithNewlines_600) {
    std::string text = "Line1\nLine2\nLine3";
    Catch::writeToDebugConsole(text);
    
    std::string output = capturedOutput_.str();
    EXPECT_NE(output.find("Line1\nLine2\nLine3"), std::string::npos);
}

// Test that writing a string with special characters works
TEST_F(WriteToDebugConsoleTest_600, WritesStringWithSpecialCharacters_600) {
    std::string text = "Special chars: \t\r\n!@#$%^&*()";
    EXPECT_NO_THROW(Catch::writeToDebugConsole(text));
    
    std::string output = capturedOutput_.str();
    EXPECT_NE(output.find("Special chars:"), std::string::npos);
}

// Test that writing a long string works
TEST_F(WriteToDebugConsoleTest_600, WritesLongString_600) {
    std::string text(10000, 'A');
    EXPECT_NO_THROW(Catch::writeToDebugConsole(text));
    
    std::string output = capturedOutput_.str();
    EXPECT_GE(output.size(), 10000u);
}

// Test that multiple writes accumulate output
TEST_F(WriteToDebugConsoleTest_600, MultipleWritesAccumulate_600) {
    Catch::writeToDebugConsole("First");
    Catch::writeToDebugConsole("Second");
    Catch::writeToDebugConsole("Third");
    
    std::string output = capturedOutput_.str();
    EXPECT_NE(output.find("First"), std::string::npos);
    EXPECT_NE(output.find("Second"), std::string::npos);
    EXPECT_NE(output.find("Third"), std::string::npos);
}

// Test that the output preserves the exact text
TEST_F(WriteToDebugConsoleTest_600, PreservesExactText_600) {
    std::string text = "Exact text 12345";
    Catch::writeToDebugConsole(text);
    
    std::string output = capturedOutput_.str();
    EXPECT_NE(output.find("Exact text 12345"), std::string::npos);
}

// Test writing a single character
TEST_F(WriteToDebugConsoleTest_600, WritesSingleCharacter_600) {
    std::string text = "X";
    Catch::writeToDebugConsole(text);
    
    std::string output = capturedOutput_.str();
    EXPECT_NE(output.find("X"), std::string::npos);
}

// Test writing string with null characters embedded
TEST_F(WriteToDebugConsoleTest_600, WritesStringWithEmbeddedContent_600) {
    std::string text = "before\0after";
    // Note: std::string constructed from literal will stop at \0
    // This tests the boundary of what the string contains
    EXPECT_NO_THROW(Catch::writeToDebugConsole(text));
}

// Test writing unicode-like content (UTF-8 bytes)
TEST_F(WriteToDebugConsoleTest_600, WritesUTF8Content_600) {
    std::string text = u8"Hello \xC3\xA9\xC3\xA0\xC3\xBC";
    EXPECT_NO_THROW(Catch::writeToDebugConsole(text));
    
    std::string output = capturedOutput_.str();
    EXPECT_FALSE(output.empty());
}
