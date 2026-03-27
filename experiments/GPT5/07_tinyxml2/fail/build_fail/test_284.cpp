// File: ./TestProjects/tinyxml2/tests/xml_document_print_test_284.cpp

#include <gtest/gtest.h>

#include <cstdio>

#include "tinyxml2.h"

namespace tinyxml2 {
namespace {

class XMLDocumentPrintTest_284 : public ::testing::Test {
protected:
    // A test double that observes XMLDocument::Print() via the virtual Accept().
    class ObservingDocument : public tinyxml2::XMLDocument {
    public:
        ObservingDocument(bool processEntities, tinyxml2::Whitespace whitespaceMode)
            : tinyxml2::XMLDocument(processEntities, whitespaceMode) {}

        bool Accept(tinyxml2::XMLVisitor* visitor) const override {
            ++acceptCallCount;
            lastVisitor = visitor;
            return acceptReturnValue;
        }

        // Mutable because Accept() is const.
        mutable int acceptCallCount{0};
        mutable tinyxml2::XMLVisitor* lastVisitor{nullptr};
        bool acceptReturnValue{true};
    };

    static FILE* MakeTempFileOrSkip() {
        FILE* fp = std::tmpfile();
        if (!fp) {
            GTEST_SKIP() << "tmpfile() failed; cannot construct XMLPrinter reliably on this platform.";
        }
        return fp;
    }
};

TEST_F(XMLDocumentPrintTest_284, PrintWithNonNullStreamer_CallsAcceptWithSamePointer_284) {
    ObservingDocument doc(/*processEntities=*/true, tinyxml2::PRESERVE_WHITESPACE);

    FILE* fp = MakeTempFileOrSkip();
    tinyxml2::XMLPrinter printer(fp, /*compact=*/false, /*depth=*/0);

    doc.Print(&printer);

    EXPECT_EQ(doc.acceptCallCount, 1);
    EXPECT_EQ(doc.lastVisitor, &printer);

    std::fclose(fp);
}

TEST_F(XMLDocumentPrintTest_284, PrintWithNullStreamer_CallsAcceptWithNonNullVisitor_284) {
    ObservingDocument doc(/*processEntities=*/true, tinyxml2::PRESERVE_WHITESPACE);

    doc.Print(nullptr);

    EXPECT_EQ(doc.acceptCallCount, 1);
    EXPECT_NE(doc.lastVisitor, nullptr);
}

TEST_F(XMLDocumentPrintTest_284, PrintCalledTwice_InvokesAcceptTwiceAndUpdatesVisitor_284) {
    ObservingDocument doc(/*processEntities=*/true, tinyxml2::PRESERVE_WHITESPACE);

    // First call uses internal stdout printer path (streamer == nullptr).
    doc.Print(nullptr);
    ASSERT_EQ(doc.acceptCallCount, 1);
    tinyxml2::XMLVisitor* firstVisitor = doc.lastVisitor;
    ASSERT_NE(firstVisitor, nullptr);

    // Second call uses provided streamer path.
    FILE* fp = MakeTempFileOrSkip();
    tinyxml2::XMLPrinter printer(fp, /*compact=*/true, /*depth=*/0);

    doc.Print(&printer);

    EXPECT_EQ(doc.acceptCallCount, 2);
    EXPECT_EQ(doc.lastVisitor, &printer);
    EXPECT_NE(doc.lastVisitor, firstVisitor);

    std::fclose(fp);
}

TEST_F(XMLDocumentPrintTest_284, PrintStillCallsAccept_EvenIfAcceptReturnsFalse_284) {
    ObservingDocument doc(/*processEntities=*/true, tinyxml2::PRESERVE_WHITESPACE);
    doc.acceptReturnValue = false;

    // Use the null streamer path; Print() must still call Accept().
    doc.Print(nullptr);

    EXPECT_EQ(doc.acceptCallCount, 1);
    EXPECT_NE(doc.lastVisitor, nullptr);
}

}  // namespace
}  // namespace tinyxml2
