#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Mock for IoWrapper (for mocking external dependencies)
class MockIoWrapper : public IoWrapper {
public:
    MOCK_METHOD(size_t, write, (const uint8_t*, size_t, ByteOrder, size_t, size_t, size_t&), (override));
};

// Test suite for TiffDirectory
class TiffDirectoryTest : public ::testing::Test {
protected:
    TiffDirectoryTest() : tiffDirectory(1, 2, true) {}
    TiffDirectory tiffDirectory; // TiffDirectory under test
};

// Normal operation: Test for adding a child component
TEST_F(TiffDirectoryTest, AddChild_AddsTiffComponent_327) {
    auto mockComponent = std::make_shared<TiffComponent>(1, 2);
    TiffComponent* addedComponent = tiffDirectory.doAddChild(mockComponent);
    ASSERT_EQ(addedComponent, mockComponent.get()) << "Expected the added component to be the same as the mock component";
}

// Boundary condition: Test when no more children can be added (hasNext_ is false)
TEST_F(TiffDirectoryTest, AddChild_NoMoreChildren_328) {
    tiffDirectory = TiffDirectory(1, 2, false);  // hasNext_ is set to false
    auto mockComponent = std::make_shared<TiffComponent>(1, 2);
    TiffComponent* addedComponent = tiffDirectory.doAddChild(mockComponent);
    ASSERT_EQ(addedComponent, mockComponent.get()) << "Expected the added component to be the same as the mock component";
}

// Exceptional case: Test error handling (mocked IoWrapper for write failure)
TEST_F(TiffDirectoryTest, Write_FailureOnWrite_329) {
    MockIoWrapper mockIoWrapper;
    size_t offset = 0;
    size_t valueIdx = 0;
    size_t dataIdx = 0;
    size_t imageIdx = 0;

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(0));  // Simulate failure in writing

    size_t result = tiffDirectory.doWrite(mockIoWrapper, ByteOrder::littleEndian, offset, valueIdx, dataIdx, imageIdx);
    ASSERT_EQ(result, 0) << "Expected the write operation to fail, returning 0 bytes written";
}

// Normal operation: Test for checking the "hasNext" status
TEST_F(TiffDirectoryTest, HasNext_ReturnsTrue_330) {
    ASSERT_TRUE(tiffDirectory.hasNext()) << "Expected hasNext() to return true";
}

// Boundary condition: Test when hasNext_ is false
TEST_F(TiffDirectoryTest, HasNext_ReturnsFalse_331) {
    tiffDirectory = TiffDirectory(1, 2, false);  // hasNext_ set to false
    ASSERT_FALSE(tiffDirectory.hasNext()) << "Expected hasNext() to return false";
}

// Normal operation: Test for cloning a TiffDirectory object
TEST_F(TiffDirectoryTest, Clone_CreatesCopy_332) {
    const TiffDirectory* clonedDirectory = tiffDirectory.doClone();
    ASSERT_NE(clonedDirectory, &tiffDirectory) << "Expected a new TiffDirectory object to be cloned";
    ASSERT_EQ(clonedDirectory->hasNext(), tiffDirectory.hasNext()) << "Expected cloned directory to have the same hasNext value";
}

// Exceptional case: Test error handling during directory entry writing
TEST_F(TiffDirectoryTest, WriteDirEntry_WriteError_333) {
    MockIoWrapper mockIoWrapper;
    TiffComponent* mockComponent = nullptr;
    size_t offset = 0, valueIdx = 0, dataIdx = 0, imageIdx = 0;

    EXPECT_CALL(mockIoWrapper, write(::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_, ::testing::_))
        .WillOnce(::testing::Return(0));  // Simulate write error

    size_t result = TiffDirectory::writeDirEntry(mockIoWrapper, ByteOrder::littleEndian, offset, mockComponent, valueIdx, dataIdx, imageIdx);
    ASSERT_EQ(result, 0) << "Expected writeDirEntry to return 0 on failure";
}