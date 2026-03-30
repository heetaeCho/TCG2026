#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock IoWrapper class to simulate external collaborator

class MockIoWrapper {

public:

    MOCK_METHOD(size_t, write, (const uint8_t*, size_t), ());

};



using namespace Exiv2::Internal;



// Test fixture for SigmaMnHeader tests

class SigmaMnHeaderTest_1497 : public ::testing::Test {

protected:

    SigmaMnHeader sigmaMnHeader;

    MockIoWrapper mockIoWrapper;

};



// Test normal operation of write function

TEST_F(SigmaMnHeaderTest_1497, WriteReturnsCorrectSize_1497) {

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_)).WillOnce(::testing::Return(6));

    size_t result = sigmaMnHeader.write(mockIoWrapper, Exiv2::littleEndian);

    EXPECT_EQ(result, 6U); // Assuming sizeOfSignature() returns 6

}



// Test boundary condition: mock write function returning zero

TEST_F(SigmaMnHeaderTest_1497, WriteReturnsZero_1497) {

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_)).WillOnce(::testing::Return(0));

    size_t result = sigmaMnHeader.write(mockIoWrapper, Exiv2::littleEndian);

    EXPECT_EQ(result, 0U);

}



// Test boundary condition: mock write function returning a value less than signature size

TEST_F(SigmaMnHeaderTest_1497, WriteReturnsLessThanSignatureSize_1497) {

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_)).WillOnce(::testing::Return(3));

    size_t result = sigmaMnHeader.write(mockIoWrapper, Exiv2::littleEndian);

    EXPECT_EQ(result, 3U); // Assuming sizeOfSignature() returns 6

}



// Test verification of external interaction: mock write function is called with correct parameters

TEST_F(SigmaMnHeaderTest_1497, WriteCallsMockWithCorrectParameters_1497) {

    const uint8_t* expectedData = sigmaMnHeader.signature1_;

    size_t expectedSize = sigmaMnHeader.sizeOfSignature();

    EXPECT_CALL(mockIoWrapper, write(expectedData, expectedSize)).WillOnce(::testing::Return(expectedSize));

    sigmaMnHeader.write(mockIoWrapper, Exiv2::littleEndian);

}
