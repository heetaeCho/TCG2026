#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::StrictMock;



// Mock class for XMLPrinter to verify interactions

class MockXMLPrinter : public XMLPrinter {

public:

    MOCK_METHOD(void, PushHeader, (bool writeBOM, bool writeDeclaration), (override));

    MOCK_METHOD(void, OpenElement, (const char * name, bool compactMode), (override));

    MOCK_METHOD(void, CloseElement, (bool compactMode), (override));

    MOCK_METHOD(bool, VisitEnter, (const XMLDocument & doc), (override));

    MOCK_METHOD(bool, VisitExit, (const XMLDocument& /*doc*/), (override));

};



class XMLDocumentTest_284 : public ::testing::Test {

protected:

    XMLDocument xmlDoc{true, Whitespace::COLLAPSE_WHITESPACE};

    StrictMock<MockXMLPrinter> mockPrinter;

};



TEST_F(XMLDocumentTest_284, PrintWithStreamerProvided_284) {

    EXPECT_CALL(mockPrinter, VisitEnter(::testing::_))

        .WillOnce(::testing::Return(true));

    EXPECT_CALL(mockPrinter, VisitExit(::testing::_))

        .WillOnce(::testing::Return(true));



    xmlDoc.Print(&mockPrinter);

}



TEST_F(XMLDocumentTest_284, PrintWithoutStreamerProvided_284) {

    // This test case assumes that the implementation uses stdout

    // when no streamer is provided. Since we cannot capture stdout directly,

    // this test only checks if the function does not crash.

    xmlDoc.Print(nullptr);

}



TEST_F(XMLDocumentTest_284, PrintWithNullStreamerDoesNotCrash_284) {

    xmlDoc.Print(nullptr);

}
