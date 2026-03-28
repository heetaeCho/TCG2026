// File: tests/xmlwriter_end_element_475_tests.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Use the real header from the codebase.
#include "catch2/internal/catch_xmlwriter.hpp"

using Catch::XmlWriter;

// Helper that finds substring position, or returns npos-style large value.
static size_t posOrBig(const std::string& haystack, const std::string& needle) {
    const auto p = haystack.find(needle);
    return p == std::string::npos ? static_cast<size_t>(-1) : p;
}

// NOTE: We treat XmlFormatting purely as an opaque parameter. We pass a
// default-initialized value and DO NOT assert anything about formatting.
TEST(XmlWriterEndElementTest_475, SelfClosesWhenTagIsStillOpen_475) {
    std::ostringstream os;
    XmlWriter w(os);

    // Start an element and immediately end it: observable effect should be a self-closing tag.
    w.startElement("root", {});   // do not assume side effects beyond public signature
    w.endElement({});

    const std::string out = os.str();

    // Verify that endElement contributed the "/>" that makes it self-closing.
    // We DO NOT assert the full tag text or whitespace; only the presence of self-close.
    ASSERT_NE(out.find("/>"), std::string::npos) << "Expected self-closing tag ending produced by endElement";
}

TEST(XmlWriterEndElementTest_475, EmitsClosingTagIfContentClosedBefore_475) {
    std::ostringstream os;
    XmlWriter w(os);

    // Make sure the tag is not "open" by writing text first (forces closing the opening tag).
    w.startElement("root", {});
    w.writeText("x", {});         // observable: content written, opening tag no longer open
    w.endElement({});             // should now produce a full closing tag

    const std::string out = os.str();

    // Check that a proper closing tag for the last opened element appears.
    // We don't validate indentation/newlines; only that "</root>" is there.
    ASSERT_NE(out.find("</root>"), std::string::npos)
        << "Expected full closing tag for 'root' when the start tag was already closed";
}

TEST(XmlWriterEndElementTest_475, ClosesInnermostFirstInNestedStructure_475) {
    std::ostringstream os;
    XmlWriter w(os);

    // Create a simple nested structure:
    w.startElement("parent", {}); // <parent
    w.startElement("child", {});  //   <child
    // Close child first …
    w.endElement({});
    // … then parent.
    w.endElement({});

    const std::string out = os.str();

    // Validate ordering: the closing for 'child' must appear before the closing for 'parent'.
    const size_t closeChild = posOrBig(out, "</child>");
    const size_t closeParent = posOrBig(out, "</parent>");

    // For the case where 'child' was self-closed, look for "/>" after its start;
    // but the key requirement is that parent closes after child-related output.
    const size_t selfCloseChild = posOrBig(out, "/>");

    // We accept either (a) explicit </child> then </parent>, or (b) a self-close for child
    // followed by a closing for parent, but in both scenarios parent must close after child’s closure output.
    bool ok = false;
    if (closeChild != static_cast<size_t>(-1) && closeParent != static_cast<size_t>(-1)) {
        ok = closeChild < closeParent;
    } else if (selfCloseChild != static_cast<size_t>(-1) && closeParent != static_cast<size_t>(-1)) {
        ok = selfCloseChild < closeParent;
    }

    ASSERT_TRUE(ok) << "Expected child to be closed before parent in the stream output.\nOutput was:\n" << out;
}

TEST(XmlWriterEndElementTest_475, ClosingAfterTextKeepsEarlierContentIntact_475) {
    std::ostringstream os;
    XmlWriter w(os);

    // Start, write text (ensures opening tag is closed), then end.
    w.startElement("greeting", {});
    w.writeText("hello", {});
    w.endElement({});

    const std::string out = os.str();

    // The text "hello" must appear, and the element should be closed afterwards.
    const size_t textPos = out.find("hello");
    ASSERT_NE(textPos, std::string::npos) << "Expected written text to be present";

    const size_t closeTagPos = out.find("</greeting>");
    ASSERT_NE(closeTagPos, std::string::npos) << "Expected a closing tag for 'greeting'";

    // The closing tag should come after the text content.
    ASSERT_LT(textPos, closeTagPos) << "Closing tag should be written after element content";
}
