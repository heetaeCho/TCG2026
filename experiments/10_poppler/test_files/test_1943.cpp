#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/DistinguishedNameParser.h"



namespace DN {

namespace detail {



using ::testing::_;

using ::testing::Return;



TEST(parse_dn_part_1943, NormalOperation_KeyValueSimple_1943) {

    auto result = parse_dn_part("CN=example");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result->second.first, "CN");

    EXPECT_EQ(result->second.second, "example");

}



TEST(parse_dn_part_1943, NormalOperation_HexString_1943) {

    auto result = parse_dn_part("UID=#6578616D706C65");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result->second.first, "UID");

    EXPECT_EQ(result->second.second, "example");

}



TEST(parse_dn_part_1943, NormalOperation_QuotedValue_1943) {

    auto result = parse_dn_part("OU=\"org\\unit\"");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result->second.first, "OU");

    EXPECT_EQ(result->second.second, "org\\unit");

}



TEST(parse_dn_part_1943, NormalOperation_EscapedValue_1943) {

    auto result = parse_dn_part("O=ex\\20ample");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(result->second.first, "O");

    EXPECT_EQ(result->second.second, "ex ample");

}



TEST(parse_dn_part_1943, BoundaryCondition_EmptyString_1943) {

    auto result = parse_dn_part("");

    ASSERT_FALSE(result.has_value());

}



TEST(parse_dn_part_1943, BoundaryCondition_NoEqualSign_1943) {

    auto result = parse_dn_part("CNexample");

    ASSERT_FALSE(result.has_value());

}



TEST(parse_dn_part_1943, BoundaryCondition_EmptyKey_1943) {

    auto result = parse_dn_part("=example");

    ASSERT_FALSE(result.has_value());

}



TEST(parse_dn_part_1943, BoundaryCondition_EmptyValue_1943) {

    auto result = parse_dn_part("CN=");

    ASSERT_FALSE(result.has_value());

}



TEST(parse_dn_part_1943, Exceptional_HexStringOddLength_1943) {

    auto result = parse_dn_part("UID=#6578616D706C65F");

    ASSERT_FALSE(result.has_value());

}



TEST(parse_dn_part_1943, Exceptional_InvalidHexString_1943) {

    auto result = parse_dn_part("UID=#6578616M706C65");

    ASSERT_FALSE(result.has_value());

}



TEST(parse_dn_part_1943, Exceptional_UnmatchedQuotes_1943) {

    auto result = parse_dn_part("OU=\"org\\unit");

    ASSERT_FALSE(result.has_value());

}



TEST(parse_dn_part_1943, Exceptional_InvalidEscapeSequence_1943) {

    auto result = parse_dn_part("O=ex\\ample");

    ASSERT_FALSE(result.has_value());

}



} // namespace detail

} // namespace DN
