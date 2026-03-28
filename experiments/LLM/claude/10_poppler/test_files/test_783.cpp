#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "Object.h"

class AnnotTest_783 : public ::testing::Test {
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
TEST_F(AnnotTest_783, ConstructWithRectangle_783) {
    // We need a valid PDFDoc to create annotations
    // Using a minimal approach - create a simple PDF in memory if possible
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_TRUE(annot.isOk());
}

// Test getRect returns the rectangle set during construction
TEST_F(AnnotTest_783, GetRectReturnsCorrectValues_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    const PDFRectangle &r = annot.getRect();
    EXPECT_DOUBLE_EQ(r.x1, 10.0);
    EXPECT_DOUBLE_EQ(r.y1, 20.0);
    EXPECT_DOUBLE_EQ(r.x2, 100.0);
    EXPECT_DOUBLE_EQ(r.y2, 200.0);
}

// Test getXMin, getYMin, getXMax, getYMax
TEST_F(AnnotTest_783, GetMinMaxCoordinates_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 100.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 200.0);
}

// Test setRect with PDFRectangle
TEST_F(AnnotTest_783, SetRectWithPDFRectangle_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    PDFRectangle newRect(50.0, 60.0, 150.0, 250.0);
    annot.setRect(newRect);

    const PDFRectangle &r = annot.getRect();
    EXPECT_DOUBLE_EQ(r.x1, 50.0);
    EXPECT_DOUBLE_EQ(r.y1, 60.0);
    EXPECT_DOUBLE_EQ(r.x2, 150.0);
    EXPECT_DOUBLE_EQ(r.y2, 250.0);
}

// Test setRect with individual coordinates
TEST_F(AnnotTest_783, SetRectWithCoordinates_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setRect(30.0, 40.0, 130.0, 240.0);

    const PDFRectangle &r = annot.getRect();
    EXPECT_DOUBLE_EQ(r.x1, 30.0);
    EXPECT_DOUBLE_EQ(r.y1, 40.0);
    EXPECT_DOUBLE_EQ(r.x2, 130.0);
    EXPECT_DOUBLE_EQ(r.y2, 240.0);
}

// Test getRect with output parameters
TEST_F(AnnotTest_783, GetRectOutputParameters_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(15.0, 25.0, 115.0, 225.0);
    Annot annot(doc.get(), &rect);

    double x1, y1, x2, y2;
    annot.getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x1, 15.0);
    EXPECT_DOUBLE_EQ(y1, 25.0);
    EXPECT_DOUBLE_EQ(x2, 115.0);
    EXPECT_DOUBLE_EQ(y2, 225.0);
}

// Test inRect - point inside rectangle
TEST_F(AnnotTest_783, InRectPointInside_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_TRUE(annot.inRect(50.0, 100.0));
}

// Test inRect - point outside rectangle
TEST_F(AnnotTest_783, InRectPointOutside_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_FALSE(annot.inRect(5.0, 10.0));
    EXPECT_FALSE(annot.inRect(150.0, 300.0));
}

// Test inRect - point on boundary
TEST_F(AnnotTest_783, InRectPointOnBoundary_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    // Boundary points - behavior depends on implementation (inclusive or exclusive)
    bool onEdge = annot.inRect(10.0, 20.0);
    // Just verify it doesn't crash; exact result depends on implementation
    (void)onEdge;
}

// Test setContents and getContents
TEST_F(AnnotTest_783, SetAndGetContents_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
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
TEST_F(AnnotTest_783, SetContentsEmpty_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
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

// Test setContents with nullptr
TEST_F(AnnotTest_783, SetContentsNull_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setContents(nullptr);
    // Should not crash; getContents might return nullptr
    const GooString *retrieved = annot.getContents();
    (void)retrieved;
}

// Test setFlags and getFlags
TEST_F(AnnotTest_783, SetAndGetFlags_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0x04); // Hidden flag
    EXPECT_EQ(annot.getFlags(), 0x04u);
}

// Test setFlags with zero
TEST_F(AnnotTest_783, SetFlagsZero_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0);
    EXPECT_EQ(annot.getFlags(), 0u);
}

// Test setModified and getModified
TEST_F(AnnotTest_783, SetAndGetModified_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    auto mod = std::make_unique<GooString>("D:20230101120000");
    annot.setModified(std::move(mod));

    const GooString *retrieved = annot.getModified();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "D:20230101120000");
}

// Test getType
TEST_F(AnnotTest_783, GetType_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    // Just verify type is accessible and doesn't crash
    AnnotSubtype t = annot.getType();
    (void)t;
}

// Test getDoc
TEST_F(AnnotTest_783, GetDoc_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    EXPECT_EQ(annot.getDoc(), doc.get());
}

// Test getPageNum
TEST_F(AnnotTest_783, GetPageNum_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    // Page number should be accessible
    int pageNum = annot.getPageNum();
    (void)pageNum;
}

// Test getHasRef for newly created annotation
TEST_F(AnnotTest_783, GetHasRef_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    // Just check it's accessible
    bool hasRef = annot.getHasRef();
    (void)hasRef;
}

// Test getBorder
TEST_F(AnnotTest_783, GetBorderInitial_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    // Border may or may not be null initially
    AnnotBorder *border = annot.getBorder();
    (void)border;
}

// Test getColor
TEST_F(AnnotTest_783, GetColorInitial_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    AnnotColor *color = annot.getColor();
    (void)color;
}

// Test getAppearStreams
TEST_F(AnnotTest_783, GetAppearStreams_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    AnnotAppearance *streams = annot.getAppearStreams();
    (void)streams;
}

// Test getAppearState
TEST_F(AnnotTest_783, GetAppearState_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    const GooString *state = annot.getAppearState();
    (void)state;
}

// Test setAppearanceState
TEST_F(AnnotTest_783, SetAppearanceState_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setAppearanceState("N");
    const GooString *state = annot.getAppearState();
    ASSERT_NE(state, nullptr);
    EXPECT_STREQ(state->c_str(), "N");
}

// Test getTreeKey
TEST_F(AnnotTest_783, GetTreeKey_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    int key = annot.getTreeKey();
    (void)key;
}

// Test setRect normalizes coordinates (x1 < x2, y1 < y2)
TEST_F(AnnotTest_783, SetRectNormalizesCoordinates_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    // Set with swapped coordinates
    annot.setRect(100.0, 200.0, 10.0, 20.0);

    const PDFRectangle &r = annot.getRect();
    // Implementation might normalize so x1 <= x2, y1 <= y2
    EXPECT_LE(r.x1, r.x2);
    EXPECT_LE(r.y1, r.y2);
}

// Test setNewAppearance
TEST_F(AnnotTest_783, SetNewAppearance_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    Object nullObj;
    annot.setNewAppearance(std::move(nullObj));
    // Should not crash
}

// Test setColor with nullptr
TEST_F(AnnotTest_783, SetColorNull_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setColor(nullptr);
    EXPECT_EQ(annot.getColor(), nullptr);
}

// Test setBorder with nullptr
TEST_F(AnnotTest_783, SetBorderNull_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setBorder(nullptr);
    EXPECT_EQ(annot.getBorder(), nullptr);
}

// Test getName
TEST_F(AnnotTest_783, GetNameInitial_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    const GooString *name = annot.getName();
    (void)name;
}

// Test getAnnotObj
TEST_F(AnnotTest_783, GetAnnotObj_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    const Object &obj = annot.getAnnotObj();
    (void)obj;
}

// Test getId
TEST_F(AnnotTest_783, GetId_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    int id = annot.getId();
    (void)id;
}

// Test setRect updates getXMin/getYMin/getXMax/getYMax consistently
TEST_F(AnnotTest_783, SetRectUpdatesMinMax_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setRect(5.0, 15.0, 55.0, 65.0);

    EXPECT_DOUBLE_EQ(annot.getXMin(), 5.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 15.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 55.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 65.0);
}

// Test inRect after setRect
TEST_F(AnnotTest_783, InRectAfterSetRect_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    // Point inside initial rect
    EXPECT_TRUE(annot.inRect(50.0, 100.0));

    // Change rect
    annot.setRect(200.0, 300.0, 400.0, 500.0);

    // Old point should be outside now
    EXPECT_FALSE(annot.inRect(50.0, 100.0));

    // New point should be inside
    EXPECT_TRUE(annot.inRect(300.0, 400.0));
}

// Test with zero-area rectangle
TEST_F(AnnotTest_783, ZeroAreaRectangle_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(50.0, 50.0, 50.0, 50.0);
    Annot annot(doc.get(), &rect);

    const PDFRectangle &r = annot.getRect();
    EXPECT_DOUBLE_EQ(r.x1, 50.0);
    EXPECT_DOUBLE_EQ(r.y1, 50.0);
    EXPECT_DOUBLE_EQ(r.x2, 50.0);
    EXPECT_DOUBLE_EQ(r.y2, 50.0);
}

// Test with negative coordinates
TEST_F(AnnotTest_783, NegativeCoordinates_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(-100.0, -200.0, -10.0, -20.0);
    Annot annot(doc.get(), &rect);

    const PDFRectangle &r = annot.getRect();
    EXPECT_DOUBLE_EQ(r.x1, -100.0);
    EXPECT_DOUBLE_EQ(r.y1, -200.0);
    EXPECT_DOUBLE_EQ(r.x2, -10.0);
    EXPECT_DOUBLE_EQ(r.y2, -20.0);
}

// Test multiple setContents calls
TEST_F(AnnotTest_783, MultipleSetContents_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setContents(std::make_unique<GooString>("First"));
    ASSERT_NE(annot.getContents(), nullptr);
    EXPECT_STREQ(annot.getContents()->c_str(), "First");

    annot.setContents(std::make_unique<GooString>("Second"));
    ASSERT_NE(annot.getContents(), nullptr);
    EXPECT_STREQ(annot.getContents()->c_str(), "Second");
}

// Test multiple setRect calls
TEST_F(AnnotTest_783, MultipleSetRect_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setRect(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(annot.getXMin(), 1.0);

    annot.setRect(5.0, 6.0, 7.0, 8.0);
    EXPECT_DOUBLE_EQ(annot.getXMin(), 5.0);
    EXPECT_DOUBLE_EQ(annot.getYMin(), 6.0);
    EXPECT_DOUBLE_EQ(annot.getXMax(), 7.0);
    EXPECT_DOUBLE_EQ(annot.getYMax(), 8.0);
}

// Test setFlags with various flag values
TEST_F(AnnotTest_783, SetFlagsMultipleValues_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    Annot annot(doc.get(), &rect);

    annot.setFlags(0x01); // Invisible
    EXPECT_EQ(annot.getFlags(), 0x01u);

    annot.setFlags(0x02); // Hidden
    EXPECT_EQ(annot.getFlags(), 0x02u);

    annot.setFlags(0xFF);
    EXPECT_EQ(annot.getFlags(), 0xFFu);
}

// Test large coordinate values
TEST_F(AnnotTest_783, LargeCoordinates_783) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 1e10, 1e10);
    Annot annot(doc.get(), &rect);

    const PDFRectangle &r = annot.getRect();
    EXPECT_DOUBLE_EQ(r.x2, 1e10);
    EXPECT_DOUBLE_EQ(r.y2, 1e10);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
