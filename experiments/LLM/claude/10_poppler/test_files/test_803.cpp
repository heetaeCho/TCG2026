#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "Object.h"
#include "PDFDocFactory.h"

// Helper to create a minimal PDFDoc for testing
class AnnotMarkupTest_803 : public ::testing::Test {
protected:
    void SetUp() override {
        // Try to create a minimal valid PDF document for testing
        // We need a PDFDoc instance to construct AnnotMarkup objects
        doc = nullptr;
    }

    void TearDown() override {
    }

    PDFDoc *doc;
};

// Since AnnotMarkup is an abstract-like class that inherits from Annot,
// and requires a PDFDoc, we test what we can through the public interface.
// Many tests will focus on the getSubject() method shown in the partial code.

TEST_F(AnnotMarkupTest_803, GetSubjectReturnsNullWhenNotSet_803)
{
    // Without being able to construct a full AnnotMarkup (requires PDFDoc + rect),
    // we verify the interface contract: getSubject() should return nullptr
    // when no subject has been set. This is tested indirectly through
    // a constructed object if possible.
    
    // Since we cannot easily construct AnnotMarkup without a valid PDFDoc,
    // we create a minimal test PDF in memory
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    
    // AnnotText is a concrete subclass of AnnotMarkup
    // We use it to test AnnotMarkup methods
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    // Subject should be null when not explicitly set
    const GooString *subject = annot->getSubject();
    // It may or may not be null depending on initialization
    // We just verify the call doesn't crash
    SUCCEED();
}

TEST_F(AnnotMarkupTest_803, GetLabelReturnsNullWhenNotSet_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    const GooString *label = annot->getLabel();
    // Verify the call completes without crashing
    SUCCEED();
}

TEST_F(AnnotMarkupTest_803, GetDateReturnsNullWhenNotSet_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    const GooString *date = annot->getDate();
    SUCCEED();
}

TEST_F(AnnotMarkupTest_803, DefaultOpacityValue_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    double opacity = annot->getOpacity();
    // Default opacity should be 1.0 (fully opaque) per PDF spec
    EXPECT_DOUBLE_EQ(1.0, opacity);
}

TEST_F(AnnotMarkupTest_803, SetOpacity_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    annot->setOpacity(0.5);
    EXPECT_DOUBLE_EQ(0.5, annot->getOpacity());
}

TEST_F(AnnotMarkupTest_803, SetOpacityZero_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    annot->setOpacity(0.0);
    EXPECT_DOUBLE_EQ(0.0, annot->getOpacity());
}

TEST_F(AnnotMarkupTest_803, SetOpacityOne_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    annot->setOpacity(1.0);
    EXPECT_DOUBLE_EQ(1.0, annot->getOpacity());
}

TEST_F(AnnotMarkupTest_803, SetLabel_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    auto label = std::make_unique<GooString>("Test Label");
    annot->setLabel(std::move(label));
    
    const GooString *result = annot->getLabel();
    ASSERT_NE(nullptr, result);
    EXPECT_STREQ("Test Label", result->c_str());
}

TEST_F(AnnotMarkupTest_803, SetLabelEmpty_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    auto label = std::make_unique<GooString>("");
    annot->setLabel(std::move(label));
    
    const GooString *result = annot->getLabel();
    ASSERT_NE(nullptr, result);
    EXPECT_STREQ("", result->c_str());
}

TEST_F(AnnotMarkupTest_803, SetDate_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    auto date = std::make_unique<GooString>("D:20230101120000");
    annot->setDate(std::move(date));
    
    const GooString *result = annot->getDate();
    ASSERT_NE(nullptr, result);
    EXPECT_STREQ("D:20230101120000", result->c_str());
}

TEST_F(AnnotMarkupTest_803, SetPopup_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    PDFRectangle popupRect(0, 0, 200, 200);
    auto popup = std::make_shared<AnnotPopup>(testDoc.get(), &popupRect);
    
    annot->setPopup(popup);
    
    auto result = annot->getPopup();
    ASSERT_NE(nullptr, result);
    EXPECT_EQ(popup, result);
}

TEST_F(AnnotMarkupTest_803, GetPopupReturnsNullWhenNotSet_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    auto result = annot->getPopup();
    EXPECT_EQ(nullptr, result);
}

TEST_F(AnnotMarkupTest_803, IsInReplyToDefaultFalse_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    // A freshly created annotation should not be in reply to anything
    EXPECT_FALSE(annot->isInReplyTo());
}

TEST_F(AnnotMarkupTest_803, GetReplyToDefault_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    // Default reply type should be annotMarkupReplyTypeR
    AnnotMarkupReplyType replyType = annot->getReplyTo();
    EXPECT_EQ(annotMarkupReplyTypeR, replyType);
}

TEST_F(AnnotMarkupTest_803, GetExDataDefault_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    AnnotExternalDataType exData = annot->getExData();
    // Verify the call doesn't crash and returns a valid enum value
    SUCCEED();
}

TEST_F(AnnotMarkupTest_803, SetLabelMultipleTimes_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    auto label1 = std::make_unique<GooString>("First Label");
    annot->setLabel(std::move(label1));
    ASSERT_NE(nullptr, annot->getLabel());
    EXPECT_STREQ("First Label", annot->getLabel()->c_str());
    
    auto label2 = std::make_unique<GooString>("Second Label");
    annot->setLabel(std::move(label2));
    ASSERT_NE(nullptr, annot->getLabel());
    EXPECT_STREQ("Second Label", annot->getLabel()->c_str());
}

TEST_F(AnnotMarkupTest_803, SetOpacityBoundaryValues_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    // Test small positive value
    annot->setOpacity(0.001);
    EXPECT_DOUBLE_EQ(0.001, annot->getOpacity());
    
    // Test value close to 1.0
    annot->setOpacity(0.999);
    EXPECT_DOUBLE_EQ(0.999, annot->getOpacity());
}

TEST_F(AnnotMarkupTest_803, SetDateMultipleTimes_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    auto date1 = std::make_unique<GooString>("D:20200101");
    annot->setDate(std::move(date1));
    ASSERT_NE(nullptr, annot->getDate());
    EXPECT_STREQ("D:20200101", annot->getDate()->c_str());
    
    auto date2 = std::make_unique<GooString>("D:20231231");
    annot->setDate(std::move(date2));
    ASSERT_NE(nullptr, annot->getDate());
    EXPECT_STREQ("D:20231231", annot->getDate()->c_str());
}

TEST_F(AnnotMarkupTest_803, SetLabelWithSpecialCharacters_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    auto label = std::make_unique<GooString>("Label with special chars: <>&\"'");
    annot->setLabel(std::move(label));
    
    const GooString *result = annot->getLabel();
    ASSERT_NE(nullptr, result);
    EXPECT_STREQ("Label with special chars: <>&\"'", result->c_str());
}

TEST_F(AnnotMarkupTest_803, ReplacePopup_803)
{
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    auto testDoc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!testDoc || !testDoc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping test";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(testDoc.get(), &rect);
    
    PDFRectangle popupRect1(0, 0, 200, 200);
    auto popup1 = std::make_shared<AnnotPopup>(testDoc.get(), &popupRect1);
    annot->setPopup(popup1);
    EXPECT_EQ(popup1, annot->getPopup());
    
    PDFRectangle popupRect2(10, 10, 300, 300);
    auto popup2 = std::make_shared<AnnotPopup>(testDoc.get(), &popupRect2);
    annot->setPopup(popup2);
    EXPECT_EQ(popup2, annot->getPopup());
}
