#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/re2/util/pcre.h"



namespace re2 {

    class MockDestination {

    public:

        MOCK_METHOD2(ParseFrom, bool(const char*, size_t));

    };

}



using namespace re2;



class PCREMatchObjectTest : public ::testing::Test {};



TEST_F(PCREMatchObjectTest_183, ParseWithNullDestReturnsTrue_183) {

    const char* str = "test";

    size_t n = 4;

    EXPECT_TRUE(_PCRE_MatchObject<MockDestination>::Parse(str, n, nullptr));

}



TEST_F(PCREMatchObjectTest_183, ParseWithNonNullDestInvokesParseFrom_183) {

    const char* str = "test";

    size_t n = 4;

    MockDestination mock_dest;

    EXPECT_CALL(mock_dest, ParseFrom(str, n)).WillOnce(::testing::Return(true));

    EXPECT_TRUE(_PCRE_MatchObject<MockDestination>::Parse(str, n, &mock_dest));

}



TEST_F(PCREMatchObjectTest_183, ParseWithNonNullDestAndFalseParseFromReturnsFalse_183) {

    const char* str = "test";

    size_t n = 4;

    MockDestination mock_dest;

    EXPECT_CALL(mock_dest, ParseFrom(str, n)).WillOnce(::testing::Return(false));

    EXPECT_FALSE(_PCRE_MatchObject<MockDestination>::Parse(str, n, &mock_dest));

}



TEST_F(PCREMatchObjectTest_183, ParseWithEmptyStringReturnsTrueWhenDestIsNull_183) {

    const char* str = "";

    size_t n = 0;

    EXPECT_TRUE(_PCRE_MatchObject<MockDestination>::Parse(str, n, nullptr));

}



TEST_F(PCREMatchObjectTest_183, ParseWithEmptyStringInvokesParseFromWhenDestIsNonNull_183) {

    const char* str = "";

    size_t n = 0;

    MockDestination mock_dest;

    EXPECT_CALL(mock_dest, ParseFrom(str, n)).WillOnce(::testing::Return(true));

    EXPECT_TRUE(_PCRE_MatchObject<MockDestination>::Parse(str, n, &mock_dest));

}
