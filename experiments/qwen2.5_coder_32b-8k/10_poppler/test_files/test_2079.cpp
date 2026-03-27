#include <gtest/gtest.h>

#include <gmock/gmock.h>

extern "C" {

    #include "poppler-annot.h"

}



// Mocking the necessary structures and functions for testing.

class MockAnnotMarkup : public AnnotMarkup {

public:

    MOCK_METHOD0(getPopup, std::shared_ptr<AnnotPopup>());

};



class MockAnnotPopup : public AnnotPopup {

public:

    MOCK_CONST_METHOD0(getOpen, bool());

};



// Test fixture for PopplerAnnotMarkup tests.

class PopplerAnnotMarkupTest_2079 : public ::testing::Test {

protected:

    void SetUp() override {

        poppler_annot_markup = static_cast<PopplerAnnotMarkup*>(g_object_new(POPPLER_TYPE_ANNOT_MARKUP, nullptr));

        mock_annot_markup = std::make_unique<MockAnnotMarkup>();

        poppler_annot_markup->parent_instance.annot = std::shared_ptr<Annot>(mock_annot_markup.get());

    }



    void TearDown() override {

        g_object_unref(poppler_annot_markup);

    }



    PopplerAnnotMarkup *poppler_annot_markup;

    std::unique_ptr<MockAnnotMarkup> mock_annot_markup;

};



// Test case to verify normal operation when popup is open.

TEST_F(PopplerAnnotMarkupTest_2079, PopupOpen_ReturnsTrue_2079) {

    auto mock_popup = std::make_shared<MockAnnotPopup>();

    EXPECT_CALL(*mock_annot_markup, getPopup()).WillOnce(::testing::Return(mock_popup));

    EXPECT_CALL(*mock_popup, getOpen()).WillOnce(::testing::Return(true));



    gboolean result = poppler_annot_markup_get_popup_is_open(poppler_annot_markup);

    EXPECT_TRUE(result);

}



// Test case to verify normal operation when popup is closed.

TEST_F(PopplerAnnotMarkupTest_2079, PopupClosed_ReturnsFalse_2079) {

    auto mock_popup = std::make_shared<MockAnnotPopup>();

    EXPECT_CALL(*mock_annot_markup, getPopup()).WillOnce(::testing::Return(mock_popup));

    EXPECT_CALL(*mock_popup, getOpen()).WillOnce(::testing::Return(false));



    gboolean result = poppler_annot_markup_get_popup_is_open(poppler_annot_markup);

    EXPECT_FALSE(result);

}



// Test case to verify behavior when popup is not available.

TEST_F(PopplerAnnotMarkupTest_2079, NoPopup_ReturnsFalse_2079) {

    EXPECT_CALL(*mock_annot_markup, getPopup()).WillOnce(::testing::Return(nullptr));



    gboolean result = poppler_annot_markup_get_popup_is_open(poppler_annot_markup);

    EXPECT_FALSE(result);

}



// Test case to verify behavior with invalid input.

TEST_F(PopplerAnnotMarkupTest_2079, InvalidInput_ReturnsFalse_2079) {

    PopplerAnnotMarkup* invalid_poppler_annot = nullptr;



    gboolean result = poppler_annot_markup_get_popup_is_open(invalid_poppler_annot);

    EXPECT_FALSE(result);

}
