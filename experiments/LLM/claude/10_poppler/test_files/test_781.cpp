#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

// Include necessary headers from the poppler project
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "PDFDocFactory.h"
#include "GooString.h"

class AnnotTest_781 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override
    {
        // We need a valid PDFDoc to create annotations.
        // We'll try to create a minimal one or use a test file if available.
    }

    void TearDown() override
    {
    }

    // Helper to create a PDFDoc from a minimal PDF in memory
    std::unique_ptr<PDFDoc> createMinimalPDFDoc()
    {
        // Create a minimal PDF file in /tmp for testing
        static const char *minimalPDF =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
            "endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n"
            "<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";

        FILE *f = fopen("/tmp/test_annot_781.pdf", "w");
        if (f) {
            fwrite(minimalPDF, 1, strlen(minimalPDF), f);
            fclose(f);
        }

        auto *fileName = new GooString("/tmp/test_annot_781.pdf");
        auto doc = std::make_unique<PDFDoc>(fileName);
        return doc;
    }
};

// Test creating an annotation with a PDFRectangle
TEST_F(AnnotTest_781, ConstructWithRectangle_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 100.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 200.0);
}

// Test getRect method
TEST_F(AnnotTest_781, GetRect_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(5.0, 10.0, 50.0, 100.0);
    Annot annot(doc.get(), &rect);

    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x1, 5.0);
    EXPECT_DOUBLE_EQ(y1, 10.0);
    EXPECT_DOUBLE_EQ(x2, 50.0);
    EXPECT_DOUBLE_EQ(y2, 100.0);
}

// Test getRectReference
TEST_F(AnnotTest_781, GetRectReference_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);
    Annot annot(doc.get(), &rect);

    const PDFRectangle &r = annot.getRect();
    EXPECT_DOUBLE_EQ(r.x1, 1.0);
    EXPECT_DOUBLE_EQ(r.y1, 2.0);
    EXPECT_DOUBLE_EQ(r.x2, 3.0);
    EXPECT_DOUBLE_EQ(r.y2, 4.0);
}

// Test setRect with PDFRectangle
TEST_F(AnnotTest_781, SetRectWithPDFRectangle_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    Annot annot(doc.get(), &rect);

    PDFRectangle newRect(20.0, 30.0, 200.0, 300.0);
    annot.setRect(newRect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 20.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 30.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 200.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 300.0);
}

// Test setRect with coordinates
TEST_F(AnnotTest_781, SetRectWithCoordinates_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    Annot annot(doc.get(), &rect);

    annot.setRect(15.0, 25.0, 150.0, 250.0);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 15.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 25.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 150.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 250.0);
}

// Test setRect normalizes when x1 > x2 or y1 > y2
TEST_F(AnnotTest_781, SetRectNormalization_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    Annot annot(doc.get(), &rect);

    // Set rect with inverted coordinates
    annot.setRect(100.0, 200.0, 10.0, 20.0);

    // Expect normalized coordinates
    EXPECT_LE(annot.getXMin(), annot.getXMax());
    EXPECT_LE(annot.getYMin(), annot.getYMax());
}

// Test inRect returns true for point inside
TEST_F(AnnotTest_781, InRectInsidePoint_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_TRUE(annot.inRect(50.0, 100.0));
}

// Test inRect returns false for point outside
TEST_F(AnnotTest_781, InRectOutsidePoint_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_FALSE(annot.inRect(0.0, 0.0));
    EXPECT_FALSE(annot.inRect(200.0, 300.0));
    EXPECT_FALSE(annot.inRect(5.0, 100.0));
    EXPECT_FALSE(annot.inRect(50.0, 5.0));
}

// Test inRect boundary points
TEST_F(AnnotTest_781, InRectBoundaryPoints_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    // Test exact boundary corners
    // Behavior at boundary may be implementation-defined, just verify no crash
    bool atCorner = annot.inRect(10.0, 20.0);
    bool atOppositeCorner = annot.inRect(100.0, 200.0);
    // We don't assert specific values since boundary behavior is implementation-defined
    (void)atCorner;
    (void)atOppositeCorner;
}

// Test setContents and getContents
TEST_F(AnnotTest_781, SetAndGetContents_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    auto content = std::make_unique<GooString>("Test Content");
    annot.setContents(std::move(content));

    const GooString *retrieved = annot.getContents();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test Content");
}

// Test setContents with empty string
TEST_F(AnnotTest_781, SetEmptyContents_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    auto content = std::make_unique<GooString>("");
    annot.setContents(std::move(content));

    const GooString *retrieved = annot.getContents();
    // Either nullptr or empty string
    if (retrieved != nullptr) {
        EXPECT_EQ(retrieved->getLength(), 0);
    }
}

// Test setContents with nullptr
TEST_F(AnnotTest_781, SetNullContents_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setContents(nullptr);

    // Should not crash, contents may be nullptr or empty
    const GooString *retrieved = annot.getContents();
    (void)retrieved; // Just ensure no crash
}

// Test getFlags and setFlags
TEST_F(AnnotTest_781, SetAndGetFlags_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0x04); // Hidden flag
    EXPECT_EQ(annot.getFlags(), 0x04u);

    annot.setFlags(0);
    EXPECT_EQ(annot.getFlags(), 0u);

    annot.setFlags(0xFFFF);
    EXPECT_EQ(annot.getFlags(), 0xFFFFu);
}

// Test setModified and getModified
TEST_F(AnnotTest_781, SetAndGetModified_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    auto mod = std::make_unique<GooString>("D:20230101120000");
    annot.setModified(std::move(mod));

    const GooString *retrieved = annot.getModified();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "D:20230101120000");
}

// Test getAnnotObj returns a valid Object
TEST_F(AnnotTest_781, GetAnnotObj_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    const Object &obj = annot.getAnnotObj();
    // The annotation object should be a dictionary
    EXPECT_TRUE(obj.isDict());
}

// Test getDoc returns non-null
TEST_F(AnnotTest_781, GetDoc_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    EXPECT_EQ(annot.getDoc(), doc.get());
}

// Test initial contents is null or empty
TEST_F(AnnotTest_781, InitialContentsEmpty_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    const GooString *contents = annot.getContents();
    // Initial contents should be null or empty
    if (contents != nullptr) {
        EXPECT_EQ(contents->getLength(), 0);
    }
}

// Test getAppearance
TEST_F(AnnotTest_781, GetAppearance_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    Object appearance = annot.getAppearance();
    // Appearance may be null for a newly created annotation
    // Just verify no crash
    (void)appearance;
}

// Test getAppearStreams for new annotation
TEST_F(AnnotTest_781, GetAppearStreams_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    AnnotAppearance *streams = annot.getAppearStreams();
    // May be null for newly created annotation
    (void)streams;
}

// Test getBorder for new annotation
TEST_F(AnnotTest_781, GetBorder_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    AnnotBorder *border = annot.getBorder();
    // Border may or may not be null; just verify no crash
    (void)border;
}

// Test getColor for new annotation
TEST_F(AnnotTest_781, GetColor_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    AnnotColor *color = annot.getColor();
    // Color may or may not be null; just verify no crash
    (void)color;
}

// Test setColor
TEST_F(AnnotTest_781, SetColor_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    annot.setColor(std::move(color));

    AnnotColor *retrieved = annot.getColor();
    ASSERT_NE(retrieved, nullptr);
}

// Test setNewAppearance
TEST_F(AnnotTest_781, SetNewAppearance_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    Object newAppearance;
    annot.setNewAppearance(std::move(newAppearance));
    // Just verify no crash
}

// Test getPageNum
TEST_F(AnnotTest_781, GetPageNum_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    int pageNum = annot.getPageNum();
    // New annotation may have page 0 or -1
    (void)pageNum;
}

// Test getType
TEST_F(AnnotTest_781, GetType_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    AnnotSubtype type = annot.getType();
    // Just verify it returns some valid subtype
    (void)type;
}

// Test getTreeKey
TEST_F(AnnotTest_781, GetTreeKey_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    int treeKey = annot.getTreeKey();
    (void)treeKey;
}

// Test getName for new annotation
TEST_F(AnnotTest_781, GetName_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    const GooString *name = annot.getName();
    // May be null
    (void)name;
}

// Test setName
TEST_F(AnnotTest_781, SetName_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    GooString *name = new GooString("TestAnnotation");
    annot.setName(name);

    const GooString *retrieved = annot.getName();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "TestAnnotation");
}

// Test getAppearState for new annotation
TEST_F(AnnotTest_781, GetAppearState_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    const GooString *state = annot.getAppearState();
    // May be null for new annotation
    (void)state;
}

// Test setAppearanceState
TEST_F(AnnotTest_781, SetAppearanceState_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setAppearanceState("N");

    const GooString *state = annot.getAppearState();
    ASSERT_NE(state, nullptr);
    EXPECT_STREQ(state->c_str(), "N");
}

// Test getHasRef
TEST_F(AnnotTest_781, GetHasRef_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    bool hasRef = annot.getHasRef();
    // For a newly created annotation without explicit ref, this may be false
    (void)hasRef;
}

// Test getAppearanceResDict for new annotation
TEST_F(AnnotTest_781, GetAppearanceResDict_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    Object resDict = annot.getAppearanceResDict();
    // May be null for new annotation
    (void)resDict;
}

// Test rect with zero dimensions
TEST_F(AnnotTest_781, ZeroDimensionRect_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(50.0, 50.0, 50.0, 50.0);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 50.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 50.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 50.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 50.0);
}

// Test rect with negative coordinates
TEST_F(AnnotTest_781, NegativeCoordinateRect_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(-100.0, -200.0, -10.0, -20.0);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), -100.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), -200.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), -10.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), -20.0);
}

// Test multiple setContents calls
TEST_F(AnnotTest_781, MultipleSetContents_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setContents(std::make_unique<GooString>("First"));
    ASSERT_NE(annot.getContents(), nullptr);
    EXPECT_STREQ(annot.getContents()->c_str(), "First");

    annot.setContents(std::make_unique<GooString>("Second"));
    ASSERT_NE(annot.getContents(), nullptr);
    EXPECT_STREQ(annot.getContents()->c_str(), "Second");

    annot.setContents(std::make_unique<GooString>("Third"));
    ASSERT_NE(annot.getContents(), nullptr);
    EXPECT_STREQ(annot.getContents()->c_str(), "Third");
}

// Test large rect values
TEST_F(AnnotTest_781, LargeRectValues_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 1e10, 1e10);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 1e10);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 1e10);
}

// Test setFlags with various flag combinations
TEST_F(AnnotTest_781, SetFlagsCombinations_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    // Test individual flags
    annot.setFlags(1u); // Invisible
    EXPECT_EQ(annot.getFlags(), 1u);

    annot.setFlags(2u); // Hidden
    EXPECT_EQ(annot.getFlags(), 2u);

    annot.setFlags(4u); // Print
    EXPECT_EQ(annot.getFlags(), 4u);

    // Combined flags
    annot.setFlags(1u | 4u);
    EXPECT_EQ(annot.getFlags(), 5u);
}

// Test setColor to null
TEST_F(AnnotTest_781, SetColorNull_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setColor(nullptr);
    // Should not crash
    AnnotColor *color = annot.getColor();
    EXPECT_EQ(color, nullptr);
}

// Test setBorder to null
TEST_F(AnnotTest_781, SetBorderNull_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setBorder(nullptr);
    // Should not crash
    AnnotBorder *border = annot.getBorder();
    EXPECT_EQ(border, nullptr);
}

// Test isOk
TEST_F(AnnotTest_781, IsOk_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    EXPECT_TRUE(annot.isOk());
}

// Test setContents with unicode content
TEST_F(AnnotTest_781, SetUnicodeContents_781)
{
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    auto content = std::make_unique<GooString>("Hello World \xc3\xa9\xc3\xa0");
    annot.setContents(std::move(content));

    const GooString *retrieved = annot.getContents();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_GT(retrieved->getLength(), 0);
}
