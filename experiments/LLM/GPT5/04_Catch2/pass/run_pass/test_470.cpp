// File: xmlwriter_scopedelement_writeText_tests_470.cpp

#include <gtest/gtest.h>
#include <sstream>

// Headers from the provided codebase
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_stringref.hpp"

namespace {

using Catch::XmlWriter;
using Catch::StringRef;

// We do not depend on specific XmlFormatting values/semantics.
// Using zero-initialized value keeps us from inferring internal behavior.
static inline Catch::XmlFormatting Fmt0() {
    return static_cast<Catch::XmlFormatting>(0);
}

// Test fixture kept minimal; we create a fresh stream & writer per test.
class XmlWriterScopedElementTest_470 : public ::testing::Test {
protected:
    std::ostringstream os;
    XmlWriter writer{os};
};

} // namespace

// Verifies that writeText returns a reference to the same ScopedElement
// (fluent API), without asserting on internal formatting.
TEST_F(XmlWriterScopedElementTest_470, WriteText_ReturnsSelf_470) {
    auto se = writer.scopedElement("node", Fmt0());
    auto& ref = se.writeText(StringRef("content"), Fmt0());
    EXPECT_EQ(&ref, &se);
}

// Verifies that calling writeText actually results in the literal text
// being observable in the output written by XmlWriter (black-box check).
TEST_F(XmlWriterScopedElementTest_470, WriteText_WritesLiteralContent_470) {
    {
        auto se = writer.scopedElement("n", Fmt0());
        se.writeText(StringRef("Hello"), Fmt0());
        // se goes out of scope here; destructor may close element
    }
    const std::string out = os.str();
    // We only assert the presence of the literal content; we do not assert
    // anything about tags, indentation, or escaping.
    EXPECT_NE(out.find("Hello"), std::string::npos);
}

// Verifies chaining: multiple writeText calls on the same ScopedElement
// append content in order, observable via the output stream.
TEST_F(XmlWriterScopedElementTest_470, WriteText_AllowsChainingAndOrder_470) {
    {
        auto se = writer.scopedElement("n", Fmt0());
        se.writeText(StringRef("A"), Fmt0())
          .writeText(StringRef("B"), Fmt0());
    }
    const std::string out = os.str();
    const auto posA = out.find("A");
    const auto posB = out.find("B");
    ASSERT_NE(posA, std::string::npos);
    ASSERT_NE(posB, std::string::npos);
    EXPECT_LT(posA, posB); // "A" appears before "B"
}

// Boundary-ish case: empty text should be safe to call and not throw.
// We avoid asserting exact formatting; we only ensure no crash and output is produced.
TEST_F(XmlWriterScopedElementTest_470, WriteText_EmptyString_DoesNotThrow_470) {
    {
        auto se = writer.scopedElement("n", Fmt0());
        EXPECT_NO_THROW({
            se.writeText(StringRef(""), Fmt0());
        });
    }
    // Output exists; we do not assert its exact contents.
    (void)os.str();
}

// Move-safety: After moving a ScopedElement, writeText should still work
// (observable by content presence in the stream). We do not assert internal state.
TEST_F(XmlWriterScopedElementTest_470, WriteText_AfterMove_StillWrites_470) {
    {
        auto se = writer.scopedElement("n", Fmt0());
        auto moved = std::move(se);
        moved.writeText(StringRef("MovedOK"), Fmt0());
    }
    const std::string out = os.str();
    EXPECT_NE(out.find("MovedOK"), std::string::npos);
}
