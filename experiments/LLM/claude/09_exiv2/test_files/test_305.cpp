#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Mock MnHeader to control byteOrder() return values
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

class TiffIfdMakernoteTest_305 : public ::testing::Test {
protected:
    // Helper to create a TiffIfdMakernote with a mock header
    // We use IfdId values that are valid; using ifdIdNotSet (0) or similar
    std::unique_ptr<TiffIfdMakernote> createWithMockHeader(MockMnHeader*& outMock) {
        auto mockHeader = std::make_unique<MockMnHeader>();
        outMock = mockHeader.get();
        return std::make_unique<TiffIfdMakernote>(
            0x927c, // typical MakerNote tag
            IfdId::exifId,
            IfdId::canonId,
            std::move(mockHeader),
            false
        );
    }

    std::unique_ptr<TiffIfdMakernote> createWithNullHeader() {
        return std::make_unique<TiffIfdMakernote>(
            0x927c,
            IfdId::exifId,
            IfdId::canonId,
            nullptr,
            false
        );
    }
};

// Test: When pHeader_ is null, byteOrder() should return imageByteOrder_
// Since imageByteOrder_ defaults to invalidByteOrder, we expect invalidByteOrder
TEST_F(TiffIfdMakernoteTest_305, ByteOrderReturnsInvalidWhenNoHeaderAndDefaultImageByteOrder_305) {
    auto makernote = createWithNullHeader();
    EXPECT_EQ(makernote->byteOrder(), invalidByteOrder);
}

// Test: When pHeader_ is null but imageByteOrder is set, byteOrder() returns imageByteOrder
TEST_F(TiffIfdMakernoteTest_305, ByteOrderReturnsImageByteOrderWhenNoHeader_305) {
    auto makernote = createWithNullHeader();
    makernote->setImageByteOrder(littleEndian);
    EXPECT_EQ(makernote->byteOrder(), littleEndian);
}

// Test: When pHeader_ is null but imageByteOrder is set to bigEndian
TEST_F(TiffIfdMakernoteTest_305, ByteOrderReturnsImageByteOrderBigEndianWhenNoHeader_305) {
    auto makernote = createWithNullHeader();
    makernote->setImageByteOrder(bigEndian);
    EXPECT_EQ(makernote->byteOrder(), bigEndian);
}

// Test: When header exists and returns invalidByteOrder, should fall back to imageByteOrder
TEST_F(TiffIfdMakernoteTest_305, ByteOrderFallsBackToImageByteOrderWhenHeaderReturnsInvalid_305) {
    MockMnHeader* mock = nullptr;
    auto makernote = createWithMockHeader(mock);
    
    EXPECT_CALL(*mock, byteOrder())
        .WillRepeatedly(::testing::Return(invalidByteOrder));
    
    makernote->setImageByteOrder(bigEndian);
    EXPECT_EQ(makernote->byteOrder(), bigEndian);
}

// Test: When header exists and returns a valid byte order, should return header's byte order
TEST_F(TiffIfdMakernoteTest_305, ByteOrderReturnsHeaderByteOrderWhenValid_305) {
    MockMnHeader* mock = nullptr;
    auto makernote = createWithMockHeader(mock);
    
    EXPECT_CALL(*mock, byteOrder())
        .WillRepeatedly(::testing::Return(littleEndian));
    
    makernote->setImageByteOrder(bigEndian);
    EXPECT_EQ(makernote->byteOrder(), littleEndian);
}

// Test: When header exists and returns bigEndian, should return bigEndian regardless of imageByteOrder
TEST_F(TiffIfdMakernoteTest_305, ByteOrderReturnsHeaderBigEndianOverImageByteOrder_305) {
    MockMnHeader* mock = nullptr;
    auto makernote = createWithMockHeader(mock);
    
    EXPECT_CALL(*mock, byteOrder())
        .WillRepeatedly(::testing::Return(bigEndian));
    
    makernote->setImageByteOrder(littleEndian);
    EXPECT_EQ(makernote->byteOrder(), bigEndian);
}

// Test: Header returns invalidByteOrder and imageByteOrder is also invalid
TEST_F(TiffIfdMakernoteTest_305, ByteOrderReturnsInvalidWhenBothHeaderAndImageAreInvalid_305) {
    MockMnHeader* mock = nullptr;
    auto makernote = createWithMockHeader(mock);
    
    EXPECT_CALL(*mock, byteOrder())
        .WillRepeatedly(::testing::Return(invalidByteOrder));
    
    // imageByteOrder_ defaults to invalidByteOrder
    EXPECT_EQ(makernote->byteOrder(), invalidByteOrder);
}

// Test: setImageByteOrder changes the fallback byte order
TEST_F(TiffIfdMakernoteTest_305, SetImageByteOrderChangesReturn_305) {
    auto makernote = createWithNullHeader();
    
    makernote->setImageByteOrder(littleEndian);
    EXPECT_EQ(makernote->byteOrder(), littleEndian);
    
    makernote->setImageByteOrder(bigEndian);
    EXPECT_EQ(makernote->byteOrder(), bigEndian);
    
    makernote->setImageByteOrder(invalidByteOrder);
    EXPECT_EQ(makernote->byteOrder(), invalidByteOrder);
}

// Test: Header's byteOrder is checked (not just imageByteOrder)
TEST_F(TiffIfdMakernoteTest_305, HeaderByteOrderTakesPrecedence_305) {
    MockMnHeader* mock = nullptr;
    auto makernote = createWithMockHeader(mock);
    
    // First call returns littleEndian, second returns invalidByteOrder
    EXPECT_CALL(*mock, byteOrder())
        .WillOnce(::testing::Return(littleEndian))
        .WillOnce(::testing::Return(invalidByteOrder));
    
    makernote->setImageByteOrder(bigEndian);
    
    // First call: header returns littleEndian -> should return littleEndian
    EXPECT_EQ(makernote->byteOrder(), littleEndian);
    
    // Second call: header returns invalidByteOrder -> should fall back to bigEndian
    EXPECT_EQ(makernote->byteOrder(), bigEndian);
}

// Test: Construction with hasNext = true
TEST_F(TiffIfdMakernoteTest_305, ConstructionWithHasNextTrue_305) {
    auto mockHeader = std::make_unique<MockMnHeader>();
    MockMnHeader* mock = mockHeader.get();
    
    EXPECT_CALL(*mock, byteOrder())
        .WillRepeatedly(::testing::Return(bigEndian));
    
    auto makernote = std::make_unique<TiffIfdMakernote>(
        0x927c,
        IfdId::exifId,
        IfdId::canonId,
        std::move(mockHeader),
        true
    );
    
    EXPECT_EQ(makernote->byteOrder(), bigEndian);
}

// Test: sizeHeader with null header
TEST_F(TiffIfdMakernoteTest_305, SizeHeaderWithNullHeader_305) {
    auto makernote = createWithNullHeader();
    // With no header, sizeHeader should return 0
    EXPECT_EQ(makernote->sizeHeader(), 0u);
}

// Test: sizeHeader with mock header
TEST_F(TiffIfdMakernoteTest_305, SizeHeaderWithMockHeader_305) {
    MockMnHeader* mock = nullptr;
    auto makernote = createWithMockHeader(mock);
    
    EXPECT_CALL(*mock, size())
        .WillOnce(::testing::Return(42));
    
    EXPECT_EQ(makernote->sizeHeader(), 42u);
}

// Test: readHeader with null header
TEST_F(TiffIfdMakernoteTest_305, ReadHeaderWithNullHeader_305) {
    auto makernote = createWithNullHeader();
    byte data[] = {0x00, 0x01, 0x02};
    // With no header, readHeader should return true (nothing to read, success)
    EXPECT_TRUE(makernote->readHeader(data, sizeof(data), littleEndian));
}

// Test: readHeader delegates to header
TEST_F(TiffIfdMakernoteTest_305, ReadHeaderDelegatesToHeader_305) {
    MockMnHeader* mock = nullptr;
    auto makernote = createWithMockHeader(mock);
    
    byte data[] = {0x00, 0x01, 0x02};
    
    EXPECT_CALL(*mock, read(data, sizeof(data), littleEndian))
        .WillOnce(::testing::Return(true));
    
    EXPECT_TRUE(makernote->readHeader(data, sizeof(data), littleEndian));
}

// Test: readHeader returns false when header read fails
TEST_F(TiffIfdMakernoteTest_305, ReadHeaderReturnsFalseOnFailure_305) {
    MockMnHeader* mock = nullptr;
    auto makernote = createWithMockHeader(mock);
    
    byte data[] = {0x00};
    
    EXPECT_CALL(*mock, read(data, sizeof(data), bigEndian))
        .WillOnce(::testing::Return(false));
    
    EXPECT_FALSE(makernote->readHeader(data, sizeof(data), bigEndian));
}

// Test: ifdOffset with null header
TEST_F(TiffIfdMakernoteTest_305, IfdOffsetWithNullHeader_305) {
    auto makernote = createWithNullHeader();
    EXPECT_EQ(makernote->ifdOffset(), 0u);
}

// Test: ifdOffset with mock header
TEST_F(TiffIfdMakernoteTest_305, IfdOffsetWithMockHeader_305) {
    MockMnHeader* mock = nullptr;
    auto makernote = createWithMockHeader(mock);
    
    EXPECT_CALL(*mock, ifdOffset())
        .WillOnce(::testing::Return(8));
    
    EXPECT_EQ(makernote->ifdOffset(), 8u);
}

// Test: setByteOrder delegates to header
TEST_F(TiffIfdMakernoteTest_305, SetByteOrderDelegatesToHeader_305) {
    MockMnHeader* mock = nullptr;
    auto makernote = createWithMockHeader(mock);
    
    EXPECT_CALL(*mock, setByteOrder(littleEndian))
        .Times(1);
    
    makernote->setByteOrder(littleEndian);
}

// Test: setByteOrder with null header doesn't crash
TEST_F(TiffIfdMakernoteTest_305, SetByteOrderWithNullHeaderDoesNotCrash_305) {
    auto makernote = createWithNullHeader();
    EXPECT_NO_THROW(makernote->setByteOrder(bigEndian));
}
