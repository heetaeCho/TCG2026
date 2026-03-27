#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "streamcharsource.h"



namespace YAML {

class MockStream : public Stream {

public:

    MOCK_METHOD(bool, Good, (), (const));

};



class StreamCharSourceTest_101 : public ::testing::Test {

protected:

    MockStream mock_stream;

    StreamCharSource source;



    StreamCharSourceTest_101() : source(mock_stream) {}

};

}



using namespace YAML;



TEST_F(StreamCharSourceTest_101, InitialOffsetIsZero_101) {

    EXPECT_EQ((source + 0).m_offset, 0);

}



TEST_F(StreamCharSourceTest_101, IncrementOperatorIncreasesOffset_101) {

    EXPECT_EQ((source + 5).m_offset, 5);

}



TEST_F(StreamCharSourceTest_101, DecrementOperatorDoesNotDecreaseBelowZero_101) {

    EXPECT_EQ((source - 1).m_offset, 0);

}



TEST_F(StreamCharSourceTest_101, OperatorBoolReturnsTrueWhenStreamIsGood_101) {

    EXPECT_CALL(mock_stream, Good()).WillOnce(::testing::Return(true));

    EXPECT_TRUE(static_cast<bool>(source));

}



TEST_F(StreamCharSourceTest_101, OperatorBoolReturnsFalseWhenStreamIsNotGood_101) {

    EXPECT_CALL(mock_stream, Good()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(static_cast<bool>(source));

}



TEST_F(StreamCharSourceTest_101, OperatorNotReturnsTrueWhenStreamIsNotGood_101) {

    EXPECT_CALL(mock_stream, Good()).WillOnce(::testing::Return(false));

    EXPECT_TRUE(!source);

}



TEST_F(StreamCharSourceTest_101, OperatorNotReturnsFalseWhenStreamIsGood_101) {

    EXPECT_CALL(mock_stream, Good()).WillOnce(::testing::Return(true));

    EXPECT_FALSE(!source);

}

```


