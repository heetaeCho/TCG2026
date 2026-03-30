#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annot.h"

#include "poppler-private.h"



using namespace testing;



// Mocking external collaborators if needed

class MockAnnot {

public:

    MOCK_METHOD(PopplerColor*, getColor, (), (const));

};



TEST_F(PopplerAnnotTest_2069, GetColor_ReturnsValidPointer_2069) {

    auto mock_annot = std::make_shared<MockAnnot>();

    PopplerAnnot poppler_annot;

    poppler_annot.annot = mock_annot;



    EXPECT_CALL(*mock_annot, getColor()).WillOnce(Return(new PopplerColor()));



    PopplerColor* result = poppler_annot_get_color(&poppler_annot);

    ASSERT_NE(result, nullptr);



    delete result; // Clean up the allocated memory

}



TEST_F(PopplerAnnotTest_2069, GetColor_ReturnsSamePointerOnSubsequentCalls_2069) {

    auto mock_annot = std::make_shared<MockAnnot>();

    PopplerAnnot poppler_annot;

    poppler_annot.annot = mock_annot;



    PopplerColor* expected_color = new PopplerColor();

    EXPECT_CALL(*mock_annot, getColor()).WillRepeatedly(Return(expected_color));



    PopplerColor* result1 = poppler_annot_get_color(&poppler_annot);

    PopplerColor* result2 = poppler_annot_get_color(&poppler_annot);



    ASSERT_EQ(result1, expected_color);

    ASSERT_EQ(result2, expected_color);



    delete expected_color; // Clean up the allocated memory

}



TEST_F(PopplerAnnotTest_2069, GetColor_ReturnsNullForInvalidInput_2069) {

    PopplerAnnot* invalid_poppler_annot = nullptr;



    PopplerColor* result = poppler_annot_get_color(invalid_poppler_annot);

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerAnnotTest_2069, GetColor_ReturnsNullWhenInternalPointerIsNull_2069) {

    PopplerAnnot poppler_annot;

    poppler_annot.annot = nullptr;



    PopplerColor* result = poppler_annot_get_color(&poppler_annot);

    ASSERT_EQ(result, nullptr);

}
