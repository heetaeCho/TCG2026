#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "GooString.h"
#include "PDFDocFactory.h"

class AnnotTest_782 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We need a valid PDFDoc to create annotations
        // Try to create a minimal PDF document for testing
    }

    std::unique_ptr<PDFDoc> createTestDoc(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that Annot can be constructed with a PDFDoc and PDFRectangle
TEST_F(AnnotTest_782, ConstructWithRectangle_782) {
    // This test checks construction; since we need a valid PDFDoc,
    // we attempt to create one from a test PDF if available.
    // If no test file, we test what we can.
    
    // Create a simple test by attempting construction with a rect
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, 0.0);
    EXPECT_DOUBLE_EQ(y1, 0.0);
    EXPECT_DOUBLE_EQ(x2, 100.0);
    EXPECT_DOUBLE_EQ(y2, 100.0);
}

// Test getType returns the annotation subtype
TEST_F(AnnotTest_782, GetTypeReturnsSubtype_782) {
    PDFRectangle rect(10.0, 20.0, 30.0, 40.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    // Default constructed annot should have some type
    AnnotSubtype type = annot.getType();
    // Just verify it returns without crashing
    (void)type;
}

// Test setRect and getRect
TEST_F(AnnotTest_782, SetRectAndGetRect_782) {
    PDFRectangle rect(0.0, 0.0, 50.0, 50.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    annot.setRect(10.0, 20.0, 30.0, 40.0);
    
    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, 10.0);
    EXPECT_DOUBLE_EQ(y1, 20.0);
    EXPECT_DOUBLE_EQ(x2, 30.0);
    EXPECT_DOUBLE_EQ(y2, 40.0);
}

// Test setRect with PDFRectangle overload
TEST_F(AnnotTest_782, SetRectWithPDFRectangle_782) {
    PDFRectangle rect(0.0, 0.0, 50.0, 50.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    PDFRectangle newRect(5.0, 10.0, 15.0, 20.0);
    annot.setRect(newRect);
    
    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, 5.0);
    EXPECT_DOUBLE_EQ(y1, 10.0);
    EXPECT_DOUBLE_EQ(x2, 15.0);
    EXPECT_DOUBLE_EQ(y2, 20.0);
}

// Test getXMin, getYMin, getXMax, getYMax
TEST_F(AnnotTest_782, GetMinMaxCoordinates_782) {
    PDFRectangle rect(10.0, 20.0, 30.0, 40.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    EXPECT_DOUBLE_EQ(annot.getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 30.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 40.0);
}

// Test setContents and getContents
TEST_F(AnnotTest_782, SetAndGetContents_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    auto content = std::make_unique<GooString>("Test content");
    annot.setContents(std::move(content));
    
    const GooString *result = annot.getContents();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "Test content");
}

// Test setContents with empty string
TEST_F(AnnotTest_782, SetContentsEmpty_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    auto content = std::make_unique<GooString>("");
    annot.setContents(std::move(content));
    
    const GooString *result = annot.getContents();
    if (result) {
        EXPECT_STREQ(result->c_str(), "");
    }
}

// Test setFlags and getFlags
TEST_F(AnnotTest_782, SetAndGetFlags_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    annot.setFlags(0x04); // Hidden flag typically
    EXPECT_EQ(annot.getFlags(), 0x04u);
}

// Test setFlags with zero
TEST_F(AnnotTest_782, SetFlagsZero_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    annot.setFlags(0);
    EXPECT_EQ(annot.getFlags(), 0u);
}

// Test setFlags with max value
TEST_F(AnnotTest_782, SetFlagsMaxValue_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    annot.setFlags(0xFFFFFFFF);
    EXPECT_EQ(annot.getFlags(), 0xFFFFFFFFu);
}

// Test inRect - point inside
TEST_F(AnnotTest_782, InRectPointInside_782) {
    PDFRectangle rect(10.0, 20.0, 30.0, 40.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    EXPECT_TRUE(annot.inRect(20.0, 30.0));
}

// Test inRect - point outside
TEST_F(AnnotTest_782, InRectPointOutside_782) {
    PDFRectangle rect(10.0, 20.0, 30.0, 40.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    EXPECT_FALSE(annot.inRect(5.0, 5.0));
}

// Test inRect - point on boundary
TEST_F(AnnotTest_782, InRectPointOnBoundary_782) {
    PDFRectangle rect(10.0, 20.0, 30.0, 40.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    // Boundary behavior - on the edge
    bool result = annot.inRect(10.0, 20.0);
    // Just verify it doesn't crash; boundary behavior is implementation-defined
    (void)result;
}

// Test inRect - point just outside right boundary
TEST_F(AnnotTest_782, InRectPointJustOutsideRight_782) {
    PDFRectangle rect(10.0, 20.0, 30.0, 40.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    EXPECT_FALSE(annot.inRect(31.0, 30.0));
}

// Test inRect - point just outside top boundary
TEST_F(AnnotTest_782, InRectPointJustOutsideTop_782) {
    PDFRectangle rect(10.0, 20.0, 30.0, 40.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    EXPECT_FALSE(annot.inRect(20.0, 41.0));
}

// Test setModified and getModified
TEST_F(AnnotTest_782, SetAndGetModified_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    auto modified = std::make_unique<GooString>("D:20230101000000");
    annot.setModified(std::move(modified));
    
    const GooString *result = annot.getModified();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "D:20230101000000");
}

// Test getDoc
TEST_F(AnnotTest_782, GetDocReturnsDoc_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    EXPECT_EQ(annot.getDoc(), doc.get());
}

// Test getRect const reference
TEST_F(AnnotTest_782, GetRectConstRef_782) {
    PDFRectangle rect(10.0, 20.0, 30.0, 40.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    const PDFRectangle &rectRef = annot.getRect();
    EXPECT_DOUBLE_EQ(rectRef.x1, 10.0);
    EXPECT_DOUBLE_EQ(rectRef.y1, 20.0);
    EXPECT_DOUBLE_EQ(rectRef.x2, 30.0);
    EXPECT_DOUBLE_EQ(rectRef.y2, 40.0);
}

// Test setRect with swapped coordinates (x1 > x2, y1 > y2)
TEST_F(AnnotTest_782, SetRectSwappedCoordinates_782) {
    PDFRectangle rect(0.0, 0.0, 50.0, 50.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    // Set rect with swapped coordinates - implementation may normalize
    annot.setRect(30.0, 40.0, 10.0, 20.0);
    
    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    // The implementation should normalize so x1 <= x2 and y1 <= y2
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// Test setColor and getColor with nullptr
TEST_F(AnnotTest_782, SetColorNull_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    annot.setColor(nullptr);
    EXPECT_EQ(annot.getColor(), nullptr);
}

// Test setBorder and getBorder with nullptr
TEST_F(AnnotTest_782, SetBorderNull_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    annot.setBorder(nullptr);
    EXPECT_EQ(annot.getBorder(), nullptr);
}

// Test getPageNum
TEST_F(AnnotTest_782, GetPageNum_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    // For a newly created annotation, page num should have some default value
    int pageNum = annot.getPageNum();
    (void)pageNum; // Just verify it doesn't crash
}

// Test getTreeKey
TEST_F(AnnotTest_782, GetTreeKey_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    int treeKey = annot.getTreeKey();
    (void)treeKey; // Just verify it doesn't crash
}

// Test getHasRef
TEST_F(AnnotTest_782, GetHasRef_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    bool hasRef = annot.getHasRef();
    (void)hasRef; // Just verify it returns without crash
}

// Test setNewAppearance
TEST_F(AnnotTest_782, SetNewAppearance_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    Object newAppearance;
    annot.setNewAppearance(std::move(newAppearance));
    
    // Verify it doesn't crash
    Object app = annot.getAppearance();
    (void)app;
}

// Test setAppearanceState
TEST_F(AnnotTest_782, SetAppearanceState_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    annot.setAppearanceState("On");
    
    const GooString *state = annot.getAppearState();
    if (state) {
        EXPECT_STREQ(state->c_str(), "On");
    }
}

// Test getAnnotObj
TEST_F(AnnotTest_782, GetAnnotObj_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    const Object &obj = annot.getAnnotObj();
    // Just verify it returns without crash
    (void)obj;
}

// Test multiple setRect calls
TEST_F(AnnotTest_782, MultipleSetRect_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    annot.setRect(1.0, 2.0, 3.0, 4.0);
    annot.setRect(5.0, 6.0, 7.0, 8.0);
    
    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, 5.0);
    EXPECT_DOUBLE_EQ(y1, 6.0);
    EXPECT_DOUBLE_EQ(x2, 7.0);
    EXPECT_DOUBLE_EQ(y2, 8.0);
}

// Test setContents replaces previous contents
TEST_F(AnnotTest_782, SetContentsReplacePrevious_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    auto content1 = std::make_unique<GooString>("First content");
    annot.setContents(std::move(content1));
    
    auto content2 = std::make_unique<GooString>("Second content");
    annot.setContents(std::move(content2));
    
    const GooString *result = annot.getContents();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "Second content");
}

// Test setRect with very large values
TEST_F(AnnotTest_782, SetRectLargeValues_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    annot.setRect(0.0, 0.0, 1e6, 1e6);
    
    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, 0.0);
    EXPECT_DOUBLE_EQ(y1, 0.0);
    EXPECT_DOUBLE_EQ(x2, 1e6);
    EXPECT_DOUBLE_EQ(y2, 1e6);
}

// Test setRect with negative values
TEST_F(AnnotTest_782, SetRectNegativeValues_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    annot.setRect(-100.0, -200.0, -10.0, -20.0);
    
    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    // Should normalize
    EXPECT_LE(x1, x2);
    EXPECT_LE(y1, y2);
}

// Test setNewAppearance with keepAppearState parameter
TEST_F(AnnotTest_782, SetNewAppearanceKeepState_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    annot.setAppearanceState("Normal");
    
    Object newAppearance;
    annot.setNewAppearance(std::move(newAppearance), true);
    
    // Verify appearance state is kept
    const GooString *state = annot.getAppearState();
    if (state) {
        EXPECT_STREQ(state->c_str(), "Normal");
    }
}

// Test inRect with zero-size rect
TEST_F(AnnotTest_782, InRectZeroSizeRect_782) {
    PDFRectangle rect(10.0, 10.0, 10.0, 10.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    // A zero-size rect - point exactly at the rect
    bool result = annot.inRect(10.0, 10.0);
    // Behavior is implementation-defined for degenerate rectangles
    (void)result;
}

// Test getAppearStreams returns pointer (may be null for new annotation)
TEST_F(AnnotTest_782, GetAppearStreams_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    AnnotAppearance *streams = annot.getAppearStreams();
    // May be null for a newly created annotation
    (void)streams;
}

// Test getName for newly created annotation
TEST_F(AnnotTest_782, GetNameDefault_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    const GooString *name = annot.getName();
    // Name may be null for newly created annotation
    (void)name;
}

// Test setName
TEST_F(AnnotTest_782, SetName_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    GooString name("TestAnnotation");
    annot.setName(&name);
    
    const GooString *result = annot.getName();
    if (result) {
        EXPECT_STREQ(result->c_str(), "TestAnnotation");
    }
}

// Test getId
TEST_F(AnnotTest_782, GetId_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    int id = annot.getId();
    // Just verify it returns without crash
    (void)id;
}

// Test getAppearanceResDict for new annotation
TEST_F(AnnotTest_782, GetAppearanceResDict_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    Object resDict = annot.getAppearanceResDict();
    // May be null object for new annotation
    (void)resDict;
}

// Test isOk
TEST_F(AnnotTest_782, IsOk_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    bool ok = annot.isOk();
    EXPECT_TRUE(ok);
}

// Test setContents with nullptr (null unique_ptr)
TEST_F(AnnotTest_782, SetContentsNull_782) {
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    std::unique_ptr<GooString> nullContent;
    annot.setContents(std::move(nullContent));
    
    // Should not crash; contents may be null or empty
    const GooString *result = annot.getContents();
    (void)result;
}

// Test coordinates after setRect update XMin/YMin/XMax/YMax
TEST_F(AnnotTest_782, SetRectUpdatesMinMax_782) {
    PDFRectangle rect(0.0, 0.0, 50.0, 50.0);
    
    auto doc = createTestDoc("./test_data/test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Annot annot(doc.get(), &rect);
    
    annot.setRect(15.0, 25.0, 35.0, 45.0);
    
    EXPECT_DOUBLE_EQ(annot.getXMin(), 15.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 25.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 35.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 45.0);
}
