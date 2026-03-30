#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest : public ::testing::Test {

protected:

    FILE* dummyFile = fopen("/dev/null", "w");

    XMLPrinter printer{dummyFile, false, 0, EscapeAposCharsInAttributes::eNoEscape};



    ~XMLPrinterTest() override {

        fclose(dummyFile);

    }

};



TEST_F(XMLPrinterTest_312, PushTextDoubleNormalOperation_312) {

    double value = 123.456;

    printer.PushText(value);



    const char* buffer = printer.CStr();

    EXPECT_NE(buffer, nullptr);

    EXPECT_STREQ(buffer, "123.456");

}



TEST_F(XMLPrinterTest_312, PushTextDoubleBoundaryConditionMax_312) {

    double value = 1e308;

    printer.PushText(value);



    const char* buffer = printer.CStr();

    EXPECT_NE(buffer, nullptr);

    // The exact string representation of max double can vary, but it should be something like "inf"

    EXPECT_STREQ(buffer, "1e+308");

}



TEST_F(XMLPrinterTest_312, PushTextDoubleBoundaryConditionMin_312) {

    double value = -1e308;

    printer.PushText(value);



    const char* buffer = printer.CStr();

    EXPECT_NE(buffer, nullptr);

    // The exact string representation of min double can vary, but it should be something like "-inf"

    EXPECT_STREQ(buffer, "-1e+308");

}



TEST_F(XMLPrinterTest_312, PushTextDoubleBoundaryConditionZero_312) {

    double value = 0.0;

    printer.PushText(value);



    const char* buffer = printer.CStr();

    EXPECT_NE(buffer, nullptr);

    EXPECT_STREQ(buffer, "0");

}



TEST_F(XMLPrinterTest_312, PushTextDoubleExceptionalCaseNaN_312) {

    double value = std::nan("");

    printer.PushText(value);



    const char* buffer = printer.CStr();

    EXPECT_NE(buffer, nullptr);

    // The exact string representation of NaN can vary, but it should be something like "nan"

    EXPECT_STREQ(buffer, "nan");

}



TEST_F(XMLPrinterTest_312, PushTextDoubleExceptionalCaseInf_312) {

    double value = std::numeric_limits<double>::infinity();

    printer.PushText(value);



    const char* buffer = printer.CStr();

    EXPECT_NE(buffer, nullptr);

    // The exact string representation of infinity can vary, but it should be something like "inf"

    EXPECT_STREQ(buffer, "inf");

}



TEST_F(XMLPrinterTest_312, PushTextDoubleExceptionalCaseNegativeInf_312) {

    double value = -std::numeric_limits<double>::infinity();

    printer.PushText(value);



    const char* buffer = printer.CStr();

    EXPECT_NE(buffer, nullptr);

    // The exact string representation of negative infinity can vary, but it should be something like "-inf"

    EXPECT_STREQ(buffer, "-inf");

}
