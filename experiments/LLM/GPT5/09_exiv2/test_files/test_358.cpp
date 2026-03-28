#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"

namespace Exiv2 {
namespace Internal {

// Mocking IoWrapper and TiffVisitor as external collaborators
class MockIoWrapper : public IoWrapper {
public:
    MOCK_METHOD(size_t, write, (const void* buffer, size_t size), (override));
    MOCK_METHOD(size_t, read, (void* buffer, size_t size), (override));
};

class MockTiffVisitor : public TiffVisitor {
public:
    MOCK_METHOD(void, visit, (const TiffDirectory& tiffDirectory), (override));
};

// Unit tests for TiffDirectory class

TEST_F(TiffDirectoryTest_358, doCount_ReturnsCorrectComponentCount_358) {
    TiffDirectory tiffDirectory(1, IfdId::ExifIFD, true);
    size_t count = tiffDirectory.doCount();

    // Assuming the components are initialized correctly, assert the count
    ASSERT_EQ(count, 0); // Replace with the actual expected count if initialized differently
}

TEST_F(TiffDirectoryTest_359, hasNext_ReturnsCorrectFlag_359) {
    TiffDirectory tiffDirectory(1, IfdId::ExifIFD, true);
    bool hasNext = tiffDirectory.hasNext();

    // Test when the hasNext_ flag is true
    ASSERT_TRUE(hasNext);
}

TEST_F(TiffDirectoryTest_360, doWrite_CallsWriteMethod_360) {
    MockIoWrapper mockIoWrapper;
    size_t offset = 0;
    size_t valueIdx = 0;
    size_t dataIdx = 0;
    size_t imageIdx = 0;

    TiffDirectory tiffDirectory(1, IfdId::ExifIFD, true);
    
    // Expecting the write function to be called
    EXPECT_CALL(mockIoWrapper, write(testing::_, testing::_)).Times(1);

    // Call the method under test
    size_t bytesWritten = tiffDirectory.doWrite(mockIoWrapper, ByteOrder::BigEndian, offset, valueIdx, dataIdx, imageIdx);

    // Assert that the write method was called and return value is as expected
    ASSERT_GT(bytesWritten, 0);
}

TEST_F(TiffDirectoryTest_361, doAccept_VisitsCorrectVisitor_361) {
    MockTiffVisitor mockVisitor;

    TiffDirectory tiffDirectory(1, IfdId::ExifIFD, true);

    // Expect the visit method to be called once
    EXPECT_CALL(mockVisitor, visit(testing::_)).Times(1);

    // Call the doAccept method with the mock visitor
    tiffDirectory.doAccept(mockVisitor);
}

TEST_F(TiffDirectoryTest_362, doSize_ReturnsCorrectSize_362) {
    TiffDirectory tiffDirectory(1, IfdId::ExifIFD, true);

    // Check that the size is as expected, it might be 0 for an empty directory
    size_t size = tiffDirectory.doSize();
    ASSERT_EQ(size, 0); // Replace with the actual expected size
}

TEST_F(TiffDirectoryTest_363, doWriteData_HandlesDataWrite_363) {
    MockIoWrapper mockIoWrapper;
    size_t offset = 0;
    size_t dataIdx = 0;
    size_t imageIdx = 0;

    TiffDirectory tiffDirectory(1, IfdId::ExifIFD, true);

    // Expect writeData to be called and return non-zero bytes written
    EXPECT_CALL(mockIoWrapper, write(testing::_, testing::_)).Times(1);

    size_t bytesWritten = tiffDirectory.doWriteData(mockIoWrapper, ByteOrder::BigEndian, offset, dataIdx, imageIdx);

    ASSERT_GT(bytesWritten, 0);
}

}  // namespace Internal
}  // namespace Exiv2