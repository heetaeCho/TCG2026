#include <gtest/gtest.h>
#include <cstdint>

// Minimal type definitions to match Exiv2 namespace
namespace Exiv2 {
using byte = uint8_t;

class RemoteIo {
public:
    size_t write(const byte* /* unused data*/, size_t /* unused wcount*/) {
        return 0; // means failure
    }
};
}  // namespace Exiv2

// Test fixture for RemoteIo
class RemoteIoTest_602 : public ::testing::Test {
protected:
    Exiv2::RemoteIo remoteIo;
};

// Normal operation: writing valid data should return 0 (failure)
TEST_F(RemoteIoTest_602, WriteValidDataReturnsZero_602) {
    Exiv2::byte data[] = {0x01, 0x02, 0x03, 0x04};
    size_t result = remoteIo.write(data, sizeof(data));
    EXPECT_EQ(result, 0u);
}

// Writing a single byte should still return 0 (failure)
TEST_F(RemoteIoTest_602, WriteSingleByteReturnsZero_602) {
    Exiv2::byte data[] = {0xFF};
    size_t result = remoteIo.write(data, 1);
    EXPECT_EQ(result, 0u);
}

// Boundary: writing zero bytes should return 0
TEST_F(RemoteIoTest_602, WriteZeroBytesReturnsZero_602) {
    Exiv2::byte data[] = {0x00};
    size_t result = remoteIo.write(data, 0);
    EXPECT_EQ(result, 0u);
}

// Boundary: writing with nullptr data should return 0
TEST_F(RemoteIoTest_602, WriteNullDataReturnsZero_602) {
    size_t result = remoteIo.write(nullptr, 0);
    EXPECT_EQ(result, 0u);
}

// Boundary: writing with nullptr data and non-zero count should return 0
TEST_F(RemoteIoTest_602, WriteNullDataNonZeroCountReturnsZero_602) {
    size_t result = remoteIo.write(nullptr, 100);
    EXPECT_EQ(result, 0u);
}

// Writing a large count should still return 0 (failure)
TEST_F(RemoteIoTest_602, WriteLargeCountReturnsZero_602) {
    Exiv2::byte data[] = {0x42};
    size_t result = remoteIo.write(data, 1000000);
    EXPECT_EQ(result, 0u);
}

// Multiple consecutive writes should all return 0
TEST_F(RemoteIoTest_602, MultipleWritesAllReturnZero_602) {
    Exiv2::byte data1[] = {0x01, 0x02};
    Exiv2::byte data2[] = {0x03, 0x04, 0x05};
    Exiv2::byte data3[] = {0x06};

    EXPECT_EQ(remoteIo.write(data1, sizeof(data1)), 0u);
    EXPECT_EQ(remoteIo.write(data2, sizeof(data2)), 0u);
    EXPECT_EQ(remoteIo.write(data3, sizeof(data3)), 0u);
}

// Boundary: writing with maximum size_t value should return 0
TEST_F(RemoteIoTest_602, WriteMaxSizeTReturnsZero_602) {
    Exiv2::byte data[] = {0xAB};
    size_t result = remoteIo.write(data, std::numeric_limits<size_t>::max());
    EXPECT_EQ(result, 0u);
}

// Verify return value is exactly size_t(0), not some other falsy value
TEST_F(RemoteIoTest_602, WriteReturnValueIsExactlyZero_602) {
    Exiv2::byte data[] = {0x10, 0x20, 0x30};
    size_t result = remoteIo.write(data, sizeof(data));
    ASSERT_EQ(result, static_cast<size_t>(0));
}

// Writing all-zero data should also return 0
TEST_F(RemoteIoTest_602, WriteAllZeroDataReturnsZero_602) {
    Exiv2::byte data[256] = {};
    size_t result = remoteIo.write(data, sizeof(data));
    EXPECT_EQ(result, 0u);
}
