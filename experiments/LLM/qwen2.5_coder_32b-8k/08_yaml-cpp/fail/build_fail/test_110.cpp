#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/src/regeximpl.h"

#include "yaml-cpp/src/stream.h"

#include <sstream>



using namespace YAML;

using ::testing::_;

using ::testing::NiceMock;



class MockStream : public Stream {

public:

    MOCK_CONST_METHOD0(operator bool, bool());

    MOCK_METHOD0(get, char());

    MOCK_METHOD1(get, std::string(int));

};



TEST_F(RegExTest_110, MatchesCharacter_NormalOperation_110) {

    RegEx regex('a');

    EXPECT_TRUE(regex.Matches('a'));

    EXPECT_FALSE(regex.Matches('b'));

}



TEST_F(RegExTest_110, MatchesRange_NormalOperation_110) {

    RegEx regex('a', 'c');

    EXPECT_TRUE(regex.Matches('a'));

    EXPECT_TRUE(regex.Matches('b'));

    EXPECT_TRUE(regex.Matches('c'));

    EXPECT_FALSE(regex.Matches('d'));

}



TEST_F(RegExTest_110, MatchesString_NormalOperation_110) {

    RegEx regex("abc");

    EXPECT_TRUE(regex.Matches("abc"));

    EXPECT_FALSE(regex.Matches("abcd"));

    EXPECT_FALSE(regex.Matches("ab"));

}



TEST_F(RegExTest_110, MatchesStream_NormalOperation_110) {

    std::istringstream iss("abc");

    Stream stream(iss);

    RegEx regex("abc");

    EXPECT_TRUE(regex.Matches(stream));

}



TEST_F(RegExTest_110, MatchCharacter_NormalOperation_110) {

    RegEx regex('a');

    EXPECT_EQ(regex.Match('a'), 1);

    EXPECT_EQ(regex.Match('b'), -1);

}



TEST_F(RegExTest_110, MatchRange_NormalOperation_110) {

    RegEx regex('a', 'c');

    EXPECT_EQ(regex.Match('a'), 1);

    EXPECT_EQ(regex.Match('b'), 1);

    EXPECT_EQ(regex.Match('c'), 1);

    EXPECT_EQ(regex.Match('d'), -1);

}



TEST_F(RegExTest_110, MatchString_NormalOperation_110) {

    RegEx regex("abc");

    EXPECT_EQ(regex.Match("abc"), 3);

    EXPECT_EQ(regex.Match("abcd"), -1);

    EXPECT_EQ(regex.Match("ab"), -1);

}



TEST_F(RegExTest_110, MatchStream_NormalOperation_110) {

    std::istringstream iss("abc");

    Stream stream(iss);

    RegEx regex("abc");

    EXPECT_EQ(regex.Match(stream), 3);

}



TEST_F(RegExTest_110, MatchesEmptyString_BoundaryCondition_110) {

    RegEx regex("");

    EXPECT_TRUE(regex.Matches(""));

    EXPECT_FALSE(regex.Matches("a"));

}



TEST_F(RegExTest_110, MatchEmptyString_BoundaryCondition_110) {

    RegEx regex("");

    EXPECT_EQ(regex.Match(""), 0);

    EXPECT_EQ(regex.Match("a"), -1);

}



TEST_F(RegExTest_110, MatchesSingleCharacter_BoundaryCondition_110) {

    RegEx regex('a');

    EXPECT_TRUE(regex.Matches('a'));

    EXPECT_FALSE(regex.Matches('b'));

}



TEST_F(RegExTest_110, MatchSingleCharacter_BoundaryCondition_110) {

    RegEx regex('a');

    EXPECT_EQ(regex.Match('a'), 1);

    EXPECT_EQ(regex.Match('b'), -1);

}



TEST_F(RegExTest_110, MatchesStreamEmptyString_BoundaryCondition_110) {

    std::istringstream iss("");

    Stream stream(iss);

    RegEx regex("");

    EXPECT_TRUE(regex.Matches(stream));

}



TEST_F(RegExTest_110, MatchStreamEmptyString_BoundaryCondition_110) {

    std::istringstream iss("");

    Stream stream(iss);

    RegEx regex("");

    EXPECT_EQ(regex.Match(stream), 0);

}



TEST_F(RegExTest_110, MatchesStreamSingleCharacter_BoundaryCondition_110) {

    std::istringstream iss("a");

    Stream stream(iss);

    RegEx regex('a');

    EXPECT_TRUE(regex.Matches(stream));

}



TEST_F(RegExTest_110, MatchStreamSingleCharacter_BoundaryCondition_110) {

    std::istringstream iss("a");

    Stream stream(iss);

    RegEx regex('a');

    EXPECT_EQ(regex.Match(stream), 1);

}



TEST_F(RegExTest_110, MatchesStreamMultipleCharacters_NormalOperation_110) {

    std::istringstream iss("abc");

    Stream stream(iss);

    RegEx regex("abc");

    EXPECT_TRUE(regex.Matches(stream));

}



TEST_F(RegExTest_110, MatchStreamMultipleCharacters_NormalOperation_110) {

    std::istringstream iss("abc");

    Stream stream(iss);

    RegEx regex("abc");

    EXPECT_EQ(regex.Match(stream), 3);

}



TEST_F(RegExTest_110, MatchesInvalidStream_ErrorCase_110) {

    NiceMock<MockStream> mockStream;

    ON_CALL(mockStream, operator bool()).WillByDefault(testing::Return(false));

    RegEx regex("abc");

    EXPECT_FALSE(regex.Matches(mockStream));

}



TEST_F(RegExTest_110, MatchInvalidStream_ErrorCase_110) {

    NiceMock<MockStream> mockStream;

    ON_CALL(mockStream, operator bool()).WillByDefault(testing::Return(false));

    RegEx regex("abc");

    EXPECT_EQ(regex.Match(mockStream), -1);

}
