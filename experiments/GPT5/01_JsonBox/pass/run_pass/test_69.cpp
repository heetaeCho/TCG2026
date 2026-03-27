// File: test_object_stream_operator_69.cpp
#include <gtest/gtest.h>
#include <sstream>
#include "JsonBox/Value.h"  // brings in JsonBox::Value and typedefs for Object/Array

using namespace JsonBox;

class ObjectStreamOperatorTest_69 : public ::testing::Test {};

// Empty object: should be "{}" exactly (no newline).
TEST_F(ObjectStreamOperatorTest_69, EmptyObjectPrintsEmptyBraces_69) {
    Object o;
    std::ostringstream oss;
    oss << o;
    EXPECT_EQ("{}", oss.str());
}

// Single entry formatting: "{\n" ... "\"key\" : value" ... "\n}"
// We avoid asserting indentation; we only check stable, public-facing formatting.
TEST_F(ObjectStreamOperatorTest_69, SingleEntryFormatting_69) {
    Object o;
    o["age"] = Value(30);

    std::ostringstream oss;
    oss << o;
    const std::string out = oss.str();

    // Starts with opening brace + newline; ends with newline + closing brace.
    ASSERT_GE(out.size(), static_cast<size_t>(3));
    EXPECT_EQ('{', out.front());
    EXPECT_EQ('}', out.back());
    // Expect at least one newline inside non-empty object formatting.
    EXPECT_NE(std::string::npos, out.find("{\n"));
    EXPECT_NE(std::string::npos, out.find("\n}"));

    // Key/value formatting with quotes and spaces around ':'.
    EXPECT_NE(std::string::npos, out.find("\"age\" : 30"));

    // Single pair → no comma present.
    EXPECT_EQ(std::string::npos, out.find(','));
}

// Multiple entries: check order (map iteration order), separator ",\n", and final "\n}".
TEST_F(ObjectStreamOperatorTest_69, MultipleEntriesOrderingAndSeparators_69) {
    Object o;
    o["a"] = Value(1);
    o["b"] = Value(2);
    o["c"] = Value(3);

    std::ostringstream oss;
    oss << o;
    const std::string out = oss.str();

    // Basic envelope checks.
    EXPECT_NE(std::string::npos, out.find("{\n"));
    EXPECT_NE(std::string::npos, out.find("\n}"));

    // There should be ",\n" between entries (at least twice).
    // We don't assert indentation that may appear after the newline.
    size_t first_sep = out.find(",\n");
    EXPECT_NE(std::string::npos, first_sep);
    size_t second_sep = out.find(",\n", first_sep + 2);
    EXPECT_NE(std::string::npos, second_sep);

    // Keys should appear in lexicographical order: "a", then "b", then "c".
    size_t pos_a = out.find("\"a\" : 1");
    size_t pos_b = out.find("\"b\" : 2");
    size_t pos_c = out.find("\"c\" : 3");
    ASSERT_NE(std::string::npos, pos_a);
    ASSERT_NE(std::string::npos, pos_b);
    ASSERT_NE(std::string::npos, pos_c);
    EXPECT_LT(pos_a, pos_b);
    EXPECT_LT(pos_b, pos_c);
}

// Key escaping: verify quotes and backslashes in keys are escaped in output.
// We don't assume anything about value formatting beyond simple, observable output.
TEST_F(ObjectStreamOperatorTest_69, KeyEscapingWithQuotesAndBackslashes_69) {
    Object o;
    // Key contains a quote and a backslash: expect \" and \\ within the JSON key string.
    std::string trickyKey = "a\"b\\c";
    o[trickyKey] = Value(true);

    std::ostringstream oss;
    oss << o;
    const std::string out = oss.str();

    // The escaped key should appear as: "a\"b\\c" within quotes in the output.
    // In C++ string literal that substring is written as: "\"a\\\"b\\\\c\""
    EXPECT_NE(std::string::npos, out.find("\"a\\\"b\\\\c\""));

    // Ensure basic surrounding structure for non-empty object.
    EXPECT_NE(std::string::npos, out.find("{\n"));
    EXPECT_NE(std::string::npos, out.find("\n}"));
}

// Mixed value types: ensure value portion is streamed via Value's operator<<
// (observable by presence of expected literal forms).
TEST_F(ObjectStreamOperatorTest_69, ValuesAreStreamedViaValueOperator_69) {
    Object o;
    o["n"] = Value(42);
    o["s"] = Value(std::string("x"));
    o["t"] = Value(true);
    o["d"] = Value(3.14);

    std::ostringstream oss;
    oss << o;
    const std::string out = oss.str();

    // We expect to see the obvious literal representations somewhere in the output.
    // Avoids asserting order/indent beyond what's necessary.
    EXPECT_NE(std::string::npos, out.find("\"n\" : 42"));
    // String should appear quoted in JSON output.
    EXPECT_NE(std::string::npos, out.find("\"s\" : \"x\""));
    EXPECT_NE(std::string::npos, out.find("\"t\" : true"));
    // Double representation: allow either "3.14" or something like "3.14000"—just check "3.14" appears.
    EXPECT_NE(std::string::npos, out.find("\"d\" : 3.14"));

    // Non-empty object formatting envelope.
    EXPECT_NE(std::string::npos, out.find("{\n"));
    EXPECT_NE(std::string::npos, out.find("\n}"));
}
