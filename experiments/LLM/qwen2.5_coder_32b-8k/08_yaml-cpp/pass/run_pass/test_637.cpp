#include <gtest/gtest.h>

#include "yaml-cpp/src/emitterutils.cpp"

#include "yaml-cpp/ostream_wrapper.h"

#include "yaml-cpp/src/regex_yaml.h"

#include "yaml-cpp/src/stringsource.h"



using namespace YAML::Utils;

using namespace YAML;



class WriteTagWithPrefixTest_637 : public ::testing::Test {

protected:

    std::ostringstream oss;

    ostream_wrapper out{oss};

};



TEST_F(WriteTagWithPrefixTest_637, NormalOperation_637) {

    EXPECT_TRUE(WriteTagWithPrefix(out, "example", "tag"));

    EXPECT_EQ("!example!tag", oss.str());

}



TEST_F(WriteTagWithPrefixTest_637, EmptyPrefixAndTag_637) {

    EXPECT_TRUE(WriteTagWithPrefix(out, "", ""));

    EXPECT_EQ("!!", oss.str());

}



TEST_F(WriteTagWithPrefixTest_637, OnlyPrefix_637) {

    EXPECT_TRUE(WriteTagWithPrefix(out, "example", ""));

    EXPECT_EQ("!example!", oss.str());

}



TEST_F(WriteTagWithPrefixTest_637, OnlyTag_637) {

    EXPECT_TRUE(WriteTagWithPrefix(out, "", "tag"));

    EXPECT_EQ("!!tag", oss.str());

}



TEST_F(WriteTagWithPrefixTest_637, InvalidPrefixCharacter_637) {

    EXPECT_FALSE(WriteTagWithPrefix(out, "ex-ample", "tag"));

}



TEST_F(WriteTagWithPrefixTest_637, InvalidTagCharacter_637) {

    EXPECT_FALSE(WriteTagWithPrefix(out, "example", "ta-g"));

}
