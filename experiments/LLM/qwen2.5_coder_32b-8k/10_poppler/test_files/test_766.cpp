#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Annot.h"

#include <memory>



using namespace std;



// Mock class for AnnotColor to verify interactions

class MockAnnotColor : public AnnotColor {

public:

    MOCK_METHOD0(clone, AnnotColor*());

};



TEST_F(AnnotAppearanceCharacsTest_766, SetBorderColor_ValidPointer_766) {

    unique_ptr<MockAnnotColor> mockColor = make_unique<MockAnnotColor>();

    AnnotAppearanceCharacs characs(nullptr);

    characs.setBorderColor(move(mockColor));

}



TEST_F(AnnotAppearanceCharacsTest_766, GetBorderColor_AfterSet_766) {

    unique_ptr<MockAnnotColor> mockColor = make_unique<MockAnnotColor>();

    const AnnotColor* rawPtr = mockColor.get();

    AnnotAppearanceCharacs characs(nullptr);

    characs.setBorderColor(move(mockColor));

    EXPECT_EQ(rawPtr, characs.getBorderColor());

}



TEST_F(AnnotAppearanceCharacsTest_766, SetBorderColor_NullPointer_766) {

    unique_ptr<MockAnnotColor> mockColor = nullptr;

    AnnotAppearanceCharacs characs(nullptr);

    characs.setBorderColor(move(mockColor));

    EXPECT_EQ(nullptr, characs.getBorderColor());

}



TEST_F(AnnotAppearanceCharacsTest_766, GetBorderColor_DefaultConstructor_766) {

    AnnotAppearanceCharacs characs(nullptr);

    EXPECT_EQ(nullptr, characs.getBorderColor());

}
