#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "html5-printer.cpp"  // Adjust the include path as necessary



using namespace testing;



class XMLPrinterHTML5Test_324 : public ::testing::Test {

protected:

    XMLPrinterHTML5 printer;

};



TEST_F(XMLPrinterHTML5Test_324, IsVoidElement_ReturnsTrueForKnownVoidElements_324) {

    EXPECT_TRUE(printer.isVoidElement("area"));

    EXPECT_TRUE(printer.isVoidElement("base"));

    EXPECT_TRUE(printer.isVoidElement("br"));

    EXPECT_TRUE(printer.isVoidElement("col"));

    EXPECT_TRUE(printer.isVoidElement("command"));

    EXPECT_TRUE(printer.isVoidElement("embed"));

    EXPECT_TRUE(printer.isVoidElement("hr"));

    EXPECT_TRUE(printer.isVoidElement("img"));

    EXPECT_TRUE(printer.isVoidElement("input"));

    EXPECT_TRUE(printer.isVoidElement("keygen"));

    EXPECT_TRUE(printer.isVoidElement("link"));

    EXPECT_TRUE(printer.isVoidElement("meta"));

    EXPECT_TRUE(printer.isVoidElement("param"));

    EXPECT_TRUE(printer.isVoidElement("source"));

    EXPECT_TRUE(printer.isVoidElement("track"));

    EXPECT_TRUE(printer.isVoidElement("wbr"));

}



TEST_F(XMLPrinterHTML5Test_324, IsVoidElement_ReturnsFalseForNonVoidElements_324) {

    EXPECT_FALSE(printer.isVoidElement("div"));

    EXPECT_FALSE(printer.isVoidElement("span"));

    EXPECT_FALSE(printer.isVoidElement("p"));

    EXPECT_FALSE(printer.isVoidElement("a"));

}



TEST_F(XMLPrinterHTML5Test_324, IsVoidElement_CaseInsensitiveComparison_324) {

    EXPECT_TRUE(printer.isVoidElement("AREA"));

    EXPECT_TRUE(printer.isVoidElement("Base"));

    EXPECT_TRUE(printer.isVoidElement("bR"));

    EXPECT_TRUE(printer.isVoidElement("COL"));

    EXPECT_TRUE(printer.isVoidElement("COMMAND"));

}



TEST_F(XMLPrinterHTML5Test_324, IsVoidElement_NullPointer_ReturnsFalse_324) {

    EXPECT_FALSE(printer.isVoidElement(nullptr));

}



TEST_F(XMLPrinterHTML5Test_324, IsVoidElement_EmptyString_ReturnsFalse_324) {

    EXPECT_FALSE(printer.isVoidElement(""));

}
