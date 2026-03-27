#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/value.cpp"



using namespace Exiv2;

using namespace testing;



class LangAltValueTest_856 : public ::testing::Test {

protected:

    LangAltValue langAltValue;

};



TEST_F(LangAltValueTest_856, ToStringDefaultParameter_856) {

    EXPECT_EQ(langAltValue.toString(0), "x-default");

}



TEST_F(LangAltValueTest_856, ToStringNonZeroParameter_856) {

    EXPECT_EQ(langAltValue.toString(123), "x-default");

}



TEST_F(LangAltValueTest_856, ToStringMaxSizeT_856) {

    EXPECT_EQ(langAltValue.toString(std::numeric_limits<size_t>::max()), "x-default");

}
