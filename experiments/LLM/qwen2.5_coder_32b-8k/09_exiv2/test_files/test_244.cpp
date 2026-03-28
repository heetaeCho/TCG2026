#include <gtest/gtest.h>

#include "TestProjects/exiv2/src/tiffcomposite_int.hpp"



using namespace Exiv2::Internal;



class TiffSizeEntryTest_244 : public ::testing::Test {

protected:

    IfdId group = 1;

    uint16_t dtTag = 500;

    IfdId dtGroup = 2;



    TiffSizeEntry tiffSizeEntry = TiffSizeEntry(300, group, dtTag, dtGroup);

};



TEST_F(TiffSizeEntryTest_244, ConstructorInitialization_244) {

    EXPECT_EQ(tiffSizeEntry.dtGroup(), dtGroup);

}



TEST_F(TiffSizeEntryTest_244, BoundaryCondition_DtGroupZero_244) {

    TiffSizeEntry entryWithZeroDtGroup(300, group, dtTag, 0);

    EXPECT_EQ(entryWithZeroDtGroup.dtGroup(), 0);

}



// Since the interface does not expose any methods to change the state of dtGroup after construction,

// we cannot test exceptional cases or error conditions for setting dtGroup.

```


