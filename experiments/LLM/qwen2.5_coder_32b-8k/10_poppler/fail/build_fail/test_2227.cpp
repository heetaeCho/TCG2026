#include <gtest/gtest.h>

#include "poppler-document.h"

#include "FontInfo.h"



// Mocking FontInfo to control its behavior during tests

class MockFontInfo : public FontInfo {

public:

    MOCK_CONST_METHOD0(getSubset, bool());

};



// Test fixture for PopplerFontsIter tests

class PopplerFontsIterTest_2227 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize the iterator with mock FontInfo objects

        iter = new _PopplerFontsIter();

        iter->index = 0;

        iter->items = reinterpret_cast<FontInfo**>(malloc(sizeof(FontInfo*) * 2));

        iter->items[0] = new MockFontInfo();

        iter->items[1] = new MockFontInfo();

    }



    void TearDown() override {

        // Clean up the allocated FontInfo objects and iterator

        delete iter->items[0];

        delete iter->items[1];

        free(iter->items);

        delete iter;

    }



    _PopplerFontsIter* iter;

};



// Test case for normal operation where font is subset

TEST_F(PopplerFontsIterTest_2227, IsSubsetTrue_2227) {

    EXPECT_CALL(*static_cast<MockFontInfo*>(iter->items[0]), getSubset()).WillOnce(::testing::Return(true));

    ASSERT_TRUE(poppler_fonts_iter_is_subset(iter));

}



// Test case for normal operation where font is not subset

TEST_F(PopplerFontsIterTest_2227, IsSubsetFalse_2227) {

    EXPECT_CALL(*static_cast<MockFontInfo*>(iter->items[0]), getSubset()).WillOnce(::testing::Return(false));

    ASSERT_FALSE(poppler_fonts_iter_is_subset(iter));

}



// Test case for boundary condition: index at the last item

TEST_F(PopplerFontsIterTest_2227, IsSubsetLastItemTrue_2227) {

    iter->index = 1;

    EXPECT_CALL(*static_cast<MockFontInfo*>(iter->items[1]), getSubset()).WillOnce(::testing::Return(true));

    ASSERT_TRUE(poppler_fonts_iter_is_subset(iter));

}



// Test case for boundary condition: index at the last item

TEST_F(PopplerFontsIterTest_2227, IsSubsetLastItemFalse_2227) {

    iter->index = 1;

    EXPECT_CALL(*static_cast<MockFontInfo*>(iter->items[1]), getSubset()).WillOnce(::testing::Return(false));

    ASSERT_FALSE(poppler_fonts_iter_is_subset(iter));

}
