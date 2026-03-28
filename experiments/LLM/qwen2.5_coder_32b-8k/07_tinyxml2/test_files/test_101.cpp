#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("TestElement");

        doc.InsertFirstChild(element);

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(XMLElementTest_101, SetAttribute_SetsUint64Value_101) {

    const char* attrName = "testAttr";

    uint64_t value = 123456789012345ULL;



    element->SetAttribute(attrName, value);



    const XMLAttribute* attribute = element->FindAttribute(attrName);

    ASSERT_NE(attribute, nullptr);

    EXPECT_EQ(attribute->Unsigned64Value(), value);

}



TEST_F(XMLElementTest_101, SetAttribute_UpdatesExistingAttribute_101) {

    const char* attrName = "testAttr";

    uint64_t initialValue = 12345ULL;

    uint64_t updatedValue = 67890ULL;



    element->SetAttribute(attrName, initialValue);

    element->SetAttribute(attrName, updatedValue);



    const XMLAttribute* attribute = element->FindAttribute(attrName);

    ASSERT_NE(attribute, nullptr);

    EXPECT_EQ(attribute->Unsigned64Value(), updatedValue);

}



TEST_F(XMLElementTest_101, SetAttribute_EmptyAttributeName_101) {

    const char* attrName = "";

    uint64_t value = 987654321ULL;



    element->SetAttribute(attrName, value);



    const XMLAttribute* attribute = element->FindAttribute(attrName);

    EXPECT_EQ(attribute, nullptr); // Assuming empty name is not allowed

}



TEST_F(XMLElementTest_101, SetAttribute_NullAttributeName_101) {

    const char* attrName = nullptr;

    uint64_t value = 987654321ULL;



    element->SetAttribute(attrName, value);



    const XMLAttribute* attribute = element->FindAttribute("");

    EXPECT_EQ(attribute, nullptr); // Assuming null name is not allowed

}
