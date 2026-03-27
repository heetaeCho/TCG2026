// File: tests/xmlwriter_writecomment_tests.cpp

#include <gtest/gtest.h>
#include <sstream>

#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_stringref.hpp"

using namespace Catch;

namespace {

// Helper: use a neutral formatting value without assuming enum contents.
// We avoid any inference about XmlFormatting; we just pass 0.
static constexpr int kNeutralFmtInt = 0;
static inline XmlFormatting NeutralFmt() {
    return static_cast<XmlFormatting>(kNeutralFmtInt);
}

} // namespace

// [480] Verifies that writeComment writes the comment delimiters with the provided text.
TEST(XmlWriter_WriteComment_480, WriteComment_WritesExactMarkerAndText_480) {
    std::ostringstream os;
    XmlWriter writer(os);

    writer.writeComment(StringRef("hello"), NeutralFmt());

    const std::string out = os.str();
    // We assert that the expected token appears, without assuming surrounding whitespace/newlines.
    ASSERT_NE(out.find("<!-- hello -->"), std::string::npos);
}

// [480] Verifies fluent API: writeComment returns a reference to the same writer for chaining.
TEST(XmlWriter_WriteComment_480, WriteComment_ReturnsSelfForChaining_480) {
    std::ostringstream os;
    XmlWriter writer(os);

    XmlWriter& returned = writer.writeComment(StringRef("first"), NeutralFmt());

    // Returned reference should be the same object (address equality).
    EXPECT_EQ(&returned, &writer);
    // And the output should contain the comment.
    EXPECT_NE(os.str().find("<!-- first -->"), std::string::npos);
}

// [480] Empty comment text should still produce a valid XML comment node.
TEST(XmlWriter_WriteComment_480, WriteComment_AllowsEmptyText_480) {
    std::ostringstream os;
    XmlWriter writer(os);

    writer.writeComment(StringRef(""), NeutralFmt());

    const std::string out = os.str();
    // Implementation writes "<!-- " + text + " -->", so with empty text we still expect the markers.
    EXPECT_NE(out.find("<!--  -->"), std::string::npos);
}

// [480] Special characters in the comment text should be preserved literally inside the comment.
TEST(XmlWriter_WriteComment_480, WriteComment_PreservesSpecialCharacters_480) {
    std::ostringstream os;
    XmlWriter writer(os);

    writer.writeComment(StringRef("&<>\"'"), NeutralFmt());

    const std::string out = os.str();
    EXPECT_NE(out.find("<!-- &<>\"' -->"), std::string::npos);
}

// [480] Multiple comments can be written; both should appear in order.
TEST(XmlWriter_WriteComment_480, WriteComment_MultipleCommentsAppearInOrder_480) {
    std::ostringstream os;
    XmlWriter writer(os);

    writer.writeComment(StringRef("one"), NeutralFmt())
          .writeComment(StringRef("two"), NeutralFmt());

    const std::string out = os.str();
    const size_t firstPos = out.find("<!-- one -->");
    const size_t secondPos = out.find("<!-- two -->");

    ASSERT_NE(firstPos, std::string::npos);
    ASSERT_NE(secondPos, std::string::npos);
    EXPECT_LT(firstPos, secondPos); // Ensure ordering
}
