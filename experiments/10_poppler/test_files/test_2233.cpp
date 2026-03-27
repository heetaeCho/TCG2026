#include <gtest/gtest.h>

#include "poppler-document.cc"

#include "poppler-private.h"



class PopplerFontInfoTest_2233 : public ::testing::Test {

protected:

    PopplerFontInfo font_info;



    void SetUp() override {

        poppler_font_info_init(&font_info);

    }

};



TEST_F(PopplerFontInfoTest_2233, DocumentPointerIsNullAfterInitialization_2233) {

    EXPECT_EQ(font_info.document, nullptr);

}



TEST_F(PopplerFontInfoTest_2233, ScannerPointerIsNullAfterInitialization_2233) {

    EXPECT_EQ(font_info.scanner, nullptr);

}
