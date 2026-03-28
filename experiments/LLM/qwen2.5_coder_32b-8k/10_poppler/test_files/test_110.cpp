#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest : public ::testing::Test {

protected:

    Object objNone;

    Object objInt;

    Object objReal;

    Object objInt64;



    ObjectTest()

        : objNone(objNone),

          objInt(42),

          objReal(3.14),

          objInt64(9223372036854775807LL) {}

};



TEST_F(ObjectTest_110, GetNumWithDefaultValue_ReturnsDefaultValueForNonNumericTypes_110) {

    EXPECT_EQ(objNone.getNumWithDefaultValue(1.0), 1.0);

}



TEST_F(ObjectTest_110, GetNumWithDefaultValue_ReturnsIntValueWhenTypeIsInt_110) {

    EXPECT_EQ(objInt.getNumWithDefaultValue(1.0), 42.0);

}



TEST_F(ObjectTest_110, GetNumWithDefaultValue_ReturnsRealValueWhenTypeIsReal_110) {

    EXPECT_DOUBLE_EQ(objReal.getNumWithDefaultValue(1.0), 3.14);

}



TEST_F(ObjectTest_110, GetNumWithDefaultValue_ReturnsInt64ValueWhenTypeIsInt64_110) {

    EXPECT_DOUBLE_EQ(objInt64.getNumWithDefaultValue(1.0), 9223372036854775807LL);

}



TEST_F(ObjectTest_110, GetNumWithDefaultValue_BoundaryConditionsWithDefaultValues_110) {

    Object objMinInt(-2147483648);

    Object objMaxInt(2147483647);

    Object objMinReal(-std::numeric_limits<double>::max());

    Object objMaxReal(std::numeric_limits<double>::max());



    EXPECT_EQ(objMinInt.getNumWithDefaultValue(0.0), -2147483648.0);

    EXPECT_EQ(objMaxInt.getNumWithDefaultValue(0.0), 2147483647.0);

    EXPECT_DOUBLE_EQ(objMinReal.getNumWithDefaultValue(0.0), -std::numeric_limits<double>::max());

    EXPECT_DOUBLE_EQ(objMaxReal.getNumWithDefaultValue(0.0), std::numeric_limits<double>::max());

}
