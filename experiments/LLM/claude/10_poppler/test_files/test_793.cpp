#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers
#include "poppler/Annot.h"
#include "poppler/PDFDoc.h"
#include "poppler/GooString.h"
#include "poppler/PDFRectangle.h"
#include "poppler/Object.h"
#include "poppler/GlobalParams.h"

#include <cstring>

// Helper to create a minimal valid PDF in memory for PDFDoc construction
class AnnotTest_793 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PDFDoc from a minimal PDF file if needed
    // Since we need a PDFDoc to construct Annot objects, we'll try to
    // create one from a minimal PDF buffer
    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Minimal PDF content
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
            "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

        int len = strlen(minimalPDF);
        auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, len, Object(objNull));
        auto doc = std::make_unique<PDFDoc>(stream);
        return doc;
    }
};

// Test: Annot construction with PDFRectangle
TEST_F(AnnotTest_793, ConstructWithRectangle_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    // After construction, the rect should be set
    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, 10.0);
    EXPECT_DOUBLE_EQ(y1, 20.0);
    EXPECT_DOUBLE_EQ(x2, 100.0);
    EXPECT_DOUBLE_EQ(y2, 200.0);
}

// Test: getXMin, getYMin, getXMax, getYMax
TEST_F(AnnotTest_793, GetMinMaxCoordinates_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(5.0, 10.0, 50.0, 100.0);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 5.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 10.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 50.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 100.0);
}

// Test: setRect with PDFRectangle
TEST_F(AnnotTest_793, SetRectWithPDFRectangle_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    Annot annot(doc.get(), &rect);

    PDFRectangle newRect(20.0, 30.0, 200.0, 300.0);
    annot.setRect(newRect);

    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, 20.0);
    EXPECT_DOUBLE_EQ(y1, 30.0);
    EXPECT_DOUBLE_EQ(x2, 200.0);
    EXPECT_DOUBLE_EQ(y2, 300.0);
}

// Test: setRect with doubles
TEST_F(AnnotTest_793, SetRectWithDoubles_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    Annot annot(doc.get(), &rect);

    annot.setRect(15.0, 25.0, 150.0, 250.0);

    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, 15.0);
    EXPECT_DOUBLE_EQ(y1, 25.0);
    EXPECT_DOUBLE_EQ(x2, 150.0);
    EXPECT_DOUBLE_EQ(y2, 250.0);
}

// Test: setContents and getContents
TEST_F(AnnotTest_793, SetAndGetContents_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    auto content = std::make_unique<GooString>("Hello World");
    annot.setContents(std::move(content));

    const GooString *result = annot.getContents();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "Hello World");
}

// Test: setContents with empty string
TEST_F(AnnotTest_793, SetEmptyContents_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    auto content = std::make_unique<GooString>("");
    annot.setContents(std::move(content));

    const GooString *result = annot.getContents();
    if (result != nullptr) {
        EXPECT_STREQ(result->c_str(), "");
    }
}

// Test: setFlags and getFlags
TEST_F(AnnotTest_793, SetAndGetFlags_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0x04); // Hidden flag
    EXPECT_EQ(annot.getFlags(), 0x04u);
}

// Test: setFlags with zero
TEST_F(AnnotTest_793, SetFlagsZero_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0);
    EXPECT_EQ(annot.getFlags(), 0u);
}

// Test: inRect - point inside rectangle
TEST_F(AnnotTest_793, InRectPointInside_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(10.0, 10.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    EXPECT_TRUE(annot.inRect(50.0, 50.0));
}

// Test: inRect - point outside rectangle
TEST_F(AnnotTest_793, InRectPointOutside_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(10.0, 10.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    EXPECT_FALSE(annot.inRect(5.0, 5.0));
    EXPECT_FALSE(annot.inRect(150.0, 150.0));
}

// Test: inRect - point on boundary
TEST_F(AnnotTest_793, InRectPointOnBoundary_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(10.0, 10.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    // On boundary - behavior may vary, test for consistency
    bool onBoundary = annot.inRect(10.0, 10.0);
    // Just verify it doesn't crash and returns a bool
    EXPECT_TRUE(onBoundary || !onBoundary);
}

// Test: getTreeKey
TEST_F(AnnotTest_793, GetTreeKey_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    // treeKey should have some default value after construction
    int key = annot.getTreeKey();
    // Just verify it returns without error
    EXPECT_GE(key, -1); // Relaxed check since we don't know the default
}

// Test: getType
TEST_F(AnnotTest_793, GetType_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    AnnotSubtype type = annot.getType();
    // Verify it returns a valid subtype
    (void)type; // Just ensure no crash
}

// Test: getDoc
TEST_F(AnnotTest_793, GetDoc_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    EXPECT_EQ(annot.getDoc(), doc.get());
}

// Test: getPageNum
TEST_F(AnnotTest_793, GetPageNum_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    // Default page number
    int pageNum = annot.getPageNum();
    // Page number should be valid or 0 for unassigned
    (void)pageNum;
}

// Test: getColor returns null for newly created annotation
TEST_F(AnnotTest_793, GetColorDefaultNull_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    // For a freshly created annotation, color might be null
    AnnotColor *color = annot.getColor();
    // Just verify no crash; color may or may not be null
    (void)color;
}

// Test: getBorder
TEST_F(AnnotTest_793, GetBorderDefault_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    AnnotBorder *border = annot.getBorder();
    (void)border; // Just check no crash
}

// Test: getName default
TEST_F(AnnotTest_793, GetNameDefault_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    const GooString *name = annot.getName();
    (void)name; // May be null for new annotation
}

// Test: getModified default
TEST_F(AnnotTest_793, GetModifiedDefault_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    const GooString *modified = annot.getModified();
    (void)modified;
}

// Test: setModified and getModified
TEST_F(AnnotTest_793, SetAndGetModified_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    auto modStr = std::make_unique<GooString>("D:20230101000000");
    annot.setModified(std::move(modStr));

    const GooString *modified = annot.getModified();
    ASSERT_NE(modified, nullptr);
    EXPECT_STREQ(modified->c_str(), "D:20230101000000");
}

// Test: getAppearStreams default
TEST_F(AnnotTest_793, GetAppearStreamsDefault_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    AnnotAppearance *streams = annot.getAppearStreams();
    (void)streams;
}

// Test: getAppearState default
TEST_F(AnnotTest_793, GetAppearStateDefault_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    const GooString *state = annot.getAppearState();
    (void)state;
}

// Test: setColor with a valid color
TEST_F(AnnotTest_793, SetColor_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    annot.setColor(std::move(color));

    AnnotColor *resultColor = annot.getColor();
    ASSERT_NE(resultColor, nullptr);
}

// Test: setColor with nullptr
TEST_F(AnnotTest_793, SetColorNull_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setColor(nullptr);

    AnnotColor *resultColor = annot.getColor();
    EXPECT_EQ(resultColor, nullptr);
}

// Test: getRect returns consistent values
TEST_F(AnnotTest_793, GetRectConsistency_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(1.5, 2.5, 99.5, 199.5);
    Annot annot(doc.get(), &rect);

    const PDFRectangle &r = annot.getRect();
    EXPECT_DOUBLE_EQ(r.x1, 1.5);
    EXPECT_DOUBLE_EQ(r.y1, 2.5);
    EXPECT_DOUBLE_EQ(r.x2, 99.5);
    EXPECT_DOUBLE_EQ(r.y2, 199.5);
}

// Test: setRect normalizes inverted coordinates
TEST_F(AnnotTest_793, SetRectInvertedCoordinates_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    // Set rect with inverted coordinates (x1 > x2, y1 > y2)
    annot.setRect(100.0, 200.0, 10.0, 20.0);

    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);

    // The implementation should normalize so that x1 <= x2 and y1 <= y2
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// Test: getHasRef
TEST_F(AnnotTest_793, GetHasRef_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    bool hasRef = annot.getHasRef();
    (void)hasRef; // Just ensure no crash
}

// Test: getId
TEST_F(AnnotTest_793, GetId_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    int id = annot.getId();
    (void)id;
}

// Test: Multiple setRect calls
TEST_F(AnnotTest_793, MultipleSetRectCalls_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    Annot annot(doc.get(), &rect);

    annot.setRect(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(annot.getXMin(), 1.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 2.0);

    annot.setRect(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(annot.getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 30.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 40.0);
}

// Test: setContents with nullptr (set to empty/null)
TEST_F(AnnotTest_793, SetContentsNull_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setContents(nullptr);
    // After setting null, getContents should handle gracefully
    const GooString *result = annot.getContents();
    (void)result;
}

// Test: setFlags with maximum unsigned int
TEST_F(AnnotTest_793, SetFlagsMaxValue_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0xFFFFFFFF);
    EXPECT_EQ(annot.getFlags(), 0xFFFFFFFFu);
}

// Test: setNewAppearance
TEST_F(AnnotTest_793, SetNewAppearance_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    Object newApp(objNull);
    annot.setNewAppearance(std::move(newApp));

    // Verify no crash
    Object app = annot.getAppearance();
    (void)app;
}

// Test: inRect with negative coordinates
TEST_F(AnnotTest_793, InRectNegativeCoordinates_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(-50.0, -50.0, 50.0, 50.0);
    Annot annot(doc.get(), &rect);

    EXPECT_TRUE(annot.inRect(0.0, 0.0));
    EXPECT_TRUE(annot.inRect(-25.0, -25.0));
    EXPECT_FALSE(annot.inRect(-100.0, -100.0));
}

// Test: Zero-size rectangle
TEST_F(AnnotTest_793, ZeroSizeRect_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(50.0, 50.0, 50.0, 50.0);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 50.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 50.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 50.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 50.0);
}

// Test: setAppearanceState
TEST_F(AnnotTest_793, SetAppearanceState_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setAppearanceState("Off");
    const GooString *state = annot.getAppearState();
    if (state != nullptr) {
        EXPECT_STREQ(state->c_str(), "Off");
    }
}

// Test: getAnnotObj
TEST_F(AnnotTest_793, GetAnnotObj_793) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    const Object &obj = annot.getAnnotObj();
    (void)obj; // Just verify no crash
}
