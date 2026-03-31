#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "Object.h"
#include "PDFRectangle.h"
#include "GlobalParams.h"

// Helper to create a minimal valid PDF document for testing
class AnnotTest_791 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PDFDoc from a minimal PDF file if needed
    // We'll use a real minimal PDF for testing
    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Create a minimal PDF in memory
        static const char *minimalPDF =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, strlen(minimalPDF), Object(objNull));
        return std::make_unique<PDFDoc>(stream);
    }
};

// Test creating an Annot with a PDFRectangle
TEST_F(AnnotTest_791, CreateAnnotWithRect_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_TRUE(annot->isOk());
}

// Test getRect returns correct rectangle values
TEST_F(AnnotTest_791, GetRectReturnsCorrectValues_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x1, 10.0);
    EXPECT_DOUBLE_EQ(y1, 20.0);
    EXPECT_DOUBLE_EQ(x2, 100.0);
    EXPECT_DOUBLE_EQ(y2, 200.0);
}

// Test getXMin, getYMin, getXMax, getYMax
TEST_F(AnnotTest_791, GetMinMaxCoordinates_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot->getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(annot->getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(annot->getXMax(), 100.0);
    EXPECT_DOUBLE_EQ(annot->getYMax(), 200.0);
}

// Test setRect with PDFRectangle
TEST_F(AnnotTest_791, SetRectWithPDFRectangle_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    PDFRectangle newRect(30.0, 40.0, 300.0, 400.0);
    annot->setRect(newRect);

    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x1, 30.0);
    EXPECT_DOUBLE_EQ(y1, 40.0);
    EXPECT_DOUBLE_EQ(x2, 300.0);
    EXPECT_DOUBLE_EQ(y2, 400.0);
}

// Test setRect with individual coordinates
TEST_F(AnnotTest_791, SetRectWithCoordinates_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setRect(50.0, 60.0, 500.0, 600.0);

    EXPECT_DOUBLE_EQ(annot->getXMin(), 50.0);
    EXPECT_DOUBLE_EQ(annot->getYMin(), 60.0);
    EXPECT_DOUBLE_EQ(annot->getXMax(), 500.0);
    EXPECT_DOUBLE_EQ(annot->getYMax(), 600.0);
}

// Test inRect returns true for point inside rectangle
TEST_F(AnnotTest_791, InRectReturnsTrueForPointInside_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_TRUE(annot->inRect(50.0, 100.0));
}

// Test inRect returns false for point outside rectangle
TEST_F(AnnotTest_791, InRectReturnsFalseForPointOutside_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_FALSE(annot->inRect(0.0, 0.0));
    EXPECT_FALSE(annot->inRect(200.0, 300.0));
}

// Test inRect boundary - point on edge
TEST_F(AnnotTest_791, InRectBoundaryPoint_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // Points on the boundary
    EXPECT_TRUE(annot->inRect(10.0, 20.0));
    EXPECT_TRUE(annot->inRect(100.0, 200.0));
    EXPECT_TRUE(annot->inRect(10.0, 200.0));
    EXPECT_TRUE(annot->inRect(100.0, 20.0));
}

// Test setContents and getContents
TEST_F(AnnotTest_791, SetAndGetContents_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    auto content = std::make_unique<GooString>("Test Content");
    annot->setContents(std::move(content));

    const GooString *retrieved = annot->getContents();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test Content");
}

// Test setContents with empty string
TEST_F(AnnotTest_791, SetContentsEmpty_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    auto content = std::make_unique<GooString>("");
    annot->setContents(std::move(content));

    const GooString *retrieved = annot->getContents();
    if (retrieved) {
        EXPECT_STREQ(retrieved->c_str(), "");
    }
}

// Test setContents with nullptr
TEST_F(AnnotTest_791, SetContentsNull_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setContents(nullptr);
    // Should not crash; contents may be null or empty
}

// Test setFlags and getFlags
TEST_F(AnnotTest_791, SetAndGetFlags_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setFlags(0x04); // Hidden flag
    EXPECT_EQ(annot->getFlags(), 0x04u);
}

// Test setFlags with zero
TEST_F(AnnotTest_791, SetFlagsZero_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setFlags(0);
    EXPECT_EQ(annot->getFlags(), 0u);
}

// Test setFlags with max value
TEST_F(AnnotTest_791, SetFlagsMaxValue_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setFlags(0xFFFFFFFF);
    EXPECT_EQ(annot->getFlags(), 0xFFFFFFFFu);
}

// Test getBorder returns nullptr by default or valid border
TEST_F(AnnotTest_791, GetBorderDefault_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // Border may or may not be null depending on initialization
    // Just ensure it doesn't crash
    AnnotBorder *border = annot->getBorder();
    (void)border; // May be null
}

// Test getColor returns nullptr by default or valid color
TEST_F(AnnotTest_791, GetColorDefault_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    AnnotColor *color = annot->getColor();
    (void)color; // May be null
}

// Test setColor
TEST_F(AnnotTest_791, SetColor_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    auto newColor = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    annot->setColor(std::move(newColor));

    AnnotColor *color = annot->getColor();
    ASSERT_NE(color, nullptr);
}

// Test setColor with nullptr
TEST_F(AnnotTest_791, SetColorNull_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setColor(nullptr);
    EXPECT_EQ(annot->getColor(), nullptr);
}

// Test getDoc
TEST_F(AnnotTest_791, GetDocReturnsCorrectDoc_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_EQ(annot->getDoc(), doc.get());
}

// Test getType
TEST_F(AnnotTest_791, GetType_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // The type should be set to some valid AnnotSubtype
    AnnotSubtype type = annot->getType();
    (void)type; // Just ensure no crash
}

// Test setModified and getModified
TEST_F(AnnotTest_791, SetAndGetModified_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    auto modified = std::make_unique<GooString>("D:20230101120000");
    annot->setModified(std::move(modified));

    const GooString *retrieved = annot->getModified();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "D:20230101120000");
}

// Test getAppearStreams
TEST_F(AnnotTest_791, GetAppearStreams_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // May be null
    AnnotAppearance *streams = annot->getAppearStreams();
    (void)streams;
}

// Test getAppearState
TEST_F(AnnotTest_791, GetAppearState_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    const GooString *state = annot->getAppearState();
    (void)state; // May be null
}

// Test setAppearanceState
TEST_F(AnnotTest_791, SetAppearanceState_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setAppearanceState("Off");
    const GooString *state = annot->getAppearState();
    ASSERT_NE(state, nullptr);
    EXPECT_STREQ(state->c_str(), "Off");
}

// Test getTreeKey
TEST_F(AnnotTest_791, GetTreeKey_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    int key = annot->getTreeKey();
    (void)key;
}

// Test getPageNum
TEST_F(AnnotTest_791, GetPageNum_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    int pageNum = annot->getPageNum();
    (void)pageNum;
}

// Test getHasRef
TEST_F(AnnotTest_791, GetHasRef_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    bool hasRef = annot->getHasRef();
    (void)hasRef;
}

// Test getName
TEST_F(AnnotTest_791, GetNameDefault_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    const GooString *name = annot->getName();
    (void)name; // May be null
}

// Test setName
TEST_F(AnnotTest_791, SetName_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    GooString name("TestAnnotation");
    annot->setName(&name);

    const GooString *retrieved = annot->getName();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "TestAnnotation");
}

// Test setBorder with nullptr
TEST_F(AnnotTest_791, SetBorderNull_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setBorder(nullptr);
    EXPECT_EQ(annot->getBorder(), nullptr);
}

// Test getRect returns correct reference
TEST_F(AnnotTest_791, GetRectReference_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(15.0, 25.0, 150.0, 250.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    const PDFRectangle &retrievedRect = annot->getRect();
    EXPECT_DOUBLE_EQ(retrievedRect.x1, 15.0);
    EXPECT_DOUBLE_EQ(retrievedRect.y1, 25.0);
    EXPECT_DOUBLE_EQ(retrievedRect.x2, 150.0);
    EXPECT_DOUBLE_EQ(retrievedRect.y2, 250.0);
}

// Test setRect with swapped coordinates (x1 > x2, y1 > y2)
TEST_F(AnnotTest_791, SetRectSwappedCoordinates_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // Set rect with swapped coordinates
    annot->setRect(100.0, 200.0, 10.0, 20.0);

    // The implementation should normalize or handle this
    // Just check it doesn't crash
    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);
    // Normalized: x1 <= x2, y1 <= y2
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// Test getAppearanceResDict
TEST_F(AnnotTest_791, GetAppearanceResDict_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    Object resDict = annot->getAppearanceResDict();
    // May be null object
    (void)resDict;
}

// Test setNewAppearance
TEST_F(AnnotTest_791, SetNewAppearance_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    Object newAppearance(objNull);
    annot->setNewAppearance(std::move(newAppearance));
    // Should not crash
}

// Test multiple setContents calls
TEST_F(AnnotTest_791, MultipleSetContents_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setContents(std::make_unique<GooString>("First"));
    ASSERT_NE(annot->getContents(), nullptr);
    EXPECT_STREQ(annot->getContents()->c_str(), "First");

    annot->setContents(std::make_unique<GooString>("Second"));
    ASSERT_NE(annot->getContents(), nullptr);
    EXPECT_STREQ(annot->getContents()->c_str(), "Second");

    annot->setContents(std::make_unique<GooString>("Third"));
    ASSERT_NE(annot->getContents(), nullptr);
    EXPECT_STREQ(annot->getContents()->c_str(), "Third");
}

// Test getId
TEST_F(AnnotTest_791, GetId_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    int id = annot->getId();
    (void)id;
}

// Test getAnnotObj
TEST_F(AnnotTest_791, GetAnnotObj_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    const Object &obj = annot->getAnnotObj();
    (void)obj;
}

// Test inRect with negative coordinates
TEST_F(AnnotTest_791, InRectNegativeCoordinates_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(-100.0, -200.0, -10.0, -20.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_TRUE(annot->inRect(-50.0, -100.0));
    EXPECT_FALSE(annot->inRect(0.0, 0.0));
}

// Test setRect with zero-sized rectangle
TEST_F(AnnotTest_791, SetRectZeroSize_791) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setRect(50.0, 50.0, 50.0, 50.0);

    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, x2);
    EXPECT_DOUBLE_EQ(y1, y2);
}
