// File: tests/json_array_writer_write_template_tests_526.cpp

#include <gtest/gtest.h>
#include <sstream>
#include "catch2/internal/catch_jsonwriter.hpp"

using Catch::JsonArrayWriter;

class JsonArrayWriterWriteTemplateTest_526 : public ::testing::Test {};

// [Normal] Calling template write<T> (e.g., int) returns self for chaining.
TEST_F(JsonArrayWriterWriteTemplateTest_526, WriteInt_ReturnsSelf_526) {
    std::ostringstream os;
    JsonArrayWriter writer{os};

    auto& ret = writer.write(42);  // template write<T>
    EXPECT_EQ(&ret, &writer) << "write<T> should return reference to the same writer for chaining";
    // Observable effect through collaborator (ostream): something should be written
    EXPECT_FALSE(os.str().empty()) << "write<T> should produce some output to the provided stream";
}

// [Normal] Chaining multiple template writes (e.g., C-string -> template)
TEST_F(JsonArrayWriterWriteTemplateTest_526, WriteCString_Chains_526) {
    std::ostringstream os;
    JsonArrayWriter writer{os};

    auto& ret = writer.write("hello").write("world");  // both via template write<T>
    EXPECT_EQ(&ret, &writer) << "Chained template writes should keep returning the same writer";
    EXPECT_FALSE(os.str().empty()) << "Chained writes should result in non-empty stream output";
}

// [Boundary] Writing boundary-ish values still returns self & touches stream.
TEST_F(JsonArrayWriterWriteTemplateTest_526, WriteZeroAndEmptyString_526) {
    std::ostringstream os;
    JsonArrayWriter writer{os};

    auto& ret = writer.write(0).write("");  // template write<T> for int and const char*
    EXPECT_EQ(&ret, &writer);
    EXPECT_FALSE(os.str().empty()) << "Even boundary-ish values should lead to some observable output";
}

// [Interaction with other overloads] Mixing template write<T> with bool overload still chains.
TEST_F(JsonArrayWriterWriteTemplateTest_526, ChainTemplateWithBoolOverload_526) {
    std::ostringstream os;
    JsonArrayWriter writer{os};

    auto& ret = writer.write(1)    // template
                      .write(false) // dedicated bool overload
                      .write(2);    // template
    EXPECT_EQ(&ret, &writer) << "Mixing overloads should preserve fluent chaining";
    EXPECT_FALSE(os.str().empty()) << "Mixed writes should produce some output";
}

// [Move semantics] After move-constructing, template write<T> still works and returns self.
TEST_F(JsonArrayWriterWriteTemplateTest_526, MoveConstructedWriter_TemplateWriteReturnsSelf_526) {
    std::ostringstream os;
    JsonArrayWriter original{os};
    JsonArrayWriter moved{std::move(original)};  // move ctor per interface

    auto& ret = moved.write(123);  // template write<T>
    EXPECT_EQ(&ret, &moved) << "write<T> on a moved-into writer should return the same writer";
    EXPECT_FALSE(os.str().empty()) << "write<T> should still produce output after move construction";
}
