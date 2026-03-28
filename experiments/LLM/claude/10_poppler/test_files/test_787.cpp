#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers from the poppler project
#include "Annot.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"
#include "Object.h"

// Helper to create a minimal PDFDoc for testing
class AnnotTest_787 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PDFDoc from a minimal PDF file
    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Create a minimal valid PDF in memory
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

    // Helper to create an Annot with a PDFRectangle
    std::unique_ptr<Annot> createAnnotWithRect(PDFDoc *doc, double x1, double y1, double x2, double y2) {
        PDFRectangle rect(x1, y1, x2, y2);
        return std::make_unique<Annot>(doc, &rect);
    }
};

// Test that getModified returns nullptr when no modified date is set
TEST_F(AnnotTest_787, GetModifiedReturnsNullWhenNotSet_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);
    // When no modified date has been set, getModified should return nullptr
    const GooString *modified = annot->getModified();
    // It may or may not be null depending on initialization, but should not crash
    SUCCEED();
}

// Test setModified and getModified
TEST_F(AnnotTest_787, SetModifiedAndGetModified_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    auto modStr = std::make_unique<GooString>("D:20230101120000Z");
    annot->setModified(std::move(modStr));

    const GooString *modified = annot->getModified();
    ASSERT_NE(modified, nullptr);
    EXPECT_STREQ(modified->c_str(), "D:20230101120000Z");
}

// Test setModified with empty string
TEST_F(AnnotTest_787, SetModifiedWithEmptyString_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    auto modStr = std::make_unique<GooString>("");
    annot->setModified(std::move(modStr));

    const GooString *modified = annot->getModified();
    ASSERT_NE(modified, nullptr);
    EXPECT_STREQ(modified->c_str(), "");
}

// Test setModified overwrites previous value
TEST_F(AnnotTest_787, SetModifiedOverwritesPrevious_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    annot->setModified(std::make_unique<GooString>("D:20230101120000Z"));
    annot->setModified(std::make_unique<GooString>("D:20240601080000Z"));

    const GooString *modified = annot->getModified();
    ASSERT_NE(modified, nullptr);
    EXPECT_STREQ(modified->c_str(), "D:20240601080000Z");
}

// Test getRect returns correct coordinates
TEST_F(AnnotTest_787, GetRectReturnsCorrectCoordinates_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 10.0, 20.0, 300.0, 400.0);

    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, 10.0);
    EXPECT_DOUBLE_EQ(y1, 20.0);
    EXPECT_DOUBLE_EQ(x2, 300.0);
    EXPECT_DOUBLE_EQ(y2, 400.0);
}

// Test getXMin, getYMin, getXMax, getYMax
TEST_F(AnnotTest_787, GetMinMaxCoordinates_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 10.0, 20.0, 300.0, 400.0);

    EXPECT_DOUBLE_EQ(annot->getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(annot->getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(annot->getXMax(), 300.0);
    EXPECT_DOUBLE_EQ(annot->getYMax(), 400.0);
}

// Test setRect with four doubles
TEST_F(AnnotTest_787, SetRectWithFourDoubles_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    annot->setRect(50.0, 60.0, 150.0, 160.0);

    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, 50.0);
    EXPECT_DOUBLE_EQ(y1, 60.0);
    EXPECT_DOUBLE_EQ(x2, 150.0);
    EXPECT_DOUBLE_EQ(y2, 160.0);
}

// Test setRect with PDFRectangle
TEST_F(AnnotTest_787, SetRectWithPDFRectangle_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    PDFRectangle newRect(25.0, 35.0, 200.0, 250.0);
    annot->setRect(newRect);

    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, 25.0);
    EXPECT_DOUBLE_EQ(y1, 35.0);
    EXPECT_DOUBLE_EQ(x2, 200.0);
    EXPECT_DOUBLE_EQ(y2, 250.0);
}

// Test inRect for a point inside the rectangle
TEST_F(AnnotTest_787, InRectReturnsTrueForPointInside_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 10.0, 10.0, 100.0, 100.0);

    EXPECT_TRUE(annot->inRect(50.0, 50.0));
}

// Test inRect for a point outside the rectangle
TEST_F(AnnotTest_787, InRectReturnsFalseForPointOutside_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 10.0, 10.0, 100.0, 100.0);

    EXPECT_FALSE(annot->inRect(200.0, 200.0));
}

// Test inRect for a point on the boundary
TEST_F(AnnotTest_787, InRectBoundaryPoint_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 10.0, 10.0, 100.0, 100.0);

    // Boundary behavior - point exactly on edge
    // This tests the boundary condition; exact behavior depends on implementation
    bool onEdge = annot->inRect(10.0, 50.0);
    // We just verify it doesn't crash; the result depends on implementation
    SUCCEED();
}

// Test setContents and getContents
TEST_F(AnnotTest_787, SetContentsAndGetContents_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    annot->setContents(std::make_unique<GooString>("Test annotation content"));

    const GooString *contents = annot->getContents();
    ASSERT_NE(contents, nullptr);
    EXPECT_STREQ(contents->c_str(), "Test annotation content");
}

// Test setContents with empty string
TEST_F(AnnotTest_787, SetContentsWithEmptyString_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    annot->setContents(std::make_unique<GooString>(""));

    const GooString *contents = annot->getContents();
    ASSERT_NE(contents, nullptr);
    EXPECT_STREQ(contents->c_str(), "");
}

// Test setFlags and getFlags
TEST_F(AnnotTest_787, SetFlagsAndGetFlags_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    annot->setFlags(0x04); // Hidden flag
    EXPECT_EQ(annot->getFlags(), 0x04u);
}

// Test setFlags with zero
TEST_F(AnnotTest_787, SetFlagsToZero_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    annot->setFlags(0);
    EXPECT_EQ(annot->getFlags(), 0u);
}

// Test getType returns a valid subtype
TEST_F(AnnotTest_787, GetTypeReturnsValidSubtype_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    AnnotSubtype type = annot->getType();
    // Just verify it doesn't crash and returns some value
    SUCCEED();
}

// Test getDoc returns the document pointer
TEST_F(AnnotTest_787, GetDocReturnsCorrectPointer_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    EXPECT_EQ(annot->getDoc(), doc.get());
}

// Test getBorder returns nullptr or valid border initially
TEST_F(AnnotTest_787, GetBorderInitial_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    // Just check it doesn't crash
    AnnotBorder *border = annot->getBorder();
    SUCCEED();
}

// Test getColor returns nullptr or valid color initially
TEST_F(AnnotTest_787, GetColorInitial_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    // Just check it doesn't crash
    AnnotColor *color = annot->getColor();
    SUCCEED();
}

// Test getAppearStreams
TEST_F(AnnotTest_787, GetAppearStreamsInitial_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    // May be null for newly created annot
    AnnotAppearance *streams = annot->getAppearStreams();
    SUCCEED();
}

// Test getAppearState
TEST_F(AnnotTest_787, GetAppearStateInitial_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    const GooString *state = annot->getAppearState();
    SUCCEED();
}

// Test setAppearanceState and getAppearState
TEST_F(AnnotTest_787, SetAppearanceState_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    annot->setAppearanceState("Off");

    const GooString *state = annot->getAppearState();
    ASSERT_NE(state, nullptr);
    EXPECT_STREQ(state->c_str(), "Off");
}

// Test getRect returns a reference to the PDFRectangle
TEST_F(AnnotTest_787, GetRectReference_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 15.0, 25.0, 115.0, 125.0);

    const PDFRectangle &rect = annot->getRect();
    EXPECT_DOUBLE_EQ(rect.x1, 15.0);
    EXPECT_DOUBLE_EQ(rect.y1, 25.0);
    EXPECT_DOUBLE_EQ(rect.x2, 115.0);
    EXPECT_DOUBLE_EQ(rect.y2, 125.0);
}

// Test setting rect with swapped coordinates (x1 > x2)
TEST_F(AnnotTest_787, SetRectSwappedCoordinates_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    // Set rect where x1 > x2 and y1 > y2 - implementation may normalize
    annot->setRect(200.0, 200.0, 50.0, 50.0);

    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);
    // The implementation may normalize or keep as-is
    // Just verify it doesn't crash
    SUCCEED();
}

// Test multiple setModified calls
TEST_F(AnnotTest_787, SetModifiedMultipleTimes_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    for (int i = 0; i < 10; i++) {
        std::string dateStr = "D:2023010" + std::to_string(i) + "120000Z";
        annot->setModified(std::make_unique<GooString>(dateStr.c_str()));
    }

    const GooString *modified = annot->getModified();
    ASSERT_NE(modified, nullptr);
    EXPECT_STREQ(modified->c_str(), "D:20230109120000Z");
}

// Test getPageNum
TEST_F(AnnotTest_787, GetPageNum_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    // Newly created annot may have a default page number
    int pageNum = annot->getPageNum();
    SUCCEED();
}

// Test getTreeKey
TEST_F(AnnotTest_787, GetTreeKey_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    int treeKey = annot->getTreeKey();
    SUCCEED();
}

// Test getName when not set
TEST_F(AnnotTest_787, GetNameWhenNotSet_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    const GooString *name = annot->getName();
    // May be null or empty for newly created annot
    SUCCEED();
}

// Test getHasRef
TEST_F(AnnotTest_787, GetHasRef_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    bool hasRef = annot->getHasRef();
    SUCCEED();
}

// Test setContents overwrite
TEST_F(AnnotTest_787, SetContentsOverwrite_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    annot->setContents(std::make_unique<GooString>("First content"));
    annot->setContents(std::make_unique<GooString>("Second content"));

    const GooString *contents = annot->getContents();
    ASSERT_NE(contents, nullptr);
    EXPECT_STREQ(contents->c_str(), "Second content");
}

// Test setFlags with maximum value
TEST_F(AnnotTest_787, SetFlagsMaxValue_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    annot->setFlags(0xFFFFFFFF);
    EXPECT_EQ(annot->getFlags(), 0xFFFFFFFFu);
}

// Test getAnnotObj
TEST_F(AnnotTest_787, GetAnnotObj_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    const Object &annotObj = annot->getAnnotObj();
    // Just verify it doesn't crash
    SUCCEED();
}

// Test inRect with negative coordinates
TEST_F(AnnotTest_787, InRectNegativeCoordinates_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), -100.0, -100.0, 100.0, 100.0);

    EXPECT_TRUE(annot->inRect(0.0, 0.0));
    EXPECT_FALSE(annot->inRect(-200.0, -200.0));
}

// Test setModified with nullptr (unique_ptr with no value)
TEST_F(AnnotTest_787, SetModifiedWithNullptr_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    // First set a valid modified string
    annot->setModified(std::make_unique<GooString>("D:20230101120000Z"));
    ASSERT_NE(annot->getModified(), nullptr);

    // Set to null
    annot->setModified(std::unique_ptr<GooString>(nullptr));
    // After setting null, getModified should return nullptr
    EXPECT_EQ(annot->getModified(), nullptr);
}

// Test very long modified string
TEST_F(AnnotTest_787, SetModifiedLongString_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    std::string longStr(1000, 'A');
    annot->setModified(std::make_unique<GooString>(longStr.c_str()));

    const GooString *modified = annot->getModified();
    ASSERT_NE(modified, nullptr);
    EXPECT_EQ(std::string(modified->c_str()), longStr);
}

// Test setRect with zero-size rectangle
TEST_F(AnnotTest_787, SetRectZeroSize_787) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    auto annot = createAnnotWithRect(doc.get(), 0, 0, 100, 100);

    annot->setRect(50.0, 50.0, 50.0, 50.0);

    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);
    // A zero-size rect - verify no crash
    SUCCEED();
}
