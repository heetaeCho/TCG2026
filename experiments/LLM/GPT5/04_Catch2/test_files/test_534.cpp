// JsonArrayWriter_write_bool_tests_534.cpp
#include <gtest/gtest.h>
#include <sstream>
#include "catch2/internal/catch_jsonwriter.hpp"

using Catch::JsonArrayWriter;

class JsonArrayWriterTest_534 : public ::testing::Test {
protected:
    std::ostringstream os_;
};

// Normal operation: writing `true` writes something and returns self
TEST_F(JsonArrayWriterTest_534, WriteTrue_WritesSomethingAndReturnsSelf_534) {
    JsonArrayWriter writer(os_);
    JsonArrayWriter& ret = writer.write(true);

    // Observable effect: stream received some output (exact format not assumed)
    EXPECT_FALSE(os_.str().empty());

    // Interface contract: returns reference to the same object (chainable)
    EXPECT_EQ(&ret, &writer);
}

// Normal operation: writing `false` writes something
TEST_F(JsonArrayWriterTest_534, WriteFalse_WritesSomething_534) {
    JsonArrayWriter writer(os_);
    writer.write(false);

    EXPECT_FALSE(os_.str().empty());
}

// Boundary/variation: outputs for true vs false differ (without assuming exact text)
TEST_F(JsonArrayWriterTest_534, TrueVsFalse_ProduceDifferentOutputs_534) {
    std::ostringstream os_true;
    std::ostringstream os_false;

    {
        JsonArrayWriter w_true(os_true);
        w_true.write(true);
    }
    {
        JsonArrayWriter w_false(os_false);
        w_false.write(false);
    }

    // We only assert they are not identical; no assumption about exact formatting.
    EXPECT_NE(os_true.str(), os_false.str());
}

// Chaining behavior: multiple writes append additional output
TEST_F(JsonArrayWriterTest_534, ChainedWrites_AppendsMoreOutput_534) {
    JsonArrayWriter writer(os_);
    size_t before = os_.str().size();

    // Should be chainable according to return type
    writer.write(true).write(false);
    size_t after_first_two = os_.str().size();

    writer.write(true);
    size_t after_three = os_.str().size();

    // Each step should have increased observable output
    EXPECT_GT(after_first_two, before);
    EXPECT_GT(after_three, after_first_two);
}

// Constructor variant: writer with explicit indent level still writes
TEST_F(JsonArrayWriterTest_534, IndentedConstructor_StillWrites_534) {
    JsonArrayWriter writer(os_, /*indent_level*/ 2ULL);
    writer.write(true);

    EXPECT_FALSE(os_.str().empty());
}

// Move semantics: moved-from to moved-to writer remains usable (observable via stream)
TEST_F(JsonArrayWriterTest_534, MoveConstructedWriter_WritesToStream_534) {
    // Create a writer, then move-construct a new one and use it.
    JsonArrayWriter original(os_);
    JsonArrayWriter moved(std::move(original));

    moved.write(true);

    EXPECT_FALSE(os_.str().empty());
}
