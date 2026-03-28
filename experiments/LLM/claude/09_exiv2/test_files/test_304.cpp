#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "makernote_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Mock MnHeader for testing
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

class TiffIfdMakernoteTest_304 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test ifdOffset returns 0 when pHeader_ is nullptr
TEST_F(TiffIfdMakernoteTest_304, IfdOffsetReturnsZeroWhenNoHeader_304) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(0u, makernote.ifdOffset());
}

// Test ifdOffset delegates to header when header is provided
TEST_F(TiffIfdMakernoteTest_304, IfdOffsetDelegatesToHeader_304) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, ifdOffset())
        .WillOnce(::testing::Return(42));
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    EXPECT_EQ(42u, makernote.ifdOffset());
}

// Test ifdOffset delegates to header returning 0
TEST_F(TiffIfdMakernoteTest_304, IfdOffsetDelegatesToHeaderReturningZero_304) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, ifdOffset())
        .WillOnce(::testing::Return(0));
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    EXPECT_EQ(0u, makernote.ifdOffset());
}

// Test byteOrder returns invalidByteOrder when no header is set (default behavior)
TEST_F(TiffIfdMakernoteTest_304, ByteOrderWithNoHeader_304) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    // When no header, byteOrder should return invalidByteOrder (default from MnHeader base)
    ByteOrder bo = makernote.byteOrder();
    EXPECT_EQ(invalidByteOrder, bo);
}

// Test byteOrder delegates to header when present
TEST_F(TiffIfdMakernoteTest_304, ByteOrderDelegatesToHeader_304) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, byteOrder())
        .WillOnce(::testing::Return(bigEndian));
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    EXPECT_EQ(bigEndian, makernote.byteOrder());
}

// Test mnOffset returns default value when freshly constructed
TEST_F(TiffIfdMakernoteTest_304, MnOffsetReturnsDefaultOnConstruction_304) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(0u, makernote.mnOffset());
}

// Test baseOffset returns default when no header
TEST_F(TiffIfdMakernoteTest_304, BaseOffsetWithNoHeader_304) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    size_t offset = makernote.baseOffset();
    EXPECT_EQ(0u, offset);
}

// Test sizeHeader returns 0 when no header
TEST_F(TiffIfdMakernoteTest_304, SizeHeaderWithNoHeader_304) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_EQ(0u, makernote.sizeHeader());
}

// Test sizeHeader delegates to header when present
TEST_F(TiffIfdMakernoteTest_304, SizeHeaderDelegatesToHeader_304) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, size())
        .WillOnce(::testing::Return(12));
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    EXPECT_EQ(12u, makernote.sizeHeader());
}

// Test readHeader with no header returns true (or appropriate value)
TEST_F(TiffIfdMakernoteTest_304, ReadHeaderWithNoHeader_304) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    byte data[] = {0x00, 0x01, 0x02};
    bool result = makernote.readHeader(data, sizeof(data), littleEndian);
    EXPECT_TRUE(result);
}

// Test readHeader delegates to header when present
TEST_F(TiffIfdMakernoteTest_304, ReadHeaderDelegatesToHeader_304) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    byte data[] = {0x00, 0x01, 0x02, 0x03};
    
    EXPECT_CALL(*rawPtr, read(data, 4, littleEndian))
        .WillOnce(::testing::Return(true));
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    EXPECT_TRUE(makernote.readHeader(data, 4, littleEndian));
}

// Test readHeader returns false when header read fails
TEST_F(TiffIfdMakernoteTest_304, ReadHeaderReturnsFalseOnFailure_304) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    byte data[] = {0xFF};
    
    EXPECT_CALL(*rawPtr, read(data, 1, bigEndian))
        .WillOnce(::testing::Return(false));
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    EXPECT_FALSE(makernote.readHeader(data, 1, bigEndian));
}

// Test setByteOrder delegates to header
TEST_F(TiffIfdMakernoteTest_304, SetByteOrderDelegatesToHeader_304) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, setByteOrder(littleEndian))
        .Times(1);
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    makernote.setByteOrder(littleEndian);
}

// Test setByteOrder with no header does not crash
TEST_F(TiffIfdMakernoteTest_304, SetByteOrderWithNoHeaderDoesNotCrash_304) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_NO_THROW(makernote.setByteOrder(bigEndian));
}

// Test ifdOffset with large value from header
TEST_F(TiffIfdMakernoteTest_304, IfdOffsetLargeValue_304) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, ifdOffset())
        .WillOnce(::testing::Return(0xFFFFFFFF));
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    EXPECT_EQ(0xFFFFFFFFu, makernote.ifdOffset());
}

// Test construction with hasNext = true
TEST_F(TiffIfdMakernoteTest_304, ConstructionWithHasNextTrue_304) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    EXPECT_NO_THROW(TiffIfdMakernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), true));
}

// Test construction with different tag values
TEST_F(TiffIfdMakernoteTest_304, ConstructionWithDifferentTag_304) {
    EXPECT_NO_THROW(TiffIfdMakernote(0x0000, IfdId::exifId, IfdId::canonId, nullptr, false));
}

// Test multiple calls to ifdOffset are consistent
TEST_F(TiffIfdMakernoteTest_304, IfdOffsetMultipleCalls_304) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, ifdOffset())
        .WillRepeatedly(::testing::Return(10));
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    EXPECT_EQ(10u, makernote.ifdOffset());
    EXPECT_EQ(10u, makernote.ifdOffset());
    EXPECT_EQ(10u, makernote.ifdOffset());
}

// Test setImageByteOrder does not crash
TEST_F(TiffIfdMakernoteTest_304, SetImageByteOrderDoesNotCrash_304) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_NO_THROW(makernote.setImageByteOrder(bigEndian));
}

// Test setImageByteOrder with little endian
TEST_F(TiffIfdMakernoteTest_304, SetImageByteOrderLittleEndian_304) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_NO_THROW(makernote.setImageByteOrder(littleEndian));
}

// Test setImageByteOrder with invalidByteOrder
TEST_F(TiffIfdMakernoteTest_304, SetImageByteOrderInvalid_304) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    EXPECT_NO_THROW(makernote.setImageByteOrder(invalidByteOrder));
}
