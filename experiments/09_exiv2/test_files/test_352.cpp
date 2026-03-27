#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "exif.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class MockTiffEncoder : public TiffEncoder {

public:

    MOCK_METHOD(void, encodeTiffEntry, (TiffEntry* object, const Exifdatum * datum), (override));

};



class TiffEntryTest_352 : public ::testing::Test {

protected:

    TiffEntry tiffEntry;

    MockTiffEncoder mockEncoder;

    std::unique_ptr<ExifKey> key = std::make_unique<ExifKey>("Exif.Image.Make");

    std::unique_ptr<Value> value = std::make_unique<UShortValue>(1);

    Exifdatum exifDatum(*key, value.get());



    void SetUp() override {

        // Setup code if needed

    }

};



TEST_F(TiffEntryTest_352, DoEncodeCallsEncoder_352) {

    EXPECT_CALL(mockEncoder, encodeTiffEntry(&tiffEntry, &exifDatum));

    tiffEntry.doEncode(mockEncoder, &exifDatum);

}



TEST_F(TiffEntryTest_352, DoEncodeWithNullExifdatum_352) {

    EXPECT_CALL(mockEncoder, encodeTiffEntry(&tiffEntry, nullptr)).Times(1);

    tiffEntry.doEncode(mockEncoder, nullptr);

}
