#include <gtest/gtest.h>

#include "yaml-cpp/ostream_wrapper.h"

#include <sstream>



class OstreamWrapperTest_28 : public ::testing::Test {

protected:

    std::ostringstream stream;

    YAML::ostream_wrapper wrapper;



    void SetUp() override {

        wrapper = YAML::ostream_wrapper(stream);

    }

};



TEST_F(OstreamWrapperTest_28, InitialColumnPositionIsZero_28) {

    EXPECT_EQ(wrapper.col(), 0);

}



TEST_F(OstreamWrapperTest_28, WriteStringUpdatesColumnPosition_28) {

    wrapper.write("Hello");

    EXPECT_EQ(wrapper.col(), 5);

}



TEST_F(OstreamWrapperTest_28, WriteCStringUpdatesColumnPosition_28) {

    wrapper.write("World", 5);

    EXPECT_EQ(wrapper.col(), 5);

}



TEST_F(OstreamWrapperTest_28, WriteStringWithNewlineUpdatesRowAndColumnPosition_28) {

    wrapper.write("Hello\nWorld");

    EXPECT_EQ(wrapper.row(), 1);

    EXPECT_EQ(wrapper.col(), 5);

}



TEST_F(OstreamWrapperTest_28, WriteCStringWithNewlineUpdatesRowAndColumnPosition_28) {

    wrapper.write("Hello\nWorld", 11);

    EXPECT_EQ(wrapper.row(), 1);

    EXPECT_EQ(wrapper.col(), 5);

}



TEST_F(OstreamWrapperTest_28, WriteEmptyStringDoesNotChangePosition_28) {

    wrapper.write("");

    EXPECT_EQ(wrapper.col(), 0);

    EXPECT_EQ(wrapper.row(), 0);

}



TEST_F(OstreamWrapperTest_28, WriteEmptyCStringDoesNotChangePosition_28) {

    wrapper.write("", 0);

    EXPECT_EQ(wrapper.col(), 0);

    EXPECT_EQ(wrapper.row(), 0);

}



TEST_F(OstreamWrapperTest_28, SetCommentSetsCommentFlagToTrue_28) {

    wrapper.set_comment();

    EXPECT_TRUE(wrapper.comment());

}
