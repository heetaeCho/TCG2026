#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the necessary headers are included for PopplerFontsIter and FontInfo



extern "C" {

    const char *poppler_fonts_iter_get_file_name(PopplerFontsIter *iter);

}



class PopplerFontsIterTest_2223 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary resources for the tests

        iter = new PopplerFontsIter();

        iter->items = reinterpret_cast<FontInfo**>(malloc(sizeof(FontInfo*)));

    }



    void TearDown() override {

        // Clean up any resources used by the tests

        free(iter->items);

        delete iter;

    }



    PopplerFontsIter *iter;

};



TEST_F(PopplerFontsIterTest_2223, GetFileName_ReturnsNullptr_WhenIndexOutOfBounds_2223) {

    iter->index = 1; // Assuming index is set to 1 and items array has only one element

    EXPECT_EQ(poppler_fonts_iter_get_file_name(iter), nullptr);

}



TEST_F(PopplerFontsIterTest_2223, GetFileName_ReturnsNullptr_WhenFileNotSet_2223) {

    iter->index = 0;

    iter->items[0] = new FontInfo(nullptr, nullptr); // Assuming a constructor that initializes with null values

    EXPECT_EQ(poppler_fonts_iter_get_file_name(iter), nullptr);

    delete iter->items[0];

}



TEST_F(PopplerFontsIterTest_2223, GetFileName_ReturnsFileName_WhenFileSet_2223) {

    iter->index = 0;

    std::string testFileName = "test_font_file.ttf";

    FontInfo *fontInfo = new FontInfo(nullptr, nullptr);

    fontInfo->file = testFileName; // Assuming a way to set the file name

    iter->items[0] = fontInfo;

    EXPECT_STREQ(poppler_fonts_iter_get_file_name(iter), testFileName.c_str());

    delete iter->items[0];

}



TEST_F(PopplerFontsIterTest_2223, GetFileName_ReturnsNullptr_WhenIndexNegative_2223) {

    iter->index = -1;

    EXPECT_EQ(poppler_fonts_iter_get_file_name(iter), nullptr);

}
