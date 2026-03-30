#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"

#include <sstream>



using namespace tinyxml2;

using ::testing::_;



class MockXMLPrinter : public XMLPrinter {

public:

    MOCK_METHOD(void, Write, (const char* data, size_t size), (override));

    MOCK_METHOD(void, Putc, (char ch), (override));



    MockXMLPrinter(FILE* file, bool compact, int depth, EscapeAposCharsInAttributes aposInAttributes)

        : XMLPrinter(file, compact, depth, aposInAttributes) {}

};



class XMLPrinterTest_315 : public ::testing::Test {

protected:

    std::ostringstream oss;

    MockXMLPrinter printer;



    XMLPrinterTest_315() : printer(oss.rdbuf(), false, 0, eApostropheHandlingNone) {}

};



TEST_F(XMLPrinterTest_315, PushUnknown_WritesCorrectValue_315) {

    EXPECT_CALL(printer, Write("!<", 2)).Times(1);

    EXPECT_CALL(printer, Write("testValue", strlen("testValue"))).Times(1);

    EXPECT_CALL(printer, Putc('>')).Times(1);



    printer.PushUnknown("testValue");

}



TEST_F(XMLPrinterTest_315, PushUnknown_WritesNothingForNullValue_315) {

    EXPECT_CALL(printer, Write(_, _)).Times(0);

    EXPECT_CALL(printer, Putc(_)).Times(0);



    printer.PushUnknown(nullptr);

}



TEST_F(XMLPrinterTest_315, PushUnknown_HandlesEmptyStringCorrectly_315) {

    EXPECT_CALL(printer, Write("!<", 2)).Times(1);

    EXPECT_CALL(printer, Write("", 0)).Times(1);

    EXPECT_CALL(printer, Putc('>')).Times(1);



    printer.PushUnknown("");

}



TEST_F(XMLPrinterTest_315, PushUnknown_VariousCharacters_315) {

    EXPECT_CALL(printer, Write("!<", 2)).Times(1);

    EXPECT_CALL(printer, Write("a!b@c#d$e%f^g&h*i(j)k-l+m,n.o/p:q;r<s>t?u=v_w`x|y~z", strlen("a!b@c#d$e%f^g&h*i(j)k-l+m,n.o/p:q;r<s>t?u=v_w`x|y~z"))).Times(1);

    EXPECT_CALL(printer, Putc('>')).Times(1);



    printer.PushUnknown("a!b@c#d$e%f^g&h*i(j)k-l+m,n.o/p:q;r<s>t?u=v_w`x|y~z");

}
