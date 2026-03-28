#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



// Mocking an external collaborator if needed (not required in this case)

// class MockExternalCollaborator {

// public:

//     MOCK_METHOD(void, someMethod, (int), ());

// };



class ValueTest_144 : public ::testing::Test {

protected:

    byte buffer[8]; // Assuming a typical size for Rational data

};



TEST_F(ValueTest_144, ToDataConvertsRationalToBytes_144) {

    Rational rational(3, 2); // Example rational number: 3/2

    ByteOrder byteOrder = littleEndian; // Example byte order



    size_t bytesWritten = toData(buffer, rational, byteOrder);



    EXPECT_EQ(bytesWritten, sizeof(Rational)); // Check if the correct number of bytes were written

}



TEST_F(ValueTest_144, ToDataBoundaryConditionZeroNumerator_144) {

    Rational rational(0, 2); // Zero numerator

    ByteOrder byteOrder = littleEndian;



    size_t bytesWritten = toData(buffer, rational, byteOrder);



    EXPECT_EQ(bytesWritten, sizeof(Rational)); // Check if the correct number of bytes were written

}



TEST_F(ValueTest_144, ToDataBoundaryConditionZeroDenominator_144) {

    Rational rational(3, 0); // Zero denominator (should be handled gracefully)

    ByteOrder byteOrder = littleEndian;



    size_t bytesWritten = toData(buffer, rational, byteOrder);



    EXPECT_EQ(bytesWritten, sizeof(Rational)); // Check if the correct number of bytes were written

}



TEST_F(ValueTest_144, ToDataBoundaryConditionLargeValues_144) {

    Rational rational(0xFFFFFFFF, 0x1); // Large numerator and small denominator

    ByteOrder byteOrder = littleEndian;



    size_t bytesWritten = toData(buffer, rational, byteOrder);



    EXPECT_EQ(bytesWritten, sizeof(Rational)); // Check if the correct number of bytes were written

}



TEST_F(ValueTest_144, ToDataBaseCaseBigEndian_144) {

    Rational rational(3, 2); // Example rational number: 3/2

    ByteOrder byteOrder = bigEndian; // Big endian byte order



    size_t bytesWritten = toData(buffer, rational, byteOrder);



    EXPECT_EQ(bytesWritten, sizeof(Rational)); // Check if the correct number of bytes were written

}



TEST_F(ValueTest_144, ToDataBaseCaseLittleEndian_144) {

    Rational rational(3, 2); // Example rational number: 3/2

    ByteOrder byteOrder = littleEndian; // Little endian byte order



    size_t bytesWritten = toData(buffer, rational, byteOrder);



    EXPECT_EQ(bytesWritten, sizeof(Rational)); // Check if the correct number of bytes were written

}
