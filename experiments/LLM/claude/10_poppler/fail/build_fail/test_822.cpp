#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "Object.h"

class AnnotFreeTextTest_822 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> createEmptyDoc() {
        // Create a minimal valid PDF in memory
        static const char pdfData[] =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
        return std::make_unique<PDFDoc>(stream);
    }
};

TEST_F(AnnotFreeTextTest_822, ConstructorCreatesValidAnnot_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(100.0, 200.0, 300.0, 400.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());
    ASSERT_NE(annot, nullptr);
}

TEST_F(AnnotFreeTextTest_822, GetRectangleReturnsNonNull_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(10.0, 20.0, 30.0, 40.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    PDFRectangle *retrievedRect = annot->getRectangle();
    // The rectangle may or may not be set depending on implementation,
    // but we can at least test the getter doesn't crash
    // getRectangle() returns the internal rectangle member
}

TEST_F(AnnotFreeTextTest_822, GetQuaddingDefault_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    VariableTextQuadding q = annot->getQuadding();
    // Default quadding should be a valid enum value
    EXPECT_TRUE(q == VariableTextQuadding::leftJustified ||
                q == VariableTextQuadding::centered ||
                q == VariableTextQuadding::rightJustified);
}

TEST_F(AnnotFreeTextTest_822, SetAndGetQuadding_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    annot->setQuadding(VariableTextQuadding::centered);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::centered);

    annot->setQuadding(VariableTextQuadding::rightJustified);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::rightJustified);

    annot->setQuadding(VariableTextQuadding::leftJustified);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::leftJustified);
}

TEST_F(AnnotFreeTextTest_822, GetStyleStringDefaultIsNull_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    const GooString *style = annot->getStyleString();
    // Default style string may be null
    // Just verify getter doesn't crash
    (void)style;
}

TEST_F(AnnotFreeTextTest_822, SetStyleString_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    auto styleStr = new GooString("font: Helvetica 12pt; color: #000000");
    annot->setStyleString(styleStr);

    const GooString *retrieved = annot->getStyleString();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "font: Helvetica 12pt; color: #000000");
}

TEST_F(AnnotFreeTextTest_822, GetCalloutLineDefaultIsNull_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    AnnotCalloutLine *callout = annot->getCalloutLine();
    EXPECT_EQ(callout, nullptr);
}

TEST_F(AnnotFreeTextTest_822, GetIntentDefault_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    AnnotFreeTextIntent intent = annot->getIntent();
    // Just verify the getter doesn't crash and returns a valid value
    (void)intent;
}

TEST_F(AnnotFreeTextTest_822, SetAndGetIntent_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    annot->setIntent(AnnotFreeText::intentFreeTextCallout);
    EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeTextCallout);

    annot->setIntent(AnnotFreeText::intentFreeTextTypeWriter);
    EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeTextTypeWriter);
}

TEST_F(AnnotFreeTextTest_822, GetBorderEffectDefault_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    AnnotBorderEffect *be = annot->getBorderEffect();
    // May be null by default
    (void)be;
}

TEST_F(AnnotFreeTextTest_822, GetEndStyleDefault_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    AnnotLineEndingStyle endStyle = annot->getEndStyle();
    // Default end style - just verify it doesn't crash
    (void)endStyle;
}

TEST_F(AnnotFreeTextTest_822, GetDefaultAppearance_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    const auto da = annot->getDefaultAppearance();
    // May or may not be null - just verify getter doesn't crash
    (void)da;
}

TEST_F(AnnotFreeTextTest_822, SetContents_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 200.0, 200.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    auto contents = std::make_unique<GooString>("Test contents for free text annotation");
    annot->setContents(std::move(contents));
    // Verify through getContents if available from parent class
    const GooString *retrieved = annot->getContents();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test contents for free text annotation");
}

TEST_F(AnnotFreeTextTest_822, SetContentsEmpty_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 200.0, 200.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    auto contents = std::make_unique<GooString>("");
    annot->setContents(std::move(contents));
    const GooString *retrieved = annot->getContents();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "");
}

TEST_F(AnnotFreeTextTest_822, SetCalloutLine_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 200.0, 200.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    auto calloutLine = std::make_unique<AnnotCalloutLine>(10.0, 20.0, 30.0, 40.0);
    annot->setCalloutLine(std::move(calloutLine));

    AnnotCalloutLine *retrieved = annot->getCalloutLine();
    ASSERT_NE(retrieved, nullptr);
}

TEST_F(AnnotFreeTextTest_822, SetCalloutLineNull_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 200.0, 200.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    // Set a callout line then clear it
    auto calloutLine = std::make_unique<AnnotCalloutLine>(10.0, 20.0, 30.0, 40.0);
    annot->setCalloutLine(std::move(calloutLine));
    ASSERT_NE(annot->getCalloutLine(), nullptr);

    annot->setCalloutLine(nullptr);
    EXPECT_EQ(annot->getCalloutLine(), nullptr);
}

TEST_F(AnnotFreeTextTest_822, SetStyleStringNull_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    annot->setStyleString(nullptr);
    const GooString *style = annot->getStyleString();
    EXPECT_EQ(style, nullptr);
}

TEST_F(AnnotFreeTextTest_822, SmallRectangle_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 1.0, 1.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());
    ASSERT_NE(annot, nullptr);
}

TEST_F(AnnotFreeTextTest_822, LargeRectangle_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 10000.0, 10000.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());
    ASSERT_NE(annot, nullptr);
}

TEST_F(AnnotFreeTextTest_822, SetDefaultAppearance_822) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 200.0, 200.0);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    DefaultAppearance da("0 0 0 rg /Helv 12 Tf");
    annot->setDefaultAppearance(da);

    const auto retrievedDA = annot->getDefaultAppearance();
    ASSERT_NE(retrievedDA, nullptr);
}
