#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLElementTest_92 : public ::testing::Test {

protected:

    XMLElement* element;



    virtual void SetUp() {

        element = new XMLElement(nullptr);

    }



    virtual void TearDown() {

        delete element;

    }

};



TEST_F(XMLElementTest_92, QueryAttribute_NormalOperation_Uint64_92) {

    uint64_t value = 0;

    element->SetAttribute("test", static_cast<uint64_t>(123));

    XMLError result = element->QueryAttribute("test", &value);

    EXPECT_EQ(result, XML_NO_ERROR);

    EXPECT_EQ(value, static_cast<uint64_t>(123));

}



TEST_F(XMLElementTest_92, QueryAttribute_AttributeNotFound_Uint64_92) {

    uint64_t value = 0;

    XMLError result = element->QueryAttribute("nonexistent", &value);

    EXPECT_EQ(result, XML_NO_ATTRIBUTE);

}



TEST_F(XMLElementTest_92, QueryAttribute_BoundaryCondition_MaxUint64_92) {

    uint64_t value = 0;

    element->SetAttribute("test", UINT64_MAX);

    XMLError result = element->QueryAttribute("test", &value);

    EXPECT_EQ(result, XML_NO_ERROR);

    EXPECT_EQ(value, UINT64_MAX);

}



TEST_F(XMLElementTest_92, QueryAttribute_BoundaryCondition_ZeroUint64_92) {

    uint64_t value = 0;

    element->SetAttribute("test", static_cast<uint64_t>(0));

    XMLError result = element->QueryAttribute("test", &value);

    EXPECT_EQ(result, XML_NO_ERROR);

    EXPECT_EQ(value, static_cast<uint64_t>(0));

}



TEST_F(XMLElementTest_92, QueryAttribute_InvalidName_Uint64_92) {

    uint64_t value = 0;

    XMLError result = element->QueryAttribute(nullptr, &value);

    EXPECT_EQ(result, XML_WRONG_ATTRIBUTE_TYPE);

}
