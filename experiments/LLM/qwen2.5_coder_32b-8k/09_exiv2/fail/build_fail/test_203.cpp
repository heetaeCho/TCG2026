#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "TestProjects/exiv2/src/pentaxmn_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class FindLensInfoTest_203 : public ::testing::Test {

protected:

    ExifData metadata;

};



TEST_F(FindLensInfoTest_203, DngLensInfoFound_203) {

    ExifKey dngLensInfoKey("Exif.PentaxDng.LensInfo");

    metadata.add(dngLensInfoKey, new Value);



    EXPECT_EQ(findLensInfo(&metadata)->key(), dngLensInfoKey);

}



TEST_F(FindLensInfoTest_203, LensInfoFound_203) {

    ExifKey lensInfoKey("Exif.Pentax.LensInfo");

    metadata.add(lensInfoKey, new Value);



    EXPECT_EQ(findLensInfo(&metadata)->key(), lensInfoKey);

}



TEST_F(FindLensInfoTest_203, BothKeysFound_DngPreferred_203) {

    ExifKey dngLensInfoKey("Exif.PentaxDng.LensInfo");

    metadata.add(dngLensInfoKey, new Value);



    ExifKey lensInfoKey("Exif.Pentax.LensInfo");

    metadata.add(lensInfoKey, new Value);



    EXPECT_EQ(findLensInfo(&metadata)->key(), dngLensInfoKey);

}



TEST_F(FindLensInfoTest_203, NoKeysFound_ExceptionThrown_203) {

    EXPECT_THROW(findLensInfo(&metadata), LensInfoNotFound);

}
