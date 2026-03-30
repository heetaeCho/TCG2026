#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::_;



class XMLPrinterTest : public ::testing::Test {

protected:

    FILE* mockFile = fopen("dummy.txt", "w");

    XMLPrinter printer{mockFile, false, 0, ESCAPE_APOS_CHARS_IN_ATTRIBUTES};

};



TEST_F(XMLPrinterTest_300, PushAttributeUint64_NormalOperation_300) {

    printer.PushAttribute("test_attr", 123456789012345ULL);

}



TEST_F(XMLPrinterTest_300, PushAttributeUint64_BoundaryCondition_Zero_300) {

    printer.PushAttribute("test_attr", 0ULL);

}



TEST_F(XMLPrinterTest_300, PushAttributeUint64_BoundaryCondition_MaxValue_300) {

    printer.PushAttribute("test_attr", UINT64_MAX);

}
