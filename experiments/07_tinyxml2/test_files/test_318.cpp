#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::_;

using ::testing::Return;



class MockXMLElement : public XMLElement {

public:

    MOCK_METHOD(bool, Accept, (XMLVisitor* visitor), (const override));

    MOCK_METHOD(const char*, Name, (), (const));

    MOCK_METHOD(ElementClosingType, ClosingType, (), (const));

};



TEST_F(XMLPrinterTest_318, VisitExit_NormalOperation_318) {

    MockXMLElement mockElement;

    XMLPrinter printer(nullptr, false, 0, EscapeAposCharsInAttributes::YES);



    EXPECT_CALL(mockElement, ClosingType()).WillOnce(Return(ElementClosingType::CLOSED));



    bool result = printer.VisitExit(mockElement);



    EXPECT_TRUE(result);

}



TEST_F(XMLPrinterTest_318, VisitExit_CompactModeOpenElement_318) {

    MockXMLElement mockElement;

    XMLPrinter printer(nullptr, true, 0, EscapeAposCharsInAttributes::YES);



    EXPECT_CALL(mockElement, ClosingType()).WillOnce(Return(ElementClosingType::OPEN));



    bool result = printer.VisitExit(mockElement);



    EXPECT_TRUE(result);

}



TEST_F(XMLPrinterTest_318, VisitExit_CompactModeClosedElement_318) {

    MockXMLElement mockElement;

    XMLPrinter printer(nullptr, true, 0, EscapeAposCharsInAttributes::YES);



    EXPECT_CALL(mockElement, ClosingType()).WillOnce(Return(ElementClosingType::CLOSED));



    bool result = printer.VisitExit(mockElement);



    EXPECT_TRUE(result);

}

```


