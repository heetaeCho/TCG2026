#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <yaml-cpp/parser.h>

#include <yaml-cpp/eventhandler.h>

#include <sstream>



using namespace YAML;

using namespace testing;



class MockEventHandler : public EventHandler {

public:

    MOCK_METHOD(void, OnDocumentStart, (const Mark&), (override));

    MOCK_METHOD(void, OnDocumentEnd, (), (override));

    MOCK_METHOD(void, OnNull, (const Mark&, anchor_t), (override));

    MOCK_METHOD(void, OnAlias, (const Mark&, anchor_t), (override));

    MOCK_METHOD(void, OnScalar, (const Mark&, const std::string&, anchor_t, const std::string&), (override));

    MOCK_METHOD(void, OnSequenceStart, (const Mark&, const std::string&, anchor_t, EmitterStyle::value), (override));

    MOCK_METHOD(void, OnSequenceEnd, (), (override));

    MOCK_METHOD(void, OnMapStart, (const Mark&, const std::string&, anchor_t, EmitterStyle::value), (override));

    MOCK_METHOD(void, OnMapEnd, (), (override));

};



class ParserTest_673 : public Test {

protected:

    std::istringstream input;

    MockEventHandler mockHandler;



    void SetUp() override {

        // Set up default input stream with a simple YAML document

        input.str("a: 1");

    }

};



TEST_F(ParserTest_673, HandleNextDocument_ValidYaml_673) {

    Parser parser(input);

    EXPECT_CALL(mockHandler, OnDocumentStart(_)).Times(1);

    EXPECT_CALL(mockHandler, OnScalar(_, Eq("a"), _, _)).Times(1);

    EXPECT_CALL(mockHandler, OnScalar(_, Eq("1"), _, _)).Times(1);

    EXPECT_CALL(mockHandler, OnDocumentEnd()).Times(1);



    bool result = parser.HandleNextDocument(mockHandler);

    EXPECT_TRUE(result);

}



TEST_F(ParserTest_673, HandleNextDocument_EmptyYaml_673) {

    input.str("");

    Parser parser(input);

    EXPECT_CALL(mockHandler, OnDocumentStart(_)).Times(0);

    EXPECT_CALL(mockHandler, OnScalar(_, _, _, _)).Times(0);

    EXPECT_CALL(mockHandler, OnDocumentEnd()).Times(0);



    bool result = parser.HandleNextDocument(mockHandler);

    EXPECT_FALSE(result);

}



TEST_F(ParserTest_673, HandleNextDocument_MultipleDocuments_673) {

    input.str("a: 1\n---\nb: 2");

    Parser parser(input);

    EXPECT_CALL(mockHandler, OnDocumentStart(_)).Times(2);

    EXPECT_CALL(mockHandler, OnScalar(_, Eq("a"), _, _)).Times(1);

    EXPECT_CALL(mockHandler, OnScalar(_, Eq("1"), _, _)).Times(1);

    EXPECT_CALL(mockHandler, OnScalar(_, Eq("b"), _, _)).Times(1);

    EXPECT_CALL(mockHandler, OnScalar(_, Eq("2"), _, _)).Times(1);

    EXPECT_CALL(mockHandler, OnDocumentEnd()).Times(2);



    bool result = parser.HandleNextDocument(mockHandler);

    EXPECT_TRUE(result);



    result = parser.HandleNextDocument(mockHandler);

    EXPECT_TRUE(result);

}



TEST_F(ParserTest_673, HandleNextDocument_NoMoreDocuments_673) {

    input.str("a: 1");

    Parser parser(input);

    bool result = parser.HandleNextDocument(mockHandler);

    EXPECT_TRUE(result);



    result = parser.HandleNextDocument(mockHandler);

    EXPECT_FALSE(result);

}



TEST_F(ParserTest_673, HandleNextDocument_InvalidYaml_673) {

    input.str("a: 1\nb");

    Parser parser(input);

    EXPECT_CALL(mockHandler, OnDocumentStart(_)).Times(1);

    EXPECT_CALL(mockHandler, OnScalar(_, Eq("a"), _, _)).Times(1);

    EXPECT_CALL(mockHandler, OnScalar(_, Eq("1"), _, _)).Times(1);



    bool result = parser.HandleNextDocument(mockHandler);

    EXPECT_FALSE(result);

}



TEST_F(ParserTest_673, HandleNextDocument_SequenceYaml_673) {

    input.str("- 1\n- 2");

    Parser parser(input);

    EXPECT_CALL(mockHandler, OnDocumentStart(_)).Times(1);

    EXPECT_CALL(mockHandler, OnSequenceStart(_, _, _, _)).Times(1);

    EXPECT_CALL(mockHandler, OnScalar(_, Eq("1"), _, _)).Times(1);

    EXPECT_CALL(mockHandler, OnScalar(_, Eq("2"), _, _)).Times(1);

    EXPECT_CALL(mockHandler, OnSequenceEnd()).Times(1);

    EXPECT_CALL(mockHandler, OnDocumentEnd()).Times(1);



    bool result = parser.HandleNextDocument(mockHandler);

    EXPECT_TRUE(result);

}



TEST_F(ParserTest_673, HandleNextDocument_MapYaml_673) {

    input.str("a: 1\nb: 2");

    Parser parser(input);

    EXPECT_CALL(mockHandler, OnDocumentStart(_)).Times(1);

    EXPECT_CALL(mockHandler, OnScalar(_, Eq("a"), _, _)).Times(1);

    EXPECT_CALL(mockHandler, OnScalar(_, Eq("1"), _, _)).Times(1);

    EXPECT_CALL(mockHandler, OnScalar(_, Eq("b"), _, _)).Times(1);

    EXPECT_CALL(mockHandler, OnScalar(_, Eq("2"), _, _)).Times(1);

    EXPECT_CALL(mockHandler, OnDocumentEnd()).Times(1);



    bool result = parser.HandleNextDocument(mockHandler);

    EXPECT_TRUE(result);

}



TEST_F(ParserTest_673, HandleNextDocument_NullYaml_673) {

    input.str("a: null");

    Parser parser(input);

    EXPECT_CALL(mockHandler, OnDocumentStart(_)).Times(1);

    EXPECT_CALL(mockHandler, OnScalar(_, Eq("a"), _, _)).Times(1);

    EXPECT_CALL(mockHandler, OnNull(_, _)).Times(1);

    EXPECT_CALL(mockHandler, OnDocumentEnd()).Times(1);



    bool result = parser.HandleNextDocument(mockHandler);

    EXPECT_TRUE(result);

}
