// File: tests/json_array_writer_dtor_tests_531.cpp

#include <gtest/gtest.h>
#include <sstream>

// Assuming the real project headers are available at this path
#include "catch2/internal/catch_jsonwriter.hpp"

using Catch::JsonArrayWriter;

// Small helper to count a character’s occurrences in a string (observable-only).
static size_t CountChar(const std::string& s, char c) {
    return static_cast<size_t>(std::count(s.begin(), s.end(), c));
}

// The fixture is simple for clarity/future extension.
class JsonArrayWriterTest_531 : public ::testing::Test {};

// Verifies that destroying an active JsonArrayWriter appends a newline + indent + closing bracket.
// We do not assume the exact indentation; we only assert the observable formatting contract:
//  - there is at least one newline
//  - the final character is a closing bracket ']'
TEST_F(JsonArrayWriterTest_531, DestructorWritesClosingBracket_531) {
    std::ostringstream oss;

    {
        // Construct with an explicit indent level to exercise the newline+indent path.
        JsonArrayWriter arr(oss, /*indent_level=*/0);
        // Intentionally do nothing else; treat class as a black box.
    } // arr goes out of scope; destructor should finalize the array

    const std::string out = oss.str();

    // Observable assertions (no reliance on internals):
    ASSERT_FALSE(out.empty()) << "Stream should not be empty after writer destruction.";
    ASSERT_EQ(out.back(), ']') << "Destructor should close the JSON array with a ']'.";
    ASSERT_NE(out.find('\n'), std::string::npos)
        << "Destructor should write a newline before the closing bracket.";
}

// Verifies that moving the writer transfers responsibility for finalization,
// so the moved-from instance does not close the array again.
// Observable effect: only one closing bracket is present in the stream.
TEST_F(JsonArrayWriterTest_531, MovedFromDoesNotCloseTwice_531) {
    std::ostringstream oss;

    {
        JsonArrayWriter a(oss, /*indent_level=*/0);
        JsonArrayWriter b(std::move(a));
        // 'a' is moved-from and should not write anything on destruction.
        // 'b' remains active and should close once on destruction.
    }

    const std::string out = oss.str();
    EXPECT_FALSE(out.empty());
    EXPECT_EQ(out.back(), ']') << "Final character should be the single closing bracket from the active writer.";
    EXPECT_EQ(CountChar(out, ']'), 1u)
        << "Exactly one closing bracket should be written (no double-close).";
}

// Verifies that when an indent level > 0 is used, the destructor writes
// a newline and then some indentation characters before the final ']',
// without assuming a specific indentation scheme.
// We only check that characters between the last newline and the final ']'
// are whitespace (e.g., spaces or tabs).
TEST_F(JsonArrayWriterTest_531, DestructorRespectsIndentFormatting_531) {
    std::ostringstream oss;

    {
        JsonArrayWriter arr(oss, /*indent_level=*/2);
        // No further calls; black-box usage.
    }

    const std::string out = oss.str();
    ASSERT_FALSE(out.empty());
    ASSERT_EQ(out.back(), ']');

    const auto nl_pos = out.rfind('\n');
    ASSERT_NE(nl_pos, std::string::npos) << "Expected a newline before the closing bracket.";
    ASSERT_LT(nl_pos, out.size() - 1) << "There should be characters after the newline.";

    // Check that any characters after the last newline and before ']' are whitespace.
    for (size_t i = nl_pos + 1; i + 1 < out.size(); ++i) {
        const unsigned char ch = static_cast<unsigned char>(out[i]);
        EXPECT_TRUE(ch == ' ' || ch == '\t')
            << "Expected indentation (spaces/tabs) before closing bracket, found char code: " << int(ch);
    }
}

// Sanity check that destruction writes the closing bracket even if the stream already contains data.
// We do not assert what the writer added pre-destruction; we only assert that the final character is ']'.
TEST_F(JsonArrayWriterTest_531, DestructorAppendsClosingBracketToExistingStream_531) {
    std::ostringstream oss;
    oss << "prefix-data";

    {
        JsonArrayWriter arr(oss, /*indent_level=*/0);
        // No further interaction.
    }

    const std::string out = oss.str();
    ASSERT_GE(out.size(), std::string("prefix-data").size());
    EXPECT_EQ(out.back(), ']') << "Closing bracket should be appended on destruction.";
}
