// File: json_object_writer_write_tests_530.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

// Include the headers from the provided interface
#include "catch2/internal/catch_jsonwriter.hpp"
#include "catch2/internal/catch_stringref.hpp"

using ::testing::EndsWith;

namespace Catch {

class JsonObjectWriterWriteTests_530 : public ::testing::Test {
protected:
    std::ostringstream os;
};

/*
 * Verifies that calling write(key) appends `"key": ` to the output stream.
 * We do not depend on any prefix emitted by JsonUtils::appendCommaNewline,
 * so we only check the tail of the stream.
 */
TEST_F(JsonObjectWriterWriteTests_530, WritesQuotedKeyAndColonSpace_530) {
    JsonObjectWriter writer(os, /*indent_level=*/0);

    auto valueWriter = writer.write(StringRef("name"));
    (void)valueWriter; // We do not examine JsonValueWriter internals.

    EXPECT_THAT(os.str(), EndsWith("\"name\": "));
}

/*
 * Boundary: empty key should still write `"": `
 */
TEST_F(JsonObjectWriterWriteTests_530, WritesEmptyKey_530) {
    JsonObjectWriter writer(os, /*indent_level=*/0);

    auto valueWriter = writer.write(StringRef(""));
    (void)valueWriter;

    EXPECT_THAT(os.str(), EndsWith("\"\": "));
}

/*
 * Unicode/UTF-8 keys are forwarded as provided through StringRef.
 * We validate the observable bytes appear before the trailing `: `.
 */
TEST_F(JsonObjectWriterWriteTests_530, WritesUtf8KeyUnmodified_530) {
    JsonObjectWriter writer(os, /*indent_level=*/0);

    const std::string utf8Key = u8"키";
    auto valueWriter = writer.write(StringRef(utf8Key));
    (void)valueWriter;

    EXPECT_THAT(os.str(), EndsWith("\"키\": "));
}

/*
 * Multiple calls: each call should append another `"key": ` segment.
 * We only assert the stream ends with the last key’s `"key": ` to avoid
 * depending on comma/newline formatting handled by JsonUtils.
 */
TEST_F(JsonObjectWriterWriteTests_530, MultipleWritesEndWithLastKey_530) {
    JsonObjectWriter writer(os, /*indent_level=*/0);

    (void)writer.write(StringRef("first"));
    std::string afterFirst = os.str();
    EXPECT_THAT(afterFirst, EndsWith("\"first\": "));

    (void)writer.write(StringRef("second"));
    std::string afterSecond = os.str();
    EXPECT_THAT(afterSecond, EndsWith("\"second\": "));
}

} // namespace Catch
