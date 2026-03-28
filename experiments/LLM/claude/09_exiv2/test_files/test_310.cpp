#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers from the project
#include "tiffcomposite_int.hpp"
#include "makernote_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Mock MnHeader for testing
class MockMnHeader : public MnHeader {
public:
    MOCK_METHOD(bool, read, (const byte* pData, size_t size, ByteOrder byteOrder), (override));
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(size_t, write, (IoWrapper& ioWrapper, ByteOrder byteOrder), (const, override));
    MOCK_METHOD(size_t, ifdOffset, (), (const, override));
    MOCK_METHOD(ByteOrder, byteOrder, (), (const, override));
    MOCK_METHOD(size_t, baseOffset, (size_t mnOffset), (const, override));
    MOCK_METHOD(void, setByteOrder, (ByteOrder byteOrder), (override));
};

// Test fixture
class TiffIfdMakernoteTest_310 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: sizeHeader returns 0 when pHeader_ is nullptr
TEST_F(TiffIfdMakernoteTest_310, SizeHeaderReturnsZeroWhenNoHeader_310) {
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, nullptr, false);
    EXPECT_EQ(0u, makernote.sizeHeader());
}

// Test: sizeHeader returns header size when header is present
TEST_F(TiffIfdMakernoteTest_310, SizeHeaderReturnsSizeFromHeader_310) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, size()).WillOnce(::testing::Return(42));
    
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, std::move(mockHeader), false);
    EXPECT_EQ(42u, makernote.sizeHeader());
}

// Test: sizeHeader with header returning zero size
TEST_F(TiffIfdMakernoteTest_310, SizeHeaderReturnsZeroFromHeaderWithZeroSize_310) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, size()).WillOnce(::testing::Return(0));
    
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, std::move(mockHeader), false);
    EXPECT_EQ(0u, makernote.sizeHeader());
}

// Test: sizeHeader with header returning large size
TEST_F(TiffIfdMakernoteTest_310, SizeHeaderReturnsLargeSize_310) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, size()).WillOnce(::testing::Return(65536));
    
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, std::move(mockHeader), false);
    EXPECT_EQ(65536u, makernote.sizeHeader());
}

// Test: byteOrder returns value from header when header is present
TEST_F(TiffIfdMakernoteTest_310, ByteOrderDelegatesToHeader_310) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, byteOrder()).WillOnce(::testing::Return(littleEndian));
    
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, std::move(mockHeader), false);
    // byteOrder() may delegate to header or return imageByteOrder depending on implementation
    // We test the observable behavior
    ByteOrder bo = makernote.byteOrder();
    (void)bo; // Just ensure it doesn't crash
}

// Test: readHeader with nullptr header
TEST_F(TiffIfdMakernoteTest_310, ReadHeaderWithNullHeader_310) {
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, nullptr, false);
    byte data[] = {0x00, 0x01, 0x02};
    bool result = makernote.readHeader(data, sizeof(data), littleEndian);
    // When no header, readHeader should return true (nothing to read)
    EXPECT_TRUE(result);
}

// Test: readHeader delegates to header's read method
TEST_F(TiffIfdMakernoteTest_310, ReadHeaderDelegatesToHeader_310) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    byte data[] = {0x00, 0x01, 0x02, 0x03};
    
    EXPECT_CALL(*rawPtr, read(data, sizeof(data), bigEndian))
        .WillOnce(::testing::Return(true));
    
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, std::move(mockHeader), false);
    bool result = makernote.readHeader(data, sizeof(data), bigEndian);
    EXPECT_TRUE(result);
}

// Test: readHeader returns false when header read fails
TEST_F(TiffIfdMakernoteTest_310, ReadHeaderReturnsFalseOnFailure_310) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    byte data[] = {0xFF};
    
    EXPECT_CALL(*rawPtr, read(data, sizeof(data), littleEndian))
        .WillOnce(::testing::Return(false));
    
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, std::move(mockHeader), false);
    bool result = makernote.readHeader(data, sizeof(data), littleEndian);
    EXPECT_FALSE(result);
}

// Test: setByteOrder delegates to header
TEST_F(TiffIfdMakernoteTest_310, SetByteOrderDelegatesToHeader_310) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, setByteOrder(bigEndian)).Times(1);
    
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, std::move(mockHeader), false);
    makernote.setByteOrder(bigEndian);
}

// Test: setByteOrder with null header doesn't crash
TEST_F(TiffIfdMakernoteTest_310, SetByteOrderWithNullHeaderDoesNotCrash_310) {
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, nullptr, false);
    EXPECT_NO_THROW(makernote.setByteOrder(littleEndian));
}

// Test: ifdOffset delegates to header
TEST_F(TiffIfdMakernoteTest_310, IfdOffsetDelegatesToHeader_310) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, ifdOffset()).WillOnce(::testing::Return(8));
    
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, std::move(mockHeader), false);
    EXPECT_EQ(8u, makernote.ifdOffset());
}

// Test: ifdOffset with null header
TEST_F(TiffIfdMakernoteTest_310, IfdOffsetWithNullHeader_310) {
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, nullptr, false);
    // Should return 0 when no header
    EXPECT_EQ(0u, makernote.ifdOffset());
}

// Test: mnOffset returns stored value (initially 0)
TEST_F(TiffIfdMakernoteTest_310, MnOffsetInitiallyZero_310) {
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, nullptr, false);
    EXPECT_EQ(0u, makernote.mnOffset());
}

// Test: baseOffset with null header
TEST_F(TiffIfdMakernoteTest_310, BaseOffsetWithNullHeader_310) {
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, nullptr, false);
    size_t result = makernote.baseOffset();
    EXPECT_EQ(0u, result);
}

// Test: Construction with hasNext = true
TEST_F(TiffIfdMakernoteTest_310, ConstructionWithHasNextTrue_310) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    TiffIfdMakernote makernote(0x927C, IfdId::ifd0Id, IfdId::canonId, std::move(mockHeader), true);
    // Should construct without error
    EXPECT_NE(nullptr, &makernote);
}

// Test: Construction with hasNext = false
TEST_F(TiffIfdMakernoteTest_310, ConstructionWithHasNextFalse_310) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    TiffIfdMakernote makernote(0x927C, IfdId::ifd0Id, IfdId::canonId, std::move(mockHeader), false);
    EXPECT_NE(nullptr, &makernote);
}

// Test: setImageByteOrder doesn't crash
TEST_F(TiffIfdMakernoteTest_310, SetImageByteOrder_310) {
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, nullptr, false);
    EXPECT_NO_THROW(makernote.setImageByteOrder(bigEndian));
}

// Test: sizeHeader called multiple times returns consistent results
TEST_F(TiffIfdMakernoteTest_310, SizeHeaderCalledMultipleTimes_310) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, size())
        .WillRepeatedly(::testing::Return(16));
    
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, std::move(mockHeader), false);
    EXPECT_EQ(16u, makernote.sizeHeader());
    EXPECT_EQ(16u, makernote.sizeHeader());
    EXPECT_EQ(16u, makernote.sizeHeader());
}

// Test: byteOrder with null header returns invalidByteOrder (imageByteOrder_ default)
TEST_F(TiffIfdMakernoteTest_310, ByteOrderWithNullHeaderReturnsInvalid_310) {
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, nullptr, false);
    ByteOrder bo = makernote.byteOrder();
    EXPECT_EQ(invalidByteOrder, bo);
}

// Test: After setImageByteOrder, byteOrder reflects change when no header
TEST_F(TiffIfdMakernoteTest_310, ByteOrderAfterSetImageByteOrder_310) {
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, nullptr, false);
    makernote.setImageByteOrder(littleEndian);
    // When header is null and header byteOrder is invalid, imageByteOrder should be used
    ByteOrder bo = makernote.byteOrder();
    EXPECT_EQ(littleEndian, bo);
}

// Test: baseOffset delegates to header
TEST_F(TiffIfdMakernoteTest_310, BaseOffsetDelegatesToHeader_310) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, baseOffset(::testing::_)).WillOnce(::testing::Return(100));
    
    TiffIfdMakernote makernote(0x0001, IfdId::ifd0Id, IfdId::canonId, std::move(mockHeader), false);
    EXPECT_EQ(100u, makernote.baseOffset());
}
