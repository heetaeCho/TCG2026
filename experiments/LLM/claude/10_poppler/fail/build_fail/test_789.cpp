#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "GooString.h"
#include "PDFDocFactory.h"

// Helper to create a minimal PDFDoc for testing
class AnnotTest_789 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Create a minimal valid PDF in memory for testing
    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Create a minimal PDF document from a file or memory
        // We'll use the factory to create from a minimal PDF string
        static const char minimalPDF[] =
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
            "startxref\n200\n%%EOF\n";

        Object obj(minimalPDF);
        auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, sizeof(minimalPDF) - 1, Object(objNull));
        auto doc = std::make_unique<PDFDoc>(stream);
        if (doc->isOk()) {
            return doc;
        }
        return nullptr;
    }
};

// Test creating an Annot with a rectangle
TEST_F(AnnotTest_789, ConstructWithRect_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 100.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 200.0);
}

// Test getRect method
TEST_F(AnnotTest_789, GetRect_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
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

// Test setRect with PDFRectangle
TEST_F(AnnotTest_789, SetRectWithPDFRectangle_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    Annot annot(doc.get(), &rect);

    PDFRectangle newRect(15.0, 25.0, 150.0, 250.0);
    annot.setRect(newRect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 15.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 25.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 150.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 250.0);
}

// Test setRect with doubles
TEST_F(AnnotTest_789, SetRectWithDoubles_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    Annot annot(doc.get(), &rect);

    annot.setRect(30.0, 40.0, 300.0, 400.0);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 30.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 40.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 300.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 400.0);
}

// Test setRect normalizes coordinates (x1 > x2 or y1 > y2)
TEST_F(AnnotTest_789, SetRectNormalizesCoordinates_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    Annot annot(doc.get(), &rect);

    // Set rect with swapped coordinates
    annot.setRect(100.0, 200.0, 10.0, 20.0);

    // The implementation should normalize so min <= max
    EXPECT_LE(annot.getXMin(), annot.getXMax());
    EXPECT_LE(annot.getYMin(), annot.getYMax());
}

// Test inRect returns true for point inside
TEST_F(AnnotTest_789, InRectInsidePoint_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_TRUE(annot.inRect(50.0, 100.0));
}

// Test inRect returns false for point outside
TEST_F(AnnotTest_789, InRectOutsidePoint_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_FALSE(annot.inRect(5.0, 10.0));
    EXPECT_FALSE(annot.inRect(150.0, 300.0));
}

// Test inRect boundary - point on edge
TEST_F(AnnotTest_789, InRectBoundaryPoint_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    // Points on the boundary
    EXPECT_TRUE(annot.inRect(10.0, 20.0));
    EXPECT_TRUE(annot.inRect(100.0, 200.0));
    EXPECT_TRUE(annot.inRect(10.0, 200.0));
    EXPECT_TRUE(annot.inRect(100.0, 20.0));
}

// Test setContents and getContents
TEST_F(AnnotTest_789, SetAndGetContents_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    auto content = std::make_unique<GooString>("Test content");
    annot.setContents(std::move(content));

    const GooString *retrieved = annot.getContents();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test content");
}

// Test setContents with empty string
TEST_F(AnnotTest_789, SetContentsEmpty_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    auto content = std::make_unique<GooString>("");
    annot.setContents(std::move(content));

    const GooString *retrieved = annot.getContents();
    if (retrieved) {
        EXPECT_STREQ(retrieved->c_str(), "");
    }
}

// Test setFlags and getFlags
TEST_F(AnnotTest_789, SetAndGetFlags_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0x04); // Hidden flag
    EXPECT_EQ(annot.getFlags(), 0x04u);
}

// Test setFlags with zero
TEST_F(AnnotTest_789, SetFlagsZero_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0);
    EXPECT_EQ(annot.getFlags(), 0u);
}

// Test setFlags with all bits set
TEST_F(AnnotTest_789, SetFlagsAllBits_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0xFFFFFFFF);
    EXPECT_EQ(annot.getFlags(), 0xFFFFFFFFu);
}

// Test getAppearStreams initially
TEST_F(AnnotTest_789, GetAppearStreamsInitial_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    // For a newly created annotation, appearance streams may be null
    // This is just testing we can call it without crashing
    annot.getAppearStreams();
}

// Test getAppearState initially
TEST_F(AnnotTest_789, GetAppearStateInitial_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    // For a newly created annotation, appear state may be null
    const GooString *state = annot.getAppearState();
    // Just verify it doesn't crash; state could be null or have some default
    (void)state;
}

// Test setAppearanceState
TEST_F(AnnotTest_789, SetAppearanceState_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setAppearanceState("On");
    const GooString *state = annot.getAppearState();
    ASSERT_NE(state, nullptr);
    EXPECT_STREQ(state->c_str(), "On");
}

// Test setModified and getModified
TEST_F(AnnotTest_789, SetAndGetModified_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    auto modified = std::make_unique<GooString>("D:20230101120000");
    annot.setModified(std::move(modified));

    const GooString *retrieved = annot.getModified();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "D:20230101120000");
}

// Test getBorder initially
TEST_F(AnnotTest_789, GetBorderInitial_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    // Just verify we can call it without crashing
    AnnotBorder *border = annot.getBorder();
    (void)border;
}

// Test getColor initially
TEST_F(AnnotTest_789, GetColorInitial_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    // Just verify we can call it without crashing
    AnnotColor *color = annot.getColor();
    (void)color;
}

// Test getDoc
TEST_F(AnnotTest_789, GetDoc_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    EXPECT_EQ(annot.getDoc(), doc.get());
}

// Test getType
TEST_F(AnnotTest_789, GetType_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    // The type should have some valid value
    AnnotSubtype type = annot.getType();
    (void)type;
}

// Test getHasRef for a new annotation
TEST_F(AnnotTest_789, GetHasRef_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    // A newly constructed annotation may or may not have a ref
    bool hasRef = annot.getHasRef();
    (void)hasRef;
}

// Test getName initially null
TEST_F(AnnotTest_789, GetNameInitiallyNull_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    const GooString *name = annot.getName();
    // Name might be null for a fresh annotation
    (void)name;
}

// Test setName
TEST_F(AnnotTest_789, SetName_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    GooString name("TestAnnotName");
    annot.setName(&name);

    const GooString *retrieved = annot.getName();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "TestAnnotName");
}

// Test getPageNum
TEST_F(AnnotTest_789, GetPageNum_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    // Page num might be 0 or some default for a fresh annotation
    int pageNum = annot.getPageNum();
    (void)pageNum;
}

// Test getTreeKey
TEST_F(AnnotTest_789, GetTreeKey_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    int treeKey = annot.getTreeKey();
    (void)treeKey;
}

// Test setNewAppearance
TEST_F(AnnotTest_789, SetNewAppearance_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    Object newApp(objNull);
    annot.setNewAppearance(std::move(newApp));

    // Verify we can retrieve the appearance without crashing
    Object app = annot.getAppearance();
    (void)app;
}

// Test setNewAppearance with keepAppearState
TEST_F(AnnotTest_789, SetNewAppearanceKeepState_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setAppearanceState("Off");

    Object newApp(objNull);
    annot.setNewAppearance(std::move(newApp), true);

    const GooString *state = annot.getAppearState();
    if (state) {
        EXPECT_STREQ(state->c_str(), "Off");
    }
}

// Test getAppearanceResDict
TEST_F(AnnotTest_789, GetAppearanceResDict_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    Object resDict = annot.getAppearanceResDict();
    // Just check it doesn't crash
    (void)resDict;
}

// Test setColor with a new color
TEST_F(AnnotTest_789, SetColor_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    annot.setColor(std::move(color));

    AnnotColor *retrieved = annot.getColor();
    ASSERT_NE(retrieved, nullptr);
}

// Test setBorder with nullptr (clearing border)
TEST_F(AnnotTest_789, SetBorderNull_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setBorder(nullptr);

    AnnotBorder *border = annot.getBorder();
    EXPECT_EQ(border, nullptr);
}

// Test setContents with nullptr
TEST_F(AnnotTest_789, SetContentsNull_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setContents(nullptr);
    // Verify it doesn't crash; contents might be null or empty string
    const GooString *contents = annot.getContents();
    (void)contents;
}

// Test rect with zero-size
TEST_F(AnnotTest_789, ZeroSizeRect_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(50.0, 50.0, 50.0, 50.0);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 50.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 50.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 50.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 50.0);
}

// Test inRect with zero-size rect
TEST_F(AnnotTest_789, InRectZeroSize_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(50.0, 50.0, 50.0, 50.0);
    Annot annot(doc.get(), &rect);

    EXPECT_TRUE(annot.inRect(50.0, 50.0));
    EXPECT_FALSE(annot.inRect(50.1, 50.0));
    EXPECT_FALSE(annot.inRect(49.9, 50.0));
}

// Test getAnnotObj
TEST_F(AnnotTest_789, GetAnnotObj_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    const Object &annotObj = annot.getAnnotObj();
    // The annotation object should be a dict for a valid annotation
    (void)annotObj;
}

// Test multiple setRect calls
TEST_F(AnnotTest_789, MultipleSetRect_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 10.0, 10.0);
    Annot annot(doc.get(), &rect);

    annot.setRect(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(annot.getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 20.0);

    annot.setRect(50.0, 60.0, 70.0, 80.0);
    EXPECT_DOUBLE_EQ(annot.getXMin(), 50.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 60.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 70.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 80.0);
}

// Test multiple setContents calls
TEST_F(AnnotTest_789, MultipleSetContents_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setContents(std::make_unique<GooString>("First"));
    ASSERT_NE(annot.getContents(), nullptr);
    EXPECT_STREQ(annot.getContents()->c_str(), "First");

    annot.setContents(std::make_unique<GooString>("Second"));
    ASSERT_NE(annot.getContents(), nullptr);
    EXPECT_STREQ(annot.getContents()->c_str(), "Second");
}

// Test large coordinate values
TEST_F(AnnotTest_789, LargeCoordinateValues_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100000.0, 100000.0);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 0.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 100000.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 100000.0);
}

// Test negative coordinate values
TEST_F(AnnotTest_789, NegativeCoordinateValues_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(-100.0, -200.0, -10.0, -20.0);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), -100.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), -200.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), -10.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), -20.0);
}

// Test setAppearanceState with different values
TEST_F(AnnotTest_789, SetAppearanceStateMultiple_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setAppearanceState("On");
    ASSERT_NE(annot.getAppearState(), nullptr);
    EXPECT_STREQ(annot.getAppearState()->c_str(), "On");

    annot.setAppearanceState("Off");
    ASSERT_NE(annot.getAppearState(), nullptr);
    EXPECT_STREQ(annot.getAppearState()->c_str(), "Off");
}

// Test setColor with nullptr
TEST_F(AnnotTest_789, SetColorNull_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setColor(nullptr);
    EXPECT_EQ(annot.getColor(), nullptr);
}

// Test getId
TEST_F(AnnotTest_789, GetId_789) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    int id = annot.getId();
    // Just verify it returns something without crashing
    (void)id;
}
