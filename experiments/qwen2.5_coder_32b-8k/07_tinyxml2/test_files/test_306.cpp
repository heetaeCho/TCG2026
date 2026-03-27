#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest : public ::testing::Test {

protected:

    FILE* file;

    XMLPrinter* printer;



    virtual void SetUp() {

        file = fopen("test_output.xml", "w");

        printer = new XMLPrinter(file, false, 0, EscapeAposCharsInAttributes::YES);

    }



    virtual void TearDown() {

        delete printer;

        fclose(file);

        remove("test_output.xml");

    }

};



TEST_F(XMLPrinterTest_306, PushTextWithInt64Value_NormalOperation_306) {

    int64_t value = 123456789012345LL;

    printer->PushText(value);

    // Assuming CStr() provides the internal buffer content for verification

    EXPECT_STREQ(printer->CStr(), "123456789012345");

}



TEST_F(XMLPrinterTest_306, PushTextWithInt64Value_BoundaryConditionMin_306) {

    int64_t value = INT64_MIN;

    printer->PushText(value);

    EXPECT_STREQ(printer->CStr(), "-9223372036854775808");

}



TEST_F(XMLPrinterTest_306, PushTextWithInt64Value_BoundaryConditionMax_306) {

    int64_t value = INT64_MAX;

    printer->PushText(value);

    EXPECT_STREQ(printer->CStr(), "9223372036854775807");

}



TEST_F(XMLPrinterTest_306, PushTextWithInt64Value_MultipleCalls_306) {

    printer->PushText(123LL);

    printer->PushText(456LL);

    EXPECT_STREQ(printer->CStr(), "123456");

}
