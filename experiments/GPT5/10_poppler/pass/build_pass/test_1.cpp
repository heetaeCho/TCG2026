// File: test_gbasename_1.cc
// Unit tests for ./TestProjects/poppler/goo/gbasename.cc
//
// NOTE: This test treats gbasename() as a black box and validates only
// observable behavior via its public interface.

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstring>
#include <string>

using ::testing::AnyOf;
using ::testing::Eq;

// Function under test (implemented in goo/gbasename.cc)
std::string gbasename(const char* filename);

namespace {

TEST(GBaseNameTest_1, ReturnsSameNameForPlainFilename_1) {
  EXPECT_EQ(gbasename("file.txt"), "file.txt");
  EXPECT_EQ(gbasename("README"), "README");
}

TEST(GBaseNameTest_1, ReturnsLastPathComponentForForwardSlashPaths_1) {
  EXPECT_EQ(gbasename("dir/sub/file.tar.gz"), "file.tar.gz");
  EXPECT_EQ(gbasename("/usr/local/bin/tool"), "tool");
}

TEST(GBaseNameTest_1, HandlesHiddenFiles_1) {
  EXPECT_EQ(gbasename(".bashrc"), ".bashrc");
  EXPECT_EQ(gbasename("dir/.gitignore"), ".gitignore");
}

TEST(GBaseNameTest_1, DoesNotModifyInputBuffer_1) {
  char buf[] = "dir/sub/file.txt";
  const std::string before(buf);

  (void)gbasename(buf);

  EXPECT_EQ(std::string(buf), before);
}

TEST(GBaseNameTest_1, HandlesDotAndDoubleDot_1) {
  // These are well-defined, common basename expectations across platforms.
  EXPECT_EQ(gbasename("."), ".");
  EXPECT_EQ(gbasename(".."), "..");
}

#ifdef _MSC_VER

TEST(GBaseNameTest_1, WindowsHandlesBackslashPaths_1) {
  EXPECT_EQ(gbasename(R"(C:\dir\sub\file.txt)"), "file.txt");
  EXPECT_EQ(gbasename(R"(dir\sub\name)"), "name");
}

TEST(GBaseNameTest_1, WindowsHandlesDriveOnlyAndRootLikeInputs_1) {
  // Boundary-ish inputs: ensure it doesn't crash and returns some plausible basename.
  // Exact Windows semantics can vary; validate a small set of acceptable results.
  EXPECT_THAT(gbasename(R"(C:\)"), AnyOf(Eq(""), Eq("\\"), Eq("C:\\"), Eq("C:")));
  EXPECT_THAT(gbasename(R"(C:)"), AnyOf(Eq(""), Eq("C:"), Eq("C")));
}

#else  // POSIX / non-MSVC

TEST(GBaseNameTest_1, PosixTreatsBackslashAsNormalCharacter_1) {
  // On POSIX, backslash is not a path separator for basename().
  EXPECT_EQ(gbasename(R"(C:\dir\sub\file.txt)"), R"(C:\dir\sub\file.txt)");
}

TEST(GBaseNameTest_1, PosixHandlesTrailingSlashPaths_1) {
  // basename("/usr/local/") is commonly "local" (libgen basename behavior).
  // Some platforms may differ in edge-cases, so allow a minimal set of plausible outputs.
  EXPECT_THAT(gbasename("/usr/local/"), AnyOf(Eq("local"), Eq("")));
  EXPECT_THAT(gbasename("dir/sub/"), AnyOf(Eq("sub"), Eq("")));
}

#endif

}  // namespace