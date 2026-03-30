#include <gtest/gtest.h>

#include "safe_op.hpp"



using namespace Safe::Internal;



TEST_F(SafeOpTest_65, BuiltinAddOverflow_Int_NormalOperation_65) {

    int result;

    EXPECT_FALSE(builtin_add_overflow(10, 20, result));

    EXPECT_EQ(result, 30);

}



TEST_F(SafeOpTest_65, BuiltinAddOverflow_Int_BoundaryCondition_MaxInt_65) {

    int result;

    EXPECT_TRUE(builtin_add_overflow(INT_MAX, 1, result));

}



TEST_F(SafeOpTest_65, BuiltinAddOverflow_Int_BoundaryCondition_MinInt_65) {

    int result;

    EXPECT_TRUE(builtin_add_overflow(INT_MIN, -1, result));

}



TEST_F(SafeOpTest_65, BuiltinAddOverflow_Long_NormalOperation_65) {

    long result;

    EXPECT_FALSE(builtin_add_overflow(10L, 20L, result));

    EXPECT_EQ(result, 30L);

}



TEST_F(SafeOpTest_65, BuiltinAddOverflow_Long_BoundaryCondition_MaxLong_65) {

    long result;

    EXPECT_TRUE(builtin_add_overflow(LONG_MAX, 1L, result));

}



TEST_F(SafeOpTest_65, BuiltinAddOverflow_Long_BoundaryCondition_MinLong_65) {

    long result;

    EXPECT_TRUE(builtin_add_overflow(LONG_MIN, -1L, result));

}



TEST_F(SafeOpTest_65, BuiltinAddOverflow_LongLong_NormalOperation_65) {

    long long result;

    EXPECT_FALSE(builtin_add_overflow(10LL, 20LL, result));

    EXPECT_EQ(result, 30LL);

}



TEST_F(SafeOpTest_65, BuiltinAddOverflow_LongLong_BoundaryCondition_MaxLongLong_65) {

    long long result;

    EXPECT_TRUE(builtin_add_overflow(LLONG_MAX, 1LL, result));

}



TEST_F(SafeOpTest_65, BuiltinAddOverflow_LongLong_BoundaryCondition_MinLongLong_65) {

    long long result;

    EXPECT_TRUE(builtin_add_overflow(LLONG_MIN, -1LL, result));

}



TEST_F(SafeOpTest_65, BuiltinAddOverflow_UInt_NormalOperation_65) {

    unsigned int result;

    EXPECT_FALSE(builtin_add_overflow(10u, 20u, result));

    EXPECT_EQ(result, 30u);

}



TEST_F(SafeOpTest_65, BuiltinAddOverflow_UInt_BoundaryCondition_MaxUInt_65) {

    unsigned int result;

    EXPECT_TRUE(builtin_add_overflow(UINT_MAX, 1u, result));

}



TEST_F(SafeOpTest_65, BuiltinAddOverflow_ULong_NormalOperation_65) {

    unsigned long result;

    EXPECT_FALSE(builtin_add_overflow(10UL, 20UL, result));

    EXPECT_EQ(result, 30UL);

}



TEST_F(SafeOpTest_65, BuiltinAddOverflow_ULong_BoundaryCondition_MaxULong_65) {

    unsigned long result;

    EXPECT_TRUE(builtin_add_overflow(ULONG_MAX, 1UL, result));

}



TEST_F(SafeOpTest_65, BuiltinAddOverflow_ULongLong_NormalOperation_65) {

    unsigned long long result;

    EXPECT_FALSE(builtin_add_overflow(10ULL, 20ULL, result));

    EXPECT_EQ(result, 30ULL);

}



TEST_F(SafeOpTest_65, BuiltinAddOverflow_ULongLong_BoundaryCondition_MaxULongLong_65) {

    unsigned long long result;

    EXPECT_TRUE(builtin_add_overflow(ULLONG_MAX, 1ULL, result));

}
