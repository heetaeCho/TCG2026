#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffEntryTest_286 : public ::testing::Test {

protected:

    TiffEntry* tiffEntry;



    void SetUp() override {

        tiffEntry = new TiffEntry();

    }



    void TearDown() override {

        delete tiffEntry;

    }

};



TEST_F(TiffEntryTest_286, DoClone_ReturnsNewInstance_286) {

    TiffEntry* clonedEntry = tiffEntry->doClone();

    EXPECT_NE(tiffEntry, clonedEntry);

    delete clonedEntry;

}



TEST_F(TiffEntryTest_286, DoClone_CloneHasSameType_286) {

    TiffEntry* clonedEntry = tiffEntry->doClone();

    EXPECT_TRUE(dynamic_cast<TiffEntry*>(clonedEntry) != nullptr);

    delete clonedEntry;

}
