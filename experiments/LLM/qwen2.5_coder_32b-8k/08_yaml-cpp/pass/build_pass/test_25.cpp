#include <gtest/gtest.h>

#include "yaml-cpp/ostream_wrapper.h"



class OstreamWrapperTest_25 : public ::testing::Test {

protected:

    YAML::ostream_wrapper wrapper;

};



TEST_F(OstreamWrapperTest_25, DefaultConstructorSetsDefaults_25) {

    EXPECT_FALSE(wrapper.comment());

}



TEST_F(OstreamWrapperTest_25, SetCommentChangesCommentStatus_25) {

    wrapper.set_comment();

    EXPECT_TRUE(wrapper.comment());

}



TEST_F(OstreamWrapperTest_25, WriteStringUpdatesPosition_25) {

    std::string test_str = "Hello";

    size_t initial_pos = wrapper.pos();

    wrapper.write(test_str);

    EXPECT_EQ(wrapper.pos(), initial_pos + test_str.size());

}



TEST_F(OstreamWrapperTest_25, WriteCharArrayUpdatesPosition_25) {

    const char* test_str = "World";

    size_t size = strlen(test_str);

    size_t initial_pos = wrapper.pos();

    wrapper.write(test_str, size);

    EXPECT_EQ(wrapper.pos(), initial_pos + size);

}



TEST_F(OstreamWrapperTest_25, WriteStringUpdatesRowAndColumn_25) {

    std::string test_str = "Hello\nWorld";

    wrapper.write(test_str);

    EXPECT_EQ(wrapper.row(), 1u);

    EXPECT_EQ(wrapper.col(), 5u); // After newline, column resets to 0 and then increments by the length of "World"

}



TEST_F(OstreamWrapperTest_25, WriteCharArrayUpdatesRowAndColumn_25) {

    const char* test_str = "Hello\nWorld";

    size_t size = strlen(test_str);

    wrapper.write(test_str, size);

    EXPECT_EQ(wrapper.row(), 1u);

    EXPECT_EQ(wrapper.col(), 5u); // After newline, column resets to 0 and then increments by the length of "World"

}



TEST_F(OstreamWrapperTest_25, WriteEmptyStringDoesNotChangePosition_25) {

    std::string test_str = "";

    size_t initial_pos = wrapper.pos();

    wrapper.write(test_str);

    EXPECT_EQ(wrapper.pos(), initial_pos);

}



TEST_F(OstreamWrapperTest_25, WriteNullCharArrayDoesNotChangePosition_25) {

    const char* test_str = nullptr;

    size_t size = 0;

    size_t initial_pos = wrapper.pos();

    wrapper.write(test_str, size);

    EXPECT_EQ(wrapper.pos(), initial_pos);

}



TEST_F(OstreamWrapperTest_25, WriteNullCharArrayWithSizeDoesNotChangePosition_25) {

    const char* test_str = nullptr;

    size_t size = 10; // Arbitrary non-zero size

    size_t initial_pos = wrapper.pos();

    EXPECT_THROW(wrapper.write(test_str, size), std::invalid_argument); // Assuming a throw on null pointer with non-zero size

}



TEST_F(OstreamWrapperTest_25, WriteStringWithNewlinesUpdatesRowAndColumnCorrectly_25) {

    std::string test_str = "Line1\nLine2\nLine3";

    wrapper.write(test_str);

    EXPECT_EQ(wrapper.row(), 2u); // After two newlines, row should be 2

    EXPECT_EQ(wrapper.col(), 5u); // Column should be the length of the last line, which is "Line3"

}
