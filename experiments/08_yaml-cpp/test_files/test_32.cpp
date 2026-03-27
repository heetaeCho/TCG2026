#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "yaml-cpp/ostream_wrapper.h"



using namespace YAML;

using ::testing::_;

using ::testing::Return;



class OstreamWrapperTest : public ::testing::Test {

protected:

    std::ostringstream oss;

    ostream_wrapper wrapper;



    OstreamWrapperTest() : wrapper(oss) {}

};



TEST_F(OstreamWrapperTest_32, WriteString_NormalOperation_32) {

    wrapper.write("test");

    EXPECT_EQ(oss.str(), "test");

}



TEST_F(OstreamWrapperTest_32, WriteCString_NormalOperation_32) {

    wrapper.write("test", 4);

    EXPECT_EQ(oss.str(), "test");

}



TEST_F(OstreamWrapperTest_32, WriteEmptyString_BoundaryCondition_32) {

    wrapper.write("");

    EXPECT_EQ(oss.str(), "");

}



TEST_F(OstreamWrapperTest_32, WriteCStringZeroSize_BoundaryCondition_32) {

    wrapper.write("test", 0);

    EXPECT_EQ(oss.str(), "");

}



TEST_F(OstreamWrapperTest_32, SetComment_ChangesState_32) {

    wrapper.set_comment();

    EXPECT_TRUE(wrapper.comment());

}



TEST_F(OstreamWrapperTest_32, RowAndCol_StartAtZero_32) {

    EXPECT_EQ(wrapper.row(), 0);

    EXPECT_EQ(wrapper.col(), 0);

}



TEST_F(OstreamWrapperTest_32, PositionUpdatesWithWrite_32) {

    wrapper.write("test\nline");

    EXPECT_EQ(wrapper.pos(), 9);

    EXPECT_EQ(wrapper.row(), 1);

    EXPECT_EQ(wrapper.col(), 4);

}
