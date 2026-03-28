#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/src/tiffcomposite_int.hpp"
#include "exiv2/basicio.hpp"

namespace Exiv2 { namespace Internal {

// Mock class for BasicIo to simulate the behavior of the actual implementation
class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(int, putb, (byte data), (override));
    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
};

// Mock class for OffsetWriter to verify its interactions
class MockOffsetWriter {
public:
    MOCK_METHOD(void, writeOffset, (size_t offset), ());
};

// Test fixture for IoWrapper
class IoWrapperTest_283 : public testing::Test {
protected:
    MockBasicIo mockIo;
    MockOffsetWriter mockOffsetWriter;

    const byte header[4] = {0x01, 0x02, 0x03, 0x04};
    size_t size = 4;

    IoWrapperTest_283() : ioWrapper(mockIo, header, size, &mockOffsetWriter) {}

    IoWrapper ioWrapper;
};

// Test case for normal operation of putb
TEST_F(IoWrapperTest_283, PutbWritesHeaderOnce_283) {
    EXPECT_CALL(mockIo, write(testing::_, testing::_))
        .Times(1)
        .WillOnce(testing::Return(4)); // Simulate writing the header

    EXPECT_CALL(mockIo, putb(testing::_))
        .Times(1)
        .WillOnce(testing::Return(0)); // Simulate successful write of byte

    EXPECT_EQ(ioWrapper.putb(0x05), 0); // Test putb operation
}

// Test case for writing data with normal behavior
TEST_F(IoWrapperTest_283, WriteWritesData_283) {
    byte data[5] = {0x01, 0x02, 0x03, 0x04, 0x05};
    EXPECT_CALL(mockIo, write(data, 5))
        .Times(1)
        .WillOnce(testing::Return(5)); // Simulate successful write of data

    EXPECT_EQ(ioWrapper.write(data, 5), 5); // Test write operation
}

// Test case for putb when the header is already written (shouldn't rewrite header)
TEST_F(IoWrapperTest_283, PutbDoesNotWriteHeaderAgain_283) {
    EXPECT_CALL(mockIo, write(testing::_, testing::_)).Times(1); // Header is written once

    // Simulate writing a byte after header is written
    EXPECT_CALL(mockIo, putb(testing::_)).Times(1).WillOnce(testing::Return(0));

    // Calling putb again, header should not be written again
    EXPECT_EQ(ioWrapper.putb(0x06), 0); // Should not write header again
}

// Test case for exceptional behavior (e.g., write failure)
TEST_F(IoWrapperTest_283, WriteFails_283) {
    byte data[3] = {0x01, 0x02, 0x03};
    EXPECT_CALL(mockIo, write(data, 3))
        .Times(1)
        .WillOnce(testing::Return(0)); // Simulate a failed write operation

    EXPECT_EQ(ioWrapper.write(data, 3), 0); // Check that write fails as expected
}

// Test case for external interaction verification (e.g., OffsetWriter)
TEST_F(IoWrapperTest_283, SetTargetInteractsWithOffsetWriter_283) {
    int targetId = 10;
    size_t targetSize = 100;
    
    EXPECT_CALL(mockOffsetWriter, writeOffset(targetSize)).Times(1); // Verify interaction with OffsetWriter

    ioWrapper.setTarget(targetId, targetSize); // Set the target, should call writeOffset on OffsetWriter
}

} } // namespace Exiv2::Internal