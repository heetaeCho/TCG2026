#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"

namespace Exiv2 {
namespace Internal {

// Mock for IoWrapper, used for testing write-related methods
class MockIoWrapper : public IoWrapper {
public:
    MOCK_METHOD(size_t, write, (const byte* buffer, size_t size), (override));
};

// Test Fixture for TiffComponent
class TiffComponentTest : public ::testing::Test {
protected:
    TiffComponentTest() : tiffComponent(100, 1) {}  // Arbitrary tag and group for testing

    TiffComponent tiffComponent;
};

// TEST_ID 397
TEST_F(TiffComponentTest, SizeData_ReturnsCorrectValue_397) {
    // Arrange
    size_t expectedSizeData = 1024; // Example expected size for data
    // Mock the doSizeData to return the expected value
    EXPECT_CALL(tiffComponent, doSizeData()).WillOnce(::testing::Return(expectedSizeData));

    // Act
    size_t sizeData = tiffComponent.sizeData();

    // Assert
    EXPECT_EQ(sizeData, expectedSizeData);
}

// TEST_ID 398
TEST_F(TiffComponentTest, Count_ReturnsCorrectValue_398) {
    // Arrange
    size_t expectedCount = 10; // Example expected count
    EXPECT_CALL(tiffComponent, doCount()).WillOnce(::testing::Return(expectedCount));

    // Act
    size_t count = tiffComponent.count();

    // Assert
    EXPECT_EQ(count, expectedCount);
}

// TEST_ID 399
TEST_F(TiffComponentTest, WriteData_CallsWriteMethod_399) {
    // Arrange
    MockIoWrapper mockIoWrapper;
    size_t offset = 0, valueIdx = 0, dataIdx = 0, imageIdx = 0;
    ByteOrder byteOrder = ByteOrder::littleEndian;
    size_t expectedSize = 128;  // Example expected write size

    // Expect the write method to be called with the specific arguments
    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_))
        .WillOnce(::testing::Return(expectedSize));

    // Act
    size_t writeSize = tiffComponent.writeData(mockIoWrapper, byteOrder, offset, dataIdx, imageIdx);

    // Assert
    EXPECT_EQ(writeSize, expectedSize);
}

// TEST_ID 400
TEST_F(TiffComponentTest, AddChild_ReturnsCorrectComponent_400) {
    // Arrange
    auto childComponent = std::make_shared<TiffComponent>(200, 2);
    EXPECT_CALL(tiffComponent, doAddChild(::testing::_))
        .WillOnce(::testing::Return(childComponent.get()));

    // Act
    auto addedChild = tiffComponent.addChild(childComponent);

    // Assert
    EXPECT_EQ(addedChild, childComponent.get());
}

// TEST_ID 401
TEST_F(TiffComponentTest, Clone_ReturnsValidClone_401) {
    // Act
    auto clone = tiffComponent.clone();

    // Assert
    EXPECT_NE(clone, nullptr);
    EXPECT_EQ(clone->tag(), tiffComponent.tag());
    EXPECT_EQ(clone->group(), tiffComponent.group());
}

// TEST_ID 402
TEST_F(TiffComponentTest, Size_ReturnsCorrectValue_402) {
    // Arrange
    size_t expectedSize = 512; // Example expected size
    EXPECT_CALL(tiffComponent, doSize()).WillOnce(::testing::Return(expectedSize));

    // Act
    size_t size = tiffComponent.size();

    // Assert
    EXPECT_EQ(size, expectedSize);
}

// TEST_ID 403
TEST_F(TiffComponentTest, AddNext_ReturnsCorrectComponent_403) {
    // Arrange
    auto nextComponent = std::make_unique<TiffComponent>(300, 3);
    EXPECT_CALL(tiffComponent, doAddNext(::testing::_))
        .WillOnce(::testing::Return(nextComponent.get()));

    // Act
    auto addedNext = tiffComponent.addNext(std::move(nextComponent));

    // Assert
    EXPECT_EQ(addedNext, nextComponent.get());
}

// TEST_ID 404
TEST_F(TiffComponentTest, WriteImage_CallsWriteMethod_404) {
    // Arrange
    MockIoWrapper mockIoWrapper;
    ByteOrder byteOrder = ByteOrder::littleEndian;
    size_t expectedSize = 256;  // Example expected write size
    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_))
        .WillOnce(::testing::Return(expectedSize));

    // Act
    size_t writeSize = tiffComponent.writeImage(mockIoWrapper, byteOrder);

    // Assert
    EXPECT_EQ(writeSize, expectedSize);
}

} // namespace Internal
} // namespace Exiv2