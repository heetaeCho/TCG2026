// File: json_value_writer_bool_tests_538.cpp

#include <gtest/gtest.h>
#include <sstream>

// Include the public header (path per the prompt)
#include "catch2/internal/catch_jsonwriter.hpp"

using namespace Catch;

class JsonValueWriterBoolTest_538 : public ::testing::Test {};

// Normal operation: writing `true` as rvalue writes unquoted literal "true"
TEST_F(JsonValueWriterBoolTest_538, WritesTrueWithoutQuotes_538) {
    std::ostringstream os;
    JsonValueWriter writer(os);
    std::move(writer).write(true);  // rvalue-qualified call
    EXPECT_EQ(os.str(), "true");
}

// Normal operation: writing `false` as rvalue writes unquoted literal "false"
TEST_F(JsonValueWriterBoolTest_538, WritesFalseWithoutQuotes_538) {
    std::ostringstream os;
    JsonValueWriter writer(os);
    std::move(writer).write(false); // rvalue-qualified call
    EXPECT_EQ(os.str(), "false");
}

// Boundary / construction variant: temporary rvalue is accepted and behaves the same
TEST_F(JsonValueWriterBoolTest_538, TemporaryWriterWritesTrue_538) {
    std::ostringstream os;
    // Direct temporary should satisfy && qualifier
    JsonValueWriter(os).write(true);
    EXPECT_EQ(os.str(), "true");
}

// Boundary: using the alternate ctor (with indent level, if available) still yields plain literals
TEST_F(JsonValueWriterBoolTest_538, IndentedWriterStillUnquotedBool_538) {
    std::ostringstream os;
    // Use the (os, indent_level) ctor if exposed; treat as black box regarding indent effects.
    JsonValueWriter writerWithIndent(os, /*indent_level*/ 4);
    std::move(writerWithIndent).write(false);
    EXPECT_EQ(os.str(), "false");
}
