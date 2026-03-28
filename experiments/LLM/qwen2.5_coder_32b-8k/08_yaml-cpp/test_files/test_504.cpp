#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/parser.h"

#include <sstream>



using namespace YAML;

using ::testing::_;

using ::testing::NiceMock;



class MockScanner : public Scanner {

public:

    MOCK_CONST_METHOD0(empty, bool());

};



class MockEventHandler : public EventHandler {

public:

    MOCK_METHOD0(OnDocumentStart, void());

    MOCK_METHOD0(OnDocumentEnd, void());

    MOCK_METHOD1(OnNode, void(const Mark&));

    MOCK_METHOD2(OnScalar, void(const Mark&, const std::string&));

    MOCK_METHOD3(OnSequenceStart, void(const Mark&, const std::string&, bool));

    MOCK_METHOD1(OnSequenceEnd, void());

    MOCK_METHOD4(OnMapStart, void(const Mark&, const std::string&, bool));

    MOCK_METHOD1(OnMapEnd, void());

};



class ParserTest_504 : public ::testing::Test {

protected:

    NiceMock<MockScanner> mock_scanner;

    Parser parser;



    ParserTest_504() : parser(std::make_unique<MockScanner>(mock_scanner)) {}

};



TEST_F(ParserTest_504, OperatorBoolReturnsTrueWhenScannerNotEmpty_504) {

    EXPECT_CALL(mock_scanner, empty()).WillOnce(::testing::Return(false));

    EXPECT_TRUE(static_cast<bool>(parser));

}



TEST_F(ParserTest_504, OperatorBoolReturnsFalseWhenScannerEmpty_504) {

    EXPECT_CALL(mock_scanner, empty()).WillOnce(::testing::Return(true));

    EXPECT_FALSE(static_cast<bool>(parser));

}



TEST_F(ParserTest_504, HandleNextDocumentCallsEventHandlerMethodsOnNonEmptyScanner_504) {

    NiceMock<MockEventHandler> mock_event_handler;

    EXPECT_CALL(mock_scanner, empty()).WillOnce(::testing::Return(false)).WillRepeatedly(::testing::Return(true));

    EXPECT_CALL(mock_event_handler, OnDocumentStart());

    EXPECT_CALL(mock_event_handler, OnDocumentEnd());



    parser.HandleNextDocument(mock_event_handler);

}



TEST_F(ParserTest_504, HandleNextDocumentDoesNotCallEventHandlerMethodsOnEmptyScanner_504) {

    NiceMock<MockEventHandler> mock_event_handler;

    EXPECT_CALL(mock_scanner, empty()).WillOnce(::testing::Return(true));



    EXPECT_CALL(mock_event_handler, OnDocumentStart()).Times(0);

    EXPECT_CALL(mock_event_handler, OnDocumentEnd()).Times(0);



    parser.HandleNextDocument(mock_event_handler);

}



TEST_F(ParserTest_504, LoadReplacesExistingScanner_504) {

    std::istringstream input("sample yaml");

    parser.Load(input);

    EXPECT_TRUE(static_cast<bool>(parser));

}
