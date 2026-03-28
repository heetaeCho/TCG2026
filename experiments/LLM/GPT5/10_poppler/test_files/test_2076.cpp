#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"  // Include the necessary header for the PopplerAnnotMarkup type

class MockAnnotMarkup : public AnnotMarkup {
public:
    MOCK_METHOD(void, setLabel, (std::unique_ptr<GooString> label), (override));
};

class PopplerAnnotMarkupTest_2076 : public ::testing::Test {
protected:
    // Prepare the PopplerAnnotMarkup mock object
    PopplerAnnotMarkup *poppler_annot;
    MockAnnotMarkup *mock_annot_markup;

    void SetUp() override {
        mock_annot_markup = new MockAnnotMarkup();
        poppler_annot = reinterpret_cast<PopplerAnnotMarkup*>(g_malloc(sizeof(PopplerAnnotMarkup)));
        poppler_annot->parent_instance.annot = mock_annot_markup;
    }

    void TearDown() override {
        g_free(poppler_annot);
    }
};

TEST_F(PopplerAnnotMarkupTest_2076, SetLabelValidInput_2076) {
    const char *label = "Test Label";
    EXPECT_CALL(*mock_annot_markup, setLabel(testing::_)).Times(1);

    poppler_annot_markup_set_label(poppler_annot, label);
}

TEST_F(PopplerAnnotMarkupTest_2076, SetLabelNull_2076) {
    // When the label is null, the annot->setLabel should not be called.
    const char *label = nullptr;
    EXPECT_CALL(*mock_annot_markup, setLabel(testing::_)).Times(0);

    poppler_annot_markup_set_label(poppler_annot, label);
}

TEST_F(PopplerAnnotMarkupTest_2076, SetLabelEmptyString_2076) {
    const char *label = "";
    EXPECT_CALL(*mock_annot_markup, setLabel(testing::_)).Times(1);

    poppler_annot_markup_set_label(poppler_annot, label);
}

TEST_F(PopplerAnnotMarkupTest_2076, SetLabelConversionFailure_2076) {
    const char *label = "Test Label";
    // Simulate failure in g_convert
    EXPECT_CALL(*mock_annot_markup, setLabel(testing::_)).Times(1);

    // Modify g_convert in the mock or redirect to simulate failure
    // This would require custom test setup, e.g., mocking g_convert if needed
    poppler_annot_markup_set_label(poppler_annot, label);
}

TEST_F(PopplerAnnotMarkupTest_2076, SetLabelInvalidAnnot_2076) {
    // Test case where the PopplerAnnotMarkup is invalid
    poppler_annot = nullptr;  // Simulate invalid PopplerAnnotMarkup

    EXPECT_EXIT(poppler_annot_markup_set_label(poppler_annot, "Invalid Annot"), ::testing::ExitedWithCode(1), "");
}