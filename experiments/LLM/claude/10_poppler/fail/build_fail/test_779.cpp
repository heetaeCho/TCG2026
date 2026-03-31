#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "Object.h"
#include "PDFRectangle.h"
#include "GlobalParams.h"

// Helper to create a minimal valid PDFDoc for testing
class AnnotTest_779 : public ::testing::Test {
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
        // Create a minimal PDF in memory
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

// Test creating an Annot with a PDFRectangle
TEST_F(AnnotTest_779, ConstructWithRect_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_TRUE(annot.isOk());
}

// Test getRect returns the rectangle set during construction
TEST_F(AnnotTest_779, GetRectReturnsCorrectValues_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x1, 10.0);
    EXPECT_DOUBLE_EQ(y1, 20.0);
    EXPECT_DOUBLE_EQ(x2, 100.0);
    EXPECT_DOUBLE_EQ(y2, 200.0);
}

// Test getXMin, getYMin, getXMax, getYMax
TEST_F(AnnotTest_779, GetMinMaxCoordinates_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(15.0, 25.0, 150.0, 250.0);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 15.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 25.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 150.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 250.0);
}

// Test setRect with PDFRectangle
TEST_F(AnnotTest_779, SetRectWithPDFRectangle_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    PDFRectangle newRect(50.0, 60.0, 500.0, 600.0);
    annot.setRect(newRect);

    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x1, 50.0);
    EXPECT_DOUBLE_EQ(y1, 60.0);
    EXPECT_DOUBLE_EQ(x2, 500.0);
    EXPECT_DOUBLE_EQ(y2, 600.0);
}

// Test setRect with individual coordinates
TEST_F(AnnotTest_779, SetRectWithCoordinates_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setRect(30.0, 40.0, 300.0, 400.0);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 30.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 40.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 300.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 400.0);
}

// Test inRect with point inside rectangle
TEST_F(AnnotTest_779, InRectPointInside_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_TRUE(annot.inRect(50.0, 100.0));
}

// Test inRect with point outside rectangle
TEST_F(AnnotTest_779, InRectPointOutside_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_FALSE(annot.inRect(5.0, 10.0));
    EXPECT_FALSE(annot.inRect(150.0, 300.0));
}

// Test inRect with point on boundary
TEST_F(AnnotTest_779, InRectPointOnBoundary_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    // Points on the boundary - behavior may vary
    bool onLeftEdge = annot.inRect(10.0, 100.0);
    bool onRightEdge = annot.inRect(100.0, 100.0);
    bool onTopEdge = annot.inRect(50.0, 200.0);
    bool onBottomEdge = annot.inRect(50.0, 20.0);

    // Just checking these don't crash; boundary behavior is implementation-defined
    (void)onLeftEdge;
    (void)onRightEdge;
    (void)onTopEdge;
    (void)onBottomEdge;
}

// Test setContents and getContents
TEST_F(AnnotTest_779, SetAndGetContents_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    auto content = std::make_unique<GooString>("Test Content");
    annot.setContents(std::move(content));

    const GooString *retrieved = annot.getContents();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test Content");
}

// Test setContents with empty string
TEST_F(AnnotTest_779, SetEmptyContents_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    auto content = std::make_unique<GooString>("");
    annot.setContents(std::move(content));

    const GooString *retrieved = annot.getContents();
    if (retrieved) {
        EXPECT_STREQ(retrieved->c_str(), "");
    }
}

// Test setFlags and getFlags
TEST_F(AnnotTest_779, SetAndGetFlags_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0x04); // Hidden flag
    EXPECT_EQ(annot.getFlags(), 0x04u);
}

// Test setFlags with zero
TEST_F(AnnotTest_779, SetFlagsZero_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0);
    EXPECT_EQ(annot.getFlags(), 0u);
}

// Test getHasRef for annotation created with rect (no ref)
TEST_F(AnnotTest_779, GetHasRefNoRef_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    // When created without an object reference, hasRef should be false
    EXPECT_FALSE(annot.getHasRef());
}

// Test getDoc returns the same doc
TEST_F(AnnotTest_779, GetDocReturnsSameDoc_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_EQ(annot.getDoc(), doc.get());
}

// Test getContents initially returns nullptr or empty
TEST_F(AnnotTest_779, GetContentsInitially_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    // Contents may be nullptr or empty initially
    const GooString *contents = annot.getContents();
    // Just verify it doesn't crash
    (void)contents;
}

// Test setModified and getModified
TEST_F(AnnotTest_779, SetAndGetModified_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    auto modified = std::make_unique<GooString>("D:20230101120000");
    annot.setModified(std::move(modified));

    const GooString *retrieved = annot.getModified();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "D:20230101120000");
}

// Test setColor and getColor
TEST_F(AnnotTest_779, SetAndGetColor_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    // Set color to nullptr
    annot.setColor(nullptr);
    EXPECT_EQ(annot.getColor(), nullptr);
}

// Test setColor with a valid AnnotColor
TEST_F(AnnotTest_779, SetValidColor_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0); // Red
    AnnotColor *colorPtr = color.get();
    annot.setColor(std::move(color));

    EXPECT_NE(annot.getColor(), nullptr);
}

// Test setBorder and getBorder
TEST_F(AnnotTest_779, SetNullBorder_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setBorder(nullptr);
    EXPECT_EQ(annot.getBorder(), nullptr);
}

// Test getType returns valid subtype
TEST_F(AnnotTest_779, GetTypeReturnsValidSubtype_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    AnnotSubtype type = annot.getType();
    // Just verify it doesn't crash and returns something
    (void)type;
}

// Test setRect normalizes coordinates (swapped min/max)
TEST_F(AnnotTest_779, SetRectSwappedCoordinates_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    // Set rect with swapped coordinates
    annot.setRect(100.0, 200.0, 10.0, 20.0);

    // After normalization, xMin should be <= xMax, yMin <= yMax
    EXPECT_LE(annot.getXMin(), annot.getXMax());
    EXPECT_LE(annot.getYMin(), annot.getYMax());
}

// Test getAppearance
TEST_F(AnnotTest_779, GetAppearance_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    Object appearance = annot.getAppearance();
    // Just verify it doesn't crash
    (void)appearance;
}

// Test setNewAppearance
TEST_F(AnnotTest_779, SetNewAppearance_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    Object newAppearance(objNull);
    annot.setNewAppearance(std::move(newAppearance));
    // Just verify it doesn't crash
}

// Test getAppearanceResDict
TEST_F(AnnotTest_779, GetAppearanceResDict_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    Object resDict = annot.getAppearanceResDict();
    // Just verify it doesn't crash
    (void)resDict;
}

// Test getPageNum
TEST_F(AnnotTest_779, GetPageNum_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    int pageNum = annot.getPageNum();
    // For a newly created annotation, page may be 0 or unset
    (void)pageNum;
}

// Test getTreeKey
TEST_F(AnnotTest_779, GetTreeKey_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    int treeKey = annot.getTreeKey();
    // Just verify it doesn't crash
    (void)treeKey;
}

// Test getId
TEST_F(AnnotTest_779, GetId_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    int id = annot.getId();
    // Just verify it returns something and doesn't crash
    (void)id;
}

// Test getAnnotObj
TEST_F(AnnotTest_779, GetAnnotObj_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    const Object &annotObj = annot.getAnnotObj();
    // Just verify the reference is valid and doesn't crash
    (void)annotObj;
}

// Test setContents with nullptr (unique_ptr)
TEST_F(AnnotTest_779, SetNullContents_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setContents(nullptr);
    // Should handle null gracefully
    const GooString *contents = annot.getContents();
    (void)contents;
}

// Test setContents replaces previous contents
TEST_F(AnnotTest_779, SetContentsReplace_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    auto content1 = std::make_unique<GooString>("First");
    annot.setContents(std::move(content1));

    auto content2 = std::make_unique<GooString>("Second");
    annot.setContents(std::move(content2));

    const GooString *retrieved = annot.getContents();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Second");
}

// Test setRect and then inRect consistency
TEST_F(AnnotTest_779, SetRectThenInRect_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0.0, 0.0, 50.0, 50.0);
    Annot annot(doc.get(), &rect);

    annot.setRect(100.0, 100.0, 200.0, 200.0);

    // Point that was inside old rect should be outside new rect
    EXPECT_FALSE(annot.inRect(25.0, 25.0));

    // Point inside new rect
    EXPECT_TRUE(annot.inRect(150.0, 150.0));
}

// Test setFlags with multiple flag bits
TEST_F(AnnotTest_779, SetMultipleFlags_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    unsigned int combinedFlags = 0x04 | 0x08 | 0x10; // Hidden | NoZoom | NoRotate
    annot.setFlags(combinedFlags);
    EXPECT_EQ(annot.getFlags(), combinedFlags);
}

// Test getRect returns const reference
TEST_F(AnnotTest_779, GetRectConstRef_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    const PDFRectangle &rectRef = annot.getRect();
    EXPECT_DOUBLE_EQ(rectRef.x1, 10.0);
    EXPECT_DOUBLE_EQ(rectRef.y1, 20.0);
    EXPECT_DOUBLE_EQ(rectRef.x2, 100.0);
    EXPECT_DOUBLE_EQ(rectRef.y2, 200.0);
}

// Test zero-area rectangle
TEST_F(AnnotTest_779, ZeroAreaRect_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(50.0, 50.0, 50.0, 50.0);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), annot.getXMax());
    EXPECT_DOUBLE_EQ(annot.getYMin(), annot.getYMax());
}

// Test setAppearanceState
TEST_F(AnnotTest_779, SetAppearanceState_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setAppearanceState("Off");
    const GooString *state = annot.getAppearState();
    if (state) {
        EXPECT_STREQ(state->c_str(), "Off");
    }
}

// Test getAppearStreams initially
TEST_F(AnnotTest_779, GetAppearStreamsInitially_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    AnnotAppearance *streams = annot.getAppearStreams();
    // May be nullptr for a newly created annotation
    (void)streams;
}

// Test large coordinate values
TEST_F(AnnotTest_779, LargeCoordinateValues_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(0.0, 0.0, 100000.0, 100000.0);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 100000.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 100000.0);

    EXPECT_TRUE(annot.inRect(50000.0, 50000.0));
}

// Test negative coordinate values
TEST_F(AnnotTest_779, NegativeCoordinateValues_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(-100.0, -200.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), -100.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), -200.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 100.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 200.0);

    EXPECT_TRUE(annot.inRect(0.0, 0.0));
    EXPECT_FALSE(annot.inRect(-150.0, 0.0));
}

// Test getName initially
TEST_F(AnnotTest_779, GetNameInitially_779) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF doc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    const GooString *name = annot.getName();
    // May be nullptr for newly created annotation
    (void)name;
}
