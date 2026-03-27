#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest : public ::testing::Test {

protected:

    XMLPrinter* printer;

    FILE* file;



    void SetUp() override {

        file = fopen("test_output.xml", "w");

        ASSERT_NE(file, nullptr);

        printer = new XMLPrinter(file, false, 0, EscapeAposCharsInAttributes::eNo);

    }



    void TearDown() override {

        delete printer;

        fclose(file);

        remove("test_output.xml");

    }

};



TEST_F(XMLPrinterTest_301, PushAttributeBoolTrue_301) {

    printer->PushAttribute("active", true);

    // We can't directly verify the internal buffer, but we can check if the output file contains the expected string.

    FILE* resultFile = fopen("test_output.xml", "r");

    char buffer[256];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, resultFile);

    fclose(resultFile);

    buffer[bytesRead] = '\0';

    EXPECT_NE(std::string(buffer).find(R"("active"="true")"), std::string::npos);

}



TEST_F(XMLPrinterTest_301, PushAttributeBoolFalse_301) {

    printer->PushAttribute("active", false);

    // We can't directly verify the internal buffer, but we can check if the output file contains the expected string.

    FILE* resultFile = fopen("test_output.xml", "r");

    char buffer[256];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, resultFile);

    fclose(resultFile);

    buffer[bytesRead] = '\0';

    EXPECT_NE(std::string(buffer).find(R"("active"="false")"), std::string::npos);

}



TEST_F(XMLPrinterTest_301, PushAttributeNullName_301) {

    // This test case is to check if the function handles null name gracefully.

    printer->PushAttribute(nullptr, true);

    FILE* resultFile = fopen("test_output.xml", "r");

    char buffer[256];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, resultFile);

    fclose(resultFile);

    buffer[bytesRead] = '\0';

    EXPECT_EQ(std::string(buffer).find("\"\"=\"true\""), std::string::npos); // Empty string should not appear as attribute name.

}



TEST_F(XMLPrinterTest_301, PushAttributeEmptyName_301) {

    // This test case is to check if the function handles empty name gracefully.

    printer->PushAttribute("", true);

    FILE* resultFile = fopen("test_output.xml", "r");

    char buffer[256];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, resultFile);

    fclose(resultFile);

    buffer[bytesRead] = '\0';

    EXPECT_EQ(std::string(buffer).find(R"(""="true")"), std::string::npos); // Empty string should not appear as attribute name.

}
