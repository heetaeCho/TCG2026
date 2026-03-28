#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Annot.h"



using namespace testing;



class DefaultAppearanceTest : public ::testing::Test {

protected:

    std::unique_ptr<AnnotColor> createMockFontColor() {

        return std::make_unique<AnnotColor>();

    }

};



TEST_F(DefaultAppearanceTest_758, GetFontColor_ReturnsNonNullPointer_758) {

    auto fontColor = createMockFontColor();

    DefaultAppearance defaultAppearance("Arial", 12.0, std::move(fontColor));

    

    EXPECT_NE(defaultAppearance.getFontColor(), nullptr);

}



TEST_F(DefaultAppearanceTest_758, GetFontColor_ReturnsSamePointerAfterMove_758) {

    auto fontColor = createMockFontColor();

    const AnnotColor* expectedFontColorPtr = fontColor.get();

    DefaultAppearance defaultAppearance("Arial", 12.0, std::move(fontColor));

    

    EXPECT_EQ(defaultAppearance.getFontColor(), expectedFontColorPtr);

}



TEST_F(DefaultAppearanceTest_758, GetFontColor_ReturnsNullPointerWhenNoColorSet_758) {

    DefaultAppearance defaultAppearance("Arial", 12.0, -1);

    

    EXPECT_EQ(defaultAppearance.getFontColor(), nullptr);

}
