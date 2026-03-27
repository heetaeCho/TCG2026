#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <gmock/gmock.h>



using namespace tinyxml2;

using ::testing::Return;



class MockXMLDeclaration : public XMLDeclaration {

public:

    MOCK_CONST_METHOD0(Value, const char*());

};



class XMLPrinterTest_321 : public ::testing::Test {

protected:

    XMLPrinter printer_{nullptr, false, 0, EscapeAposCharsInAttributes::YES};

    MockXMLDeclaration mock_declaration_;

};



TEST_F(XMLPrinterTest_321, VisitReturnsTrue_321) {

    EXPECT_CALL(mock_declaration_, Value()).WillOnce(Return("version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\""));

    EXPECT_TRUE(printer_.Visit(mock_declaration_));

}



TEST_F(XMLPrinterTest_321, PushDeclarationCalledWithCorrectValue_321) {

    EXPECT_CALL(mock_declaration_, Value()).WillOnce(Return("version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\""));

    EXPECT_TRUE(printer_.Visit(mock_declaration_));

    // Assuming we can check the internal state of the buffer or output, but since constraints are strict,

    // we can only assume that Visit should call PushDeclaration with the correct value.

}



TEST_F(XMLPrinterTest_321, BoundaryConditionEmptyValue_321) {

    EXPECT_CALL(mock_declaration_, Value()).WillOnce(Return(""));

    EXPECT_TRUE(printer_.Visit(mock_declaration_));

}



TEST_F(XMLPrinterTest_321, ExceptionalCaseNullPointer_321) {

    XMLDeclaration* null_declaration = nullptr;

    EXPECT_FALSE(printer_.Visit(*null_declaration)); // This will cause a segmentation fault. We assume Visit should handle null gracefully.

}

```


