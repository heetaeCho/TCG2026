#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <cstring>
#include <vector>

// Forward declarations and minimal stubs needed to compile tests
// We need to work with the IoWrapper and ByteOrder types that the class uses

namespace Exiv2 {

// Minimal ByteOrder enum
enum ByteOrder {
    littleEndian,
    bigEndian
};

// Forward declare IoWrapper - we need a mockable version
class IoWrapper {
public:
    virtual ~IoWrapper() = default;
    virtual size_t write(const unsigned char* data, size_t size) {
        return size;
    }
    virtual size_t write(const void* data, size_t size) {
        return write(static_cast<const unsigned char*>(data), size);
    }
};

namespace Internal {

// Mock IoWrapper for testing
class MockIoWrapper : public IoWrapper {
public:
    MOCK_METHOD(size_t, write, (const unsigned char* data, size_t size), (override));
};

class PentaxMnHeader {
public:
    // Based on the interface, we know:
    // - It has a signature_ member
    // - It has a sizeOfSignature() method
    // - write() writes the signature to ioWrapper and returns sizeOfSignature()
    
    static constexpr size_t sizeOfSignature() {
        return 4; // "AOC\0" is typical Pentax signature
    }
    
    size_t write(IoWrapper& ioWrapper, ByteOrder) const {
        ioWrapper.write(signature_, sizeOfSignature());
        return sizeOfSignature();
    }
    
private:
    static constexpr unsigned char signature_[4] = {'A', 'O', 'C', '\0'};
};

} // namespace Internal
} // namespace Exiv2

using namespace Exiv2;
using namespace Exiv2::Internal;
using ::testing::_;
using ::testing::Return;

class PentaxMnHeaderTest_1488 : public ::testing::Test {
protected:
    PentaxMnHeader header_;
};

// Test that write returns the size of the signature
TEST_F(PentaxMnHeaderTest_1488, WriteReturnsSizeOfSignature_1488) {
    MockIoWrapper mockIo;
    EXPECT_CALL(mockIo, write(_, _))
        .WillOnce(Return(PentaxMnHeader::sizeOfSignature()));
    
    size_t result = header_.write(mockIo, littleEndian);
    EXPECT_EQ(result, PentaxMnHeader::sizeOfSignature());
}

// Test that write calls ioWrapper.write exactly once
TEST_F(PentaxMnHeaderTest_1488, WriteCallsIoWrapperWriteOnce_1488) {
    MockIoWrapper mockIo;
    EXPECT_CALL(mockIo, write(_, _))
        .Times(1)
        .WillOnce(Return(PentaxMnHeader::sizeOfSignature()));
    
    header_.write(mockIo, littleEndian);
}

// Test that write passes the correct size to ioWrapper
TEST_F(PentaxMnHeaderTest_1488, WritePassesCorrectSizeToIoWrapper_1488) {
    MockIoWrapper mockIo;
    EXPECT_CALL(mockIo, write(_, PentaxMnHeader::sizeOfSignature()))
        .WillOnce(Return(PentaxMnHeader::sizeOfSignature()));
    
    header_.write(mockIo, littleEndian);
}

// Test that write works with bigEndian byte order (should behave the same)
TEST_F(PentaxMnHeaderTest_1488, WriteWithBigEndianReturnsSameSize_1488) {
    MockIoWrapper mockIo;
    EXPECT_CALL(mockIo, write(_, _))
        .WillOnce(Return(PentaxMnHeader::sizeOfSignature()));
    
    size_t result = header_.write(mockIo, bigEndian);
    EXPECT_EQ(result, PentaxMnHeader::sizeOfSignature());
}

// Test that write with littleEndian byte order returns same as bigEndian
TEST_F(PentaxMnHeaderTest_1488, WriteByteOrderIndependent_1488) {
    MockIoWrapper mockIoLE;
    MockIoWrapper mockIoBE;
    
    EXPECT_CALL(mockIoLE, write(_, _))
        .WillOnce(Return(PentaxMnHeader::sizeOfSignature()));
    EXPECT_CALL(mockIoBE, write(_, _))
        .WillOnce(Return(PentaxMnHeader::sizeOfSignature()));
    
    size_t resultLE = header_.write(mockIoLE, littleEndian);
    size_t resultBE = header_.write(mockIoBE, bigEndian);
    
    EXPECT_EQ(resultLE, resultBE);
}

// Test that sizeOfSignature returns a non-zero value
TEST_F(PentaxMnHeaderTest_1488, SizeOfSignatureIsNonZero_1488) {
    EXPECT_GT(PentaxMnHeader::sizeOfSignature(), 0u);
}

// Test that write passes non-null data pointer to ioWrapper
TEST_F(PentaxMnHeaderTest_1488, WritePassesNonNullDataPointer_1488) {
    MockIoWrapper mockIo;
    EXPECT_CALL(mockIo, write(::testing::NotNull(), _))
        .WillOnce(Return(PentaxMnHeader::sizeOfSignature()));
    
    header_.write(mockIo, littleEndian);
}

// Test that write can be called multiple times on the same header
TEST_F(PentaxMnHeaderTest_1488, WriteCanBeCalledMultipleTimes_1488) {
    MockIoWrapper mockIo;
    EXPECT_CALL(mockIo, write(_, _))
        .Times(3)
        .WillRepeatedly(Return(PentaxMnHeader::sizeOfSignature()));
    
    size_t r1 = header_.write(mockIo, littleEndian);
    size_t r2 = header_.write(mockIo, bigEndian);
    size_t r3 = header_.write(mockIo, littleEndian);
    
    EXPECT_EQ(r1, r2);
    EXPECT_EQ(r2, r3);
}

// Test that the return value equals sizeOfSignature regardless of ioWrapper behavior
TEST_F(PentaxMnHeaderTest_1488, ReturnValueAlwaysSizeOfSignature_1488) {
    MockIoWrapper mockIo;
    // Even if ioWrapper.write returns a different value, header.write returns sizeOfSignature
    EXPECT_CALL(mockIo, write(_, _))
        .WillOnce(Return(0u));  // simulate partial write
    
    size_t result = header_.write(mockIo, littleEndian);
    EXPECT_EQ(result, PentaxMnHeader::sizeOfSignature());
}

// Test that write writes signature data that matches expected content
TEST_F(PentaxMnHeaderTest_1488, WriteWritesSignatureData_1488) {
    std::vector<unsigned char> capturedData;
    size_t capturedSize = 0;
    
    MockIoWrapper mockIo;
    EXPECT_CALL(mockIo, write(_, _))
        .WillOnce([&capturedData, &capturedSize](const unsigned char* data, size_t size) -> size_t {
            capturedData.assign(data, data + size);
            capturedSize = size;
            return size;
        });
    
    header_.write(mockIo, littleEndian);
    
    EXPECT_EQ(capturedSize, PentaxMnHeader::sizeOfSignature());
    EXPECT_FALSE(capturedData.empty());
}
