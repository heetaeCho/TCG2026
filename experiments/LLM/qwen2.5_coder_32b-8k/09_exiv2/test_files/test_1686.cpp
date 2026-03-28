#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "./TestProjects/exiv2/src/tiffvisitor_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TiffEncoderTest_1686 : public ::testing::Test {

protected:

    TiffEncoder encoder{ExifData(), IptcData(), XmpData(), nullptr, false, PrimaryGroups{}, nullptr, nullptr};

    TiffSizeEntry sizeEntry{0x123, IfdId::exifIFD, 0x456, IfdId::subIFD};

    std::unique_ptr<Exifdatum> exifdatum;



    void SetUp() override {

        exifdatum = std::make_unique<Exifdatum>(ExifKey("Exif.Image.Artist"), new Value);

        *exifdatum = "Test Artist";

    }

};



TEST_F(TiffEncoderTest_1686, EncodeSizeEntry_NormalOperation_1686) {

    EXPECT_NO_THROW(encoder.encodeSizeEntry(&sizeEntry, exifdatum.get()));

}



TEST_F(TiffEncoderTest_1686, EncodeSizeEntry_NullDatum_1686) {

    EXPECT_NO_THROW(encoder.encodeSizeEntry(&sizeEntry, nullptr));

}



TEST_F(TiffEncoderTest_1686, EncodeSizeEntry_NullObject_1686) {

    EXPECT_NO_THROW(encoder.encodeSizeEntry(nullptr, exifdatum.get()));

}



TEST_F(TiffEncoderTest_1686, EncodeSizeEntry_BothNull_1686) {

    EXPECT_NO_THROW(encoder.encodeSizeEntry(nullptr, nullptr));

}
