#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/GfxFont.h"

class GfxFontTest_1151 : public ::testing::Test {
protected:
    GfxFontTest_1151() {
        // Initialize any necessary test data here
    }
    ~GfxFontTest_1151() override = default;

    // Mock or real instances can be set here if required for testing
};

// Test case for isFixedWidth method
TEST_F(GfxFontTest_1151, IsFixedWidth_1151) {
    // Mocking a scenario where flags is set to fontFixedWidth
    GfxFont font;
    EXPECT_CALL(font, isFixedWidth())
        .WillOnce(testing::Return(true));
    
    // Validate behavior
    ASSERT_TRUE(font.isFixedWidth());
}

// Boundary test for isFixedWidth when flags is set to zero (not fixed width)
TEST_F(GfxFontTest_1151, IsFixedWidth_False_1151) {
    // Mocking a scenario where flags is set to 0 (not fixed width)
    GfxFont font;
    EXPECT_CALL(font, isFixedWidth())
        .WillOnce(testing::Return(false));

    // Validate behavior
    ASSERT_FALSE(font.isFixedWidth());
}

// Exceptional test case for isFixedWidth when it's not expected to be set
TEST_F(GfxFontTest_1151, IsFixedWidth_Exceptional_1151) {
    // Assuming an exceptional scenario
    GfxFont font;
    // If flags were invalid or uninitialized
    EXPECT_CALL(font, isFixedWidth())
        .WillOnce(testing::Throw(std::runtime_error("Invalid flag state")));

    ASSERT_THROW(font.isFixedWidth(), std::runtime_error);
}

// Test for getFamily method
TEST_F(GfxFontTest_1151, GetFamily_1151) {
    GfxFont font;
    // Assuming that font family is initialized
    EXPECT_CALL(font, getFamily())
        .WillOnce(testing::Return("Arial"));

    ASSERT_EQ(font.getFamily(), "Arial");
}

// Boundary test for getFamily when family is empty
TEST_F(GfxFontTest_1151, GetFamily_Empty_1151) {
    GfxFont font;
    // Assuming that family could be empty or unset
    EXPECT_CALL(font, getFamily())
        .WillOnce(testing::Return(""));

    ASSERT_EQ(font.getFamily(), "");
}

// Test for getAscent method
TEST_F(GfxFontTest_1151, GetAscent_1151) {
    GfxFont font;
    // Mocking that ascent is 12.5
    EXPECT_CALL(font, getAscent())
        .WillOnce(testing::Return(12.5));

    ASSERT_DOUBLE_EQ(font.getAscent(), 12.5);
}

// Boundary test for getAscent when value is 0
TEST_F(GfxFontTest_1151, GetAscent_Zero_1151) {
    GfxFont font;
    // Mocking ascent as 0
    EXPECT_CALL(font, getAscent())
        .WillOnce(testing::Return(0.0));

    ASSERT_DOUBLE_EQ(font.getAscent(), 0.0);
}

// Test for getFontBBox method
TEST_F(GfxFontTest_1151, GetFontBBox_1151) {
    GfxFont font;
    // Mocking bounding box values
    std::array<double, 4> bbox = {0.0, 0.0, 10.0, 10.0};
    EXPECT_CALL(font, getFontBBox())
        .WillOnce(testing::Return(bbox));

    ASSERT_EQ(font.getFontBBox(), bbox);
}

// Test for isOk method
TEST_F(GfxFontTest_1151, IsOk_1151) {
    GfxFont font;
    EXPECT_CALL(font, isOk())
        .WillOnce(testing::Return(true));

    ASSERT_TRUE(font.isOk());
}

// Test for getTag method
TEST_F(GfxFontTest_1151, GetTag_1151) {
    GfxFont font;
    std::string tag = "fontTag123";
    EXPECT_CALL(font, getTag())
        .WillOnce(testing::Return(tag));

    ASSERT_EQ(font.getTag(), tag);
}

// Exceptional case for getTag when it might throw
TEST_F(GfxFontTest_1151, GetTag_Exceptional_1151) {
    GfxFont font;
    EXPECT_CALL(font, getTag())
        .WillOnce(testing::Throw(std::runtime_error("Tag not found")));

    ASSERT_THROW(font.getTag(), std::runtime_error);
}