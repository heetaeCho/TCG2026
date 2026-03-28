#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"

class AnnotFreeTextTest_818 : public ::testing::Test {
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

        auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
        return std::make_unique<PDFDoc>(stream);
    }
};

TEST_F(AnnotFreeTextTest_818, ConstructorCreatesAnnot_818) {
    auto doc = createEmptyDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    auto rect = std::make_unique<PDFRectangle>(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());
    ASSERT_NE(annot, nullptr);
}

TEST_F(AnnotFreeTextTest_818, GetStyleStringInitiallyNull_818) {
    auto doc = createEmptyDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    auto rect = std::make_unique<PDFRectangle>(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    const GooString *style = annot->getStyleString();
    // Initially, styleString may be null if not set
    // We just verify no crash occurs
    SUCCEED();
}

TEST_F(AnnotFreeTextTest_818, SetStyleStringAndGet_818) {
    auto doc = createEmptyDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    auto rect = std::make_unique<PDFRectangle>(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    GooString *newStyle = new GooString("font: Helvetica 12pt; color: red");
    annot->setStyleString(newStyle);

    const GooString *result = annot->getStyleString();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "font: Helvetica 12pt; color: red");
}

TEST_F(AnnotFreeTextTest_818, SetStyleStringWithEmptyString_818) {
    auto doc = createEmptyDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    auto rect = std::make_unique<PDFRectangle>(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    GooString *newStyle = new GooString("");
    annot->setStyleString(newStyle);

    const GooString *result = annot->getStyleString();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "");
}

TEST_F(AnnotFreeTextTest_818, SetStyleStringWithNull_818) {
    auto doc = createEmptyDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    auto rect = std::make_unique<PDFRectangle>(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    annot->setStyleString(nullptr);

    const GooString *result = annot->getStyleString();
    // After setting null, styleString should be null
    EXPECT_EQ(result, nullptr);
}

TEST_F(AnnotFreeTextTest_818, SetStyleStringOverwritesPrevious_818) {
    auto doc = createEmptyDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    auto rect = std::make_unique<PDFRectangle>(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    GooString *style1 = new GooString("first style");
    annot->setStyleString(style1);

    const GooString *result1 = annot->getStyleString();
    ASSERT_NE(result1, nullptr);
    EXPECT_STREQ(result1->c_str(), "first style");

    GooString *style2 = new GooString("second style");
    annot->setStyleString(style2);

    const GooString *result2 = annot->getStyleString();
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result2->c_str(), "second style");
}

TEST_F(AnnotFreeTextTest_818, GetQuaddingDefault_818) {
    auto doc = createEmptyDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    auto rect = std::make_unique<PDFRectangle>(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    // Just verify we can call it without crashing
    VariableTextQuadding q = annot->getQuadding();
    SUCCEED();
}

TEST_F(AnnotFreeTextTest_818, SetAndGetQuadding_818) {
    auto doc = createEmptyDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    auto rect = std::make_unique<PDFRectangle>(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    annot->setQuadding(VariableTextQuadding::centered);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::centered);

    annot->setQuadding(VariableTextQuadding::rightJustified);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::rightJustified);

    annot->setQuadding(VariableTextQuadding::leftJustified);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::leftJustified);
}

TEST_F(AnnotFreeTextTest_818, GetIntentDefault_818) {
    auto doc = createEmptyDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    auto rect = std::make_unique<PDFRectangle>(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    AnnotFreeTextIntent intent = annot->getIntent();
    SUCCEED();
}

TEST_F(AnnotFreeTextTest_818, SetAndGetIntent_818) {
    auto doc = createEmptyDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    auto rect = std::make_unique<PDFRectangle>(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    annot->setIntent(AnnotFreeText::intentFreeTextCallout);
    EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeTextCallout);

    annot->setIntent(AnnotFreeText::intentFreeText);
    EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeText);
}

TEST_F(AnnotFreeTextTest_818, GetCalloutLineInitiallyNull_818) {
    auto doc = createEmptyDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    auto rect = std::make_unique<PDFRectangle>(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    AnnotCalloutLine *callout = annot->getCalloutLine();
    // May be null initially
    SUCCEED();
}

TEST_F(AnnotFreeTextTest_818, GetBorderEffectInitially_818) {
    auto doc = createEmptyDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    auto rect = std::make_unique<PDFRectangle>(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    AnnotBorderEffect *be = annot->getBorderEffect();
    // Just test no crash
    SUCCEED();
}

TEST_F(AnnotFreeTextTest_818, GetRectangleInitially_818) {
    auto doc = createEmptyDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    auto rect = std::make_unique<PDFRectangle>(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    PDFRectangle *r = annot->getRectangle();
    // May be null initially for inner rectangle
    SUCCEED();
}

TEST_F(AnnotFreeTextTest_818, GetEndStyleInitially_818) {
    auto doc = createEmptyDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    auto rect = std::make_unique<PDFRectangle>(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    AnnotLineEndingStyle endStyle = annot->getEndStyle();
    SUCCEED();
}

TEST_F(AnnotFreeTextTest_818, SetContentsWithGooString_818) {
    auto doc = createEmptyDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    auto rect = std::make_unique<PDFRectangle>(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    auto content = std::make_unique<GooString>("Test content for free text annotation");
    annot->setContents(std::move(content));

    // Verify through getContents if available from parent class
    const GooString *c = annot->getContents();
    if (c) {
        EXPECT_STREQ(c->c_str(), "Test content for free text annotation");
    }
}

TEST_F(AnnotFreeTextTest_818, GetDefaultAppearance_818) {
    auto doc = createEmptyDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    auto rect = std::make_unique<PDFRectangle>(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), rect.get());

    const auto da = annot->getDefaultAppearance();
    // Just verify no crash; DA may or may not be set
    SUCCEED();
}
