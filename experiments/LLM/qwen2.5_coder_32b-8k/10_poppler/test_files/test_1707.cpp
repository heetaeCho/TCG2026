#include <gtest/gtest.h>

#include "StructElement.h"



class StructElementTest : public ::testing::Test {

protected:

    void SetUp() override {

        element = new StructElement();

        childElement = new StructElement();

    }



    void TearDown() override {

        delete element;

        delete childElement;

    }



    StructElement* element;

    StructElement* childElement;

};



TEST_F(StructElementTest_1707, AppendChild_Successful_1707) {

    EXPECT_TRUE(element->isOk());

    EXPECT_TRUE(childElement->isOk());

    element->appendChild(childElement);

    EXPECT_EQ(element->getNumChildren(), 1U);

}



TEST_F(StructElementTest_1707, AppendChild_ContentElement_Fails_1707) {

    // Assuming isContent() returns true for some condition

    childElement->s = nullptr; // Mocking content element by setting s to nullptr

    element->appendChild(childElement);

    EXPECT_EQ(element->getNumChildren(), 0U);

}



TEST_F(StructElementTest_1707, AppendChild_NullChild_Fails_1707) {

    element->appendChild(nullptr);

    EXPECT_EQ(element->getNumChildren(), 0U);

}



TEST_F(StructElementTest_1707, AppendChild_NotOkChild_Fails_1707) {

    childElement->s = nullptr; // Mocking not ok element by setting s to nullptr

    element->appendChild(childElement);

    EXPECT_EQ(element->getNumChildren(), 0U);

}



TEST_F(StructElementTest_1707, GetNumChildren_BoundaryConditions_1707) {

    EXPECT_EQ(element->getNumChildren(), 0U);

    element->appendChild(childElement);

    EXPECT_EQ(element->getNumChildren(), 1U);

}



TEST_F(StructElementTest_1707, GetChild_ValidIndex_ReturnsChild_1707) {

    element->appendChild(childElement);

    EXPECT_EQ(element->getChild(0), childElement);

}



TEST_F(StructElementTest_1707, GetChild_OutOfBounds_ReturnsNull_1707) {

    EXPECT_EQ(element->getChild(0), nullptr);

}
