#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_enum_values_registry.cpp"



using namespace Catch::Detail;



class EnumInfoTest : public ::testing::Test {

protected:

    EnumInfo enumInfo;

};



TEST_F(EnumInfoTest_NormalOperation_598, LookupExistingValue_598) {

    enumInfo.m_values = {{1, "One"_sr}, {2, "Two"_sr}};

    EXPECT_EQ(enumInfo.lookup(1), "One"_sr);

}



TEST_F(EnumInfoTest_NormalOperation_598, LookupAnotherExistingValue_598) {

    enumInfo.m_values = {{1, "One"_sr}, {2, "Two"_sr}};

    EXPECT_EQ(enumInfo.lookup(2), "Two"_sr);

}



TEST_F(EnumInfoTest_BoundaryConditions_598, LookupMinimumValue_598) {

    enumInfo.m_values = {{std::numeric_limits<int>::min(), "MinInt"_sr}};

    EXPECT_EQ(enumInfo.lookup(std::numeric_limits<int>::min()), "MinInt"_sr);

}



TEST_F(EnumInfoTest_BoundaryConditions_598, LookupMaximumValue_598) {

    enumInfo.m_values = {{std::numeric_limits<int>::max(), "MaxInt"_sr}};

    EXPECT_EQ(enumInfo.lookup(std::numeric_limits<int>::max()), "MaxInt"_sr);

}



TEST_F(EnumInfoTest_ErrorCases_598, LookupNonExistingValue_598) {

    enumInfo.m_values = {{1, "One"_sr}, {2, "Two"_sr}};

    EXPECT_EQ(enumInfo.lookup(3), "{** unexpected enum value **}"_sr);

}



TEST_F(EnumInfoTest_ErrorCases_598, LookupEmptyValues_598) {

    enumInfo.m_values.clear();

    EXPECT_EQ(enumInfo.lookup(1), "{** unexpected enum value **}"_sr);

}
