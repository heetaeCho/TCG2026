#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <string>

#include "src/util.cc"  // Assuming this is where CanonicalizePath is declared



using ::testing::_;

using ::testing::Eq;



class CanonicalizePathTest_133 : public ::testing::Test {

protected:

    std::string path;

    uint64_t slash_bits;



    void SetUp() override {

        path.clear();

        slash_bits = 0;

    }

};



TEST_F(CanonicalizePathTest_133, EmptyString_NoChange_133) {

    CanonicalizePath(&path, &slash_bits);

    EXPECT_EQ(path, "");

    EXPECT_EQ(slash_bits, 0);

}



TEST_F(CanonicalizePathTest_133, SingleCharacter_NoChange_133) {

    path = "a";

    CanonicalizePath(&path, &slash_bits);

    EXPECT_EQ(path, "a");

    EXPECT_EQ(slash_bits, 0);

}



TEST_F(CanonicalizePathTest_133, SimplePath_NoChange_133) {

    path = "abc";

    CanonicalizePath(&path, &slash_bits);

    EXPECT_EQ(path, "abc");

    EXPECT_EQ(slash_bits, 0);

}



TEST_F(CanonicalizePathTest_133, PathWithSingleSlash_SetBit_133) {

    path = "a/b";

    CanonicalizePath(&path, &slash_bits);

    EXPECT_EQ(path, "a/b");

    EXPECT_EQ(slash_bits, 2); // Assuming slash_bits is a bitmask and '/' at position 1 sets the second bit

}



TEST_F(CanonicalizePathTest_133, PathWithMultipleSlashes_SetBits_133) {

    path = "a/b/c/d";

    CanonicalizePath(&path, &slash_bits);

    EXPECT_EQ(path, "a/b/c/d");

    EXPECT_EQ(slash_bits, 0x3E); // Assuming slash_bits is a bitmask and '/' at positions 1,2,3,4 set the respective bits

}



TEST_F(CanonicalizePathTest_133, PathWithTrailingSlash_Removed_133) {

    path = "abc/";

    CanonicalizePath(&path, &slash_bits);

    EXPECT_EQ(path, "abc");

    EXPECT_EQ(slash_bits, 2); // Assuming slash_bits is a bitmask and '/' at position 1 sets the second bit

}



TEST_F(CanonicalizePathTest_133, PathWithMultipleTrailingSlashes_Removed_133) {

    path = "abc///";

    CanonicalizePath(&path, &slash_bits);

    EXPECT_EQ(path, "abc");

    EXPECT_EQ(slash_bits, 2); // Assuming slash_bits is a bitmask and '/' at position 1 sets the second bit

}



TEST_F(CanonicalizePathTest_133, PathWithDot_NoChange_133) {

    path = "./a/b";

    CanonicalizePath(&path, &slash_bits);

    EXPECT_EQ(path, "./a/b");

    EXPECT_EQ(slash_bits, 6); // Assuming slash_bits is a bitmask and '/' at positions 1,2 set the respective bits

}



TEST_F(CanonicalizePathTest_133, PathWithDots_NoChange_133) {

    path = "a/./b";

    CanonicalizePath(&path, &slash_bits);

    EXPECT_EQ(path, "a/./b");

    EXPECT_EQ(slash_bits, 6); // Assuming slash_bits is a bitmask and '/' at positions 1,2 set the respective bits

}
