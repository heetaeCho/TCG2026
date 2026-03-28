#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <cstdio>
#include <memory>

using namespace tinyxml2;

// Test fixture for XMLPrinter
class XMLPrinterTest_297 : public ::testing::Test {
protected:
    // Use a memory-backed file for XMLPrinter to avoid actual file I/O
    std::unique_ptr<XMLPrinter> printer;

    void SetUp() override {
        // Pass nullptr for FILE* to let XMLPrinter write to internal buffer
        printer = std::make_unique<XMLPrinter>(nullptr, false, 0, XMLPrinter::EscapeAposCharsInAttributes::YES);
        // Start a root element to allow attributes to be pushed
        printer->OpenElement("root", false);
    }

    void TearDown() override {
        printer.reset();
    }
};

// Normal operation: Push a positive integer attribute
TEST_F(XMLPrinterTest_297, PushPositiveIntAttribute_297) {
    printer->PushAttribute("count", 42);
    printer->CloseElement(false);
    std::string output = printer->CStr();
    EXPECT_NE(output.find("count=\"42\""), std::string::npos);
}

// Normal operation: Push a negative integer attribute
TEST_F(XMLPrinterTest_297, PushNegativeIntAttribute_297) {
    printer->PushAttribute("offset", -7);
    printer->CloseElement(false);
    std::string output = printer->CStr();
    EXPECT_NE(output.find("offset=\"-7\""), std::string::npos);
}

// Boundary: Push zero as attribute
TEST_F(XMLPrinterTest_297, PushZeroIntAttribute_297) {
    printer->PushAttribute("zeroValue", 0);
    printer->CloseElement(false);
    std::string output = printer->CStr();
    EXPECT_NE(output.find("zeroValue=\"0\""), std::string::npos);
}

// Exceptional / large integer: Push INT_MAX
TEST_F(XMLPrinterTest_297, PushIntMaxAttribute_297) {
    printer->PushAttribute("maxInt", INT_MAX);
    printer->CloseElement(false);
    std::string output = printer->CStr();
    EXPECT_NE(output.find("maxInt=\"2147483647\""), std::string::npos);
}

// Exceptional / large negative integer: Push INT_MIN
TEST_F(XMLPrinterTest_297, PushIntMinAttribute_297) {
    printer->PushAttribute("minInt", INT_MIN);
    printer->CloseElement(false);
    std::string output = printer->CStr();
    EXPECT_NE(output.find("minInt=\"-2147483648\""), std::string::npos);
}
