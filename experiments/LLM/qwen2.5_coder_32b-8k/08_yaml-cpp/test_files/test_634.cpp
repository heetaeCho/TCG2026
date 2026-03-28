#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "yaml-cpp/ostream_wrapper.h"

#include "emitterutils.cpp"



using namespace YAML::Utils;

using namespace YAML;



class WriteAliasTest_634 : public ::testing::Test {

protected:

    std::ostringstream oss;

    ostream_wrapper out{oss};

};



TEST_F(WriteAliasTest_634, NormalOperation_634) {

    const char* alias = "alias1";

    std::size_t size = strlen(alias);

    bool result = WriteAlias(out, alias, size);

    EXPECT_TRUE(result);

    EXPECT_EQ(oss.str(), "*alias1");

}



TEST_F(WriteAliasTest_634, EmptyString_634) {

    const char* empty_alias = "";

    std::size_t size = 0;

    bool result = WriteAlias(out, empty_alias, size);

    EXPECT_TRUE(result);

    EXPECT_EQ(oss.str(), "*");

}



TEST_F(WriteAliasTest_634, SingleCharacterAlias_634) {

    const char* single_char_alias = "a";

    std::size_t size = 1;

    bool result = WriteAlias(out, single_char_alias, size);

    EXPECT_TRUE(result);

    EXPECT_EQ(oss.str(), "*a");

}



TEST_F(WriteAliasTest_634, LargeAlias_634) {

    const char* large_alias = "averylongaliasname";

    std::size_t size = strlen(large_alias);

    bool result = WriteAlias(out, large_alias, size);

    EXPECT_TRUE(result);

    EXPECT_EQ(oss.str(), "*averylongaliasname");

}
