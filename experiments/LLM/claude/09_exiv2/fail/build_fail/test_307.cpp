#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "makernote_int.hpp"
#include "tiffvisitor_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Mock for MnHeader to test TiffIfdMakernote behavior
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

class TiffIfdMakernoteTest_307 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test: baseOffset returns 0 when pHeader_ is null
TEST_F(TiffIfdMakernoteTest_307, BaseOffsetReturnsZeroWhenNoHeader_307) {
    // Create TiffIfdMakernote with null header
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    EXPECT_EQ(0u, makernote.baseOffset());
}

// Test: baseOffset delegates to pHeader_->baseOffset when header exists
TEST_F(TiffIfdMakernoteTest_307, BaseOffsetDelegatesToHeader_307) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, baseOffset(testing::_))
        .WillOnce(testing::Return(42u));
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    
    EXPECT_EQ(42u, makernote.baseOffset());
}

// Test: ifdOffset returns 0 when pHeader_ is null
TEST_F(TiffIfdMakernoteTest_307, IfdOffsetReturnsZeroWhenNoHeader_307) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    EXPECT_EQ(0u, makernote.ifdOffset());
}

// Test: ifdOffset delegates to pHeader_->ifdOffset when header exists
TEST_F(TiffIfdMakernoteTest_307, IfdOffsetDelegatesToHeader_307) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, ifdOffset())
        .WillOnce(testing::Return(100u));
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    
    EXPECT_EQ(100u, makernote.ifdOffset());
}

// Test: byteOrder returns invalidByteOrder when pHeader_ is null
TEST_F(TiffIfdMakernoteTest_307, ByteOrderReturnsInvalidWhenNoHeader_307) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    EXPECT_EQ(invalidByteOrder, makernote.byteOrder());
}

// Test: byteOrder delegates to pHeader_->byteOrder when header exists
TEST_F(TiffIfdMakernoteTest_307, ByteOrderDelegatesToHeader_307) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, byteOrder())
        .WillOnce(testing::Return(littleEndian));
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    
    EXPECT_EQ(littleEndian, makernote.byteOrder());
}

// Test: sizeHeader returns 0 when pHeader_ is null
TEST_F(TiffIfdMakernoteTest_307, SizeHeaderReturnsZeroWhenNoHeader_307) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    EXPECT_EQ(0u, makernote.sizeHeader());
}

// Test: sizeHeader delegates to pHeader_->size when header exists
TEST_F(TiffIfdMakernoteTest_307, SizeHeaderDelegatesToHeader_307) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, size())
        .WillOnce(testing::Return(8u));
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    
    EXPECT_EQ(8u, makernote.sizeHeader());
}

// Test: readHeader returns true when pHeader_ is null (no header to read)
TEST_F(TiffIfdMakernoteTest_307, ReadHeaderWithNullHeader_307) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    byte data[] = {0x00, 0x01, 0x02, 0x03};
    bool result = makernote.readHeader(data, sizeof(data), littleEndian);
    EXPECT_TRUE(result);
}

// Test: readHeader delegates to pHeader_->read when header exists
TEST_F(TiffIfdMakernoteTest_307, ReadHeaderDelegatesToHeader_307) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    byte data[] = {0x00, 0x01, 0x02, 0x03};
    
    EXPECT_CALL(*rawPtr, read(data, sizeof(data), littleEndian))
        .WillOnce(testing::Return(true));
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    
    EXPECT_TRUE(makernote.readHeader(data, sizeof(data), littleEndian));
}

// Test: readHeader returns false when header read fails
TEST_F(TiffIfdMakernoteTest_307, ReadHeaderReturnsFalseOnFailure_307) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    byte data[] = {0xFF};
    
    EXPECT_CALL(*rawPtr, read(data, sizeof(data), bigEndian))
        .WillOnce(testing::Return(false));
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    
    EXPECT_FALSE(makernote.readHeader(data, sizeof(data), bigEndian));
}

// Test: setByteOrder delegates to pHeader_->setByteOrder when header exists
TEST_F(TiffIfdMakernoteTest_307, SetByteOrderDelegatesToHeader_307) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    EXPECT_CALL(*rawPtr, setByteOrder(bigEndian))
        .Times(1);
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    
    makernote.setByteOrder(bigEndian);
}

// Test: setByteOrder with null header does not crash
TEST_F(TiffIfdMakernoteTest_307, SetByteOrderWithNullHeaderNoCrash_307) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    // Should not crash
    makernote.setByteOrder(littleEndian);
}

// Test: mnOffset returns initial value (0)
TEST_F(TiffIfdMakernoteTest_307, MnOffsetInitiallyZero_307) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    EXPECT_EQ(0u, makernote.mnOffset());
}

// Test: Construction with hasNext true
TEST_F(TiffIfdMakernoteTest_307, ConstructionWithHasNextTrue_307) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    
    // Should not crash
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), true);
    
    EXPECT_EQ(0u, makernote.mnOffset());
}

// Test: Construction with hasNext false
TEST_F(TiffIfdMakernoteTest_307, ConstructionWithHasNextFalse_307) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    
    EXPECT_EQ(0u, makernote.mnOffset());
}

// Test: baseOffset passes mnOffset to header
TEST_F(TiffIfdMakernoteTest_307, BaseOffsetPassesMnOffsetToHeader_307) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    // mnOffset_ is initialized to 0
    EXPECT_CALL(*rawPtr, baseOffset(0u))
        .WillOnce(testing::Return(256u));
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    
    EXPECT_EQ(256u, makernote.baseOffset());
}

// Test: setImageByteOrder does not crash
TEST_F(TiffIfdMakernoteTest_307, SetImageByteOrderNoCrash_307) {
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    // Should not crash
    makernote.setImageByteOrder(littleEndian);
    makernote.setImageByteOrder(bigEndian);
    makernote.setImageByteOrder(invalidByteOrder);
}

// Test: Different tag values in construction
TEST_F(TiffIfdMakernoteTest_307, DifferentTagValues_307) {
    TiffIfdMakernote makernote1(0x0000, IfdId::exifId, IfdId::canonId, nullptr, false);
    TiffIfdMakernote makernote2(0xFFFF, IfdId::exifId, IfdId::canonId, nullptr, false);
    
    // Both should be constructable without issues
    EXPECT_EQ(0u, makernote1.baseOffset());
    EXPECT_EQ(0u, makernote2.baseOffset());
}

// Test: Large baseOffset value from header
TEST_F(TiffIfdMakernoteTest_307, LargeBaseOffsetFromHeader_307) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* rawPtr = mockHeader.get();
    
    size_t largeOffset = static_cast<size_t>(-1);  // Max size_t
    EXPECT_CALL(*rawPtr, baseOffset(testing::_))
        .WillOnce(testing::Return(largeOffset));
    
    TiffIfdMakernote makernote(0x927c, IfdId::exifId, IfdId::canonId, std::move(mockHeader), false);
    
    EXPECT_EQ(largeOffset, makernote.baseOffset());
}
