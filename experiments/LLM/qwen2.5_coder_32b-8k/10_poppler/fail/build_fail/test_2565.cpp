#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-structure-element.h"

#include "Object.h"



class PopplerStructureElementTest_2565 : public ::testing::Test {

protected:

    struct _PopplerStructureElement* mockStructureElement;

    

    void SetUp() override {

        mockStructureElement = new _PopplerStructureElement();

    }

    

    void TearDown() override {

        delete mockStructureElement;

    }

};



TEST_F(PopplerStructureElementTest_2565, GetStartIndent_ReturnsDefaultWhenAttributeNotFound_2565) {

    // Arrange

    double result;



    // Act

    result = poppler_structure_element_get_start_indent(mockStructureElement);



    // Assert

    EXPECT_DOUBLE_EQ(result, NAN);

}



TEST_F(PopplerStructureElementTest_2565, GetStartIndent_ReturnsCorrectValueWhenAttributeExists_2565) {

    // Arrange

    double expectedValue = 10.5;

    mockStructureElement->elem = new StructElement();

    // Assuming a function to set the attribute for testing purposes

    // This is just for simulation and should not be part of actual implementation

    mockStructureElement->elem->setAttribute(Attribute::StartIndent, Object(expectedValue));



    // Act

    double result = poppler_structure_element_get_start_indent(mockStructureElement);



    // Assert

    EXPECT_DOUBLE_EQ(result, expectedValue);



    // Cleanup

    delete mockStructureElement->elem;

}



TEST_F(PopplerStructureElementTest_2565, GetStartIndent_ReturnsNANForNonBlockElement_2565) {

    // Arrange

    double result;



    // Simulate non-block element by setting elem to nullptr or invalid state

    mockStructureElement->elem = nullptr;



    // Act

    result = poppler_structure_element_get_start_indent(mockStructureElement);



    // Assert

    EXPECT_DOUBLE_EQ(result, NAN);

}

```


