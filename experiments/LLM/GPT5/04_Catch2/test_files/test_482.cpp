// tests/xmlwriter_ensure_tag_closed_482.cpp
#include <gtest/gtest.h>
#include <sstream>

// Include the public XmlWriter interface
#include "Catch2/src/catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

class XmlWriterEnsureTagClosedTest_482 : public ::testing::Test {
protected:
    std::stringstream ss;
    // Helper to count occurrences of a character in the stream so far
    static size_t countChar(const std::string& s, char c) {
        return static_cast<size_t>(std::count(s.begin(), s.end(), c));
    }
};

// [482] When no tag is open, ensureTagClosed should not write anything.
TEST_F(XmlWriterEnsureTagClosedTest_482, NoOp_WhenTagNotOpen_482) {
    XmlWriter w(ss);

    const auto before = ss.str();
    w.ensureTagClosed();
    const auto after = ss.str();

    // Observable behavior: stream content unchanged
    EXPECT_EQ(before, after);
    // And there should be no '>' produced by ensureTagClosed
    EXPECT_EQ(countChar(after, '>'), 0u);
}

// [482] When a tag is open (after startElement), ensureTagClosed should write exactly one '>'.
// Calling it again should be a no-op (idempotent).
TEST_F(XmlWriterEnsureTagClosedTest_482, ClosesOpenTag_AndIsIdempotent_482) {
    XmlWriter w(ss);

    // Use startElement to create an open tag through the public API.
    // We do not assume any specific formatting semantics; passing a default value is sufficient.
    // The implementation details are treated as black box per constraints.
    // If XmlFormatting is an enum class, default-constructing it yields a valid value.
    XmlFormatting fmt{};
    w.startElement("root", fmt);

    const auto afterStart = ss.str();
    const auto gtBefore = countChar(afterStart, '>');

    // First call should close the open tag and write one '>'.
    w.ensureTagClosed();
    const auto afterCloseOnce = ss.str();
    const auto gtAfterOnce = countChar(afterCloseOnce, '>');
    ASSERT_EQ(gtAfterOnce, gtBefore + 1) << "ensureTagClosed should write exactly one '>' when a tag is open";

    // Second call should do nothing (no additional '>').
    w.ensureTagClosed();
    const auto afterCloseTwice = ss.str();
    const auto gtAfterTwice = countChar(afterCloseTwice, '>');
    EXPECT_EQ(gtAfterTwice, gtAfterOnce) << "ensureTagClosed should be idempotent when called again";
}
