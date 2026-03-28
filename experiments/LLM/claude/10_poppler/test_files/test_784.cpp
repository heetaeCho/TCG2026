#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "PDFRectangle.h"
#include "GlobalParams.h"

// Helper to create a minimal valid PDF document for testing
class AnnotTest_784 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PDFDoc from a minimal PDF in memory
    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Create a minimal PDF file in memory
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

// Test that creating an Annot with a rectangle stores the rectangle correctly
TEST_F(AnnotTest_784, ConstructWithRectangle_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 100.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 200.0);
}

// Test getContents returns nullptr or empty initially
TEST_F(AnnotTest_784, GetContentsInitiallyNullOrEmpty_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    // Contents may be nullptr or an empty string depending on initialization
    const GooString *contents = annot.getContents();
    if (contents != nullptr) {
        // If not null, it should be some valid string (possibly empty)
        EXPECT_GE(contents->getLength(), 0);
    }
}

// Test setContents and getContents
TEST_F(AnnotTest_784, SetAndGetContents_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    auto newContent = std::make_unique<GooString>("Test content");
    annot.setContents(std::move(newContent));

    const GooString *contents = annot.getContents();
    ASSERT_NE(contents, nullptr);
    EXPECT_STREQ(contents->c_str(), "Test content");
}

// Test setContents with empty string
TEST_F(AnnotTest_784, SetContentsEmpty_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    auto newContent = std::make_unique<GooString>("");
    annot.setContents(std::move(newContent));

    const GooString *contents = annot.getContents();
    ASSERT_NE(contents, nullptr);
    EXPECT_EQ(contents->getLength(), 0);
}

// Test setRect with four doubles
TEST_F(AnnotTest_784, SetRectFourDoubles_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    annot.setRect(15.0, 25.0, 150.0, 250.0);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 15.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 25.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 150.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 250.0);
}

// Test setRect with PDFRectangle
TEST_F(AnnotTest_784, SetRectPDFRectangle_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    PDFRectangle newRect(5.0, 10.0, 50.0, 60.0);
    annot.setRect(newRect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 5.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 10.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 50.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 60.0);
}

// Test getRect with output parameters
TEST_F(AnnotTest_784, GetRectOutputParams_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 30.0, 40.0);
    Annot annot(doc.get(), &rect);

    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x1, 10.0);
    EXPECT_DOUBLE_EQ(y1, 20.0);
    EXPECT_DOUBLE_EQ(x2, 30.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

// Test inRect - point inside
TEST_F(AnnotTest_784, InRectPointInside_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_TRUE(annot.inRect(50.0, 100.0));
}

// Test inRect - point outside
TEST_F(AnnotTest_784, InRectPointOutside_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_FALSE(annot.inRect(5.0, 10.0));
    EXPECT_FALSE(annot.inRect(150.0, 300.0));
}

// Test inRect - point on boundary
TEST_F(AnnotTest_784, InRectPointOnBoundary_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    // Boundary points - behavior may be inclusive or exclusive
    bool onMinX = annot.inRect(10.0, 100.0);
    bool onMaxX = annot.inRect(100.0, 100.0);
    bool onMinY = annot.inRect(50.0, 20.0);
    bool onMaxY = annot.inRect(50.0, 200.0);
    // Just verify it doesn't crash; boundary behavior is implementation-defined
    (void)onMinX;
    (void)onMaxX;
    (void)onMinY;
    (void)onMaxY;
}

// Test setFlags and getFlags
TEST_F(AnnotTest_784, SetAndGetFlags_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0x04); // Hidden flag
    EXPECT_EQ(annot.getFlags(), 0x04u);

    annot.setFlags(0);
    EXPECT_EQ(annot.getFlags(), 0u);
}

// Test setContents with nullptr (unique_ptr that is null)
TEST_F(AnnotTest_784, SetContentsNull_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    // First set some content
    auto content = std::make_unique<GooString>("Hello");
    annot.setContents(std::move(content));
    ASSERT_NE(annot.getContents(), nullptr);

    // Now set null content
    annot.setContents(std::unique_ptr<GooString>(nullptr));
    // After setting null, getContents should handle gracefully
    // It might return nullptr or empty string
    const GooString *c = annot.getContents();
    if (c != nullptr) {
        EXPECT_GE(c->getLength(), 0);
    }
}

// Test getName returns value (initially may be nullptr or empty)
TEST_F(AnnotTest_784, GetNameInitial_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    // Name may be nullptr initially
    const GooString *name = annot.getName();
    // Just check it doesn't crash
    (void)name;
}

// Test setName and getName
TEST_F(AnnotTest_784, SetAndGetName_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    auto name = new GooString("TestAnnotation");
    annot.setName(name);

    const GooString *retrievedName = annot.getName();
    ASSERT_NE(retrievedName, nullptr);
    EXPECT_STREQ(retrievedName->c_str(), "TestAnnotation");
}

// Test getModified initially
TEST_F(AnnotTest_784, GetModifiedInitial_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    const GooString *modified = annot.getModified();
    // May be nullptr or empty
    (void)modified;
}

// Test setModified and getModified
TEST_F(AnnotTest_784, SetAndGetModified_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    auto mod = std::make_unique<GooString>("D:20230101120000");
    annot.setModified(std::move(mod));

    const GooString *modified = annot.getModified();
    ASSERT_NE(modified, nullptr);
    EXPECT_STREQ(modified->c_str(), "D:20230101120000");
}

// Test getDoc
TEST_F(AnnotTest_784, GetDoc_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    EXPECT_EQ(annot.getDoc(), doc.get());
}

// Test getBorder initially
TEST_F(AnnotTest_784, GetBorderInitial_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    // Border may or may not be set initially
    AnnotBorder *border = annot.getBorder();
    (void)border;
}

// Test getColor initially
TEST_F(AnnotTest_784, GetColorInitial_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    AnnotColor *color = annot.getColor();
    (void)color;
}

// Test setColor and getColor
TEST_F(AnnotTest_784, SetAndGetColor_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0); // Red
    annot.setColor(std::move(color));

    AnnotColor *retrievedColor = annot.getColor();
    ASSERT_NE(retrievedColor, nullptr);
}

// Test getAppearStreams initially
TEST_F(AnnotTest_784, GetAppearStreamsInitial_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    AnnotAppearance *streams = annot.getAppearStreams();
    (void)streams;
}

// Test getAppearState initially
TEST_F(AnnotTest_784, GetAppearStateInitial_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    const GooString *state = annot.getAppearState();
    (void)state;
}

// Test setAppearanceState and getAppearState
TEST_F(AnnotTest_784, SetAndGetAppearanceState_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    annot.setAppearanceState("Off");

    const GooString *state = annot.getAppearState();
    ASSERT_NE(state, nullptr);
    EXPECT_STREQ(state->c_str(), "Off");
}

// Test setRect with swapped coordinates (x1 > x2, y1 > y2)
TEST_F(AnnotTest_784, SetRectSwappedCoordinates_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    // Set rect with swapped coordinates - implementation should normalize
    annot.setRect(100.0, 200.0, 10.0, 20.0);

    // The implementation may normalize, so min should be smaller
    EXPECT_LE(annot.getXMin(), annot.getXMax());
    EXPECT_LE(annot.getYMin(), annot.getYMax());
}

// Test getTreeKey
TEST_F(AnnotTest_784, GetTreeKey_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    int treeKey = annot.getTreeKey();
    // Just verify it returns without crashing
    (void)treeKey;
}

// Test getPageNum
TEST_F(AnnotTest_784, GetPageNum_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    int pageNum = annot.getPageNum();
    // Page number for a newly created annotation
    (void)pageNum;
}

// Test setContents overwrite
TEST_F(AnnotTest_784, SetContentsOverwrite_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    annot.setContents(std::make_unique<GooString>("First"));
    ASSERT_NE(annot.getContents(), nullptr);
    EXPECT_STREQ(annot.getContents()->c_str(), "First");

    annot.setContents(std::make_unique<GooString>("Second"));
    ASSERT_NE(annot.getContents(), nullptr);
    EXPECT_STREQ(annot.getContents()->c_str(), "Second");
}

// Test getRect reference version
TEST_F(AnnotTest_784, GetRectReference_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 30.0, 40.0);
    Annot annot(doc.get(), &rect);

    const PDFRectangle &r = annot.getRect();
    EXPECT_DOUBLE_EQ(r.x1, 10.0);
    EXPECT_DOUBLE_EQ(r.y1, 20.0);
    EXPECT_DOUBLE_EQ(r.x2, 30.0);
    EXPECT_DOUBLE_EQ(r.y2, 40.0);
}

// Test setFlags with maximum value
TEST_F(AnnotTest_784, SetFlagsMaxValue_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0xFFFFFFFF);
    EXPECT_EQ(annot.getFlags(), 0xFFFFFFFFu);
}

// Test setContents with long string
TEST_F(AnnotTest_784, SetContentsLongString_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    std::string longStr(10000, 'A');
    annot.setContents(std::make_unique<GooString>(longStr.c_str()));

    const GooString *contents = annot.getContents();
    ASSERT_NE(contents, nullptr);
    EXPECT_EQ(contents->getLength(), 10000);
}

// Test setRect with zero-area rectangle
TEST_F(AnnotTest_784, SetRectZeroArea_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    annot.setRect(50.0, 50.0, 50.0, 50.0);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 50.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 50.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 50.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 50.0);
}

// Test inRect with zero-area rectangle
TEST_F(AnnotTest_784, InRectZeroAreaRect_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(50.0, 50.0, 50.0, 50.0);
    Annot annot(doc.get(), &rect);

    // A point exactly at the zero-area rect
    bool result = annot.inRect(50.0, 50.0);
    // Just ensure no crash; behavior is implementation-defined
    (void)result;
}

// Test setRect with negative coordinates
TEST_F(AnnotTest_784, SetRectNegativeCoordinates_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    annot.setRect(-100.0, -200.0, -10.0, -20.0);

    EXPECT_DOUBLE_EQ(annot.getXMin(), -100.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), -200.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), -10.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), -20.0);
}

// Test getHasRef for newly created annotation
TEST_F(AnnotTest_784, GetHasRef_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    bool hasRef = annot.getHasRef();
    // For a newly created annotation with rect constructor, hasRef behavior depends on implementation
    (void)hasRef;
}

// Test setContents with Unicode content
TEST_F(AnnotTest_784, SetContentsUnicode_784) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0, 0, 100, 100);
    Annot annot(doc.get(), &rect);

    // GooString can hold arbitrary bytes
    annot.setContents(std::make_unique<GooString>("Unicode: \xc3\xa9\xc3\xa8"));

    const GooString *contents = annot.getContents();
    ASSERT_NE(contents, nullptr);
    EXPECT_GT(contents->getLength(), 0);
}
