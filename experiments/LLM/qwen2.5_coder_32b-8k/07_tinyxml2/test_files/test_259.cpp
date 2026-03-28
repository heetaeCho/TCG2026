#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <gmock/gmock.h>



using namespace tinyxml2;

using testing::Eq;



class XMLElementTest : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* rootElement;



    XMLElementTest() : doc(false, Whitespace::COLLAPSE) {

        rootElement = doc.NewElement("root");

        doc.InsertFirstChild(rootElement);

    }

};



TEST_F(XMLElementTest_259, InsertNewChildElement_Success_259) {

    XMLElement* child = rootElement->InsertNewChildElement("child");

    EXPECT_NE(child, nullptr);

    EXPECT_STREQ(child->Value(), "child");

}



TEST_F(XMLElementTest_259, InsertNewChildElement_MultipleChildren_259) {

    rootElement->InsertNewChildElement("child1");

    rootElement->InsertNewChildElement("child2");



    const XMLElement* child1 = rootElement->FirstChildElement();

    const XMLElement* child2 = child1 ? child1->NextSiblingElement() : nullptr;



    EXPECT_STREQ(child1->Value(), "child1");

    EXPECT_STREQ(child2->Value(), "child2");

}



TEST_F(XMLElementTest_259, InsertNewChildElement_EmptyName_259) {

    XMLElement* child = rootElement->InsertNewChildElement("");

    EXPECT_NE(child, nullptr);

    EXPECT_STREQ(child->Value(), "");

}



TEST_F(XMLElementTest_259, InsertNewChildElement_NullName_259) {

    XMLElement* child = rootElement->InsertNewChildElement(nullptr);

    EXPECT_EQ(child, nullptr);

}
