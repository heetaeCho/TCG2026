#include <gtest/gtest.h>

#include "util.h"



class CanonicalizePathTest_135 : public ::testing::Test {

protected:

    char path[256];

    size_t len;

    uint64_t slash_bits;



    void SetUp() override {

        memset(path, 0, sizeof(path));

        len = 0;

        slash_bits = 0;

    }

};



TEST_F(CanonicalizePathTest_135, EmptyPath_135) {

    strcpy(path, "");

    len = strlen(path);

    CanonicalizePath(path, &len, &slash_bits);

    EXPECT_EQ(len, 1u);

    EXPECT_STREQ(path, ".");

    EXPECT_EQ(slash_bits, 0u);

}



TEST_F(CanonicalizePathTest_135, SingleSlash_135) {

    strcpy(path, "/");

    len = strlen(path);

    CanonicalizePath(path, &len, &slash_bits);

    EXPECT_EQ(len, 1u);

    EXPECT_STREQ(path, "/");

#ifdef _WIN32

    EXPECT_EQ(slash_bits, 1u);

#else

    EXPECT_EQ(slash_bits, 0u);

#endif

}



TEST_F(CanonicalizePathTest_135, MultipleSlashes_135) {

    strcpy(path, "///");

    len = strlen(path);

    CanonicalizePath(path, &len, &slash_bits);

    EXPECT_EQ(len, 1u);

    EXPECT_STREQ(path, "/");

#ifdef _WIN32

    EXPECT_EQ(slash_bits, 7u); // Three slashes in binary: 111

#else

    EXPECT_EQ(slash_bits, 0u);

#endif

}



TEST_F(CanonicalizePathTest_135, DotInPath_135) {

    strcpy(path, "foo/./bar");

    len = strlen(path);

    CanonicalizePath(path, &len, &slash_bits);

    EXPECT_EQ(len, 7u);

    EXPECT_STREQ(path, "foo/bar");

#ifdef _WIN32

    EXPECT_EQ(slash_bits, 6u); // Two slashes in binary: 110

#else

    EXPECT_EQ(slash_bits, 0u);

#endif

}



TEST_F(CanonicalizePathTest_135, DotDotInPath_135) {

    strcpy(path, "foo/../bar");

    len = strlen(path);

    CanonicalizePath(path, &len, &slash_bits);

    EXPECT_EQ(len, 4u);

    EXPECT_STREQ(path, "bar");

#ifdef _WIN32

    EXPECT_EQ(slash_bits, 6u); // Two slashes in binary: 110

#else

    EXPECT_EQ(slash_bits, 0u);

#endif

}



TEST_F(CanonicalizePathTest_135, DotDotAtStart_135) {

    strcpy(path, "../foo");

    len = strlen(path);

    CanonicalizePath(path, &len, &slash_bits);

    EXPECT_EQ(len, 4u);

    EXPECT_STREQ(path, "../foo");

#ifdef _WIN32

    EXPECT_EQ(slash_bits, 6u); // Two slashes in binary: 110

#else

    EXPECT_EQ(slash_bits, 0u);

#endif

}



TEST_F(CanonicalizePathTest_135, DotDotPastRoot_135) {

    strcpy(path, "foo/../../bar");

    len = strlen(path);

    CanonicalizePath(path, &len, &slash_bits);

    EXPECT_EQ(len, 4u);

    EXPECT_STREQ(path, "../bar");

#ifdef _WIN32

    EXPECT_EQ(slash_bits, 14u); // Three slashes in binary: 1110

#else

    EXPECT_EQ(slash_bits, 0u);

#endif

}



TEST_F(CanonicalizePathTest_135, ComplexPath_135) {

    strcpy(path, "a/b/c/../../d/e/../f");

    len = strlen(path);

    CanonicalizePath(path, &len, &slash_bits);

    EXPECT_EQ(len, 7u);

    EXPECT_STREQ(path, "a/d/f");

#ifdef _WIN32

    EXPECT_EQ(slash_bits, 14u); // Three slashes in binary: 1110

#else

    EXPECT_EQ(slash_bits, 0u);

#endif

}



TEST_F(CanonicalizePathTest_135, TrailingDot_135) {

    strcpy(path, "foo/bar.");

    len = strlen(path);

    CanonicalizePath(path, &len, &slash_bits);

    EXPECT_EQ(len, 7u);

    EXPECT_STREQ(path, "foo/bar.");

#ifdef _WIN32

    EXPECT_EQ(slash_bits, 6u); // Two slashes in binary: 110

#else

    EXPECT_EQ(slash_bits, 0u);

#endif

}



TEST_F(CanonicalizePathTest_135, TrailingDotDot_135) {

    strcpy(path, "foo/bar..");

    len = strlen(path);

    CanonicalizePath(path, &len, &slash_bits);

    EXPECT_EQ(len, 8u);

    EXPECT_STREQ(path, "foo/bar..");

#ifdef _WIN32

    EXPECT_EQ(slash_bits, 6u); // Two slashes in binary: 110

#else

    EXPECT_EQ(slash_bits, 0u);

#endif

}



TEST_F(CanonicalizePathTest_135, WindowsStylePath_135) {

#ifdef _WIN32

    strcpy(path, "C:\\foo\\bar");

    len = strlen(path);

    CanonicalizePath(path, &len, &slash_bits);

    EXPECT_EQ(len, 9u);

    EXPECT_STREQ(path, "C:/foo/bar");

    EXPECT_EQ(slash_bits, 6u); // Two slashes in binary: 110

#endif

}



TEST_F(CanonicalizePathTest_135, WindowsStyleDoubleSlashes_135) {

#ifdef _WIN32

    strcpy(path, "C:\\\\foo\\\\bar");

    len = strlen(path);

    CanonicalizePath(path, &len, &slash_bits);

    EXPECT_EQ(len, 9u);

    EXPECT_STREQ(path, "C:/foo/bar");

    EXPECT_EQ(slash_bits, 14u); // Three slashes in binary: 1110

#endif

}
