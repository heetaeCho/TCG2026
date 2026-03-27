#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("testElement");

        doc.InsertFirstChild(element);

    }



    void TearDown() override {

        doc.Clear();

        element = nullptr;

    }

};



TEST_F(XMLElementTest_231, Unsigned64Attribute_DefaultValueReturnedWhenNoAttribute_231) {

    uint64_t result = element->Unsigned64Attribute("nonExistent", 123);

    EXPECT_EQ(result, 123u);

}



TEST_F(XMLElementTest_231, Unsigned64Attribute_ValueReturnedWhenAttributePresent_231) {

    element->SetAttribute("testAttr", "456");

    uint64_t result = element->Unsigned64Attribute("testAttr", 123);

    EXPECT_EQ(result, 456u);

}



TEST_F(XMLElementTest_231, Unsigned64Attribute_DefaultValueReturnedWhenInvalidValue_231) {

    element->SetAttribute("testAttr", "invalid");

    uint64_t result = element->Unsigned64Attribute("testAttr", 789);

    EXPECT_EQ(result, 789u);

}



TEST_F(XMLElementTest_231, Unsigned64Attribute_MaxValue_231) {

    element->SetAttribute("testAttr", "18446744073709551615");

    uint64_t result = element->Unsigned64Attribute("testAttr", 0);

    EXPECT_EQ(result, UINT64_MAX);

}



TEST_F(XMLElementTest_231, Unsigned64Attribute_ZeroValue_231) {

    element->SetAttribute("testAttr", "0");

    uint64_t result = element->Unsigned64Attribute("testAttr", 123);

    EXPECT_EQ(result, 0u);

}
