#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "exif.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class MockTiffEncoder : public TiffEncoder {

public:

    MOCK_METHOD(void, encodeTiffEntryBase, (TiffEntryBase* object, const Exifdatum* datum), (override));

};



class TiffEntryBaseTest_348 : public ::testing::Test {

protected:

    std::unique_ptr<TiffEntryBase> tiffEntry;

    MockTiffEncoder mockEncoder;

    std::unique_ptr<Exifdatum> exifDatum;



    void SetUp() override {

        tiffEntry = std::make_unique<TiffEntryBase>(0x1234, ifdExif, ttUnsignedShort);

        exifDatum = std::make_unique<Exifdatum>("Exif.Image.Artist", static_cast<const Value*>(nullptr));

    }

};



TEST_F(TiffEntryBaseTest_348, EncodeCallsEncoderMethod_348) {

    EXPECT_CALL(mockEncoder, encodeTiffEntryBase(tiffEntry.get(), exifDatum.get())).Times(1);

    tiffEntry->encode(mockEncoder, exifDatum.get());

}



TEST_F(TiffEntryBaseTest_348, EncodeWithNullExifdatum_348) {

    EXPECT_CALL(mockEncoder, encodeTiffEntryBase(tiffEntry.get(), nullptr)).Times(1);

    tiffEntry->encode(mockEncoder, nullptr);

}
