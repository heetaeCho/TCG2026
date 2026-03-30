#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "samsungmn_int.cpp"  // Assuming this is how the file is included in your project



using namespace Exiv2::Internal;



class PrintPwColorTest_1723 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value value;

};



TEST_F(PrintPwColorTest_1723, NormalOperationWithValueTypeUnsignedShortAndValue65535_1723) {

    value = Value::create(Exiv2::unsignedShort);

    value.setValue(uint16_t(65535));

    printPwColor(os, value, nullptr);

    EXPECT_EQ(os.str(), "Neutral");

}



TEST_F(PrintPwColorTest_1723, NormalOperationWithValueTypeUnsignedShortAndValueLessThan65535_1723) {

    value = Value::create(Exiv2::unsignedShort);

    value.setValue(uint16_t(100));

    printPwColor(os, value, nullptr);

    EXPECT_EQ(os.str(), "100");

}



TEST_F(PrintPwColorTest_1723, BoundaryConditionWithValueTypeUnsignedShortAndValueZero_1723) {

    value = Value::create(Exiv2::unsignedShort);

    value.setValue(uint16_t(0));

    printPwColor(os, value, nullptr);

    EXPECT_EQ(os.str(), "0");

}



TEST_F(PrintPwColorTest_1723, BoundaryConditionWithValueTypeUnsignedShortAndMaxValue_1723) {

    value = Value::create(Exiv2::unsignedShort);

    value.setValue(uint16_t(65535));

    printPwColor(os, value, nullptr);

    EXPECT_EQ(os.str(), "Neutral");

}



TEST_F(PrintPwColorTest_1723, ExceptionalCaseWithCountNotEqualToOne_1723) {

    value = Value::create(Exiv2::unsignedShort);

    value.setValue(uint16_t(65535));

    value.copy(Value::create(Exiv2::unsignedShort));  // This should increase the count to more than one

    printPwColor(os, value, nullptr);

    EXPECT_EQ(os.str(), "65535");

}



TEST_F(PrintPwColorTest_1723, ExceptionalCaseWithDifferentValueType_1723) {

    value = Value::create(Exiv2::unsignedLong);  // Different type

    value.setValue(uint32_t(65535));

    printPwColor(os, value, nullptr);

    EXPECT_EQ(os.str(), "65535");

}
