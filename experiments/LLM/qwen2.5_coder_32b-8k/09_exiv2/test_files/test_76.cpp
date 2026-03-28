#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/utils.hpp"



using namespace Exiv2::Internal;



// Test suite for contains function with TEST_ID 76

class ContainsFunctionTest_76 : public ::testing::Test {};



TEST_F(ContainsFunctionTest_76, NormalOperation_76) {

    EXPECT_TRUE(contains("hello", 'e'));

    EXPECT_FALSE(contains("world", 'x'));

}



TEST_F(ContainsFunctionTest_76, BoundaryConditions_76) {

    EXPECT_FALSE(contains("", 'a')); // Empty string

    EXPECT_TRUE(contains("a", 'a'));  // Single character match

    EXPECT_FALSE(contains("a", 'b')); // Single character mismatch

}



TEST_F(ContainsFunctionTest_76, ExceptionalCases_76) {

    // No exceptional cases observable through the interface for this function

}
