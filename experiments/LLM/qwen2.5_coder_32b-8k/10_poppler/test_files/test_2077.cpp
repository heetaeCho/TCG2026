#include <gtest/gtest.h>

#include "poppler-annot.h"



// Mocking external collaborators if necessary (not needed in this case)



class PopplerAnnotMarkupTest_2077 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary resources or mocks here

    }



    void TearDown() override {

        // Clean up resources or mocks here

    }

};



TEST_F(PopplerAnnotMarkupTest_2077, HasPopup_ReturnsFalse_WhenNoPopup_2077) {

    // Arrange

    PopplerAnnotMarkup* poppler_annot = static_cast<PopplerAnnotMarkup*>(g_object_new(POPPLER_TYPE_ANNOT_MARKUP, nullptr));



    // Act & Assert

    EXPECT_FALSE(poppler_annot_markup_has_popup(poppler_annot));



    // Clean up

    g_object_unref(poppler_annot);

}



TEST_F(PopplerAnnotMarkupTest_2077, HasPopup_ReturnsTrue_WhenPopupExists_2077) {

    // Arrange

    PopplerAnnotMarkup* poppler_annot = static_cast<PopplerAnnotMarkup*>(g_object_new(POPPLER_TYPE_ANNOT_MARKUP, nullptr));

    AnnotMarkup* annot = static_cast<AnnotMarkup*>(POPPLER_ANNOT(poppler_annot)->annot.get());

    annot->setPopup(new AnnotPopup()); // Assuming setPopup is a method to add popup



    // Act & Assert

    EXPECT_TRUE(poppler_annot_markup_has_popup(poppler_annot));



    // Clean up

    g_object_unref(poppler_annot);

}



TEST_F(PopplerAnnotMarkupTest_2077, HasPopup_ReturnsFalse_WhenInvalidPointer_2077) {

    // Arrange & Act & Assert

    EXPECT_FALSE(poppler_annot_markup_has_popup(nullptr));

}
