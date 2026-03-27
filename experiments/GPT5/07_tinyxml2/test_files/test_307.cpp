#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <cstdio>
#include <cstdint>

using namespace tinyxml2;

class XMLPrinterTest_307 : public ::testing::Test {
protected:
    XMLPrinter* printer;

    void SetUp() override {
        // Construct XMLPrinter writing to memory (no file)
        printer = new XMLPrinter(nullptr, false, 0, XMLPrinter::EscapeAposCharsInAttributes::NO);
    }

    void TearDown() override {
        delete printer;
    }
};

// Normal operation: push a typical uint64_t value
TEST_F(XMLPrinterTest_307, PushTextTypicalValue_307) {
    uint64_t value = 1234567890ULL;
    printer->PushText(value);

    const char* result = printer->CStr();
    ASSERT_NE(result, nullptr);
    std::string strResult(result);

    // The printed string should contain the numeric value
    EXPECT_NE(strResult.find("1234567890"), std::string::npos);
}

// Boundary: push 0
TEST_F(XMLPrinterTest_307, PushTextZero_307) {
    uint64_t value = 0ULL;
    printer->PushText(value);

    const char* result = printer->CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "0");
}

// Boundary: push maximum uint64_t value
TEST_F(XMLPrinterTest_307, PushTextMaxValue_307) {
    uint64_t value = UINT64_MAX;
    printer->PushText(value);

    const char* result = printer->CStr();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "18446744073709551615");
}

// Exceptional / edge: repeated pushes
TEST_F(XMLPrinterTest_307, PushTextMultipleValues_307) {
    printer->PushText(0ULL);
    printer->PushText(1ULL);
    printer->PushText(42ULL);

    const char* result = printer->CStr();
    ASSERT_NE(result, nullptr);
    std::string strResult(result);

    // All values should appear in the output, in order
    EXPECT_NE(strResult.find("0"), std::string::npos);
    EXPECT_NE(strResult.find("1"), std::string::npos);
    EXPECT_NE(strResult.find("42"), std::string::npos);
}

// Verify interaction with OpenElement and PushText
TEST_F(XMLPrinterTest_307, PushTextInsideElement_307) {
    printer->OpenElement("TestElement", false);
    printer->PushText(555ULL);
    printer->CloseElement(false);

    const char* result = printer->CStr();
    ASSERT_NE(result, nullptr);
    std::string strResult(result);

    // Should contain opening tag, value, and closing tag
    EXPECT_NE(strResult.find("<TestElement>"), std::string::npos);
    EXPECT_NE(strResult.find("555"), std::string::npos);
    EXPECT_NE(strResult.find("</TestElement>"), std::string::npos);
}
