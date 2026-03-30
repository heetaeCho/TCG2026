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

        doc.Clear();

    }

};



TEST_F(XMLElementTest_237, SetTextInt_NormalOperation_237) {

    int value = 123;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "123");

}



TEST_F(XMLElementTest_237, SetTextInt_ZeroValue_237) {

    int value = 0;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "0");

}



TEST_F(XMLElementTest_237, SetTextInt_NegativeValue_237) {

    int value = -456;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "-456");

}



TEST_F(XMLElementTest_237, SetTextUnsignedInt_NormalOperation_237) {

    unsigned int value = 123;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "123");

}



TEST_F(XMLElementTest_237, SetTextUnsignedInt_ZeroValue_237) {

    unsigned int value = 0;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "0");

}



TEST_F(XMLElementTest_237, SetTextLong_NormalOperation_237) {

    int64_t value = 123456789012345LL;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "123456789012345");

}



TEST_F(XMLElementTest_237, SetTextLong_ZeroValue_237) {

    int64_t value = 0LL;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "0");

}



TEST_F(XMLElementTest_237, SetTextULong_NormalOperation_237) {

    uint64_t value = 123456789012345ULL;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "123456789012345");

}



TEST_F(XMLElementTest_237, SetTextULong_ZeroValue_237) {

    uint64_t value = 0ULL;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "0");

}



TEST_F(XMLElementTest_237, SetTextBool_True_237) {

    bool value = true;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "1");

}



TEST_F(XMLElementTest_237, SetTextBool_False_237) {

    bool value = false;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "0");

}



TEST_F(XMLElementTest_237, SetTextFloat_NormalOperation_237) {

    float value = 123.456f;

    element->SetText(value);

    // Floating point precision might cause discrepancies, so we use a string comparison with tolerance

    EXPECT_TRUE(std::string(element->GetText()) == "123.456" || std::string(element->GetText()) == "123.4560");

}



TEST_F(XMLElementTest_237, SetTextFloat_ZeroValue_237) {

    float value = 0.0f;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "0");

}



TEST_F(XMLElementTest_237, SetTextDouble_NormalOperation_237) {

    double value = 123456789.123456789;

    element->SetText(value);

    // Floating point precision might cause discrepancies, so we use a string comparison with tolerance

    EXPECT_TRUE(std::string(element->GetText()) == "123456789.123456789" || std::string(element->GetText()).substr(0, 15) == "123456789.1234");

}



TEST_F(XMLElementTest_237, SetTextDouble_ZeroValue_237) {

    double value = 0.0;

    element->SetText(value);

    EXPECT_STREQ(element->GetText(), "0");

}
