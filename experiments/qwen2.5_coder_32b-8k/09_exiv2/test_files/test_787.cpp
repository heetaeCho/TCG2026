#include <gtest/gtest.h>

#include "value.cpp"



using namespace Exiv2;



class ValueTest_787 : public ::testing::Test {

protected:

    Value value;

};



TEST_F(ValueTest_787, SetDataAreaWithNullBuffer_787) {

    const byte* buf = nullptr;

    size_t len = 10;

    int result = value.setDataArea(buf, len);

    EXPECT_EQ(result, -1);

}



TEST_F(ValueTest_787, SetDataAreaWithZeroLength_787) {

    const byte* buf = reinterpret_cast<const byte*>("dummy");

    size_t len = 0;

    int result = value.setDataArea(buf, len);

    EXPECT_EQ(result, -1);

}



TEST_F(ValueTest_787, SetDataAreaWithNormalBufferAndLength_787) {

    const byte* buf = reinterpret_cast<const byte*>("dummy");

    size_t len = 5;

    int result = value.setDataArea(buf, len);

    EXPECT_EQ(result, -1);

}



TEST_F(ValueTest_787, SetDataAreaWithLargeLength_787) {

    const byte* buf = reinterpret_cast<const byte*>("dummy");

    size_t len = std::numeric_limits<size_t>::max();

    int result = value.setDataArea(buf, len);

    EXPECT_EQ(result, -1);

}
