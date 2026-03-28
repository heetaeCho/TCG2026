#include <gtest/gtest.h>
#include <string>
#include <cstdint>

// Declaration of the function under test
void CanonicalizePath(std::string* path, uint64_t* slash_bits);

class CanonicalizePathTest_133 : public ::testing::Test {
 protected:
  uint64_t slash_bits_;
  void SetUp() override {
    slash_bits_ = 0;
  }
};

TEST_F(CanonicalizePathTest_133, EmptyPath_133) {
  std::string path = "";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("", path);
}

TEST_F(CanonicalizePathTest_133, SimplePath_133) {
  std::string path = "foo.cc";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("foo.cc", path);
}

TEST_F(CanonicalizePathTest_133, PathWithDirectory_133) {
  std::string path = "foo/bar.cc";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("foo/bar.cc", path);
}

TEST_F(CanonicalizePathTest_133, PathWithDotDot_133) {
  std::string path = "foo/../bar.cc";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("bar.cc", path);
}

TEST_F(CanonicalizePathTest_133, PathWithDot_133) {
  std::string path = "./foo.cc";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("foo.cc", path);
}

TEST_F(CanonicalizePathTest_133, PathWithMultipleDots_133) {
  std::string path = "./foo/./bar.cc";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("foo/bar.cc", path);
}

TEST_F(CanonicalizePathTest_133, PathWithTrailingSlash_133) {
  std::string path = "foo/bar/";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("foo/bar", path);
}

TEST_F(CanonicalizePathTest_133, PathWithDoubleSlash_133) {
  std::string path = "foo//bar.cc";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("foo/bar.cc", path);
}

TEST_F(CanonicalizePathTest_133, PathWithDotDotAtStart_133) {
  std::string path = "../foo.cc";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("../foo.cc", path);
}

TEST_F(CanonicalizePathTest_133, PathWithMultipleDotDot_133) {
  std::string path = "foo/bar/baz/../../qux.cc";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("foo/qux.cc", path);
}

TEST_F(CanonicalizePathTest_133, SingleDot_133) {
  std::string path = ".";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ(".", path);
}

TEST_F(CanonicalizePathTest_133, JustSlash_133) {
  std::string path = "/";
  CanonicalizePath(&path, &slash_bits_);
  // Root path should remain
  EXPECT_FALSE(path.empty());
}

TEST_F(CanonicalizePathTest_133, AbsolutePath_133) {
  std::string path = "/foo/bar.cc";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("/foo/bar.cc", path);
}

TEST_F(CanonicalizePathTest_133, AbsolutePathWithDotDot_133) {
  std::string path = "/foo/../bar.cc";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("/bar.cc", path);
}

TEST_F(CanonicalizePathTest_133, AbsolutePathWithDot_133) {
  std::string path = "/foo/./bar.cc";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("/foo/bar.cc", path);
}

TEST_F(CanonicalizePathTest_133, PathDoesNotGrowInSize_133) {
  std::string path = "foo/../bar/../baz.cc";
  size_t original_size = path.size();
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_LE(path.size(), original_size);
}

TEST_F(CanonicalizePathTest_133, PathWithBackslash_133) {
  std::string path = "foo\\bar.cc";
  CanonicalizePath(&path, &slash_bits_);
  // The path should be canonicalized; backslashes may be converted or kept
  EXPECT_FALSE(path.empty());
}

TEST_F(CanonicalizePathTest_133, PathWithMixedSlashes_133) {
  std::string path = "foo/bar\\baz.cc";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_FALSE(path.empty());
}

TEST_F(CanonicalizePathTest_133, DotDotBeyondRoot_133) {
  std::string path = "/../foo.cc";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("/foo.cc", path);
}

TEST_F(CanonicalizePathTest_133, MultipleDotDotAtStart_133) {
  std::string path = "../../foo/bar.cc";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("../../foo/bar.cc", path);
}

TEST_F(CanonicalizePathTest_133, SlashBitsInitialized_133) {
  std::string path = "foo/bar/baz.cc";
  uint64_t bits = 0xFFFFFFFF;
  CanonicalizePath(&path, &bits);
  // slash_bits should be set to some value (implementation-defined)
  // Just ensure no crash and path is valid
  EXPECT_EQ("foo/bar/baz.cc", path);
}

TEST_F(CanonicalizePathTest_133, DeepNestedPath_133) {
  std::string path = "a/b/c/d/e/f/g.cc";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("a/b/c/d/e/f/g.cc", path);
}

TEST_F(CanonicalizePathTest_133, SingleCharFilename_133) {
  std::string path = "a";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("a", path);
}

TEST_F(CanonicalizePathTest_133, DotDotCancelsOneLevel_133) {
  std::string path = "a/b/../c";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("a/c", path);
}

TEST_F(CanonicalizePathTest_133, ConsecutiveDotDirs_133) {
  std::string path = "a/././././b";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("a/b", path);
}

TEST_F(CanonicalizePathTest_133, TrailingDot_133) {
  std::string path = "a/b/.";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("a/b", path);
}

TEST_F(CanonicalizePathTest_133, TrailingDotDot_133) {
  std::string path = "a/b/c/..";
  CanonicalizePath(&path, &slash_bits_);
  EXPECT_EQ("a/b", path);
}
