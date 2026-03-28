// File: tests/Value_Ostream_Operator_Test_67.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <map>
#include <vector>

#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueOstreamTest_67 : public ::testing::Test {};

// Prints "null" for a default-constructed Value.
TEST_F(ValueOstreamTest_67, PrintsNull_67) {
    Value v; // NULL_VALUE
    std::ostringstream oss;
    oss << v;
    EXPECT_EQ("null", oss.str());
}

// Prints boolean literals "true" and "false".
TEST_F(ValueOstreamTest_67, PrintsBooleanTrueFalse_67) {
    std::ostringstream ossTrue, ossFalse;
    Value vt(true), vf(false);

    ossTrue << vt;
    ossFalse << vf;

    EXPECT_EQ("true", ossTrue.str());
    EXPECT_EQ("false", ossFalse.str());
}

// Prints integer numerals as-is.
TEST_F(ValueOstreamTest_67, PrintsInteger_67) {
    Value vi(12345);
    std::ostringstream oss;
    oss << vi;
    EXPECT_EQ("12345", oss.str());
}

// For doubles: uses precision(17) during output and restores the original precision afterward.
TEST_F(ValueOstreamTest_67, PrintsDoubleWithPrecisionAndRestores_67) {
    Value vd(1.125); // clean decimal representation
    std::ostringstream oss;
    // Set a non-default precision to verify it gets restored.
    std::streamsize original = oss.precision(3);

    oss << vd;
    // Content expectation: with precision(17), "1.125" remains exactly "1.125".
    EXPECT_EQ("1.125", oss.str());

    // Precision should be restored to the previous value (3)
    EXPECT_EQ(3, oss.precision());
    // Also confirm original was whatever the stream held before (just to avoid unused var warning)
    (void)original;
}

// For non-double types, precision should not be modified.
TEST_F(ValueOstreamTest_67, DoesNotChangePrecisionForNonDouble_67) {
    std::ostringstream oss;
    oss.precision(4);
    Value vi(42);

    oss << vi;

    EXPECT_EQ("42", oss.str());
    EXPECT_EQ(4, oss.precision());
}

// Strings are wrapped in quotes and minimally escaped via escapeMinimumCharacters.
TEST_F(ValueOstreamTest_67, PrintsStringWithQuotesAndEscapesMinimum_67) {
    // Include characters likely to be minimally escaped (quote and backslash).
    const std::string raw = "say \"hi\" and \\ backslash";
    Value vs(raw);

    std::ostringstream oss;
    oss << vs;

    // Expected: quotes around escapeMinimumCharacters(raw)
    const std::string expected = std::string("\"") + Value::escapeMinimumCharacters(raw) + "\"";
    EXPECT_EQ(expected, oss.str());
}

// OBJECT: operator<< should delegate to the Object stream output.
TEST_F(ValueOstreamTest_67, DelegatesToObjectStream_67) {
    Object obj;
    obj["a"] = Value(1);
    obj["b"] = Value("x");

    Value v(obj);

    std::ostringstream ossObj, ossVal;
    // Whatever formatting Object's stream operator uses, Value must match it.
    ossObj << obj;
    ossVal << v;

    EXPECT_EQ(ossObj.str(), ossVal.str());
}

// ARRAY: operator<< should delegate to the Array stream output.
TEST_F(ValueOstreamTest_67, DelegatesToArrayStream_67) {
    Array arr;
    arr.push_back(Value(1));
    arr.push_back(Value(true));
    arr.push_back(Value("z"));

    Value v(arr);

    std::ostringstream ossArr, ossVal;
    // Whatever formatting Array's stream operator uses, Value must match it.
    ossArr << arr;
    ossVal << v;

    EXPECT_EQ(ossArr.str(), ossVal.str());
}
