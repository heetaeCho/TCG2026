#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// Minimal TiffHeader implementation for testing
class TestTiffHeader : public TiffHeaderBase {
public:
    TestTiffHeader() : TiffHeaderBase(42, 8, littleEndian, 0x002a) {}
    ~TestTiffHeader() override = default;
};

// Helper to create a minimal TiffEncoder
class TiffEncoderTest_1680 : public ::testing::Test {
protected:
    void SetUp() override {
        exifData_ = ExifData();
        iptcData_ = IptcData();
        xmpData_ = XmpData();
        header_ = std::make_unique<TestTiffHeader>();
    }

    ExifData exifData_;
    IptcData iptcData_;
    XmpData xmpData_;
    std::unique_ptr<TestTiffHeader> header_;
};

// Test that TiffEncoder can be constructed and dirty flag defaults to false
TEST_F(TiffEncoderTest_1680, ConstructorSetsDirtyFalse_1680) {
    PrimaryGroups primaryGroups;
    TiffEncoder encoder(exifData_, iptcData_, xmpData_, nullptr, false,
                        std::move(primaryGroups), header_.get(), nullptr);
    EXPECT_FALSE(encoder.dirty());
}

// Test setDirty changes the dirty flag
TEST_F(TiffEncoderTest_1680, SetDirtyTrue_1680) {
    PrimaryGroups primaryGroups;
    TiffEncoder encoder(exifData_, iptcData_, xmpData_, nullptr, false,
                        std::move(primaryGroups), header_.get(), nullptr);
    encoder.setDirty(true);
    EXPECT_TRUE(encoder.dirty());
}

// Test setDirty can toggle back to false
TEST_F(TiffEncoderTest_1680, SetDirtyFalseAfterTrue_1680) {
    PrimaryGroups primaryGroups;
    TiffEncoder encoder(exifData_, iptcData_, xmpData_, nullptr, false,
                        std::move(primaryGroups), header_.get(), nullptr);
    encoder.setDirty(true);
    EXPECT_TRUE(encoder.dirty());
    encoder.setDirty(false);
    EXPECT_FALSE(encoder.dirty());
}

// Test byte order is inherited from header
TEST_F(TiffEncoderTest_1680, ByteOrderFromHeader_1680) {
    PrimaryGroups primaryGroups;
    TiffEncoder encoder(exifData_, iptcData_, xmpData_, nullptr, false,
                        std::move(primaryGroups), header_.get(), nullptr);
    EXPECT_EQ(encoder.byteOrder(), littleEndian);
}

// Test writeMethod defaults to non-intrusive
TEST_F(TiffEncoderTest_1680, WriteMethodDefaultNonIntrusive_1680) {
    PrimaryGroups primaryGroups;
    TiffEncoder encoder(exifData_, iptcData_, xmpData_, nullptr, false,
                        std::move(primaryGroups), header_.get(), nullptr);
    EXPECT_EQ(encoder.writeMethod(), wmNonIntrusive);
}

// Test construction with isNewImage = true
TEST_F(TiffEncoderTest_1680, ConstructorWithNewImage_1680) {
    PrimaryGroups primaryGroups;
    TiffEncoder encoder(exifData_, iptcData_, xmpData_, nullptr, true,
                        std::move(primaryGroups), header_.get(), nullptr);
    // Should still start clean
    EXPECT_FALSE(encoder.dirty());
}

// Test encodeBinaryArray with nullptr datum doesn't crash
TEST_F(TiffEncoderTest_1680, EncodeBinaryArrayNullDatum_1680) {
    PrimaryGroups primaryGroups;
    TiffEncoder encoder(exifData_, iptcData_, xmpData_, nullptr, false,
                        std::move(primaryGroups), header_.get(), nullptr);

    ArrayCfg arrayCfg{IfdId::ifd0Id, littleEndian, ttUndefined, nullptr, false};
    TiffBinaryArray binaryArray(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);

    // Calling with null datum - should not crash
    EXPECT_NO_THROW(encoder.encodeBinaryArray(&binaryArray, nullptr));
}

// Test TiffBinaryArray basic properties
TEST(TiffBinaryArrayTest_1680, BasicConstruction_1680) {
    ArrayCfg arrayCfg{IfdId::ifd0Id, littleEndian, ttUndefined, nullptr, false};
    TiffBinaryArray binaryArray(0x0042, IfdId::ifd0Id, arrayCfg, nullptr, 0);

    EXPECT_EQ(binaryArray.cfg(), &arrayCfg);
    EXPECT_EQ(binaryArray.def(), nullptr);
    EXPECT_EQ(binaryArray.defSize(), 0u);
    EXPECT_FALSE(binaryArray.decoded());
}

// Test TiffBinaryArray setDecoded
TEST(TiffBinaryArrayTest_1680, SetDecoded_1680) {
    ArrayCfg arrayCfg{IfdId::ifd0Id, littleEndian, ttUndefined, nullptr, false};
    TiffBinaryArray binaryArray(0x0042, IfdId::ifd0Id, arrayCfg, nullptr, 0);

    binaryArray.setDecoded(true);
    EXPECT_TRUE(binaryArray.decoded());

    binaryArray.setDecoded(false);
    EXPECT_FALSE(binaryArray.decoded());
}

// Test TiffBinaryArray with ArrayDef
TEST(TiffBinaryArrayTest_1680, ConstructionWithArrayDef_1680) {
    ArrayCfg arrayCfg{IfdId::ifd0Id, littleEndian, ttUndefined, nullptr, false};
    ArrayDef arrayDef{0, ttUnsignedByte, 1};
    TiffBinaryArray binaryArray(0x0042, IfdId::ifd0Id, arrayCfg, &arrayDef, 1);

    EXPECT_EQ(binaryArray.def(), &arrayDef);
    EXPECT_EQ(binaryArray.defSize(), 1u);
}

// Test encodeBinaryArray with valid Exifdatum
TEST_F(TiffEncoderTest_1680, EncodeBinaryArrayWithDatum_1680) {
    PrimaryGroups primaryGroups;
    TiffEncoder encoder(exifData_, iptcData_, xmpData_, nullptr, false,
                        std::move(primaryGroups), header_.get(), nullptr);

    ArrayCfg arrayCfg{IfdId::ifd0Id, littleEndian, ttUndefined, nullptr, false};
    TiffBinaryArray binaryArray(0x0001, IfdId::ifd0Id, arrayCfg, nullptr, 0);

    ExifKey key("Exif.Image.ImageWidth");
    Exifdatum datum(key);
    datum = uint32_t(100);

    // Should not throw
    EXPECT_NO_THROW(encoder.encodeBinaryArray(&binaryArray, &datum));
}

// Test multiple setDirty calls
TEST_F(TiffEncoderTest_1680, MultipleDirtyToggle_1680) {
    PrimaryGroups primaryGroups;
    TiffEncoder encoder(exifData_, iptcData_, xmpData_, nullptr, false,
                        std::move(primaryGroups), header_.get(), nullptr);

    for (int i = 0; i < 10; ++i) {
        encoder.setDirty(true);
        EXPECT_TRUE(encoder.dirty());
        encoder.setDirty(false);
        EXPECT_FALSE(encoder.dirty());
    }
}

}  // namespace
