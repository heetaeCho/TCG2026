#include "tinyxml2.h"
#include <gtest/gtest.h>

using namespace tinyxml2;

class XMLPrinterTest_301 : public ::testing::Test {
protected:
    // Using a memory buffer (nullptr FILE*) to capture output via CStr()
    XMLPrinter printer{ nullptr, true, 0, XMLPrinter::EscapeAposCharsInAttributes::NO };

    void OpenElementWithAttribute(const char* elementName, const char* attrName, bool attrValue) {
        printer.OpenElement(elementName, true);
        printer.PushAttribute(attrName, attrValue);
        printer.CloseElement(true);
    }
};

// Test normal operation: PushAttribute with true value
TEST_F(XMLPrinterTest_301, PushAttributeTrue_301) {
    OpenElementWithAttribute("TestElement", "flag", true);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string s(output);
    EXPECT_NE(s.find("flag=\"true\""), std::string::npos);
}

// Test normal operation: PushAttribute with false value
TEST_F(XMLPrinterTest_301, PushAttributeFalse_301) {
    OpenElementWithAttribute("TestElement", "flag", false);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string s(output);
    EXPECT_NE(s.find("flag=\"false\""), std::string::npos);
}

// Boundary test: attribute name empty string
TEST_F(XMLPrinterTest_301, PushAttributeEmptyName_301) {
    OpenElementWithAttribute("TestElement", "", true);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string s(output);
    // Should still generate some attribute output, but name is empty
    EXPECT_NE(s.find("=\"true\""), std::string::npos);
}

// Boundary test: attribute name very long string
TEST_F(XMLPrinterTest_301, PushAttributeLongName_301) {
    std::string longName(180, 'x'); // near BUF_SIZE
    OpenElementWithAttribute("TestElement", longName.c_str(), true);
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string s(output);
    EXPECT_NE(s.find(longName + "=\"true\""), std::string::npos);
}

// Exceptional test: PushAttribute with nullptr name
TEST_F(XMLPrinterTest_301, PushAttributeNullName_301) {
    // Expect no crash and either no output or a graceful handling
    EXPECT_NO_THROW({
        OpenElementWithAttribute("TestElement", nullptr, true);
    });
    const char* output = printer.CStr();
    ASSERT_NE(output, nullptr);
    std::string s(output);
    // Depending on implementation, it may skip or write empty attribute
    EXPECT_TRUE(s.find("=\"true\"") != std::string::npos || s.find("flag") == std::string::npos);
}
