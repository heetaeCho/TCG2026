#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock IoWrapper for testing purposes

class MockIoWrapper {

public:

    MOCK_METHOD(size_t, write, (const uint8_t*, size_t), ());

};



using namespace Exiv2::Internal;



TEST_F(OlympusMnHeaderTest_1440, WriteCallsIoWrapperWriteWithCorrectParameters_1440) {

    MockIoWrapper mockIoWrapper;

    OlympusMnHeader olympusMnHeader;

    uint8_t expectedSignature[2] = { 0x00, 0x01 }; // Example signature

    size_t expectedSize = sizeof(expectedSignature);



    EXPECT_CALL(mockIoWrapper, write(::testing::Eq(expectedSignature), ::testing::Eq(expectedSize)))

        .WillOnce(::testing::Return(expectedSize));



    size_t result = olympusMnHeader.write(mockIoWrapper, littleEndian);

    EXPECT_EQ(result, expectedSize);

}



TEST_F(OlympusMnHeaderTest_1440, WriteReturnsCorrectSize_1440) {

    MockIoWrapper mockIoWrapper;

    OlympusMnHeader olympusMnHeader;

    size_t expectedSize = olympusMnHeader.sizeOfSignature();



    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_))

        .WillOnce(::testing::Return(expectedSize));



    size_t result = olympusMnHeader.write(mockIoWrapper, littleEndian);

    EXPECT_EQ(result, expectedSize);

}



TEST_F(OlympusMnHeaderTest_1440, WriteBoundaryConditionEmptySignature_1440) {

    MockIoWrapper mockIoWrapper;

    OlympusMnHeader olympusMnHeader;



    // Assuming sizeOfSignature() can return 0 for some reason

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::Eq(0)))

        .WillOnce(::testing::Return(0));



    size_t result = olympusMnHeader.write(mockIoWrapper, littleEndian);

    EXPECT_EQ(result, 0);

}



// Assuming there are no observable error cases in the provided interface

```


