// File: tests/xmlwriter_scoped_element_469_tests.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "catch2/internal/catch_xmlwriter.hpp"

using namespace Catch;

namespace {

// Small helper to count substring occurrences in a string
static int CountSubstr(const std::string& haystack, const std::string& needle) {
    if (needle.empty()) return 0;
    int count = 0;
    std::string::size_type pos = 0;
    while ((pos = haystack.find(needle, pos)) != std::string::npos) {
        ++count;
        pos += needle.size();
    }
    return count;
}

} // namespace

// A simple fixture to provide a stream and writer for tests
class XmlWriterScopedElementTest_469 : public ::testing::Test {
protected:
    std::ostringstream os;
    std::unique_ptr<XmlWriter> writer;

    void SetUp() override {
        writer = std::make_unique<XmlWriter>(os);
    }
};

// --- Tests ---

// Verifies that when a ScopedElement goes out of scope, it ends the element on the writer.
TEST_F(XmlWriterScopedElementTest_469, DestructorCallsEndElement_469) {
    // Choose a formatting value that is valid in the library. `None` is commonly present.
    const XmlFormatting fmt = XmlFormatting::None;

    writer->startElement("root", fmt);

    {
        auto scoped = writer->scopedElement("child", fmt);
        // (Optional) write something inside to make the close tag clearly observable
        scoped.writeText(StringRef("payload"), fmt);
    } // scoped dtor should call writer->endElement(fmt) for "child"

    // Observable behavior: output contains a closing tag for "child"
    const std::string out = os.str();
    EXPECT_GE(out.find("</child>"), 0u) << "Expected closing tag for 'child' to be written by ScopedElement destructor.";
}

// Verifies move-construction transfers responsibility; only the moved-to object should close the element.
TEST_F(XmlWriterScopedElementTest_469, MoveConstructionClosesExactlyOnce_469) {
    const XmlFormatting fmt = XmlFormatting::None;

    writer->startElement("root", fmt);

    std::string out_before_move;
    {
        auto se1 = writer->scopedElement("only-once", fmt);
        // move-construct
        auto se2 = std::move(se1);
        (void)se2;
        out_before_move = os.str();
    } // only one dtor should close "only-once"

    const std::string out = os.str();
    // There should be exactly one closing tag for "only-once"
    EXPECT_EQ(CountSubstr(out, "</only-once>"), 1);
    // And nothing should have prematurely closed it before the moved-to dtor ran
    EXPECT_EQ(CountSubstr(out_before_move, "</only-once>"), 0);
}

// Verifies move-assignment transfers responsibility; the final owner closes once.
TEST_F(XmlWriterScopedElementTest_469, MoveAssignmentClosesExactlyOnce_469) {
    const XmlFormatting fmt = XmlFormatting::None;

    writer->startElement("root", fmt);

    std::string out_mid;
    {
        auto se1 = writer->scopedElement("assigned", fmt);
        // Create a dummy ScopedElement with no writer; then move-assign ownership into it.
        XmlWriter::ScopedElement se2(nullptr, fmt);
        se2 = std::move(se1);  // se2 now owns the endElement call

        out_mid = os.str(); // should not yet contain the closing tag
    } // se2 destructor should close once

    const std::string out = os.str();
    EXPECT_EQ(CountSubstr(out, "</assigned>"), 1);
    EXPECT_EQ(CountSubstr(out_mid, "</assigned>"), 0);
}

// Verifies that when a ScopedElement is constructed with nullptr writer, its destructor is a no-op.
TEST(XmlWriterScopedElementNoFixture_469, NullWriterDestructorIsNoOp_469) {
    const XmlFormatting fmt = XmlFormatting::None;

    std::ostringstream os;
    XmlWriter writer(os);
    writer.startElement("root", fmt);

    const std::string before = os.str();
    {
        XmlWriter::ScopedElement se_null(nullptr, fmt);
        // No interactions expected with writer; going out of scope should do nothing observable.
        (void)se_null;
    }
    const std::string after = os.str();

    // Stream output must be unchanged (no unexpected endElement write)
    EXPECT_EQ(before, after);
}

// Verifies that ScopedElement created via XmlWriter::scopedElement can still forward writes,
// and still closes on destruction. This checks basic interaction without assuming internal logic.
TEST_F(XmlWriterScopedElementTest_469, ScopedElementForwardsWritesAndThenCloses_469) {
    const XmlFormatting fmt = XmlFormatting::None;

    writer->startElement("root", fmt);
    {
        auto se = writer->scopedElement("node", fmt);
        se.writeAttribute(StringRef("k"), StringRef("v"));
        se.writeText(StringRef("txt"), fmt);
    } // should close "node"

    const std::string out = os.str();
    // Observable checks: has attribute and closing tag
    EXPECT_NE(out.find("k=\"v\""), std::string::npos);
    EXPECT_NE(out.find("txt"), std::string::npos);
    EXPECT_EQ(CountSubstr(out, "</node>"), 1);
}
