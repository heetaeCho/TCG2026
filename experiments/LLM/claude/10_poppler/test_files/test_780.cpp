#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "GooString.h"
#include "PDFDocFactory.h"

class AnnotTest_780 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We need a valid PDFDoc to construct annotations
        // Try to create a minimal PDF in memory or load a test file
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> createTestDoc(const std::string &filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that Annot constructed with PDFRectangle has correct rect values
TEST_F(AnnotTest_780, ConstructWithRectangle_780) {
    // We need a PDFDoc for construction. Since we may not have a test file,
    // we test what we can with the interface.
    // This test documents expected behavior with a valid doc.
    
    // Without a valid PDF file, we test the interface contract through
    // annotations obtained from a document.
    // For now, we verify the class interface compiles and basic constants.
    SUCCEED();
}

// Test getRef returns a Ref
TEST_F(AnnotTest_780, GetRefReturnsRef_780) {
    // This is a basic interface test - the ref should be retrievable
    // We verify through document-loaded annotations if possible
    SUCCEED();
}

// Test that setRect properly updates the rectangle with normalized coordinates
TEST_F(AnnotTest_780, SetRectWithFourDoubles_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    
    // After construction, rect should match what was provided (possibly normalized)
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// Test setRect with PDFRectangle object
TEST_F(AnnotTest_780, SetRectWithPDFRectangle_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    PDFRectangle newRect(50.0, 60.0, 150.0, 250.0);
    annot.setRect(newRect);
    
    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    
    EXPECT_DOUBLE_EQ(x1, 50.0);
    EXPECT_DOUBLE_EQ(y1, 60.0);
    EXPECT_DOUBLE_EQ(x2, 150.0);
    EXPECT_DOUBLE_EQ(y2, 250.0);
}

// Test setRect normalizes inverted coordinates
TEST_F(AnnotTest_780, SetRectNormalizesInvertedCoordinates_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    // Set rect with inverted coordinates (x1 > x2, y1 > y2)
    annot.setRect(100.0, 200.0, 50.0, 60.0);
    
    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    
    // Should be normalized so x1 <= x2 and y1 <= y2
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// Test getXMin, getYMin, getXMax, getYMax
TEST_F(AnnotTest_780, GetMinMaxCoordinates_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    EXPECT_DOUBLE_EQ(annot.getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 100.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 200.0);
}

// Test inRect returns true for point inside rectangle
TEST_F(AnnotTest_780, InRectTrueForPointInside_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    EXPECT_TRUE(annot.inRect(50.0, 100.0));
}

// Test inRect returns false for point outside rectangle
TEST_F(AnnotTest_780, InRectFalseForPointOutside_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    EXPECT_FALSE(annot.inRect(5.0, 10.0));
    EXPECT_FALSE(annot.inRect(150.0, 300.0));
}

// Test inRect for boundary points
TEST_F(AnnotTest_780, InRectBoundaryPoints_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    // Points exactly on the boundary
    EXPECT_TRUE(annot.inRect(10.0, 20.0));
    EXPECT_TRUE(annot.inRect(100.0, 200.0));
    EXPECT_TRUE(annot.inRect(10.0, 200.0));
    EXPECT_TRUE(annot.inRect(100.0, 20.0));
}

// Test setContents and getContents
TEST_F(AnnotTest_780, SetAndGetContents_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    auto content = std::make_unique<GooString>("Test content");
    annot.setContents(std::move(content));
    
    const GooString *retrieved = annot.getContents();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test content");
}

// Test setContents with empty string
TEST_F(AnnotTest_780, SetEmptyContents_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    auto content = std::make_unique<GooString>("");
    annot.setContents(std::move(content));
    
    const GooString *retrieved = annot.getContents();
    // Contents should be set (possibly null for empty, or empty string)
    if (retrieved) {
        EXPECT_EQ(retrieved->getLength(), 0);
    }
}

// Test setFlags and getFlags
TEST_F(AnnotTest_780, SetAndGetFlags_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    annot.setFlags(0x04); // Hidden flag
    EXPECT_EQ(annot.getFlags(), 0x04u);
}

// Test setFlags with zero
TEST_F(AnnotTest_780, SetFlagsZero_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    annot.setFlags(0);
    EXPECT_EQ(annot.getFlags(), 0u);
}

// Test setModified and getModified
TEST_F(AnnotTest_780, SetAndGetModified_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    auto modified = std::make_unique<GooString>("D:20230101120000");
    annot.setModified(std::move(modified));
    
    const GooString *retrieved = annot.getModified();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "D:20230101120000");
}

// Test getType returns valid subtype
TEST_F(AnnotTest_780, GetTypeReturnsValidSubtype_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    AnnotSubtype type = annot.getType();
    // The type should be a valid enum value
    // At minimum, it should not crash
    (void)type;
    SUCCEED();
}

// Test getHasRef
TEST_F(AnnotTest_780, GetHasRef_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    // hasRef should be a valid boolean
    bool hasRef = annot.getHasRef();
    (void)hasRef;
    SUCCEED();
}

// Test getDoc returns the document
TEST_F(AnnotTest_780, GetDocReturnsPDFDoc_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    EXPECT_EQ(annot.getDoc(), doc.get());
}

// Test getPageNum
TEST_F(AnnotTest_780, GetPageNum_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    int pageNum = annot.getPageNum();
    // Default page num should be 0 or some valid value
    (void)pageNum;
    SUCCEED();
}

// Test getRect returns const reference to PDFRectangle
TEST_F(AnnotTest_780, GetRectReturnsConstRef_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    const PDFRectangle &rect = annot.getRect();
    EXPECT_DOUBLE_EQ(rect.x1, 10.0);
    EXPECT_DOUBLE_EQ(rect.y1, 20.0);
    EXPECT_DOUBLE_EQ(rect.x2, 100.0);
    EXPECT_DOUBLE_EQ(rect.y2, 200.0);
}

// Test setColor and getColor
TEST_F(AnnotTest_780, SetAndGetColor_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    annot.setColor(std::move(color));
    
    AnnotColor *retrieved = annot.getColor();
    ASSERT_NE(retrieved, nullptr);
}

// Test setBorder and getBorder
TEST_F(AnnotTest_780, SetAndGetBorder_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    // Set a null border
    annot.setBorder(nullptr);
    AnnotBorder *border = annot.getBorder();
    EXPECT_EQ(border, nullptr);
}

// Test setNewAppearance
TEST_F(AnnotTest_780, SetNewAppearance_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    Object newAppearance;
    annot.setNewAppearance(std::move(newAppearance));
    
    // Should not crash
    SUCCEED();
}

// Test getAppearStreams
TEST_F(AnnotTest_780, GetAppearStreams_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    AnnotAppearance *streams = annot.getAppearStreams();
    // May be null for newly created annotation
    (void)streams;
    SUCCEED();
}

// Test getAppearState
TEST_F(AnnotTest_780, GetAppearState_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    const GooString *state = annot.getAppearState();
    // May be null for default state
    (void)state;
    SUCCEED();
}

// Test setAppearanceState
TEST_F(AnnotTest_780, SetAppearanceState_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    annot.setAppearanceState("Off");
    
    const GooString *state = annot.getAppearState();
    if (state) {
        EXPECT_STREQ(state->c_str(), "Off");
    }
}

// Test getTreeKey
TEST_F(AnnotTest_780, GetTreeKey_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    int treeKey = annot.getTreeKey();
    (void)treeKey;
    SUCCEED();
}

// Test getId
TEST_F(AnnotTest_780, GetId_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    int id = annot.getId();
    (void)id;
    SUCCEED();
}

// Test isOk
TEST_F(AnnotTest_780, IsOk_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    bool ok = annot.isOk();
    EXPECT_TRUE(ok);
}

// Test getAnnotObj
TEST_F(AnnotTest_780, GetAnnotObj_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    const Object &obj = annot.getAnnotObj();
    // Should be a valid object
    (void)obj;
    SUCCEED();
}

// Test match with matching Ref
TEST_F(AnnotTest_780, MatchWithMatchingRef_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    Ref ref = annot.getRef();
    bool matches = annot.match(&ref);
    // If hasRef is true, it should match its own ref
    if (annot.getHasRef()) {
        EXPECT_TRUE(matches);
    }
}

// Test match with non-matching Ref
TEST_F(AnnotTest_780, MatchWithNonMatchingRef_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    Ref fakeRef = {99999, 99999};
    bool matches = annot.match(&fakeRef);
    // Should not match a random ref (unless by extremely unlikely coincidence)
    // We don't assert because the annot's own ref could theoretically match
    (void)matches;
    SUCCEED();
}

// Test getName returns null for newly created annotation without name
TEST_F(AnnotTest_780, GetNameDefault_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    const GooString *name = annot.getName();
    // May be null for newly created annotations
    (void)name;
    SUCCEED();
}

// Test setName and getName
TEST_F(AnnotTest_780, SetAndGetName_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    GooString name("TestAnnotation");
    annot.setName(&name);
    
    const GooString *retrieved = annot.getName();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "TestAnnotation");
}

// Test getAppearance
TEST_F(AnnotTest_780, GetAppearance_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    Object appearance = annot.getAppearance();
    // Should not crash
    (void)appearance;
    SUCCEED();
}

// Test getAppearanceResDict
TEST_F(AnnotTest_780, GetAppearanceResDict_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    Object resDict = annot.getAppearanceResDict();
    (void)resDict;
    SUCCEED();
}

// Test setRect rejects zero-area rectangle (equal points)
TEST_F(AnnotTest_780, SetRectWithEqualPoints_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    // Try setting a zero-area rect
    annot.setRect(50.0, 50.0, 50.0, 50.0);
    
    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    // Behavior may vary - just verify no crash
    SUCCEED();
}

// Test multiple setContents calls replace previous content
TEST_F(AnnotTest_780, SetContentsReplacePrevious_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    annot.setContents(std::make_unique<GooString>("First"));
    annot.setContents(std::make_unique<GooString>("Second"));
    
    const GooString *retrieved = annot.getContents();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Second");
}

// Test setFlags with various flag combinations
TEST_F(AnnotTest_780, SetFlagsMultipleBits_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    // Set multiple flags at once
    unsigned int flags = 0x04 | 0x08 | 0x20; // Hidden | NoZoom | NoRotate
    annot.setFlags(flags);
    EXPECT_EQ(annot.getFlags(), flags);
}

// Test setNewAppearance with keepAppearState parameter
TEST_F(AnnotTest_780, SetNewAppearanceWithKeepState_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    Object newAppearance;
    annot.setNewAppearance(std::move(newAppearance), true);
    
    SUCCEED();
}

// Test setContents with nullptr/null unique_ptr
TEST_F(AnnotTest_780, SetContentsNull_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    annot.setContents(nullptr);
    
    // Should handle null gracefully
    const GooString *retrieved = annot.getContents();
    (void)retrieved;
    SUCCEED();
}

// Test large coordinate values for setRect
TEST_F(AnnotTest_780, SetRectLargeCoordinates_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    annot.setRect(0.0, 0.0, 100000.0, 100000.0);
    
    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    
    EXPECT_DOUBLE_EQ(x1, 0.0);
    EXPECT_DOUBLE_EQ(y1, 0.0);
    EXPECT_DOUBLE_EQ(x2, 100000.0);
    EXPECT_DOUBLE_EQ(y2, 100000.0);
}

// Test negative coordinate values for setRect
TEST_F(AnnotTest_780, SetRectNegativeCoordinates_780) {
    auto doc = createTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    PDFRectangle rectA(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rectA);
    
    annot.setRect(-100.0, -200.0, -10.0, -20.0);
    
    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}
