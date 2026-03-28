#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>

#include "JsonBox/Value.h"
#include "JsonBox/Array.h"

using namespace JsonBox;

class ArrayOutputTest_68 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// Test that an empty array outputs "[]"
TEST_F(ArrayOutputTest_68, EmptyArrayOutputsBrackets_68) {
    Array a;
    oss << a;
    EXPECT_EQ("[]", oss.str());
}

// Test that a single-element array outputs correctly with begin/end array markers
TEST_F(ArrayOutputTest_68, SingleElementArray_68) {
    Array a;
    Value v(42);
    a.push_back(v);
    oss << a;
    std::string result = oss.str();
    // Should start with '[' and end with ']'
    EXPECT_EQ('[', result.front());
    EXPECT_EQ(']', result.back());
    // Should contain the value
    EXPECT_NE(std::string::npos, result.find("42"));
    // Should NOT contain a comma (only one element)
    EXPECT_EQ(std::string::npos, result.find(','));
}

// Test that a multi-element array has commas separating values
TEST_F(ArrayOutputTest_68, MultipleElementsHaveCommaSeparators_68) {
    Array a;
    a.push_back(Value(1));
    a.push_back(Value(2));
    a.push_back(Value(3));
    oss << a;
    std::string result = oss.str();
    EXPECT_EQ('[', result.front());
    EXPECT_EQ(']', result.back());
    // Should contain commas
    // Count commas - should be exactly 2 for 3 elements
    int commaCount = 0;
    for (char c : result) {
        if (c == ',') commaCount++;
    }
    EXPECT_EQ(2, commaCount);
    // Should contain all three values
    EXPECT_NE(std::string::npos, result.find("1"));
    EXPECT_NE(std::string::npos, result.find("2"));
    EXPECT_NE(std::string::npos, result.find("3"));
}

// Test that a two-element array has exactly one comma
TEST_F(ArrayOutputTest_68, TwoElementsOneComma_68) {
    Array a;
    a.push_back(Value(10));
    a.push_back(Value(20));
    oss << a;
    std::string result = oss.str();
    int commaCount = 0;
    for (char c : result) {
        if (c == ',') commaCount++;
    }
    EXPECT_EQ(1, commaCount);
}

// Test that non-empty array output contains newlines (due to indentation)
TEST_F(ArrayOutputTest_68, NonEmptyArrayContainsNewlines_68) {
    Array a;
    a.push_back(Value(1));
    oss << a;
    std::string result = oss.str();
    EXPECT_NE(std::string::npos, result.find('\n'));
}

// Test that empty array output does NOT contain newlines
TEST_F(ArrayOutputTest_68, EmptyArrayNoNewlines_68) {
    Array a;
    oss << a;
    std::string result = oss.str();
    EXPECT_EQ(std::string::npos, result.find('\n'));
}

// Test that the stream is in good state after outputting
TEST_F(ArrayOutputTest_68, StreamGoodStateAfterOutput_68) {
    Array a;
    a.push_back(Value("hello"));
    a.push_back(Value(3.14));
    oss << a;
    EXPECT_TRUE(oss.good());
}

// Test that the stream's rdbuf is properly restored after output
TEST_F(ArrayOutputTest_68, StreamRdbufRestoredAfterOutput_68) {
    Array a;
    a.push_back(Value(1));
    std::streambuf* originalBuf = oss.rdbuf();
    oss << a;
    EXPECT_EQ(originalBuf, oss.rdbuf());
}

// Test that stream rdbuf is unchanged for empty array
TEST_F(ArrayOutputTest_68, EmptyArrayStreamRdbufUnchanged_68) {
    Array a;
    std::streambuf* originalBuf = oss.rdbuf();
    oss << a;
    EXPECT_EQ(originalBuf, oss.rdbuf());
}

// Test nested array output
TEST_F(ArrayOutputTest_68, NestedArrayOutput_68) {
    Array inner;
    inner.push_back(Value(1));
    inner.push_back(Value(2));
    
    Array outer;
    outer.push_back(Value(inner));
    oss << outer;
    std::string result = oss.str();
    // Should have begin/end markers for outer array
    EXPECT_EQ('[', result.front());
    EXPECT_EQ(']', result.back());
    // Should contain inner array brackets too
    // Count '[' - should be at least 2
    int openCount = 0;
    for (char c : result) {
        if (c == '[') openCount++;
    }
    EXPECT_GE(openCount, 2);
}

// Test array with string values
TEST_F(ArrayOutputTest_68, ArrayWithStringValues_68) {
    Array a;
    a.push_back(Value("foo"));
    a.push_back(Value("bar"));
    oss << a;
    std::string result = oss.str();
    EXPECT_NE(std::string::npos, result.find("foo"));
    EXPECT_NE(std::string::npos, result.find("bar"));
}

// Test chaining output operator
TEST_F(ArrayOutputTest_68, ChainingOutputOperator_68) {
    Array a1;
    Array a2;
    a2.push_back(Value(42));
    oss << a1 << a2;
    std::string result = oss.str();
    // a1 is empty: "[]", a2 has content
    EXPECT_EQ('[', result[0]);
    EXPECT_EQ(']', result[1]);
    // The rest should be a2's output
    EXPECT_NE(std::string::npos, result.find("42"));
}
