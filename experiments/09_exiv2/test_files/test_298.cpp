#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TiffEntryBaseTest_298 : public ::testing::Test {

protected:

    std::shared_ptr<DataBuf> dataBuffer;

    TiffEntryBase* tiffEntry;



    void SetUp() override {

        dataBuffer = std::make_shared<DataBuf>(10);

        tiffEntry = new TiffEntryBase(0x0112, ifdExif, ttLong);

    }



    void TearDown() override {

        delete tiffEntry;

    }

};



TEST_F(TiffEntryBaseTest_298, SetDataWithBuffer_298) {

    tiffEntry->setData(dataBuffer);



    EXPECT_EQ(tiffEntry->storage(), dataBuffer);

}



TEST_F(TiffEntryBaseTest_298, SetDataWithNullBuffer_298) {

    std::shared_ptr<DataBuf> nullBuffer;

    tiffEntry->setData(nullBuffer);



    EXPECT_EQ(tiffEntry->storage(), nullptr);

}



TEST_F(TiffEntryBaseTest_298, SetDataWithEmptyBuffer_298) {

    auto emptyBuffer = std::make_shared<DataBuf>();

    tiffEntry->setData(emptyBuffer);



    EXPECT_EQ(tiffEntry->storage(), emptyBuffer);

    EXPECT_EQ(tiffEntry->pData(), nullptr);

}



TEST_F(TiffEntryBaseTest_298, SetDataWithZeroSizeBuffer_298) {

    auto zeroSizeBuffer = std::make_shared<DataBuf>(0);

    tiffEntry->setData(zeroSizeBuffer);



    EXPECT_EQ(tiffEntry->storage(), zeroSizeBuffer);

    EXPECT_EQ(tiffEntry->pData(), nullptr);

}



TEST_F(TiffEntryBaseTest_298, SetDataWithNonZeroSizeBuffer_298) {

    auto nonZeroSizeBuffer = std::make_shared<DataBuf>(10);

    tiffEntry->setData(nonZeroSizeBuffer);



    EXPECT_EQ(tiffEntry->storage(), nonZeroSizeBuffer);

    EXPECT_NE(tiffEntry->pData(), nullptr);

    EXPECT_EQ(nonZeroSizeBuffer->size(), 10);

}
