#include <gtest/gtest.h>

#include "re2/re2.h"  // Assuming re2.h includes the necessary declarations



namespace {



using namespace re2;



class FindMSBSetTest_246 : public ::testing::Test {

protected:

    void CheckFindMSBSet(uint32_t input, int expected) {

        EXPECT_EQ(FindMSBSet(input), expected);

    }

};



TEST_F(FindMSBSetTest_246, NormalOperation_246) {

    CheckFindMSBSet(1, 0);

    CheckFindMSBSet(2, 1);

    CheckFindMSBSet(3, 1);

    CheckFindMSBSet(4, 2);

    CheckFindMSBSet(5, 2);

    CheckFindMSBSet(8, 3);

    CheckFindMSBSet(16, 4);

    CheckFindMSBSet(32, 5);

}



TEST_F(FindMSBSetTest_246, BoundaryConditions_246) {

    CheckFindMSBSet(std::numeric_limits<uint32_t>::max(), 31);

    CheckFindMSBSet(0xFFFFFFFF, 31);  // Explicitly testing max value

}



TEST_F(FindMSBSetTest_246, EdgeCases_246) {

    CheckFindMSBSet(0x80000000, 31);

    CheckFindMSBSet(0x7FFFFFFF, 30);

}



TEST_F(FindMSBSetTest_246, InvalidInput_246) {

    EXPECT_DEATH(FindMSBSet(0), ".*Check failed: n != uint32_t{0}.*");

}



}  // namespace

```


