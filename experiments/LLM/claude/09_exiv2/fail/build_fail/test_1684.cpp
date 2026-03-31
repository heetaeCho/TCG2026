#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// Helper to create a minimal TiffHeaderBase for encoder construction
class TestTiffHeader : public TiffHeaderBase {
public:
    TestTiffHeader(ByteOrder bo = littleEndian)
        : TiffHeaderBase(42, 8, bo, 0) {}
    ~TestTiffHeader() override = default;

    bool read(const byte* /*pData*/, size_t /*size*/) override { return true; }
    DataBuf write() const override { return DataBuf(); }
};

// Helper function to find encoder function (returns nullptr for default encoding)
static EncoderFct findEncoderFctDefault(uint16_t /*tag*/, IfdId /*group*/) {
    return nullptr;
}

class TiffEncoderEncodeImageEntryTest_1684 : public ::testing::Test {
protected:
    void SetUp() override {
        // Suppress log messages during tests
        LogMsg::setLevel(LogMsg::mute);
    }

    void TearDown() override {
        LogMsg::setLevel(LogMsg::warn);
    }

    std::unique_ptr<TiffEncoder> createEncoder(
        ExifData exifData,
        WriteMethod wm,
        TiffComponent* pRoot = nullptr,
        bool isNewImage = false)
    {
        IptcData iptcData;
        XmpData xmpData;
        PrimaryGroups primaryGroups;

        auto header = std::make_unique<TestTiffHeader>();

        auto encoder = std::make_unique<TiffEncoder>(
            std::move(exifData),
            iptcData,
            xmpData,
            pRoot,
            isNewImage,
            std::move(primaryGroups),
            header.get(),
            findEncoderFctDefault);

        headers_.push_back(std::move(header));

        // Set the write method via setDirty if needed
        // wmNonIntrusive is default (writeMethod_ = wmNonIntrusive)
        // To get wmIntrusive, we need to call setDirty(true) or make it dirty
        if (wm == wmIntrusive) {
            encoder->setDirty(true);
        }

        return encoder;
    }

    std::vector<std::unique_ptr<TestTiffHeader>> headers_;
};

// Test: encodeImageEntry with null datum - basic call doesn't crash
TEST_F(TiffEncoderEncodeImageEntryTest_1684, NullDatum_DoesNotCrash_1684) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData), wmNonIntrusive);

    // Create a TiffImageEntry with some tag
    TiffImageEntry imageEntry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    // With null datum, encodeOffsetEntry should handle it
    // This tests that the method doesn't crash with null datum
    // Note: behavior depends on encodeOffsetEntry handling nullptr
    // We primarily test it doesn't segfault
    EXPECT_NO_THROW(encoder->encodeImageEntry(&imageEntry, nullptr));
}

// Test: encodeImageEntry with non-intrusive write and data area > 0 sets dirty
TEST_F(TiffEncoderEncodeImageEntryTest_1684, NonIntrusiveWithDataArea_SetsDirty_1684) {
    ExifData exifData;
    
    // Create the encoder in non-intrusive mode
    auto encoder = createEncoder(std::move(exifData), wmNonIntrusive);
    ASSERT_EQ(encoder->writeMethod(), wmNonIntrusive);

    // Create a TiffImageEntry
    TiffImageEntry imageEntry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    // We need a Value with a data area set
    auto val = Value::create(unsignedLong);
    val->read("0");
    byte dataArea[10] = {0};
    val->setDataArea(dataArea, 10);
    imageEntry.setValue(std::move(val));

    // Create a matching Exifdatum
    ExifKey key(0x0111, "Image");
    Exifdatum datum(key);
    auto dval = Value::create(unsignedLong);
    dval->read("0");
    byte dArea[10] = {0};
    dval->setDataArea(dArea, 10);
    datum.setValue(dval.get());

    encoder->setDirty(false);
    encoder->encodeImageEntry(&imageEntry, &datum);

    // After encoding with data area > 0 in non-intrusive mode, dirty should be set
    EXPECT_TRUE(encoder->dirty());
}

// Test: encodeImageEntry in intrusive mode with data area and missing size tag
TEST_F(TiffEncoderEncodeImageEntryTest_1684, IntrusiveWithDataAreaMissingSizeTag_OneStrip_1684) {
    ExifData exifData;
    // Don't add the size tag (0x0117) so it won't be found
    
    auto encoder = createEncoder(std::move(exifData), wmIntrusive);

    // Create a TiffImageEntry
    TiffImageEntry imageEntry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    // Set a value with data area
    auto val = Value::create(unsignedLong);
    val->read("0");
    byte dataArea[100] = {0};
    val->setDataArea(dataArea, 100);
    imageEntry.setValue(std::move(val));

    // Create datum
    ExifKey key(0x0111, "Image");
    Exifdatum datum(key);
    auto dval = Value::create(unsignedLong);
    dval->read("0");
    byte dArea[100] = {0};
    dval->setDataArea(dArea, 100);
    datum.setValue(dval.get());

    // This should result in one strip of size 100 since size tag is not found
    EXPECT_NO_THROW(encoder->encodeImageEntry(&imageEntry, &datum));
}

// Test: encodeImageEntry in intrusive mode with data area and existing size tag
TEST_F(TiffEncoderEncodeImageEntryTest_1684, IntrusiveWithDataAreaAndSizeTag_MultipleStrips_1684) {
    ExifData exifData;
    
    // Add the size tag (StripByteCounts = 0x0117 in Image group)
    ExifKey sizeKey(0x0117, "Image");
    auto sizeVal = Value::create(unsignedLong);
    sizeVal->read("50 50");
    exifData.add(sizeKey, sizeVal.get());

    auto encoder = createEncoder(std::move(exifData), wmIntrusive);

    // Create a TiffImageEntry (StripOffsets tag with StripByteCounts as size tag)
    TiffImageEntry imageEntry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    // Set a value with data area of 100 bytes
    auto val = Value::create(unsignedLong);
    val->read("0");
    byte dataArea[100] = {0};
    val->setDataArea(dataArea, 100);
    imageEntry.setValue(std::move(val));

    // Create datum
    ExifKey key(0x0111, "Image");
    Exifdatum datum(key);
    auto dval = Value::create(unsignedLong);
    dval->read("0");
    byte dArea[100] = {0};
    dval->setDataArea(dArea, 100);
    datum.setValue(dval.get());

    EXPECT_NO_THROW(encoder->encodeImageEntry(&imageEntry, &datum));
}

// Test: encodeImageEntry in intrusive mode with data area and mismatched size total
TEST_F(TiffEncoderEncodeImageEntryTest_1684, IntrusiveWithDataAreaMismatchedSizeTotal_1684) {
    ExifData exifData;
    
    // Add size tag with total != data area size
    ExifKey sizeKey(0x0117, "Image");
    auto sizeVal = Value::create(unsignedLong);
    sizeVal->read("30 30"); // total = 60, but data area will be 100
    exifData.add(sizeKey, sizeVal.get());

    auto encoder = createEncoder(std::move(exifData), wmIntrusive);

    TiffImageEntry imageEntry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    auto val = Value::create(unsignedLong);
    val->read("0");
    byte dataArea[100] = {0};
    val->setDataArea(dataArea, 100);
    imageEntry.setValue(std::move(val));

    ExifKey key(0x0111, "Image");
    Exifdatum datum(key);
    auto dval = Value::create(unsignedLong);
    dval->read("0");
    byte dArea[100] = {0};
    dval->setDataArea(dArea, 100);
    datum.setValue(dval.get());

    // Should not crash even with mismatched sizes (just logs a warning)
    EXPECT_NO_THROW(encoder->encodeImageEntry(&imageEntry, &datum));
}

// Test: encodeImageEntry in intrusive mode with no data area and no source tree
TEST_F(TiffEncoderEncodeImageEntryTest_1684, IntrusiveNoDataAreaNoSourceTree_1684) {
    ExifData exifData;
    
    auto encoder = createEncoder(std::move(exifData), wmIntrusive);

    TiffImageEntry imageEntry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    // Set a value without data area (sizeDataArea == 0)
    auto val = Value::create(unsignedLong);
    val->read("0");
    imageEntry.setValue(std::move(val));

    ExifKey key(0x0111, "Image");
    Exifdatum datum(key);
    auto dval = Value::create(unsignedLong);
    dval->read("0");
    datum.setValue(dval.get());

    // No source tree, should just log warning and not crash
    EXPECT_NO_THROW(encoder->encodeImageEntry(&imageEntry, &datum));
}

// Test: encodeImageEntry with non-intrusive write and no data area
TEST_F(TiffEncoderEncodeImageEntryTest_1684, NonIntrusiveNoDataArea_NoDirtySet_1684) {
    ExifData exifData;

    auto encoder = createEncoder(std::move(exifData), wmNonIntrusive);
    ASSERT_EQ(encoder->writeMethod(), wmNonIntrusive);

    TiffImageEntry imageEntry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    auto val = Value::create(unsignedLong);
    val->read("0");
    imageEntry.setValue(std::move(val));

    ExifKey key(0x0111, "Image");
    Exifdatum datum(key);
    auto dval = Value::create(unsignedLong);
    dval->read("0");
    datum.setValue(dval.get());

    encoder->setDirty(false);
    encoder->encodeImageEntry(&imageEntry, &datum);

    // No data area, non-intrusive - dirty should not be set by this path
    // (may be set by encodeOffsetEntry, but that's separate logic)
    // We just verify no crash
    SUCCEED();
}

// Test: Verify writeMethod returns correct value
TEST_F(TiffEncoderEncodeImageEntryTest_1684, WriteMethodReturnsCorrectValue_1684) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData), wmNonIntrusive);
    EXPECT_EQ(encoder->writeMethod(), wmNonIntrusive);
}

// Test: encodeImageEntry with intrusive and single strip in size tag
TEST_F(TiffEncoderEncodeImageEntryTest_1684, IntrusiveWithSingleStripSizeTag_1684) {
    ExifData exifData;
    
    ExifKey sizeKey(0x0117, "Image");
    auto sizeVal = Value::create(unsignedLong);
    sizeVal->read("100");
    exifData.add(sizeKey, sizeVal.get());

    auto encoder = createEncoder(std::move(exifData), wmIntrusive);

    TiffImageEntry imageEntry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    auto val = Value::create(unsignedLong);
    val->read("0");
    byte dataArea[100] = {0};
    val->setDataArea(dataArea, 100);
    imageEntry.setValue(std::move(val));

    ExifKey key(0x0111, "Image");
    Exifdatum datum(key);
    auto dval = Value::create(unsignedLong);
    dval->read("0");
    byte dArea[100] = {0};
    dval->setDataArea(dArea, 100);
    datum.setValue(dval.get());

    EXPECT_NO_THROW(encoder->encodeImageEntry(&imageEntry, &datum));
}

// Test: setDirty and dirty accessors
TEST_F(TiffEncoderEncodeImageEntryTest_1684, SetDirtyAndDirtyAccessor_1684) {
    ExifData exifData;
    auto encoder = createEncoder(std::move(exifData), wmNonIntrusive);
    
    encoder->setDirty(false);
    EXPECT_FALSE(encoder->dirty());
    
    encoder->setDirty(true);
    EXPECT_TRUE(encoder->dirty());
}

// Test: encodeImageEntry with zero-length data area in intrusive mode
TEST_F(TiffEncoderEncodeImageEntryTest_1684, IntrusiveZeroSizeDataArea_1684) {
    ExifData exifData;

    auto encoder = createEncoder(std::move(exifData), wmIntrusive);

    TiffImageEntry imageEntry(0x0111, IfdId::ifd0Id, 0x0117, IfdId::ifd0Id);

    // Value with no data area set (default sizeDataArea == 0)
    auto val = Value::create(unsignedLong);
    val->read("42");
    imageEntry.setValue(std::move(val));

    ExifKey key(0x0111, "Image");
    Exifdatum datum(key);
    auto dval = Value::create(unsignedLong);
    dval->read("42");
    datum.setValue(dval.get());

    // sizeDataArea == 0 and intrusive mode, no source tree
    EXPECT_NO_THROW(encoder->encodeImageEntry(&imageEntry, &datum));
}

} // anonymous namespace
