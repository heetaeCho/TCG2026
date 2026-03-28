#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::Return;



class XMLTextMock : public XMLText {

public:

    MOCK_CONST_METHOD0(Value, const char*());

    MOCK_CONST_METHOD0(CData, bool());

};



TEST_F(XMLPrinterTest_319, VisitNormalOperation_319) {

    XMLTextMock text;

    XMLPrinter printer(nullptr, false, 0, EscapeAposCharsInAttributes::NO);



    EXPECT_CALL(text, Value()).WillOnce(Return("Sample Text"));

    EXPECT_CALL(text, CData()).WillOnce(Return(false));



    bool result = printer.Visit(text);

    EXPECT_TRUE(result);

}



TEST_F(XMLPrinterTest_319, VisitCDataTrue_319) {

    XMLTextMock text;

    XMLPrinter printer(nullptr, false, 0, EscapeAposCharsInAttributes::NO);



    EXPECT_CALL(text, Value()).WillOnce(Return("Sample CDATA Text"));

    EXPECT_CALL(text, CData()).WillOnce(Return(true));



    bool result = printer.Visit(text);

    EXPECT_TRUE(result);

}



TEST_F(XMLPrinterTest_319, VisitEmptyText_319) {

    XMLTextMock text;

    XMLPrinter printer(nullptr, false, 0, EscapeAposCharsInAttributes::NO);



    EXPECT_CALL(text, Value()).WillOnce(Return(""));

    EXPECT_CALL(text, CData()).WillOnce(Return(false));



    bool result = printer.Visit(text);

    EXPECT_TRUE(result);

}



TEST_F(XMLPrinterTest_319, VisitNullText_319) {

    XMLTextMock text;

    XMLPrinter printer(nullptr, false, 0, EscapeAposCharsInAttributes::NO);



    EXPECT_CALL(text, Value()).WillOnce(Return(static_cast<const char*>(nullptr)));

    EXPECT_CALL(text, CData()).WillOnce(Return(false));



    bool result = printer.Visit(text);

    EXPECT_TRUE(result);

}



TEST_F(XMLPrinterTest_319, VisitCDataEmptyText_319) {

    XMLTextMock text;

    XMLPrinter printer(nullptr, false, 0, EscapeAposCharsInAttributes::NO);



    EXPECT_CALL(text, Value()).WillOnce(Return(""));

    EXPECT_CALL(text, CData()).WillOnce(Return(true));



    bool result = printer.Visit(text);

    EXPECT_TRUE(result);

}
