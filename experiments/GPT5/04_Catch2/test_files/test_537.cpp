// JsonValueWriter_write_rvalue_tests_537.cpp
#include <gtest/gtest.h>
#include <sstream>

#include "catch2/internal/catch_jsonwriter.hpp"
#include "catch2/internal/catch_stringref.hpp"

using namespace Catch;

class JsonValueWriterRValueTest_537 : public ::testing::Test {};

// Verifies that calling the rvalue-qualified write(StringRef)&& writes the value
// to the bound ostream in a JSON string form (observable as quotes in output).
TEST_F(JsonValueWriterRValueTest_537, WriteStringRef_RValue_WritesQuotedValue_537) {
    std::ostringstream os;
    JsonValueWriter writer(os);

    std::move(writer).write(StringRef("hello"));

    EXPECT_EQ(os.str(), "\"hello\"");
}

// Boundary: empty string should still be represented as an empty JSON string.
TEST_F(JsonValueWriterRValueTest_537, WriteStringRef_RValue_EmptyString_537) {
    std::ostringstream os;
    JsonValueWriter writer(os);

    std::move(writer).write(StringRef(""));

    EXPECT_EQ(os.str(), "\"\"");
}

// Ensures that the exact content of the StringRef (including spaces) is preserved
// within the output’s quotes. This checks there is no extra trimming/whitespace added.
TEST_F(JsonValueWriterRValueTest_537, WriteStringRef_RValue_PreservesInnerWhitespace_537) {
    std::ostringstream os;
    JsonValueWriter writer(os);

    std::move(writer).write(StringRef("  spaced  "));

    EXPECT_EQ(os.str(), "\"  spaced  \"");
}
