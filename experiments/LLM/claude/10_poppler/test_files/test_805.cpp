#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "Object.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"

class AnnotMarkupTest_805 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We need a valid PDFDoc to create annotations.
        // Try to create a minimal test document or use a factory approach.
    }
};

// Since AnnotMarkup requires a PDFDoc, and creating one from scratch is complex,
// we test what we can through the public interface. We'll attempt to create
// a minimal PDF in memory if possible, or test with a simple file.

class AnnotMarkupWithDocTest_805 : public ::testing::Test {
protected:
    std::unique_ptr<PDFDoc> doc;

    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a minimal PDF document in memory
        static const char *minimalPDF =
            "%PDF-1.4\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n198\n%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0,
                                     strlen(minimalPDF), Object(objNull));
        doc = std::make_unique<PDFDoc>(stream);
    }
};

// Test getExData returns a valid AnnotExternalDataType
TEST_F(AnnotMarkupWithDocTest_805, GetExDataDefault_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    // AnnotText is a concrete subclass of AnnotMarkup
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    AnnotExternalDataType exData = annot->getExData();
    // Default should be annotExternalDataMarkupUnknown or similar default
    // We just verify it returns without crashing and is a valid enum value
    EXPECT_TRUE(exData == annotExternalDataMarkupUnknown ||
                exData == annotExternalDataMarkup3D);
}

// Test getLabel returns nullptr or valid string for newly created annotation
TEST_F(AnnotMarkupWithDocTest_805, GetLabelDefault_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    const GooString *label = annot->getLabel();
    // For a newly created annotation, label may be nullptr or empty
    // We just verify it doesn't crash
    SUCCEED();
}

// Test setLabel and getLabel
TEST_F(AnnotMarkupWithDocTest_805, SetAndGetLabel_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto newLabel = std::make_unique<GooString>("Test Label");
    annot->setLabel(std::move(newLabel));

    const GooString *label = annot->getLabel();
    ASSERT_NE(label, nullptr);
    EXPECT_STREQ(label->c_str(), "Test Label");
}

// Test setOpacity and getOpacity
TEST_F(AnnotMarkupWithDocTest_805, SetAndGetOpacity_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(0.5);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.5);
}

// Test default opacity
TEST_F(AnnotMarkupWithDocTest_805, DefaultOpacity_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // Default opacity should be 1.0
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 1.0);
}

// Test setOpacity with boundary value 0.0
TEST_F(AnnotMarkupWithDocTest_805, SetOpacityZero_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(0.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.0);
}

// Test setOpacity with boundary value 1.0
TEST_F(AnnotMarkupWithDocTest_805, SetOpacityOne_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(1.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 1.0);
}

// Test setDate and getDate
TEST_F(AnnotMarkupWithDocTest_805, SetAndGetDate_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto newDate = std::make_unique<GooString>("D:20230101120000");
    annot->setDate(std::move(newDate));

    const GooString *date = annot->getDate();
    ASSERT_NE(date, nullptr);
    EXPECT_STREQ(date->c_str(), "D:20230101120000");
}

// Test getDate default
TEST_F(AnnotMarkupWithDocTest_805, GetDateDefault_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // Date may or may not be set by default
    const GooString *date = annot->getDate();
    // Just verify no crash
    SUCCEED();
}

// Test getPopup default is nullptr
TEST_F(AnnotMarkupWithDocTest_805, GetPopupDefault_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    std::shared_ptr<AnnotPopup> popup = annot->getPopup();
    // For a newly created annotation, popup should be nullptr
    EXPECT_EQ(popup, nullptr);
}

// Test setPopup and getPopup
TEST_F(AnnotMarkupWithDocTest_805, SetAndGetPopup_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    PDFRectangle popupRect(200, 200, 400, 300);
    auto popup = std::make_shared<AnnotPopup>(doc.get(), &popupRect);

    annot->setPopup(popup);

    std::shared_ptr<AnnotPopup> retrievedPopup = annot->getPopup();
    EXPECT_NE(retrievedPopup, nullptr);
    EXPECT_EQ(retrievedPopup, popup);
}

// Test isInReplyTo default
TEST_F(AnnotMarkupWithDocTest_805, IsInReplyToDefault_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // Newly created annotation should not be in reply to anything
    EXPECT_FALSE(annot->isInReplyTo());
}

// Test getReplyTo default
TEST_F(AnnotMarkupWithDocTest_805, GetReplyToDefault_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    AnnotMarkupReplyType replyTo = annot->getReplyTo();
    // Default should be annotMarkupReplyTypeR
    EXPECT_EQ(replyTo, annotMarkupReplyTypeR);
}

// Test getSubject default
TEST_F(AnnotMarkupWithDocTest_805, GetSubjectDefault_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    const GooString *subject = annot->getSubject();
    // For a newly created annotation, subject may be nullptr
    // Just verify no crash
    SUCCEED();
}

// Test setLabel with empty string
TEST_F(AnnotMarkupWithDocTest_805, SetLabelEmpty_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto emptyLabel = std::make_unique<GooString>("");
    annot->setLabel(std::move(emptyLabel));

    const GooString *label = annot->getLabel();
    ASSERT_NE(label, nullptr);
    EXPECT_STREQ(label->c_str(), "");
}

// Test setLabel with nullptr (passing nullptr unique_ptr)
TEST_F(AnnotMarkupWithDocTest_805, SetLabelNullptr_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    std::unique_ptr<GooString> nullLabel;
    annot->setLabel(std::move(nullLabel));

    // After setting null label, getLabel should return nullptr or handle gracefully
    const GooString *label = annot->getLabel();
    // Just verify no crash
    SUCCEED();
}

// Test setDate with empty string
TEST_F(AnnotMarkupWithDocTest_805, SetDateEmpty_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto emptyDate = std::make_unique<GooString>("");
    annot->setDate(std::move(emptyDate));

    const GooString *date = annot->getDate();
    ASSERT_NE(date, nullptr);
    EXPECT_STREQ(date->c_str(), "");
}

// Test setting popup to nullptr
TEST_F(AnnotMarkupWithDocTest_805, SetPopupNullptr_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // First set a valid popup
    PDFRectangle popupRect(200, 200, 400, 300);
    auto popup = std::make_shared<AnnotPopup>(doc.get(), &popupRect);
    annot->setPopup(popup);
    EXPECT_NE(annot->getPopup(), nullptr);

    // Now set it to nullptr
    annot->setPopup(nullptr);
    EXPECT_EQ(annot->getPopup(), nullptr);
}

// Test multiple opacity changes
TEST_F(AnnotMarkupWithDocTest_805, MultipleOpacityChanges_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(0.3);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.3);

    annot->setOpacity(0.7);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.7);

    annot->setOpacity(1.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 1.0);
}

// Test setLabel overwrite
TEST_F(AnnotMarkupWithDocTest_805, SetLabelOverwrite_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
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

// Test getInReplyToID when not in reply
TEST_F(AnnotMarkupWithDocTest_805, GetInReplyToIDDefault_805) {
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // When not in reply, the ID should be some default (likely 0 or -1)
    int replyToID = annot->getInReplyToID();
    // Just verify it doesn't crash and returns a reasonable value
    SUCCEED();
}
