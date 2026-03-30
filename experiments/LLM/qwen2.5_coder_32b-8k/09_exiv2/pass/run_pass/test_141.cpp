#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



namespace {



using namespace Exiv2;



class URationalTestData {

public:

    URational value;

    ByteOrder byteOrder;

    size_t expectedSize;

    byte buffer[10]; // Assuming a reasonable buffer size for the test



    URationalTestData(URational val, ByteOrder bo, size_t expSize)

        : value(val), byteOrder(bo), expectedSize(expSize) {}

};



class ToDataTest_141 : public ::testing::TestWithParam<URationalTestData> {

protected:

    void SetUp() override {

        // Initialize buffer to zero or any known state if necessary

        memset(param.buffer, 0, sizeof(param.buffer));

    }



    URationalTestData param = GetParam();

};



TEST_P(ToDataTest_141, NormalOperation_141) {

    size_t resultSize = toData(param.buffer, param.value, param.byteOrder);

    EXPECT_EQ(resultSize, param.expectedSize);

}



INSTANTIATE_TEST_SUITE_P(URationalValues_141, ToDataTest_141,

    ::testing::Values(

        URationalTestData({1, 2}, littleEndian, 8), // Simple fraction

        URationalTestData({0, 1}, bigEndian, 8),   // Zero numerator

        URationalTestData({3, 0}, littleEndian, 8)  // Zero denominator (should handle gracefully)

    )

);



TEST(ToDataTest_141, BoundaryConditions_141) {

    byte buffer[8];

    URational zeroValue = {0, 0};

    size_t resultSize = toData(buffer, zeroValue, littleEndian);

    EXPECT_EQ(resultSize, 8); // Assuming zero rational still takes up the same space



    URational maxValues = {(uint32_t)-1, (uint32_t)-1};

    resultSize = toData(buffer, maxValues, bigEndian);

    EXPECT_EQ(resultSize, 8); // Max values should also fit within expected size

}



TEST(ToDataTest_141, ExceptionalCases_141) {

    byte buffer[8];

    URational invalidValue = {1, 0}; // Invalid rational (division by zero)

    EXPECT_NO_THROW(toData(buffer, invalidValue, littleEndian)); // Should not throw exception

}



} // namespace
