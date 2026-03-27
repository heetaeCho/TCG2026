#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class MockTiffEncoder : public TiffEncoder {

public:

    MOCK_METHOD(void, encodeImageEntry, (const TiffImageEntry* object, const Exifdatum* datum), (override));

};



TEST_F(TiffImageEntryTest_353, DoEncodeCallsEncoder_353) {

    MockTiffEncoder mockEncoder({}, {}, nullptr, nullptr, false, 0, nullptr, nullptr);

    TiffImageEntry imageEntry;

    Exifdatum exifDatum(ExifKey(), nullptr);



    EXPECT_CALL(mockEncoder, encodeImageEntry(&imageEntry, &exifDatum)).Times(1);



    imageEntry.doEncode(mockEncoder, &exifDatum);

}



TEST_F(TiffImageEntryTest_353, DoEncodeWithNullDatum_353) {

    MockTiffEncoder mockEncoder({}, {}, nullptr, nullptr, false, 0, nullptr, nullptr);

    TiffImageEntry imageEntry;



    EXPECT_CALL(mockEncoder, encodeImageEntry(&imageEntry, static_cast<const Exifdatum*>(nullptr))).Times(1);



    imageEntry.doEncode(mockEncoder, nullptr);

}



TEST_F(TiffImageEntryTest_353, DoEncodeWithNullEncoder_353) {

    TiffImageEntry imageEntry;

    Exifdatum exifDatum(ExifKey(), nullptr);



    EXPECT_THROW(imageEntry.doEncode(*static_cast<MockTiffEncoder*>(nullptr), &exifDatum), std::exception);

}



TEST_F(TiffImageEntryTest_353, DoEncodeBoundaryConditions_353) {

    MockTiffEncoder mockEncoder({}, {}, nullptr, nullptr, false, 0, nullptr, nullptr);

    TiffImageEntry imageEntry;

    Exifdatum exifDatum(ExifKey(), nullptr);



    EXPECT_CALL(mockEncoder, encodeImageEntry(&imageEntry, &exifDatum)).Times(1);



    // Boundary condition: Minimum values

    imageEntry.doEncode(mockEncoder, &exifDatum);

}
