#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "DistinguishedNameParser.h"



using namespace DN;

using ::testing::ElementsAre;



TEST_F(DistinguishedNameParserTest_1944, ParseString_NormalOperation_1944) {

    std::string_view input = "CN=example,C=US";

    auto result = parseString(input);

    ASSERT_EQ(result.size(), 2);

    EXPECT_EQ(result[0], std::make_pair("CN", "example"));

    EXPECT_EQ(result[1], std::make_pair("C", "US"));

}



TEST_F(DistinguishedNameParserTest_1944, ParseString_BoundaryCondition_EmptyString_1944) {

    std::string_view input = "";

    auto result = parseString(input);

    ASSERT_TRUE(result.empty());

}



TEST_F(DistinguishedNameParserTest_1944, ParseString_BoundaryCondition_SinglePart_1944) {

    std::string_view input = "CN=example";

    auto result = parseString(input);

    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(result[0], std::make_pair("CN", "example"));

}



TEST_F(DistinguishedNameParserTest_1944, ParseString_BoundaryCondition_SpacesAroundParts_1944) {

    std::string_view input = " CN=example , C=US ";

    auto result = parseString(input);

    ASSERT_EQ(result.size(), 2);

    EXPECT_EQ(result[0], std::make_pair("CN", "example"));

    EXPECT_EQ(result[1], std::make_pair("C", "US"));

}



TEST_F(DistinguishedNameParserTest_1944, ParseString_ErrorCase_MissingValue_1944) {

    std::string_view input = "CN=example,C=";

    auto result = parseString(input);

    ASSERT_TRUE(result.empty());

}



TEST_F(DistinguishedNameParserTest_1944, ParseString_ErrorCase_InvalidSeparator_1944) {

    std::string_view input = "CN=example C=US";

    auto result = parseString(input);

    ASSERT_TRUE(result.empty());

}
