#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// Helper to create a minimal TiffHeader for TiffEncoder construction
class MinimalTiffHeader : public TiffHeaderBase {
public:
    MinimalTiffHeader() : TiffHeaderBase(42, 8, littleEndian, 8) {}
    ~MinimalTiffHeader() override = default;
    
    bool read(const byte* pData, size_t size) override { return true; }
    DataBuf write() const override { return DataBuf(); }
    void setByteOrder(ByteOrder byteOrder) { TiffHeaderBase::setByteOrder(byteOrder); }
};

class TiffEncoderTest_1670 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<MinimalTiffHeader>();
    }

    std::unique_ptr<MinimalTiffHeader> header_;
    ExifData exifData_;
    IptcData iptcData_;
    XmpData xmpData_;
};

// Test that dirty() returns false initially after construction
TEST_F(TiffEncoderTest_1670, DirtyReturnsFalseInitially_1670) {
    PrimaryGroups primaryGroups;
    TiffDirectory rootDir(0, IfdId::ifd0Id);
    
    TiffEncoder encoder(
        exifData_, iptcData_, xmpData_,
        &rootDir, false, std::move(primaryGroups),
        header_.get(), nullptr
    );
    
    EXPECT_FALSE(encoder.dirty());
}

// Test that setDirty(true) makes dirty() return true
TEST_F(TiffEncoderTest_1670, SetDirtyTrueMakesDirtyTrue_1670) {
    PrimaryGroups primaryGroups;
    TiffDirectory rootDir(0, IfdId::ifd0Id);
    
    TiffEncoder encoder(
        exifData_, iptcData_, xmpData_,
        &rootDir, false, std::move(primaryGroups),
        header_.get(), nullptr
    );
    
    encoder.setDirty(true);
    EXPECT_TRUE(encoder.dirty());
}

// Test that setDirty(false) makes dirty() return false
TEST_F(TiffEncoderTest_1670, SetDirtyFalseMakesDirtyFalse_1670) {
    PrimaryGroups primaryGroups;
    TiffDirectory rootDir(0, IfdId::ifd0Id);
    
    TiffEncoder encoder(
        exifData_, iptcData_, xmpData_,
        &rootDir, false, std::move(primaryGroups),
        header_.get(), nullptr
    );
    
    encoder.setDirty(true);
    encoder.setDirty(false);
    EXPECT_FALSE(encoder.dirty());
}

// Test that byteOrder() returns the byte order from the header
TEST_F(TiffEncoderTest_1670, ByteOrderMatchesHeader_1670) {
    PrimaryGroups primaryGroups;
    TiffDirectory rootDir(0, IfdId::ifd0Id);
    
    TiffEncoder encoder(
        exifData_, iptcData_, xmpData_,
        &rootDir, false, std::move(primaryGroups),
        header_.get(), nullptr
    );
    
    EXPECT_EQ(encoder.byteOrder(), littleEndian);
}

// Test that writeMethod() returns wmNonIntrusive by default
TEST_F(TiffEncoderTest_1670, WriteMethodDefaultNonIntrusive_1670) {
    PrimaryGroups primaryGroups;
    TiffDirectory rootDir(0, IfdId::ifd0Id);
    
    TiffEncoder encoder(
        exifData_, iptcData_, xmpData_,
        &rootDir, false, std::move(primaryGroups),
        header_.get(), nullptr
    );
    
    EXPECT_EQ(encoder.writeMethod(), wmNonIntrusive);
}

// Test with big endian header
TEST_F(TiffEncoderTest_1670, ByteOrderBigEndian_1670) {
    auto bigEndianHeader = std::make_unique<MinimalTiffHeader>();
    bigEndianHeader->setByteOrder(bigEndian);
    
    PrimaryGroups primaryGroups;
    TiffDirectory rootDir(0, IfdId::ifd0Id);
    
    TiffEncoder encoder(
        exifData_, iptcData_, xmpData_,
        &rootDir, false, std::move(primaryGroups),
        bigEndianHeader.get(), nullptr
    );
    
    EXPECT_EQ(encoder.byteOrder(), bigEndian);
}

// Test toggling dirty flag multiple times
TEST_F(TiffEncoderTest_1670, SetDirtyToggleMultipleTimes_1670) {
    PrimaryGroups primaryGroups;
    TiffDirectory rootDir(0, IfdId::ifd0Id);
    
    TiffEncoder encoder(
        exifData_, iptcData_, xmpData_,
        &rootDir, false, std::move(primaryGroups),
        header_.get(), nullptr
    );
    
    EXPECT_FALSE(encoder.dirty());
    encoder.setDirty(true);
    EXPECT_TRUE(encoder.dirty());
    encoder.setDirty(true);
    EXPECT_TRUE(encoder.dirty());
    encoder.setDirty(false);
    EXPECT_FALSE(encoder.dirty());
    encoder.setDirty(false);
    EXPECT_FALSE(encoder.dirty());
}

// Test construction with isNewImage = true
TEST_F(TiffEncoderTest_1670, ConstructionWithNewImage_1670) {
    PrimaryGroups primaryGroups;
    TiffDirectory rootDir(0, IfdId::ifd0Id);
    
    TiffEncoder encoder(
        exifData_, iptcData_, xmpData_,
        &rootDir, true, std::move(primaryGroups),
        header_.get(), nullptr
    );
    
    // Should still initialize properly
    EXPECT_FALSE(encoder.dirty());
    EXPECT_EQ(encoder.writeMethod(), wmNonIntrusive);
}

// Test visitDirectory does not crash with valid directory
TEST_F(TiffEncoderTest_1670, VisitDirectoryDoesNotCrash_1670) {
    PrimaryGroups primaryGroups;
    TiffDirectory rootDir(0, IfdId::ifd0Id);
    
    TiffEncoder encoder(
        exifData_, iptcData_, xmpData_,
        &rootDir, false, std::move(primaryGroups),
        header_.get(), nullptr
    );
    
    TiffDirectory dir(0, IfdId::ifd0Id);
    EXPECT_NO_THROW(encoder.visitDirectory(&dir));
}

// Test construction with non-empty ExifData
TEST_F(TiffEncoderTest_1670, ConstructionWithExifData_1670) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestCamera";
    
    PrimaryGroups primaryGroups;
    TiffDirectory rootDir(0, IfdId::ifd0Id);
    
    TiffEncoder encoder(
        exifData, iptcData_, xmpData_,
        &rootDir, false, std::move(primaryGroups),
        header_.get(), nullptr
    );
    
    EXPECT_FALSE(encoder.dirty());
    EXPECT_EQ(encoder.byteOrder(), littleEndian);
}

} // namespace
