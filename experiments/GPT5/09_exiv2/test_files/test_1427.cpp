// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_makernote_int_getExiv2ConfigPath_1427.cpp
//
// Unit tests for:
//   Exiv2::Internal::getExiv2ConfigPath()
// From: ./TestProjects/exiv2/src/makernote_int.cpp

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <string>

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif

// Forward declaration (function is implemented in the production code).
namespace Exiv2 {
namespace Internal {
std::string getExiv2ConfigPath();
}  // namespace Internal
}  // namespace Exiv2

namespace {

class CurrentPathGuard final {
 public:
  CurrentPathGuard() : old_(fs::current_path()) {}
  explicit CurrentPathGuard(const fs::path& newPath) : old_(fs::current_path()) { fs::current_path(newPath); }
  ~CurrentPathGuard() {
    // Best-effort restore; don't throw from destructor.
    std::error_code ec;
    fs::current_path(old_, ec);
  }

  CurrentPathGuard(const CurrentPathGuard&) = delete;
  CurrentPathGuard& operator=(const CurrentPathGuard&) = delete;

 private:
  fs::path old_;
};

static fs::path MakeUniqueTempDir(const std::string& prefix) {
  const fs::path base = fs::temp_directory_path();
  // Use a simple uniqueness scheme (no requirement to be cryptographically unique).
  for (int i = 0; i < 200; ++i) {
    fs::path candidate = base / (prefix + "_1427_" + std::to_string(::getpid()) + "_" + std::to_string(i));
    std::error_code ec;
    if (fs::create_directory(candidate, ec) && !ec) return candidate;
  }
  // Fall back to filesystem's temp name pattern if repeated collisions happen.
  fs::path candidate = base / fs::path(prefix + "_1427_fallback");
  std::error_code ec;
  fs::create_directories(candidate, ec);
  return candidate;
}

static void WriteFile(const fs::path& p, const std::string& content = "x") {
  std::ofstream ofs(p.string(), std::ios::binary);
  ofs << content;
  ofs.close();
}

static bool EndsWith(const std::string& s, const std::string& suffix) {
  if (suffix.size() > s.size()) return false;
  return s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0;
}

}  // namespace

class MakernoteIntTest_1427 : public ::testing::Test {};

TEST_F(MakernoteIntTest_1427, ReturnsEmptyStringWhenFilesystemDisabled_1427) {
#if !defined(EXV_ENABLE_FILESYSTEM)
  EXPECT_EQ(Exiv2::Internal::getExiv2ConfigPath(), "");
#else
  GTEST_SKIP() << "EXV_ENABLE_FILESYSTEM is enabled; this build cannot observe the disabled-filesystem branch.";
#endif
}

TEST_F(MakernoteIntTest_1427, ReturnsIniPathFromCurrentDirectoryWhenPresent_1427) {
#if defined(EXV_ENABLE_FILESYSTEM)
  const fs::path tmp = MakeUniqueTempDir("exiv2_cfg_test");
  CurrentPathGuard guard(tmp);

#ifdef _WIN32
  const std::string iniName = "exiv2.ini";
#else
  const std::string iniName = ".exiv2";
#endif

  const fs::path iniPath = tmp / iniName;
  WriteFile(iniPath, "dummy");

  const std::string got = Exiv2::Internal::getExiv2ConfigPath();

  // Observable behavior: when the ini file exists in current_path, returned path should match it.
  EXPECT_EQ(got, iniPath.string());
#else
  GTEST_SKIP() << "EXV_ENABLE_FILESYSTEM is not enabled; function returns empty string.";
#endif
}

TEST_F(MakernoteIntTest_1427, WhenNoIniInCurrentDirReturnsPathEndingWithExpectedIniName_1427) {
#if defined(EXV_ENABLE_FILESYSTEM)
  const fs::path tmp = MakeUniqueTempDir("exiv2_cfg_test_noini");
  CurrentPathGuard guard(tmp);

#ifdef _WIN32
  const std::string iniName = "exiv2.ini";
#else
  const std::string iniName = ".exiv2";
#endif

  // Ensure the file does NOT exist in current directory.
  std::error_code ec;
  fs::remove(tmp / iniName, ec);

  const std::string got = Exiv2::Internal::getExiv2ConfigPath();

  // We do not assume the specific home/profile resolution logic; we only assert observable invariants:
  // - result is non-empty
  // - it ends with the platform-specific ini filename
  EXPECT_FALSE(got.empty());
  EXPECT_TRUE(EndsWith(got, iniName));

  // Also, it should not claim the ini exists in the current directory, since we ensured it doesn't.
  // (We don't require the path to exist on disk; just that it isn't the current-dir iniPath.)
  EXPECT_NE(got, (tmp / iniName).string());
#else
  GTEST_SKIP() << "EXV_ENABLE_FILESYSTEM is not enabled; function returns empty string.";
#endif
}

TEST_F(MakernoteIntTest_1427, PrefersCurrentDirIniEvenIfOtherCandidateWouldExist_1427) {
#if defined(EXV_ENABLE_FILESYSTEM)
  const fs::path tmp = MakeUniqueTempDir("exiv2_cfg_test_prefercwd");
  CurrentPathGuard guard(tmp);

#ifdef _WIN32
  const std::string iniName = "exiv2.ini";
#else
  const std::string iniName = ".exiv2";
#endif

  // Create the ini file in current dir; function should return that exact path.
  const fs::path iniPath = tmp / iniName;
  WriteFile(iniPath, "dummy");

  const std::string got = Exiv2::Internal::getExiv2ConfigPath();
  EXPECT_EQ(got, iniPath.string());
#else
  GTEST_SKIP() << "EXV_ENABLE_FILESYSTEM is not enabled; function returns empty string.";
#endif
}