#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_enum_values_registry.cpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;

using namespace Catch::Detail;



class ParseEnumsTest_597 : public ::testing::Test {

protected:

    std::vector<StringRef> parseEnums(StringRef enums) {

        return Detail::parseEnums(enums);

    }

};



TEST_F(ParseEnumsTest_597, SingleEnumValue_597) {

    StringRef input("ENUM_VALUE");

    auto result = parseEnums(input);

    EXPECT_EQ(result.size(), 1);

    EXPECT_EQ(std::string(result[0]), "ENUM_VALUE");

}



TEST_F(ParseEnumsTest_597, MultipleEnumValuesCommaSeparated_597) {

    StringRef input("ENUM_VALUE1, ENUM_VALUE2, ENUM_VALUE3");

    auto result = parseEnums(input);

    EXPECT_EQ(result.size(), 3);

    EXPECT_EQ(std::string(result[0]), "ENUM_VALUE1");

    EXPECT_EQ(std::string(result[1]), "ENUM_VALUE2");

    EXPECT_EQ(std::string(result[2]), "ENUM_VALUE3");

}



TEST_F(ParseEnumsTest_597, MultipleEnumValuesWithSpaces_597) {

    StringRef input("  ENUM_VALUE1 , ENUM_VALUE2 , ENUM_VALUE3  ");

    auto result = parseEnums(input);

    EXPECT_EQ(result.size(), 3);

    EXPECT_EQ(std::string(result[0]), "ENUM_VALUE1");

    EXPECT_EQ(std::string(result[1]), "ENUM_VALUE2");

    EXPECT_EQ(std::string(result[2]), "ENUM_VALUE3");

}



TEST_F(ParseEnumsTest_597, EmptyString_597) {

    StringRef input("");

    auto result = parseEnums(input);

    EXPECT_EQ(result.size(), 0);

}



TEST_F(ParseEnumsTest_597, SingleEmptyEnumValue_597) {

    StringRef input(",");

    auto result = parseEnums(input);

    EXPECT_EQ(result.size(), 2);

    EXPECT_TRUE(std::string(result[0]).empty());

    EXPECT_TRUE(std::string(result[1]).empty());

}



TEST_F(ParseEnumsTest_597, LeadingAndTrailingCommas_597) {

    StringRef input(",ENUM_VALUE,");

    auto result = parseEnums(input);

    EXPECT_EQ(result.size(), 3);

    EXPECT_TRUE(std::string(result[0]).empty());

    EXPECT_EQ(std::string(result[1]), "ENUM_VALUE");

    EXPECT_TRUE(std::string(result[2]).empty());

}



TEST_F(ParseEnumsTest_597, ConsecutiveCommas_597) {

    StringRef input("ENUM_VALUE1,,ENUM_VALUE2,");

    auto result = parseEnums(input);

    EXPECT_EQ(result.size(), 4);

    EXPECT_EQ(std::string(result[0]), "ENUM_VALUE1");

    EXPECT_TRUE(std::string(result[1]).empty());

    EXPECT_EQ(std::string(result[2]), "ENUM_VALUE2");

    EXPECT_TRUE(std::string(result[3]).empty());

}
