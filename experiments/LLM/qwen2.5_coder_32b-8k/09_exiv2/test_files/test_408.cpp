#include <gtest/gtest.h>

#include "TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffEntryBaseTest_408 : public ::testing::Test {

protected:

    TiffEntryBase* entry;

    

    void SetUp() override {

        entry = new TiffEntryBase(0x123, IfdId::IFD0, TiffType::undefined);

    }



    void TearDown() override {

        delete entry;

    }

};



TEST_F(TiffEntryBaseTest_408, DefaultConstructorInitialization_408) {

    EXPECT_EQ(entry->tiffType(), TiffType::undefined);

    EXPECT_EQ(entry->offset(), 0);

    EXPECT_EQ(entry->pData(), nullptr);

}



TEST_F(TiffEntryBaseTest_408, SetOffsetUpdatesOffset_408) {

    entry->setOffset(1234);

    EXPECT_EQ(entry->offset(), 1234);

}



TEST_F(TiffEntryBaseTest_408, DoSizeImageReturnsZero_408) {

    EXPECT_EQ(entry->doSizeImage(), 0);

}
