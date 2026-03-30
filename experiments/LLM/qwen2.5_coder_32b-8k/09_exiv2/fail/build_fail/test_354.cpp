#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "exiv2/exif.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class TiffMnEntryTest : public ::testing::Test {

protected:

    uint16_t tag = 0x0001;

    IfdId group = ifdExif;

    IfdId mnGroup = ifdGpsInfo;

    std::unique_ptr<Exifdatum> exifDatum;

    TiffMnEntry tiffMnEntry;



    void SetUp() override {

        exifDatum = std::make_unique<Exifdatum>(ExifKey("Exif.Image.Artist"), static_cast<const Value*>(nullptr));

        tiffMnEntry = TiffMnEntry(tag, group, mnGroup);

    }

};



TEST_F(TiffMnEntryTest_354, DoEncodeCallsEncoderWithCorrectParameters_354) {

    MockTiffEncoder mockEncoder;

    EXPECT_CALL(mockEncoder, encodeMnEntry(&tiffMnEntry, exifDatum.get())).Times(1);



    tiffMnEntry.doEncode(mockEncoder, exifDatum.get());

}



class MockTiffEncoder : public TiffEncoder {

public:

    MOCK_METHOD(void, encodeMnEntry, (TiffMnEntry *object, const Exifdatum *datum), (override));

};



TEST_F(TiffMnEntryTest_354, DoEncodeWithNullExifdatumDoesNotThrow_354) {

    MockTiffEncoder mockEncoder;

    EXPECT_CALL(mockEncoder, encodeMnEntry(&tiffMnEntry, nullptr)).Times(1);



    ASSERT_NO_THROW(tiffMnEntry.doEncode(mockEncoder, nullptr));

}



TEST_F(TiffMnEntryTest_354, DoEncodeWithValidExifdatumDoesNotThrow_354) {

    MockTiffEncoder mockEncoder;

    EXPECT_CALL(mockEncoder, encodeMnEntry(&tiffMnEntry, exifDatum.get())).Times(1);



    ASSERT_NO_THROW(tiffMnEntry.doEncode(mockEncoder, exifDatum.get()));

}
