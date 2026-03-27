#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"  // Assuming Annot.h is included for the classes

// Mock class for AnnotPopup if needed for interaction verification
class MockAnnotPopup : public AnnotPopup {
public:
    MOCK_METHOD(void, somePopupMethod, (), (const));
};

// TEST_ID is 797

// Test Fixture for AnnotMarkup
class AnnotMarkupTest_797 : public ::testing::Test {
protected:
    AnnotMarkupTest_797() : doc(nullptr), rect(nullptr) {}

    PDFDoc *doc;
    PDFRectangle *rect;
    std::shared_ptr<AnnotPopup> mockPopup;
    std::unique_ptr<GooString> label;
    std::unique_ptr<GooString> date;

    void SetUp() override {
        // Setup the necessary environment
        doc = new PDFDoc();
        rect = new PDFRectangle();
        label = std::make_unique<GooString>("Test Label");
        date = std::make_unique<GooString>("2026-02-15");

        mockPopup = std::make_shared<MockAnnotPopup>();
    }

    void TearDown() override {
        delete doc;
        delete rect;
    }
};

// Test normal operation for getLabel
TEST_F(AnnotMarkupTest_797, GetLabel_ReturnsCorrectLabel_797) {
    AnnotMarkup annotMarkup(doc, rect);

    annotMarkup.setLabel(std::move(label));

    EXPECT_EQ(annotMarkup.getLabel()->getCString(), "Test Label");
}

// Test boundary condition for empty label
TEST_F(AnnotMarkupTest_797, GetLabel_EmptyLabel_797) {
    AnnotMarkup annotMarkup(doc, rect);

    std::unique_ptr<GooString> emptyLabel = std::make_unique<GooString>("");
    annotMarkup.setLabel(std::move(emptyLabel));

    EXPECT_EQ(annotMarkup.getLabel()->getCString(), "");
}

// Test normal operation for setOpacity and getOpacity
TEST_F(AnnotMarkupTest_797, SetGetOpacity_ValidOpacity_797) {
    AnnotMarkup annotMarkup(doc, rect);

    annotMarkup.setOpacity(0.5);

    EXPECT_DOUBLE_EQ(annotMarkup.getOpacity(), 0.5);
}

// Test boundary condition for opacity value of 0
TEST_F(AnnotMarkupTest_797, SetGetOpacity_ZeroOpacity_797) {
    AnnotMarkup annotMarkup(doc, rect);

    annotMarkup.setOpacity(0.0);

    EXPECT_DOUBLE_EQ(annotMarkup.getOpacity(), 0.0);
}

// Test boundary condition for maximum opacity value of 1
TEST_F(AnnotMarkupTest_797, SetGetOpacity_MaxOpacity_797) {
    AnnotMarkup annotMarkup(doc, rect);

    annotMarkup.setOpacity(1.0);

    EXPECT_DOUBLE_EQ(annotMarkup.getOpacity(), 1.0);
}

// Test normal operation for setPopup and getPopup
TEST_F(AnnotMarkupTest_797, SetGetPopup_ValidPopup_797) {
    AnnotMarkup annotMarkup(doc, rect);

    annotMarkup.setPopup(mockPopup);

    EXPECT_EQ(annotMarkup.getPopup(), mockPopup);
}

// Test exceptional case for invalid label
TEST_F(AnnotMarkupTest_797, SetLabel_InvalidLabel_797) {
    AnnotMarkup annotMarkup(doc, rect);

    EXPECT_THROW(annotMarkup.setLabel(nullptr), std::invalid_argument);
}

// Test exceptional case for invalid date
TEST_F(AnnotMarkupTest_797, SetDate_InvalidDate_797) {
    AnnotMarkup annotMarkup(doc, rect);

    EXPECT_THROW(annotMarkup.setDate(nullptr), std::invalid_argument);
}

// Test normal operation for setDate and getDate
TEST_F(AnnotMarkupTest_797, SetGetDate_ValidDate_797) {
    AnnotMarkup annotMarkup(doc, rect);

    annotMarkup.setDate(std::move(date));

    EXPECT_EQ(annotMarkup.getDate()->getCString(), "2026-02-15");
}

// Test boundary condition for empty date
TEST_F(AnnotMarkupTest_797, SetDate_EmptyDate_797) {
    AnnotMarkup annotMarkup(doc, rect);

    std::unique_ptr<GooString> emptyDate = std::make_unique<GooString>("");
    annotMarkup.setDate(std::move(emptyDate));

    EXPECT_EQ(annotMarkup.getDate()->getCString(), "");
}

// Test for isInReplyTo
TEST_F(AnnotMarkupTest_797, IsInReplyTo_Valid_797) {
    AnnotMarkup annotMarkup(doc, rect);

    EXPECT_FALSE(annotMarkup.isInReplyTo());
}

// Test for getInReplyToID
TEST_F(AnnotMarkupTest_797, GetInReplyToID_Valid_797) {
    AnnotMarkup annotMarkup(doc, rect);

    EXPECT_EQ(annotMarkup.getInReplyToID(), -1);  // Assuming the default value
}

// Test exceptional case for invalid popup set
TEST_F(AnnotMarkupTest_797, SetPopup_InvalidPopup_797) {
    AnnotMarkup annotMarkup(doc, rect);

    EXPECT_THROW(annotMarkup.setPopup(nullptr), std::invalid_argument);
}