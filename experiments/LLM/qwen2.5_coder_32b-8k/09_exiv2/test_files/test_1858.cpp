#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/xmp_exiv2.hpp"



using namespace Exiv2;



class MoveXmpToExifTest_1858 : public ::testing::Test {

protected:

    XmpData xmpData;

    ExifData exifData;

};



TEST_F(MoveXmpToExifTest_1858, EmptyXmpData_1858) {

    moveXmpToExif(xmpData, exifData);

    EXPECT_TRUE(exifData.empty());

}



TEST_F(MoveXmpToExifTest_1858, SingleEntryInXmpData_1858) {

    Xmpdatum xmpDatum("Xmp.dc.title", "Sample Title");

    xmpData.add(xmpDatum);



    moveXmpToExif(xmpData, exifData);

    EXPECT_EQ(exifData.count(), 0); // Assuming conversion does not add a corresponding entry

}



TEST_F(MoveXmpToExifTest_1858, MultipleEntriesInXmpData_1858) {

    Xmpdatum xmpDatum1("Xmp.dc.title", "Sample Title");

    Xmpdatum xmpDatum2("Xmp.dc.description", "Sample Description");

    xmpData.add(xmpDatum1);

    xmpData.add(xmpDatum2);



    moveXmpToExif(xmpData, exifData);

    EXPECT_EQ(exifData.count(), 0); // Assuming conversion does not add corresponding entries

}



TEST_F(MoveXmpToExifTest_1858, NoConversionPossible_1858) {

    Xmpdatum xmpDatum("Xmp.dc.title", "Sample Title");

    xmpData.add(xmpDatum);



    moveXmpToExif(xmpData, exifData);

    EXPECT_EQ(exifData.count(), 0); // Assuming no conversion is possible for the given key

}



TEST_F(MoveXmpToExifTest_1858, BoundaryConditionSingleChar_1858) {

    Xmpdatum xmpDatum("Xmp.dc.title", "A");

    xmpData.add(xmpDatum);



    moveXmpToExif(xmpData, exifData);

    EXPECT_EQ(exifData.count(), 0); // Assuming conversion does not add a corresponding entry

}



TEST_F(MoveXmpToExifTest_1858, LargeValueInXmpData_1858) {

    std::string largeValue(65536, 'a'); // Large value

    Xmpdatum xmpDatum("Xmp.dc.description", largeValue);

    xmpData.add(xmpDatum);



    moveXmpToExif(xmpData, exifData);

    EXPECT_EQ(exifData.count(), 0); // Assuming conversion does not add a corresponding entry

}
