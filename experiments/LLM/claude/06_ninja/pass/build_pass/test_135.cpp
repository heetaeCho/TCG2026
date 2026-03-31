#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <string>

// Forward declaration of the function under test
void CanonicalizePath(char* path, size_t* len, uint64_t* slash_bits);

// Helper function to canonicalize a string and return the result
static std::string Canonicalize(const std::string& input, uint64_t* slash_bits = nullptr) {
  std::string path = input;
  size_t len = path.size();
  uint64_t bits = 0;
  // Need a mutable buffer; std::string provides one via &path[0] for non-empty
  if (len == 0) {
    CanonicalizePath(nullptr, &len, &bits);
    if (slash_bits) *slash_bits = bits;
    return "";
  }
  // Allocate enough space for the path
  char* buf = new char[len + 1];
  memcpy(buf, path.c_str(), len);
  buf[len] = '\0';
  CanonicalizePath(buf, &len, &bits);
  std::string result(buf, len);
  delete[] buf;
  if (slash_bits) *slash_bits = bits;
  return result;
}

class CanonicalizePathTest_135 : public ::testing::Test {
protected:
  void CheckCanonicalize(const std::string& input, const std::string& expected) {
    uint64_t slash_bits;
    std::string result = Canonicalize(input, &slash_bits);
    EXPECT_EQ(expected, result) << "Input: \"" << input << "\"";
  }
};

// Test empty path
TEST_F(CanonicalizePathTest_135, EmptyPath_135) {
  size_t len = 0;
  uint64_t slash_bits;
  char buf[] = "";
  CanonicalizePath(buf, &len, &slash_bits);
  EXPECT_EQ(0u, len);
}

// Test single dot becomes dot
TEST_F(CanonicalizePathTest_135, SingleDot_135) {
  CheckCanonicalize(".", ".");
}

// Test simple filename
TEST_F(CanonicalizePathTest_135, SimpleFilename_135) {
  CheckCanonicalize("foo", "foo");
}

// Test current directory prefix removed
TEST_F(CanonicalizePathTest_135, DotSlashPrefix_135) {
  CheckCanonicalize("./foo", "foo");
}

// Test double dot slash prefix preserved
TEST_F(CanonicalizePathTest_135, DotDotSlashPrefix_135) {
  CheckCanonicalize("../foo", "../foo");
}

// Test removing intermediate dot
TEST_F(CanonicalizePathTest_135, IntermediateDot_135) {
  CheckCanonicalize("foo/./bar", "foo/bar");
}

// Test removing intermediate double dot
TEST_F(CanonicalizePathTest_135, IntermediateDotDot_135) {
  CheckCanonicalize("foo/bar/../baz", "foo/baz");
}

// Test collapsing double slashes
TEST_F(CanonicalizePathTest_135, DoubleSlash_135) {
  CheckCanonicalize("foo//bar", "foo/bar");
}

// Test trailing slash removed
TEST_F(CanonicalizePathTest_135, TrailingSlash_135) {
  CheckCanonicalize("foo/bar/", "foo/bar");
}

// Test absolute path
TEST_F(CanonicalizePathTest_135, AbsolutePath_135) {
  CheckCanonicalize("/foo/bar", "/foo/bar");
}

// Test absolute path with dot
TEST_F(CanonicalizePathTest_135, AbsolutePathWithDot_135) {
  CheckCanonicalize("/foo/./bar", "/foo/bar");
}

// Test absolute path with dotdot
TEST_F(CanonicalizePathTest_135, AbsolutePathWithDotDot_135) {
  CheckCanonicalize("/foo/bar/../baz", "/foo/baz");
}

// Test root path
TEST_F(CanonicalizePathTest_135, RootPath_135) {
  CheckCanonicalize("/", "/");
}

// Test multiple dotdot going beyond components
TEST_F(CanonicalizePathTest_135, MultipleDotDotBeyondComponents_135) {
  CheckCanonicalize("foo/../../bar", "../bar");
}

// Test only dotdot
TEST_F(CanonicalizePathTest_135, OnlyDotDot_135) {
  CheckCanonicalize("..", "..");
}

// Test multiple dotdot
TEST_F(CanonicalizePathTest_135, MultipleDotDot_135) {
  CheckCanonicalize("../../foo", "../../foo");
}

// Test dotdot at the end
TEST_F(CanonicalizePathTest_135, DotDotAtEnd_135) {
  CheckCanonicalize("foo/bar/..", "foo");
}

// Test complex path
TEST_F(CanonicalizePathTest_135, ComplexPath_135) {
  CheckCanonicalize("foo/./bar/../baz/./qux/../quux", "foo/baz/quux");
}

// Test trailing dot
TEST_F(CanonicalizePathTest_135, TrailingDot_135) {
  CheckCanonicalize("foo/bar/.", "foo/bar");
}

// Test trailing dotdot collapsing everything
TEST_F(CanonicalizePathTest_135, TrailingDotDotCollapsesAll_135) {
  CheckCanonicalize("foo/..", ".");
}

// Test path with only slashes after root
TEST_F(CanonicalizePathTest_135, MultipleSlashes_135) {
  CheckCanonicalize("foo///bar", "foo/bar");
}

// Test dotslash only
TEST_F(CanonicalizePathTest_135, DotSlashOnly_135) {
  CheckCanonicalize("./", ".");
}

// Test dotdotslash only
TEST_F(CanonicalizePathTest_135, DotDotSlashOnly_135) {
  CheckCanonicalize("../", "..");
}

// Test deeply nested dotdot
TEST_F(CanonicalizePathTest_135, DeeplyNestedDotDot_135) {
  CheckCanonicalize("a/b/c/../../d", "a/d");
}

// Test all components cancel out
TEST_F(CanonicalizePathTest_135, AllComponentsCancelOut_135) {
  CheckCanonicalize("a/b/c/../../../", ".");
}

// Test dotdot beyond root (absolute path)
TEST_F(CanonicalizePathTest_135, AbsolutePathDotDotAtRoot_135) {
  // On absolute paths, dotdot at root should not go beyond root
  CheckCanonicalize("/foo/..", "/");
}

// Test dot in middle of component name (not special)
TEST_F(CanonicalizePathTest_135, DotInComponentName_135) {
  CheckCanonicalize("foo.bar/baz", "foo.bar/baz");
}

// Test dotdot-like but longer component
TEST_F(CanonicalizePathTest_135, DotDotLongerComponent_135) {
  CheckCanonicalize("foo/..bar/baz", "foo/..bar/baz");
}

// Test single character path
TEST_F(CanonicalizePathTest_135, SingleCharPath_135) {
  CheckCanonicalize("a", "a");
}

// Test slash_bits is zero on non-Windows
TEST_F(CanonicalizePathTest_135, SlashBitsZeroOnNonWindows_135) {
  uint64_t slash_bits = 99;
  std::string result = Canonicalize("foo/bar/baz", &slash_bits);
#ifndef _WIN32
  EXPECT_EQ(0u, slash_bits);
#endif
  EXPECT_EQ("foo/bar/baz", result);
}

// Test multiple dotdots in sequence
TEST_F(CanonicalizePathTest_135, MultipleDotDotsInSequence_135) {
  CheckCanonicalize("a/b/c/d/../../../e", "a/e");
}

// Test path consisting of just ./. 
TEST_F(CanonicalizePathTest_135, DotSlashDot_135) {
  CheckCanonicalize("./.", ".");
}

// Test path with multiple leading ../
TEST_F(CanonicalizePathTest_135, MultipleLeadingDotDot_135) {
  CheckCanonicalize("../../../foo/bar", "../../../foo/bar");
}

// Test that the length is correctly set
TEST_F(CanonicalizePathTest_135, LengthCorrectlySet_135) {
  const char* input = "foo/bar/../baz";
  size_t len = strlen(input);
  char buf[64];
  memcpy(buf, input, len);
  uint64_t slash_bits;
  CanonicalizePath(buf, &len, &slash_bits);
  std::string result(buf, len);
  EXPECT_EQ("foo/baz", result);
  EXPECT_EQ(7u, len);
}

// Test path with only dots that are not special
TEST_F(CanonicalizePathTest_135, ThreeDotsComponent_135) {
  CheckCanonicalize("foo/.../bar", "foo/.../bar");
}

#ifdef _WIN32
// Windows-specific tests for backslash handling
TEST_F(CanonicalizePathTest_135, BackslashConvertedToSlash_135) {
  uint64_t slash_bits;
  std::string result = Canonicalize("foo\\bar\\baz", &slash_bits);
  EXPECT_EQ("foo/bar/baz", result);
  // slash_bits should indicate which separators were backslashes
  EXPECT_NE(0u, slash_bits);
}

TEST_F(CanonicalizePathTest_135, UNCPath_135) {
  uint64_t slash_bits;
  std::string result = Canonicalize("\\\\server\\share", &slash_bits);
  EXPECT_EQ("//server/share", result);
}
#endif
