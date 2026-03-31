#include <gtest/gtest.h>
#include "tinyxml2.h"
#include <cmath>
#include <limits>
#include <string>

using namespace tinyxml2;

// Helper: We can't directly construct XMLAttribute (private constructor/destructor),
// so we use XMLDocument to create elements with attributes and then access them.

class XMLAttributeSetAttributeDoubleTest_224 : public ::testing::Test {
protected:
    XMLDocument doc;

    // Helper to create an element with an attribute and return the attribute
    XMLElement* CreateElementWithAttribute(const char* attrName, const char* initialValue) {
        XMLElement* elem = doc.NewElement("test");
        doc.InsertFirstChild(elem);
        elem->SetAttribute(attrName, initialValue);
        return elem;
    }
};

// Test setting a normal positive double value
TEST_F(XMLAttributeSetAttributeDoubleTest_224, SetPositiveDouble_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    elem->SetAttribute("val", 3.14);
    
    double result = 0.0;
    XMLError err = elem->QueryDoubleAttribute("val", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(3.14, result);
}

// Test setting a negative double value
TEST_F(XMLAttributeSetAttributeDoubleTest_224, SetNegativeDouble_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    elem->SetAttribute("val", -2.718);
    
    double result = 0.0;
    XMLError err = elem->QueryDoubleAttribute("val", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(-2.718, result);
}

// Test setting zero
TEST_F(XMLAttributeSetAttributeDoubleTest_224, SetZeroDouble_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "1.0");
    elem->SetAttribute("val", 0.0);
    
    double result = 1.0;
    XMLError err = elem->QueryDoubleAttribute("val", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(0.0, result);
}

// Test setting negative zero
TEST_F(XMLAttributeSetAttributeDoubleTest_224, SetNegativeZeroDouble_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "1.0");
    elem->SetAttribute("val", -0.0);
    
    double result = 1.0;
    XMLError err = elem->QueryDoubleAttribute("val", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    // -0.0 == 0.0 in IEEE 754
    EXPECT_DOUBLE_EQ(0.0, result);
}

// Test setting a very small double value
TEST_F(XMLAttributeSetAttributeDoubleTest_224, SetVerySmallDouble_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    double tiny = 1e-300;
    elem->SetAttribute("val", tiny);
    
    double result = 0.0;
    XMLError err = elem->QueryDoubleAttribute("val", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(tiny, result);
}

// Test setting a very large double value
TEST_F(XMLAttributeSetAttributeDoubleTest_224, SetVeryLargeDouble_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    double large = 1e+300;
    elem->SetAttribute("val", large);
    
    double result = 0.0;
    XMLError err = elem->QueryDoubleAttribute("val", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(large, result);
}

// Test setting DBL_MAX
TEST_F(XMLAttributeSetAttributeDoubleTest_224, SetDBLMax_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    double maxVal = std::numeric_limits<double>::max();
    elem->SetAttribute("val", maxVal);
    
    double result = 0.0;
    XMLError err = elem->QueryDoubleAttribute("val", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(maxVal, result);
}

// Test setting DBL_MIN (smallest positive normalized)
TEST_F(XMLAttributeSetAttributeDoubleTest_224, SetDBLMin_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    double minVal = std::numeric_limits<double>::min();
    elem->SetAttribute("val", minVal);
    
    double result = 0.0;
    XMLError err = elem->QueryDoubleAttribute("val", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(minVal, result);
}

// Test setting a double with many decimal places
TEST_F(XMLAttributeSetAttributeDoubleTest_224, SetPreciseDouble_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    double precise = 1.23456789012345;
    elem->SetAttribute("val", precise);
    
    double result = 0.0;
    XMLError err = elem->QueryDoubleAttribute("val", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(precise, result);
}

// Test setting a whole number as double
TEST_F(XMLAttributeSetAttributeDoubleTest_224, SetWholeNumberDouble_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    elem->SetAttribute("val", 42.0);
    
    double result = 0.0;
    XMLError err = elem->QueryDoubleAttribute("val", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(42.0, result);
}

// Test overwriting an existing double attribute with a new double
TEST_F(XMLAttributeSetAttributeDoubleTest_224, OverwriteDouble_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    elem->SetAttribute("val", 1.0);
    
    double result = 0.0;
    elem->QueryDoubleAttribute("val", &result);
    EXPECT_DOUBLE_EQ(1.0, result);
    
    elem->SetAttribute("val", 99.99);
    elem->QueryDoubleAttribute("val", &result);
    EXPECT_DOUBLE_EQ(99.99, result);
}

// Test that the Value() string is updated after SetAttribute(double)
TEST_F(XMLAttributeSetAttributeDoubleTest_224, ValueStringUpdated_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "initial");
    elem->SetAttribute("val", 5.5);
    
    const char* valStr = elem->Attribute("val");
    ASSERT_NE(nullptr, valStr);
    
    // The value should be parseable as a double equal to 5.5
    double parsed = 0.0;
    bool ok = XMLUtil::ToDouble(valStr, &parsed);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(5.5, parsed);
}

// Test DoubleValue() convenience method after setting double
TEST_F(XMLAttributeSetAttributeDoubleTest_224, DoubleValueMethod_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    elem->SetAttribute("val", 123.456);
    
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(nullptr, attr);
    EXPECT_DOUBLE_EQ(123.456, attr->DoubleValue());
}

// Test QueryDoubleValue returns success after SetAttribute(double)
TEST_F(XMLAttributeSetAttributeDoubleTest_224, QueryDoubleValueSuccess_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    elem->SetAttribute("val", 7.77);
    
    const XMLAttribute* attr = elem->FindAttribute("val");
    ASSERT_NE(nullptr, attr);
    
    double result = 0.0;
    XMLError err = attr->QueryDoubleValue(&result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(7.77, result);
}

// Test setting a double and then querying as float
TEST_F(XMLAttributeSetAttributeDoubleTest_224, SetDoubleQueryFloat_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    elem->SetAttribute("val", 1.5);
    
    float result = 0.0f;
    XMLError err = elem->QueryFloatAttribute("val", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_FLOAT_EQ(1.5f, result);
}

// Test with negative large double
TEST_F(XMLAttributeSetAttributeDoubleTest_224, SetNegativeLargeDouble_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    double negLarge = -1e+300;
    elem->SetAttribute("val", negLarge);
    
    double result = 0.0;
    XMLError err = elem->QueryDoubleAttribute("val", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(negLarge, result);
}

// Test that the attribute name is preserved after setting a double value
TEST_F(XMLAttributeSetAttributeDoubleTest_224, NamePreservedAfterSet_224) {
    XMLElement* elem = CreateElementWithAttribute("myattr", "0");
    elem->SetAttribute("myattr", 2.5);
    
    const XMLAttribute* attr = elem->FindAttribute("myattr");
    ASSERT_NE(nullptr, attr);
    EXPECT_STREQ("myattr", attr->Name());
}

// Test setting double value 1.0 (exactly representable)
TEST_F(XMLAttributeSetAttributeDoubleTest_224, SetExactlyOne_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    elem->SetAttribute("val", 1.0);
    
    double result = 0.0;
    XMLError err = elem->QueryDoubleAttribute("val", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(1.0, result);
}

// Test round-trip: set double, print document, re-parse, read double
TEST_F(XMLAttributeSetAttributeDoubleTest_224, RoundTripThroughPrint_224) {
    XMLElement* elem = CreateElementWithAttribute("val", "0");
    elem->SetAttribute("val", 3.141592653589793);
    
    XMLPrinter printer;
    doc.Print(&printer);
    
    XMLDocument doc2;
    XMLError err = doc2.Parse(printer.CStr());
    EXPECT_EQ(XML_SUCCESS, err);
    
    XMLElement* elem2 = doc2.FirstChildElement("test");
    ASSERT_NE(nullptr, elem2);
    
    double result = 0.0;
    err = elem2->QueryDoubleAttribute("val", &result);
    EXPECT_EQ(XML_SUCCESS, err);
    EXPECT_DOUBLE_EQ(3.141592653589793, result);
}
