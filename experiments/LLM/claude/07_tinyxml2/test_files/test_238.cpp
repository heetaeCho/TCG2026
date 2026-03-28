#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetTextTest_238 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* CreateElement(const char* name = "test") {
        XMLElement* elem = doc.NewElement(name);
        doc.InsertEndChild(elem);
        return elem;
    }
};

// Test SetText with unsigned int - normal value
TEST_F(XMLElementSetTextTest_238, SetTextUnsigned_NormalValue_238) {
    XMLElement* elem = CreateElement();
    elem->SetText((unsigned)42);
    EXPECT_STREQ("42", elem->GetText());
}

// Test SetText with unsigned int - zero
TEST_F(XMLElementSetTextTest_238, SetTextUnsigned_Zero_238) {
    XMLElement* elem = CreateElement();
    elem->SetText((unsigned)0);
    EXPECT_STREQ("0", elem->GetText());
}

// Test SetText with unsigned int - max value
TEST_F(XMLElementSetTextTest_238, SetTextUnsigned_MaxValue_238) {
    XMLElement* elem = CreateElement();
    unsigned maxVal = UINT_MAX;
    elem->SetText(maxVal);
    
    unsigned result = 0;
    XMLError err = elem->QueryUnsignedText(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(maxVal, result);
}

// Test SetText with unsigned int - value of 1
TEST_F(XMLElementSetTextTest_238, SetTextUnsigned_One_238) {
    XMLElement* elem = CreateElement();
    elem->SetText((unsigned)1);
    EXPECT_STREQ("1", elem->GetText());
}

// Test SetText with unsigned int - large value
TEST_F(XMLElementSetTextTest_238, SetTextUnsigned_LargeValue_238) {
    XMLElement* elem = CreateElement();
    elem->SetText((unsigned)4294967295u);
    EXPECT_STREQ("4294967295", elem->GetText());
}

// Test SetText with unsigned int - verify QueryUnsignedText roundtrip
TEST_F(XMLElementSetTextTest_238, SetTextUnsigned_QueryRoundtrip_238) {
    XMLElement* elem = CreateElement();
    elem->SetText((unsigned)12345);
    
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(12345u, val);
}

// Test SetText with unsigned int - overwrite existing text
TEST_F(XMLElementSetTextTest_238, SetTextUnsigned_OverwriteExistingText_238) {
    XMLElement* elem = CreateElement();
    elem->SetText("old text");
    EXPECT_STREQ("old text", elem->GetText());
    
    elem->SetText((unsigned)999);
    EXPECT_STREQ("999", elem->GetText());
}

// Test SetText with unsigned int - overwrite existing unsigned text
TEST_F(XMLElementSetTextTest_238, SetTextUnsigned_OverwriteExistingUnsigned_238) {
    XMLElement* elem = CreateElement();
    elem->SetText((unsigned)100);
    EXPECT_STREQ("100", elem->GetText());
    
    elem->SetText((unsigned)200);
    EXPECT_STREQ("200", elem->GetText());
}

// Test SetText with int - normal value
TEST_F(XMLElementSetTextTest_238, SetTextInt_NormalValue_238) {
    XMLElement* elem = CreateElement();
    elem->SetText((int)42);
    EXPECT_STREQ("42", elem->GetText());
}

// Test SetText with int - negative value
TEST_F(XMLElementSetTextTest_238, SetTextInt_NegativeValue_238) {
    XMLElement* elem = CreateElement();
    elem->SetText((int)-42);
    EXPECT_STREQ("-42", elem->GetText());
}

// Test SetText with int - zero
TEST_F(XMLElementSetTextTest_238, SetTextInt_Zero_238) {
    XMLElement* elem = CreateElement();
    elem->SetText((int)0);
    EXPECT_STREQ("0", elem->GetText());
}

// Test SetText with bool - true
TEST_F(XMLElementSetTextTest_238, SetTextBool_True_238) {
    XMLElement* elem = CreateElement();
    elem->SetText(true);
    EXPECT_STREQ("true", elem->GetText());
}

// Test SetText with bool - false
TEST_F(XMLElementSetTextTest_238, SetTextBool_False_238) {
    XMLElement* elem = CreateElement();
    elem->SetText(false);
    EXPECT_STREQ("false", elem->GetText());
}

// Test SetText with double
TEST_F(XMLElementSetTextTest_238, SetTextDouble_NormalValue_238) {
    XMLElement* elem = CreateElement();
    elem->SetText(3.14);
    
    double val = 0.0;
    XMLError err = elem->QueryDoubleText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(3.14, val);
}

// Test SetText with float
TEST_F(XMLElementSetTextTest_238, SetTextFloat_NormalValue_238) {
    XMLElement* elem = CreateElement();
    elem->SetText(2.5f);
    
    float val = 0.0f;
    XMLError err = elem->QueryFloatText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(2.5f, val);
}

// Test SetText with int64_t
TEST_F(XMLElementSetTextTest_238, SetTextInt64_NormalValue_238) {
    XMLElement* elem = CreateElement();
    int64_t bigVal = 9223372036854775807LL;
    elem->SetText(bigVal);
    
    int64_t result = 0;
    XMLError err = elem->QueryInt64Text(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(bigVal, result);
}

// Test SetText with uint64_t
TEST_F(XMLElementSetTextTest_238, SetTextUint64_NormalValue_238) {
    XMLElement* elem = CreateElement();
    uint64_t bigVal = 18446744073709551615ULL;
    elem->SetText(bigVal);
    
    uint64_t result = 0;
    XMLError err = elem->QueryUnsigned64Text(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(bigVal, result);
}

// Test SetText with string
TEST_F(XMLElementSetTextTest_238, SetTextString_NormalValue_238) {
    XMLElement* elem = CreateElement();
    elem->SetText("Hello World");
    EXPECT_STREQ("Hello World", elem->GetText());
}

// Test GetText returns nullptr when no text child exists
TEST_F(XMLElementSetTextTest_238, GetText_NoTextChild_ReturnsNull_238) {
    XMLElement* elem = CreateElement();
    EXPECT_EQ(nullptr, elem->GetText());
}

// Test SetText with unsigned then verify IntText works with appropriate values
TEST_F(XMLElementSetTextTest_238, SetTextUnsigned_IntTextRoundtrip_238) {
    XMLElement* elem = CreateElement();
    elem->SetText((unsigned)500);
    
    int val = elem->IntText(0);
    EXPECT_EQ(500, val);
}

// Test UnsignedText with default value when no text is set
TEST_F(XMLElementSetTextTest_238, UnsignedText_DefaultValue_238) {
    XMLElement* elem = CreateElement();
    unsigned val = elem->UnsignedText(77u);
    EXPECT_EQ(77u, val);
}

// Test SetText with unsigned - medium value
TEST_F(XMLElementSetTextTest_238, SetTextUnsigned_MediumValue_238) {
    XMLElement* elem = CreateElement();
    elem->SetText((unsigned)1000000);
    EXPECT_STREQ("1000000", elem->GetText());
    
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_EQ(1000000u, val);
}

// Test SetText with const char* then SetText with unsigned overwrites
TEST_F(XMLElementSetTextTest_238, SetTextUnsigned_OverwriteStringWithUnsigned_238) {
    XMLElement* elem = CreateElement();
    elem->SetText("not a number");
    EXPECT_STREQ("not a number", elem->GetText());
    
    elem->SetText((unsigned)55);
    EXPECT_STREQ("55", elem->GetText());
}

// Test QueryUnsignedText on non-numeric text
TEST_F(XMLElementSetTextTest_238, QueryUnsignedText_NonNumericText_238) {
    XMLElement* elem = CreateElement();
    elem->SetText("abc");
    
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_NE(XML_SUCCESS, err);
}

// Test QueryUnsignedText on empty element (no text child)
TEST_F(XMLElementSetTextTest_238, QueryUnsignedText_NoText_238) {
    XMLElement* elem = CreateElement();
    
    unsigned val = 0;
    XMLError err = elem->QueryUnsignedText(&val);
    EXPECT_NE(XML_SUCCESS, err);
}
