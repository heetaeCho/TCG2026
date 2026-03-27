#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"



using namespace Exiv2::Internal;



class TiffReaderTest_1701 : public ::testing::Test {

protected:

    byte dummyData[1];

    size_t dataSize = sizeof(dummyData);

    TiffComponent root;

    TiffRwState state;

    TiffReader reader{dummyData, dataSize, &root, state};

};



TEST_F(TiffReaderTest_1701, NextIdx_IncrementsIndexForGroup_1701) {

    IfdId group = 0;

    int initialIdx = reader.nextIdx(group);

    int nextIdx = reader.nextIdx(group);



    EXPECT_EQ(nextIdx, initialIdx + 1);

}



TEST_F(TiffReaderTest_1701, NextIdx_StartsAtZeroForNewGroup_1701) {

    IfdId group = 1;

    int idx = reader.nextIdx(group);



    EXPECT_EQ(idx, 1);

}



TEST_F(TiffReaderTest_1701, NextIdx_BoundaryConditionWithMultipleGroups_1701) {

    IfdId group1 = 2;

    IfdId group2 = 3;



    int idx1 = reader.nextIdx(group1);

    int idx2 = reader.nextIdx(group2);



    EXPECT_EQ(idx1, 1);

    EXPECT_EQ(idx2, 1);

}



TEST_F(TiffReaderTest_1701, NextIdx_IncrementsConsistentlyForMultipleCalls_1701) {

    IfdId group = 4;

    int idx1 = reader.nextIdx(group);

    int idx2 = reader.nextIdx(group);

    int idx3 = reader.nextIdx(group);



    EXPECT_EQ(idx1, 1);

    EXPECT_EQ(idx2, 2);

    EXPECT_EQ(idx3, 3);

}
