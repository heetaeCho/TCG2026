#include "tinyxml2.h"
#include "gtest/gtest.h"

using namespace tinyxml2;

// Helper fixture for XMLPrinter tests
class XMLPrinterTest_311 : public ::testing::Test {
protected:
    // Using a FILE* that writes to memory via tmpfile to satisfy constructor
    FILE* file;
    XMLPrinter* printer;

    void SetUp() override {
        file = tmpfile(); // Temporary file
        ASSERT_NE(file, nullptr);
        printer = new XMLPrinter(file, false, 0, XMLPrinter::EscapeAposCharsInAttributes::kNo);
    }

    void TearDown() override {
        delete printer;
        fclose(file);
    }
};

// Normal operation: push a positive float
TEST_F(XMLPrinterTest_311, PushPositiveFloat_311) {
    printer->PushText(123.456f);
    const char* output = printer->CStr();
    ASSERT_NE(output, nullptr);
    // Ensure the output contains "123.456" as a substring
    std::string outStr(output);
    EXPECT_NE(outStr.find("123.456"), std::string::npos);
}

// Normal operation: push a negative float
TEST_F(XMLPrinterTest_311, PushNegativeFloat_311) {
    printer->PushText(-789.01f);
    const char* output = printer->CStr();
    ASSERT_NE(output, nullptr);
    std::string outStr(output);
    EXPECT_NE(outStr.find("-789.01"), std::string::npos);
}

// Boundary condition: push zero
TEST_F(XMLPrinterTest_311, PushZeroFloat_311) {
    printer->PushText(0.0f);
    const char* output = printer->CStr();
    ASSERT_NE(output, nullptr);
    std::string outStr(output);
    EXPECT_NE(outStr.find("0"), std::string::npos);
}

// Exceptional/edge: push NaN
TEST_F(XMLPrinterTest_311, PushNaNFloat_311) {
    float nanValue = std::numeric_limits<float>::quiet_NaN();
    printer->PushText(nanValue);
    const char* output = printer->CStr();
    ASSERT_NE(output, nullptr);
    // Expect the output contains "nan" (implementation dependent, lowercase is common)
    std::string outStr(output);
    EXPECT_TRUE(outStr.find("nan") != std::string::npos || outStr.find("NaN") != std::string::npos);
}

// Exceptional/edge: push infinity
TEST_F(XMLPrinterTest_311, PushInfinityFloat_311) {
    float infValue = std::numeric_limits<float>::infinity();
    printer->PushText(infValue);
    const char* output = printer->CStr();
    ASSERT_NE(output, nullptr);
    std::string outStr(output);
    EXPECT_TRUE(outStr.find("inf") != std::string::npos || outStr.find("INF") != std::string::npos);
}
