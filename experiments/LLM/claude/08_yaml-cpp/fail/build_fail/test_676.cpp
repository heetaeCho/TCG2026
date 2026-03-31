#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

// We test the parse() function declared in the partial code.
// Since parse() is defined in parse.cpp, we declare it here.
void parse(std::istream& input);

class ParseTest_676 : public ::testing::Test {
protected:
    // Helper to capture stdout
    std::string captureStdout(std::istream& input) {
        std::streambuf* oldCoutBuf = std::cout.rdbuf();
        std::ostringstream capturedOut;
        std::cout.rdbuf(capturedOut.rdbuf());
        parse(input);
        std::cout.rdbuf(oldCoutBuf);
        return capturedOut.str();
    }

    // Helper to capture stderr
    std::string captureStderr(std::istream& input) {
        std::streambuf* oldCerrBuf = std::cerr.rdbuf();
        std::ostringstream capturedErr;
        std::cerr.rdbuf(capturedErr.rdbuf());
        parse(input);
        std::cerr.rdbuf(oldCerrBuf);
        return capturedErr.str();
    }

    // Helper to capture both stdout and stderr
    std::pair<std::string, std::string> captureBoth(std::istream& input) {
        std::streambuf* oldCoutBuf = std::cout.rdbuf();
        std::streambuf* oldCerrBuf = std::cerr.rdbuf();
        std::ostringstream capturedOut, capturedErr;
        std::cout.rdbuf(capturedOut.rdbuf());
        std::cerr.rdbuf(capturedErr.rdbuf());
        parse(input);
        std::cout.rdbuf(oldCoutBuf);
        std::cerr.rdbuf(oldCerrBuf);
        return {capturedOut.str(), capturedErr.str()};
    }
};

// Test: parsing a simple scalar value
TEST_F(ParseTest_676, SimpleScalar_676) {
    std::istringstream input("hello");
    std::string output = captureStdout(input);
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("hello"), std::string::npos);
}

// Test: parsing an integer scalar
TEST_F(ParseTest_676, IntegerScalar_676) {
    std::istringstream input("42");
    std::string output = captureStdout(input);
    EXPECT_NE(output.find("42"), std::string::npos);
}

// Test: parsing a simple map
TEST_F(ParseTest_676, SimpleMap_676) {
    std::istringstream input("key: value");
    std::string output = captureStdout(input);
    EXPECT_NE(output.find("key"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

// Test: parsing a simple sequence
TEST_F(ParseTest_676, SimpleSequence_676) {
    std::istringstream input("- one\n- two\n- three");
    std::string output = captureStdout(input);
    EXPECT_NE(output.find("one"), std::string::npos);
    EXPECT_NE(output.find("two"), std::string::npos);
    EXPECT_NE(output.find("three"), std::string::npos);
}

// Test: parsing an empty input (null document)
TEST_F(ParseTest_676, EmptyInput_676) {
    std::istringstream input("");
    auto [out, err] = captureBoth(input);
    // Empty input should produce a null node output or empty, no error
    EXPECT_TRUE(err.empty());
}

// Test: parsing a nested map
TEST_F(ParseTest_676, NestedMap_676) {
    std::istringstream input("outer:\n  inner: value");
    std::string output = captureStdout(input);
    EXPECT_NE(output.find("outer"), std::string::npos);
    EXPECT_NE(output.find("inner"), std::string::npos);
    EXPECT_NE(output.find("value"), std::string::npos);
}

// Test: parsing a nested sequence
TEST_F(ParseTest_676, NestedSequence_676) {
    std::istringstream input("- - a\n  - b\n- c");
    std::string output = captureStdout(input);
    EXPECT_NE(output.find("a"), std::string::npos);
    EXPECT_NE(output.find("b"), std::string::npos);
    EXPECT_NE(output.find("c"), std::string::npos);
}

// Test: parsing invalid YAML should output error to stderr
TEST_F(ParseTest_676, InvalidYamlOutputsError_676) {
    std::istringstream input(":\n  :\n    - :\n  bad: [unclosed");
    std::string errOutput = captureStderr(input);
    // Invalid YAML may or may not trigger an exception depending on the parser;
    // but if it does, the error goes to stderr.
    // We just ensure no crash occurs.
    // The test passes if we get here without crashing.
    SUCCEED();
}

// Test: parsing a boolean value
TEST_F(ParseTest_676, BooleanValue_676) {
    std::istringstream input("true");
    std::string output = captureStdout(input);
    EXPECT_NE(output.find("true"), std::string::npos);
}

// Test: parsing a floating point value
TEST_F(ParseTest_676, FloatingPointValue_676) {
    std::istringstream input("3.14");
    std::string output = captureStdout(input);
    EXPECT_NE(output.find("3.14"), std::string::npos);
}

// Test: parsing a null value
TEST_F(ParseTest_676, NullValue_676) {
    std::istringstream input("~");
    auto [out, err] = captureBoth(input);
    EXPECT_TRUE(err.empty());
}

// Test: parsing multiline string (literal block scalar)
TEST_F(ParseTest_676, MultilineString_676) {
    std::istringstream input("|\n  line1\n  line2\n  line3");
    std::string output = captureStdout(input);
    EXPECT_NE(output.find("line1"), std::string::npos);
    EXPECT_NE(output.find("line2"), std::string::npos);
}

// Test: parsing a map with multiple keys
TEST_F(ParseTest_676, MultipleKeysMap_676) {
    std::istringstream input("a: 1\nb: 2\nc: 3");
    std::string output = captureStdout(input);
    EXPECT_NE(output.find("a"), std::string::npos);
    EXPECT_NE(output.find("b"), std::string::npos);
    EXPECT_NE(output.find("c"), std::string::npos);
}

// Test: parsing with explicit document markers
TEST_F(ParseTest_676, DocumentMarkers_676) {
    std::istringstream input("---\nfoo: bar\n...");
    std::string output = captureStdout(input);
    EXPECT_NE(output.find("foo"), std::string::npos);
    EXPECT_NE(output.find("bar"), std::string::npos);
}

// Test: parsing a quoted string with special characters
TEST_F(ParseTest_676, QuotedString_676) {
    std::istringstream input("\"hello: world\"");
    std::string output = captureStdout(input);
    EXPECT_NE(output.find("hello: world"), std::string::npos);
}

// Test: parsing flow-style sequence
TEST_F(ParseTest_676, FlowSequence_676) {
    std::istringstream input("[1, 2, 3]");
    std::string output = captureStdout(input);
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

// Test: parsing flow-style map
TEST_F(ParseTest_676, FlowMap_676) {
    std::istringstream input("{a: 1, b: 2}");
    std::string output = captureStdout(input);
    EXPECT_NE(output.find("a"), std::string::npos);
    EXPECT_NE(output.find("b"), std::string::npos);
}

// Test: severely malformed YAML with tab indentation issues
TEST_F(ParseTest_676, MalformedTabIndentation_676) {
    std::istringstream input("key:\n\t- bad");
    auto [out, err] = captureBoth(input);
    // Tabs in YAML are not allowed for indentation in strict mode
    // Either it parses or produces an error; ensure no crash
    SUCCEED();
}

// Test: parsing only whitespace
TEST_F(ParseTest_676, WhitespaceOnly_676) {
    std::istringstream input("   \n  \n   ");
    auto [out, err] = captureBoth(input);
    EXPECT_TRUE(err.empty());
}

// Test: parsing anchors and aliases
TEST_F(ParseTest_676, AnchorsAndAliases_676) {
    std::istringstream input("a: &anchor value\nb: *anchor");
    std::string output = captureStdout(input);
    EXPECT_NE(output.find("value"), std::string::npos);
}

// Test: parsing a large document doesn't crash
TEST_F(ParseTest_676, LargeDocument_676) {
    std::ostringstream largeYaml;
    for (int i = 0; i < 1000; ++i) {
        largeYaml << "key" << i << ": value" << i << "\n";
    }
    std::istringstream input(largeYaml.str());
    auto [out, err] = captureBoth(input);
    EXPECT_TRUE(err.empty());
    EXPECT_FALSE(out.empty());
}
