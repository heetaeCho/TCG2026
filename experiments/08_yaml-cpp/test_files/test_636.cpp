#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/src/emitterutils.cpp"

#include "yaml-cpp/ostream_wrapper.h"



using namespace YAML;

using namespace Utils;



class WriteTagTest_636 : public ::testing::Test {

protected:

    std::ostringstream oss;

    ostream_wrapper out{oss};

};



TEST_F(WriteTagTest_636, NormalOperationNonVerbatim_636) {

    std::string tag = "example";

    EXPECT_TRUE(WriteTag(out, tag, false));

    EXPECT_EQ("!example", oss.str());

}



TEST_F(WriteTagTest_636, NormalOperationVerbatim_636) {

    std::string tag = "http://example.com";

    EXPECT_TRUE(WriteTag(out, tag, true));

    EXPECT_EQ("!<http://example.com>", oss.str());

}



TEST_F(WriteTagTest_636, BoundaryConditionEmptyStringNonVerbatim_636) {

    std::string tag = "";

    EXPECT_FALSE(WriteTag(out, tag, false));

    EXPECT_EQ("", oss.str());

}



TEST_F(WriteTagTest_636, BoundaryConditionEmptyStringVerbatim_636) {

    std::string tag = "";

    EXPECT_FALSE(WriteTag(out, tag, true));

    EXPECT_EQ("", oss.str());

}



TEST_F(WriteTagTest_636, ExceptionalCaseInvalidCharactersNonVerbatim_636) {

    std::string tag = "exa mple";

    EXPECT_FALSE(WriteTag(out, tag, false));

    EXPECT_EQ("!exa", oss.str());

}



TEST_F(WriteTagTest_636, ExceptionalCaseInvalidCharactersVerbatim_636) {

    std::string tag = "http://exa mple.com";

    EXPECT_FALSE(WriteTag(out, tag, true));

    EXPECT_EQ("!<http://exa", oss.str());

}



TEST_F(WriteTagTest_636, ValidUriWithSpecialCharactersVerbatim_636) {

    std::string tag = "http://example.com/path?query=123#fragment";

    EXPECT_TRUE(WriteTag(out, tag, true));

    EXPECT_EQ("!<http://example.com/path?query=123#fragment>", oss.str());

}



TEST_F(WriteTagTest_636, ValidUriWithSpecialCharactersNonVerbatim_636) {

    std::string tag = "http://example.com/path?query=123#fragment";

    EXPECT_FALSE(WriteTag(out, tag, false));

    EXPECT_EQ("!http", oss.str());

}



TEST_F(WriteTagTest_636, ValidShortUriNonVerbatim_636) {

    std::string tag = "ex";

    EXPECT_TRUE(WriteTag(out, tag, false));

    EXPECT_EQ("!ex", oss.str());

}
