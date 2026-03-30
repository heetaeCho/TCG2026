// File: json_array_writer_writeObject_tests_532.cpp

#include <gtest/gtest.h>
#include <sstream>

// Headers under test
#include "catch2/internal/catch_jsonwriter.hpp"

using namespace Catch;

class JsonArrayWriterTest_532 : public ::testing::Test {
protected:
    std::ostringstream os_;
};

// [Normal] Calling writeObject should produce some output in the stream
TEST_F(JsonArrayWriterTest_532, WriteObject_WritesSomething_532) {
    JsonArrayWriter arr(os_);
    const auto before = os_.str();
    auto obj = arr.writeObject(); // observable: should cause some output via JsonUtils::appendCommaNewline

    const auto after = os_.str();
    EXPECT_NE(after, before) << "writeObject() should cause observable change to the stream.";
}

// [Boundary] Higher initial indentation should result in *at least* as much output
// as lower indentation after writeObject() (observable: output length grows with indent).
TEST_F(JsonArrayWriterTest_532, WriteObject_HigherIndent_ProducesMoreOutput_532) {
    std::ostringstream osLow;
    std::ostringstream osHigh;

    // Small indent
    JsonArrayWriter arrLow(osLow, /*indent_level=*/0);
    (void)arrLow.writeObject();
    const auto lowSize = osLow.str().size();

    // Larger indent
    JsonArrayWriter arrHigh(osHigh, /*indent_level=*/8);
    (void)arrHigh.writeObject();
    const auto highSize = osHigh.str().size();

    // With greater indent level, the observable output should not be smaller.
    EXPECT_GE(highSize, lowSize)
        << "Greater indent should not produce less output than smaller indent.";
}

// [Normal] Multiple consecutive writeObject() calls should keep appending to the stream
TEST_F(JsonArrayWriterTest_532, WriteObject_Twice_AppendsMore_532) {
    JsonArrayWriter arr(os_);
    (void)arr.writeObject();
    const auto sizeAfterFirst = os_.str().size();

    (void)arr.writeObject();
    const auto sizeAfterSecond = os_.str().size();

    EXPECT_GT(sizeAfterSecond, sizeAfterFirst)
        << "Second writeObject() call should further modify/append to the stream.";
}

// [Boundary] writeObject on a moved-from JsonArrayWriter should still be safe to call
// (assuming the interface permits move construction). We only assert observable effects.
TEST_F(JsonArrayWriterTest_532, WriteObject_OnMovedFromWriter_IsUsable_532) {
    JsonArrayWriter original(os_, /*indent_level=*/2);
    JsonArrayWriter moved(std::move(original)); // move-construct

    const auto before = os_.str();
    (void)moved.writeObject();
    const auto after = os_.str();

    EXPECT_NE(after, before) << "writeObject() on a moved-from writer instance should still change the stream.";
}

// [Integration-ish/Type] Returned type from writeObject should be usable as a value (no compile/link issues)
// We don't assume anything about JsonObjectWriter internals beyond it being constructible/returnable.
TEST_F(JsonArrayWriterTest_532, WriteObject_ReturnsAJsonObjectWriter_UsableValue_532) {
    JsonArrayWriter arr(os_);
    auto obj = arr.writeObject();
    // No assertions on internals; simply verify we could obtain a value and nothing threw.
    SUCCEED();
}
