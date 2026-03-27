#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include <vector>



namespace {



class ExifDataTest_782 : public ::testing::Test {

protected:

    Exiv2::ExifData exifData;



    void SetUp() override {

        // Add some initial data to test with

        exifData.add(Exiv2::ExifKey("Exif.Image.Artist"), new Exiv2::Value);

        exifData.add(Exiv2::ExifKey("Exif.Image.Copyright"), new Exiv2::Value);

        exifData.add(Exiv2::ExifKey("Exif.Image.DateTime"), new Exiv2::Value);

    }

};



TEST_F(ExifDataTest_782, EraseSingleElement_782) {

    size_t initialCount = exifData.count();

    auto it = exifData.begin();

    ++it; // Move to the second element

    exifData.erase(it);

    EXPECT_EQ(exifData.count(), initialCount - 1);

}



TEST_F(ExifDataTest_782, EraseRangeOfElements_782) {

    size_t initialCount = exifData.count();

    auto beg = exifData.begin();

    ++beg; // Start from the second element

    auto end = exifData.begin();

    ++end;

    ++end; // End at the third element

    exifData.erase(beg, end);

    EXPECT_EQ(exifData.count(), initialCount - 2);

}



TEST_F(ExifDataTest_782, EraseAllElements_782) {

    exifData.erase(exifData.begin(), exifData.end());

    EXPECT_TRUE(exifData.empty());

}



TEST_F(ExifDataTest_782, EraseEmptyRange_782) {

    size_t initialCount = exifData.count();

    auto beg = exifData.begin();

    auto end = exifData.begin(); // Same start and end

    exifData.erase(beg, end);

    EXPECT_EQ(exifData.count(), initialCount); // No elements should be removed

}



TEST_F(ExifDataTest_782, EraseInvalidIterator_782) {

    auto it = exifData.end();

    EXPECT_THROW(exifData.erase(it), Exiv2::Error);

}



TEST_F(ExifDataTest_782, EraseRangeWithEndPastLastElement_782) {

    size_t initialCount = exifData.count();

    auto beg = exifData.begin();

    ++beg; // Start from the second element

    auto end = exifData.end(); // End at one past last element

    exifData.erase(beg, end);

    EXPECT_EQ(exifData.count(), 1); // Only first element should remain

}



} // namespace
