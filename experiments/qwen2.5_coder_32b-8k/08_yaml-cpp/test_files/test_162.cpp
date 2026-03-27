#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "stream.h"

#include "scantag.h"



using namespace YAML;

using ::testing::NiceMock;

using ::testing::Return;



class MockStream : public Stream {

public:

    MOCK_METHOD(bool, operator bool, (), (const override));

    MOCK_METHOD(char, peek, (), (override));

    MOCK_METHOD(char, get, (), (override));

    MOCK_METHOD(std::string, get, (int n), (override));

    MOCK_METHOD(void, eat, (int n), (override));

    MOCK_METHOD(Mark, mark, () const, (override));

};



class ScanVerbatimTagTest_162 : public ::testing::Test {

protected:

    NiceMock<MockStream> mock_stream;

};



TEST_F(ScanVerbatimTagTest_162, NormalOperationSingleChar_162) {

    EXPECT_CALL(mock_stream, peek()).WillOnce(Return('a'));

    EXPECT_CALL(mock_stream, get()).Times(3).WillRepeatedly(Return('a'));

    EXPECT_CALL(mock_stream, mark()).WillOnce(Return(Mark()));

    EXPECT_EQ(ScanVerbatimTag(mock_stream), "a");

}



TEST_F(ScanVerbatimTagTest_162, NormalOperationMultipleChars_162) {

    EXPECT_CALL(mock_stream, peek())

        .WillOnce(Return('a'))

        .WillOnce(Return('b'))

        .WillOnce(Return('>'));

    EXPECT_CALL(mock_stream, get()).Times(4)

        .WillOnce(Return('a'))

        .WillOnce(Return('b'))

        .WillOnce(Return('>'))

        .WillOnce(Return(Mark::eof()));

    EXPECT_CALL(mock_stream, mark()).WillOnce(Return(Mark()));

    EXPECT_EQ(ScanVerbatimTag(mock_stream), "ab");

}



TEST_F(ScanVerbatimTagTest_162, BoundaryConditionEmptyString_162) {

    EXPECT_CALL(mock_stream, peek()).WillOnce(Return('>'));

    EXPECT_CALL(mock_stream, get()).Times(2)

        .WillOnce(Return('>'))

        .WillOnce(Return(Mark::eof()));

    EXPECT_CALL(mock_stream, mark()).WillOnce(Return(Mark()));

    EXPECT_EQ(ScanVerbatimTag(mock_stream), "");

}



TEST_F(ScanVerbatimTagTest_162, ExceptionalCaseEndOfFileWithoutTermination_162) {

    EXPECT_CALL(mock_stream, peek())

        .WillOnce(Return('a'))

        .WillOnce(Return('b'));

    EXPECT_CALL(mock_stream, get()).Times(3)

        .WillOnce(Return('a'))

        .WillOnce(Return('b'))

        .WillOnce(Return(Mark::eof()));

    EXPECT_CALL(mock_stream, mark()).WillOnce(Return(Mark()));

    EXPECT_THROW(ScanVerbatimTag(mock_stream), ParserException);

}



TEST_F(ScanVerbatimTagTest_162, ExceptionalCaseEndOfFileAfterTermination_162) {

    EXPECT_CALL(mock_stream, peek())

        .WillOnce(Return('>'))

        .WillOnce(Return(Mark::eof()));

    EXPECT_CALL(mock_stream, get()).Times(2)

        .WillOnce(Return('>'))

        .WillOnce(Return(Mark::eof()));

    EXPECT_CALL(mock_stream, mark()).WillOnce(Return(Mark()));

    EXPECT_EQ(ScanVerbatimTag(mock_stream), "");

}



TEST_F(ScanVerbatimTagTest_162, ExceptionalCaseEndOfFileInMiddleOfMatch_162) {

    EXPECT_CALL(mock_stream, peek())

        .WillOnce(Return('a'))

        .WillOnce(Return(Mark::eof()));

    EXPECT_CALL(mock_stream, get()).Times(3)

        .WillOnce(Return('a'))

        .WillOnce(Return(Mark::eof()))

        .WillOnce(Return(Mark::eof()));

    EXPECT_CALL(mock_stream, mark()).WillOnce(Return(Mark()));

    EXPECT_THROW(ScanVerbatimTag(mock_stream), ParserException);

}
