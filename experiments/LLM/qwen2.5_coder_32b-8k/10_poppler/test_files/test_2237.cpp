#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.cc"

#include "poppler-private.h"



using ::testing::Test;

using ::testing::_;



class PopplerFontInfoTest_2237 : public Test {

protected:

    void SetUp() override {

        // Initialize any necessary state before each test

        font_info = reinterpret_cast<PopplerFontInfo*>(g_object_new(G_TYPE_OBJECT, nullptr));

    }



    void TearDown() override {

        // Clean up any state after each test

        if (font_info) {

            poppler_font_info_free(font_info);

            font_info = nullptr;

        }

    }



    PopplerFontInfo* font_info;

};



TEST_F(PopplerFontInfoTest_2237, FreeNullPointer_2237) {

    // Test the behavior when passing a null pointer to poppler_font_info_free

    EXPECT_NO_THROW(poppler_font_info_free(nullptr));

}



TEST_F(PopplerFontInfoTest_2237, FreeValidPointer_2237) {

    // Test the normal operation of freeing a valid PopplerFontInfo pointer

    EXPECT_NO_THROW(poppler_font_info_free(font_info));

    font_info = nullptr;  // Prevent double-free in TearDown

}



TEST_F(PopplerFontInfoTest_2237, DoubleFree_2237) {

    // Test the behavior of freeing a PopplerFontInfo pointer twice

    EXPECT_NO_THROW(poppler_font_info_free(font_info));

    font_info = nullptr;  // Prevent double-free in TearDown

    EXPECT_NO_THROW(poppler_font_info_free(font_info));  // Should handle gracefully if already freed

}
