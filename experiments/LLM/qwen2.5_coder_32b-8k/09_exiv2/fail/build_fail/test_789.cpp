#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/value.cpp"



using namespace Exiv2;

using ::testing::Return;



class ValueTest_789 : public ::testing::Test {

protected:

    Value value;

};



TEST_F(ValueTest_789, ToString_ReturnsEmptyString_789) {

    EXPECT_EQ(value.toString(0), "");

}



TEST_F(ValueTest_789, ToString_IgnoredParameter_789) {

    std::string result1 = value.toString(0);

    std::string result2 = value.toString(42);



    EXPECT_EQ(result1, result2);

}



TEST_F(ValueTest_789, ToString_ConsistentOutput_789) {

    std::string expected = value.toString();

    for (size_t i = 0; i < 10; ++i) {

        EXPECT_EQ(value.toString(i), expected);

    }

}

```


