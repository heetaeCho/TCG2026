#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "FontInfo.h"



// Mocking FontInfo for necessary interactions

class MockFontInfo : public FontInfo {

public:

    MOCK_METHOD(Type, getType, (), (const));

};



// Test fixture for PopplerFontsIter tests

class PopplerFontsIterTest_2224 : public ::testing::Test {

protected:

    std::unique_ptr<MockFontInfo> mockFontInfo;

    _PopplerFontsIter iter;



    void SetUp() override {

        mockFontInfo = std::make_unique<MockFontInfo>();

        iter.items = reinterpret_cast<FontInfo**>(new FontInfo*[1]);

        iter.index = 0;

        iter.items[0] = mockFontInfo.get();

    }



    void TearDown() override {

        delete[] iter.items;

    }

};



// Normal operation test

TEST_F(PopplerFontsIterTest_2224, GetFontTypeNormalOperation_2224) {

    EXPECT_CALL(*mockFontInfo, getType()).WillOnce(::testing::Return(FontInfo::TYPE1));

    EXPECT_EQ(poppler_fonts_iter_get_font_type(&iter), POPPLER_FONT_TYPE_TYPE1);

}



// Boundary condition test: empty items array

TEST(PopplerFontsIterTest_2224, GetFontTypeEmptyItems_2224) {

    _PopplerFontsIter iter;

    iter.items = nullptr;

    iter.index = 0;

    EXPECT_EQ(poppler_fonts_iter_get_font_type(&iter), POPPLER_FONT_TYPE_UNKNOWN);

}



// Boundary condition test: index out of bounds

TEST_F(PopplerFontsIterTest_2224, GetFontTypeIndexOutOfBounds_2224) {

    iter.index = 1; // Assuming there is only one item in the array for this test

    EXPECT_EQ(poppler_fonts_iter_get_font_type(&iter), POPPLER_FONT_TYPE_UNKNOWN);

}



// Nullptr test: null PopplerFontsIter pointer

TEST(PopplerFontsIterTest_2224, GetFontTypeNullPtr_2224) {

    EXPECT_EQ(poppler_fonts_iter_get_font_type(nullptr), POPPLER_FONT_TYPE_UNKNOWN);

}
