#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementSetAttributeDoubleTest_103 : public ::testing::Test {
protected:
    XMLDocument doc;
    XMLElement* elem;

    void SetUp() override {
        elem = doc.NewElement("TestElement");
        doc.InsertFirstChild(elem);
    }
};

// Test setting a double attribute with a normal positive value
TEST_F(XMLElementSetAttributeDoubleTest_103, SetDoubleAttributePositive_103) {
    elem->SetAttribute("value", 3.14);
    double result = elem->DoubleAttribute("value", 0.0);
    EXPECT_DOUBLE_EQ(result, 3.14);
}

// Test setting a double attribute with a negative value
TEST_F(XMLElementSetAttributeDoubleTest_103, SetDoubleAttributeNegative_103) {
    elem->SetAttribute("value", -2.718);
    double result = elem->DoubleAttribute("value", 0.0);
    EXPECT_DOUBLE_EQ(result, -2.718);
}

// Test setting a double attribute with zero
TEST_F(XMLElementSetAttributeDoubleTest_103, SetDoubleAttributeZero_103) {
    elem->SetAttribute("value", 0.0);
    double result = elem->DoubleAttribute("value", 999.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test setting a double attribute with a very large value
TEST_F(XMLElementSetAttributeDoubleTest_103, SetDoubleAttributeLargeValue_103) {
    elem->SetAttribute("value", 1.0e+300);
    double result = elem->DoubleAttribute("value", 0.0);
    EXPECT_DOUBLE_EQ(result, 1.0e+300);
}

// Test setting a double attribute with a very small positive value
TEST_F(XMLElementSetAttributeDoubleTest_103, SetDoubleAttributeSmallValue_103) {
    elem->SetAttribute("value", 1.0e-300);
    double result = elem->DoubleAttribute("value", 0.0);
    EXPECT_DOUBLE_EQ(result, 1.0e-300);
}

// Test setting a double attribute with negative zero
TEST_F(XMLElementSetAttributeDoubleTest_103, SetDoubleAttributeNegativeZero_103) {
    elem->SetAttribute("value", -0.0);
    double result = elem->DoubleAttribute("value", 999.0);
    // -0.0 == 0.0 in IEEE 754
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test overwriting an existing double attribute
TEST_F(XMLElementSetAttributeDoubleTest_103, SetDoubleAttributeOverwrite_103) {
    elem->SetAttribute("value", 1.0);
    elem->SetAttribute("value", 2.0);
    double result = elem->DoubleAttribute("value", 0.0);
    EXPECT_DOUBLE_EQ(result, 2.0);
}

// Test setting multiple different double attributes
TEST_F(XMLElementSetAttributeDoubleTest_103, SetMultipleDoubleAttributes_103) {
    elem->SetAttribute("x", 1.1);
    elem->SetAttribute("y", 2.2);
    elem->SetAttribute("z", 3.3);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("x", 0.0), 1.1);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("y", 0.0), 2.2);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("z", 0.0), 3.3);
}

// Test that SetAttribute with double creates the attribute if it doesn't exist
TEST_F(XMLElementSetAttributeDoubleTest_103, SetDoubleAttributeCreatesNew_103) {
    const XMLAttribute* attr = elem->FindAttribute("newattr");
    EXPECT_EQ(attr, nullptr);
    elem->SetAttribute("newattr", 42.5);
    attr = elem->FindAttribute("newattr");
    EXPECT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "newattr");
    double val = 0.0;
    EXPECT_EQ(attr->QueryDoubleValue(&val), XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 42.5);
}

// Test QueryDoubleAttribute after SetAttribute with double
TEST_F(XMLElementSetAttributeDoubleTest_103, QueryDoubleAttributeAfterSet_103) {
    elem->SetAttribute("pi", 3.14159265358979);
    double val = 0.0;
    XMLError err = elem->QueryDoubleAttribute("pi", &val);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_NEAR(val, 3.14159265358979, 1e-10);
}

// Test setting a double attribute with a fractional value
TEST_F(XMLElementSetAttributeDoubleTest_103, SetDoubleAttributeFractional_103) {
    elem->SetAttribute("frac", 0.123456789);
    double result = elem->DoubleAttribute("frac", 0.0);
    EXPECT_NEAR(result, 0.123456789, 1e-9);
}

// Test that the attribute value can be retrieved via Attribute() as a string
TEST_F(XMLElementSetAttributeDoubleTest_103, SetDoubleAttributeStringRepresentation_103) {
    elem->SetAttribute("val", 5.0);
    const char* str = elem->Attribute("val");
    EXPECT_NE(str, nullptr);
    // The string representation should be parseable back to a double
    double parsed = atof(str);
    EXPECT_DOUBLE_EQ(parsed, 5.0);
}

// Test overwriting a string attribute with a double attribute
TEST_F(XMLElementSetAttributeDoubleTest_103, OverwriteStringWithDouble_103) {
    elem->SetAttribute("attr", "hello");
    EXPECT_STREQ(elem->Attribute("attr"), "hello");
    elem->SetAttribute("attr", 99.99);
    double result = elem->DoubleAttribute("attr", 0.0);
    EXPECT_DOUBLE_EQ(result, 99.99);
}

// Test overwriting an int attribute with a double attribute
TEST_F(XMLElementSetAttributeDoubleTest_103, OverwriteIntWithDouble_103) {
    elem->SetAttribute("attr", 42);
    EXPECT_EQ(elem->IntAttribute("attr", 0), 42);
    elem->SetAttribute("attr", 42.5);
    double result = elem->DoubleAttribute("attr", 0.0);
    EXPECT_DOUBLE_EQ(result, 42.5);
}

// Test that FirstAttribute returns the attribute after setting a double
TEST_F(XMLElementSetAttributeDoubleTest_103, FirstAttributeAfterSetDouble_103) {
    elem->SetAttribute("first", 1.0);
    const XMLAttribute* attr = elem->FirstAttribute();
    EXPECT_NE(attr, nullptr);
    EXPECT_STREQ(attr->Name(), "first");
    EXPECT_DOUBLE_EQ(attr->DoubleValue(), 1.0);
}

// Test setting double attribute with integer-valued double
TEST_F(XMLElementSetAttributeDoubleTest_103, SetDoubleAttributeIntegerValued_103) {
    elem->SetAttribute("intlike", 100.0);
    double result = elem->DoubleAttribute("intlike", 0.0);
    EXPECT_DOUBLE_EQ(result, 100.0);
}

// Test that querying a non-existent attribute returns default value
TEST_F(XMLElementSetAttributeDoubleTest_103, DoubleAttributeDefaultWhenMissing_103) {
    double result = elem->DoubleAttribute("nonexistent", 7.77);
    EXPECT_DOUBLE_EQ(result, 7.77);
}

// Test QueryDoubleAttribute on non-existent attribute
TEST_F(XMLElementSetAttributeDoubleTest_103, QueryDoubleAttributeNonExistent_103) {
    double val = 0.0;
    XMLError err = elem->QueryDoubleAttribute("missing", &val);
    EXPECT_EQ(err, XML_NO_ATTRIBUTE);
}

// Test SetAttribute with double preserves other existing attributes
TEST_F(XMLElementSetAttributeDoubleTest_103, SetDoublePreservesOtherAttributes_103) {
    elem->SetAttribute("a", "text");
    elem->SetAttribute("b", 123);
    elem->SetAttribute("c", 4.56);
    EXPECT_STREQ(elem->Attribute("a"), "text");
    EXPECT_EQ(elem->IntAttribute("b", 0), 123);
    EXPECT_DOUBLE_EQ(elem->DoubleAttribute("c", 0.0), 4.56);
}

// Test printing/serialization after setting double attribute
TEST_F(XMLElementSetAttributeDoubleTest_103, SerializationAfterSetDouble_103) {
    elem->SetAttribute("val", 2.5);
    XMLPrinter printer;
    doc.Print(&printer);
    const char* result = printer.CStr();
    EXPECT_NE(result, nullptr);
    // The output should contain the attribute name
    EXPECT_NE(strstr(result, "val"), nullptr);
}

// Test setting double attribute on a parsed document element
TEST_F(XMLElementSetAttributeDoubleTest_103, SetDoubleOnParsedElement_103) {
    const char* xml = "<root existing=\"1.0\"/>";
    XMLDocument parsedDoc;
    EXPECT_EQ(parsedDoc.Parse(xml), XML_SUCCESS);
    XMLElement* root = parsedDoc.RootElement();
    EXPECT_NE(root, nullptr);
    root->SetAttribute("existing", 9.99);
    EXPECT_DOUBLE_EQ(root->DoubleAttribute("existing", 0.0), 9.99);
    root->SetAttribute("newdouble", 3.14);
    EXPECT_DOUBLE_EQ(root->DoubleAttribute("newdouble", 0.0), 3.14);
}
