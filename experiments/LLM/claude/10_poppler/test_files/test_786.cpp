#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "Page.h"

class AnnotTest_786 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We'll create annotations using PDFDoc from a minimal PDF if available,
        // or use the rect-based constructor
    }

    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Create a minimal PDF in memory
        static const char pdfData[] =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R"
            "/Annots[4 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]"
            "/Contents(Test Annotation)/NM(TestName)/M(D:20230101000000)>>endobj\n"
            "xref\n0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000232 00000 n \n"
            "trailer<</Size 5/Root 1 0 R>>\nstartxref\n370\n%%EOF\n";

        Object obj;
        auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
        return std::make_unique<PDFDoc>(stream);
    }
};

// Test that getName returns the annotation name
TEST_F(AnnotTest_786, GetNameReturnsName_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    auto annots = page->getAnnots();
    if (!annots || annots->getNumAnnots() == 0) {
        GTEST_SKIP() << "No annotations found";
    }

    Annot *annot = annots->getAnnot(0);
    ASSERT_NE(annot, nullptr);

    const GooString *name = annot->getName();
    // Name may or may not be set depending on the PDF
    if (name) {
        EXPECT_FALSE(name->toStr().empty());
    }
}

// Test creating an Annot with a PDFRectangle
TEST_F(AnnotTest_786, CreateAnnotWithRect_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 300.0, 400.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_NEAR(annot->getXMin(), 10.0, 0.001);
    EXPECT_NEAR(annot->getYMin(), 20.0, 0.001);
    EXPECT_NEAR(annot->getXMax(), 300.0, 0.001);
    EXPECT_NEAR(annot->getYMax(), 400.0, 0.001);
}

// Test getRect method
TEST_F(AnnotTest_786, GetRectReturnsCorrectValues_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(15.0, 25.0, 350.0, 450.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);

    EXPECT_NEAR(x1, 15.0, 0.001);
    EXPECT_NEAR(y1, 25.0, 0.001);
    EXPECT_NEAR(x2, 350.0, 0.001);
    EXPECT_NEAR(y2, 450.0, 0.001);
}

// Test getRectReference
TEST_F(AnnotTest_786, GetRectReferenceReturnsCorrectValues_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    const PDFRectangle &r = annot->getRect();
    EXPECT_NEAR(r.x1, 10.0, 0.001);
    EXPECT_NEAR(r.y1, 20.0, 0.001);
    EXPECT_NEAR(r.x2, 100.0, 0.001);
    EXPECT_NEAR(r.y2, 200.0, 0.001);
}

// Test setRect with PDFRectangle
TEST_F(AnnotTest_786, SetRectWithPDFRectangle_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    PDFRectangle newRect(50.0, 60.0, 500.0, 600.0);
    annot->setRect(newRect);

    EXPECT_NEAR(annot->getXMin(), 50.0, 0.001);
    EXPECT_NEAR(annot->getYMin(), 60.0, 0.001);
    EXPECT_NEAR(annot->getXMax(), 500.0, 0.001);
    EXPECT_NEAR(annot->getYMax(), 600.0, 0.001);
}

// Test setRect with individual coordinates
TEST_F(AnnotTest_786, SetRectWithCoordinates_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setRect(70.0, 80.0, 700.0, 800.0);

    EXPECT_NEAR(annot->getXMin(), 70.0, 0.001);
    EXPECT_NEAR(annot->getYMin(), 80.0, 0.001);
    EXPECT_NEAR(annot->getXMax(), 700.0, 0.001);
    EXPECT_NEAR(annot->getYMax(), 800.0, 0.001);
}

// Test setContents and getContents
TEST_F(AnnotTest_786, SetAndGetContents_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    auto content = std::make_unique<GooString>("Hello World");
    annot->setContents(std::move(content));

    const GooString *retrieved = annot->getContents();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "Hello World");
}

// Test setContents with empty string
TEST_F(AnnotTest_786, SetContentsEmpty_786) {
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
        EXPECT_EQ(retrieved->toStr(), "");
    }
}

// Test setName and getName
TEST_F(AnnotTest_786, SetAndGetName_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    GooString *newName = new GooString("TestAnnotation");
    annot->setName(newName);

    const GooString *retrieved = annot->getName();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "TestAnnotation");
}

// Test setModified and getModified
TEST_F(AnnotTest_786, SetAndGetModified_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    auto mod = std::make_unique<GooString>("D:20230601120000");
    annot->setModified(std::move(mod));

    const GooString *retrieved = annot->getModified();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(retrieved->toStr(), "D:20230601120000");
}

// Test setFlags and getFlags
TEST_F(AnnotTest_786, SetAndGetFlags_786) {
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
TEST_F(AnnotTest_786, SetFlagsZero_786) {
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
TEST_F(AnnotTest_786, SetFlagsMaxValue_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setFlags(0xFFFFFFFF);
    EXPECT_EQ(annot->getFlags(), 0xFFFFFFFF);
}

// Test inRect - point inside rectangle
TEST_F(AnnotTest_786, InRectPointInside_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_TRUE(annot->inRect(50.0, 100.0));
}

// Test inRect - point outside rectangle
TEST_F(AnnotTest_786, InRectPointOutside_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_FALSE(annot->inRect(0.0, 0.0));
    EXPECT_FALSE(annot->inRect(200.0, 300.0));
}

// Test inRect - point on boundary
TEST_F(AnnotTest_786, InRectPointOnBoundary_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // Boundary behavior: on the edge should be in rect
    EXPECT_TRUE(annot->inRect(10.0, 20.0));
    EXPECT_TRUE(annot->inRect(100.0, 200.0));
    EXPECT_TRUE(annot->inRect(10.0, 200.0));
    EXPECT_TRUE(annot->inRect(100.0, 20.0));
}

// Test inRect - point just outside
TEST_F(AnnotTest_786, InRectPointJustOutside_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_FALSE(annot->inRect(9.99, 100.0));
    EXPECT_FALSE(annot->inRect(100.01, 100.0));
    EXPECT_FALSE(annot->inRect(50.0, 19.99));
    EXPECT_FALSE(annot->inRect(50.0, 200.01));
}

// Test getType returns valid type
TEST_F(AnnotTest_786, GetTypeReturnsValidType_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    AnnotSubtype type = annot->getType();
    // Just verify we can get the type without crashing
    (void)type;
}

// Test getDoc returns non-null
TEST_F(AnnotTest_786, GetDocReturnsNonNull_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_EQ(annot->getDoc(), doc.get());
}

// Test setColor and getColor
TEST_F(AnnotTest_786, SetAndGetColor_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0); // Red
    annot->setColor(std::move(color));

    const AnnotColor *retrieved = annot->getColor();
    ASSERT_NE(retrieved, nullptr);
}

// Test setColor with nullptr (no color)
TEST_F(AnnotTest_786, SetColorNull_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setColor(nullptr);
    const AnnotColor *retrieved = annot->getColor();
    EXPECT_EQ(retrieved, nullptr);
}

// Test initial contents may be null
TEST_F(AnnotTest_786, InitialContentsState_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // Contents may or may not be null initially
    // Just verify we don't crash
    const GooString *contents = annot->getContents();
    (void)contents;
}

// Test getAppearStreams
TEST_F(AnnotTest_786, GetAppearStreams_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // May be null for newly created annotation
    AnnotAppearance *streams = annot->getAppearStreams();
    (void)streams;
}

// Test getAppearState
TEST_F(AnnotTest_786, GetAppearState_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    const GooString *state = annot->getAppearState();
    (void)state;
}

// Test setAppearanceState
TEST_F(AnnotTest_786, SetAppearanceState_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setAppearanceState("Off");
    const GooString *state = annot->getAppearState();
    if (state) {
        EXPECT_EQ(state->toStr(), "Off");
    }
}

// Test getBorder
TEST_F(AnnotTest_786, GetBorder_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    AnnotBorder *border = annot->getBorder();
    (void)border;
}

// Test getTreeKey
TEST_F(AnnotTest_786, GetTreeKey_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    int treeKey = annot->getTreeKey();
    (void)treeKey;
}

// Test getId
TEST_F(AnnotTest_786, GetId_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    int id = annot->getId();
    (void)id;
}

// Test getPageNum
TEST_F(AnnotTest_786, GetPageNum_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    int pageNum = annot->getPageNum();
    // Newly created annotation may have page 0 or unset
    (void)pageNum;
}

// Test getHasRef
TEST_F(AnnotTest_786, GetHasRef_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    bool hasRef = annot->getHasRef();
    (void)hasRef;
}

// Test setRect normalizes coordinates (swapped coordinates)
TEST_F(AnnotTest_786, SetRectNormalizesCoordinates_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // Set with swapped coordinates
    annot->setRect(100.0, 200.0, 10.0, 20.0);

    // The implementation may normalize these
    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);

    // Either normalized or as-is, but should be consistent with getXMin/getXMax
    EXPECT_LE(annot->getXMin(), annot->getXMax());
    EXPECT_LE(annot->getYMin(), annot->getYMax());
}

// Test setContents replaces previous contents
TEST_F(AnnotTest_786, SetContentsReplacesExisting_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    auto content1 = std::make_unique<GooString>("First");
    annot->setContents(std::move(content1));
    ASSERT_NE(annot->getContents(), nullptr);
    EXPECT_EQ(annot->getContents()->toStr(), "First");

    auto content2 = std::make_unique<GooString>("Second");
    annot->setContents(std::move(content2));
    ASSERT_NE(annot->getContents(), nullptr);
    EXPECT_EQ(annot->getContents()->toStr(), "Second");
}

// Test setNewAppearance
TEST_F(AnnotTest_786, SetNewAppearance_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    Object newAppearance(objNull);
    annot->setNewAppearance(std::move(newAppearance));
    // Just verify no crash
}

// Test annotation from existing PDF has proper values
TEST_F(AnnotTest_786, AnnotFromExistingPDF_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    auto annots = page->getAnnots();
    if (!annots || annots->getNumAnnots() == 0) {
        GTEST_SKIP() << "No annotations found on page";
    }

    Annot *annot = annots->getAnnot(0);
    ASSERT_NE(annot, nullptr);

    // Check rect values from our test PDF
    EXPECT_NEAR(annot->getXMin(), 100.0, 0.5);
    EXPECT_NEAR(annot->getYMin(), 100.0, 0.5);
    EXPECT_NEAR(annot->getXMax(), 200.0, 0.5);
    EXPECT_NEAR(annot->getYMax(), 200.0, 0.5);

    // Check contents
    const GooString *contents = annot->getContents();
    if (contents) {
        EXPECT_EQ(contents->toStr(), "Test Annotation");
    }

    // Check type is Text
    EXPECT_EQ(annot->getType(), Annot::typeText);
}

// Test getAnnotObj returns valid object
TEST_F(AnnotTest_786, GetAnnotObj_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    const Object &obj = annot->getAnnotObj();
    // Should be a valid object
    (void)obj;
}

// Test multiple flag settings
TEST_F(AnnotTest_786, SetMultipleFlags_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // Set invisible + hidden + norotate flags
    unsigned int flags = 0x01 | 0x02 | 0x10;
    annot->setFlags(flags);
    EXPECT_EQ(annot->getFlags(), flags);
}

// Test isOk
TEST_F(AnnotTest_786, IsOk_786) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_TRUE(annot->isOk());
}
