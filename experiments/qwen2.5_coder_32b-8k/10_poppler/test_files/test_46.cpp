#include <gtest/gtest.h>



// Assuming the necessary headers are included for Google Test and the classes/structs under test.



struct TrueTypeLoca {

    public: int idx = 0;

    public: int newOffset = 0;

};



struct cmpTrueTypeLocaOffsetFunctor {

    public: bool operator()(const TrueTypeLoca loca1, const TrueTypeLoca loca2);

};



// Test fixture for the cmpTrueTypeLocaOffsetFunctor

class CmpTrueTypeLocaOffsetFunctorTest_46 : public ::testing::Test {

protected:

    cmpTrueTypeLocaOffsetFunctor comparator;

};



// Test case to verify normal operation where origOffsets are different

TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, DifferentOrigOffsets_NormalOperation_46) {

    TrueTypeLoca loca1{0, 0};

    TrueTypeLoca loca2{1, 0};



    EXPECT_TRUE(comparator(loca1, loca2));

}



// Test case to verify normal operation where origOffsets are the same but idxs are different

TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, SameOrigOffsets_DifferentIdxs_NormalOperation_46) {

    TrueTypeLoca loca1{0, 0};

    TrueTypeLoca loca2{0, 1};



    EXPECT_TRUE(comparator(loca1, loca2));

}



// Test case to verify normal operation where both origOffsets and idxs are the same

TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, SameOrigOffsets_SameIdxs_NormalOperation_46) {

    TrueTypeLoca loca1{0, 0};

    TrueTypeLoca loca2{0, 0};



    EXPECT_FALSE(comparator(loca1, loca2));

}



// Test case to verify boundary condition with minimum values

TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, BoundaryCondition_MinValues_NormalOperation_46) {

    TrueTypeLoca loca1{INT_MIN, INT_MIN};

    TrueTypeLoca loca2{INT_MIN + 1, INT_MIN};



    EXPECT_TRUE(comparator(loca1, loca2));

}



// Test case to verify boundary condition with maximum values

TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, BoundaryCondition_MaxValues_NormalOperation_46) {

    TrueTypeLoca loca1{INT_MAX - 1, INT_MAX};

    TrueTypeLoca loca2{INT_MAX, INT_MAX};



    EXPECT_TRUE(comparator(loca1, loca2));

}



// Test case to verify exceptional or error cases (if any observable through the interface)

TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, ExceptionalCase_SameValues_NormalOperation_46) {

    TrueTypeLoca loca1{0, 0};

    TrueTypeLoca loca2{0, 0};



    EXPECT_FALSE(comparator(loca1, loca2));

}



// Test case to verify exceptional or error cases (if any observable through the interface)

TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, ExceptionalCase_SameOrigOffsets_MaxIdxs_NormalOperation_46) {

    TrueTypeLoca loca1{0, INT_MAX};

    TrueTypeLoca loca2{0, INT_MAX};



    EXPECT_FALSE(comparator(loca1, loca2));

}
