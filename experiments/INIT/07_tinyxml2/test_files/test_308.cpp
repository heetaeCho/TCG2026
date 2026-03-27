#include "gtest/gtest.h"
#include "tinyxml2.h"
#include <cstdio>
#include <memory>

using namespace tinyxml2;

// Helper fixture for XMLPrinter tests
class XMLPrinterTest_308 : public ::testing::Test {
protected:
    std::unique_ptr<XMLPrinter> printer;
    FILE* tempFile;

    void SetUp() override {
        // Use a temporary file to observe output
        tempFile = tmpfile();
        ASSERT_NE(tempFile, nullptr);
        printer = std::make_unique<XMLPrinter>(tempFile, false, 0, XMLPrinter::EscapeAposCharsInAttributes::No);
    }

    void TearDown() override {
        if (tempFile) {
            fclose(tempFile);
            tempFile = nullptr;
        }
    }

    std::string GetOutput() {
        fflush(tempFile);
        fseek(tempFile, 0, SEEK_SET);
        std::string result;
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), tempFile)) {
            result += buffer;
        }
        return result;
    }
};

// Normal operation: Push positive integer
TEST_F(XMLPrinterTest_308, PushPositiveInt_308) {
    printer->PushText(12345);
    std::string output = GetOutput();
    EXPECT_NE(output.find("12345"), std::string::npos);
}

// Normal operation: Push zero
TEST_F(XMLPrinterTest_308, PushZero_308) {
    printer->PushText(0);
    std::string output = GetOutput();
    EXPECT_NE(output.find("0"), std::string::npos);
}

// Normal operation: Push negative integer
TEST_F(XMLPrinterTest_308, PushNegativeInt_308) {
    printer->PushText(-987);
    std::string output = GetOutput();
    EXPECT_NE(output.find("-987"), std::string::npos);
}

// Boundary condition: Push INT_MAX
TEST_F(XMLPrinterTest_308, PushIntMax_308) {
    printer->PushText(INT_MAX);
    std::string output = GetOutput();
    EXPECT_NE(output.find(std::to_string(INT_MAX)), std::string::npos);
}

// Boundary condition: Push INT_MIN
TEST_F(XMLPrinterTest_308, PushIntMin_308) {
    printer->PushText(INT_MIN);
    std::string output = GetOutput();
    EXPECT_NE(output.find(std::to_string(INT_MIN)), std::string::npos);
}

// Exceptional / error scenario: File is nullptr (printer should not crash)
TEST_F(XMLPrinterTest_308, PushTextWithNullFile_308) {
    XMLPrinter nullPrinter(nullptr, false, 0, XMLPrinter::EscapeAposCharsInAttributes::No);
    EXPECT_NO_THROW(nullPrinter.PushText(42));
}

// Multiple calls: consecutive integers
TEST_F(XMLPrinterTest_308, PushMultipleIntegers_308) {
    printer->PushText(1);
    printer->PushText(2);
    printer->PushText(3);
    std::string output = GetOutput();
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}
