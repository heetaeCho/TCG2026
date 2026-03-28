#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"  // Assuming the provided header

class PopplerAnnotMock : public PopplerAnnotMarkup {
public:
    MOCK_METHOD(PopplerRectangle*, getPopup, (), (const));
};

TEST_F(PopplerAnnotTest_2081, TestGetPopupRectangle_2081) {
    // Setup
    PopplerAnnotMarkup annot_markup;
    PopplerRectangle poppler_rect;
    
    // Mock behavior
    PopplerAnnotMock annot_mock;
    EXPECT_CALL(annot_mock, getPopup()).WillOnce([]() {
        return new PopplerRectangle{0, 0, 10, 10}; // Mocked value
    });

    // Test: Valid annotation with popup
    gboolean result = poppler_annot_markup_get_popup_rectangle(&annot_mock, &poppler_rect);
    EXPECT_TRUE(result);
    EXPECT_EQ(poppler_rect.x1, 0);
    EXPECT_EQ(poppler_rect.y1, 0);
    EXPECT_EQ(poppler_rect.x2, 10);
    EXPECT_EQ(poppler_rect.y2, 10);
}

TEST_F(PopplerAnnotTest_2081, TestGetPopupRectangle_NoPopup_2081) {
    // Setup
    PopplerAnnotMarkup annot_markup;
    PopplerRectangle poppler_rect;

    // Mock behavior
    PopplerAnnotMock annot_mock;
    EXPECT_CALL(annot_mock, getPopup()).WillOnce([]() {
        return nullptr; // No popup
    });

    // Test: No popup
    gboolean result = poppler_annot_markup_get_popup_rectangle(&annot_mock, &poppler_rect);
    EXPECT_FALSE(result);
}