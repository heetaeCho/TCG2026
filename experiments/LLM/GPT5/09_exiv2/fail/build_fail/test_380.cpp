#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"  // Path to the header containing the TiffSubIfd definition

using namespace Exiv2::Internal;

class IoWrapperMock : public IoWrapper {
public:
    MOCK_METHOD(int, putb, (byte data), (override));
    MOCK_METHOD(size_t, write, (const byte* pData, size_t wcount), (override));
    MOCK_METHOD(void, setTarget, (int id, size_t target), (override));
};

TEST_F(TiffSubIfdTest_380, doWriteData_ValidInput) {
    // Setup
    IoWrapperMock ioWrapperMock;
    ByteOrder byteOrder = ByteOrder::bigEndian;  // Or any other valid ByteOrder
    size_t offset = 100;
    size_t dataIdx = 50;
    size_t imageIdx = 200;

    TiffSubIfd tiffSubIfd(1, IfdId::Image, IfdId::Exif); // Instantiate TiffSubIfd
    // Expectations
    EXPECT_CALL(ioWrapperMock, putb(0x0)).Times(0);  // No padding expected
    EXPECT_CALL(ioWrapperMock, write(::testing::_, ::testing::_)).Times(::testing::AtLeast(1)); // Expect write at least once

    // Act
    size_t len = tiffSubIfd.doWriteData(ioWrapperMock, byteOrder, offset, dataIdx, imageIdx);

    // Assert
    EXPECT_GT(len, 0);  // Ensure len is greater than 0 (valid write)
}

TEST_F(TiffSubIfdTest_380, doWriteData_AlignedWrite) {
    // Setup
    IoWrapperMock ioWrapperMock;
    ByteOrder byteOrder = ByteOrder::bigEndian;
    size_t offset = 100;
    size_t dataIdx = 50;
    size_t imageIdx = 200;

    TiffSubIfd tiffSubIfd(1, IfdId::Image, IfdId::Exif);
    // Expectations
    EXPECT_CALL(ioWrapperMock, putb(0x0)).Times(1);  // Expect one padding byte
    EXPECT_CALL(ioWrapperMock, write(::testing::_, ::testing::_)).Times(::testing::AtLeast(1));

    // Act
    size_t len = tiffSubIfd.doWriteData(ioWrapperMock, byteOrder, offset, dataIdx, imageIdx);

    // Assert
    EXPECT_GT(len, 0);  // Ensure len is greater than 0 (valid write)
}

TEST_F(TiffSubIfdTest_380, doWriteData_EmptyIfds) {
    // Setup
    IoWrapperMock ioWrapperMock;
    ByteOrder byteOrder = ByteOrder::bigEndian;
    size_t offset = 100;
    size_t dataIdx = 50;
    size_t imageIdx = 200;

    TiffSubIfd tiffSubIfd(1, IfdId::Image, IfdId::Exif);
    // Expectations
    EXPECT_CALL(ioWrapperMock, write(::testing::_, ::testing::_)).Times(0); // No writes should happen

    // Act
    size_t len = tiffSubIfd.doWriteData(ioWrapperMock, byteOrder, offset, dataIdx, imageIdx);

    // Assert
    EXPECT_EQ(len, 0);  // No data should be written
}

TEST_F(TiffSubIfdTest_380, doWriteData_ErrorOnWrite) {
    // Setup
    IoWrapperMock ioWrapperMock;
    ByteOrder byteOrder = ByteOrder::bigEndian;
    size_t offset = 100;
    size_t dataIdx = 50;
    size_t imageIdx = 200;

    TiffSubIfd tiffSubIfd(1, IfdId::Image, IfdId::Exif);
    // Expectations
    EXPECT_CALL(ioWrapperMock, write(::testing::_, ::testing::_))
        .WillOnce(::testing::Return(0)); // Simulate error by returning 0

    // Act
    size_t len = tiffSubIfd.doWriteData(ioWrapperMock, byteOrder, offset, dataIdx, imageIdx);

    // Assert
    EXPECT_EQ(len, 0);  // Ensure that no data was written
}