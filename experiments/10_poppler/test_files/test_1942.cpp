#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/DistinguishedNameParser.h"

#include <string_view>



namespace DN {

    namespace detail {

        // Mocking oidmap for testing purposes

        static const std::unordered_map<std::string_view, std::string_view> oidmap = {

            {"CN", "2.5.4.3"},

            {"OU", "2.5.4.11"},

            {"O", "2.5.4.10"}

        };

    }

}



using namespace DN::detail;



TEST_F(DNParserTest_1942, NormalOperationWithKnownOID_1942) {

    EXPECT_EQ(attributeNameForOID("2.5.4.3"), "CN");

    EXPECT_EQ(attributeNameForOID("2.5.4.11"), "OU");

    EXPECT_EQ(attributeNameForOID("2.5.4.10"), "O");

}



TEST_F(DNParserTest_1942, NormalOperationWithPrefixOID_1942) {

    EXPECT_EQ(attributeNameForOID("OID.2.5.4.3"), "CN");

    EXPECT_EQ(attributeNameForOID("oid.2.5.4.11"), "OU");

}



TEST_F(DNParserTest_1942, BoundaryConditionWithEmptyString_1942) {

    EXPECT_TRUE(attributeNameForOID("").empty());

}



TEST_F(DNParserTest_1942, BoundaryConditionWithUnknownOID_1942) {

    EXPECT_TRUE(attributeNameForOID("1.2.3.4").empty());

}



TEST_F(DNParserTest_1942, BoundaryConditionWithShortPrefix_1942) {

    EXPECT_TRUE(attributeNameForOID("OID.").empty());

    EXPECT_TRUE(attributeNameForOID("oid.").empty());

}



TEST_F(DNParserTest_1942, ExceptionalCaseWithInvalidPrefix_1942) {

    EXPECT_TRUE(attributeNameForOID("OIDS.2.5.4.3").empty());

    EXPECT_TRUE(attributeNameForOID("oids.2.5.4.11").empty());

}
