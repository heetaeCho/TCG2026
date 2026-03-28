#include <gtest/gtest.h>
#include <exiv2/exiv2.hpp>
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// A minimal TiffHeader to satisfy the constructor
class TestTiffHeader : public TiffHeaderBase {
public:
    TestTiffHeader(ByteOrder bo = littleEndian)
        : TiffHeaderBase(42, 8, bo, 0) {}
    ~TestTiffHeader() override = default;
    bool read(const byte* pData, size_t size) override { return true; }
    DataBuf write() const override { return DataBuf(); }
};

// Helper to create a TiffEncoder with given byte order
class TiffEncoderTest_277 : public ::testing::Test {
protected:
    void SetUp() override {
        exifData_ = ExifData();
        iptcData_ = IptcData();
        xmpData_ = XmpData();
    }

    std::unique_ptr<TiffEncoder> createEncoder(ByteOrder bo = littleEndian, bool isNewImage = false) {
        header_ = std::make_unique<TestTiffHeader>(bo);
        // Create a minimal TiffDirectory as root
        root_ = std::make_unique<TiffDirectory>(0x0001, IfdId::ifd0Id);
        
        PrimaryGroups primaryGroups;
        primaryGroups.push_back(IfdId::ifd0Id);

        return std::make_unique<TiffEncoder>(
            exifData_,
            iptcData_,
            xmpData_,
            root_.get(),
            isNewImage,
            std::move(primaryGroups),
            header_.get(),
            nullptr
        );
    }

    ExifData exifData_;
    IptcData iptcData_;
    XmpData xmpData_;
    std::unique_ptr<TestTiffHeader> header_;
    std::unique_ptr<TiffDirectory> root_;
};

// Test that byteOrder returns the byte order from the header (little endian)
TEST_F(TiffEncoderTest_277, ByteOrderLittleEndian_277) {
    auto encoder = createEncoder(littleEndian);
    EXPECT_EQ(littleEndian, encoder->byteOrder());
}

// Test that byteOrder returns the byte order from the header (big endian)
TEST_F(TiffEncoderTest_277, ByteOrderBigEndian_277) {
    auto encoder = createEncoder(bigEndian);
    EXPECT_EQ(bigEndian, encoder->byteOrder());
}

// Test that dirty returns false by default (initial state)
TEST_F(TiffEncoderTest_277, DirtyDefaultFalse_277) {
    auto encoder = createEncoder();
    EXPECT_FALSE(encoder->dirty());
}

// Test that setDirty(true) makes dirty() return true
TEST_F(TiffEncoderTest_277, SetDirtyTrue_277) {
    auto encoder = createEncoder();
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
}

// Test that setDirty(false) makes dirty() return false
TEST_F(TiffEncoderTest_277, SetDirtyFalse_277) {
    auto encoder = createEncoder();
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
}

// Test toggling dirty flag multiple times
TEST_F(TiffEncoderTest_277, SetDirtyToggle_277) {
    auto encoder = createEncoder();
    EXPECT_FALSE(encoder->dirty());
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
}

// Test that writeMethod returns wmNonIntrusive by default
TEST_F(TiffEncoderTest_277, WriteMethodDefault_277) {
    auto encoder = createEncoder();
    EXPECT_EQ(wmNonIntrusive, encoder->writeMethod());
}

// Test encoder creation with isNewImage = true
TEST_F(TiffEncoderTest_277, CreateWithNewImageTrue_277) {
    auto encoder = createEncoder(littleEndian, true);
    ASSERT_NE(nullptr, encoder.get());
    EXPECT_EQ(littleEndian, encoder->byteOrder());
}

// Test encoder creation with isNewImage = false
TEST_F(TiffEncoderTest_277, CreateWithNewImageFalse_277) {
    auto encoder = createEncoder(bigEndian, false);
    ASSERT_NE(nullptr, encoder.get());
    EXPECT_EQ(bigEndian, encoder->byteOrder());
}

// Test that setting dirty to false on a fresh encoder stays false
TEST_F(TiffEncoderTest_277, SetDirtyFalseOnFresh_277) {
    auto encoder = createEncoder();
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
}

} // namespace
