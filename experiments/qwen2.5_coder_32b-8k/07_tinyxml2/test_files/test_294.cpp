#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::_;

using ::testing::HasSubstr;



class MockXMLPrinter : public XMLPrinter {

public:

    MOCK_METHOD(void, Write, (const char* data), (override));

    MOCK_METHOD(void, PushDeclaration, (const char* value), (override));



    MockXMLPrinter(FILE* file, bool compact, int depth, EscapeAposCharsInAttributes aposInAttributes)

        : XMLPrinter(file, compact, depth, aposInAttributes) {}

};



class XMLPrinterTest_294 : public ::testing::Test {

protected:

    FILE* mockFile = nullptr;

    MockXMLPrinter printer;



    XMLPrinterTest_294() : printer(mockFile, false, 0, APOS_DONT_ESCAPE) {}



    ~XMLPrinterTest_294() override {}

};



TEST_F(XMLPrinterTest_294, PushHeader_NoBOM_NoDeclaration_294) {

    EXPECT_CALL(printer, Write(_)).Times(0);

    EXPECT_CALL(printer, PushDeclaration(_)).Times(0);



    printer.PushHeader(false, false);

}



TEST_F(XMLPrinterTest_294, PushHeader_BOM_NoDeclaration_294) {

    const unsigned char bom[] = { TIXML_UTF_LEAD_0, TIXML_UTF_LEAD_1, TIXML_UTF_LEAD_2, 0 };

    EXPECT_CALL(printer, Write(reinterpret_cast<const char*>(bom))).Times(1);

    EXPECT_CALL(printer, PushDeclaration(_)).Times(0);



    printer.PushHeader(true, false);

}



TEST_F(XMLPrinterTest_294, PushHeader_NoBOM_Declaration_294) {

    EXPECT_CALL(printer, Write(_)).Times(0);

    EXPECT_CALL(printer, PushDeclaration("xml version=\"1.0\"")).Times(1);



    printer.PushHeader(false, true);

}



TEST_F(XMLPrinterTest_294, PushHeader_BOM_Declaration_294) {

    const unsigned char bom[] = { TIXML_UTF_LEAD_0, TIXML_UTF_LEAD_1, TIXML_UTF_LEAD_2, 0 };

    EXPECT_CALL(printer, Write(reinterpret_cast<const char*>(bom))).Times(1);

    EXPECT_CALL(printer, PushDeclaration("xml version=\"1.0\"")).Times(1);



    printer.PushHeader(true, true);

}
