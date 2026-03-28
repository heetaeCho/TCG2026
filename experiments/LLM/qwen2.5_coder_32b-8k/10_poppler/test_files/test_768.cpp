#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Annot.h"

#include <memory>



// Mock class for AnnotColor to verify interactions

class MockAnnotColor : public AnnotColor {

public:

    MOCK_METHOD(void, someMethod, (), (const));

};



TEST_F(AnnotAppearanceCharacsTest_768, SetBackColor_SetsColorPointer_768) {

    std::unique_ptr<MockAnnotColor> mockColor = std::make_unique<MockAnnotColor>();

    AnnotAppearanceCharacs annotAppearance(nullptr);

    annotAppearance.setBackColor(std::move(mockColor));

    EXPECT_NE(annotAppearance.getBackColor(), nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_768, SetBackColor_ReplacesPreviousColor_768) {

    std::unique_ptr<MockAnnotColor> mockColor1 = std::make_unique<MockAnnotColor>();

    std::unique_ptr<MockAnnotColor> mockColor2 = std::make_unique<MockAnnotColor>();

    AnnotAppearanceCharacs annotAppearance(nullptr);

    annotAppearance.setBackColor(std::move(mockColor1));

    auto firstColor = annotAppearance.getBackColor();

    annotAppearance.setBackColor(std::move(mockColor2));

    EXPECT_NE(annotAppearance.getBackColor(), firstColor);

}



TEST_F(AnnotAppearanceCharacsTest_768, SetBackColor_NullptrAccepted_768) {

    AnnotAppearanceCharacs annotAppearance(nullptr);

    std::unique_ptr<MockAnnotColor> mockColor = nullptr;

    annotAppearance.setBackColor(std::move(mockColor));

    EXPECT_EQ(annotAppearance.getBackColor(), nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_768, SetBackColor_NoSideEffectsOnNullptr_768) {

    AnnotAppearanceCharacs annotAppearance(nullptr);

    std::unique_ptr<MockAnnotColor> mockColor = std::make_unique<MockAnnotColor>();

    annotAppearance.setBackColor(std::move(mockColor));

    auto firstColor = annotAppearance.getBackColor();

    annotAppearance.setBackColor(nullptr);

    EXPECT_EQ(annotAppearance.getBackColor(), nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_768, GetBackColor_ReturnsSetPointer_768) {

    std::unique_ptr<MockAnnotColor> mockColor = std::make_unique<MockAnnotColor>();

    AnnotAppearanceCharacs annotAppearance(nullptr);

    annotAppearance.setBackColor(std::move(mockColor));

    EXPECT_NE(annotAppearance.getBackColor(), nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_768, GetBackColor_ReturnsNullptrWhenNotSet_768) {

    AnnotAppearanceCharacs annotAppearance(nullptr);

    EXPECT_EQ(annotAppearance.getBackColor(), nullptr);

}
