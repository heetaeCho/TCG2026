// File: tests/ArrayOstreamOperator_68_test.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Library headers (adjust include paths to your project layout)
#include "JsonBox/Value.h"
#include "JsonBox/Array.h"

using JsonBox::Value;
using JsonBox::Array;

// Helper: normalize output so tests don't rely on the exact indentation style.
// We only test the structural characters, element order, commas, and newlines.
static std::string NormalizeLeadingIndent(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    bool at_line_start = true;
    for (char c : s) {
        if (at_line_start && (c == ' ' || c == '\t')) {
            // skip leading spaces/tabs on each line
            continue;
        }
        out.push_back(c);
        if (c == '\n' || c == '\r') {
            at_line_start = true;
        } else {
            at_line_start = false;
        }
    }
    return out;
}

class ArrayOstreamOperatorTest_68 : public ::testing::Test {
protected:
    static std::string Print(const Array& a) {
        std::ostringstream oss;
        oss << a;
        return oss.str();
    }
    static std::string NPrint(const Array& a) {
        return NormalizeLeadingIndent(Print(a));
    }
};

// Empty array prints [] exactly (no spaces, no newlines).
TEST_F(ArrayOstreamOperatorTest_68, EmptyArrayPrintsBracketPair_68) {
    Array a; // empty
    EXPECT_EQ("[]", Print(a));
}

// Single simple element: appears on its own line between [ and ],
// with newlines before and after, and no trailing comma.
TEST_F(ArrayOstreamOperatorTest_68, SingleBooleanElement_Newlines_NoTrailingComma_68) {
    Array a;
    a.push_back(Value(true));

    const std::string normalized = NPrint(a);
    EXPECT_EQ("[\ntrue\n]", normalized);
}

// Two simple elements: appear on separate lines, with a comma line-separator ",\n".
TEST_F(ArrayOstreamOperatorTest_68, TwoNumericElements_CommaAndNewlines_68) {
    Array a;
    a.push_back(Value(1));
    a.push_back(Value(2));

    const std::string normalized = NPrint(a);
    EXPECT_EQ("[\n1,\n2\n]", normalized);
}

// String element should be quoted (delegated to Value's ostream<<).
// We only assert structural formatting and quotes, ignoring indentation.
TEST_F(ArrayOstreamOperatorTest_68, StringElement_IsQuotedAndOnOwnLine_68) {
    Array a;
    a.push_back(Value(std::string("hello")));

    const std::string normalized = NPrint(a);
    EXPECT_EQ("[\n\"hello\"\n]", normalized);
}

// Stream is returned by reference and remains usable (chaining).
// We verify output is immediately followed by subsequent stream content.
TEST_F(ArrayOstreamOperatorTest_68, StreamChaining_ReturnsSameStream_68) {
    Array a;
    a.push_back(Value(42));

    std::ostringstream oss;
    (oss << a) << "TAIL";

    // After normalization, we expect the array then "TAIL" without extra characters.
    const std::string normalized = NormalizeLeadingIndent(oss.str());
    EXPECT_EQ("[\n42\n]TAIL", normalized);
}

// Order is preserved: elements appear in insertion order.
TEST_F(ArrayOstreamOperatorTest_68, PreservesElementOrder_68) {
    Array a;
    a.push_back(Value(10));
    a.push_back(Value(20));
    a.push_back(Value(30));

    const std::string normalized = NPrint(a);
    EXPECT_EQ("[\n10,\n20,\n30\n]", normalized);
}
