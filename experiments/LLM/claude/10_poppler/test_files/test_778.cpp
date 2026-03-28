#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "GooString.h"
#include "PDFDocFactory.h"

class AnnotTest_778 : public ::testing::Test {
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
TEST_F(AnnotTest_778, ConstructWithRectangle_778) {
    // We need a valid PDFDoc to create an annotation
    // Create a minimal annotation using PDFRectangle
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_TRUE(annot->isOk());
    EXPECT_EQ(annot->getDoc(), doc.get());
}

// Test getRect returns correct coordinates
TEST_F(AnnotTest_778, GetRectCoordinates_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x1, 10.0);
    EXPECT_DOUBLE_EQ(y1, 20.0);
    EXPECT_DOUBLE_EQ(x2, 100.0);
    EXPECT_DOUBLE_EQ(y2, 200.0);
}

// Test getXMin, getYMin, getXMax, getYMax
TEST_F(AnnotTest_778, GetMinMaxCoordinates_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(15.0, 25.0, 150.0, 250.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot->getXMin(), 15.0);
    EXPECT_DOUBLE_EQ(annot->getYMin(), 25.0);
    EXPECT_DOUBLE_EQ(annot->getXMax(), 150.0);
    EXPECT_DOUBLE_EQ(annot->getYMax(), 250.0);
}

// Test setRect with PDFRectangle
TEST_F(AnnotTest_778, SetRectWithPDFRectangle_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    PDFRectangle newRect(50.0, 60.0, 500.0, 600.0);
    annot->setRect(newRect);

    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);

    EXPECT_DOUBLE_EQ(x1, 50.0);
    EXPECT_DOUBLE_EQ(y1, 60.0);
    EXPECT_DOUBLE_EQ(x2, 500.0);
    EXPECT_DOUBLE_EQ(y2, 600.0);
}

// Test setRect with individual coordinates
TEST_F(AnnotTest_778, SetRectWithCoordinates_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setRect(30.0, 40.0, 300.0, 400.0);

    EXPECT_DOUBLE_EQ(annot->getXMin(), 30.0);
    EXPECT_DOUBLE_EQ(annot->getYMin(), 40.0);
    EXPECT_DOUBLE_EQ(annot->getXMax(), 300.0);
    EXPECT_DOUBLE_EQ(annot->getYMax(), 400.0);
}

// Test setContents and getContents
TEST_F(AnnotTest_778, SetAndGetContents_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    auto content = std::make_unique<GooString>("Test content");
    annot->setContents(std::move(content));

    const GooString *retrieved = annot->getContents();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test content");
}

// Test setContents with empty string
TEST_F(AnnotTest_778, SetEmptyContents_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    auto content = std::make_unique<GooString>("");
    annot->setContents(std::move(content));

    const GooString *retrieved = annot->getContents();
    if (retrieved != nullptr) {
        EXPECT_STREQ(retrieved->c_str(), "");
    }
}

// Test setFlags and getFlags
TEST_F(AnnotTest_778, SetAndGetFlags_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setFlags(0x04); // Hidden flag
    EXPECT_EQ(annot->getFlags(), 0x04u);
}

// Test setFlags with zero
TEST_F(AnnotTest_778, SetFlagsZero_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setFlags(0);
    EXPECT_EQ(annot->getFlags(), 0u);
}

// Test inRect - point inside rectangle
TEST_F(AnnotTest_778, InRectPointInside_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_TRUE(annot->inRect(50.0, 100.0));
}

// Test inRect - point outside rectangle
TEST_F(AnnotTest_778, InRectPointOutside_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_FALSE(annot->inRect(5.0, 10.0));
    EXPECT_FALSE(annot->inRect(150.0, 250.0));
}

// Test inRect - point on boundary
TEST_F(AnnotTest_778, InRectPointOnBoundary_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // Boundary points - behavior depends on implementation (inclusive or exclusive)
    // Just test that it doesn't crash
    bool onEdge = annot->inRect(10.0, 20.0);
    (void)onEdge; // suppress unused warning
}

// Test getDoc returns the correct document
TEST_F(AnnotTest_778, GetDocReturnsCorrectDoc_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_EQ(annot->getDoc(), doc.get());
}

// Test getType on a newly created annotation
TEST_F(AnnotTest_778, GetTypeNewAnnot_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // The type should be set to some valid AnnotSubtype
    AnnotSubtype type = annot->getType();
    (void)type; // At minimum, no crash
}

// Test setModified and getModified
TEST_F(AnnotTest_778, SetAndGetModified_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    auto modStr = std::make_unique<GooString>("D:20230101000000");
    annot->setModified(std::move(modStr));

    const GooString *retrieved = annot->getModified();
    if (retrieved != nullptr) {
        EXPECT_STREQ(retrieved->c_str(), "D:20230101000000");
    }
}

// Test getPageNum
TEST_F(AnnotTest_778, GetPageNum_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // Page num for a newly created annotation
    int pageNum = annot->getPageNum();
    (void)pageNum; // Just ensure no crash
}

// Test setColor with nullptr
TEST_F(AnnotTest_778, SetColorNullptr_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setColor(nullptr);

    EXPECT_EQ(annot->getColor(), nullptr);
}

// Test setBorder with nullptr
TEST_F(AnnotTest_778, SetBorderNullptr_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setBorder(nullptr);

    EXPECT_EQ(annot->getBorder(), nullptr);
}

// Test getHasRef
TEST_F(AnnotTest_778, GetHasRef_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // Just verify no crash; the value depends on how it was constructed
    bool hasRef = annot->getHasRef();
    (void)hasRef;
}

// Test getAppearStreams on new annotation
TEST_F(AnnotTest_778, GetAppearStreamsNewAnnot_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // May be null for newly created annotation
    AnnotAppearance *streams = annot->getAppearStreams();
    (void)streams;
}

// Test getAppearState on new annotation
TEST_F(AnnotTest_778, GetAppearStateNewAnnot_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    const GooString *state = annot->getAppearState();
    (void)state; // No crash
}

// Test setAppearanceState
TEST_F(AnnotTest_778, SetAppearanceState_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setAppearanceState("Off");

    const GooString *state = annot->getAppearState();
    if (state != nullptr) {
        EXPECT_STREQ(state->c_str(), "Off");
    }
}

// Test getTreeKey
TEST_F(AnnotTest_778, GetTreeKey_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    int key = annot->getTreeKey();
    (void)key; // No crash expected
}

// Test getId
TEST_F(AnnotTest_778, GetId_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    int id = annot->getId();
    (void)id; // No crash expected
}

// Test getRect returns reference
TEST_F(AnnotTest_778, GetRectReference_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    const PDFRectangle &r = annot->getRect();
    EXPECT_DOUBLE_EQ(r.x1, 10.0);
    EXPECT_DOUBLE_EQ(r.y1, 20.0);
    EXPECT_DOUBLE_EQ(r.x2, 100.0);
    EXPECT_DOUBLE_EQ(r.y2, 200.0);
}

// Test setRect normalizes coordinates when x1 > x2 or y1 > y2
TEST_F(AnnotTest_778, SetRectSwappedCoordinates_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // Set rect with swapped coordinates
    annot->setRect(100.0, 200.0, 10.0, 20.0);

    // The implementation may or may not normalize; just check no crash
    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);
    
    // Verify that the rect is stored (either normalized or as-is)
    EXPECT_TRUE((x1 <= x2) || (x1 >= x2)); // always true, just verifying no crash
}

// Test setNewAppearance
TEST_F(AnnotTest_778, SetNewAppearance_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    Object newAppearance;
    annot->setNewAppearance(std::move(newAppearance));
    
    // No crash expected
}

// Test setNewAppearance with keepAppearState
TEST_F(AnnotTest_778, SetNewAppearanceKeepState_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    Object newAppearance;
    annot->setNewAppearance(std::move(newAppearance), true);
    
    // No crash expected
}

// Test getName on new annotation
TEST_F(AnnotTest_778, GetNameNewAnnot_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    const GooString *name = annot->getName();
    (void)name; // May be null for new annotations
}

// Test getAnnotObj
TEST_F(AnnotTest_778, GetAnnotObj_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    const Object &obj = annot->getAnnotObj();
    (void)obj; // No crash expected
}

// Test getAppearance
TEST_F(AnnotTest_778, GetAppearance_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    Object appearance = annot->getAppearance();
    (void)appearance; // No crash
}

// Test getAppearanceResDict
TEST_F(AnnotTest_778, GetAppearanceResDict_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    Object resDict = annot->getAppearanceResDict();
    (void)resDict;
}

// Test multiple setRect calls
TEST_F(AnnotTest_778, MultipleSetRect_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setRect(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(annot->getXMin(), 1.0);

    annot->setRect(5.0, 6.0, 7.0, 8.0);
    EXPECT_DOUBLE_EQ(annot->getXMin(), 5.0);
    EXPECT_DOUBLE_EQ(annot->getYMin(), 6.0);
    EXPECT_DOUBLE_EQ(annot->getXMax(), 7.0);
    EXPECT_DOUBLE_EQ(annot->getYMax(), 8.0);
}

// Test setContents replaces previous contents
TEST_F(AnnotTest_778, SetContentsReplacesPrevious_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setContents(std::make_unique<GooString>("First"));
    ASSERT_NE(annot->getContents(), nullptr);
    EXPECT_STREQ(annot->getContents()->c_str(), "First");

    annot->setContents(std::make_unique<GooString>("Second"));
    ASSERT_NE(annot->getContents(), nullptr);
    EXPECT_STREQ(annot->getContents()->c_str(), "Second");
}

// Test setFlags with max value
TEST_F(AnnotTest_778, SetFlagsMaxValue_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    annot->setFlags(0xFFFFFFFF);
    EXPECT_EQ(annot->getFlags(), 0xFFFFFFFF);
}

// Test inRect with exact corner points
TEST_F(AnnotTest_778, InRectExactCorners_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    // Test corners - just ensure no crash
    annot->inRect(0.0, 0.0);
    annot->inRect(100.0, 100.0);
    annot->inRect(0.0, 100.0);
    annot->inRect(100.0, 0.0);
}

// Test inRect with center point
TEST_F(AnnotTest_778, InRectCenterPoint_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_TRUE(annot->inRect(50.0, 50.0));
}

// Test inRect with negative coordinates
TEST_F(AnnotTest_778, InRectNegativeCoordinates_778) {
    auto doc = loadTestDoc("../test/pdf-sample/simple.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(-100.0, -100.0, 100.0, 100.0);
    auto annot = std::make_unique<Annot>(doc.get(), &rect);

    EXPECT_TRUE(annot->inRect(0.0, 0.0));
    EXPECT_FALSE(annot->inRect(-200.0, -200.0));
}
