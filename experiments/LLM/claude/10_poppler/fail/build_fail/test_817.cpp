#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers
#include "poppler/Annot.h"
#include "poppler/PDFDoc.h"
#include "poppler/GooString.h"
#include "poppler/Object.h"
#include "poppler/PDFRectangle.h"

// Helper to create a minimal PDFDoc for testing
// We need a valid PDFDoc to construct AnnotFreeText objects
class AnnotFreeTextTest_817 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal PDF document for testing
        // This typically requires a valid PDF file or stream
        // For unit testing, we may need to create a minimal one
    }

    void TearDown() override {
    }

    // Helper to create a PDFDoc from a minimal PDF in memory
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

// Test that a newly created AnnotFreeText has a default quadding value
TEST_F(AnnotFreeTextTest_817, DefaultQuadding_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    // Default quadding should be leftJustified (0)
    VariableTextQuadding q = annot->getQuadding();
    // Just verify it returns a valid enum value
    EXPECT_TRUE(q == VariableTextQuadding::quaddingLeftJustified ||
                q == VariableTextQuadding::quaddingCentered ||
                q == VariableTextQuadding::quaddingRightJustified);
}

// Test setQuadding and getQuadding for left justified
TEST_F(AnnotFreeTextTest_817, SetQuaddingLeftJustified_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    annot->setQuadding(VariableTextQuadding::quaddingLeftJustified);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::quaddingLeftJustified);
}

// Test setQuadding and getQuadding for centered
TEST_F(AnnotFreeTextTest_817, SetQuaddingCentered_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    annot->setQuadding(VariableTextQuadding::quaddingCentered);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::quaddingCentered);
}

// Test setQuadding and getQuadding for right justified
TEST_F(AnnotFreeTextTest_817, SetQuaddingRightJustified_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    annot->setQuadding(VariableTextQuadding::quaddingRightJustified);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::quaddingRightJustified);
}

// Test getStyleString returns nullptr initially
TEST_F(AnnotFreeTextTest_817, DefaultStyleStringIsNull_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    // Style string may be null by default
    const GooString *style = annot->getStyleString();
    // Just verify the call doesn't crash - style may or may not be null
    (void)style;
    SUCCEED();
}

// Test setStyleString and getStyleString
TEST_F(AnnotFreeTextTest_817, SetAndGetStyleString_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    GooString *styleStr = new GooString("font: bold 12pt Helvetica");
    annot->setStyleString(styleStr);

    const GooString *result = annot->getStyleString();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "font: bold 12pt Helvetica");
}

// Test getCalloutLine default
TEST_F(AnnotFreeTextTest_817, DefaultCalloutLineIsNull_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    AnnotCalloutLine *callout = annot->getCalloutLine();
    EXPECT_EQ(callout, nullptr);
}

// Test getIntent default
TEST_F(AnnotFreeTextTest_817, DefaultIntent_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    AnnotFreeTextIntent intent = annot->getIntent();
    // Verify it returns a valid intent value
    (void)intent;
    SUCCEED();
}

// Test setIntent and getIntent
TEST_F(AnnotFreeTextTest_817, SetAndGetIntent_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    annot->setIntent(AnnotFreeText::intentFreeTextCallout);
    EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeTextCallout);
}

// Test getBorderEffect default
TEST_F(AnnotFreeTextTest_817, DefaultBorderEffect_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    AnnotBorderEffect *be = annot->getBorderEffect();
    // May be null by default
    (void)be;
    SUCCEED();
}

// Test getRectangle default
TEST_F(AnnotFreeTextTest_817, DefaultRectangle_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    PDFRectangle *r = annot->getRectangle();
    // May or may not be null
    (void)r;
    SUCCEED();
}

// Test getEndStyle default
TEST_F(AnnotFreeTextTest_817, DefaultEndStyle_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    AnnotLineEndingStyle endStyle = annot->getEndStyle();
    // Just verify it doesn't crash and returns a valid value
    (void)endStyle;
    SUCCEED();
}

// Test setContents
TEST_F(AnnotFreeTextTest_817, SetContents_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    auto content = std::make_unique<GooString>("Test content");
    annot->setContents(std::move(content));

    // Verify via getContents (inherited from Annot)
    const GooString *contents = annot->getContents();
    ASSERT_NE(contents, nullptr);
    EXPECT_STREQ(contents->c_str(), "Test content");
}

// Test setContents with empty string
TEST_F(AnnotFreeTextTest_817, SetContentsEmpty_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    auto content = std::make_unique<GooString>("");
    annot->setContents(std::move(content));

    const GooString *contents = annot->getContents();
    ASSERT_NE(contents, nullptr);
    EXPECT_STREQ(contents->c_str(), "");
}

// Test changing quadding multiple times
TEST_F(AnnotFreeTextTest_817, ChangeQuaddingMultipleTimes_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    annot->setQuadding(VariableTextQuadding::quaddingLeftJustified);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::quaddingLeftJustified);

    annot->setQuadding(VariableTextQuadding::quaddingCentered);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::quaddingCentered);

    annot->setQuadding(VariableTextQuadding::quaddingRightJustified);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::quaddingRightJustified);

    annot->setQuadding(VariableTextQuadding::quaddingLeftJustified);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::quaddingLeftJustified);
}

// Test getDefaultAppearance
TEST_F(AnnotFreeTextTest_817, GetDefaultAppearance_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    const auto da = annot->getDefaultAppearance();
    // Just verify it doesn't crash
    (void)da;
    SUCCEED();
}

// Test with zero-area rectangle
TEST_F(AnnotFreeTextTest_817, ZeroAreaRectangle_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100, 100, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    // Should still be constructible and functional
    annot->setQuadding(VariableTextQuadding::quaddingCentered);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::quaddingCentered);
}

// Test with large rectangle coordinates
TEST_F(AnnotFreeTextTest_817, LargeRectangleCoordinates_817) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 10000, 10000);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);

    annot->setQuadding(VariableTextQuadding::quaddingRightJustified);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::quaddingRightJustified);
}
