#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffEntryBaseTest_235 : public ::testing::Test {

protected:

    TiffEntryBase* tiffEntryBase;



    void SetUp() override {

        tiffEntryBase = new TiffEntryBase(1, ifdExif, ttByte);

    }



    void TearDown() override {

        delete tiffEntryBase;

    }

};



TEST_F(TiffEntryBaseTest_235, DefaultOffsetIsZero_235) {

    EXPECT_EQ(tiffEntryBase->offset(), 0U);

}



TEST_F(TiffEntryBaseTest_235, SetOffsetUpdatesValue_235) {

    tiffEntryBase->setOffset(1234);

    EXPECT_EQ(tiffEntryBase->offset(), 1234U);

}



// Assuming boundary condition for offset is non-negative integer

TEST_F(TiffEntryBaseTest_235, SetOffsetToMaxSizeT_235) {

    tiffEntryBase->setOffset(std::numeric_limits<size_t>::max());

    EXPECT_EQ(tiffEntryBase->offset(), std::numeric_limits<size_t>::max());

}



// Assuming no exceptional or error cases for offset as per the provided interface

```


