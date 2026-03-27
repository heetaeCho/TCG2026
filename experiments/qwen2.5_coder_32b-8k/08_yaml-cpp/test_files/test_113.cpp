#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "regeximpl.h"

#include "stream.h"



using namespace YAML;

using ::testing::NiceMock;



class MockStream : public Stream {

public:

    MockStream(std::istream &input) : Stream(input) {}



    MOCK_CONST_METHOD0(bool, operator bool());

    MOCK_METHOD0(get, char());

    MOCK_METHOD1(get, std::string(int));

    MOCK_METHOD1(eat, void(int));

};



class RegExTest_113 : public ::testing::Test {

protected:

    NiceMock<MockStream> mockStream;

    RegEx regEx;



    RegExTest_113() : mockStream(std::istringstream("")), regEx('a') {}

};



TEST_F(RegExTest_113, MatchSingleCharacterSuccess_113) {

    EXPECT_CALL(mockStream, get()).WillOnce(::testing::Return('a'));

    EXPECT_EQ(regEx.Match(mockStream), 1);

}



TEST_F(RegExTest_113, MatchSingleCharacterFailure_113) {

    EXPECT_CALL(mockStream, get()).WillOnce(::testing::Return('b'));

    EXPECT_EQ(regEx.Match(mockStream), -1);

}



TEST_F(RegExTest_113, MatchEmptyStream_113) {

    EXPECT_CALL(mockStream, bool()).WillOnce(::testing::Return(false));

    EXPECT_EQ(regEx.Match(mockStream), -1);

}



TEST_F(RegExTest_113, MatchMultipleCharactersSuccess_113) {

    regEx = RegEx("abc", REGEX_OP::REGEX_SEQ);

    std::istringstream input("abc");

    MockStream mockStream(input);

    

    EXPECT_CALL(mockStream, get()).WillOnce(::testing::Return('a'))

                                  .WillOnce(::testing::Return('b'))

                                  .WillOnce(::testing::Return('c'));

    EXPECT_EQ(regEx.Match(mockStream), 3);

}



TEST_F(RegExTest_113, MatchMultipleCharactersFailure_113) {

    regEx = RegEx("abc", REGEX_OP::REGEX_SEQ);

    std::istringstream input("abcd");

    MockStream mockStream(input);

    

    EXPECT_CALL(mockStream, get()).WillOnce(::testing::Return('a'))

                                  .WillOnce(::testing::Return('b'))

                                  .WillOnce(::testing::Return('d'));

    EXPECT_EQ(regEx.Match(mockStream), -1);

}



TEST_F(RegExTest_113, MatchRangeSuccess_113) {

    regEx = RegEx('a', 'c');

    std::istringstream input("b");

    MockStream mockStream(input);



    EXPECT_CALL(mockStream, get()).WillOnce(::testing::Return('b'));

    EXPECT_EQ(regEx.Match(mockStream), 1);

}



TEST_F(RegExTest_113, MatchRangeFailure_113) {

    regEx = RegEx('a', 'c');

    std::istringstream input("d");

    MockStream mockStream(input);



    EXPECT_CALL(mockStream, get()).WillOnce(::testing::Return('d'));

    EXPECT_EQ(regEx.Match(mockStream), -1);

}
