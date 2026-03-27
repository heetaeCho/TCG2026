#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <iostream>

#include "yaml-cpp/ostream_wrapper.h"



using namespace YAML;

using namespace testing;



class OstreamWrapperTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    ostream_wrapper wrapperWithoutStream;

    ostream_wrapper wrapperWithStream;



    OstreamWrapperTest() : wrapperWithStream(oss) {}

};



TEST_F(OstreamWrapperTest_30, DefaultConstructorSetsCommentFalse_30) {

    EXPECT_FALSE(wrapperWithoutStream.comment());

}



TEST_F(OstreamWrapperTest_30, StreamConstructorSetsCommentFalse_30) {

    EXPECT_FALSE(wrapperWithStream.comment());

}



TEST_F(OstreamWrapperTest_30, SetCommentChangesCommentState_30) {

    wrapperWithoutStream.set_comment();

    EXPECT_TRUE(wrapperWithoutStream.comment());



    wrapperWithStream.set_comment();

    EXPECT_TRUE(wrapperWithStream.comment());

}



TEST_F(OstreamWrapperTest_30, WriteStringUpdatesPosition_30) {

    std::string testString = "Hello";

    wrapperWithoutStream.write(testString);

    EXPECT_EQ(wrapperWithoutStream.pos(), testString.size());



    wrapperWithStream.write(testString);

    EXPECT_EQ(wrapperWithStream.pos(), testString.size());

}



TEST_F(OstreamWrapperTest_30, WriteCStringUpdatesPosition_30) {

    const char* testString = "World";

    std::size_t size = strlen(testString);



    wrapperWithoutStream.write(testString, size);

    EXPECT_EQ(wrapperWithoutStream.pos(), size);



    wrapperWithStream.write(testString, size);

    EXPECT_EQ(wrapperWithStream.pos(), size);

}



TEST_F(OstreamWrapperTest_30, WriteStringUpdatesRowAndColumn_30) {

    std::string testString = "Line1\nLine2";

    wrapperWithoutStream.write(testString);

    EXPECT_EQ(wrapperWithoutStream.row(), 2u);

    EXPECT_EQ(wrapperWithoutStream.col(), 6u);



    wrapperWithStream.write(testString);

    EXPECT_EQ(wrapperWithStream.row(), 2u);

    EXPECT_EQ(wrapperWithStream.col(), 6u);

}



TEST_F(OstreamWrapperTest_30, WriteCStringUpdatesRowAndColumn_30) {

    const char* testString = "Line1\nLine2";

    std::size_t size = strlen(testString);



    wrapperWithoutStream.write(testString, size);

    EXPECT_EQ(wrapperWithoutStream.row(), 2u);

    EXPECT_EQ(wrapperWithoutStream.col(), 6u);



    wrapperWithStream.write(testString, size);

    EXPECT_EQ(wrapperWithStream.row(), 2u);

    EXPECT_EQ(wrapperWithStream.col(), 6u);

}



TEST_F(OstreamWrapperTest_30, WriteEmptyStringDoesNotChangePosition_30) {

    std::string emptyString = "";

    wrapperWithoutStream.write(emptyString);

    EXPECT_EQ(wrapperWithoutStream.pos(), 0u);



    wrapperWithStream.write(emptyString);

    EXPECT_EQ(wrapperWithStream.pos(), 0u);

}



TEST_F(OstreamWrapperTest_30, WriteEmptyCStringDoesNotChangePosition_30) {

    const char* emptyString = "";

    std::size_t size = strlen(emptyString);



    wrapperWithoutStream.write(emptyString, size);

    EXPECT_EQ(wrapperWithoutStream.pos(), 0u);



    wrapperWithStream.write(emptyString, size);

    EXPECT_EQ(wrapperWithStream.pos(), 0u);

}
