#include <gtest/gtest.h>

#include "yaml-cpp/ostream_wrapper.h"

#include <sstream>



class OstreamWrapperTest_587 : public ::testing::Test {

protected:

    std::ostringstream oss;

    YAML::ostream_wrapper streamWrapperWithoutStream_587;

    YAML::ostream_wrapper streamWrapperWithStream_587;



    OstreamWrapperTest_587() : streamWrapperWithStream_587(oss) {}

};



TEST_F(OstreamWrapperTest_587, WriteToBuffer_587) {

    const char* testString = "Hello";

    std::size_t size = 5;

    streamWrapperWithoutStream_587.write(testString, size);

    EXPECT_EQ(std::string(streamWrapperWithoutStream_587.str(), size), testString);

}



TEST_F(OstreamWrapperTest_587, WriteToStream_587) {

    const char* testString = "World";

    std::size_t size = 5;

    streamWrapperWithStream_587.write(testString, size);

    EXPECT_EQ(oss.str(), testString);

}



TEST_F(OstreamWrapperTest_587, WriteEmptyString_587) {

    const char* emptyString = "";

    std::size_t size = 0;

    streamWrapperWithoutStream_587.write(emptyString, size);

    EXPECT_EQ(std::string(streamWrapperWithoutStream_587.str(), size), "");

}



TEST_F(OstreamWrapperTest_587, WriteWithNullPointer_587) {

    const char* nullPtr = nullptr;

    std::size_t size = 0;

    EXPECT_NO_THROW(streamWrapperWithoutStream_587.write(nullPtr, size));

}



TEST_F(OstreamWrapperTest_587, UpdatePositionNormal_587) {

    const char* testString = "Line1\nLine2";

    std::size_t size = 9;

    streamWrapperWithoutStream_587.write(testString, size);

    EXPECT_EQ(streamWrapperWithoutStream_587.row(), 2u);

    EXPECT_EQ(streamWrapperWithoutStream_587.col(), 6u);

}



TEST_F(OstreamWrapperTest_587, UpdatePositionWithTabs_587) {

    const char* testString = "Line1\tLine2";

    std::size_t size = 10;

    streamWrapperWithoutStream_587.write(testString, size);

    EXPECT_EQ(streamWrapperWithoutStream_587.row(), 1u);

    // Assuming tab size is 4

    EXPECT_EQ(streamWrapperWithoutStream_587.col(), 9u);

}
