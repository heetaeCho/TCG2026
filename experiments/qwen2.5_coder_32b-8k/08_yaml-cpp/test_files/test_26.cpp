#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/ostream_wrapper.h"



using namespace YAML;

using ::testing::Eq;



class OutputStreamWrapperTest_26 : public ::testing::Test {

protected:

    ostream_wrapper* wrapper;



    void SetUp() override {

        wrapper = new ostream_wrapper();

    }



    void TearDown() override {

        delete wrapper;

    }

};



TEST_F(OutputStreamWrapperTest_26, DefaultConstructorInitializesEmptyString_26) {

    EXPECT_EQ(wrapper->str(), nullptr);

}



TEST_F(OutputStreamWrapperTest_26, WriteStringUpdatesPosition_26) {

    const std::string testString = "Hello";

    wrapper->write(testString);

    EXPECT_NE(wrapper->pos(), 0);

}



TEST_F(OutputStreamWrapperTest_26, WriteCStringUpdatesPosition_26) {

    const char* testString = "World";

    wrapper->write(testString, strlen(testString));

    EXPECT_NE(wrapper->pos(), 0);

}



TEST_F(OutputStreamWrapperTest_26, WriteStringReflectsInStr_26) {

    const std::string testString = "Hello";

    wrapper->write(testString);

    wrapper->str();

    EXPECT_EQ(std::string(wrapper->str()), testString);

}



TEST_F(OutputStreamWrapperTest_26, WriteCStringReflectsInStr_26) {

    const char* testString = "World";

    wrapper->write(testString, strlen(testString));

    wrapper->str();

    EXPECT_EQ(std::string(wrapper->str()), testString);

}



TEST_F(OutputStreamWrapperTest_26, MultipleWritesConcatenateStrings_26) {

    const std::string firstString = "Hello ";

    const std::string secondString = "World";

    wrapper->write(firstString);

    wrapper->write(secondString);

    wrapper->str();

    EXPECT_EQ(std::string(wrapper->str()), firstString + secondString);

}



TEST_F(OutputStreamWrapperTest_26, PositionIncrementsWithWrite_26) {

    const std::string testString = "Hello";

    size_t initialPos = wrapper->pos();

    wrapper->write(testString);

    EXPECT_GT(wrapper->pos(), initialPos);

}



TEST_F(OutputStreamWrapperTest_26, RowAndColumnUpdateWithNewline_26) {

    const char* testString = "Hello\nWorld";

    wrapper->write(testString, strlen(testString));

    EXPECT_EQ(wrapper->row(), 1u);

    EXPECT_GT(wrapper->col(), 0u);

}



TEST_F(OutputStreamWrapperTest_26, SetCommentFlagSetsCorrectly_26) {

    wrapper->set_comment();

    EXPECT_TRUE(wrapper->comment());

}
