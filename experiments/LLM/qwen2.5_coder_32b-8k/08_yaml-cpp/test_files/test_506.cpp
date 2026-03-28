#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/parser.h"

#include "yaml-cpp/eventhandler.h"



using namespace YAML;

using ::testing::_;

using ::testing::MockFunction;



class MockEventHandler : public EventHandler {

public:

    MOCK_METHOD1(OnDocumentStart, void(const Mark& mark));

    MOCK_METHOD0(OnDocumentEnd, void());

};



class ParserTest_506 : public ::testing::Test {

protected:

    std::istringstream input;

    Parser parser;

    MockEventHandler mockEventHandler;



    void SetUp() override {

        input.str("");

        parser.Load(input);

    }

};



TEST_F(ParserTest_506, HandleNextDocument_NoScanner_ReturnsFalse_506) {

    // Arrange

    parser = Parser();



    // Act & Assert

    EXPECT_FALSE(parser.HandleNextDocument(mockEventHandler));

}



TEST_F(ParserTest_506, HandleNextDocument_EmptyInput_ReturnsFalse_506) {

    // Arrange

    input.str("");

    parser.Load(input);



    // Act & Assert

    EXPECT_FALSE(parser.HandleNextDocument(mockEventHandler));

}



TEST_F(ParserTest_506, HandleNextDocument_ValidYaml_CallsOnDocumentStartAndEnd_506) {

    // Arrange

    input.str("a: b");

    parser.Load(input);

    EXPECT_CALL(mockEventHandler, OnDocumentStart(_)).Times(1);

    EXPECT_CALL(mockEventHandler, OnDocumentEnd()).Times(1);



    // Act & Assert

    EXPECT_TRUE(parser.HandleNextDocument(mockEventHandler));

}



TEST_F(ParserTest_506, HandleNextDocument_MultipleDocuments_ReturnsTrueForAll_506) {

    // Arrange

    input.str("---\na: b\n---\nc: d");

    parser.Load(input);

    EXPECT_CALL(mockEventHandler, OnDocumentStart(_)).Times(2);

    EXPECT_CALL(mockEventHandler, OnDocumentEnd()).Times(2);



    // Act & Assert

    EXPECT_TRUE(parser.HandleNextDocument(mockEventHandler));

    EXPECT_TRUE(parser.HandleNextDocument(mockEventHandler));

}



TEST_F(ParserTest_506, HandleNextDocument_EndOfStream_ReturnsFalse_506) {

    // Arrange

    input.str("a: b");

    parser.Load(input);

    parser.HandleNextDocument(mockEventHandler);



    // Act & Assert

    EXPECT_FALSE(parser.HandleNextDocument(mockEventHandler));

}
