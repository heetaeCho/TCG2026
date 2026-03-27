#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tags_int.cpp"

#include "exiv2/value.hpp"

#include "exiv2/exif.hpp"

#include "stringformat.h"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Print0x9206Test_1403 : public ::testing::Test {

protected:

    Value value;

    std::ostringstream os;

};



TEST_F(Print0x9206Test_1403, DistanceZero_1403) {

    Rational rational(0, 1);

    value.setValue(&rational, 1);

    print0x9206(os, value, nullptr);

    EXPECT_EQ(os.str(), "Unknown");

}



TEST_F(Print0x9206Test_1403, DistanceMaxUint32_1403) {

    Rational rational(std::numeric_limits<uint32_t>::max(), 1);

    value.setValue(&rational, 1);

    print0x9206(os, value, nullptr);

    EXPECT_EQ(os.str(), "Infinity");

}



TEST_F(Print0x9206Test_1403, DistanceFinite_1403) {

    Rational rational(100, 5);

    value.setValue(&rational, 1);

    print0x9206(os, value, nullptr);

    EXPECT_EQ(os.str(), "20.00 m");

}



TEST_F(Print0x9206Test_1403, DistanceSecondZero_1403) {

    Rational rational(50, 0);

    value.setValue(&rational, 1);

    print0x9206(os, value, nullptr);

    EXPECT_EQ(os.str(), "(50/0)");

}



TEST_F(Print0x9206Test_1403, DistanceNonTrivial_1403) {

    Rational rational(12345, 6789);

    value.setValue(&rational, 1);

    print0x9206(os, value, nullptr);

    EXPECT_EQ(os.str(), "1.82 m");

}
