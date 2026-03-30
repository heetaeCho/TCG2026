#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "exiv2/exif.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;

using testing::_;



class MockTiffEncoder : public TiffEncoder {

public:

    MOCK_METHOD(void, encodeBinaryElement, (const TiffBinaryElement* object, const Exifdatum* datum), (override));

};



class TiffBinaryElementTest_349 : public ::testing::Test {

protected:

    TiffBinaryElement tiffBinaryElement;

    MockTiffEncoder mockEncoder;

    std::unique_ptr<ExifKey> key = std::make_unique<ExifKey>("Exif.Image.Artist");

    std::unique_ptr<Value> value = Value::create(TypeId::asciiString, 1);

    Exifdatum exifDatum(*key, value.get());

};



TEST_F(TiffBinaryElementTest_349, DoEncodeCallsEncoder_349) {

    EXPECT_CALL(mockEncoder, encodeBinaryElement(&tiffBinaryElement, &exifDatum));

    tiffBinaryElement.doEncode(mockEncoder, &exifDatum);

}



TEST_F(TiffBinaryElementTest_349, DoEncodeWithNullExifdatum_349) {

    EXPECT_CALL(mockEncoder, encodeBinaryElement(&tiffBinaryElement, nullptr)).Times(0);

    tiffBinaryElement.doEncode(mockEncoder, nullptr);

}
