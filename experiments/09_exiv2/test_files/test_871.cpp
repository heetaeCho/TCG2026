#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <limits>



using namespace Exiv2;



class DateValueTest_871 : public ::testing::Test {

protected:

    DateValue dateValue;

};



TEST_F(DateValueTest_871, ToUint32_ReturnsZeroForNegativeInt64_871) {

    // Arrange

    int64_t negativeValue = -1;



    // Act & Assert

    EXPECT_EQ(dateValue.toUint32(negativeValue), 0U);

}



TEST_F(DateValueTest_871, ToUint32_ReturnsZeroForGreaterThanMaxUint32_871) {

    // Arrange

    int64_t maxValue = static_cast<int64_t>(std::numeric_limits<uint32_t>::max()) + 1;



    // Act & Assert

    EXPECT_EQ(dateValue.toUint32(maxValue), 0U);

}



TEST_F(DateValueTest_871, ToUint32_ReturnsCorrectUint32ForValidInt64_871) {

    // Arrange

    int64_t validValue = 12345;



    // Act & Assert

    EXPECT_EQ(dateValue.toUint32(validValue), 12345U);

}



TEST_F(DateValueTest_871, ToUint32_ReturnsMaxUint32ForMaxInt64_871) {

    // Arrange

    int64_t maxValue = std::numeric_limits<uint32_t>::max();



    // Act & Assert

    EXPECT_EQ(dateValue.toUint32(maxValue), std::numeric_limits<uint32_t>::max());

}



TEST_F(DateValueTest_871, ToUint32_ReturnsZeroAndInvalidatesForNegativeInt64_871) {

    // Arrange

    int64_t negativeValue = -1;



    // Act

    dateValue.toUint32(negativeValue);



    // Assert

    EXPECT_EQ(dateValue.ok_, false);

}



TEST_F(DateValueTest_871, ToUint32_ReturnsZeroAndInvalidatesForGreaterThanMaxUint32_871) {

    // Arrange

    int64_t maxValue = static_cast<int64_t>(std::numeric_limits<uint32_t>::max()) + 1;



    // Act

    dateValue.toUint32(maxValue);



    // Assert

    EXPECT_EQ(dateValue.ok_, false);

}



TEST_F(DateValueTest_871, ToUint32_ReturnsValidAndDoesNotInvalidateForValidInt64_871) {

    // Arrange

    int64_t validValue = 12345;



    // Act

    dateValue.toUint32(validValue);



    // Assert

    EXPECT_EQ(dateValue.ok_, true);

}



TEST_F(DateValueTest_871, ToUint32_ReturnsMaxAndDoesNotInvalidateForMaxInt64_871) {

    // Arrange

    int64_t maxValue = std::numeric_limits<uint32_t>::max();



    // Act

    dateValue.toUint32(maxValue);



    // Assert

    EXPECT_EQ(dateValue.ok_, true);

}
