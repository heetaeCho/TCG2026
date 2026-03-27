#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include <cairo.h>



using namespace testing;



class PopplerAnnotStampTest : public ::testing::Test {

protected:

    GError *error = nullptr;

    cairo_surface_t *image = nullptr;

    PopplerAnnotStamp *poppler_annot_stamp = nullptr;



    void SetUp() override {

        image = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 10, 10);

        poppler_annot_stamp = static_cast<PopplerAnnotStamp*>(g_malloc0(sizeof(PopplerAnnotStamp)));

        g_type_init();

    }



    void TearDown() override {

        if (image) cairo_surface_destroy(image);

        if (poppler_annot_stamp) g_free(poppler_annot_stamp);

        if (error) g_error_free(error);

    }

};



TEST_F(PopplerAnnotStampTest_2121, SetCustomImageWithValidImage_ReturnsTrue_2121) {

    EXPECT_TRUE(poppler_annot_stamp_set_custom_image(poppler_annot_stamp, image, &error));

}



TEST_F(PopplerAnnotStampTest_2121, SetCustomImageWithNullImage_ReturnsFalseAndSetsError_2121) {

    EXPECT_FALSE(poppler_annot_stamp_set_custom_image(poppler_annot_stamp, nullptr, &error));

    EXPECT_NE(error, nullptr);

}



TEST_F(PopplerAnnotStampTest_2121, SetCustomImageWithInvalidPopplerAnnot_ReturnsFalse_2121) {

    PopplerAnnotStamp *invalid_poppler_annot_stamp = nullptr;

    EXPECT_FALSE(poppler_annot_stamp_set_custom_image(invalid_poppler_annot_stamp, image, &error));

}



TEST_F(PopplerAnnotStampTest_2121, SetCustomImageWithValidImageAndNullError_ReturnsTrue_2121) {

    EXPECT_TRUE(poppler_annot_stamp_set_custom_image(poppler_annot_stamp, image, nullptr));

}
