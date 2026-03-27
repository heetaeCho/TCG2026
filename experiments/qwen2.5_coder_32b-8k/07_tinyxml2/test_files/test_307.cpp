#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLPrinterTest : public ::testing::Test {

protected:

    FILE* mockFile = fopen("dummy.txt", "w");

    XMLPrinter printer{mockFile, false, 0, EscapeAposCharsInAttributes::YES};

};



TEST_F(XMLPrinterTest_307, PushText_Uint64_NormalOperation_307) {

    uint64_t value = 123456789;

    EXPECT_NO_THROW(printer.PushText(value));

}



TEST_F(XMLPrinterTest_307, PushText_Uint64_BoundaryCondition_MaxValue_307) {

    uint64_t maxValue = UINT64_MAX;

    EXPECT_NO_THROW(printer.PushText(maxValue));

}



TEST_F(XMLPrinterTest_307, PushText_Uint64_BoundaryCondition_Zero_307) {

    uint64_t zeroValue = 0;

    EXPECT_NO_THROW(printer.PushText(zeroValue));

}
