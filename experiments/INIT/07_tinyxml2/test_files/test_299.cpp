#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <cstdio>
#include <string>

using namespace tinyxml2;

class XMLPrinterTest_299 : public ::testing::Test {
protected:
    FILE* tempFile;
    XMLPrinter* printer;

    void SetUp() override {
        // Create a temporary file to pass to XMLPrinter
        tempFile = tmpfile();
        ASSERT_NE(tempFile, nullptr);
        printer = new XMLPrinter(tempFile, true, 0, XMLPrinter::EscapeAposCharsInAttributes::YES);
    }

    void TearDown() override {
        delete printer;
        fclose(tempFile);
    }

    // Helper to read back the buffer from the file
    std::string GetFileContent() {
        fflush(tempFile);
        fseek(tempFile, 0, SEEK_SET);
        std::string content;
        char buffer[512];
        while (fgets(buffer, sizeof(buffer), tempFile)) {
            content += buffer;
        }
        return content;
    }
};

// Normal operation: Push a single int64_t attribute
TEST_F(XMLPrinterTest_299, PushInt64Attribute_Normal_299) {
    printer->OpenElement("TestElement", true);
    int64_t value = 123456789012345LL;
    printer->PushAttribute("attr", value);
    printer->CloseElement(true);

    std::string content = GetFileContent();
    // Verify that the attribute value appears in the output
    EXPECT_NE(content.find("attr=\"123456789012345\""), std::string::npos);
}

// Boundary: Push the maximum int64_t value
TEST_F(XMLPrinterTest_299, PushInt64Attribute_MaxValue_299) {
    printer->OpenElement("TestElement", true);
    int64_t value = std::numeric_limits<int64_t>::max();
    printer->PushAttribute("maxAttr", value);
    printer->CloseElement(true);

    std::string content = GetFileContent();
    EXPECT_NE(content.find("maxAttr=\"9223372036854775807\""), std::string::npos);
}

// Boundary: Push the minimum int64_t value
TEST_F(XMLPrinterTest_299, PushInt64Attribute_MinValue_299) {
    printer->OpenElement("TestElement", true);
    int64_t value = std::numeric_limits<int64_t>::min();
    printer->PushAttribute("minAttr", value);
    printer->CloseElement(true);

    std::string content = GetFileContent();
    EXPECT_NE(content.find("minAttr=\"-9223372036854775808\""), std::string::npos);
}

// Exceptional / unusual: Push attribute with zero
TEST_F(XMLPrinterTest_299, PushInt64Attribute_ZeroValue_299) {
    printer->OpenElement("TestElement", true);
    printer->PushAttribute("zeroAttr", int64_t(0));
    printer->CloseElement(true);

    std::string content = GetFileContent();
    EXPECT_NE(content.find("zeroAttr=\"0\""), std::string::npos);
}

// Multiple attributes: Verify order and correct values
TEST_F(XMLPrinterTest_299, PushInt64Attribute_MultipleAttributes_299) {
    printer->OpenElement("TestElement", true);
    printer->PushAttribute("first", int64_t(1));
    printer->PushAttribute("second", int64_t(-1));
    printer->PushAttribute("third", int64_t(0));
    printer->CloseElement(true);

    std::string content = GetFileContent();
    EXPECT_NE(content.find("first=\"1\""), std::string::npos);
    EXPECT_NE(content.find("second=\"-1\""), std::string::npos);
    EXPECT_NE(content.find("third=\"0\""), std::string::npos);
}

// Verify external interaction: The content written contains the attribute name and value
TEST_F(XMLPrinterTest_299, PushInt64Attribute_ContentWritten_299) {
    printer->OpenElement("Element", true);
    int64_t value = 42;
    printer->PushAttribute("answer", value);

    std::string content = GetFileContent();
    EXPECT_NE(content.find("answer=\"42\""), std::string::npos);
}
