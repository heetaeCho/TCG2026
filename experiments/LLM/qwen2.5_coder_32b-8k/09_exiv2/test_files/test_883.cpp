#include <gtest/gtest.h>

#include <climits>

#include <cstdint>

#include <Exiv2/value.hpp>



namespace {



class TimeValueTest_883 : public ::testing::Test {

protected:

    Exiv2::TimeValue timeValue;

};



TEST_F(TimeValueTest_883, ToUint32_ReturnsZeroForNegativeInt64_883) {

    // Arrange

    int64_t negativeValue = -1;



    // Act & Assert

    EXPECT_EQ(timeValue.toUint32(negativeValue), 0u);

}



TEST_F(TimeValueTest_883, ToUint32_ReturnsMaxUint32ForOverflowInt64_883) {

    // Arrange

    int64_t overflowValue = static_cast<int64_t>(std::numeric_limits<uint32_t>::max()) + 1;



    // Act & Assert

    EXPECT_EQ(timeValue.toUint32(overflowValue), std::numeric_limits<uint32_t>::max());

}



TEST_F(TimeValueTest_883, ToUint32_ReturnsCorrectValueForValidInt64_883) {

    // Arrange

    int64_t validValue = 12345;



    // Act & Assert

    EXPECT_EQ(timeValue.toUint32(validValue), static_cast<uint32_t>(validValue));

}



TEST_F(TimeValueTest_883, ToUint32_ReturnsZeroForMaxInt64_883) {

    // Arrange

    int64_t maxValue = std::numeric_limits<int64_t>::max();



    // Act & Assert

    EXPECT_EQ(timeValue.toUint32(maxValue), std::numeric_limits<uint32_t>::max());

}



TEST_F(TimeValueTest_883, ToUint32_ReturnsZeroForMinInt64_883) {

    // Arrange

    int64_t minValue = std::numeric_limits<int64_t>::min();



    // Act & Assert

    EXPECT_EQ(timeValue.toUint32(minValue), 0u);

}



}  // namespace
