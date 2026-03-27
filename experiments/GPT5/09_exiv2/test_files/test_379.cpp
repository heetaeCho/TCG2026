#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IoWrapper.hpp"  // Assuming IoWrapper is defined in this file

namespace Exiv2 { namespace Internal {

// Mock class for IoWrapper to simulate external behavior
class MockIoWrapper : public IoWrapper {
public:
    MOCK_METHOD(void, write, (const void* buf, size_t size), (override));
    MOCK_METHOD(void, putb, (uint8_t byte), (override));
};

class TiffDataEntryTest : public ::testing::Test {
protected:
    TiffDataEntry entry;
    MockIoWrapper ioWrapper;
};

TEST_F(TiffDataEntryTest, doWriteData_EmptyValue_379) {
    // Simulate case where pValue() returns null (empty data)
    EXPECT_CALL(ioWrapper, write(::testing::_, ::testing::_)).Times(0);  // No write call should happen
    EXPECT_CALL(ioWrapper, putb(::testing::_)).Times(0);  // No padding should happen

    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, ByteOrder::littleEndian, 0, 0, imageIdx);

    EXPECT_EQ(result, 0);  // Expected to return 0 since there's no data to write
}

TEST_F(TiffDataEntryTest, doWriteData_AlignedData_380) {
    // Simulate case where pValue() returns data that doesn't require padding
    DataBuf buf(10, 0x01);  // 10-byte buffer, no padding needed
    EXPECT_CALL(ioWrapper, write(::testing::_, 10)).Times(1);  // Expect write with 10 bytes
    EXPECT_CALL(ioWrapper, putb(::testing::_)).Times(0);  // No padding should happen

    // Mock pValue() behavior to return our buffer
    entry.pValue = [&]() -> const DataBuf* { return &buf; };

    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, ByteOrder::littleEndian, 0, 0, imageIdx);

    EXPECT_EQ(result, 10);  // Expected to write 10 bytes and return 10
}

TEST_F(TiffDataEntryTest, doWriteData_NeedPadding_381) {
    // Simulate case where pValue() returns data that requires padding
    DataBuf buf(9, 0x01);  // 9-byte buffer, needs 1-byte padding
    EXPECT_CALL(ioWrapper, write(::testing::_, 9)).Times(1);  // Expect write with 9 bytes
    EXPECT_CALL(ioWrapper, putb(0x0)).Times(1);  // Expect 1-byte padding with 0x0

    // Mock pValue() behavior to return our buffer
    entry.pValue = [&]() -> const DataBuf* { return &buf; };

    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, ByteOrder::littleEndian, 0, 0, imageIdx);

    EXPECT_EQ(result, 10);  // Expected to write 9 bytes + 1-byte padding = 10 bytes
}

TEST_F(TiffDataEntryTest, doWriteData_NoData_382) {
    // Simulate case where pValue() returns a data area that's empty
    DataBuf buf(0, 0x01);  // Empty buffer
    EXPECT_CALL(ioWrapper, write(::testing::_, ::testing::_)).Times(0);  // No write should happen
    EXPECT_CALL(ioWrapper, putb(::testing::_)).Times(0);  // No padding should happen

    // Mock pValue() behavior to return our empty buffer
    entry.pValue = [&]() -> const DataBuf* { return &buf; };

    size_t imageIdx = 0;
    size_t result = entry.doWriteData(ioWrapper, ByteOrder::littleEndian, 0, 0, imageIdx);

    EXPECT_EQ(result, 0);  // Expected to return 0 as there's no data to write
}

} }  // namespace Exiv2::Internal