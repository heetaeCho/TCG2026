#include <gtest/gtest.h>

#include "catch2/internal/catch_enum_values_registry.hpp"

#include "catch2/interfaces/catch_interfaces_enum_values_registry.hpp"



using namespace Catch::Detail;



TEST_F(EnumInfoTest_599, CreateEnumInfoWithValidData_599) {

    StringRef enumName("Color");

    StringRef allValueNames("Red,Green,Blue");

    std::vector<int> values = {1, 2, 3};



    auto enumInfo = makeEnumInfo(enumName, allValueNames, values);



    ASSERT_EQ(enumInfo->m_name, "Color");

    ASSERT_EQ(enumInfo->m_values.size(), 3);

    EXPECT_EQ(enumInfo->m_values[0], std::make_pair(1, StringRef("Red")));

    EXPECT_EQ(enumInfo->m_values[1], std::make_pair(2, StringRef("Green")));

    EXPECT_EQ(enumInfo->m_values[2], std::make_pair(3, StringRef("Blue")));

}



TEST_F(EnumInfoTest_599, LookupExistingValue_599) {

    StringRef enumName("Color");

    StringRef allValueNames("Red,Green,Blue");

    std::vector<int> values = {1, 2, 3};



    auto enumInfo = makeEnumInfo(enumName, allValueNames, values);



    EXPECT_EQ(enumInfo->lookup(1), "Red");

    EXPECT_EQ(enumInfo->lookup(2), "Green");

    EXPECT_EQ(enumInfo->lookup(3), "Blue");

}



TEST_F(EnumInfoTest_599, LookupNonExistingValue_599) {

    StringRef enumName("Color");

    StringRef allValueNames("Red,Green,Blue");

    std::vector<int> values = {1, 2, 3};



    auto enumInfo = makeEnumInfo(enumName, allValueNames, values);



    EXPECT_TRUE(enumInfo->lookup(4).empty());

}



TEST_F(EnumInfoTest_599, CreateEnumInfoWithEmptyValues_599) {

    StringRef enumName("Color");

    StringRef allValueNames("");

    std::vector<int> values = {};



    auto enumInfo = makeEnumInfo(enumName, allValueNames, values);



    ASSERT_EQ(enumInfo->m_name, "Color");

    EXPECT_TRUE(enumInfo->m_values.empty());

}



TEST_F(EnumInfoTest_599, CreateEnumInfoWithSingleValue_599) {

    StringRef enumName("Color");

    StringRef allValueNames("Red");

    std::vector<int> values = {1};



    auto enumInfo = makeEnumInfo(enumName, allValueNames, values);



    ASSERT_EQ(enumInfo->m_name, "Color");

    ASSERT_EQ(enumInfo->m_values.size(), 1);

    EXPECT_EQ(enumInfo->m_values[0], std::make_pair(1, StringRef("Red")));

}



TEST_F(EnumInfoTest_599, CreateEnumInfoWithMismatchedNamesAndValues_599) {

    StringRef enumName("Color");

    StringRef allValueNames("Red,Green");

    std::vector<int> values = {1};



    EXPECT_THROW(makeEnumInfo(enumName, allValueNames, values), std::exception);

}
