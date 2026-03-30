#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"
#include "exiv2/error.hpp"

namespace Exiv2 {
namespace Internal {

// Mock for IoWrapper
class MockIoWrapper : public IoWrapper {
public:
    MockIoWrapper(BasicIo& io, const byte* pHeader, size_t size, OffsetWriter* pow)
        : IoWrapper(io, pHeader, size, pow) {}

    MOCK_METHOD(size_t, write, (const byte* pData, size_t wcount), (override));
    MOCK_METHOD(int, putb, (byte data), (override));
    MOCK_METHOD(void, setTarget, (int id, size_t target), (override));
};

// Test fixture
class TiffDirectoryTest : public ::testing::Test {
protected:
    BasicIo mockIo;
    OffsetWriter* mockWriter;
    MockIoWrapper mockIoWrapper;
    TiffDirectory tiffDir{0x1001, 0, false};  // Sample tag and IfdId

    TiffDirectoryTest() : mockIoWrapper(mockIo, nullptr, 0, mockWriter) {}
};

// Normal operation test case
TEST_F(TiffDirectoryTest, DoWriteImage_NormalOperation_383) {
    // Arrange
    MockIoWrapper mockIoWrapper(mockIo, nullptr, 0, mockWriter);
    EXPECT_CALL(mockIoWrapper, write(testing::_, testing::_))
        .WillOnce(testing::Return(10));

    // Act
    size_t len = tiffDir.doWriteImage(mockIoWrapper, ByteOrder::bigEndian);

    // Assert
    EXPECT_EQ(len, 10);
}

// Test case for handling multiple sub-IFD image data tags
TEST_F(TiffDirectoryTest, DoWriteImage_MultipleSubIfdTags_383) {
    // Arrange
    MockIoWrapper mockIoWrapper(mockIo, nullptr, 0, mockWriter);
    tiffDir.addChild(std::make_shared<TiffComponent>(0x014a, 0));  // Adding sub-IFD tag
    tiffDir.addChild(std::make_shared<TiffComponent>(0x014a, 0));  // Another sub-IFD tag

    EXPECT_CALL(mockIoWrapper, write(testing::_, testing::_))
        .Times(2)
        .WillRepeatedly(testing::Return(10));

    // Act
    size_t len = tiffDir.doWriteImage(mockIoWrapper, ByteOrder::bigEndian);

    // Assert
    EXPECT_EQ(len, 20);  // Should include two writes
}

// Boundary condition for empty components
TEST_F(TiffDirectoryTest, DoWriteImage_EmptyComponents_384) {
    // Arrange
    MockIoWrapper mockIoWrapper(mockIo, nullptr, 0, mockWriter);
    tiffDir.clearComponents();  // Ensure no components are present

    // Act
    size_t len = tiffDir.doWriteImage(mockIoWrapper, ByteOrder::bigEndian);

    // Assert
    EXPECT_EQ(len, 0);  // No components to write
}

// Exceptional case: if write fails for IoWrapper
TEST_F(TiffDirectoryTest, DoWriteImage_WriteFails_385) {
    // Arrange
    MockIoWrapper mockIoWrapper(mockIo, nullptr, 0, mockWriter);
    EXPECT_CALL(mockIoWrapper, write(testing::_, testing::_))
        .WillOnce(testing::Throw(std::runtime_error("Write failed")));

    // Act & Assert
    EXPECT_THROW(tiffDir.doWriteImage(mockIoWrapper, ByteOrder::bigEndian), std::runtime_error);
}

// Verify external interactions with IoWrapper
TEST_F(TiffDirectoryTest, DoWriteImage_VerifyInteractionWithIoWrapper_386) {
    // Arrange
    MockIoWrapper mockIoWrapper(mockIo, nullptr, 0, mockWriter);
    EXPECT_CALL(mockIoWrapper, write(testing::_, testing::_))
        .Times(2)
        .WillRepeatedly(testing::Return(10));

    // Act
    size_t len = tiffDir.doWriteImage(mockIoWrapper, ByteOrder::bigEndian);

    // Assert
    EXPECT_EQ(len, 20);  // Verify that the IoWrapper's write method was called twice
    // Additional checks could be performed for parameter values if needed
}

}  // namespace Internal
}  // namespace Exiv2