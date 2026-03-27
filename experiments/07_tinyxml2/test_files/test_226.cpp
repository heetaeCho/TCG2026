#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_226 : public ::testing::Test {

protected:

    XMLElement element;

};



TEST_F(XMLElementTest_226, FindAttribute_NormalOperation_226) {

    XMLDocument doc;

    XMLElement* root = doc.NewElement("Root");

    root->SetAttribute("test", "value");

    element.LinkEndChild(root);



    const XMLAttribute* attr = element.FindAttribute("test");

    EXPECT_NE(attr, nullptr);

    EXPECT_STREQ(attr->Value(), "value");

}



TEST_F(XMLElementTest_226, FindAttribute_NotFound_226) {

    const XMLAttribute* attr = element.FindAttribute("nonexistent");

    EXPECT_EQ(attr, nullptr);

}



TEST_F(XMLElementTest_226, FindAttribute_BoundaryEmptyString_226) {

    const XMLAttribute* attr = element.FindAttribute("");

    EXPECT_EQ(attr, nullptr);

}



TEST_F(XMLElementTest_226, FindAttribute_BoundaryLongName_226) {

    std::string longName(1000, 'a');

    element.SetAttribute(longName.c_str(), "value");



    const XMLAttribute* attr = element.FindAttribute(longName.c_str());

    EXPECT_NE(attr, nullptr);

    EXPECT_STREQ(attr->Value(), "value");

}
