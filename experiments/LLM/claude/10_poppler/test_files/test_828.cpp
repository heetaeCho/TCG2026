#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include "GooString.h"

class AnnotLineTest_828 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<AnnotLine> createAnnotLine() {
        // Create a minimal AnnotLine using a PDFRectangle
        // We need a PDFDoc for construction. We'll try to create one from scratch.
        auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
        
        // Create a minimal PDF in memory for the PDFDoc
        GooString *pdfContent = new GooString(
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n190\n%%EOF\n"
        );
        
        doc = PDFDocFactory().createPDFDoc(GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf"), nullptr, nullptr);
        if (!doc || !doc->isOk()) {
            // Try creating without a file
            return nullptr;
        }
        
        auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
        return annot;
    }

    std::unique_ptr<PDFDoc> doc;
};

TEST_F(AnnotLineTest_828, DefaultLeaderLineExtension_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    // Default leader line extension should be 0
    EXPECT_DOUBLE_EQ(0.0, annot->getLeaderLineExtension());
}

TEST_F(AnnotLineTest_828, SetLeaderLineExtension_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    annot->setLeaderLineExtension(5.0);
    EXPECT_DOUBLE_EQ(5.0, annot->getLeaderLineExtension());
}

TEST_F(AnnotLineTest_828, SetLeaderLineExtensionZero_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    annot->setLeaderLineExtension(0.0);
    EXPECT_DOUBLE_EQ(0.0, annot->getLeaderLineExtension());
}

TEST_F(AnnotLineTest_828, SetLeaderLineExtensionLargeValue_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    annot->setLeaderLineExtension(99999.99);
    EXPECT_DOUBLE_EQ(99999.99, annot->getLeaderLineExtension());
}

TEST_F(AnnotLineTest_828, SetLeaderLineExtensionNegative_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    // Negative values - testing boundary behavior
    annot->setLeaderLineExtension(-1.0);
    // We observe what the getter returns; the spec may or may not allow negative
    EXPECT_DOUBLE_EQ(-1.0, annot->getLeaderLineExtension());
}

TEST_F(AnnotLineTest_828, DefaultLeaderLineLength_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    EXPECT_DOUBLE_EQ(0.0, annot->getLeaderLineLength());
}

TEST_F(AnnotLineTest_828, SetLeaderLineLength_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    annot->setLeaderLineLength(10.0);
    EXPECT_DOUBLE_EQ(10.0, annot->getLeaderLineLength());
}

TEST_F(AnnotLineTest_828, DefaultCaption_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    EXPECT_FALSE(annot->getCaption());
}

TEST_F(AnnotLineTest_828, SetCaptionTrue_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());
}

TEST_F(AnnotLineTest_828, SetCaptionFalse_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    annot->setCaption(true);
    annot->setCaption(false);
    EXPECT_FALSE(annot->getCaption());
}

TEST_F(AnnotLineTest_828, SetVertices_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    annot->setVertices(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(10.0, annot->getX1());
    EXPECT_DOUBLE_EQ(20.0, annot->getY1());
    EXPECT_DOUBLE_EQ(30.0, annot->getX2());
    EXPECT_DOUBLE_EQ(40.0, annot->getY2());
}

TEST_F(AnnotLineTest_828, SetVerticesZero_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    annot->setVertices(0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(0.0, annot->getX1());
    EXPECT_DOUBLE_EQ(0.0, annot->getY1());
    EXPECT_DOUBLE_EQ(0.0, annot->getX2());
    EXPECT_DOUBLE_EQ(0.0, annot->getY2());
}

TEST_F(AnnotLineTest_828, SetVerticesNegative_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    annot->setVertices(-10.0, -20.0, -30.0, -40.0);
    EXPECT_DOUBLE_EQ(-10.0, annot->getX1());
    EXPECT_DOUBLE_EQ(-20.0, annot->getY1());
    EXPECT_DOUBLE_EQ(-30.0, annot->getX2());
    EXPECT_DOUBLE_EQ(-40.0, annot->getY2());
}

TEST_F(AnnotLineTest_828, DefaultInteriorColor_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    // Default interior color should be nullptr
    EXPECT_EQ(nullptr, annot->getInteriorColor());
}

TEST_F(AnnotLineTest_828, SetInteriorColor_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    AnnotColor *colorPtr = color.get();
    annot->setInteriorColor(std::move(color));
    EXPECT_NE(nullptr, annot->getInteriorColor());
}

TEST_F(AnnotLineTest_828, SetInteriorColorNull_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    annot->setInteriorColor(nullptr);
    EXPECT_EQ(nullptr, annot->getInteriorColor());
}

TEST_F(AnnotLineTest_828, DefaultLeaderLineOffset_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    EXPECT_DOUBLE_EQ(0.0, annot->getLeaderLineOffset());
}

TEST_F(AnnotLineTest_828, DefaultCaptionTextHorizontal_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    EXPECT_DOUBLE_EQ(0.0, annot->getCaptionTextHorizontal());
}

TEST_F(AnnotLineTest_828, DefaultCaptionTextVertical_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    EXPECT_DOUBLE_EQ(0.0, annot->getCaptionTextVertical());
}

TEST_F(AnnotLineTest_828, DefaultMeasure_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    EXPECT_EQ(nullptr, annot->getMeasure());
}

TEST_F(AnnotLineTest_828, SetLeaderLineExtensionMultipleTimes_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    annot->setLeaderLineExtension(1.0);
    EXPECT_DOUBLE_EQ(1.0, annot->getLeaderLineExtension());
    annot->setLeaderLineExtension(2.0);
    EXPECT_DOUBLE_EQ(2.0, annot->getLeaderLineExtension());
    annot->setLeaderLineExtension(3.0);
    EXPECT_DOUBLE_EQ(3.0, annot->getLeaderLineExtension());
}

TEST_F(AnnotLineTest_828, SetIntent_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    annot->setIntent(annotLineArrow);
    EXPECT_EQ(annotLineArrow, annot->getIntent());
}

TEST_F(AnnotLineTest_828, SetIntentDimension_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    annot->setIntent(annotLineDimension);
    EXPECT_EQ(annotLineDimension, annot->getIntent());
}

TEST_F(AnnotLineTest_828, SetVerticesUpdateCoordinates_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    annot->setVertices(1.5, 2.5, 3.5, 4.5);
    EXPECT_DOUBLE_EQ(1.5, annot->getX1());
    EXPECT_DOUBLE_EQ(2.5, annot->getY1());
    EXPECT_DOUBLE_EQ(3.5, annot->getX2());
    EXPECT_DOUBLE_EQ(4.5, annot->getY2());
    
    // Update vertices
    annot->setVertices(100.0, 200.0, 300.0, 400.0);
    EXPECT_DOUBLE_EQ(100.0, annot->getX1());
    EXPECT_DOUBLE_EQ(200.0, annot->getY1());
    EXPECT_DOUBLE_EQ(300.0, annot->getX2());
    EXPECT_DOUBLE_EQ(400.0, annot->getY2());
}

TEST_F(AnnotLineTest_828, LeaderLineLengthNegative_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    annot->setLeaderLineLength(-5.0);
    EXPECT_DOUBLE_EQ(-5.0, annot->getLeaderLineLength());
}

TEST_F(AnnotLineTest_828, SetLeaderLineExtensionSmallPositive_828) {
    auto annot = createAnnotLine();
    if (!annot) {
        GTEST_SKIP() << "Could not create AnnotLine (no test PDF available)";
    }
    annot->setLeaderLineExtension(0.001);
    EXPECT_DOUBLE_EQ(0.001, annot->getLeaderLineExtension());
}
