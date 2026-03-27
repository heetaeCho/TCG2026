#include <gtest/gtest.h>

#include <yaml-cpp/ostream_wrapper.h>

#include <sstream>



using namespace YAML;



class OstreamWrapperTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    ostream_wrapper wrapper;

    ostream_wrapper stream_wrapper{oss};



    OstreamWrapperTest() : wrapper(), stream_wrapper(oss) {}

};



TEST_F(OstreamWrapperTest, InitialPositionIsZero_29) {

    EXPECT_EQ(wrapper.pos(), 0);

}



TEST_F(OstreamWrapperTest, WriteStringIncreasesPosition_29) {

    const std::string test_string = "Hello";

    stream_wrapper.write(test_string);

    EXPECT_EQ(stream_wrapper.pos(), test_string.size());

}



TEST_F(OstreamWrapperTest, WriteCStringIncreasesPosition_29) {

    const char* test_cstring = "World";

    stream_wrapper.write(test_cstring, 5);

    EXPECT_EQ(stream_wrapper.pos(), 5);

}



TEST_F(OstreamWrapperTest, WriteEmptyStringDoesNotChangePosition_29) {

    const std::string empty_string;

    stream_wrapper.write(empty_string);

    EXPECT_EQ(stream_wrapper.pos(), 0);

}



TEST_F(OstreamWrapperTest, WriteEmptyCStringDoesNotChangePosition_29) {

    const char* test_cstring = "";

    stream_wrapper.write(test_cstring, 0);

    EXPECT_EQ(stream_wrapper.pos(), 0);

}



TEST_F(OstreamWrapperTest, MultipleWritesIncreasePositionAccumulatively_29) {

    const std::string first_string = "Hello";

    const std::string second_string = "World";

    stream_wrapper.write(first_string);

    stream_wrapper.write(second_string);

    EXPECT_EQ(stream_wrapper.pos(), first_string.size() + second_string.size());

}



TEST_F(OstreamWrapperTest, WriteUpdatesRowAndColumn_29) {

    const std::string test_string = "Hello\nWorld";

    stream_wrapper.write(test_string);

    EXPECT_EQ(stream_wrapper.row(), 1); // Newline should increment row

    EXPECT_EQ(stream_wrapper.col(), 5); // Column should be at the end of "World"

}



TEST_F(OstreamWrapperTest, SetCommentUpdatesFlag_29) {

    EXPECT_FALSE(wrapper.comment());

    wrapper.set_comment();

    EXPECT_TRUE(wrapper.comment());

}



TEST_F(OstreamWrapperTest, StringRepresentationMatchesWrittenData_29) {

    const std::string test_string = "Hello";

    stream_wrapper.write(test_string);

    EXPECT_STREQ(stream_wrapper.str(), test_string.c_str());

}
