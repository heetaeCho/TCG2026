#include "tinyxml2.h"
#include "gtest/gtest.h"
#include <cstdio>
#include <memory>

using namespace tinyxml2;

class XMLPrinterTest_302 : public ::testing::Test {
protected:
    void SetUp() override {
        // Open a memory stream to avoid file I/O
        fp = tmpfile();
        ASSERT_NE(fp, nullptr);
        printer = std::make_unique<XMLPrinter>(fp, false, 0, XMLPrinter::EscapeAposCharsInAttributes::NO);
    }

    void TearDown() override {
        if (fp) {
            fclose(fp);
            fp = nullptr;
        }
    }

    FILE* fp;
    std::unique_ptr<XMLPrinter> printer;
};

// Normal operation: Push a typical double value
TEST_F(XMLPrinterTest_302, PushNormalDouble_302) {
    printer->OpenElement("Test", false);
    printer->PushAttribute("value", 3.14159);
    printer->CloseElement(false);
    fflush(fp);

    fseek(fp, 0, SEEK_SET);
    char buffer[512] = {0};
    fread(buffer, 1, sizeof(buffer) - 1, fp);

    std::string output(buffer);
    EXPECT_NE(output.find("value=\"3.14159\""), std::string::npos);
}

// Boundary case: Push zero
TEST_F(XMLPrinterTest_302, PushZeroDouble_302) {
    printer->OpenElement("Test", false);
    printer->PushAttribute("zero", 0.0);
    printer->CloseElement(false);
    fflush(fp);

    fseek(fp, 0, SEEK_SET);
    char buffer[512] = {0};
    fread(buffer, 1, sizeof(buffer) - 1, fp);

    std::string output(buffer);
    EXPECT_NE(output.find("zero=\"0\""), std::string::npos);
}

// Boundary case: Push negative double
TEST_F(XMLPrinterTest_302, PushNegativeDouble_302) {
    printer->OpenElement("Test", false);
    printer->PushAttribute("neg", -123.456);
    printer->CloseElement(false);
    fflush(fp);

    fseek(fp, 0, SEEK_SET);
    char buffer[512] = {0};
    fread(buffer, 1, sizeof(buffer) - 1, fp);

    std::string output(buffer);
    EXPECT_NE(output.find("neg=\"-123.456\""), std::string::npos);
}

// Boundary case: Push very large double
TEST_F(XMLPrinterTest_302, PushLargeDouble_302) {
    printer->OpenElement("Test", false);
    double largeValue = 1.79769e+308; // Near DBL_MAX
    printer->PushAttribute("large", largeValue);
    printer->CloseElement(false);
    fflush(fp);

    fseek(fp, 0, SEEK_SET);
    char buffer[1024] = {0};
    fread(buffer, 1, sizeof(buffer) - 1, fp);

    std::string output(buffer);
    EXPECT_NE(output.find("large=\"1.79769e+308\""), std::string::npos);
}

// Boundary case: Push very small double
TEST_F(XMLPrinterTest_302, PushSmallDouble_302) {
    printer->OpenElement("Test", false);
    double smallValue = 1e-308;
    printer->PushAttribute("small", smallValue);
    printer->CloseElement(false);
    fflush(fp);

    fseek(fp, 0, SEEK_SET);
    char buffer[1024] = {0};
    fread(buffer, 1, sizeof(buffer) - 1, fp);

    std::string output(buffer);
    EXPECT_NE(output.find("small=\"1e-308\""), std::string::npos);
}

// Exceptional: Push NaN
TEST_F(XMLPrinterTest_302, PushNaNDouble_302) {
    printer->OpenElement("Test", false);
    double nanValue = std::numeric_limits<double>::quiet_NaN();
    printer->PushAttribute("nan", nanValue);
    printer->CloseElement(false);
    fflush(fp);

    fseek(fp, 0, SEEK_SET);
    char buffer[512] = {0};
    fread(buffer, 1, sizeof(buffer) - 1, fp);

    std::string output(buffer);
    // Implementation-defined output for NaN; just check that the attribute name is present
    EXPECT_NE(output.find("nan="), std::string::npos);
}

// Exceptional: Push infinity
TEST_F(XMLPrinterTest_302, PushInfinityDouble_302) {
    printer->OpenElement("Test", false);
    double infValue = std::numeric_limits<double>::infinity();
    printer->PushAttribute("inf", infValue);
    printer->CloseElement(false);
    fflush(fp);

    fseek(fp, 0, SEEK_SET);
    char buffer[512] = {0};
    fread(buffer, 1, sizeof(buffer) - 1, fp);

    std::string output(buffer);
    EXPECT_NE(output.find("inf="), std::string::npos);
}
