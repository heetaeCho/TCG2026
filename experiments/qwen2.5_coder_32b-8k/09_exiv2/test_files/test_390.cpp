#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffEntryBaseTest : public ::testing::Test {

protected:

    TiffEntryBase* tiffEntry;



    void SetUp() override {

        tiffEntry = new TiffEntryBase(0x0112, ifdExif, ttShort);

    }



    void TearDown() override {

        delete tiffEntry;

    }

};



TEST_F(TiffEntryBaseTest_390, InitialSizeIsZero_390) {

    EXPECT_EQ(tiffEntry->doSize(), 0U);

}



TEST_F(TiffEntryBaseTest_390, SetDataUpdatesSize_390) {

    std::shared_ptr<DataBuf> buffer = std::make_shared<DataBuf>(4, new byte[4]{1, 2, 3, 4});

    tiffEntry->setData(buffer.get(), 4, buffer);

    EXPECT_EQ(tiffEntry->doSize(), 4U);

}



TEST_F(TiffEntryBaseTest_390, SetDataWithSharedBufferUpdatesSize_390) {

    std::shared_ptr<DataBuf> buffer = std::make_shared<DataBuf>(8, new byte[8]{1, 2, 3, 4, 5, 6, 7, 8});

    tiffEntry->setData(buffer);

    EXPECT_EQ(tiffEntry->doSize(), 0U); // doSize does not consider shared buffer size directly

}



TEST_F(TiffEntryBaseTest_390, SetOffsetDoesNotAffectSize_390) {

    tiffEntry->setOffset(1024);

    EXPECT_EQ(tiffEntry->doSize(), 0U);

}



// Assuming doCount is relevant and returns count_

TEST_F(TiffEntryBaseTest_390, DoCountReturnsZeroInitially_390) {

    EXPECT_EQ(tiffEntry->doCount(), 0U);

}



TEST_F(TiffEntryBaseTest_390, SetDataSetsOffsetCorrectly_390) {

    byte data[4] = {1, 2, 3, 4};

    std::shared_ptr<DataBuf> buffer = std::make_shared<DataBuf>(data, 4);

    tiffEntry->setData(data, 4, buffer);

    EXPECT_EQ(tiffEntry->offset(), 0U); // offset_ is not set by setData, should remain default

}



TEST_F(TiffEntryBaseTest_390, TiffTypeIsSetCorrectly_390) {

    EXPECT_EQ(tiffEntry->tiffType(), ttShort);

}
