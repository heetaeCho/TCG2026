#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "Object.h"
#include "Page.h"

class AnnotTest_776 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test creating an Annot with a PDFRectangle
TEST_F(AnnotTest_776, ConstructWithRectangle_776) {
    // We need a valid PDFDoc to construct an Annot
    // Since we can't easily create one without a file, we test with a minimal setup
    // This test verifies the constructor doesn't crash with valid inputs
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);
    EXPECT_TRUE(annot.isOk());
}

// Test getRect returns correct values
TEST_F(AnnotTest_776, GetRectReturnsCorrectValues_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 300.0, 400.0);
    Annot annot(doc.get(), &rect);

    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, 10.0);
    EXPECT_DOUBLE_EQ(y1, 20.0);
    EXPECT_DOUBLE_EQ(x2, 300.0);
    EXPECT_DOUBLE_EQ(y2, 400.0);
}

// Test getXMin/getYMin/getXMax/getYMax
TEST_F(AnnotTest_776, GetMinMaxCoordinates_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(5.0, 10.0, 200.0, 300.0);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 5.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 10.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 200.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 300.0);
}

// Test setRect with PDFRectangle
TEST_F(AnnotTest_776, SetRectWithPDFRectangle_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    PDFRectangle newRect(50.0, 50.0, 250.0, 250.0);
    annot.setRect(newRect);

    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, 50.0);
    EXPECT_DOUBLE_EQ(y1, 50.0);
    EXPECT_DOUBLE_EQ(x2, 250.0);
    EXPECT_DOUBLE_EQ(y2, 250.0);
}

// Test setRect with double values
TEST_F(AnnotTest_776, SetRectWithDoubles_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setRect(15.0, 25.0, 315.0, 425.0);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 15.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 25.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 315.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 425.0);
}

// Test inRect with a point inside the rectangle
TEST_F(AnnotTest_776, InRectPointInside_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    EXPECT_TRUE(annot.inRect(50.0, 50.0));
}

// Test inRect with a point outside the rectangle
TEST_F(AnnotTest_776, InRectPointOutside_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    EXPECT_FALSE(annot.inRect(150.0, 150.0));
}

// Test inRect with a point on the boundary
TEST_F(AnnotTest_776, InRectPointOnBoundary_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    // Boundary points - behavior depends on implementation (inclusive or exclusive)
    bool onEdge = annot.inRect(0.0, 0.0);
    // Just verify it doesn't crash; the exact result depends on implementation
    (void)onEdge;
}

// Test inRect with negative coordinates outside
TEST_F(AnnotTest_776, InRectNegativeCoordinates_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 10.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    EXPECT_FALSE(annot.inRect(-5.0, -5.0));
}

// Test setContents and getContents
TEST_F(AnnotTest_776, SetAndGetContents_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    auto content = std::make_unique<GooString>("Hello World");
    annot.setContents(std::move(content));

    const GooString *retrieved = annot.getContents();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Hello World");
}

// Test setContents with empty string
TEST_F(AnnotTest_776, SetContentsEmpty_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
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

// Test setContents with nullptr (null unique_ptr)
TEST_F(AnnotTest_776, SetContentsNull_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    std::unique_ptr<GooString> nullContent;
    annot.setContents(std::move(nullContent));

    // Should not crash; contents may be null or empty
    const GooString *retrieved = annot.getContents();
    (void)retrieved; // Implementation dependent
}

// Test setFlags and getFlags
TEST_F(AnnotTest_776, SetAndGetFlags_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0x04); // Hidden flag
    EXPECT_EQ(annot.getFlags(), 0x04u);
}

// Test setFlags with zero
TEST_F(AnnotTest_776, SetFlagsZero_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0);
    EXPECT_EQ(annot.getFlags(), 0u);
}

// Test setFlags with all bits set
TEST_F(AnnotTest_776, SetFlagsAllBits_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0xFFFFFFFF);
    EXPECT_EQ(annot.getFlags(), 0xFFFFFFFFu);
}

// Test getDoc
TEST_F(AnnotTest_776, GetDocReturnsCorrectDoc_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    EXPECT_EQ(annot.getDoc(), doc.get());
}

// Test getType returns a valid subtype
TEST_F(AnnotTest_776, GetTypeReturnsValidSubtype_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    AnnotSubtype subtype = annot.getType();
    // Just verify it returns without crashing
    (void)subtype;
}

// Test initial contents are null or empty for a new annotation
TEST_F(AnnotTest_776, InitialContentsNullOrEmpty_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    const GooString *contents = annot.getContents();
    // For a newly created annotation, contents may be null or empty
    if (contents) {
        EXPECT_EQ(contents->getLength(), 0);
    }
}

// Test getName initially
TEST_F(AnnotTest_776, GetNameInitial_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    const GooString *name = annot.getName();
    // May be null for a newly created annotation
    (void)name;
}

// Test getModified initially
TEST_F(AnnotTest_776, GetModifiedInitial_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    const GooString *modified = annot.getModified();
    // May be null for a newly created annotation
    (void)modified;
}

// Test setModified and getModified
TEST_F(AnnotTest_776, SetAndGetModified_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setModified(std::make_unique<GooString>("D:20230101120000"));

    const GooString *modified = annot.getModified();
    ASSERT_NE(modified, nullptr);
    EXPECT_STREQ(modified->c_str(), "D:20230101120000");
}

// Test getBorder initially
TEST_F(AnnotTest_776, GetBorderInitial_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    AnnotBorder *border = annot.getBorder();
    // May be null for a newly created annotation
    (void)border;
}

// Test getColor initially
TEST_F(AnnotTest_776, GetColorInitial_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    AnnotColor *color = annot.getColor();
    // May be null for a newly created annotation
    (void)color;
}

// Test getAppearStreams initially
TEST_F(AnnotTest_776, GetAppearStreamsInitial_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    AnnotAppearance *streams = annot.getAppearStreams();
    (void)streams;
}

// Test getAppearState initially
TEST_F(AnnotTest_776, GetAppearStateInitial_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    const GooString *state = annot.getAppearState();
    (void)state;
}

// Test setAppearanceState
TEST_F(AnnotTest_776, SetAppearanceState_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setAppearanceState("On");
    const GooString *state = annot.getAppearState();
    ASSERT_NE(state, nullptr);
    EXPECT_STREQ(state->c_str(), "On");
}

// Test getTreeKey
TEST_F(AnnotTest_776, GetTreeKey_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    int key = annot.getTreeKey();
    (void)key; // Just verify it doesn't crash
}

// Test getId
TEST_F(AnnotTest_776, GetId_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    int id = annot.getId();
    (void)id; // Just verify it doesn't crash
}

// Test getPageNum
TEST_F(AnnotTest_776, GetPageNum_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    int pageNum = annot.getPageNum();
    // For a newly created annotation, page may be 0 or -1
    (void)pageNum;
}

// Test getHasRef
TEST_F(AnnotTest_776, GetHasRef_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    bool hasRef = annot.getHasRef();
    (void)hasRef;
}

// Test setRect normalizes coordinates (swapped x1 > x2)
TEST_F(AnnotTest_776, SetRectNormalizesSwappedX_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    // Set rect with x1 > x2 - implementation may normalize
    annot.setRect(200.0, 10.0, 50.0, 300.0);

    // The implementation might normalize so that xMin <= xMax
    double xMin = annot.getXMin();
    double xMax = annot.getXMax();
    EXPECT_LE(xMin, xMax);
}

// Test setRect normalizes coordinates (swapped y1 > y2)
TEST_F(AnnotTest_776, SetRectNormalizesSwappedY_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setRect(10.0, 400.0, 200.0, 50.0);

    double yMin = annot.getYMin();
    double yMax = annot.getYMax();
    EXPECT_LE(yMin, yMax);
}

// Test setColor with a new color
TEST_F(AnnotTest_776, SetColor_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0); // Red
    annot.setColor(std::move(color));

    AnnotColor *retrievedColor = annot.getColor();
    ASSERT_NE(retrievedColor, nullptr);
}

// Test setColor with null
TEST_F(AnnotTest_776, SetColorNull_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    std::unique_ptr<AnnotColor> nullColor;
    annot.setColor(std::move(nullColor));

    AnnotColor *retrievedColor = annot.getColor();
    EXPECT_EQ(retrievedColor, nullptr);
}

// Test getAnnotObj
TEST_F(AnnotTest_776, GetAnnotObj_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    const Object &obj = annot.getAnnotObj();
    // The annotation object should be a dictionary
    (void)obj;
}

// Test getAppearance
TEST_F(AnnotTest_776, GetAppearance_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    Object appearance = annot.getAppearance();
    // For a new annotation, appearance may be null
    (void)appearance;
}

// Test setNewAppearance
TEST_F(AnnotTest_776, SetNewAppearance_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    Object newAppearance;
    annot.setNewAppearance(std::move(newAppearance));

    // Verify no crash
}

// Test setNewAppearance with keepAppearState
TEST_F(AnnotTest_776, SetNewAppearanceKeepState_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setAppearanceState("Normal");

    Object newAppearance;
    annot.setNewAppearance(std::move(newAppearance), true);

    const GooString *state = annot.getAppearState();
    if (state) {
        EXPECT_STREQ(state->c_str(), "Normal");
    }
}

// Test getRect returns reference
TEST_F(AnnotTest_776, GetRectReturnsReference_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(1.0, 2.0, 3.0, 4.0);
    Annot annot(doc.get(), &rect);

    const PDFRectangle &r = annot.getRect();
    EXPECT_DOUBLE_EQ(r.x1, 1.0);
    EXPECT_DOUBLE_EQ(r.y1, 2.0);
    EXPECT_DOUBLE_EQ(r.x2, 3.0);
    EXPECT_DOUBLE_EQ(r.y2, 4.0);
}

// Test multiple setContents calls
TEST_F(AnnotTest_776, SetContentsMultipleTimes_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
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

// Test setRect with zero-area rectangle
TEST_F(AnnotTest_776, SetRectZeroArea_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setRect(50.0, 50.0, 50.0, 50.0);

    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, x2);
    EXPECT_DOUBLE_EQ(y1, y2);
}

// Test inRect with zero-area rectangle
TEST_F(AnnotTest_776, InRectZeroArea_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(50.0, 50.0, 50.0, 50.0);
    Annot annot(doc.get(), &rect);

    // A point at the exact location of a zero-area rect
    bool result = annot.inRect(50.0, 50.0);
    (void)result; // Implementation dependent
}

// Test setRect with very large coordinates
TEST_F(AnnotTest_776, SetRectLargeCoordinates_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setRect(0.0, 0.0, 1e6, 1e6);

    EXPECT_DOUBLE_EQ(annot.getXMax(), 1e6);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 1e6);
}

// Test setAppearanceState with different states
TEST_F(AnnotTest_776, SetAppearanceStateDifferentValues_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setAppearanceState("Off");
    ASSERT_NE(annot.getAppearState(), nullptr);
    EXPECT_STREQ(annot.getAppearState()->c_str(), "Off");

    annot.setAppearanceState("On");
    ASSERT_NE(annot.getAppearState(), nullptr);
    EXPECT_STREQ(annot.getAppearState()->c_str(), "On");
}

// Test getAppearanceResDict
TEST_F(AnnotTest_776, GetAppearanceResDict_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    Object resDict = annot.getAppearanceResDict();
    // For a new annotation, this may be null
    (void)resDict;
}

// Test setFlags multiple times
TEST_F(AnnotTest_776, SetFlagsMultipleTimes_776) {
    auto doc = loadTestDoc("test.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0x01);
    EXPECT_EQ(annot.getFlags(), 0x01u);

    annot.setFlags(0x10);
    EXPECT_EQ(annot.getFlags(), 0x10u);

    annot.setFlags(0);
    EXPECT_EQ(annot.getFlags(), 0u);
}
