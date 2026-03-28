#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/Annot.h"



using namespace testing;



// Mock class for AnnotBorder if needed in future tests involving external collaborators

class MockAnnotBorder : public AnnotBorder {

public:

    MOCK_METHOD(double, getWidth, (), (const, override));

};



TEST_F(AnnotBorderTest_747, GetWidth_DefaultValue_747) {

    AnnotBorder border;

    EXPECT_EQ(border.getWidth(), 0.0);

}



TEST_F(AnnotBorderTest_747, SetWidth_ValidValue_747) {

    AnnotBorder border;

    border.setWidth(5.0);

    EXPECT_EQ(border.getWidth(), 5.0);

}



TEST_F(AnnotBorderTest_747, SetWidth_ZeroValue_747) {

    AnnotBorder border;

    border.setWidth(0.0);

    EXPECT_EQ(border.getWidth(), 0.0);

}



TEST_F(AnnotBorderTest_747, SetWidth_NegativeValue_747) {

    AnnotBorder border;

    border.setWidth(-5.0);

    EXPECT_EQ(border.getWidth(), -5.0);

}
