#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class TiffEntryBaseTest_299 : public ::testing::Test {

protected:

    TiffEntryBase* tiffEntry;

    

    virtual void SetUp() {

        tiffEntry = new TiffEntryBase(1, IfdId::IFD0, TiffType::unsignedShort);

    }



    virtual void TearDown() {

        delete tiffEntry;

    }

};



TEST_F(TiffEntryBaseTest_299, SetDataWithValidParameters_299) {

    byte data[] = {0x1, 0x2, 0x3};

    std::shared_ptr<DataBuf> storage = std::make_shared<DataBuf>(data, sizeof(data));

    tiffEntry->setData(data, sizeof(data), storage);

    EXPECT_EQ(tiffEntry->pData(), data);

    EXPECT_EQ(tiffEntry->storage()->pData_, data);

}



TEST_F(TiffEntryBaseTest_299, SetDataWithNullPointer_299) {

    std::shared_ptr<DataBuf> storage = std::make_shared<DataBuf>(nullptr, 0);

    tiffEntry->setData(nullptr, 10, storage);

    EXPECT_EQ(tiffEntry->pData(), nullptr);

    EXPECT_EQ(tiffEntry->size_, 0);

}



TEST_F(TiffEntryBaseTest_299, SetDataWithZeroSize_299) {

    byte data[] = {0x1, 0x2, 0x3};

    std::shared_ptr<DataBuf> storage = std::make_shared<DataBuf>(data, 0);

    tiffEntry->setData(data, 0, storage);

    EXPECT_EQ(tiffEntry->pData(), data);

    EXPECT_EQ(tiffEntry->size_, 0);

}



TEST_F(TiffEntryBaseTest_299, SetDataWithNonZeroSizeAndNullStorage_299) {

    byte data[] = {0x1, 0x2, 0x3};

    tiffEntry->setData(data, sizeof(data), nullptr);

    EXPECT_EQ(tiffEntry->pData(), data);

    EXPECT_EQ(tiffEntry->size_, sizeof(data));

}



TEST_F(TiffEntryBaseTest_299, SetDataWithStorageOnly_299) {

    byte data[] = {0x1, 0x2, 0x3};

    std::shared_ptr<DataBuf> storage = std::make_shared<DataBuf>(data, sizeof(data));

    tiffEntry->setData(storage);

    EXPECT_EQ(tiffEntry->pData(), data);

    EXPECT_EQ(tiffEntry->storage()->pData_, data);

}



TEST_F(TiffEntryBaseTest_299, SetDataWithEmptyStorage_299) {

    std::shared_ptr<DataBuf> storage = std::make_shared<DataBuf>(nullptr, 0);

    tiffEntry->setData(storage);

    EXPECT_EQ(tiffEntry->pData(), nullptr);

    EXPECT_EQ(tiffEntry->size_, 0);

}
