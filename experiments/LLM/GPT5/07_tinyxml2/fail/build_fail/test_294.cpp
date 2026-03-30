#include <gtest/gtest.h>
#include "tinyxml2.h"

using namespace tinyxml2;

// Test fixture for XMLPrinter
class XMLPrinterTest_294 : public ::testing::Test {
protected:
    void SetUp() override {
        printer = new XMLPrinter(nullptr, false, 0, XMLPrinter::EscapeAposCharsInAttributes::No);
    }

    void TearDown() override {
        delete printer;
    }

    XMLPrinter* printer;
};

// Test: PushHeader with both BOM and declaration
TEST_F(XMLPrinterTest_294, PushHeaderWritesBOMAndDeclaration_294) {
    printer->PushHeader(true, true);
    const char* output = printer->CStr();
    ASSERT_NE(output, nullptr);

    // BOM bytes check (UTF-8 BOM)
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 239U);
    EXPECT_EQ(static_cast<unsigned char>(output[1]), 187U);
    EXPECT_EQ(static_cast<unsigned char>(output[2]), 191U);

    // Declaration check
    EXPECT_NE(std::strstr(output, "xml version=\"1.0\""), nullptr);
}

// Test: PushHeader with BOM only
TEST_F(XMLPrinterTest_294, PushHeaderWritesOnlyBOM_294) {
    printer->PushHeader(true, false);
    const char* output = printer->CStr();
    ASSERT_NE(output, nullptr);

    // BOM bytes check
    EXPECT_EQ(static_cast<unsigned char>(output[0]), 239U);
    EXPECT_EQ(static_cast<unsigned char>(output[1]), 187U);
    EXPECT_EQ(static_cast<unsigned char>(output[2]), 191U);

    // Declaration should not be present
    EXPECT_EQ(std::strstr(output, "xml version=\"1.0\""), nullptr);
}

// Test: PushHeader with declaration only
TEST_F(XMLPrinterTest_294, PushHeaderWritesOnlyDeclaration_294) {
    printer->PushHeader(false, true);
    const char* output = printer->CStr();
    ASSERT_NE(output, nullptr);

    // BOM should not be present
    EXPECT_NE(static_cast<unsigned char>(output[0]), 239U);

    // Declaration check
    EXPECT_NE(std::strstr(output, "xml version=\"1.0\""), nullptr);
}

// Test: PushHeader with neither BOM nor declaration
TEST_F(XMLPrinterTest_294, PushHeaderWritesNothing_294) {
    printer->PushHeader(false, false);
    const char* output = printer->CStr();
    ASSERT_NE(output, nullptr);

    // Output should be empty
    EXPECT_EQ(std::strlen(output), 0u);
}
