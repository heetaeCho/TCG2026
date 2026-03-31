#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

// Helper fixture that creates XMLDocument and elements to access XMLAttribute
class XMLAttributeTest_209 : public ::testing::Test {
protected:
    XMLDocument doc;

    XMLElement* CreateElementWithAttribute(const char* elemName, const char* attrName, const char* attrValue) {
        XMLElement* elem = doc.NewElement(elemName);
        doc.InsertFirstChild(elem);
        elem->SetAttribute(attrName, attrValue);
        return elem;
    }
};

// Test Name() returns the correct attribute name
TEST_F(XMLAttributeTest_209, NameReturnsCorrectName_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "myattr", "value");
    const XMLAttribute* attr = elem->FindAttribute("myattr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "myattr");
}

// Test Value() returns the correct attribute value
TEST_F(XMLAttributeTest_209, ValueReturnsCorrectValue_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "attr", "hello");
    const XMLAttribute* attr = elem->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello");
}

// Test SetAttribute with string value
TEST_F(XMLAttributeTest_209, SetAttributeString_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "key", "initial");
    elem->SetAttribute("key", "updated");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "updated");
}

// Test SetAttribute with int value
TEST_F(XMLAttributeTest_209, SetAttributeInt_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "0");
    elem->SetAttribute("num", 42);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), 42);
}

// Test SetAttribute with unsigned int value
TEST_F(XMLAttributeTest_209, SetAttributeUnsigned_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "0");
    elem->SetAttribute("num", (unsigned)123);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 123u);
}

// Test SetAttribute with int64_t value
TEST_F(XMLAttributeTest_209, SetAttributeInt64_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "0");
    elem->SetAttribute("num", (int64_t)9223372036854775807LL);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), 9223372036854775807LL);
}

// Test SetAttribute with uint64_t value
TEST_F(XMLAttributeTest_209, SetAttributeUnsigned64_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "0");
    elem->SetAttribute("num", (uint64_t)18446744073709551615ULL);
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Unsigned64Value(), 18446744073709551615ULL);
}

// Test SetAttribute with bool value true
TEST_F(XMLAttributeTest_209, SetAttributeBoolTrue_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "flag", "false");
    elem->SetAttribute("flag", true);
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), true);
}

// Test SetAttribute with bool value false
TEST_F(XMLAttributeTest_209, SetAttributeBoolFalse_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "flag", "true");
    elem->SetAttribute("flag", false);
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->BoolValue(), false);
}

// Test SetAttribute with double value
TEST_F(XMLAttributeTest_209, SetAttributeDouble_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "0");
    elem->SetAttribute("val", 3.14159);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->DoubleValue(), 3.14159, 0.0001);
}

// Test SetAttribute with float value
TEST_F(XMLAttributeTest_209, SetAttributeFloat_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "0");
    elem->SetAttribute("val", 2.5f);
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->FloatValue(), 2.5f, 0.001f);
}

// Test QueryIntValue with valid int
TEST_F(XMLAttributeTest_209, QueryIntValueValid_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "100");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    XMLError err = attr->QueryIntValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 100);
}

// Test QueryIntValue with invalid string
TEST_F(XMLAttributeTest_209, QueryIntValueInvalid_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "notanumber");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    int val = 0;
    XMLError err = attr->QueryIntValue(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test QueryUnsignedValue with valid unsigned
TEST_F(XMLAttributeTest_209, QueryUnsignedValueValid_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "200");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    unsigned val = 0;
    XMLError err = attr->QueryUnsignedValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 200u);
}

// Test QueryInt64Value with valid int64
TEST_F(XMLAttributeTest_209, QueryInt64ValueValid_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "9223372036854775807");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    int64_t val = 0;
    XMLError err = attr->QueryInt64Value(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 9223372036854775807LL);
}

// Test QueryUnsigned64Value with valid uint64
TEST_F(XMLAttributeTest_209, QueryUnsigned64ValueValid_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "18446744073709551615");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    uint64_t val = 0;
    XMLError err = attr->QueryUnsigned64Value(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 18446744073709551615ULL);
}

// Test QueryBoolValue with "true"
TEST_F(XMLAttributeTest_209, QueryBoolValueTrue_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "flag", "true");
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    bool val = false;
    XMLError err = attr->QueryBoolValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, true);
}

// Test QueryBoolValue with "false"
TEST_F(XMLAttributeTest_209, QueryBoolValueFalse_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "flag", "false");
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    bool val = true;
    XMLError err = attr->QueryBoolValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, false);
}

// Test QueryBoolValue with invalid string
TEST_F(XMLAttributeTest_209, QueryBoolValueInvalid_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "flag", "notbool");
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    bool val = false;
    XMLError err = attr->QueryBoolValue(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test QueryDoubleValue with valid double
TEST_F(XMLAttributeTest_209, QueryDoubleValueValid_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "3.14");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    double val = 0.0;
    XMLError err = attr->QueryDoubleValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 3.14, 0.001);
}

// Test QueryDoubleValue with invalid string
TEST_F(XMLAttributeTest_209, QueryDoubleValueInvalid_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "abc");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    double val = 0.0;
    XMLError err = attr->QueryDoubleValue(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test QueryFloatValue with valid float
TEST_F(XMLAttributeTest_209, QueryFloatValueValid_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "1.5");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    float val = 0.0f;
    XMLError err = attr->QueryFloatValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 1.5f, 0.001f);
}

// Test QueryFloatValue with invalid string
TEST_F(XMLAttributeTest_209, QueryFloatValueInvalid_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "xyz");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    float val = 0.0f;
    XMLError err = attr->QueryFloatValue(&val);
    EXPECT_NE(err, XML_SUCCESS);
}

// Test Next() returns nullptr when there is only one attribute
TEST_F(XMLAttributeTest_209, NextReturnsNullWhenSingleAttribute_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "only", "one");
    const XMLAttribute* attr = elem->FindAttribute("only");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Next(), nullptr);
}

// Test Next() returns next attribute when multiple exist
TEST_F(XMLAttributeTest_209, NextReturnsNextAttribute_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "first", "1");
    elem->SetAttribute("second", "2");
    const XMLAttribute* attr = elem->FindAttribute("first");
    ASSERT_NE(attr, nullptr);
    const XMLAttribute* next = attr->Next();
    ASSERT_NE(next, nullptr);
    EXPECT_STREQ(next->Name(), "second");
    EXPECT_STREQ(next->Value(), "2");
}

// Test empty attribute value
TEST_F(XMLAttributeTest_209, EmptyAttributeValue_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "empty", "");
    const XMLAttribute* attr = elem->FindAttribute("empty");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "");
}

// Test attribute name with special but valid characters
TEST_F(XMLAttributeTest_209, NameWithUnderscoreAndDash_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "my-attr_name", "val");
    const XMLAttribute* attr = elem->FindAttribute("my-attr_name");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "my-attr_name");
}

// Test IntValue convenience function
TEST_F(XMLAttributeTest_209, IntValueConvenience_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "-42");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->IntValue(), -42);
}

// Test negative int64 value
TEST_F(XMLAttributeTest_209, NegativeInt64Value_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "-9223372036854775807");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->Int64Value(), -9223372036854775807LL);
}

// Test UnsignedValue
TEST_F(XMLAttributeTest_209, UnsignedValueConvenience_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "4294967295");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    EXPECT_EQ(attr->UnsignedValue(), 4294967295u);
}

// Test DoubleValue convenience
TEST_F(XMLAttributeTest_209, DoubleValueConvenience_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "1.23456789");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->DoubleValue(), 1.23456789, 0.0000001);
}

// Test FloatValue convenience
TEST_F(XMLAttributeTest_209, FloatValueConvenience_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "val", "1.5");
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(attr, nullptr);
    EXPECT_NEAR(attr->FloatValue(), 1.5f, 0.001f);
}

// Test GetLineNum for attribute parsed from XML
TEST_F(XMLAttributeTest_209, GetLineNumFromParsedXML_209) {
    const char* xml = "<root attr=\"val\"/>";
    doc.Parse(xml);
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_GE(attr->GetLineNum(), 1);
}

// Test parsing XML with multiple attributes
TEST_F(XMLAttributeTest_209, MultipleAttributesParsed_209) {
    const char* xml = "<root a=\"1\" b=\"2\" c=\"3\"/>";
    doc.Parse(xml);
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    const XMLAttribute* a = root->FindAttribute("a");
    ASSERT_NE(a, nullptr);
    EXPECT_STREQ(a->Value(), "1");

    const XMLAttribute* b = root->FindAttribute("b");
    ASSERT_NE(b, nullptr);
    EXPECT_STREQ(b->Value(), "2");

    const XMLAttribute* c = root->FindAttribute("c");
    ASSERT_NE(c, nullptr);
    EXPECT_STREQ(c->Value(), "3");
}

// Test SetAttribute overwrites existing value
TEST_F(XMLAttributeTest_209, SetAttributeOverwritesValue_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "key", "old");
    const XMLAttribute* attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "old");

    elem->SetAttribute("key", "new");
    attr = elem->FindAttribute("key");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "new");
}

// Test QueryIntValue with zero
TEST_F(XMLAttributeTest_209, QueryIntValueZero_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "0");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    int val = -1;
    XMLError err = attr->QueryIntValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, 0);
}

// Test QueryUnsignedValue with invalid negative
TEST_F(XMLAttributeTest_209, QueryUnsignedValueNegative_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "num", "-1");
    const XMLAttribute* attr = elem->FindAttribute("num");
    ASSERT_NE(attr, nullptr);
    unsigned val = 0;
    // Behavior depends on implementation; just call it
    attr->QueryUnsignedValue(&val);
    // We don't assert specific behavior for this edge case
}

// Test BoolValue with "1"
TEST_F(XMLAttributeTest_209, QueryBoolValue1_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "flag", "1");
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    bool val = false;
    XMLError err = attr->QueryBoolValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, true);
}

// Test BoolValue with "0"
TEST_F(XMLAttributeTest_209, QueryBoolValue0_209) {
    XMLElement* elem = CreateElementWithAttribute("test", "flag", "0");
    const XMLAttribute* attr = elem->FindAttribute("flag");
    ASSERT_NE(attr, nullptr);
    bool val = true;
    XMLError err = attr->QueryBoolValue(&val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(val, false);
}

// Test attribute with special characters in value
TEST_F(XMLAttributeTest_209, SpecialCharactersInValue_209) {
    const char* xml = "<root attr=\"hello &amp; world\"/>";
    doc.Parse(xml);
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);
    const XMLAttribute* attr = root->FindAttribute("attr");
    ASSERT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Value(), "hello & world");
}

// Test traversal of all attributes via Next()
TEST_F(XMLAttributeTest_209, TraverseAllAttributes_209) {
    const char* xml = "<root a=\"1\" b=\"2\" c=\"3\" d=\"4\"/>";
    doc.Parse(xml);
    const XMLElement* root = doc.FirstChildElement("root");
    ASSERT_NE(root, nullptr);

    int count = 0;
    for (const XMLAttribute* attr = root->FirstAttribute(); attr; attr = attr->Next()) {
        count++;
    }
    EXPECT_EQ(count, 4);
}
