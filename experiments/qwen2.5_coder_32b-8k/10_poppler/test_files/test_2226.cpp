#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"



// Mock FontInfo class to simulate behavior for testing purposes

class MockFontInfo : public FontInfo {

public:

    MOCK_CONST_METHOD0(getEmbedded, bool());

};



// Test fixture for PopplerFontsIter tests

class PopplerFontsIterTest_2226 : public ::testing::Test {

protected:

    void SetUp() override {

        mockFontInfo = std::make_unique<MockFontInfo>();

        iter.items[iter.index] = mockFontInfo.get();

    }



    MockFontInfo* mockFontInfo;

    _PopplerFontsIter iter;

};



// Test normal operation when the font is embedded

TEST_F(PopplerFontsIterTest_2226, IsEmbedded_ReturnsTrueWhenEmbedded_2226) {

    EXPECT_CALL(*mockFontInfo, getEmbedded()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(poppler_fonts_iter_is_embedded(&iter));

}



// Test normal operation when the font is not embedded

TEST_F(PopplerFontsIterTest_2226, IsEmbedded_ReturnsFalseWhenNotEmbedded_2226) {

    EXPECT_CALL(*mockFontInfo, getEmbedded()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(poppler_fonts_iter_is_embedded(&iter));

}



// Test boundary condition when index is at the start

TEST_F(PopplerFontsIterTest_2226, IsEmbedded_StartIndex_ReturnsExpectedValue_2226) {

    iter.index = 0;

    EXPECT_CALL(*mockFontInfo, getEmbedded()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(poppler_fonts_iter_is_embedded(&iter));

}



// Test boundary condition when index is at the end

TEST_F(PopplerFontsIterTest_2226, IsEmbedded_EndIndex_ReturnsExpectedValue_2226) {

    iter.index = 1; // Assuming there are at least two items for testing purposes

    auto mockFontInfoEnd = std::make_unique<MockFontInfo>();

    iter.items[iter.index] = mockFontInfoEnd.get();

    EXPECT_CALL(*mockFontInfoEnd, getEmbedded()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(poppler_fonts_iter_is_embedded(&iter));

}
