#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



// Fixture for ValueType tests

template <typename T>

class ValueTypeTest : public ::testing::Test {

protected:

    ValueType<T> value_type;

};



using TestTypes = ::testing::Types<int, double, float>;

TYPED_TEST_SUITE(ValueTypeTest, TestTypes);



TYPED_TEST(ValueTypeTest, SetDataAreaWithValidData_175) {

    byte buf[] = {0x01, 0x02, 0x03};

    size_t len = sizeof(buf);

    EXPECT_EQ(this->value_type.setDataArea(buf, len), 0);

}



TYPED_TEST(ValueTypeTest, SetDataAreaWithEmptyData_175) {

    byte buf[] = {};

    size_t len = sizeof(buf);

    EXPECT_EQ(this->value_type.setDataArea(buf, len), 0);

}



TYPED_TEST(ValueTypeTest, SetDataAreaWithLargeData_175) {

    size_t len = 1000000;

    byte* buf = new byte[len];

    for (size_t i = 0; i < len; ++i) {

        buf[i] = static_cast<byte>(i % 256);

    }

    EXPECT_EQ(this->value_type.setDataArea(buf, len), 0);

    delete[] buf;

}



TYPED_TEST(ValueTypeTest, SetDataAreaWithNullBuffer_175) {

    byte* buf = nullptr;

    size_t len = 10;

    EXPECT_EQ(this->value_type.setDataArea(buf, len), 0);

}
