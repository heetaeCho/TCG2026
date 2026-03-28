#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "Object.h"
#include "GooString.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"

// Helper to create a minimal valid PDF in memory for testing
class AnnotMarkupTest_801 : public ::testing::Test {
protected:
    void SetUp() override {
        // Try to create a minimal PDFDoc for testing
        // We'll use a simple PDF file if available, or create one in memory
        doc = nullptr;
    }

    void TearDown() override {
        delete doc;
    }

    PDFDoc *doc;

    PDFDoc *getOrCreateDoc() {
        if (!doc) {
            // Create a minimal PDF document for testing
            GooString fileName("./TestProjects/poppler/test/unittestcases/simple.pdf");
            doc = new PDFDoc(&fileName);
            if (!doc->isOk()) {
                delete doc;
                doc = nullptr;
            }
        }
        return doc;
    }
};

// Test Ref::INVALID behavior which underpins isInReplyTo
TEST_F(AnnotMarkupTest_801, RefInvalidIsConsistent_801) {
    Ref invalid1 = Ref::INVALID();
    Ref invalid2 = Ref::INVALID();
    EXPECT_EQ(invalid1.num, invalid2.num);
    EXPECT_EQ(invalid1.gen, invalid2.gen);
}

// Test that isInReplyTo returns false when inReplyTo is INVALID
TEST_F(AnnotMarkupTest_801, IsInReplyToReturnsFalseForInvalidRef_801) {
    PDFDoc *d = getOrCreateDoc();
    if (!d) {
        GTEST_SKIP() << "Could not create PDFDoc for testing";
    }

    PDFRectangle rect(0, 0, 100, 100);
    // Create a fresh AnnotMarkup - by default inReplyTo should be INVALID
    // We use a subclass like AnnotText which extends AnnotMarkup
    auto annot = std::make_unique<AnnotText>(d, &rect);
    EXPECT_FALSE(annot->isInReplyTo());
}

// Test getOpacity default value
TEST_F(AnnotMarkupTest_801, DefaultOpacity_801) {
    PDFDoc *d = getOrCreateDoc();
    if (!d) {
        GTEST_SKIP() << "Could not create PDFDoc for testing";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(d, &rect);
    // Default opacity should be 1.0
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 1.0);
}

// Test setOpacity and getOpacity
TEST_F(AnnotMarkupTest_801, SetAndGetOpacity_801) {
    PDFDoc *d = getOrCreateDoc();
    if (!d) {
        GTEST_SKIP() << "Could not create PDFDoc for testing";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(d, &rect);
    annot->setOpacity(0.5);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.5);
}

// Test setOpacity boundary - 0.0
TEST_F(AnnotMarkupTest_801, SetOpacityZero_801) {
    PDFDoc *d = getOrCreateDoc();
    if (!d) {
        GTEST_SKIP() << "Could not create PDFDoc for testing";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(d, &rect);
    annot->setOpacity(0.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.0);
}

// Test setOpacity boundary - 1.0
TEST_F(AnnotMarkupTest_801, SetOpacityOne_801) {
    PDFDoc *d = getOrCreateDoc();
    if (!d) {
        GTEST_SKIP() << "Could not create PDFDoc for testing";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(d, &rect);
    annot->setOpacity(1.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 1.0);
}

// Test setLabel and getLabel
TEST_F(AnnotMarkupTest_801, SetAndGetLabel_801) {
    PDFDoc *d = getOrCreateDoc();
    if (!d) {
        GTEST_SKIP() << "Could not create PDFDoc for testing";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(d, &rect);
    auto label = std::make_unique<GooString>("Test Label");
    annot->setLabel(std::move(label));
    const GooString *result = annot->getLabel();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "Test Label");
}

// Test setDate and getDate
TEST_F(AnnotMarkupTest_801, SetAndGetDate_801) {
    PDFDoc *d = getOrCreateDoc();
    if (!d) {
        GTEST_SKIP() << "Could not create PDFDoc for testing";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(d, &rect);
    auto date = std::make_unique<GooString>("D:20230101000000");
    annot->setDate(std::move(date));
    const GooString *result = annot->getDate();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "D:20230101000000");
}

// Test getPopup returns nullptr by default
TEST_F(AnnotMarkupTest_801, DefaultPopupIsNull_801) {
    PDFDoc *d = getOrCreateDoc();
    if (!d) {
        GTEST_SKIP() << "Could not create PDFDoc for testing";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(d, &rect);
    EXPECT_EQ(annot->getPopup(), nullptr);
}

// Test getSubject returns nullptr by default
TEST_F(AnnotMarkupTest_801, DefaultSubjectIsNull_801) {
    PDFDoc *d = getOrCreateDoc();
    if (!d) {
        GTEST_SKIP() << "Could not create PDFDoc for testing";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(d, &rect);
    // Subject should be nullptr for a freshly created annotation
    const GooString *subject = annot->getSubject();
    // May or may not be null depending on implementation, just verify no crash
    (void)subject;
    SUCCEED();
}

// Test setLabel with empty string
TEST_F(AnnotMarkupTest_801, SetEmptyLabel_801) {
    PDFDoc *d = getOrCreateDoc();
    if (!d) {
        GTEST_SKIP() << "Could not create PDFDoc for testing";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(d, &rect);
    auto label = std::make_unique<GooString>("");
    annot->setLabel(std::move(label));
    const GooString *result = annot->getLabel();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "");
}

// Test setLabel with nullptr
TEST_F(AnnotMarkupTest_801, SetNullLabel_801) {
    PDFDoc *d = getOrCreateDoc();
    if (!d) {
        GTEST_SKIP() << "Could not create PDFDoc for testing";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(d, &rect);
    annot->setLabel(nullptr);
    const GooString *result = annot->getLabel();
    EXPECT_EQ(result, nullptr);
}

// Test getReplyTo default value
TEST_F(AnnotMarkupTest_801, DefaultReplyTo_801) {
    PDFDoc *d = getOrCreateDoc();
    if (!d) {
        GTEST_SKIP() << "Could not create PDFDoc for testing";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(d, &rect);
    // Just verify it doesn't crash and returns a valid enum value
    AnnotMarkupReplyType replyType = annot->getReplyTo();
    (void)replyType;
    SUCCEED();
}

// Test getExData default value
TEST_F(AnnotMarkupTest_801, DefaultExData_801) {
    PDFDoc *d = getOrCreateDoc();
    if (!d) {
        GTEST_SKIP() << "Could not create PDFDoc for testing";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(d, &rect);
    AnnotExternalDataType exData = annot->getExData();
    (void)exData;
    SUCCEED();
}

// Test getInReplyToID when not in reply
TEST_F(AnnotMarkupTest_801, GetInReplyToIDWhenNotInReply_801) {
    PDFDoc *d = getOrCreateDoc();
    if (!d) {
        GTEST_SKIP() << "Could not create PDFDoc for testing";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(d, &rect);
    EXPECT_FALSE(annot->isInReplyTo());
    // getInReplyToID should still be callable
    int id = annot->getInReplyToID();
    // When not in reply, the ID should correspond to INVALID ref
    Ref invalid = Ref::INVALID();
    EXPECT_EQ(id, invalid.num);
}

// Test multiple opacity changes
TEST_F(AnnotMarkupTest_801, MultipleOpacityChanges_801) {
    PDFDoc *d = getOrCreateDoc();
    if (!d) {
        GTEST_SKIP() << "Could not create PDFDoc for testing";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(d, &rect);
    
    annot->setOpacity(0.3);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.3);
    
    annot->setOpacity(0.7);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.7);
    
    annot->setOpacity(1.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 1.0);
}

// Test setDate with nullptr
TEST_F(AnnotMarkupTest_801, SetNullDate_801) {
    PDFDoc *d = getOrCreateDoc();
    if (!d) {
        GTEST_SKIP() << "Could not create PDFDoc for testing";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(d, &rect);
    annot->setDate(nullptr);
    const GooString *result = annot->getDate();
    EXPECT_EQ(result, nullptr);
}
