#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IoWrapper.h"  // Assuming IoWrapper is defined in this header.
#include "Error.h"      // Assuming ErrorCode is defined here.

namespace Exiv2 { namespace Internal {

class MockIoWrapper : public IoWrapper {
public:
    MOCK_METHOD(void, write, (const char* data, size_t size), (override));
    MOCK_METHOD(void, putb, (uint8_t byte), (override));
};

class TiffImageEntryTest_387 : public ::testing::Test {
protected:
    MockIoWrapper ioWrapper;
    TiffImageEntry tiffImageEntry;
};

TEST_F(TiffImageEntryTest_387, DoWriteImageWritesImageData_WhenValueIsNotNull) {
    // Arrange
    // Setup mock behavior and expectations for writing image data
    EXPECT_CALL(ioWrapper, write(::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(ioWrapper, putb(::testing::_)).Times(1);  // Assuming alignment might be necessary

    // Act
    size_t len = tiffImageEntry.doWriteImage(ioWrapper, ByteOrder::bigEndian);

    // Assert
    EXPECT_GT(len, 0); // Ensure that some data was written
}

TEST_F(TiffImageEntryTest_387, DoWriteImageThrowsError_WhenValueIsNull) {
    // Arrange
    // Mock the pValue() to return nullptr to simulate an error condition
    EXPECT_CALL(ioWrapper, write(::testing::_, ::testing::_)).Times(0);
    EXPECT_CALL(ioWrapper, putb(::testing::_)).Times(0);

    // Act & Assert
    EXPECT_THROW(tiffImageEntry.doWriteImage(ioWrapper, ByteOrder::bigEndian), Error);
}

TEST_F(TiffImageEntryTest_387, DoWriteImageWritesStrips_WhenValueIsEmpty) {
    // Arrange
    // Setup mock behavior for writing strip data
    EXPECT_CALL(ioWrapper, write(::testing::_, ::testing::_)).Times(::testing::AtLeast(1));
    EXPECT_CALL(ioWrapper, putb(::testing::_)).Times(::testing::AtLeast(1));  // Alignment check

    // Act
    size_t len = tiffImageEntry.doWriteImage(ioWrapper, ByteOrder::bigEndian);

    // Assert
    EXPECT_EQ(len, 0);  // If there are no strips, the length should be 0
}

TEST_F(TiffImageEntryTest_387, DoWriteImageHandlesAlignmentCorrectly) {
    // Arrange
    size_t expectedLen = 100;
    // Setup mock behavior
    EXPECT_CALL(ioWrapper, write(::testing::_, ::testing::_)).Times(1);
    EXPECT_CALL(ioWrapper, putb(0x0)).Times(1);  // Check that alignment byte is written

    // Act
    size_t len = tiffImageEntry.doWriteImage(ioWrapper, ByteOrder::bigEndian);

    // Assert
    EXPECT_EQ(len, expectedLen + 1);  // Ensure the alignment adds 1 byte
}

} }