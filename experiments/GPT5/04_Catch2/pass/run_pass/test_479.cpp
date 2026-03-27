// File: tests/xmlwriter_writeText_479_test.cpp
#include <gtest/gtest.h>
#include <sstream>

// Headers under test (paths follow the prompt)
#include "Catch2/src/catch2/internal/catch_xmlwriter.hpp"
#include "Catch2/src/catch2/internal/catch_stringref.hpp"

using Catch::XmlWriter;
using Catch::StringRef;

class XmlWriterWriteTextTest_479 : public ::testing::Test {
protected:
    std::ostringstream oss;
    // Use default-initialized formatting; we don't assume any specific flags.
    Catch::XmlFormatting fmt{};
};

// [Error/exceptional] Writing text at top level must throw (CATCH_ENFORCE)
TEST_F(XmlWriterWriteTextTest_479, WriteTextAtTopLevelThrows_479) {
    XmlWriter w(oss);
    EXPECT_ANY_THROW({
        w.writeText(StringRef("top"), fmt);
    });
}

// [Normal] Non-empty text is written to the underlying stream (observable substring)
TEST_F(XmlWriterWriteTextTest_479, WriteTextWritesContent_479) {
    XmlWriter w(oss);
    w.startElement("root", fmt);
    w.writeText(StringRef("hello"), fmt);
    w.endElement(fmt);

    const std::string out = oss.str();
    // We do not assert exact XML layout; only that the text content appears.
    EXPECT_NE(out.find("hello"), std::string::npos);
}

// [Boundary] Empty text: should NOT close the tag (since code path is skipped),
// so writing an attribute afterwards should still be allowed (no throw)
TEST_F(XmlWriterWriteTextTest_479, EmptyTextKeepsTagOpen_AllowsAttributeAfter_479) {
    XmlWriter w(oss);
    w.startElement("root", fmt);

    // Empty text
    w.writeText(StringRef(""), fmt);

    // If the tag remained open, writing an attribute should be valid.
    EXPECT_NO_THROW({
        w.writeAttribute(StringRef("k"), StringRef("v"));
    });

    w.endElement(fmt);

    const std::string out = oss.str();
    EXPECT_NE(out.find("k=\"v\""), std::string::npos);
}

// [Behavioral] Non-empty text closes an open start tag internally;
// attempting to write an attribute after text should fail (enforced by writer)
TEST_F(XmlWriterWriteTextTest_479, NonEmptyTextClosesTag_DisallowsAttributeAfter_479) {
    XmlWriter w(oss);
    w.startElement("root", fmt);
    w.writeText(StringRef("x"), fmt);

    // After writing non-empty text, attributes should no longer be accepted.
    EXPECT_ANY_THROW({
        w.writeAttribute(StringRef("later"), StringRef("nope"));
    });

    // Close to keep well-formed output where possible
    EXPECT_NO_THROW({ w.endElement(fmt); });
}

// [Encoding] Text is XML-encoded for text nodes (at least '&' and '<')
TEST_F(XmlWriterWriteTextTest_479, TextIsXmlEncoded_479) {
    XmlWriter w(oss);
    w.startElement("root", fmt);

    const char* raw = "A & B < C";
    w.writeText(StringRef(raw), fmt);
    w.endElement(fmt);

    const std::string out = oss.str();

    // The raw unescaped sequence should not appear
    EXPECT_EQ(out.find("A & B < C"), std::string::npos);

    // Encoded entities should appear for text nodes
    EXPECT_NE(out.find("A &amp; B &lt; C"), std::string::npos);
}
