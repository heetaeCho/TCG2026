// XmlWriter_dtor_tests_472.cpp
#include <gtest/gtest.h>
#include <sstream>
#include "catch2/internal/catch_xmlwriter.hpp"

namespace {

// Helper: a neutral XmlFormatting value without depending on any specific enum member.
static inline Catch::XmlFormatting Fmt0() {
    return static_cast<Catch::XmlFormatting>(0);
}

} // namespace

// Verifies that when a single element is left open, the destructor closes it
// (either as a self-closing tag or with an explicit closing tag).
TEST(XmlWriterDtorTest_472, DtorClosesSingleOpenElement_472) {
    std::ostringstream os;
    {
        Catch::XmlWriter w(os);
        w.startElement(std::string("root"), Fmt0());
        // Intentionally do not call endElement()
        // Destructor should close any remaining open tags.
    }

    const std::string out = os.str();

    // Accept either <root/> or <root ...></root>, with any whitespace/newlines.
    // We avoid asserting exact formatting.
    const bool hasSelfClosed = out.find("<root/>") != std::string::npos ||
                               out.find("<root />") != std::string::npos;
    const bool hasExplicitClose = out.find("</root>") != std::string::npos;

    EXPECT_TRUE(hasSelfClosed || hasExplicitClose)
        << "Destructor should have closed the 'root' element. Output was:\n" << out;
}

// Verifies that multiple nested open elements are all closed by the destructor.
// We only assert that *each* element is closed in some way (self-closing or explicit).
TEST(XmlWriterDtorTest_472, DtorClosesNestedOpenElements_472) {
    std::ostringstream os;
    {
        Catch::XmlWriter w(os);
        w.startElement(std::string("a"), Fmt0());
        w.startElement(std::string("b"), Fmt0());
        // No explicit endElement() calls; dtor should close all.
    }

    const std::string out = os.str();

    const bool bClosed = (out.find("<b/>") != std::string::npos) ||
                         (out.find("<b />") != std::string::npos) ||
                         (out.find("</b>") != std::string::npos);

    const bool aClosed = (out.find("<a/>") != std::string::npos) ||
                         (out.find("<a />") != std::string::npos) ||
                         (out.find("</a>") != std::string::npos);

    EXPECT_TRUE(bClosed) << "Expected 'b' to be closed by destructor. Output:\n" << out;
    EXPECT_TRUE(aClosed) << "Expected 'a' to be closed by destructor. Output:\n" << out;
}

// Verifies that destroying an untouched XmlWriter does not emit stray open tags,
// and (conservatively) allows either empty output or a trailing newline depending on implementation.
TEST(XmlWriterDtorTest_472, DtorOnEmptyWriterProducesNoUnfinishedTags_472) {
    std::ostringstream os;
    {
        Catch::XmlWriter w(os);
        // Do nothing; just let it go out of scope.
    }

    const std::string out = os.str();

    // There should be no raw unclosed tag starts like '<' without closing.
    // Conservatively, we assert the output is either empty or ends with a newline,
    // without over-specifying formatting.
    const bool emptyOutput = out.empty();
    const bool newlineOnly = (!out.empty() && out.find('<') == std::string::npos);

    EXPECT_TRUE(emptyOutput || newlineOnly)
        << "Unexpected output for empty writer destruction. Output was:\n" << out;
}

