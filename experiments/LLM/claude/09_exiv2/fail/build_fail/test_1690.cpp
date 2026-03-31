#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exif.hpp"
#include "exiv2/types.hpp"
#include "exiv2/tags.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Helper to create a minimal TiffHeader for TiffEncoder construction
class MinimalTiffHeader : public TiffHeaderBase {
public:
    MinimalTiffHeader(ByteOrder bo = littleEndian)
        : TiffHeaderBase(42, 8, bo, 0) {}
    ~MinimalTiffHeader() override = default;
    bool read(const byte* /*pData*/, size_t /*size*/) override { return true; }
    DataBuf write() const override { return DataBuf(); }
};

// Fixture for TiffEncoder tests
class TiffEncoderTest_1690 : public ::testing::Test {
protected:
    void SetUp() override {
        header_ = std::make_unique<MinimalTiffHeader>(littleEndian);
    }

    std::unique_ptr<TiffEncoder> createEncoder(ExifData exifData, bool isNewImage = false) {
        PrimaryGroups primaryGroups;
        return std::make_unique<TiffEncoder>(
            std::move(exifData),
            iptcData_,
            xmpData_,
            nullptr,  // pRoot
            isNewImage,
            std::move(primaryGroups),
            header_.get(),
            nullptr   // findEncoderFct
        );
    }

    IptcData iptcData_;
    XmpData xmpData_;
    std::unique_ptr<MinimalTiffHeader> header_;
};

// Test: Initial writeMethod should be wmNonIntrusive
TEST_F(TiffEncoderTest_1690, InitialWriteMethodIsNonIntrusive_1690) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData));
    EXPECT_EQ(encoder->writeMethod(), wmNonIntrusive);
}

// Test: Initial dirty flag should be false
TEST_F(TiffEncoderTest_1690, InitialDirtyIsFalse_1690) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData));
    EXPECT_FALSE(encoder->dirty());
}

// Test: setDirty sets the dirty flag to true
TEST_F(TiffEncoderTest_1690, SetDirtyTrue_1690) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData));
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
}

// Test: setDirty can reset the dirty flag to false
TEST_F(TiffEncoderTest_1690, SetDirtyFalseAfterTrue_1690) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData));
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
}

// Test: byteOrder returns the header's byte order
TEST_F(TiffEncoderTest_1690, ByteOrderMatchesHeader_1690) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData));
    EXPECT_EQ(encoder->byteOrder(), littleEndian);
}

// Test: byteOrder with bigEndian header
TEST_F(TiffEncoderTest_1690, ByteOrderBigEndian_1690) {
    header_ = std::make_unique<MinimalTiffHeader>(bigEndian);
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData));
    EXPECT_EQ(encoder->byteOrder(), bigEndian);
}

// Test: TiffFinder with default state returns null result
class TiffFinderTest_1690 : public ::testing::Test {};

TEST_F(TiffFinderTest_1690, DefaultResultIsNull_1690) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test: TiffFinder init resets the finder
TEST_F(TiffFinderTest_1690, InitResetsResult_1690) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    finder.init(0x0200, IfdId::exifId);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test: TiffComponent basic tag and group
class TiffComponentTest_1690 : public ::testing::Test {};

TEST_F(TiffComponentTest_1690, TiffEntryTagAndGroup_1690) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(entry.tag(), 0x0100);
    EXPECT_EQ(entry.group(), IfdId::ifd0Id);
}

// Test: TiffDirectory basic construction
TEST_F(TiffComponentTest_1690, TiffDirectoryTagAndGroup_1690) {
    TiffDirectory dir(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(dir.tag(), 0x0000);
    EXPECT_EQ(dir.group(), IfdId::ifd0Id);
}

// Test: TiffMnEntry construction
TEST_F(TiffComponentTest_1690, TiffMnEntryConstruction_1690) {
    TiffMnEntry mnEntry(0x927c, IfdId::exifId, IfdId::mnId);
    EXPECT_EQ(mnEntry.tag(), 0x927c);
    EXPECT_EQ(mnEntry.group(), IfdId::exifId);
}

// Test: ExifData operations for encoder scenarios
class ExifDataForEncoderTest_1690 : public ::testing::Test {};

TEST_F(ExifDataForEncoderTest_1690, EmptyExifData_1690) {
    ExifData exifData;
    EXPECT_TRUE(exifData.empty());
    EXPECT_EQ(exifData.count(), 0u);
}

TEST_F(ExifDataForEncoderTest_1690, AddAndFindExifdatum_1690) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestCamera";
    auto it = exifData.findKey(ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, exifData.end());
    EXPECT_EQ(it->toString(), "TestCamera");
}

TEST_F(ExifDataForEncoderTest_1690, AddMultipleEntries_1690) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestCamera";
    exifData["Exif.Image.Model"] = "TestModel";
    EXPECT_EQ(exifData.count(), 2u);
}

// Test: Encoder with empty ExifData - writeMethod stays non-intrusive before add
TEST_F(TiffEncoderTest_1690, WriteMethodBeforeAdd_1690) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData));
    EXPECT_EQ(encoder->writeMethod(), wmNonIntrusive);
}

// Test: TiffIfdMakernote basic construction and byte order
class TiffIfdMakernoteTest_1690 : public ::testing::Test {};

TEST_F(TiffIfdMakernoteTest_1690, DefaultByteOrder_1690) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::mnId, nullptr, false);
    EXPECT_EQ(mn.byteOrder(), invalidByteOrder);
}

TEST_F(TiffIfdMakernoteTest_1690, SetByteOrder_1690) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::mnId, nullptr, false);
    mn.setByteOrder(bigEndian);
    EXPECT_EQ(mn.byteOrder(), bigEndian);
}

TEST_F(TiffIfdMakernoteTest_1690, SetByteOrderLittleEndian_1690) {
    TiffIfdMakernote mn(0x927c, IfdId::exifId, IfdId::mnId, nullptr, false);
    mn.setByteOrder(littleEndian);
    EXPECT_EQ(mn.byteOrder(), littleEndian);
}

// Test: Repeated setDirty calls
TEST_F(TiffEncoderTest_1690, RepeatedSetDirty_1690) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData));
    encoder->setDirty(true);
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
    encoder->setDirty(false);
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
}

// Test: TiffFinder findObject with a matching entry
TEST_F(TiffFinderTest_1690, FindObjectMatchingEntry_1690) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    finder.findObject(&entry);
    EXPECT_EQ(finder.result(), &entry);
}

// Test: TiffFinder findObject with a non-matching entry
TEST_F(TiffFinderTest_1690, FindObjectNonMatchingEntry_1690) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    TiffEntry entry(0x0200, IfdId::ifd0Id);
    finder.findObject(&entry);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test: TiffFinder findObject with non-matching group
TEST_F(TiffFinderTest_1690, FindObjectNonMatchingGroup_1690) {
    TiffFinder finder(0x0100, IfdId::ifd0Id);
    TiffEntry entry(0x0100, IfdId::exifId);
    finder.findObject(&entry);
    EXPECT_EQ(finder.result(), nullptr);
}

// Test: TiffComponent start pointer
TEST_F(TiffComponentTest_1690, StartPointerDefault_1690) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    EXPECT_EQ(entry.start(), nullptr);
}

TEST_F(TiffComponentTest_1690, SetStartPointer_1690) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    byte data[10] = {};
    entry.setStart(data);
    EXPECT_EQ(entry.start(), data);
}

// Test: ExifData clear
TEST_F(ExifDataForEncoderTest_1690, ClearExifData_1690) {
    ExifData exifData;
    exifData["Exif.Image.Make"] = "TestCamera";
    EXPECT_FALSE(exifData.empty());
    exifData.clear();
    EXPECT_TRUE(exifData.empty());
}

// Test: Encoder constructed with new image flag
TEST_F(TiffEncoderTest_1690, ConstructWithNewImageFlag_1690) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData), true);
    EXPECT_FALSE(encoder->dirty());
    EXPECT_EQ(encoder->writeMethod(), wmNonIntrusive);
}
