#include <gtest/gtest.h>

#include "yaml-cpp/ostream_wrapper.h"

#include <sstream>



class OstreamWrapperTest_586 : public ::testing::Test {

protected:

    YAML::ostream_wrapper wrapper;

    std::ostringstream stream;

    YAML::ostream_wrapper stream_wrapper{stream};

};



TEST_F(OstreamWrapperTest_586, WriteToBuffer_NormalOperation_586) {

    std::string test_str = "Hello, World!";

    wrapper.write(test_str);

    EXPECT_EQ(wrapper.str(), test_str);

}



TEST_F(OstreamWrapperTest_586, WriteToStream_NormalOperation_586) {

    std::string test_str = "Hello, Stream!";

    stream_wrapper.write(test_str);

    EXPECT_EQ(stream.str(), test_str);

}



TEST_F(OstreamWrapperTest_586, WriteEmptyString_BoundaryCondition_586) {

    wrapper.write("");

    EXPECT_EQ(wrapper.str(), "");

}



TEST_F(OstreamWrapperTest_586, WriteMultipleTimes_NormalOperation_586) {

    std::string test_str1 = "First line\n";

    std::string test_str2 = "Second line";

    wrapper.write(test_str1);

    wrapper.write(test_str2);

    EXPECT_EQ(wrapper.str(), test_str1 + test_str2);

}



TEST_F(OstreamWrapperTest_586, WriteToStreamMultipleTimes_NormalOperation_586) {

    std::string test_str1 = "First line\n";

    std::string test_str2 = "Second line";

    stream_wrapper.write(test_str1);

    stream_wrapper.write(test_str2);

    EXPECT_EQ(stream.str(), test_str1 + test_str2);

}



TEST_F(OstreamWrapperTest_586, WriteWithNewlines_UpdatePos_586) {

    std::string test_str = "Line1\nLine2\n";

    wrapper.write(test_str);

    EXPECT_EQ(wrapper.row(), 3u);

    EXPECT_EQ(wrapper.col(), 6u); // After the last newline, column should be at start of new line

}



TEST_F(OstreamWrapperTest_586, WriteWithTabs_UpdatePos_586) {

    std::string test_str = "Line1\tLine2";

    wrapper.write(test_str);

    EXPECT_EQ(wrapper.row(), 1u); // No newline, so row remains 1

    EXPECT_EQ(wrapper.col(), 9u); // Column should account for tab width (assuming default 4 spaces)

}



TEST_F(OstreamWrapperTest_586, WriteWithSpecialChars_UpdatePos_586) {

    std::string test_str = "Line1\r\nLine2";

    wrapper.write(test_str);

    EXPECT_EQ(wrapper.row(), 3u); // Carriage return and newline should increment row

    EXPECT_EQ(wrapper.col(), 6u); // Column resets after newline, then increments for "Line2"

}
