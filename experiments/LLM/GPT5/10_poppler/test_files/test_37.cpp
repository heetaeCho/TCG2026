// File: append_to_path_test_37.cc
// Unit tests for appendToPath (./TestProjects/poppler/goo/gfile.cc)

#include <gtest/gtest.h>

#include <string>

#include "goo/GooString.h"

// Prefer including the public header if it exists in the codebase.
#if __has_include("goo/gfile.h")
#include "goo/gfile.h"
#else
// Fallback declaration (kept minimal; no re-implementation).
GooString *appendToPath(GooString *path, const char *fileName);
#endif

namespace {

class AppendToPathTest_37 : public ::testing::Test {};

static std::string S(const GooString &gs) {
  return gs.toStr();
}

TEST_F(AppendToPathTest_37, ReturnsSamePointer_37) {
  GooString path("base");
  GooString *ret = appendToPath(&path, "file");
  EXPECT_EQ(ret, &path);
}

#ifndef _WIN32

TEST_F(AppendToPathTest_37, DotDoesNotChangePath_NonWindows_37) {
  GooString path("a/b");
  const std::string before = S(path);

  GooString *ret = appendToPath(&path, ".");
  EXPECT_EQ(ret, &path);
  EXPECT_EQ(S(path), before);
}

TEST_F(AppendToPathTest_37, DotDoesNotChangeEmptyPath_NonWindows_37) {
  GooString path("");
  GooString *ret = appendToPath(&path, ".");
  EXPECT_EQ(ret, &path);
  EXPECT_EQ(S(path), "");
}

TEST_F(AppendToPathTest_37, AppendsWithSlashWhenNeeded_NonWindows_37) {
  GooString path("usr");
  GooString *ret = appendToPath(&path, "bin");
  EXPECT_EQ(ret, &path);
  EXPECT_EQ(S(path), "usr/bin");
}

TEST_F(AppendToPathTest_37, DoesNotDuplicateSlashWhenAlreadyPresent_NonWindows_37) {
  GooString path("usr/");
  GooString *ret = appendToPath(&path, "bin");
  EXPECT_EQ(ret, &path);
  EXPECT_EQ(S(path), "usr/bin");
}

TEST_F(AppendToPathTest_37, AppendToEmptyPath_NonWindows_37) {
  GooString path("");
  GooString *ret = appendToPath(&path, "bin");
  EXPECT_EQ(ret, &path);
  EXPECT_EQ(S(path), "bin");
}

TEST_F(AppendToPathTest_37, AppendToRootPath_NonWindows_37) {
  GooString path("/");
  GooString *ret = appendToPath(&path, "etc");
  EXPECT_EQ(ret, &path);
  EXPECT_EQ(S(path), "/etc");
}

TEST_F(AppendToPathTest_37, DotDotRemovesLastComponentWhenSlashExists_NonWindows_37) {
  GooString path("/usr/bin");
  GooString *ret = appendToPath(&path, "..");
  EXPECT_EQ(ret, &path);
  EXPECT_EQ(S(path), "/usr");
}

TEST_F(AppendToPathTest_37, DotDotOnSingleComponentRelativeBecomesDotDot_NonWindows_37) {
  GooString path("usr");
  GooString *ret = appendToPath(&path, "..");
  EXPECT_EQ(ret, &path);
  EXPECT_EQ(S(path), "..");
}

TEST_F(AppendToPathTest_37, DotDotOnRootStaysRoot_NonWindows_37) {
  GooString path("/");
  GooString *ret = appendToPath(&path, "..");
  EXPECT_EQ(ret, &path);
  EXPECT_EQ(S(path), "/");
}

TEST_F(AppendToPathTest_37, DotDotOnAbsoluteSingleComponentStaysRoot_NonWindows_37) {
  GooString path("/usr");
  GooString *ret = appendToPath(&path, "..");
  EXPECT_EQ(ret, &path);
  EXPECT_EQ(S(path), "/");
}

#else  // _WIN32

TEST_F(AppendToPathTest_37, AppendsAndNormalizesToFullPath_Windows_37) {
  GooString path("C:/");  // Provide something that is already absolute to reduce environment sensitivity.
  GooString *ret = appendToPath(&path, "Windows");
  EXPECT_EQ(ret, &path);

  const std::string out = S(path);
  EXPECT_FALSE(out.empty());

  // Black-box friendly checks: result should still mention the appended leaf somewhere.
  EXPECT_NE(out.find("Windows"), std::string::npos);
}

TEST_F(AppendToPathTest_37, DotDoesNotChangePath_Windows_37) {
  GooString path("C:/Temp");
  const std::string before = S(path);
  GooString *ret = appendToPath(&path, ".");
  EXPECT_EQ(ret, &path);
  EXPECT_EQ(S(path), before);
}

#endif  // _WIN32

}  // namespace