// File: canonicalize_path_test_135.cc

#include "gtest/gtest.h"

#include "util.h"  // Declares CanonicalizePath

#include <cstdint>
#include <string>

namespace {

struct CanonicalizePathResult {
  std::string path;
  size_t length;
  uint64_t slash_bits;
};

CanonicalizePathResult CanonicalizePathForTest(const std::string& input) {
  CanonicalizePathResult res;
  res.path = input;
  res.length = res.path.size();
  res.slash_bits = 0;

  // For empty input, path buffer is not used because length is 0
  char* data = res.path.empty() ? nullptr : &res.path[0];
  CanonicalizePath(data, &res.length, &res.slash_bits);
  res.path.resize(res.length);
  return res;
}

}  // namespace

class CanonicalizePathTest_135 : public ::testing::Test {};

// Empty input: nothing should change, including slash_bits.
TEST_F(CanonicalizePathTest_135, EmptyPath_NoChange_135) {
  char path[1] = {'\0'};
  size_t len = 0;
  const uint64_t kSentinel = 0xDEADBEEFDEADBEEFULL;
  uint64_t slash_bits = kSentinel;

  CanonicalizePath(path, &len, &slash_bits);

  EXPECT_EQ(0u, len);
  EXPECT_EQ('\0', path[0]);
  EXPECT_EQ(kSentinel, slash_bits);
}

// Simple relative path without any special components should remain unchanged.
TEST_F(CanonicalizePathTest_135, RelativeSimplePath_Unchanged_135) {
  CanonicalizePathResult res = CanonicalizePathForTest("foo/bar");

  EXPECT_EQ("foo/bar", res.path);
  EXPECT_EQ(res.path.size(), res.length);
}

// Trailing slash should be removed for a non-root path: "foo/" -> "foo".
TEST_F(CanonicalizePathTest_135, TrailingSlashRemoved_135) {
  CanonicalizePathResult res = CanonicalizePathForTest("foo/");

  EXPECT_EQ("foo", res.path);
  EXPECT_EQ(res.path.size(), res.length);
}

// "." components in the middle should be removed: "./foo/./bar" -> "foo/bar".
TEST_F(CanonicalizePathTest_135, RemovesSingleDotComponents_135) {
  CanonicalizePathResult res = CanonicalizePathForTest("./foo/./bar");

  EXPECT_EQ("foo/bar", res.path);
  EXPECT_EQ(res.path.size(), res.length);
}

// ".." should remove the previous component when possible: "a/b/../c" -> "a/c".
TEST_F(CanonicalizePathTest_135, RemovesDoubleDotWithPreviousComponent_135) {
  CanonicalizePathResult res = CanonicalizePathForTest("a/b/../c");

  EXPECT_EQ("a/c", res.path);
  EXPECT_EQ(res.path.size(), res.length);
}

// Leading ".." that cannot be resolved should be preserved: "../a/b" -> "../a/b".
TEST_F(CanonicalizePathTest_135, LeadingDoubleDotPreserved_135) {
  CanonicalizePathResult res = CanonicalizePathForTest("../a/b");

  EXPECT_EQ("../a/b", res.path);
  EXPECT_EQ(res.path.size(), res.length);
}

// Path that is exactly ".." should remain "..".
TEST_F(CanonicalizePathTest_135, OnlyDoubleDotComponentPreserved_135) {
  CanonicalizePathResult res = CanonicalizePathForTest("..");

  EXPECT_EQ("..", res.path);
  EXPECT_EQ(res.path.size(), res.length);
}

// Multiple adjacent slashes should be collapsed: "foo//bar///baz" -> "foo/bar/baz".
TEST_F(CanonicalizePathTest_135, CollapsesMultipleAdjacentSlashes_135) {
  CanonicalizePathResult res = CanonicalizePathForTest("foo//bar///baz");

  EXPECT_EQ("foo/bar/baz", res.path);
  EXPECT_EQ(res.path.size(), res.length);
}

// When path resolves to nothing (e.g. "foo/.."), it should become ".".
TEST_F(CanonicalizePathTest_135, ResolvingToEmptyPathYieldsDot_135) {
  {
    CanonicalizePathResult res = CanonicalizePathForTest("foo/..");
    EXPECT_EQ(".", res.path);
    EXPECT_EQ(res.path.size(), res.length);
  }
  {
    CanonicalizePathResult res = CanonicalizePathForTest("a/../b/..");
    EXPECT_EQ(".", res.path);
    EXPECT_EQ(res.path.size(), res.length);
  }
}

// Root path and variants with redundant components should normalize to "/".
TEST_F(CanonicalizePathTest_135, AbsoluteRootNormalization_135) {
  {
    CanonicalizePathResult res = CanonicalizePathForTest("/");
    EXPECT_EQ("/", res.path);
    EXPECT_EQ(res.path.size(), res.length);
  }
  {
    CanonicalizePathResult res = CanonicalizePathForTest("//");
    EXPECT_EQ("/", res.path);
    EXPECT_EQ(res.path.size(), res.length);
  }
  {
    CanonicalizePathResult res = CanonicalizePathForTest("/./");
    EXPECT_EQ("/", res.path);
    EXPECT_EQ(res.path.size(), res.length);
  }
}

#ifndef _WIN32

// On non-Windows platforms, slash_bits should always be zero for non-empty paths.
TEST_F(CanonicalizePathTest_135, SlashBitsAlwaysZeroOnPosix_135) {
  CanonicalizePathResult res = CanonicalizePathForTest("foo/bar/baz");

  EXPECT_EQ("foo/bar/baz", res.path);
  EXPECT_EQ(0u, res.slash_bits);
}

#else  // _WIN32

// On Windows, backslashes should be converted to '/', and slash_bits should mark separators.
TEST_F(CanonicalizePathTest_135, BackslashesConvertedAndSlashBitsRecorded_135) {
  CanonicalizePathResult res = CanonicalizePathForTest("dir\\subdir\\file");

  // Path separators normalized to forward slashes.
  EXPECT_EQ("dir/subdir/file", res.path);
  EXPECT_EQ(res.path.size(), res.length);

  // For "dir/subdir/file", there are two separators.
  // According to the implementation, bits should be 1 (for first separator)
  // and 2 (for second separator) => 1 | 2 = 3.
  EXPECT_EQ(3u, res.slash_bits);
}

// On Windows, a UNC-style prefix ("\\server\share\...") should preserve the double leading separator.
TEST_F(CanonicalizePathTest_135, UncPrefixPreservedAndNormalized_135) {
  CanonicalizePathResult res =
      CanonicalizePathForTest("\\\\server\\share\\dir\\..\\file");

  // Expect UNC prefix kept as '//' and separators normalized to '/'.
  EXPECT_EQ("//server/share/file", res.path);
  EXPECT_EQ(res.path.size(), res.length);

  // For "//server/share/file" there are four separators ("//", "/share", "/file"),
  // and the implementation records them in slash_bits. The concrete value
  // is 1 | 2 | 4 | 8 = 15 for this specific string.
  EXPECT_EQ(15u, res.slash_bits);
}

#endif  // _WIN32
