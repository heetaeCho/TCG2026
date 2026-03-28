#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"

class AnnotMarkupTest_797 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We need a valid PDFDoc to create annotations
        // Try to create a minimal test environment
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> createTestDoc() {
        // Create a simple PDF document from a minimal PDF file or use a helper
        GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
        auto doc = std::unique_ptr<PDFDoc>(new PDFDoc(&fileName));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test getLabel returns the label that was set
TEST_F(AnnotMarkupTest_797, GetLabelReturnsSetLabel_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto label = std::make_unique<GooString>("Test Label");
    annot->setLabel(std::move(label));

    const GooString *result = annot->getLabel();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "Test Label");
}

// Test getLabel returns nullptr or empty when no label set on fresh annotation
TEST_F(AnnotMarkupTest_797, GetLabelDefaultValue_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // Default label may be nullptr or empty
    const GooString *result = annot->getLabel();
    // Just check it doesn't crash - the default could be nullptr or a valid string
    (void)result;
}

// Test setLabel with empty string
TEST_F(AnnotMarkupTest_797, SetLabelEmptyString_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto label = std::make_unique<GooString>("");
    annot->setLabel(std::move(label));

    const GooString *result = annot->getLabel();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "");
}

// Test setLabel replaces previous label
TEST_F(AnnotMarkupTest_797, SetLabelReplacesExisting_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto label1 = std::make_unique<GooString>("First Label");
    annot->setLabel(std::move(label1));

    auto label2 = std::make_unique<GooString>("Second Label");
    annot->setLabel(std::move(label2));

    const GooString *result = annot->getLabel();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "Second Label");
}

// Test getOpacity default value
TEST_F(AnnotMarkupTest_797, GetOpacityDefaultValue_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    double opacity = annot->getOpacity();
    // Default opacity is typically 1.0
    EXPECT_DOUBLE_EQ(opacity, 1.0);
}

// Test setOpacity and getOpacity
TEST_F(AnnotMarkupTest_797, SetAndGetOpacity_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(0.5);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.5);
}

// Test setOpacity with boundary value 0.0
TEST_F(AnnotMarkupTest_797, SetOpacityZero_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(0.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.0);
}

// Test setOpacity with boundary value 1.0
TEST_F(AnnotMarkupTest_797, SetOpacityOne_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(1.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 1.0);
}

// Test getDate default
TEST_F(AnnotMarkupTest_797, GetDateDefault_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    const GooString *date = annot->getDate();
    // Default date may be nullptr
    (void)date;
}

// Test setDate and getDate
TEST_F(AnnotMarkupTest_797, SetAndGetDate_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto date = std::make_unique<GooString>("D:20230101120000");
    annot->setDate(std::move(date));

    const GooString *result = annot->getDate();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "D:20230101120000");
}

// Test getPopup default
TEST_F(AnnotMarkupTest_797, GetPopupDefault_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    std::shared_ptr<AnnotPopup> popup = annot->getPopup();
    // Default popup is typically nullptr
    EXPECT_EQ(popup, nullptr);
}

// Test setPopup and getPopup
TEST_F(AnnotMarkupTest_797, SetAndGetPopup_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    PDFRectangle popupRect(0, 0, 200, 200);
    auto popup = std::make_shared<AnnotPopup>(doc.get(), &popupRect);

    annot->setPopup(popup);

    std::shared_ptr<AnnotPopup> result = annot->getPopup();
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result, popup);
}

// Test getSubject default
TEST_F(AnnotMarkupTest_797, GetSubjectDefault_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    const GooString *subject = annot->getSubject();
    // Default subject may be nullptr
    (void)subject;
}

// Test isInReplyTo default
TEST_F(AnnotMarkupTest_797, IsInReplyToDefault_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // Fresh annotation should not be in reply to anything
    EXPECT_FALSE(annot->isInReplyTo());
}

// Test getReplyTo default
TEST_F(AnnotMarkupTest_797, GetReplyToDefault_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    AnnotMarkupReplyType replyTo = annot->getReplyTo();
    // Default reply type is typically replyTypeR
    EXPECT_EQ(replyTo, AnnotMarkup::replyTypeR);
}

// Test getExData default
TEST_F(AnnotMarkupTest_797, GetExDataDefault_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    AnnotExternalDataType exData = annot->getExData();
    // Check default exData type
    EXPECT_EQ(exData, AnnotMarkup::externalDataMarkupUnknown);
}

// Test setLabel with long string
TEST_F(AnnotMarkupTest_797, SetLabelLongString_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    std::string longStr(1000, 'A');
    auto label = std::make_unique<GooString>(longStr.c_str());
    annot->setLabel(std::move(label));

    const GooString *result = annot->getLabel();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(std::string(result->c_str()), longStr);
}

// Test multiple opacity changes
TEST_F(AnnotMarkupTest_797, MultipleOpacityChanges_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(0.1);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.1);

    annot->setOpacity(0.9);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.9);

    annot->setOpacity(0.5);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.5);
}

// Test setDate with empty string
TEST_F(AnnotMarkupTest_797, SetDateEmptyString_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto date = std::make_unique<GooString>("");
    annot->setDate(std::move(date));

    const GooString *result = annot->getDate();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "");
}

// Test setLabel with nullptr (moving a null unique_ptr)
TEST_F(AnnotMarkupTest_797, SetLabelNullptr_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // First set a valid label
    auto label = std::make_unique<GooString>("Test");
    annot->setLabel(std::move(label));
    ASSERT_NE(annot->getLabel(), nullptr);

    // Now set nullptr
    std::unique_ptr<GooString> nullLabel;
    annot->setLabel(std::move(nullLabel));

    // After setting null, getLabel may return nullptr
    const GooString *result = annot->getLabel();
    (void)result; // Just ensure it doesn't crash
}

// Test replacing popup
TEST_F(AnnotMarkupTest_797, ReplacePopup_797) {
    auto doc = createTestDoc();
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    PDFRectangle popupRect1(0, 0, 200, 200);
    auto popup1 = std::make_shared<AnnotPopup>(doc.get(), &popupRect1);
    annot->setPopup(popup1);
    EXPECT_EQ(annot->getPopup(), popup1);

    PDFRectangle popupRect2(10, 10, 300, 300);
    auto popup2 = std::make_shared<AnnotPopup>(doc.get(), &popupRect2);
    annot->setPopup(popup2);
    EXPECT_EQ(annot->getPopup(), popup2);
    EXPECT_NE(annot->getPopup(), popup1);
}
