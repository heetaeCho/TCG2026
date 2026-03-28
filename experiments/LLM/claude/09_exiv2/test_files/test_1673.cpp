#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to create a minimal TiffHeader for the encoder
class MinimalTiffHeader : public TiffHeaderBase {
public:
    MinimalTiffHeader() : TiffHeaderBase(42, 8, littleEndian, 8) {}
    ~MinimalTiffHeader() override = default;
    
    bool read(const byte* pData, size_t size) override { return true; }
    DataBuf write() const override { return DataBuf(); }
};

// A test fixture for TiffEncoder tests
class TiffEncoderTest_1673 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<MinimalTiffHeader>();
    }

    std::unique_ptr<MinimalTiffHeader> header_;
};

// Test that TiffEncoder can be constructed and dirty flag defaults to false
TEST_F(TiffEncoderTest_1673, InitialDirtyIsFalse_1673) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    
    // Create a minimal root component
    auto pRoot = new TiffDirectory(Tag::root, IfdId::ifdIdNotSet);
    
    PrimaryGroups primaryGroups;
    
    TiffEncoder encoder(
        exifData,
        iptcData,
        xmpData,
        pRoot,
        false,  // isNewImage
        std::move(primaryGroups),
        header_.get(),
        nullptr  // findEncoderFct
    );
    
    EXPECT_FALSE(encoder.dirty());
    
    delete pRoot;
}

// Test setDirty changes the dirty flag
TEST_F(TiffEncoderTest_1673, SetDirtyTrue_1673) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    
    auto pRoot = new TiffDirectory(Tag::root, IfdId::ifdIdNotSet);
    PrimaryGroups primaryGroups;
    
    TiffEncoder encoder(
        exifData,
        iptcData,
        xmpData,
        pRoot,
        false,
        std::move(primaryGroups),
        header_.get(),
        nullptr
    );
    
    encoder.setDirty(true);
    EXPECT_TRUE(encoder.dirty());
    
    delete pRoot;
}

// Test setDirty can toggle back to false
TEST_F(TiffEncoderTest_1673, SetDirtyFalseAfterTrue_1673) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    
    auto pRoot = new TiffDirectory(Tag::root, IfdId::ifdIdNotSet);
    PrimaryGroups primaryGroups;
    
    TiffEncoder encoder(
        exifData,
        iptcData,
        xmpData,
        pRoot,
        false,
        std::move(primaryGroups),
        header_.get(),
        nullptr
    );
    
    encoder.setDirty(true);
    EXPECT_TRUE(encoder.dirty());
    encoder.setDirty(false);
    EXPECT_FALSE(encoder.dirty());
    
    delete pRoot;
}

// Test byteOrder returns the header's byte order
TEST_F(TiffEncoderTest_1673, ByteOrderMatchesHeader_1673) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    
    auto pRoot = new TiffDirectory(Tag::root, IfdId::ifdIdNotSet);
    PrimaryGroups primaryGroups;
    
    TiffEncoder encoder(
        exifData,
        iptcData,
        xmpData,
        pRoot,
        false,
        std::move(primaryGroups),
        header_.get(),
        nullptr
    );
    
    EXPECT_EQ(encoder.byteOrder(), littleEndian);
    
    delete pRoot;
}

// Test writeMethod defaults to wmNonIntrusive
TEST_F(TiffEncoderTest_1673, DefaultWriteMethodIsNonIntrusive_1673) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    
    auto pRoot = new TiffDirectory(Tag::root, IfdId::ifdIdNotSet);
    PrimaryGroups primaryGroups;
    
    TiffEncoder encoder(
        exifData,
        iptcData,
        xmpData,
        pRoot,
        false,
        std::move(primaryGroups),
        header_.get(),
        nullptr
    );
    
    EXPECT_EQ(encoder.writeMethod(), wmNonIntrusive);
    
    delete pRoot;
}

// Test visitSubIfd with a TiffSubIfd object doesn't crash
TEST_F(TiffEncoderTest_1673, VisitSubIfdDoesNotCrash_1673) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    
    auto pRoot = new TiffDirectory(Tag::root, IfdId::ifdIdNotSet);
    PrimaryGroups primaryGroups;
    
    TiffEncoder encoder(
        exifData,
        iptcData,
        xmpData,
        pRoot,
        false,
        std::move(primaryGroups),
        header_.get(),
        nullptr
    );
    
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    
    // visitSubIfd should not crash when called with a valid TiffSubIfd
    EXPECT_NO_THROW(encoder.visitSubIfd(&subIfd));
    
    delete pRoot;
}

// Test visitSubIfd with new image flag set
TEST_F(TiffEncoderTest_1673, VisitSubIfdNewImage_1673) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    
    auto pRoot = new TiffDirectory(Tag::root, IfdId::ifdIdNotSet);
    PrimaryGroups primaryGroups;
    
    TiffEncoder encoder(
        exifData,
        iptcData,
        xmpData,
        pRoot,
        true,  // isNewImage
        std::move(primaryGroups),
        header_.get(),
        nullptr
    );
    
    TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    
    EXPECT_NO_THROW(encoder.visitSubIfd(&subIfd));
    
    delete pRoot;
}

// Test visitDirectory does not crash
TEST_F(TiffEncoderTest_1673, VisitDirectoryDoesNotCrash_1673) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    
    auto pRoot = new TiffDirectory(Tag::root, IfdId::ifdIdNotSet);
    PrimaryGroups primaryGroups;
    
    TiffEncoder encoder(
        exifData,
        iptcData,
        xmpData,
        pRoot,
        false,
        std::move(primaryGroups),
        header_.get(),
        nullptr
    );
    
    TiffDirectory dir(Tag::root, IfdId::ifd0Id);
    
    EXPECT_NO_THROW(encoder.visitDirectory(&dir));
    
    delete pRoot;
}

// Test construction with empty exif/iptc/xmp data
TEST_F(TiffEncoderTest_1673, ConstructWithEmptyData_1673) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    
    auto pRoot = new TiffDirectory(Tag::root, IfdId::ifdIdNotSet);
    PrimaryGroups primaryGroups;
    
    EXPECT_NO_THROW({
        TiffEncoder encoder(
            exifData,
            iptcData,
            xmpData,
            pRoot,
            false,
            std::move(primaryGroups),
            header_.get(),
            nullptr
        );
    });
    
    delete pRoot;
}

// Test TiffSubIfd construction
TEST(TiffSubIfdTest_1673, ConstructionDoesNotThrow_1673) {
    EXPECT_NO_THROW({
        TiffSubIfd subIfd(0x014a, IfdId::ifd0Id, IfdId::subImage1Id);
    });
}

// Test TiffSubIfd with different tag values
TEST(TiffSubIfdTest_1673, DifferentTagValues_1673) {
    EXPECT_NO_THROW({
        TiffSubIfd subIfd1(0x0000, IfdId::ifd0Id, IfdId::subImage1Id);
        TiffSubIfd subIfd2(0xFFFF, IfdId::ifd0Id, IfdId::subImage1Id);
    });
}

// Test multiple setDirty calls
TEST_F(TiffEncoderTest_1673, MultipleSetDirtyCalls_1673) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    
    auto pRoot = new TiffDirectory(Tag::root, IfdId::ifdIdNotSet);
    PrimaryGroups primaryGroups;
    
    TiffEncoder encoder(
        exifData,
        iptcData,
        xmpData,
        pRoot,
        false,
        std::move(primaryGroups),
        header_.get(),
        nullptr
    );
    
    // Multiple calls should work without issues
    for (int i = 0; i < 10; ++i) {
        encoder.setDirty(true);
        EXPECT_TRUE(encoder.dirty());
        encoder.setDirty(false);
        EXPECT_FALSE(encoder.dirty());
    }
    
    delete pRoot;
}

// Test visitDirectoryNext does not crash
TEST_F(TiffEncoderTest_1673, VisitDirectoryNextDoesNotCrash_1673) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    
    auto pRoot = new TiffDirectory(Tag::root, IfdId::ifdIdNotSet);
    PrimaryGroups primaryGroups;
    
    TiffEncoder encoder(
        exifData,
        iptcData,
        xmpData,
        pRoot,
        false,
        std::move(primaryGroups),
        header_.get(),
        nullptr
    );
    
    TiffDirectory dir(Tag::root, IfdId::ifd0Id);
    
    EXPECT_NO_THROW(encoder.visitDirectoryNext(&dir));
    
    delete pRoot;
}
