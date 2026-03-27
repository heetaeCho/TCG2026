#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "./TestProjects/yaml-cpp/src/exp.cpp"



using namespace YAML;

using namespace YAML::Exp;



class StreamMock : public Stream {

public:

    MOCK_METHOD(char, get, (), (override));

    MOCK_CONST_METHOD0(mark, Mark());

};



TEST_F(StreamMockTest_168, PutIncreasesCount_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('a'));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, "\x07");

}



TEST_F(StreamMockTest_168, BoundaryConditionSingleQuoteEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('\''));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, "'");

}



TEST_F(StreamMockTest_168, BoundaryConditionDoubleQuoteEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('\"'));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, "\"");

}



TEST_F(StreamMockTest_168, BoundaryConditionBackslashEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('\\'));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, "\\");

}



TEST_F(StreamMockTest_168, BoundaryConditionForwardSlashEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('/'));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, "/");

}



TEST_F(StreamMockTest_168, BoundaryConditionNULLEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('0'));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, "\x00");

}



TEST_F(StreamMockTest_168, BoundaryConditionLineTabEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('t'));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, "\x09");

}



TEST_F(StreamMockTest_168, BoundaryConditionLineFeedEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('n'));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, "\x0A");

}



TEST_F(StreamMockTest_168, BoundaryConditionVerticalTabEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('v'));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, "\x0B");

}



TEST_F(StreamMockTest_168, BoundaryConditionFormFeedEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('f'));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, "\x0C");

}



TEST_F(StreamMockTest_168, BoundaryConditionCarriageReturnEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('r'));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, "\x0D");

}



TEST_F(StreamMockTest_168, BoundaryConditionEscapeEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('e'));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, "\x1B");

}



TEST_F(StreamMockTest_168, BoundaryConditionSpaceEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return(' '));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, " ");

}



TEST_F(StreamMockTest_168, BoundaryConditionNextLineEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('N'));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, "\x85");

}



TEST_F(StreamMockTest_168, BoundaryConditionNonBreakingSpaceEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('_'));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, "\xA0");

}



TEST_F(StreamMockTest_168, BoundaryConditionLineSeparatorEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('L'));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, "\xE2\x80\xA8");

}



TEST_F(StreamMockTest_168, BoundaryConditionParagraphSeparatorEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('P'));

    std::string result = Escape(streamMock);

    EXPECT_EQ(result, "\xE2\x80\xA9");

}



TEST_F(StreamMockTest_168, ExceptionalCaseInvalidEscape_168) {

    StreamMock streamMock;

    EXPECT_CALL(streamMock, get()).WillOnce(::testing::Return('\\')).WillOnce(::testing::Return('z'));

    EXPECT_THROW(Escape(streamMock), ParserException);

}
