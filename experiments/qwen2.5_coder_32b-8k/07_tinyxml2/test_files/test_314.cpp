#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <gmock/gmock.h>



using namespace tinyxml2;

using ::testing::_;

using ::testing::Mock;



class MockXMLPrinter : public XMLPrinter {

public:

    MOCK_METHOD(void, Write, (const char* data), (override));

};



TEST_F(MockXMLPrinterTest_314, PushDeclaration_NormalOperation_314) {

    MockXMLPrinter mockPrinter(stdout, true, 0, EscapeAposCharsInAttributes::YES);

    EXPECT_CALL(mockPrinter, Write("<?test?>"));

    mockPrinter.PushDeclaration("test");

}



TEST_F(MockXMLPrinterTest_314, PushDeclaration_EmptyString_314) {

    MockXMLPrinter mockPrinter(stdout, true, 0, EscapeAposCharsInAttributes::YES);

    EXPECT_CALL(mockPrinter, Write("<?>??>"));

    mockPrinter.PushDeclaration("");

}



TEST_F(MockXMLPrinterTest_314, PushDeclaration_NullPointer_314) {

    MockXMLPrinter mockPrinter(stdout, true, 0, EscapeAposCharsInAttributes::YES);

    EXPECT_CALL(mockPrinter, Write("<?"));

    EXPECT_CALL(mockPrinter, Write("?>"));

    mockPrinter.PushDeclaration(nullptr);

}



TEST_F(MockXMLPrinterTest_314, PushDeclaration_LongString_314) {

    MockXMLPrinter mockPrinter(stdout, true, 0, EscapeAposCharsInAttributes::YES);

    std::string longValue(1024, 'a');

    EXPECT_CALL(mockPrinter, Write((testing::StartsWith("<?") && testing::EndsWith("?>"))));

    mockPrinter.PushDeclaration(longValue.c_str());

}
