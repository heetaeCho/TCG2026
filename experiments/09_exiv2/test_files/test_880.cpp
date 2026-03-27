#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class TimeValueTest_880 : public ::testing::Test {

protected:

    TimeValue timeValue;

};



TEST_F(TimeValueTest_880, SizeReturnsCorrectValue_880) {

    EXPECT_EQ(timeValue.size(), 11U);

}



TEST_F(TimeValueTest_880, CountReturnsCorrectValue_880) {

    EXPECT_EQ(timeValue.count(), 1U); // Assuming count() returns the number of time components, which is typically 1 for a single Time instance.

}



TEST_F(TimeValueTest_880, ReadFromBufferNormalOperation_880) {

    byte buffer[11] = {0};

    EXPECT_EQ(timeValue.read(buffer, sizeof(buffer), littleEndian), 0); // Assuming read returns 0 on success.

}



TEST_F(TimeValueTest_880, ReadFromStringNormalOperation_880) {

    std::string buffer("2023-10-05T14:48:00Z");

    EXPECT_EQ(timeValue.read(buffer), 0); // Assuming read returns 0 on success.

}



TEST_F(TimeValueTest_880, ReadWithInvalidBufferLength_880) {

    byte buffer[1] = {0};

    EXPECT_NE(timeValue.read(buffer, sizeof(buffer), littleEndian), 0); // Assuming read returns non-zero on failure.

}



TEST_F(TimeValueTest_880, CopyToBufferNormalOperation_880) {

    byte buffer[11];

    size_t copiedSize = timeValue.copy(buffer, littleEndian);

    EXPECT_EQ(copiedSize, 11U);

}



TEST_F(TimeValueTest_880, WriteToStreamNormalOperation_880) {

    std::ostringstream os;

    timeValue.write(os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(TimeValueTest_880, ToInt64BoundaryCondition_880) {

    EXPECT_THROW(timeValue.toInt64(0), Error); // Assuming toInt64 throws an error for invalid index.

}



TEST_F(TimeValueTest_880, ToUint32BoundaryCondition_880) {

    EXPECT_THROW(timeValue.toUint32(0), Error); // Assuming toUint32 throws an error for invalid index.

}



TEST_F(TimeValueTest_880, ToFloatBoundaryCondition_880) {

    EXPECT_THROW(timeValue.toFloat(0), Error); // Assuming toFloat throws an error for invalid index.

}



TEST_F(TimeValueTest_880, ToRationalBoundaryCondition_880) {

    EXPECT_THROW(timeValue.toRational(0), Error); // Assuming toRational throws an error for invalid index.

}
