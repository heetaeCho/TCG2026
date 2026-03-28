#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <limits>
#include <cstdio>

using namespace tinyxml2;

class XMLPrinterTest_306 : public ::testing::Test {
protected:
    // Use a memory file to capture output
    FILE* tempFile = nullptr;

    void SetUp() override {
        tempFile = tmpfile(); // create a temporary file
        ASSERT_NE(tempFile, nullptr);
    }

    void TearDown() override {
        if (tempFile) {
            fclose(tempFile);
            tempFile = nullptr;
        }
    }

    // Helper to read the content of the FILE* into a string
    std::string ReadFileContent() {
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

// Test normal positive value
TEST_F(XMLPrinterTest_306, PushText_NormalValue_306) {
    XMLPrinter printer(tempFile, false, 0, XMLPrinter::EscapeAposCharsInAttributes::YES);
    int64_t value = 1234567890;
    printer.PushText(value);

    std::string output = ReadFileContent();
    ASSERT_NE(output.find("1234567890"), std::string::npos);
}

// Test normal negative value
TEST_F(XMLPrinterTest_306, PushText_NegativeValue_306) {
    XMLPrinter printer(tempFile, false, 0, XMLPrinter::EscapeAposCharsInAttributes::YES);
    int64_t value = -9876543210;
    printer.PushText(value);

    std::string output = ReadFileContent();
    ASSERT_NE(output.find("-9876543210"), std::string::npos);
}

// Test boundary: maximum int64_t
TEST_F(XMLPrinterTest_306, PushText_MaxInt64_306) {
    XMLPrinter printer(tempFile, false, 0, XMLPrinter::EscapeAposCharsInAttributes::YES);
    int64_t value = std::numeric_limits<int64_t>::max();
    printer.PushText(value);

    std::string output = ReadFileContent();
    ASSERT_NE(output.find(std::to_string(value)), std::string::npos);
}

// Test boundary: minimum int64_t
TEST_F(XMLPrinterTest_306, PushText_MinInt64_306) {
    XMLPrinter printer(tempFile, false, 0, XMLPrinter::EscapeAposCharsInAttributes::YES);
    int64_t value = std::numeric_limits<int64_t>::min();
    printer.PushText(value);

    std::string output = ReadFileContent();
    ASSERT_NE(output.find(std::to_string(value)), std::string::npos);
}

// Test multiple PushText calls
TEST_F(XMLPrinterTest_306, PushText_MultipleCalls_306) {
    XMLPrinter printer(tempFile, false, 0, XMLPrinter::EscapeAposCharsInAttributes::YES);
    printer.PushText(42);
    printer.PushText(-42);
    printer.PushText(0);

    std::string output = ReadFileContent();
    ASSERT_NE(output.find("42"), std::string::npos);
    ASSERT_NE(output.find("-42"), std::string::npos);
    ASSERT_NE(output.find("0"), std::string::npos);
}
