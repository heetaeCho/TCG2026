#include <gtest/gtest.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffDirectoryTest : public ::testing::Test {

protected:

    TiffDirectory directoryWithNext;

    TiffDirectory directoryWithoutNext;



    TiffDirectoryTest()

        : directoryWithNext(0x123, IfdId::rootIfd, true),

          directoryWithoutNext(0x456, IfdId::exifIfd, false) {}

};



TEST_F(TiffDirectoryTest_245, HasNext_ReturnsTrueWhenConstructedWithHasNext_245) {

    EXPECT_TRUE(directoryWithNext.hasNext());

}



TEST_F(TiffDirectoryTest_245, HasNext_ReturnsFalseWhenConstructedWithoutHasNext_245) {

    EXPECT_FALSE(directoryWithoutNext.hasNext());

}
