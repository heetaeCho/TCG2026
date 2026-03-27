#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <yaml-cpp/yaml.h>

#include <sstream>



using namespace YAML;

using ::testing::StrictMock;



// Mock EventHandler to verify interactions with Parser

class MockEventHandler : public EventHandler {

public:

    MOCK_METHOD(void, OnDocumentStart, (const Mark &mark), (override));

    MOCK_METHOD(void, OnDocumentEnd, (), (override));

    MOCK_METHOD(void, OnNull, (const Mark &mark, anchor_t anchor), (override));

    MOCK_METHOD(void, OnAlias, (const Mark &mark, anchor_t anchor), (override));

    MOCK_METHOD(void, OnScalar, (const Mark &mark, const std::string &tag, anchor_t anchor, const std::string &value), (override));

    MOCK_METHOD(void, OnSequenceStart, (const Mark &mark, const std::string &tag, anchor_t anchor, EmitterStyle::value style), (override));

    MOCK_METHOD(void, OnSequenceEnd, (), (override));

    MOCK_METHOD(void, OnMapStart, (const Mark &mark, const std::string &tag, anchor_t anchor, EmitterStyle::value style), (override));

    MOCK_METHOD(void, OnMapEnd, (), (override));

};



TEST(LoadAllTest_584, SingleDocument_584) {

    std::istringstream input("key: value");

    std::vector<Node> docs = LoadAll(input);

    ASSERT_EQ(docs.size(), 1);

    EXPECT_TRUE(docs[0].IsMap());

}



TEST(LoadAllTest_584, MultipleDocuments_584) {

    std::istringstream input("---\nkey1: value1\n---\nkey2: value2");

    std::vector<Node> docs = LoadAll(input);

    ASSERT_EQ(docs.size(), 2);

    EXPECT_TRUE(docs[0].IsMap());

    EXPECT_TRUE(docs[1].IsMap());

}



TEST(LoadAllTest_584, EmptyInput_584) {

    std::istringstream input("");

    std::vector<Node> docs = LoadAll(input);

    ASSERT_EQ(docs.size(), 0);

}



TEST(LoadAllTest_584, NullDocument_584) {

    std::istringstream input("--- ~");

    std::vector<Node> docs = LoadAll(input);

    ASSERT_EQ(docs.size(), 1);

    EXPECT_TRUE(docs[0].IsNull());

}



TEST(LoadAllTest_584, InvalidYAML_584) {

    std::istringstream input("key: value\n- invalid");

    EXPECT_THROW(LoadAll(input), ParserException);

}



// Test for boundary conditions with empty documents

TEST(LoadAllTest_584, EmptyDocuments_584) {

    std::istringstream input("---\n---\n---");

    std::vector<Node> docs = LoadAll(input);

    ASSERT_EQ(docs.size(), 3);

    EXPECT_TRUE(docs[0].IsNull());

    EXPECT_TRUE(docs[1].IsNull());

    EXPECT_TRUE(docs[2].IsNull());

}



// Test for interaction with Parser through MockEventHandler

TEST(LoadAllTest_584, VerifyParserInteractions_584) {

    std::istringstream input("key: value");

    StrictMock<MockEventHandler> mockEventHandler;



    Parser parser(input);

    EXPECT_CALL(mockEventHandler, OnDocumentStart(::testing::_)).Times(1);

    EXPECT_CALL(mockEventHandler, OnScalar(::testing::_, ::testing::_, ::testing::_, "value")).Times(1);

    EXPECT_CALL(mockEventHandler, OnDocumentEnd()).Times(1);



    while (parser.HandleNextDocument(mockEventHandler)) {

        // Document processing

    }

}



// Test for handling of sequences

TEST(LoadAllTest_584, SequenceHandling_584) {

    std::istringstream input("- item1\n- item2");

    std::vector<Node> docs = LoadAll(input);

    ASSERT_EQ(docs.size(), 1);

    EXPECT_TRUE(docs[0].IsSequence());

    EXPECT_EQ(docs[0].size(), 2);

}



// Test for handling of maps

TEST(LoadAllTest_584, MapHandling_584) {

    std::istringstream input("key1: value1\nkey2: value2");

    std::vector<Node> docs = LoadAll(input);

    ASSERT_EQ(docs.size(), 1);

    EXPECT_TRUE(docs[0].IsMap());

    EXPECT_EQ(docs[0]["key1"].as<std::string>(), "value1");

    EXPECT_EQ(docs[0]["key2"].as<std::string>(), "value2");

}
