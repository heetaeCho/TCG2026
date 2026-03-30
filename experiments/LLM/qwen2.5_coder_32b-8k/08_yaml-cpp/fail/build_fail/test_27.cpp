#include <gtest/gtest.h>

#include "yaml-cpp/ostream_wrapper.h"

#include <sstream>



using namespace YAML;



class OstreamWrapperTest_27 : public ::testing::Test {

protected:

    std::ostringstream oss;

    ostream_wrapper wrapper;



    void SetUp() override {

        wrapper = ostream_wrapper(oss);

    }

};



TEST_F(OstreamWrapperTest_27, InitialRowIsZero_27) {

    EXPECT_EQ(wrapper.row(), 0);

}



TEST_F(OstreamWrapperTest_27, WriteStringIncreasesRow_27) {

    wrapper.write("Hello\nWorld");

    EXPECT_EQ(wrapper.row(), 1);

}



TEST_F(OstreamWrapperTest_27, WriteCharPointerIncreasesRow_27) {

    const char* str = "Hello\nWorld";

    wrapper.write(str, std::strlen(str));

    EXPECT_EQ(wrapper.row(), 1);

}



TEST_F(OstreamWrapperTest_27, MultipleNewLinesIncreaseRow_27) {

    wrapper.write("Line1\nLine2\nLine3");

    EXPECT_EQ(wrapper.row(), 2);

}



TEST_F(OstreamWrapperTest_27, NoNewLineDoesNotChangeRow_27) {

    wrapper.write("NoNewlineHere");

    EXPECT_EQ(wrapper.row(), 0);

}



TEST_F(OstreamWrapperTest_27, WriteEmptyStringDoesNotChangeRow_27) {

    wrapper.write("");

    EXPECT_EQ(wrapper.row(), 0);

}



TEST_F(OstreamWrapperTest_27, WriteNullCharPointerDoesNotChangeRow_27) {

    const char* str = nullptr;

    wrapper.write(str, 0);

    EXPECT_EQ(wrapper.row(), 0);

}
