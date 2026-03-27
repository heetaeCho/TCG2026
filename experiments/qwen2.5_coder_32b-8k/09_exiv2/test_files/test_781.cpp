#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExifDataTest_781 : public ::testing::Test {

protected:

    ExifData exif_data;

};



TEST_F(ExifDataTest_781, SortByTag_EmptyData_781) {

    exif_data.sortByTag();

    EXPECT_TRUE(exif_data.empty());

}



TEST_F(ExifDataTest_781, SortByTag_SingleElement_781) {

    Exifdatum datum;

    exif_data.add(datum);

    exif_data.sortByTag();

    EXPECT_EQ(exif_data.count(), 1U);

}



TEST_F(ExifDataTest_781, SortByTag_MultipleElements_781) {

    Exifdatum datum1("Exif.Image.Artist", "Artist");

    Exifdatum datum2("Exif.Image.Copyright", "Copyright");

    exif_data.add(datum1);

    exif_data.add(datum2);

    exif_data.sortByTag();

    EXPECT_EQ(exif_data.count(), 2U);

}



TEST_F(ExifDataTest_781, SortByTag_NoChangeAfterSort_781) {

    Exifdatum datum1("Exif.Image.Artist", "Artist");

    Exifdatum datum2("Exif.Image.Copyright", "Copyright");

    exif_data.add(datum1);

    exif_data.add(datum2);

    exif_data.sortByTag();

    exif_data.sortByTag(); // Repeated sort

    EXPECT_EQ(exif_data.count(), 2U);

}



TEST_F(ExifDataTest_781, SortByKey_AfterSortByTag_781) {

    Exifdatum datum1("Exif.Image.Artist", "Artist");

    Exifdatum datum2("Exif.Image.Copyright", "Copyright");

    exif_data.add(datum1);

    exif_data.add(datum2);

    exif_data.sortByTag();

    exif_data.sortByKey(); // Sort by key after tag sort

    EXPECT_EQ(exif_data.count(), 2U);

}



TEST_F(ExifDataTest_781, FindKey_AfterSortByTag_781) {

    Exifdatum datum1("Exif.Image.Artist", "Artist");

    Exifdatum datum2("Exif.Image.Copyright", "Copyright");

    exif_data.add(datum1);

    exif_data.add(datum2);

    exif_data.sortByTag();

    EXPECT_NE(exif_data.findKey(ExifKey("Exif.Image.Artist")), exif_data.end());

}



TEST_F(ExifDataTest_781, Clear_AfterSortByTag_781) {

    Exifdatum datum1("Exif.Image.Artist", "Artist");

    Exifdatum datum2("Exif.Image.Copyright", "Copyright");

    exif_data.add(datum1);

    exif_data.add(datum2);

    exif_data.sortByTag();

    exif_data.clear();

    EXPECT_TRUE(exif_data.empty());

}
