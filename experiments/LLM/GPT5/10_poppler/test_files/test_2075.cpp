#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/glib/poppler-annot.h"
#include "./TestProjects/poppler/poppler/Annot.h"

// Mock classes to simulate external dependencies
class MockAnnotMarkup : public AnnotMarkup {
public:
    MOCK_METHOD(const GooString*, getLabel, (), (const, override));
};

class PopplerAnnotMarkupTest_2075 : public testing::Test {
protected:
    // Create mock object for AnnotMarkup
    std::shared_ptr<MockAnnotMarkup> mockAnnotMarkup;

    // Test setup
    void SetUp() override {
        mockAnnotMarkup = std::make_shared<MockAnnotMarkup>(nullptr, nullptr);
    }
};

// Test case for normal operation
TEST_F(PopplerAnnotMarkupTest_2075, GetLabel_ReturnsLabel_2075) {
    GooString label("Test Label");
    EXPECT_CALL(*mockAnnotMarkup, getLabel())
        .WillOnce(testing::Return(&label));

    PopplerAnnotMarkup popplerAnnotMarkup;
    popplerAnnotMarkup.annot = mockAnnotMarkup;

    gchar* result = poppler_annot_markup_get_label(&popplerAnnotMarkup);

    EXPECT_STREQ(result, "Test Label");
}

// Test case when getLabel returns nullptr
TEST_F(PopplerAnnotMarkupTest_2075, GetLabel_ReturnsNull_2075) {
    EXPECT_CALL(*mockAnnotMarkup, getLabel())
        .WillOnce(testing::Return(nullptr));

    PopplerAnnotMarkup popplerAnnotMarkup;
    popplerAnnotMarkup.annot = mockAnnotMarkup;

    gchar* result = poppler_annot_markup_get_label(&popplerAnnotMarkup);

    EXPECT_EQ(result, nullptr);
}

// Test case when the annotation is not a valid PopplerAnnotMarkup
TEST_F(PopplerAnnotMarkupTest_2075, InvalidAnnotation_2075) {
    PopplerAnnotMarkup invalidAnnot;

    // Pass an invalid PopplerAnnotMarkup
    gchar* result = poppler_annot_markup_get_label(&invalidAnnot);

    EXPECT_EQ(result, nullptr);
}

// Test case for boundary condition: empty label
TEST_F(PopplerAnnotMarkupTest_2075, GetLabel_EmptyLabel_2075) {
    GooString emptyLabel("");
    EXPECT_CALL(*mockAnnotMarkup, getLabel())
        .WillOnce(testing::Return(&emptyLabel));

    PopplerAnnotMarkup popplerAnnotMarkup;
    popplerAnnotMarkup.annot = mockAnnotMarkup;

    gchar* result = poppler_annot_markup_get_label(&popplerAnnotMarkup);

    EXPECT_STREQ(result, "");
}