#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "makernote_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;
using ::testing::Return;
using ::testing::_;

class MockMnHeader : public MnHeader {
public:
    MOCK_METHOD(bool, read, (const byte* pData, size_t size, ByteOrder byteOrder), (override));
    MOCK_METHOD(void, setByteOrder, (ByteOrder byteOrder), (override));
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(size_t, ifdOffset, (), (const, override));
    MOCK_METHOD(ByteOrder, byteOrder, (), (const, override));
    MOCK_METHOD(size_t, baseOffset, (size_t mnOffset), (const, override));
};

class TiffIfdMakernoteTest_308 : public ::testing::Test {
protected:
    // Helper to create TiffIfdMakernote with a mock header
    std::pair<TiffIfdMakernote*, MockMnHeader*> createWithMockHeader() {
        auto mockHeader = std::make_unique<MockMnHeader>();
        MockMnHeader* rawPtr = mockHeader.get();
        auto* makernote = new TiffIfdMakernote(
            0x927c, IfdId::exifId, IfdId::canonId,
            std::move(mockHeader), false);
        return {makernote, rawPtr};
    }

    // Helper to create TiffIfdMakernote with null header
    TiffIfdMakernote* createWithNullHeader() {
        return new TiffIfdMakernote(
            0x927c, IfdId::exifId, IfdId::canonId,
            nullptr, false);
    }
};

// Test that readHeader returns true when pHeader_ is null
TEST_F(TiffIfdMakernoteTest_308, ReadHeaderWithNullHeader_ReturnsTrue_308) {
    auto* makernote = createWithNullHeader();
    
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    bool result = makernote->readHeader(data, sizeof(data), littleEndian);
    
    EXPECT_TRUE(result);
    delete makernote;
}

// Test that readHeader delegates to pHeader_->read when header exists and returns true
TEST_F(TiffIfdMakernoteTest_308, ReadHeaderWithValidHeader_DelegatesToHeaderRead_ReturnsTrue_308) {
    auto [makernote, mockHeader] = createWithMockHeader();
    
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_CALL(*mockHeader, read(data, sizeof(data), littleEndian))
        .WillOnce(Return(true));
    
    bool result = makernote->readHeader(data, sizeof(data), littleEndian);
    
    EXPECT_TRUE(result);
    delete makernote;
}

// Test that readHeader returns false when pHeader_->read returns false
TEST_F(TiffIfdMakernoteTest_308, ReadHeaderWithValidHeader_DelegatesToHeaderRead_ReturnsFalse_308) {
    auto [makernote, mockHeader] = createWithMockHeader();
    
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    EXPECT_CALL(*mockHeader, read(data, sizeof(data), bigEndian))
        .WillOnce(Return(false));
    
    bool result = makernote->readHeader(data, sizeof(data), bigEndian);
    
    EXPECT_FALSE(result);
    delete makernote;
}

// Test readHeader with zero-size data and null header
TEST_F(TiffIfdMakernoteTest_308, ReadHeaderWithNullHeaderAndZeroSize_ReturnsTrue_308) {
    auto* makernote = createWithNullHeader();
    
    bool result = makernote->readHeader(nullptr, 0, littleEndian);
    
    EXPECT_TRUE(result);
    delete makernote;
}

// Test readHeader with zero-size data and valid header
TEST_F(TiffIfdMakernoteTest_308, ReadHeaderWithValidHeaderAndZeroSize_DelegatesCorrectly_308) {
    auto [makernote, mockHeader] = createWithMockHeader();
    
    EXPECT_CALL(*mockHeader, read(nullptr, 0, littleEndian))
        .WillOnce(Return(false));
    
    bool result = makernote->readHeader(nullptr, 0, littleEndian);
    
    EXPECT_FALSE(result);
    delete makernote;
}

// Test readHeader passes correct byte order to header
TEST_F(TiffIfdMakernoteTest_308, ReadHeaderPassesBigEndianByteOrder_308) {
    auto [makernote, mockHeader] = createWithMockHeader();
    
    const byte data[] = {0xAA, 0xBB};
    EXPECT_CALL(*mockHeader, read(data, sizeof(data), bigEndian))
        .WillOnce(Return(true));
    
    bool result = makernote->readHeader(data, sizeof(data), bigEndian);
    
    EXPECT_TRUE(result);
    delete makernote;
}

// Test readHeader passes correct size to header
TEST_F(TiffIfdMakernoteTest_308, ReadHeaderPassesCorrectSize_308) {
    auto [makernote, mockHeader] = createWithMockHeader();
    
    const byte data[256] = {};
    EXPECT_CALL(*mockHeader, read(data, 256, littleEndian))
        .WillOnce(Return(true));
    
    bool result = makernote->readHeader(data, 256, littleEndian);
    
    EXPECT_TRUE(result);
    delete makernote;
}

// Test readHeader with large data size
TEST_F(TiffIfdMakernoteTest_308, ReadHeaderWithLargeSize_308) {
    auto [makernote, mockHeader] = createWithMockHeader();
    
    const byte data[] = {0x00};
    size_t largeSize = static_cast<size_t>(-1);
    EXPECT_CALL(*mockHeader, read(data, largeSize, littleEndian))
        .WillOnce(Return(false));
    
    bool result = makernote->readHeader(data, largeSize, littleEndian);
    
    EXPECT_FALSE(result);
    delete makernote;
}

// Test setByteOrder delegates to header when header exists
TEST_F(TiffIfdMakernoteTest_308, SetByteOrderWithValidHeader_308) {
    auto [makernote, mockHeader] = createWithMockHeader();
    
    EXPECT_CALL(*mockHeader, setByteOrder(bigEndian))
        .Times(1);
    
    makernote->setByteOrder(bigEndian);
    delete makernote;
}

// Test that readHeader with null pData and non-zero size still delegates
TEST_F(TiffIfdMakernoteTest_308, ReadHeaderNullDataNonZeroSize_DelegatesToHeader_308) {
    auto [makernote, mockHeader] = createWithMockHeader();
    
    EXPECT_CALL(*mockHeader, read(nullptr, 10, littleEndian))
        .WillOnce(Return(false));
    
    bool result = makernote->readHeader(nullptr, 10, littleEndian);
    
    EXPECT_FALSE(result);
    delete makernote;
}
