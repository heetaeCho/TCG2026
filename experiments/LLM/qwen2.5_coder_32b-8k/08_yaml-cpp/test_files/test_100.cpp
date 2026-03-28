#include <gtest/gtest.h>

#include "streamcharsource.h"

#include <sstream>



using namespace YAML;



class StreamCharSourceTest_100 : public ::testing::Test {

protected:

    std::istringstream input;

    Stream stream;

    StreamCharSource source;



    StreamCharSourceTest_100() : input("test"), stream(input), source(stream) {}

};



TEST_F(StreamCharSourceTest_100, BoolOperatorReturnsTrueWhenStreamHasData_100) {

    EXPECT_TRUE(static_cast<bool>(source));

}



TEST_F(StreamCharSourceTest_100, BoolOperatorReturnsFalseWhenStreamIsEmpty_100) {

    std::istringstream emptyInput;

    Stream emptyStream(emptyInput);

    StreamCharSource emptySource(emptyStream);



    EXPECT_FALSE(static_cast<bool>(emptySource));

}



TEST_F(StreamCharSourceTest_100, OperatorPlusIncreasesOffset_100) {

    auto newSource = source + 2;



    EXPECT_EQ(source.m_offset + 2, newSource.m_offset);

}



TEST_F(StreamCharSourceTest_100, SubscriptOperatorReturnsCorrectCharacter_100) {

    EXPECT_EQ('t', source[0]);

    EXPECT_EQ('e', source[1]);

}



TEST_F(StreamCharSourceTest_100, NotOperatorReturnsFalseWhenStreamHasData_100) {

    EXPECT_FALSE(!source);

}



TEST_F(StreamCharSourceTest_100, NotOperatorReturnsTrueWhenStreamIsEmpty_100) {

    std::istringstream emptyInput;

    Stream emptyStream(emptyInput);

    StreamCharSource emptySource(emptyStream);



    EXPECT_TRUE(!emptySource);

}
