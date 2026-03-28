#include <gtest/gtest.h>

#include "XMPCore_Impl.hpp"



class IsPathPrefixTest_1867 : public ::testing::Test {

protected:

    // No additional setup needed for this function

};



TEST_F(IsPathPrefixTest_1867, FullPathMatchesPrefixExactly_1867) {

    EXPECT_TRUE(IsPathPrefix("prefix", "prefix"));

}



TEST_F(IsPathPrefixTest_1867, FullPathHasAdditionalSlashAfterPrefix_1867) {

    EXPECT_TRUE(IsPathPrefix("prefix/suffix", "prefix"));

}



TEST_F(IsPathPrefixTest_1867, FullPathHasAdditionalBracketAfterPrefix_1867) {

    EXPECT_TRUE(IsPathPrefix("prefix[suffix]", "prefix"));

}



TEST_F(IsPathPrefixTest_1867, FullPathHasAdditionalAsteriskAfterPrefix_1867) {

    EXPECT_TRUE(IsPathPrefix("prefix*suffix", "prefix"));

}



TEST_F(IsPathPrefixTest_1867, PrefixIsEmptyString_1867) {

    EXPECT_TRUE(IsPathPrefix("fullpath", ""));

}



TEST_F(IsPathPrefixTest_1867, FullPathIsShorterThanPrefix_1867) {

    EXPECT_FALSE(IsPathPrefix("pre", "prefix"));

}



TEST_F(IsPathPrefixTest_1867, PrefixDoesNotMatchFullPath_1867) {

    EXPECT_FALSE(IsPathPrefix("differentpath", "prefix"));

}



TEST_F(IsPathPrefixTest_1867, FullPathHasDifferentCharacterAfterPrefix_1867) {

    EXPECT_FALSE(IsPathPrefix("prefix.suffix", "prefix"));

}



TEST_F(IsPathPrefixTest_1867, BothFullPathAndPrefixAreEmpty_1867) {

    EXPECT_TRUE(IsPathPrefix("", ""));

}
