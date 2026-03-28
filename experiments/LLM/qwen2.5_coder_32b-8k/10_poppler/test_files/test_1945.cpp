#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "./TestProjects/poppler/poppler/DistinguishedNameParser.h"



using namespace DN;

using namespace testing;



// Mock Result type assuming it's a vector of pairs of string and string

using Result = std::vector<std::pair<std::string, std::string>>;



class DistinguishedNameParserTest_1945 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if necessary

    }



    void TearDown() override {

        // Teardown code if necessary

    }

};



TEST_F(DistinguishedNameParserTest_1945, FindFirstValue_NormalOperation_1945) {

    Result dn = {{"CN", "example.com"}, {"OU", "IT"}};

    auto result = FindFirstValue(dn, "CN");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, "example.com");

}



TEST_F(DistinguishedNameParserTest_1945, FindFirstValue_BoundaryCondition_EmptyResult_1945) {

    Result dn = {};

    auto result = FindFirstValue(dn, "CN");

    ASSERT_FALSE(result.has_value());

}



TEST_F(DistinguishedNameParserTest_1945, FindFirstValue_BoundaryCondition_KeyNotFound_1945) {

    Result dn = {{"OU", "IT"}, {"DC", "example"}};

    auto result = FindFirstValue(dn, "CN");

    ASSERT_FALSE(result.has_value());

}



TEST_F(DistinguishedNameParserTest_1945, FindFirstValue_BoundaryCondition_MultipleOccurrences_1945) {

    Result dn = {{"CN", "example.com"}, {"OU", "IT"}, {"CN", "another.example.com"}};

    auto result = FindFirstValue(dn, "CN");

    ASSERT_TRUE(result.has_value());

    EXPECT_EQ(*result, "example.com"); // Should return the first occurrence

}



TEST_F(DistinguishedNameParserTest_1945, FindFirstValue_ExceptionalCase_EmptyKey_1945) {

    Result dn = {{"CN", "example.com"}};

    auto result = FindFirstValue(dn, "");

    ASSERT_FALSE(result.has_value()); // Empty key should not match any entry

}
