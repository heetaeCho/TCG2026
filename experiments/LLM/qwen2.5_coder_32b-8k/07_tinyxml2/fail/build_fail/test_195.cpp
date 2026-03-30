#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLTextTest_195 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLText* text1;

    XMLText* text2;

    XMLNode* node;



    void SetUp() override {

        text1 = new XMLText(&doc);

        text2 = new XMLText(&doc);

        node = new XMLText(&doc);



        text1->SetValue("TestValue", false);

        text2->SetValue("TestValue", false);

        node->SetValue("DifferentValue", false);

    }



    void TearDown() override {

        delete text1;

        delete text2;

        delete node;

    }

};



TEST_F(XMLTextTest_195, ShallowEqual_SameContent_ReturnsTrue_195) {

    EXPECT_TRUE(text1->ShallowEqual(text2));

}



TEST_F(XMLTextTest_195, ShallowEqual_DifferentContent_ReturnsFalse_195) {

    EXPECT_FALSE(text1->ShallowEqual(node));

}



TEST_F(XMLTextTest_195, ShallowEqual_NullPointer_ReturnsFalse_195) {

    EXPECT_FALSE(text1->ShallowEqual(nullptr));

}



TEST_F(XMLTextTest_195, ShallowEqual_DifferentType_ReturnsFalse_195) {

    XMLElement* element = new XMLElement(&doc);

    element->SetName("ElementName");

    EXPECT_FALSE(text1->ShallowEqual(element));

    delete element;

}
