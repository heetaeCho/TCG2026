#include <gtest/gtest.h>

#include "StructElement.h"



class StructElementTest_1695 : public ::testing::Test {

protected:

    StructElement* element;

    StructElement* parentElement;

    StructTreeRoot treeRoot;



    void SetUp() override {

        parentElement = new StructElement(&treeRoot);

        element = new StructElement(parentElement);

    }



    void TearDown() override {

        delete element;

        delete parentElement;

    }

};



TEST_F(StructElementTest_1695, GetParentRef_ReturnsCorrectReference_1695) {

    Ref expectedRef = parentElement->getParentRef();

    EXPECT_EQ(expectedRef, element->getParentRef());

}



TEST_F(StructElementTest_1695, IsContent_ReturnsTrueForContentElement_1695) {

    StructElement contentElement(parentElement);

    EXPECT_TRUE(contentElement.isContent());

}



TEST_F(StructElementTest_1695, IsContent_ReturnsFalseForNonContentElement_1695) {

    element->parse(nullptr); // Assuming parse sets it to non-content

    EXPECT_FALSE(element->isContent());

}



TEST_F(StructElementTest_1695, GetParentRef_NonContentElement_ReturnsCorrectReference_1695) {

    Ref expectedRef = parentElement->getParentRef();

    element->parse(nullptr); // Assuming parse sets it to non-content

    EXPECT_EQ(expectedRef, element->getParentRef());

}



TEST_F(StructElementTest_1695, GetParentRef_ContentElement_ReturnsCorrectReference_1695) {

    Ref expectedRef = parentElement->getParentRef();

    StructElement contentElement(parentElement);

    EXPECT_EQ(expectedRef, contentElement.getParentRef());

}
