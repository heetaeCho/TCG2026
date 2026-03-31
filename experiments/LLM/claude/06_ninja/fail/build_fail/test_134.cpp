#include "gtest/gtest.h"

// We need to test the IsPathSeparator function which is static in util.cc
// Since it's static, we can't directly access it from outside the translation unit.
// However, it's likely used by public functions in util.h. Let's include the header
// and test through the public API that uses IsPathSeparator.

// Based on the ninja codebase, util.h typically exposes functions like:
// - bool CanonicalizePath(string* path, uint64_t* slash_bits, string* err);
// - bool CanonicalizePath(char* path, size_t* len, uint64_t* slash_bits, string* err);

#include "util.h"
#include <string>
#include <cstdint>

class IsPathSeparatorTest_134 : public ::testing::Test {
protected:
  // Helper to test path canonicalization which internally uses IsPathSeparator
  bool CanonicalizePath(std::string* path, std::string* err) {
    uint64_t slash_bits;
    return ::CanonicalizePath(path, &slash_bits, err);
  }
};

// Test that forward slash is recognized as path separator
TEST_F(IsPathSeparatorTest_134, ForwardSlashIsPathSeparator_134) {
  std::string path = "foo/bar";
  std::string err;
  EXPECT_TRUE(CanonicalizePath(&path, &err));
  EXPECT_EQ("", err);
  // Path should be canonicalized properly, meaning '/' was recognized as separator
  EXPECT_EQ("foo/bar", path);
}

// Test canonicalization with multiple forward slashes
TEST_F(IsPathSeparatorTest_134, MultipleForwardSlashes_134) {
  std::string path = "foo//bar";
  std::string err;
  EXPECT_TRUE(CanonicalizePath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_EQ("foo/bar", path);
}

// Test canonicalization with dot components
TEST_F(IsPathSeparatorTest_134, DotInPath_134) {
  std::string path = "foo/./bar";
  std::string err;
  EXPECT_TRUE(CanonicalizePath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_EQ("foo/bar", path);
}

// Test canonicalization with double dot components
TEST_F(IsPathSeparatorTest_134, DoubleDotInPath_134) {
  std::string path = "foo/bar/../baz";
  std::string err;
  EXPECT_TRUE(CanonicalizePath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_EQ("foo/baz", path);
}

// Test simple filename with no separators
TEST_F(IsPathSeparatorTest_134, NoSeparator_134) {
  std::string path = "foobar";
  std::string err;
  EXPECT_TRUE(CanonicalizePath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_EQ("foobar", path);
}

// Test empty path
TEST_F(IsPathSeparatorTest_134, EmptyPath_134) {
  std::string path = "";
  std::string err;
  EXPECT_FALSE(CanonicalizePath(&path, &err));
  EXPECT_NE("", err);
}

// Test trailing slash
TEST_F(IsPathSeparatorTest_134, TrailingSlash_134) {
  std::string path = "foo/bar/";
  std::string err;
  EXPECT_TRUE(CanonicalizePath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_EQ("foo/bar", path);
}

// Test leading dot-slash
TEST_F(IsPathSeparatorTest_134, LeadingDotSlash_134) {
  std::string path = "./foo";
  std::string err;
  EXPECT_TRUE(CanonicalizePath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_EQ("foo", path);
}

// Test path with only a slash
TEST_F(IsPathSeparatorTest_134, OnlySlash_134) {
  std::string path = "/";
  std::string err;
  EXPECT_TRUE(CanonicalizePath(&path, &err));
  EXPECT_EQ("", err);
}

#ifdef _WIN32
// Test that backslash is recognized as path separator on Windows
TEST_F(IsPathSeparatorTest_134, BackslashIsPathSeparatorOnWindows_134) {
  std::string path = "foo\\bar";
  std::string err;
  EXPECT_TRUE(CanonicalizePath(&path, &err));
  EXPECT_EQ("", err);
  // On Windows, backslash should be treated as a path separator
  EXPECT_EQ("foo/bar", path);
}

// Test mixed separators on Windows
TEST_F(IsPathSeparatorTest_134, MixedSeparatorsOnWindows_134) {
  std::string path = "foo\\bar/baz";
  std::string err;
  EXPECT_TRUE(CanonicalizePath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_EQ("foo/bar/baz", path);
}

// Test double backslash on Windows
TEST_F(IsPathSeparatorTest_134, DoubleBackslashOnWindows_134) {
  std::string path = "foo\\\\bar";
  std::string err;
  EXPECT_TRUE(CanonicalizePath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_EQ("foo/bar", path);
}
#endif

// Test deeply nested path
TEST_F(IsPathSeparatorTest_134, DeeplyNestedPath_134) {
  std::string path = "a/b/c/d/e/f";
  std::string err;
  EXPECT_TRUE(CanonicalizePath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_EQ("a/b/c/d/e/f", path);
}

// Test multiple parent references
TEST_F(IsPathSeparatorTest_134, MultipleParentReferences_134) {
  std::string path = "a/b/c/../../d";
  std::string err;
  EXPECT_TRUE(CanonicalizePath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_EQ("a/d", path);
}

// Test path starting with absolute forward slash
TEST_F(IsPathSeparatorTest_134, AbsolutePath_134) {
  std::string path = "/foo/bar";
  std::string err;
  EXPECT_TRUE(CanonicalizePath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_EQ("/foo/bar", path);
}

// Test path that is just a dot
TEST_F(IsPathSeparatorTest_134, JustDot_134) {
  std::string path = ".";
  std::string err;
  EXPECT_TRUE(CanonicalizePath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_EQ(".", path);
}

// Non-separator characters should not be treated as separators
TEST_F(IsPathSeparatorTest_134, NonSeparatorCharacters_134) {
  std::string path = "foo-bar_baz.txt";
  std::string err;
  EXPECT_TRUE(CanonicalizePath(&path, &err));
  EXPECT_EQ("", err);
  EXPECT_EQ("foo-bar_baz.txt", path);
}
