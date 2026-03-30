#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include <memory>



using namespace Exiv2;



class DateValueTest_868 : public ::testing::Test {

protected:

    void SetUp() override {

        dateValue = std::make_unique<DateValue>();

    }



    std::unique_ptr<DateValue> dateValue;

};



TEST_F(DateValueTest_868, SizeReturnsEight_868) {

    EXPECT_EQ(dateValue->size(), 8);

}



TEST_F(DateValueTest_868, CountReturnsOne_868) {

    EXPECT_EQ(dateValue->count(), 1);

}



TEST_F(DateValueTest_868, ReadFromBufferReturnsZeroForValidInput_868) {

    byte buffer[8] = {0};

    EXPECT_EQ(dateValue->read(buffer, 8, littleEndian), 0);

}



TEST_F(DateValueTest_868, ReadFromStringReturnsZeroForValidInput_868) {

    std::string buffer = "2023:10:05";

    EXPECT_EQ(dateValue->read(buffer), 0);

}



TEST_F(DateValueTest_868, ReadFromBufferWithInsufficientLengthFails_868) {

    byte buffer[4] = {0};

    EXPECT_NE(dateValue->read(buffer, 4, littleEndian), 0);

}



TEST_F(DateValueTest_868, CopyToBufferReturnsEightForValidInput_868) {

    byte buffer[8];

    EXPECT_EQ(dateValue->copy(buffer, littleEndian), 8);

}



TEST_F(DateValueTest_868, ToInt64ThrowsForNonZeroIndex_868) {

    EXPECT_THROW(dateValue->toInt64(1), std::out_of_range);

}



TEST_F(DateValueTest_868, ToUint32ThrowsForNonZeroIndex_868) {

    EXPECT_THROW(dateValue->toUint32(1), std::out_of_range);

}



TEST_F(DateValueTest_868, ToFloatReturnsZeroForValidInput_868) {

    EXPECT_EQ(dateValue->toFloat(0), 0.0f);

}



TEST_F(DateValueTest_868, ToRationalThrowsForNonZeroIndex_868) {

    EXPECT_THROW(dateValue->toRational(1), std::out_of_range);



}
