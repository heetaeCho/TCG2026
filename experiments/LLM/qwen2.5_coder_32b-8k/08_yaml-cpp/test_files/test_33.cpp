#include <gtest/gtest.h>

#include "yaml-cpp/ostream_wrapper.h"

#include <sstream>



class OstreamWrapperTest_33 : public ::testing::Test {

protected:

    std::ostringstream oss;

    YAML::ostream_wrapper wrapper;



    OstreamWrapperTest_33() : wrapper(oss) {}

};



TEST_F(OstreamWrapperTest_33, WriteString_NormalOperation_33) {

    const std::string testStr = "Hello, World!";

    wrapper.write(testStr);

    EXPECT_EQ(oss.str(), testStr);

}



TEST_F(OstreamWrapperTest_33, WriteCharArray_NormalOperation_33) {

    const char* testArr = "Hello, World!";

    wrapper.write(testArr, strlen(testArr));

    EXPECT_EQ(oss.str(), testArr);

}



TEST_F(OstreamWrapperTest_33, WriteEmptyString_BoundaryCondition_33) {

    const std::string emptyStr;

    wrapper.write(emptyStr);

    EXPECT_EQ(oss.str().size(), 0);

}



TEST_F(OstreamWrapperTest_33, WriteEmptyCharArray_BoundaryCondition_33) {

    const char* emptyArr = "";

    wrapper.write(emptyArr, strlen(emptyArr));

    EXPECT_EQ(oss.str().size(), 0);

}



TEST_F(OstreamWrapperTest_33, RowColPositionTracking_33) {

    wrapper.write("Hello\nWorld");

    EXPECT_EQ(wrapper.row(), 2);

    EXPECT_EQ(wrapper.col(), 6);

}



TEST_F(OstreamWrapperTest_33, CommentFlagSet_Properly_33) {

    EXPECT_FALSE(wrapper.comment());

    wrapper.set_comment();

    EXPECT_TRUE(wrapper.comment());

}
