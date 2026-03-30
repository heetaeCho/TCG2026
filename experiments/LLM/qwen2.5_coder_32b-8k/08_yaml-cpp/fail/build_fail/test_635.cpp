#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/ostream_wrapper.h"

#include "TestProjects/yaml-cpp/src/emitterutils.cpp"



using namespace YAML::Utils;

using ::testing::Eq;



class WriteAnchorTest_635 : public ::testing::Test {

protected:

    std::ostringstream oss;

    ostream_wrapper out{oss};

};



TEST_F(WriteAnchorTest_635, NormalOperation_635) {

    const char* str = "test";

    std::size_t size = 4;

    bool result = WriteAnchor(out, str, size);

    

    EXPECT_TRUE(result);

    EXPECT_STREQ(out.str(), "&test");

}



TEST_F(WriteAnchorTest_635, EmptyString_635) {

    const char* str = "";

    std::size_t size = 0;

    bool result = WriteAnchor(out, str, size);



    EXPECT_TRUE(result);

    EXPECT_STREQ(out.str(), "&");

}



TEST_F(WriteAnchorTest_635, SingleCharacter_635) {

    const char* str = "a";

    std::size_t size = 1;

    bool result = WriteAnchor(out, str, size);



    EXPECT_TRUE(result);

    EXPECT_STREQ(out.str(), "&a");

}



TEST_F(WriteAnchorTest_635, LargeString_635) {

    const char* str = "averylongstringthatshouldworkwithoutanyissues";

    std::size_t size = 40;

    bool result = WriteAnchor(out, str, size);



    EXPECT_TRUE(result);

    EXPECT_STREQ(out.str(), "&averylongstringthatshouldworkwithoutanyissues");

}
