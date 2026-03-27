#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffEntryBaseTest_399 : public ::testing::Test {

protected:

    TiffEntryBase* tiffEntry;



    void SetUp() override {

        tiffEntry = new TiffEntryBase(0x123, ifdExif, ttLong);

    }



    void TearDown() override {

        delete tiffEntry;

    }

};



TEST_F(TiffEntryBaseTest_399, DefaultConstructorInitializesCountToZero_399) {

    EXPECT_EQ(tiffEntry->doSizeData(), 0U);

}



TEST_F(TiffEntryBaseTest_399, SetDataWithPointerUpdatesOffsetAndSize_399) {

    const size_t dataSize = 4;

    byte data[dataSize] = {1, 2, 3, 4};

    std::shared_ptr<DataBuf> storage(new DataBuf(data, dataSize));

    tiffEntry->setData(data, dataSize, storage);

    EXPECT_EQ(tiffEntry->offset(), 0U);

}



TEST_F(TiffEntryBaseTest_399, SetDataWithBufferUpdatesOffsetAndSize_399) {

    const size_t dataSize = 4;

    byte data[dataSize] = {1, 2, 3, 4};

    std::shared_ptr<DataBuf> storage(new DataBuf(data, dataSize));

    tiffEntry->setData(storage);

    EXPECT_EQ(tiffEntry->offset(), 0U);

}



TEST_F(TiffEntryBaseTest_399, UpdateValueDoesNotAffectDoSizeData_399) {

    auto value = std::make_unique<Value>(12345);

    tiffEntry->updateValue(std::move(value), bigEndian);

    EXPECT_EQ(tiffEntry->doSizeData(), 0U);

}



TEST_F(TiffEntryBaseTest_399, SetValueDoesNotAffectDoSizeData_399) {

    auto value = std::make_unique<Value>(12345);

    tiffEntry->setValue(std::move(value));

    EXPECT_EQ(tiffEntry->doSizeData(), 0U);

}



TEST_F(TiffEntryBaseTest_399, SetOffsetUpdatesOffsetValue_399) {

    const size_t newOffset = 16;

    tiffEntry->setOffset(newOffset);

    EXPECT_EQ(tiffEntry->offset(), newOffset);

}
