#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "exiv2/exif.hpp"

namespace Exiv2 {
namespace Internal {

// Mock the TiffEncoder class for testing purposes
class MockTiffEncoder : public TiffEncoder {
public:
    MOCK_METHOD(void, encodeSizeEntry, (const TiffSizeEntry* entry, const Exifdatum* datum), (override));
    using TiffEncoder::TiffEncoder;  // Inherit constructors
};

class TiffSizeEntryTest : public ::testing::Test {
protected:
    uint16_t tag = 123;
    IfdId group = IfdId::IFD0;
    uint16_t dtTag = 456;
    IfdId dtGroup = IfdId::IFD1;
    TiffSizeEntry sizeEntry = TiffSizeEntry(tag, group, dtTag, dtGroup);
};

TEST_F(TiffSizeEntryTest, ConstructorInitializesCorrectly_355) {
    // Verify that the TiffSizeEntry is initialized correctly
    EXPECT_EQ(sizeEntry.dtTag(), dtTag);
    EXPECT_EQ(sizeEntry.dtGroup(), dtGroup);
}

TEST_F(TiffSizeEntryTest, DoEncodeCallsEncoderEncodeSizeEntry_355) {
    // Create a mock encoder and datum
    MockTiffEncoder mockEncoder(ExifData(), IptcData(), XmpData(), nullptr, true, PrimaryGroups(), nullptr, nullptr);
    Exifdatum datum(ExifKey(), Value());

    // Set up the expectation for the encoder call
    EXPECT_CALL(mockEncoder, encodeSizeEntry(&sizeEntry, &datum))
        .Times(1);  // Expect it to be called once

    // Call the method
    sizeEntry.doEncode(mockEncoder, &datum);
}

TEST_F(TiffSizeEntryTest, DtTagReturnsCorrectValue_355) {
    // Test the dtTag method
    EXPECT_EQ(sizeEntry.dtTag(), dtTag);
}

TEST_F(TiffSizeEntryTest, DtGroupReturnsCorrectValue_355) {
    // Test the dtGroup method
    EXPECT_EQ(sizeEntry.dtGroup(), dtGroup);
}

TEST_F(TiffSizeEntryTest, DoCloneReturnsNonNullPointer_355) {
    // Test the doClone method
    const TiffSizeEntry* clonedEntry = sizeEntry.doClone();
    EXPECT_NE(clonedEntry, nullptr);
}

}  // namespace Internal
}  // namespace Exiv2