#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// Helper to create a minimal TiffHeader for encoder construction
class TestTiffHeader : public TiffHeaderBase {
public:
    TestTiffHeader() : TiffHeaderBase(42, 8, littleEndian, 0) {}
    ~TestTiffHeader() override = default;
};

// Helper function that acts as a FindEncoderFct
EncoderFct testFindEncoderFct(uint16_t, IfdId, bool) {
    return nullptr;
}

// Fixture that sets up a TiffEncoder with minimal dependencies
class TiffEncoderTest_1683 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<TestTiffHeader>();
        root_ = new TiffDirectory(0x0000, IfdId::ifd0Id);
        PrimaryGroups primaryGroups;
        primaryGroups.push_back(IfdId::ifd0Id);

        encoder_ = std::make_unique<TiffEncoder>(
            ExifData(),
            iptcData_,
            xmpData_,
            root_,
            false,
            std::move(primaryGroups),
            header_.get(),
            testFindEncoderFct
        );
    }

    void TearDown() override {
        encoder_.reset();
        delete root_;
    }

    ExifData exifData_;
    IptcData iptcData_;
    XmpData xmpData_;
    std::unique_ptr<TestTiffHeader> header_;
    TiffDirectory* root_ = nullptr;
    std::unique_ptr<TiffEncoder> encoder_;
};

// Test that dirty flag is initially false
TEST_F(TiffEncoderTest_1683, DirtyInitiallyFalse_1683) {
    EXPECT_FALSE(encoder_->dirty());
}

// Test setDirty with true
TEST_F(TiffEncoderTest_1683, SetDirtyTrue_1683) {
    encoder_->setDirty(true);
    EXPECT_TRUE(encoder_->dirty());
}

// Test setDirty with false after setting to true
TEST_F(TiffEncoderTest_1683, SetDirtyFalseThenTrue_1683) {
    encoder_->setDirty(true);
    EXPECT_TRUE(encoder_->dirty());
    encoder_->setDirty(false);
    EXPECT_FALSE(encoder_->dirty());
}

// Test setDirty toggle multiple times
TEST_F(TiffEncoderTest_1683, SetDirtyToggle_1683) {
    encoder_->setDirty(false);
    EXPECT_FALSE(encoder_->dirty());
    encoder_->setDirty(true);
    EXPECT_TRUE(encoder_->dirty());
    encoder_->setDirty(true);
    EXPECT_TRUE(encoder_->dirty());
    encoder_->setDirty(false);
    EXPECT_FALSE(encoder_->dirty());
}

// Test byteOrder returns the header's byte order
TEST_F(TiffEncoderTest_1683, ByteOrderMatchesHeader_1683) {
    EXPECT_EQ(encoder_->byteOrder(), littleEndian);
}

// Test writeMethod initial value is non-intrusive
TEST_F(TiffEncoderTest_1683, WriteMethodInitiallyNonIntrusive_1683) {
    EXPECT_EQ(encoder_->writeMethod(), wmNonIntrusive);
}

// Test encodeTiffEntry with null datum does not crash
TEST_F(TiffEncoderTest_1683, EncodeTiffEntryNullDatum_1683) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    EXPECT_NO_THROW(encoder_->encodeTiffEntry(&entry, nullptr));
}

// Test encodeTiffEntry with a valid datum
TEST_F(TiffEncoderTest_1683, EncodeTiffEntryWithDatum_1683) {
    TiffEntry entry(0x010e, IfdId::ifd0Id);  // ImageDescription tag
    ExifKey key("Exif.Image.ImageDescription");
    Exifdatum datum(key, nullptr);
    datum.setValue("Test description");
    EXPECT_NO_THROW(encoder_->encodeTiffEntry(&entry, &datum));
}

// Test encodeTiffComponent with null datum
TEST_F(TiffEncoderTest_1683, EncodeTiffComponentNullDatum_1683) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    EXPECT_NO_THROW(encoder_->encodeTiffComponent(&entry, nullptr));
}

// Test visitEntry does not crash on a basic TiffEntry
TEST_F(TiffEncoderTest_1683, VisitEntryBasic_1683) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    EXPECT_NO_THROW(encoder_->visitEntry(&entry));
}

// Test that creating encoder as new image
class TiffEncoderNewImageTest_1683 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<TestTiffHeader>();
        root_ = new TiffDirectory(0x0000, IfdId::ifd0Id);
        PrimaryGroups primaryGroups;
        primaryGroups.push_back(IfdId::ifd0Id);

        encoder_ = std::make_unique<TiffEncoder>(
            ExifData(),
            iptcData_,
            xmpData_,
            root_,
            true,  // isNewImage
            std::move(primaryGroups),
            header_.get(),
            testFindEncoderFct
        );
    }

    void TearDown() override {
        encoder_.reset();
        delete root_;
    }

    IptcData iptcData_;
    XmpData xmpData_;
    std::unique_ptr<TestTiffHeader> header_;
    TiffDirectory* root_ = nullptr;
    std::unique_ptr<TiffEncoder> encoder_;
};

// Test new image encoder starts not dirty
TEST_F(TiffEncoderNewImageTest_1683, NewImageNotDirtyInitially_1683) {
    EXPECT_FALSE(encoder_->dirty());
}

// Test new image encoder byte order
TEST_F(TiffEncoderNewImageTest_1683, NewImageByteOrder_1683) {
    EXPECT_EQ(encoder_->byteOrder(), littleEndian);
}

// Test encodeTiffEntryBase with null datum
TEST_F(TiffEncoderTest_1683, EncodeTiffEntryBaseNullDatum_1683) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    EXPECT_NO_THROW(encoder_->encodeTiffEntryBase(&entry, nullptr));
}

// Test visitDirectory does not crash
TEST_F(TiffEncoderTest_1683, VisitDirectoryBasic_1683) {
    TiffDirectory dir(0x0000, IfdId::ifd0Id);
    EXPECT_NO_THROW(encoder_->visitDirectory(&dir));
}

// Test visitDirectoryNext
TEST_F(TiffEncoderTest_1683, VisitDirectoryNextBasic_1683) {
    TiffDirectory dir(0x0000, IfdId::ifd0Id);
    EXPECT_NO_THROW(encoder_->visitDirectoryNext(&dir));
}

} // namespace
