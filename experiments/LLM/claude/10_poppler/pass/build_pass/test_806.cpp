#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include <memory>

class AnnotTextTest_806 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

// Test that a newly created AnnotText via rect constructor can be queried for open state
TEST_F(AnnotTextTest_806, DefaultOpenState_806)
{
    // Create a minimal PDF document for testing
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // getOpen should return a bool value (default is typically false)
    bool openState = annot->getOpen();
    EXPECT_FALSE(openState);
}

// Test setOpen(true) makes getOpen return true
TEST_F(AnnotTextTest_806, SetOpenTrue_806)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpen(true);
    EXPECT_TRUE(annot->getOpen());
}

// Test setOpen(false) makes getOpen return false
TEST_F(AnnotTextTest_806, SetOpenFalse_806)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpen(false);
    EXPECT_FALSE(annot->getOpen());
}

// Test toggling open state
TEST_F(AnnotTextTest_806, ToggleOpenState_806)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpen(true);
    EXPECT_TRUE(annot->getOpen());

    annot->setOpen(false);
    EXPECT_FALSE(annot->getOpen());

    annot->setOpen(true);
    EXPECT_TRUE(annot->getOpen());
}

// Test getIcon returns a valid string
TEST_F(AnnotTextTest_806, DefaultIcon_806)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    const std::string &icon = annot->getIcon();
    // Default icon is typically "Note"
    EXPECT_FALSE(icon.empty());
}

// Test setIcon changes the icon
TEST_F(AnnotTextTest_806, SetIcon_806)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setIcon("Comment");
    EXPECT_EQ(annot->getIcon(), "Comment");
}

// Test setIcon with different icon names
TEST_F(AnnotTextTest_806, SetIconVariousNames_806)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setIcon("Note");
    EXPECT_EQ(annot->getIcon(), "Note");

    annot->setIcon("Help");
    EXPECT_EQ(annot->getIcon(), "Help");

    annot->setIcon("Key");
    EXPECT_EQ(annot->getIcon(), "Key");

    annot->setIcon("NewParagraph");
    EXPECT_EQ(annot->getIcon(), "NewParagraph");

    annot->setIcon("Paragraph");
    EXPECT_EQ(annot->getIcon(), "Paragraph");

    annot->setIcon("Insert");
    EXPECT_EQ(annot->getIcon(), "Insert");
}

// Test setIcon with empty string
TEST_F(AnnotTextTest_806, SetIconEmptyString_806)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setIcon("");
    EXPECT_EQ(annot->getIcon(), "");
}

// Test getState returns a valid state
TEST_F(AnnotTextTest_806, DefaultState_806)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // Just verify getState doesn't crash and returns some value
    auto state = annot->getState();
    (void)state; // suppress unused variable warning
    SUCCEED();
}

// Test setting open multiple times to the same value
TEST_F(AnnotTextTest_806, SetOpenIdempotent_806)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpen(true);
    annot->setOpen(true);
    EXPECT_TRUE(annot->getOpen());

    annot->setOpen(false);
    annot->setOpen(false);
    EXPECT_FALSE(annot->getOpen());
}

// Test setIcon overwriting with a custom non-standard name
TEST_F(AnnotTextTest_806, SetIconCustomName_806)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setIcon("CustomIconName");
    EXPECT_EQ(annot->getIcon(), "CustomIconName");
}

// Test creating annotation with different rectangle coordinates
TEST_F(AnnotTextTest_806, DifferentRectCoordinates_806)
{
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    PDFRectangle rect(0, 0, 50, 50);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
    EXPECT_FALSE(annot->getOpen());

    PDFRectangle rect2(0, 0, 1000, 1000);
    auto annot2 = std::make_unique<AnnotText>(doc.get(), &rect2);
    EXPECT_FALSE(annot2->getOpen());
}
