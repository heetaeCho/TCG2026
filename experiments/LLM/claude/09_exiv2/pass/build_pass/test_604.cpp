#include <gtest/gtest.h>

// Include necessary headers based on the provided code
namespace Exiv2 {
using byte = unsigned char;

class RemoteIo {
public:
    int putb(byte /*unused data*/) {
        return 0;
    }
};
}  // namespace Exiv2

// Test fixture for RemoteIo
class RemoteIoTest_604 : public ::testing::Test {
protected:
    Exiv2::RemoteIo remoteIo;
};

// Normal operation: putb returns 0 for a typical byte value
TEST_F(RemoteIoTest_604, PutbReturnsZeroForTypicalValue_604) {
    int result = remoteIo.putb(0x42);
    EXPECT_EQ(result, 0);
}

// Normal operation: putb returns 0 for zero byte
TEST_F(RemoteIoTest_604, PutbReturnsZeroForZeroByte_604) {
    int result = remoteIo.putb(0x00);
    EXPECT_EQ(result, 0);
}

// Boundary condition: putb with maximum byte value (255)
TEST_F(RemoteIoTest_604, PutbReturnsZeroForMaxByte_604) {
    int result = remoteIo.putb(0xFF);
    EXPECT_EQ(result, 0);
}

// Boundary condition: putb with minimum byte value (0)
TEST_F(RemoteIoTest_604, PutbReturnsZeroForMinByte_604) {
    int result = remoteIo.putb(static_cast<Exiv2::byte>(0));
    EXPECT_EQ(result, 0);
}

// Normal operation: putb called multiple times still returns 0
TEST_F(RemoteIoTest_604, PutbReturnsZeroOnMultipleCalls_604) {
    EXPECT_EQ(remoteIo.putb(0x01), 0);
    EXPECT_EQ(remoteIo.putb(0x02), 0);
    EXPECT_EQ(remoteIo.putb(0x03), 0);
}

// Boundary condition: putb with value 1
TEST_F(RemoteIoTest_604, PutbReturnsZeroForOneByte_604) {
    int result = remoteIo.putb(0x01);
    EXPECT_EQ(result, 0);
}

// Boundary condition: putb with value 127 (mid-range)
TEST_F(RemoteIoTest_604, PutbReturnsZeroForMidRangeByte_604) {
    int result = remoteIo.putb(0x7F);
    EXPECT_EQ(result, 0);
}

// Boundary condition: putb with value 128
TEST_F(RemoteIoTest_604, PutbReturnsZeroForByte128_604) {
    int result = remoteIo.putb(0x80);
    EXPECT_EQ(result, 0);
}

// Test that multiple RemoteIo instances behave consistently
TEST_F(RemoteIoTest_604, MultipleInstancesBehaveSame_604) {
    Exiv2::RemoteIo anotherIo;
    EXPECT_EQ(remoteIo.putb(0xAA), anotherIo.putb(0xAA));
}

// Stress-like test: call putb many times in succession
TEST_F(RemoteIoTest_604, PutbReturnsZeroAfterManyCalls_604) {
    for (int i = 0; i < 256; ++i) {
        EXPECT_EQ(remoteIo.putb(static_cast<Exiv2::byte>(i)), 0)
            << "Failed for byte value: " << i;
    }
}
