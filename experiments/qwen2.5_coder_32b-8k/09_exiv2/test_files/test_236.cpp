#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"

#include <memory>



using namespace Exiv2::Internal;



class TiffEntryBaseTest_236 : public ::testing::Test {

protected:

    TiffEntryBase* entry;

    

    void SetUp() override {

        entry = new TiffEntryBase(0x0100, ifdIdExif, ttByte);

    }



    void TearDown() override {

        delete entry;

    }

};



TEST_F(TiffEntryBaseTest_236, PDataReturnsNullPointerByDefault_236) {

    EXPECT_EQ(entry->pData(), nullptr);

}



TEST_F(TiffEntryBaseTest_236, SetDataWithBufferUpdatesPData_236) {

    std::shared_ptr<DataBuf> buf = std::make_shared<DataBuf>(10);

    entry->setData(buf);

    EXPECT_NE(entry->pData(), nullptr);

}



TEST_F(TiffEntryBaseTest_236, SetDataWithPointerAndSizeUpdatesPData_236) {

    byte data[5] = {1, 2, 3, 4, 5};

    std::shared_ptr<DataBuf> buf = std::make_shared<DataBuf>(data, 5);

    entry->setData(data, 5, buf);

    EXPECT_NE(entry->pData(), nullptr);

}



TEST_F(TiffEntryBaseTest_236, PDataPointsToCorrectBufferAfterSetData_236) {

    byte data[5] = {1, 2, 3, 4, 5};

    std::shared_ptr<DataBuf> buf = std::make_shared<DataBuf>(data, 5);

    entry->setData(data, 5, buf);

    EXPECT_EQ(entry->pData(), data);

}



TEST_F(TiffEntryBaseTest_236, TiffTypeReturnsCorrectValue_236) {

    EXPECT_EQ(entry->tiffType(), ttByte);

}
