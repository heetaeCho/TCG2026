#include <gtest/gtest.h>

#include <tinyxml2.h>



using namespace tinyxml2;



class XMLElementTest_230 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLElement* element;



    void SetUp() override {

        element = doc.NewElement("TestElement");

        doc.InsertEndChild(element);

    }



    void TearDown() override {

        doc.Clear();

    }

};



TEST_F(XMLElementTest_230, Int64Attribute_DefaultValue_230) {

    int64_t defaultValue = 12345;

    int64_t result = element->Int64Attribute("nonexistent", defaultValue);

    EXPECT_EQ(result, defaultValue);

}



TEST_F(XMLElementTest_230, Int64Attribute_NormalOperation_230) {

    element->SetAttribute("testattr", "98765");

    int64_t result = element->Int64Attribute("testattr", 0);

    EXPECT_EQ(result, 98765);

}



TEST_F(XMLElementTest_230, Int64Attribute_OutOfRangeValue_230) {

    element->SetAttribute("testattr", "18446744073709551615"); // UINT64_MAX

    int64_t result = element->Int64Attribute("testattr", 0);

    EXPECT_EQ(result, INT64_MIN); // This will actually be negative due to overflow

}



TEST_F(XMLElementTest_230, Int64Attribute_NegativeValue_230) {

    element->SetAttribute("testattr", "-98765");

    int64_t result = element->Int64Attribute("testattr", 0);

    EXPECT_EQ(result, -98765);

}



TEST_F(XMLElementTest_230, Int64Attribute_EmptyString_230) {

    element->SetAttribute("testattr", "");

    int64_t defaultValue = 12345;

    int64_t result = element->Int64Attribute("testattr", defaultValue);

    EXPECT_EQ(result, defaultValue);

}



TEST_F(XMLElementTest_230, Int64Attribute_NonNumericString_230) {

    element->SetAttribute("testattr", "abc");

    int64_t defaultValue = 12345;

    int64_t result = element->Int64Attribute("testattr", defaultValue);

    EXPECT_EQ(result, defaultValue);

}
