#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// A minimal TiffHeader implementation for testing
class TestTiffHeader : public TiffHeaderBase {
public:
    TestTiffHeader()
        : TiffHeaderBase(42, 8, littleEndian, 0x002a) {}
};

// Helper to find encoder function (default)
const TiffMappingInfo* testFindEncoderFct(const std::string& make,
                                           int tag,
                                           IfdId group) {
    return nullptr;
}

class TiffEncoderTest_1669 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<TestTiffHeader>();
    }

    std::unique_ptr<TiffEncoder> createEncoder(
        ExifData exifData = ExifData(),
        const IptcData& iptcData = IptcData(),
        const XmpData& xmpData = XmpData(),
        TiffComponent* pRoot = nullptr,
        bool isNewImage = false) {
        PrimaryGroups primaryGroups;
        return std::make_unique<TiffEncoder>(
            std::move(exifData),
            iptcData,
            xmpData,
            pRoot,
            isNewImage,
            std::move(primaryGroups),
            header_.get(),
            testFindEncoderFct);
    }

    std::unique_ptr<TestTiffHeader> header_;
};

// Test that dirty flag is initially false
TEST_F(TiffEncoderTest_1669, DirtyInitiallyFalse_1669) {
    auto encoder = createEncoder();
    EXPECT_FALSE(encoder->dirty());
}

// Test that setDirty(true) makes dirty() return true
TEST_F(TiffEncoderTest_1669, SetDirtyTrue_1669) {
    auto encoder = createEncoder();
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
}

// Test that setDirty(false) makes dirty() return false
TEST_F(TiffEncoderTest_1669, SetDirtyFalse_1669) {
    auto encoder = createEncoder();
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
}

// Test that setDirty can toggle multiple times
TEST_F(TiffEncoderTest_1669, SetDirtyToggle_1669) {
    auto encoder = createEncoder();
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
}

// Test byteOrder returns the header's byte order
TEST_F(TiffEncoderTest_1669, ByteOrderMatchesHeader_1669) {
    auto encoder = createEncoder();
    EXPECT_EQ(littleEndian, encoder->byteOrder());
}

// Test writeMethod default is wmNonIntrusive
TEST_F(TiffEncoderTest_1669, WriteMethodDefaultNonIntrusive_1669) {
    auto encoder = createEncoder();
    EXPECT_EQ(wmNonIntrusive, encoder->writeMethod());
}

// Test visitDataEntry with nullptr does not crash (boundary)
TEST_F(TiffEncoderTest_1669, VisitDataEntryNullptr_1669) {
    auto encoder = createEncoder();
    // Passing nullptr may cause undefined behavior in production code,
    // but we test that a valid TiffDataEntry can be visited
    // We'll use a properly constructed TiffDataEntry instead
    TiffDataEntry dataEntry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);
    // This should not throw for a default-constructed entry with no matching exif data
    EXPECT_NO_THROW(encoder->visitDataEntry(&dataEntry));
}

// Test that visiting a data entry on a new image encoder doesn't crash
TEST_F(TiffEncoderTest_1669, VisitDataEntryNewImage_1669) {
    auto encoder = createEncoder(ExifData(), IptcData(), XmpData(), nullptr, true);
    TiffDataEntry dataEntry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);
    EXPECT_NO_THROW(encoder->visitDataEntry(&dataEntry));
}

// Test that visiting a data entry with matching exif data
TEST_F(TiffEncoderTest_1669, VisitDataEntryWithExifData_1669) {
    ExifData exifData;
    exifData["Exif.Image.StripOffsets"] = uint32_t(0);
    auto encoder = createEncoder(exifData);
    TiffDataEntry dataEntry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);
    EXPECT_NO_THROW(encoder->visitDataEntry(&dataEntry));
}

// Test encoder with empty ExifData, IptcData, XmpData
TEST_F(TiffEncoderTest_1669, EncoderWithEmptyData_1669) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;
    auto encoder = createEncoder(exifData, iptcData, xmpData);
    EXPECT_FALSE(encoder->dirty());
    EXPECT_EQ(littleEndian, encoder->byteOrder());
}

// Test that creating encoder and checking state is consistent
TEST_F(TiffEncoderTest_1669, EncoderConsistentState_1669) {
    auto encoder = createEncoder();
    EXPECT_FALSE(encoder->dirty());
    EXPECT_EQ(wmNonIntrusive, encoder->writeMethod());
    EXPECT_EQ(littleEndian, encoder->byteOrder());
}

// Test multiple visitDataEntry calls don't accumulate errors
TEST_F(TiffEncoderTest_1669, MultipleVisitDataEntryCalls_1669) {
    auto encoder = createEncoder();
    TiffDataEntry dataEntry1(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);
    TiffDataEntry dataEntry2(0x0201, IfdId::ifd1Id, 0x0202, IfdId::ifd1Id);
    EXPECT_NO_THROW(encoder->visitDataEntry(&dataEntry1));
    EXPECT_NO_THROW(encoder->visitDataEntry(&dataEntry2));
}

}  // namespace
