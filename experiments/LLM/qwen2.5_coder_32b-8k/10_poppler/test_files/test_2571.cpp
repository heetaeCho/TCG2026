#include <gtest/gtest.h>

#include "poppler-structure-element.h"

#include "Object.h"



class PopplerStructureElementTest_2571 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize a mock or dummy PopplerStructureElement if needed

        poppler_structure_element = new PopplerStructureElement();

    }



    void TearDown() override {

        delete poppler_structure_element;

    }



    PopplerStructureElement* poppler_structure_element;

};



TEST_F(PopplerStructureElementTest_2571, GetHeight_ReturnsValidNumber_2571) {

    // Arrange

    Object mockObject(0.0);

    EXPECT_CALL(mockAttrValueOrDefault, Call(poppler_structure_element, Attribute::Height)).WillOnce(::testing::Return(&mockObject));



    // Act

    gdouble result = poppler_structure_element_get_height(poppler_structure_element);



    // Assert

    EXPECT_EQ(result, 0.0);

}



TEST_F(PopplerStructureElementTest_2571, GetHeight_ReturnsNegativeOneForAuto_2571) {

    // Arrange

    Object mockObject("Auto");

    EXPECT_CALL(mockAttrValueOrDefault, Call(poppler_structure_element, Attribute::Height)).WillOnce(::testing::Return(&mockObject));



    // Act

    gdouble result = poppler_structure_element_get_height(poppler_structure_element);



    // Assert

    EXPECT_EQ(result, -1.0);

}



TEST_F(PopplerStructureElementTest_2571, GetHeight_ReturnsNANForNonBlock_2571) {

    // Arrange

    EXPECT_CALL(mockPopplerStructureElementIsBlock, Call(poppler_structure_element)).WillOnce(::testing::Return(false));



    // Act

    gdouble result = poppler_structure_element_get_height(poppler_structure_element);



    // Assert

    EXPECT_TRUE(std::isnan(result));

}



TEST_F(PopplerStructureElementTest_2571, GetHeight_HandlesNullObject_2571) {

    // Arrange

    Object mockObject(Object::null());

    EXPECT_CALL(mockAttrValueOrDefault, Call(poppler_structure_element, Attribute::Height)).WillOnce(::testing::Return(&mockObject));



    // Act

    gdouble result = poppler_structure_element_get_height(poppler_structure_element);



    // Assert

    EXPECT_TRUE(std::isnan(result));

}



TEST_F(PopplerStructureElementTest_2571, GetHeight_HandlesErrorObject_2571) {

    // Arrange

    Object mockObject(Object::error());

    EXPECT_CALL(mockAttrValueOrDefault, Call(poppler_structure_element, Attribute::Height)).WillOnce(::testing::Return(&mockObject));



    // Act

    gdouble result = poppler_structure_element_get_height(poppler_structure_element);



    // Assert

    EXPECT_TRUE(std::isnan(result));

}

```


