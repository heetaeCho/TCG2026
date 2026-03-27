// File: tests/xmlwriter_writeAttribute_template_18_tests.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Include the headers under test
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_stringref.hpp"

using Catch::XmlWriter;
using Catch::StringRef;

// A tiny helper: require that a substring appears in the final XML output.
// We keep this intentionally weak to avoid relying on exact formatting.
static void ExpectContains(const std::string& haystack, const std::string& needle) {
    ASSERT_NE(haystack.find(needle), std::string::npos)
        << "Expected to find substring [" << needle << "] in output:\n" << haystack;
}

// A minimal stand‑in streamable type to exercise the templated overload
// (not convertible to StringRef, but has operator<<).
struct StreamableThing {
    int a{0};
};

static std::ostream& operator<<(std::ostream& os, const StreamableThing& s) {
    return os << "Thing(" << s.a << ")";
}

// Note: We assume an XmlFormatting value that does not alter core emission logic
// is available as `XmlFormatting::None`. If your codebase uses a different name
// for the "no special formatting" value, adjust below accordingly.
enum class XmlFormatting : unsigned { None = 0 };

class XmlWriterWriteAttributeTest_18 : public ::testing::Test {
protected:
    std::ostringstream oss;
};

// [18] Normal operation with arithmetic types
TEST_F(XmlWriterWriteAttributeTest_18, WritesArithmeticAttributes_18) {
    XmlWriter w(oss);

    // Open an element so attributes have a place to go.
    // Use whatever "no-op" formatting your project defines; here we use None.
    w.startElement("root", XmlFormatting::None);

    // Exercise the templated overload with types not convertible to StringRef
    // (int, double, long long, etc.)
    w.writeAttribute("count", 42)
     .writeAttribute("pi", 3.1415)
     .writeAttribute("neg", -7LL);

    // Close the element to flush any pending tag text.
    w.endElement(XmlFormatting::None);

    const std::string out = oss.str();

    // We do not assert exact XML formatting; we only assert that the textual
    // representations made it into the output.
    ExpectContains(out, "42");
    ExpectContains(out, "3.1415");
    ExpectContains(out, "-7");
}

// [18] Custom streamable type routes through operator<<
TEST_F(XmlWriterWriteAttributeTest_18, StreamsCustomTypeThroughOperatorShift_18) {
    XmlWriter w(oss);
    w.startElement("node", XmlFormatting::None);

    StreamableThing s{5};
    w.writeAttribute("payload", s);

    w.endElement(XmlFormatting::None);

    const std::string out = oss.str();
    // If the templated overload streamed into ReusableStringStream and forwarded
    // to the StringRef overload, we should observe the streamed text in output.
    ExpectContains(out, "Thing(5)");
}

// [18] Chaining works (returns XmlWriter&)
TEST_F(XmlWriterWriteAttributeTest_18, ReturnsSelfForChaining_18) {
    XmlWriter w(oss);
    w.startElement("chain", XmlFormatting::None);

    // The function returns XmlWriter&, so the address should remain identical.
    XmlWriter* retPtr =
        &w.writeAttribute("first", 1)
          .writeAttribute("second", 2);

    EXPECT_EQ(retPtr, &w);

    w.endElement(XmlFormatting::None);
    const std::string out = oss.str();
    // Light sanity: both values appear somewhere.
    ExpectContains(out, "1");
    ExpectContains(out, "2");
}
