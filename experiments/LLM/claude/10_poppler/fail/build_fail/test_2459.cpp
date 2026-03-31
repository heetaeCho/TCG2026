#include <gtest/gtest.h>
#include <memory>
#include "poppler/Annot.h"
#include "poppler/Page.h"
#include "poppler/PDFDoc.h"
#include "poppler/GlobalParams.h"
#include "glib/poppler-page.h"

// Forward declaration of the function under test
extern AnnotQuadrilaterals *_page_new_quads_unrotated(Page *page, AnnotQuadrilaterals *quads);

class PageNewQuadsUnrotatedTest_2459 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<AnnotQuadrilaterals> makeQuads(int count, double baseVal = 1.0)
    {
        auto quadsArray = std::make_unique<AnnotQuadrilaterals::AnnotQuadrilateral[]>(count);
        for (int i = 0; i < count; i++) {
            double offset = i * 10.0;
            quadsArray[i] = AnnotQuadrilaterals::AnnotQuadrilateral(
                baseVal + offset, baseVal + 1.0 + offset,
                baseVal + 2.0 + offset, baseVal + 3.0 + offset,
                baseVal + 4.0 + offset, baseVal + 5.0 + offset,
                baseVal + 6.0 + offset, baseVal + 7.0 + offset);
        }
        return std::make_unique<AnnotQuadrilaterals>(std::move(quadsArray), count);
    }
};

TEST_F(PageNewQuadsUnrotatedTest_2459, ReturnsNonNullForValidInput_2459)
{
    // Create a simple PDF document to get a page with 0 rotation
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto inputQuads = makeQuads(1);
    AnnotQuadrilaterals *result = _page_new_quads_unrotated(page, inputQuads.get());

    ASSERT_NE(result, nullptr);
    delete result;
}

TEST_F(PageNewQuadsUnrotatedTest_2459, PreservesQuadrilateralsLength_2459)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const int numQuads = 3;
    auto inputQuads = makeQuads(numQuads);
    AnnotQuadrilaterals *result = _page_new_quads_unrotated(page, inputQuads.get());

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), numQuads);
    delete result;
}

TEST_F(PageNewQuadsUnrotatedTest_2459, SingleQuadPreservesLengthOne_2459)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto inputQuads = makeQuads(1);
    AnnotQuadrilaterals *result = _page_new_quads_unrotated(page, inputQuads.get());

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), 1);
    delete result;
}

TEST_F(PageNewQuadsUnrotatedTest_2459, ZeroRotationPreservesCoordinates_2459)
{
    // For a page with 0 rotation, unrotation should be identity
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    if (page->getRotate() != 0) {
        GTEST_SKIP() << "Page rotation is not 0, skipping identity test";
    }

    double x1 = 10.0, y1 = 20.0, x2 = 30.0, y2 = 40.0;
    double x3 = 50.0, y3 = 60.0, x4 = 70.0, y4 = 80.0;

    auto quadsArray = std::make_unique<AnnotQuadrilaterals::AnnotQuadrilateral[]>(1);
    quadsArray[0] = AnnotQuadrilaterals::AnnotQuadrilateral(x1, y1, x2, y2, x3, y3, x4, y4);
    auto inputQuads = std::make_unique<AnnotQuadrilaterals>(std::move(quadsArray), 1);

    AnnotQuadrilaterals *result = _page_new_quads_unrotated(page, inputQuads.get());

    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->getX1(0), x1);
    EXPECT_DOUBLE_EQ(result->getY1(0), y1);
    EXPECT_DOUBLE_EQ(result->getX2(0), x2);
    EXPECT_DOUBLE_EQ(result->getY2(0), y2);
    EXPECT_DOUBLE_EQ(result->getX3(0), x3);
    EXPECT_DOUBLE_EQ(result->getY3(0), y3);
    EXPECT_DOUBLE_EQ(result->getX4(0), x4);
    EXPECT_DOUBLE_EQ(result->getY4(0), y4);
    delete result;
}

TEST_F(PageNewQuadsUnrotatedTest_2459, MultipleQuadsAllPreserved_2459)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const int numQuads = 5;
    auto inputQuads = makeQuads(numQuads, 100.0);
    AnnotQuadrilaterals *result = _page_new_quads_unrotated(page, inputQuads.get());

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), numQuads);

    // Each quad should have valid (finite) coordinate values
    for (int i = 0; i < numQuads; i++) {
        EXPECT_TRUE(std::isfinite(result->getX1(i)));
        EXPECT_TRUE(std::isfinite(result->getY1(i)));
        EXPECT_TRUE(std::isfinite(result->getX2(i)));
        EXPECT_TRUE(std::isfinite(result->getY2(i)));
        EXPECT_TRUE(std::isfinite(result->getX3(i)));
        EXPECT_TRUE(std::isfinite(result->getY3(i)));
        EXPECT_TRUE(std::isfinite(result->getX4(i)));
        EXPECT_TRUE(std::isfinite(result->getY4(i)));
    }
    delete result;
}

TEST_F(PageNewQuadsUnrotatedTest_2459, ZeroCoordinatesHandled_2459)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto quadsArray = std::make_unique<AnnotQuadrilaterals::AnnotQuadrilateral[]>(1);
    quadsArray[0] = AnnotQuadrilaterals::AnnotQuadrilateral(0, 0, 0, 0, 0, 0, 0, 0);
    auto inputQuads = std::make_unique<AnnotQuadrilaterals>(std::move(quadsArray), 1);

    AnnotQuadrilaterals *result = _page_new_quads_unrotated(page, inputQuads.get());

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), 1);
    EXPECT_TRUE(std::isfinite(result->getX1(0)));
    EXPECT_TRUE(std::isfinite(result->getY1(0)));
    delete result;
}

TEST_F(PageNewQuadsUnrotatedTest_2459, NegativeCoordinatesHandled_2459)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto quadsArray = std::make_unique<AnnotQuadrilaterals::AnnotQuadrilateral[]>(1);
    quadsArray[0] = AnnotQuadrilaterals::AnnotQuadrilateral(-10, -20, -30, -40, -50, -60, -70, -80);
    auto inputQuads = std::make_unique<AnnotQuadrilaterals>(std::move(quadsArray), 1);

    AnnotQuadrilaterals *result = _page_new_quads_unrotated(page, inputQuads.get());

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), 1);
    EXPECT_TRUE(std::isfinite(result->getX1(0)));
    EXPECT_TRUE(std::isfinite(result->getY1(0)));
    delete result;
}

TEST_F(PageNewQuadsUnrotatedTest_2459, LargeCoordinatesHandled_2459)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto quadsArray = std::make_unique<AnnotQuadrilaterals::AnnotQuadrilateral[]>(1);
    quadsArray[0] = AnnotQuadrilaterals::AnnotQuadrilateral(1e6, 1e6, 1e6, 1e6, 1e6, 1e6, 1e6, 1e6);
    auto inputQuads = std::make_unique<AnnotQuadrilaterals>(std::move(quadsArray), 1);

    AnnotQuadrilaterals *result = _page_new_quads_unrotated(page, inputQuads.get());

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), 1);
    EXPECT_TRUE(std::isfinite(result->getX1(0)));
    delete result;
}

TEST_F(PageNewQuadsUnrotatedTest_2459, ResultIsIndependentOfInput_2459)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    if (!doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto inputQuads = makeQuads(2, 50.0);
    AnnotQuadrilaterals *result = _page_new_quads_unrotated(page, inputQuads.get());

    ASSERT_NE(result, nullptr);

    // The result should be a separate object
    EXPECT_NE(result, inputQuads.get());
    EXPECT_EQ(result->getQuadrilateralsLength(), 2);

    delete result;
}
