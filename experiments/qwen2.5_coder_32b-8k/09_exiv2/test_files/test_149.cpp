#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <string>



using namespace Exiv2;



// Fixture for ValueType tests

template<typename T>

class ValueTypeTest : public ::testing::Test {

protected:

    ValueType<T> value_type;

};



using TestTypes = ::testing::Types<int, double, float, Rational, URational>;

TYPED_TEST_SUITE(ValueTypeTest, TestTypes);



TYPED_TEST(ValueTypeTest_149, ReadValidString_149) {

    std::string buf = "1 2 3";

    EXPECT_EQ(this->value_type.read(buf), 0);

    EXPECT_EQ(this->value_type.count(), 3U);

}



TYPED_TEST(ValueTypeTest_149, ReadEmptyString_149) {

    std::string buf = "";

    EXPECT_EQ(this->value_type.read(buf), 0);

    EXPECT_EQ(this->value_type.count(), 0U);

}



TYPED_TEST(ValueTypeTest_149, ReadInvalidString_149) {

    std::string buf = "1 2 abc";

    EXPECT_EQ(this->value_type.read(buf), 1);

    EXPECT_EQ(this->value_type.count(), 2U); // Successfully read '1' and '2'

}



TYPED_TEST(ValueTypeTest_149, ReadSingleValueString_149) {

    std::string buf = "42";

    EXPECT_EQ(this->value_type.read(buf), 0);

    EXPECT_EQ(this->value_type.count(), 1U);

}



TYPED_TEST(ValueTypeTest_149, ReadLargeNumberString_149) {

    std::string large_number = std::to_string(LARGE_INT); // Assuming LARGE_INT is defined in exiv2/value.hpp

    std::string buf = large_number;

    EXPECT_EQ(this->value_type.read(buf), 0);

    EXPECT_EQ(this->value_type.count(), 1U);

}



TYPED_TEST(ValueTypeTest_149, ReadMultipleLargeNumbersString_149) {

    std::string large_number = std::to_string(LARGE_INT); // Assuming LARGE_INT is defined in exiv2/value.hpp

    std::string buf = large_number + " " + large_number;

    EXPECT_EQ(this->value_type.read(buf), 0);

    EXPECT_EQ(this->value_type.count(), 2U);

}



TYPED_TEST(ValueTypeTest_149, ReadStringWithExtraWhitespace_149) {

    std::string buf = "  1  2  3  ";

    EXPECT_EQ(this->value_type.read(buf), 0);

    EXPECT_EQ(this->value_type.count(), 3U);

}



TYPED_TEST(ValueTypeTest_149, ReadStringWithTrailingNonNumericCharacters_149) {

    std::string buf = "1 2 3 abc";

    EXPECT_EQ(this->value_type.read(buf), 1);

    EXPECT_EQ(this->value_type.count(), 3U); // Successfully read '1', '2', and '3'

}
