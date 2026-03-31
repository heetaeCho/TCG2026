#include <gtest/gtest.h>
#include <cstring>
#include <string>
#include <cmath>
#include <limits>
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLPrinterTest_302 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test PushAttribute with a simple positive double value
TEST_F(XMLPrinterTest_302, PushAttributeDoublePositive_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 3.14);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val="), std::string::npos);
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

// Test PushAttribute with zero double value
TEST_F(XMLPrinterTest_302, PushAttributeDoubleZero_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 0.0);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val="), std::string::npos);
    EXPECT_NE(result.find("0"), std::string::npos);
}

// Test PushAttribute with negative double value
TEST_F(XMLPrinterTest_302, PushAttributeDoubleNegative_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", -2.718);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val="), std::string::npos);
    EXPECT_NE(result.find("-2.718"), std::string::npos);
}

// Test PushAttribute with a very large double value
TEST_F(XMLPrinterTest_302, PushAttributeDoubleLargeValue_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 1.0e+100);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val="), std::string::npos);
    // The value should be present in some form
    EXPECT_GT(result.size(), 0u);
}

// Test PushAttribute with a very small double value
TEST_F(XMLPrinterTest_302, PushAttributeDoubleVerySmall_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 1.0e-100);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val="), std::string::npos);
}

// Test PushAttribute with double max value
TEST_F(XMLPrinterTest_302, PushAttributeDoubleMax_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", std::numeric_limits<double>::max());
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val="), std::string::npos);
}

// Test PushAttribute with double min (smallest positive) value
TEST_F(XMLPrinterTest_302, PushAttributeDoubleMin_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", std::numeric_limits<double>::min());
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val="), std::string::npos);
}

// Test PushAttribute with negative double max value
TEST_F(XMLPrinterTest_302, PushAttributeDoubleNegativeMax_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", -std::numeric_limits<double>::max());
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val="), std::string::npos);
}

// Test PushAttribute with integer-like double value
TEST_F(XMLPrinterTest_302, PushAttributeDoubleIntegerLike_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 42.0);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val="), std::string::npos);
    EXPECT_NE(result.find("42"), std::string::npos);
}

// Test PushAttribute with multiple double attributes
TEST_F(XMLPrinterTest_302, PushAttributeDoubleMultiple_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("x", 1.0);
    printer.PushAttribute("y", 2.0);
    printer.PushAttribute("z", 3.0);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("x="), std::string::npos);
    EXPECT_NE(result.find("y="), std::string::npos);
    EXPECT_NE(result.find("z="), std::string::npos);
}

// Test PushAttribute double in non-compact mode
TEST_F(XMLPrinterTest_302, PushAttributeDoubleNonCompact_302) {
    XMLPrinter printer(nullptr, false);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 99.99);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val="), std::string::npos);
    EXPECT_NE(result.find("99.99"), std::string::npos);
}

// Test PushAttribute with double 0.5
TEST_F(XMLPrinterTest_302, PushAttributeDoubleHalf_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 0.5);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val="), std::string::npos);
    EXPECT_NE(result.find("0.5"), std::string::npos);
}

// Test PushAttribute with double negative zero
TEST_F(XMLPrinterTest_302, PushAttributeDoubleNegativeZero_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", -0.0);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val="), std::string::npos);
}

// Test that attribute name is correctly included
TEST_F(XMLPrinterTest_302, PushAttributeDoubleNamePresence_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("testnode");
    printer.PushAttribute("myattribute", 1.23456);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("myattribute="), std::string::npos);
}

// Test PushAttribute double along with other attribute types
TEST_F(XMLPrinterTest_302, PushAttributeDoubleMixedTypes_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("intval", 42);
    printer.PushAttribute("doubleval", 3.14);
    printer.PushAttribute("strval", "hello");
    printer.PushAttribute("boolval", true);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("intval="), std::string::npos);
    EXPECT_NE(result.find("doubleval="), std::string::npos);
    EXPECT_NE(result.find("strval="), std::string::npos);
    EXPECT_NE(result.find("boolval="), std::string::npos);
}

// Test ClearBuffer after using PushAttribute with double
TEST_F(XMLPrinterTest_302, PushAttributeDoubleClearBuffer_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 7.77);
    printer.CloseElement();
    
    EXPECT_GT(printer.CStrSize(), 0u);
    
    printer.ClearBuffer();
    
    // After clearing, CStr should be minimal (empty or null-terminated)
    EXPECT_LE(printer.CStrSize(), 1u);
}

// Test PushAttribute double on nested elements
TEST_F(XMLPrinterTest_302, PushAttributeDoubleNestedElements_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("outer");
    printer.PushAttribute("outerval", 1.1);
    printer.OpenElement("inner");
    printer.PushAttribute("innerval", 2.2);
    printer.CloseElement();
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("outerval="), std::string::npos);
    EXPECT_NE(result.find("innerval="), std::string::npos);
}

// Test PushAttribute with double that has many decimal places
TEST_F(XMLPrinterTest_302, PushAttributeDoublePrecision_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 1.23456789012345);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    EXPECT_NE(result.find("val="), std::string::npos);
    // At least some digits of precision should be present
    EXPECT_NE(result.find("1.23456"), std::string::npos);
}

// Test that output is valid XML-like structure
TEST_F(XMLPrinterTest_302, PushAttributeDoubleValidXMLStructure_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("test");
    printer.PushAttribute("value", 5.5);
    printer.CloseElement();
    
    std::string result = printer.CStr();
    // Should have opening and closing angle brackets
    EXPECT_NE(result.find("<test"), std::string::npos);
    EXPECT_NE(result.find("/>"), std::string::npos);
}

// Test using XMLDocument to parse the output back (round-trip verification)
TEST_F(XMLPrinterTest_302, PushAttributeDoubleRoundTrip_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 3.14);
    printer.CloseElement();
    
    XMLDocument doc;
    XMLError err = doc.Parse(printer.CStr());
    EXPECT_EQ(err, XML_SUCCESS);
    
    const XMLElement* elem = doc.FirstChildElement("elem");
    ASSERT_NE(elem, nullptr);
    
    double val = 0.0;
    XMLError queryErr = elem->QueryDoubleAttribute("val", &val);
    EXPECT_EQ(queryErr, XML_SUCCESS);
    EXPECT_NEAR(val, 3.14, 1e-10);
}

// Test round-trip with negative value
TEST_F(XMLPrinterTest_302, PushAttributeDoubleRoundTripNegative_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", -100.001);
    printer.CloseElement();
    
    XMLDocument doc;
    XMLError err = doc.Parse(printer.CStr());
    EXPECT_EQ(err, XML_SUCCESS);
    
    const XMLElement* elem = doc.FirstChildElement("elem");
    ASSERT_NE(elem, nullptr);
    
    double val = 0.0;
    XMLError queryErr = elem->QueryDoubleAttribute("val", &val);
    EXPECT_EQ(queryErr, XML_SUCCESS);
    EXPECT_NEAR(val, -100.001, 1e-10);
}

// Test round-trip with zero
TEST_F(XMLPrinterTest_302, PushAttributeDoubleRoundTripZero_302) {
    XMLPrinter printer(nullptr, true);
    printer.OpenElement("elem");
    printer.PushAttribute("val", 0.0);
    printer.CloseElement();
    
    XMLDocument doc;
    XMLError err = doc.Parse(printer.CStr());
    EXPECT_EQ(err, XML_SUCCESS);
    
    const XMLElement* elem = doc.FirstChildElement("elem");
    ASSERT_NE(elem, nullptr);
    
    double val = 999.0;
    XMLError queryErr = elem->QueryDoubleAttribute("val", &val);
    EXPECT_EQ(queryErr, XML_SUCCESS);
    EXPECT_DOUBLE_EQ(val, 0.0);
}
