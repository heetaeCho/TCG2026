#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "Object.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"

class AnnotMarkupTest_800 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We need a valid PDFDoc to create annotations
        // Try to create a minimal document for testing
    }

    std::unique_ptr<PDFDoc> createTestDoc(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test getDate returns the date that was set via setDate with GooString
TEST_F(AnnotMarkupTest_800, GetDateReturnsSetDate_800) {
    // We need a valid PDFDoc; use a test PDF if available
    // Since we can't easily create a PDFDoc without a file, we test with
    // available constructor using PDFRectangle
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    // AnnotText is a concrete subclass of AnnotMarkup
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // Initially date might be null or empty
    // Set a date
    auto dateStr = std::make_unique<GooString>("D:20230101120000");
    annot->setDate(std::move(dateStr));

    const GooString *result = annot->getDate();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "D:20230101120000");
}

// Test getDate returns nullptr when no date is set (or default)
TEST_F(AnnotMarkupTest_800, GetDateDefaultValue_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // The date after construction from rect - it may have a default or be null
    // We just verify it doesn't crash
    const GooString *result = annot->getDate();
    // Date might be set to current date or null depending on implementation
    // Just verify no crash
    (void)result;
}

// Test setDate with nullptr/empty
TEST_F(AnnotMarkupTest_800, SetDateWithNullptr_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setDate(nullptr);
    const GooString *result = annot->getDate();
    EXPECT_EQ(result, nullptr);
}

// Test setLabel and getLabel
TEST_F(AnnotMarkupTest_800, SetAndGetLabel_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
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

// Test getLabel default
TEST_F(AnnotMarkupTest_800, GetLabelDefault_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // Label may default to something or nullptr
    const GooString *result = annot->getLabel();
    (void)result; // Just verify no crash
}

// Test setOpacity and getOpacity
TEST_F(AnnotMarkupTest_800, SetAndGetOpacity_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(0.5);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.5);
}

// Test opacity default value
TEST_F(AnnotMarkupTest_800, GetOpacityDefault_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // Default opacity is typically 1.0
    double opacity = annot->getOpacity();
    EXPECT_DOUBLE_EQ(opacity, 1.0);
}

// Test opacity boundary - 0.0
TEST_F(AnnotMarkupTest_800, SetOpacityZero_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(0.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.0);
}

// Test opacity boundary - 1.0
TEST_F(AnnotMarkupTest_800, SetOpacityOne_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(1.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 1.0);
}

// Test setPopup and getPopup
TEST_F(AnnotMarkupTest_800, SetAndGetPopup_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    PDFRectangle popupRect(10, 10, 200, 200);
    auto popup = std::make_shared<AnnotPopup>(doc.get(), &popupRect);
    annot->setPopup(popup);

    auto result = annot->getPopup();
    EXPECT_EQ(result, popup);
}

// Test getPopup when no popup is set
TEST_F(AnnotMarkupTest_800, GetPopupDefault_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto result = annot->getPopup();
    EXPECT_EQ(result, nullptr);
}

// Test getSubject default
TEST_F(AnnotMarkupTest_800, GetSubjectDefault_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    const GooString *subject = annot->getSubject();
    // Subject is typically null by default for a newly created annotation
    (void)subject;
}

// Test isInReplyTo default
TEST_F(AnnotMarkupTest_800, IsInReplyToDefault_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // A newly created annotation should not be in reply to anything
    EXPECT_FALSE(annot->isInReplyTo());
}

// Test getReplyTo default
TEST_F(AnnotMarkupTest_800, GetReplyToDefault_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    AnnotMarkupReplyType replyTo = annot->getReplyTo();
    // Default should be annotMarkupReplyTypeR
    EXPECT_EQ(replyTo, AnnotMarkup::replyTypeR);
}

// Test setDate overwrite existing date
TEST_F(AnnotMarkupTest_800, SetDateOverwriteExisting_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto date1 = std::make_unique<GooString>("D:20220101000000");
    annot->setDate(std::move(date1));
    ASSERT_NE(annot->getDate(), nullptr);
    EXPECT_STREQ(annot->getDate()->c_str(), "D:20220101000000");

    auto date2 = std::make_unique<GooString>("D:20230601120000");
    annot->setDate(std::move(date2));
    ASSERT_NE(annot->getDate(), nullptr);
    EXPECT_STREQ(annot->getDate()->c_str(), "D:20230601120000");
}

// Test setLabel overwrite existing label
TEST_F(AnnotMarkupTest_800, SetLabelOverwriteExisting_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto label1 = std::make_unique<GooString>("First Label");
    annot->setLabel(std::move(label1));
    ASSERT_NE(annot->getLabel(), nullptr);
    EXPECT_STREQ(annot->getLabel()->c_str(), "First Label");

    auto label2 = std::make_unique<GooString>("Second Label");
    annot->setLabel(std::move(label2));
    ASSERT_NE(annot->getLabel(), nullptr);
    EXPECT_STREQ(annot->getLabel()->c_str(), "Second Label");
}

// Test setLabel with nullptr
TEST_F(AnnotMarkupTest_800, SetLabelWithNullptr_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setLabel(nullptr);
    const GooString *result = annot->getLabel();
    EXPECT_EQ(result, nullptr);
}

// Test setDate with empty string
TEST_F(AnnotMarkupTest_800, SetDateWithEmptyString_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto dateStr = std::make_unique<GooString>("");
    annot->setDate(std::move(dateStr));

    const GooString *result = annot->getDate();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "");
}

// Test setPopup with nullptr (clearing popup)
TEST_F(AnnotMarkupTest_800, SetPopupWithNullptr_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setPopup(nullptr);
    auto result = annot->getPopup();
    EXPECT_EQ(result, nullptr);
}

// Test multiple opacity changes
TEST_F(AnnotMarkupTest_800, MultipleOpacityChanges_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
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

// Test getExData default
TEST_F(AnnotMarkupTest_800, GetExDataDefault_800) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    AnnotExternalDataType exData = annot->getExData();
    // Default should indicate no external data
    (void)exData;
}
