#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest : public ::testing::Test {

protected:

    FILE* mockFile;

    XMLDocument doc;

    XMLComment comment;



    void SetUp() override {

        mockFile = fopen("mock_output.txt", "w");

        ASSERT_NE(mockFile, nullptr);

        comment.SetValue("This is a test comment", true);

    }



    void TearDown() override {

        fclose(mockFile);

        remove("mock_output.txt");

    }

};



TEST_F(XMLPrinterTest_NormalOperation_320, VisitComment_ReturnsTrue_320) {

    XMLPrinter printer(mockFile, false, 0, EscapeAposCharsInAttributes::YES);

    EXPECT_TRUE(printer.Visit(comment));

}



TEST_F(XMLPrinterTest_BoundaryConditions_320, VisitEmptyComment_ReturnsTrue_320) {

    comment.SetValue("", true);

    XMLPrinter printer(mockFile, false, 0, EscapeAposCharsInAttributes::YES);

    EXPECT_TRUE(printer.Visit(comment));

}



TEST_F(XMLPrinterTest_ExceptionalCases_320, VisitNullValue_Comment_ReturnsTrue_320) {

    comment.SetValue(nullptr, true);

    XMLPrinter printer(mockFile, false, 0, EscapeAposCharsInAttributes::YES);

    EXPECT_TRUE(printer.Visit(comment));

}



TEST_F(XMLPrinterTest_VerifyExternalInteractions_320, VisitComment_WritesToMockFile_320) {

    XMLPrinter printer(mockFile, false, 0, EscapeAposCharsInAttributes::YES);

    printer.Visit(comment);



    rewind(mockFile);

    char buffer[1024];

    size_t bytesRead = fread(buffer, 1, sizeof(buffer), mockFile);

    EXPECT_GT(bytesRead, 0);

    std::string output(buffer, bytesRead);

    EXPECT_NE(output.find("<!--This is a test comment-->"), std::string::npos);

}
