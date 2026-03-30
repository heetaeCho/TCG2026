#include <gtest/gtest.h>

#include "yaml-cpp/ostream_wrapper.h"

#include <sstream>



class OstreamWrapperTest_31 : public ::testing::Test {

protected:

    std::ostringstream oss;

    YAML::ostream_wrapper wrapper;



    void SetUp() override {

        wrapper = YAML::ostream_wrapper(oss);

    }

};



TEST_F(OstreamWrapperTest_31, WriteString_NormalOperation_31) {

    wrapper.write("Hello");

    EXPECT_EQ(oss.str(), "Hello");

}



TEST_F(OstreamWrapperTest_31, WriteCString_NormalOperation_31) {

    wrapper.write("World", 5);

    EXPECT_EQ(oss.str(), "World");

}



TEST_F(OstreamWrapperTest_31, WriteString_EmptyString_31) {

    wrapper.write("");

    EXPECT_EQ(oss.str(), "");

}



TEST_F(OstreamWrapperTest_31, WriteCString_EmptyString_31) {

    wrapper.write("", 0);

    EXPECT_EQ(oss.str(), "");

}



TEST_F(OstreamWrapperTest_31, WriteCString_ExceedsLength_31) {

    wrapper.write("Hello", 10); // Length exceeds actual string length

    EXPECT_EQ(oss.str(), "Hello");

}



TEST_F(OstreamWrapperTest_31, RowAndCol_UpdateAfterWrite_31) {

    wrapper.write("Hello\nWorld");

    EXPECT_EQ(wrapper.row(), 2);

    EXPECT_EQ(wrapper.col(), 6);

}



TEST_F(OstreamWrapperTest_31, Position_UpdateAfterWrite_31) {

    wrapper.write("Hello");

    EXPECT_EQ(wrapper.pos(), 5);

}



TEST_F(OstreamWrapperTest_31, SetComment_FlagSet_31) {

    wrapper.set_comment();

    EXPECT_TRUE(wrapper.comment());

}
