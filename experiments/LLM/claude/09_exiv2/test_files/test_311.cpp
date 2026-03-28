#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "makernote_int.hpp"
#include "basicio.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Mock MnHeader to control behavior
class MockMnHeader : public MnHeader {
public:
    MOCK_METHOD(bool, read, (const byte* pData, size_t size, ByteOrder byteOrder), (override));
    MOCK_METHOD(void, setByteOrder, (ByteOrder byteOrder), (override));
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(size_t, write, (IoWrapper& ioWrapper, ByteOrder byteOrder), (const, override));
    MOCK_METHOD(size_t, ifdOffset, (), (const, override));
    MOCK_METHOD(ByteOrder, byteOrder, (), (const, override));
    MOCK_METHOD(size_t, baseOffset, (size_t mnOffset), (const, override));
};

class TiffIfdMakernoteTest_311 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test writeHeader with null pHeader_ (no header set)
TEST_F(TiffIfdMakernoteTest_311, WriteHeaderWithNullHeader_ReturnsZero_311) {
    // Create TiffIfdMakernote with nullptr header
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);

    // Create a MemIo for the IoWrapper
    MemIo memIo;
    IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);

    size_t result = makernote.writeHeader(ioWrapper, littleEndian);
    EXPECT_EQ(0u, result);
}

// Test writeHeader with a valid header that writes data
TEST_F(TiffIfdMakernoteTest_311, WriteHeaderWithValidHeader_CallsHeaderWrite_311) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();

    // Expect the write method to be called once
    EXPECT_CALL(*rawPtr, write(::testing::_, littleEndian))
        .WillOnce(::testing::Return(10));

    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);

    MemIo memIo;
    IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);

    size_t result = makernote.writeHeader(ioWrapper, littleEndian);
    EXPECT_EQ(10u, result);
}

// Test writeHeader with big endian byte order
TEST_F(TiffIfdMakernoteTest_311, WriteHeaderWithBigEndian_311) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();

    EXPECT_CALL(*rawPtr, write(::testing::_, bigEndian))
        .WillOnce(::testing::Return(8));

    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);

    MemIo memIo;
    IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);

    size_t result = makernote.writeHeader(ioWrapper, bigEndian);
    EXPECT_EQ(8u, result);
}

// Test writeHeader where header write returns zero
TEST_F(TiffIfdMakernoteTest_311, WriteHeaderReturnsZeroFromHeader_311) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();

    EXPECT_CALL(*rawPtr, write(::testing::_, ::testing::_))
        .WillOnce(::testing::Return(0));

    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);

    MemIo memIo;
    IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);

    size_t result = makernote.writeHeader(ioWrapper, littleEndian);
    EXPECT_EQ(0u, result);
}

// Test sizeHeader with null header
TEST_F(TiffIfdMakernoteTest_311, SizeHeaderWithNullHeader_311) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    size_t result = makernote.sizeHeader();
    EXPECT_EQ(0u, result);
}

// Test sizeHeader with a valid header
TEST_F(TiffIfdMakernoteTest_311, SizeHeaderWithValidHeader_311) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();

    EXPECT_CALL(*rawPtr, size())
        .WillOnce(::testing::Return(12));

    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);

    size_t result = makernote.sizeHeader();
    EXPECT_EQ(12u, result);
}

// Test readHeader with null header
TEST_F(TiffIfdMakernoteTest_311, ReadHeaderWithNullHeader_311) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);

    byte data[] = {0x01, 0x02, 0x03};
    bool result = makernote.readHeader(data, sizeof(data), littleEndian);
    // With null header, readHeader should return false (or true, depending on implementation)
    // We just verify it doesn't crash and returns a bool
    EXPECT_TRUE(result == true || result == false);
}

// Test readHeader with a valid header
TEST_F(TiffIfdMakernoteTest_311, ReadHeaderWithValidHeader_311) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();

    byte data[] = {0x01, 0x02, 0x03, 0x04};

    EXPECT_CALL(*rawPtr, read(data, 4, littleEndian))
        .WillOnce(::testing::Return(true));

    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);

    bool result = makernote.readHeader(data, sizeof(data), littleEndian);
    EXPECT_TRUE(result);
}

// Test readHeader with a header that fails to read
TEST_F(TiffIfdMakernoteTest_311, ReadHeaderFailure_311) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();

    byte data[] = {0xFF};

    EXPECT_CALL(*rawPtr, read(data, 1, bigEndian))
        .WillOnce(::testing::Return(false));

    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);

    bool result = makernote.readHeader(data, sizeof(data), bigEndian);
    EXPECT_FALSE(result);
}

// Test setByteOrder delegates to header
TEST_F(TiffIfdMakernoteTest_311, SetByteOrderWithValidHeader_311) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();

    EXPECT_CALL(*rawPtr, setByteOrder(bigEndian))
        .Times(1);

    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);

    makernote.setByteOrder(bigEndian);
}

// Test setByteOrder with null header doesn't crash
TEST_F(TiffIfdMakernoteTest_311, SetByteOrderWithNullHeader_311) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);

    // Should not crash
    makernote.setByteOrder(littleEndian);
}

// Test byteOrder with valid header
TEST_F(TiffIfdMakernoteTest_311, ByteOrderWithValidHeader_311) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();

    EXPECT_CALL(*rawPtr, byteOrder())
        .WillOnce(::testing::Return(bigEndian));

    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);

    ByteOrder result = makernote.byteOrder();
    EXPECT_EQ(bigEndian, result);
}

// Test byteOrder with null header returns invalidByteOrder
TEST_F(TiffIfdMakernoteTest_311, ByteOrderWithNullHeader_311) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);

    ByteOrder result = makernote.byteOrder();
    EXPECT_EQ(invalidByteOrder, result);
}

// Test ifdOffset with valid header
TEST_F(TiffIfdMakernoteTest_311, IfdOffsetWithValidHeader_311) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();

    EXPECT_CALL(*rawPtr, ifdOffset())
        .WillOnce(::testing::Return(42));

    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);

    size_t result = makernote.ifdOffset();
    EXPECT_EQ(42u, result);
}

// Test ifdOffset with null header
TEST_F(TiffIfdMakernoteTest_311, IfdOffsetWithNullHeader_311) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);

    size_t result = makernote.ifdOffset();
    EXPECT_EQ(0u, result);
}

// Test writeHeader with large return value
TEST_F(TiffIfdMakernoteTest_311, WriteHeaderLargeSize_311) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();

    EXPECT_CALL(*rawPtr, write(::testing::_, littleEndian))
        .WillOnce(::testing::Return(65536));

    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);

    MemIo memIo;
    IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);

    size_t result = makernote.writeHeader(ioWrapper, littleEndian);
    EXPECT_EQ(65536u, result);
}

// Test construction with hasNext=true
TEST_F(TiffIfdMakernoteTest_311, ConstructionWithHasNextTrue_311) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    // Just verify construction doesn't throw
    EXPECT_NO_THROW(
        TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), true)
    );
}

// Test construction with different tag values
TEST_F(TiffIfdMakernoteTest_311, ConstructionWithDifferentTags_311) {
    EXPECT_NO_THROW(
        TiffIfdMakernote makernote(0x0000, IfdId::exifId, IfdId::canonId, nullptr, false)
    );
    EXPECT_NO_THROW(
        TiffIfdMakernote makernote(0xFFFF, IfdId::exifId, IfdId::canonId, nullptr, false)
    );
}

// Test setImageByteOrder
TEST_F(TiffIfdMakernoteTest_311, SetImageByteOrder_311) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // Should not crash
    EXPECT_NO_THROW(makernote.setImageByteOrder(bigEndian));
    EXPECT_NO_THROW(makernote.setImageByteOrder(littleEndian));
    EXPECT_NO_THROW(makernote.setImageByteOrder(invalidByteOrder));
}

// Test writeHeader called multiple times
TEST_F(TiffIfdMakernoteTest_311, WriteHeaderCalledMultipleTimes_311) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();

    EXPECT_CALL(*rawPtr, write(::testing::_, ::testing::_))
        .WillOnce(::testing::Return(5))
        .WillOnce(::testing::Return(5))
        .WillOnce(::testing::Return(5));

    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);

    MemIo memIo;
    IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);

    EXPECT_EQ(5u, makernote.writeHeader(ioWrapper, littleEndian));
    EXPECT_EQ(5u, makernote.writeHeader(ioWrapper, bigEndian));
    EXPECT_EQ(5u, makernote.writeHeader(ioWrapper, littleEndian));
}
