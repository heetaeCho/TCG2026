#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming necessary headers are included for PopplerFontsIter and FontInfo



class PopplerFontsIterTest : public ::testing::Test {

protected:

    struct _PopplerFontsIter iter;

    FontInfo fontInfoWithSubstitute;

    FontInfo fontInfoWithoutSubstitute;



    void SetUp() override {

        // Initialize the iterator with some mock data

        iter.index = 0;

        iter.items = new FontInfo*[1];

        

        // Mock a FontInfo object that has a substitute name

        std::optional<std::string> substituteName = "MockSubstituteName";

        fontInfoWithSubstitute = FontInfo(/* constructor arguments */);

        *const_cast<std::optional<std::string>*>(&fontInfoWithSubstitute.substituteName) = substituteName;



        // Mock a FontInfo object that does not have a substitute name

        fontInfoWithoutSubstitute = FontInfo(/* constructor arguments */);

        *const_cast<std::optional<std::string>*>(&fontInfoWithoutSubstitute.substituteName) = std::nullopt;



        iter.items[0] = &fontInfoWithSubstitute;

    }



    void TearDown() override {

        delete[] iter.items;

    }

};



TEST_F(PopplerFontsIterTest_2222, GetSubstituteName_ReturnsCorrectValueWhenPresent_2222) {

    iter.index = 0; // Point to the fontInfoWithSubstitute

    const char* result = poppler_fonts_iter_get_substitute_name(&iter);

    EXPECT_STREQ(result, "MockSubstituteName");

}



TEST_F(PopplerFontsIterTest_2222, GetSubstituteName_ReturnsNullptrWhenNotPresent_2222) {

    iter.items[0] = &fontInfoWithoutSubstitute; // Point to the fontInfoWithoutSubstitute

    const char* result = poppler_fonts_iter_get_substitute_name(&iter);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerFontsIterTest_2222, GetSubstituteName_OutOfBoundsIndex_ReturnsNullptr_2222) {

    iter.index = 1; // Out of bounds index

    const char* result = poppler_fonts_iter_get_substitute_name(&iter);

    EXPECT_EQ(result, nullptr);

}



TEST_F(PopplerFontsIterTest_2222, GetSubstituteName_IndexNegative_ReturnsNullptr_2222) {

    iter.index = -1; // Negative index

    const char* result = poppler_fonts_iter_get_substitute_name(&iter);

    EXPECT_EQ(result, nullptr);

}
