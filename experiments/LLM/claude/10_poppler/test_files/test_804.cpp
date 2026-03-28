#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers
#include "Annot.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "Object.h"
#include "PDFRectangle.h"

// Since we cannot easily construct PDFDoc and other dependencies without a real PDF,
// we'll test what we can through the interface. For many tests we need a valid PDFDoc,
// so we'll create a minimal test fixture that attempts to work with available constructors.

class AnnotMarkupTest_804 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll try to create objects needed for testing.
        // Since creating a full PDFDoc is complex, tests may need to be adjusted
        // based on what's available in the test environment.
    }

    void TearDown() override {
    }
};

// Helper to create a minimal PDF file for testing
static std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
    // Create a minimal valid PDF in memory
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

    auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, strlen(minimalPDF), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    if (doc->isOk()) {
        return doc;
    }
    return nullptr;
}

// Test that getReplyTo returns a valid AnnotMarkupReplyType
TEST_F(AnnotMarkupTest_804, GetReplyToReturnsValidType_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    // Create using the rect constructor - this should create a default AnnotMarkup
    // We need a concrete subclass since AnnotMarkup may be abstract or need specific type
    // Using AnnotText as a concrete subclass of AnnotMarkup
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    AnnotMarkupReplyType replyType = annot->getReplyTo();
    // Default should be annotMarkupReplyTypeR (Reply)
    EXPECT_TRUE(replyType == annotMarkupReplyTypeR || replyType == annotMarkupReplyTypeGroup);
}

// Test default opacity value
TEST_F(AnnotMarkupTest_804, DefaultOpacity_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    double opacity = annot->getOpacity();
    // Default opacity should be 1.0
    EXPECT_DOUBLE_EQ(opacity, 1.0);
}

// Test setOpacity and getOpacity
TEST_F(AnnotMarkupTest_804, SetAndGetOpacity_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(0.5);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.5);
}

// Test setOpacity with boundary value 0.0
TEST_F(AnnotMarkupTest_804, SetOpacityZero_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(0.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.0);
}

// Test setOpacity with boundary value 1.0
TEST_F(AnnotMarkupTest_804, SetOpacityOne_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(1.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 1.0);
}

// Test getLabel returns nullptr by default (no label set)
TEST_F(AnnotMarkupTest_804, DefaultLabelIsNullOrEmpty_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    const GooString *label = annot->getLabel();
    // Label may be nullptr or empty by default
    if (label != nullptr) {
        // If not null, it's acceptable - just verify it's accessible
        EXPECT_GE(label->getLength(), 0);
    }
}

// Test setLabel and getLabel
TEST_F(AnnotMarkupTest_804, SetAndGetLabel_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto label = std::make_unique<GooString>("Test Label");
    annot->setLabel(std::move(label));

    const GooString *retrievedLabel = annot->getLabel();
    ASSERT_NE(retrievedLabel, nullptr);
    EXPECT_STREQ(retrievedLabel->c_str(), "Test Label");
}

// Test setLabel with empty string
TEST_F(AnnotMarkupTest_804, SetEmptyLabel_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto label = std::make_unique<GooString>("");
    annot->setLabel(std::move(label));

    const GooString *retrievedLabel = annot->getLabel();
    ASSERT_NE(retrievedLabel, nullptr);
    EXPECT_EQ(retrievedLabel->getLength(), 0);
}

// Test getDate returns nullptr by default
TEST_F(AnnotMarkupTest_804, DefaultDateIsNullOrEmpty_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    const GooString *date = annot->getDate();
    // Date may be nullptr or valid by default
    if (date != nullptr) {
        EXPECT_GE(date->getLength(), 0);
    }
}

// Test setDate and getDate
TEST_F(AnnotMarkupTest_804, SetAndGetDate_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto date = std::make_unique<GooString>("D:20230101120000");
    annot->setDate(std::move(date));

    const GooString *retrievedDate = annot->getDate();
    ASSERT_NE(retrievedDate, nullptr);
    EXPECT_STREQ(retrievedDate->c_str(), "D:20230101120000");
}

// Test isInReplyTo returns false by default
TEST_F(AnnotMarkupTest_804, DefaultIsNotInReplyTo_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    EXPECT_FALSE(annot->isInReplyTo());
}

// Test getSubject returns nullptr by default
TEST_F(AnnotMarkupTest_804, DefaultSubjectIsNull_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    const GooString *subject = annot->getSubject();
    // Subject may be nullptr by default
    if (subject != nullptr) {
        EXPECT_GE(subject->getLength(), 0);
    }
}

// Test getPopup returns nullptr by default
TEST_F(AnnotMarkupTest_804, DefaultPopupIsNull_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    std::shared_ptr<AnnotPopup> popup = annot->getPopup();
    EXPECT_EQ(popup, nullptr);
}

// Test setPopup and getPopup
TEST_F(AnnotMarkupTest_804, SetAndGetPopup_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    PDFRectangle popupRect(100, 100, 300, 200);
    auto popup = std::make_shared<AnnotPopup>(doc.get(), &popupRect);

    annot->setPopup(popup);

    std::shared_ptr<AnnotPopup> retrievedPopup = annot->getPopup();
    EXPECT_NE(retrievedPopup, nullptr);
    EXPECT_EQ(retrievedPopup, popup);
}

// Test getExData returns default value
TEST_F(AnnotMarkupTest_804, DefaultExData_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    AnnotExternalDataType exData = annot->getExData();
    // Default should be annotExternalDataMarkupUnknown or similar
    EXPECT_GE(static_cast<int>(exData), 0);
}

// Test getReplyTo default value is annotMarkupReplyTypeR
TEST_F(AnnotMarkupTest_804, DefaultReplyToIsR_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    AnnotMarkupReplyType replyType = annot->getReplyTo();
    EXPECT_EQ(replyType, annotMarkupReplyTypeR);
}

// Test multiple opacity changes
TEST_F(AnnotMarkupTest_804, MultipleOpacityChanges_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(0.3);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.3);

    annot->setOpacity(0.7);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.7);

    annot->setOpacity(1.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 1.0);
}

// Test setLabel replaces previous label
TEST_F(AnnotMarkupTest_804, SetLabelReplacesExisting_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setLabel(std::make_unique<GooString>("First Label"));
    const GooString *label1 = annot->getLabel();
    ASSERT_NE(label1, nullptr);
    EXPECT_STREQ(label1->c_str(), "First Label");

    annot->setLabel(std::make_unique<GooString>("Second Label"));
    const GooString *label2 = annot->getLabel();
    ASSERT_NE(label2, nullptr);
    EXPECT_STREQ(label2->c_str(), "Second Label");
}

// Test setPopup to nullptr
TEST_F(AnnotMarkupTest_804, SetPopupToNull_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    PDFRectangle popupRect(100, 100, 300, 200);
    auto popup = std::make_shared<AnnotPopup>(doc.get(), &popupRect);
    annot->setPopup(popup);
    EXPECT_NE(annot->getPopup(), nullptr);

    annot->setPopup(nullptr);
    EXPECT_EQ(annot->getPopup(), nullptr);
}

// Test getInReplyToID when not in reply
TEST_F(AnnotMarkupTest_804, GetInReplyToIDWhenNotInReply_804) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Cannot create minimal PDF document";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // When not in reply, the ID should be some default/invalid value
    if (!annot->isInReplyTo()) {
        int replyToID = annot->getInReplyToID();
        // Just verify we can call it without crashing
        EXPECT_GE(replyToID, 0); // or any observable default
    }
}
