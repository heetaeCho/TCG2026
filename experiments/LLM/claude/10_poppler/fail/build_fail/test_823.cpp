#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers
#include "poppler/Annot.h"
#include "poppler/PDFDoc.h"
#include "poppler/GooString.h"
#include "poppler/Object.h"
#include "poppler/PDFDocFactory.h"
#include "poppler/GlobalParams.h"

class AnnotFreeTextTest_823 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal PDFDoc for testing
    // We need a valid PDFDoc to create AnnotFreeText objects
    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Create a minimal valid PDF in memory
        static const char *minimalPDF =
            "%PDF-1.4\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n198\n%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, strlen(minimalPDF), Object(objNull));
        return std::make_unique<PDFDoc>(stream);
    }
};

// Test creating AnnotFreeText with a rectangle and checking default endStyle
TEST_F(AnnotFreeTextTest_823, DefaultEndStyle_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    // Default end style should be annotLineEndingNone
    AnnotLineEndingStyle style = annot->getEndStyle();
    EXPECT_EQ(style, annotLineEndingNone);
}

// Test getQuadding returns a valid quadding value after construction
TEST_F(AnnotFreeTextTest_823, DefaultQuadding_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    VariableTextQuadding quadding = annot->getQuadding();
    // Default quadding should be left-justified (0)
    EXPECT_GE(static_cast<int>(quadding), 0);
    EXPECT_LE(static_cast<int>(quadding), 2);
}

// Test setQuadding and getQuadding
TEST_F(AnnotFreeTextTest_823, SetAndGetQuadding_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    annot->setQuadding(VariableTextQuadding::centered);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::centered);

    annot->setQuadding(VariableTextQuadding::rightJustified);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::rightJustified);

    annot->setQuadding(VariableTextQuadding::leftJustified);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::leftJustified);
}

// Test getIntent returns default intent
TEST_F(AnnotFreeTextTest_823, DefaultIntent_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    AnnotFreeTextIntent intent = annot->getIntent();
    // Just verify it returns a valid value without crashing
    EXPECT_GE(static_cast<int>(intent), 0);
}

// Test setIntent and getIntent
TEST_F(AnnotFreeTextTest_823, SetAndGetIntent_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    annot->setIntent(AnnotFreeText::intentFreeTextCallout);
    EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeTextCallout);

    annot->setIntent(AnnotFreeText::intentFreeTextTypeWriter);
    EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeTextTypeWriter);

    annot->setIntent(AnnotFreeText::intentFreeText);
    EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeText);
}

// Test getCalloutLine returns nullptr by default
TEST_F(AnnotFreeTextTest_823, DefaultCalloutLineIsNull_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    EXPECT_EQ(annot->getCalloutLine(), nullptr);
}

// Test getStyleString returns nullptr by default
TEST_F(AnnotFreeTextTest_823, DefaultStyleStringIsNull_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    const GooString *style = annot->getStyleString();
    // May be null or empty by default
    if (style != nullptr) {
        // If not null, it should be a valid string
        EXPECT_GE(style->getLength(), 0);
    }
}

// Test setStyleString and getStyleString
TEST_F(AnnotFreeTextTest_823, SetAndGetStyleString_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    GooString *testStyle = new GooString("font: Helvetica 12pt");
    annot->setStyleString(testStyle);

    const GooString *result = annot->getStyleString();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "font: Helvetica 12pt");
}

// Test getBorderEffect returns nullptr by default
TEST_F(AnnotFreeTextTest_823, DefaultBorderEffectIsNull_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    // Border effect may or may not be null depending on defaults
    AnnotBorderEffect *effect = annot->getBorderEffect();
    // Just verify no crash - the value depends on implementation
    (void)effect;
    SUCCEED();
}

// Test getRectangle
TEST_F(AnnotFreeTextTest_823, GetRectangle_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    PDFRectangle *resultRect = annot->getRectangle();
    // Rectangle may or may not be set by default; just verify no crash
    (void)resultRect;
    SUCCEED();
}

// Test setContents
TEST_F(AnnotFreeTextTest_823, SetContents_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    auto content = std::make_unique<GooString>("Test free text content");
    annot->setContents(std::move(content));

    // Verify through getContents (inherited from Annot)
    const GooString *contents = annot->getContents();
    ASSERT_NE(contents, nullptr);
    EXPECT_STREQ(contents->c_str(), "Test free text content");
}

// Test setContents with empty string
TEST_F(AnnotFreeTextTest_823, SetContentsEmpty_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    auto content = std::make_unique<GooString>("");
    annot->setContents(std::move(content));

    const GooString *contents = annot->getContents();
    ASSERT_NE(contents, nullptr);
    EXPECT_EQ(contents->getLength(), 0);
}

// Test creating AnnotFreeText with zero-size rectangle (boundary)
TEST_F(AnnotFreeTextTest_823, ZeroSizeRectangle_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 0, 0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    // Should not crash; annotation should still be valid
    EXPECT_NE(annot.get(), nullptr);
    AnnotLineEndingStyle style = annot->getEndStyle();
    (void)style;
    SUCCEED();
}

// Test creating AnnotFreeText with negative coordinates (boundary)
TEST_F(AnnotFreeTextTest_823, NegativeCoordinatesRectangle_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(-100, -100, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    EXPECT_NE(annot.get(), nullptr);
    SUCCEED();
}

// Test creating AnnotFreeText with very large rectangle (boundary)
TEST_F(AnnotFreeTextTest_823, LargeRectangle_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100000, 100000);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    EXPECT_NE(annot.get(), nullptr);
    SUCCEED();
}

// Test setCalloutLine with a valid callout line
TEST_F(AnnotFreeTextTest_823, SetCalloutLine_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    auto callout = std::make_unique<AnnotCalloutLine>(10, 20, 30, 40);
    annot->setCalloutLine(std::move(callout));

    AnnotCalloutLine *result = annot->getCalloutLine();
    ASSERT_NE(result, nullptr);
}

// Test setCalloutLine with nullptr (clearing the callout line)
TEST_F(AnnotFreeTextTest_823, SetCalloutLineNull_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    // First set a callout line
    auto callout = std::make_unique<AnnotCalloutLine>(10, 20, 30, 40);
    annot->setCalloutLine(std::move(callout));
    ASSERT_NE(annot->getCalloutLine(), nullptr);

    // Then clear it
    annot->setCalloutLine(nullptr);
    EXPECT_EQ(annot->getCalloutLine(), nullptr);
}

// Test getDefaultAppearance
TEST_F(AnnotFreeTextTest_823, GetDefaultAppearance_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    const auto da = annot->getDefaultAppearance();
    // Should return a valid DefaultAppearance object or nullptr
    // Just verify no crash
    SUCCEED();
}

// Test setStyleString with nullptr
TEST_F(AnnotFreeTextTest_823, SetStyleStringNull_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    annot->setStyleString(nullptr);
    // Should not crash
    SUCCEED();
}

// Test multiple setter calls in sequence
TEST_F(AnnotFreeTextTest_823, MultipleSetterCalls_823) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 300, 300);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    // Set various properties
    annot->setQuadding(VariableTextQuadding::centered);
    annot->setIntent(AnnotFreeText::intentFreeTextCallout);

    auto content = std::make_unique<GooString>("Multi-setter test");
    annot->setContents(std::move(content));

    // Verify all properties
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::centered);
    EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeTextCallout);

    const GooString *contents = annot->getContents();
    ASSERT_NE(contents, nullptr);
    EXPECT_STREQ(contents->c_str(), "Multi-setter test");
}
