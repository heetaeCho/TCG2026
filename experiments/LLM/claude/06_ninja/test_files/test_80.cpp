#include "gtest/gtest.h"
#include "version.h"
#include <string>

// ParseVersion is declared in version.h
extern void ParseVersion(const std::string& version, int* major, int* minor);
extern void CheckNinjaVersion(const std::string& version);
extern const char* kNinjaVersion;

// Tests for ParseVersion
TEST(ParseVersionTest_80, ParsesSimpleVersion_80) {
  int major, minor;
  ParseVersion("1.2", &major, &minor);
  EXPECT_EQ(1, major);
  EXPECT_EQ(2, minor);
}

TEST(ParseVersionTest_80, ParsesMajorOnly_80) {
  int major, minor;
  ParseVersion("3", &major, &minor);
  EXPECT_EQ(3, major);
  EXPECT_EQ(0, minor);
}

TEST(ParseVersionTest_80, ParsesVersionWithPatch_80) {
  int major, minor;
  ParseVersion("1.6.2", &major, &minor);
  EXPECT_EQ(1, major);
  EXPECT_EQ(6, minor);
}

TEST(ParseVersionTest_80, ParsesZeroVersion_80) {
  int major, minor;
  ParseVersion("0.0", &major, &minor);
  EXPECT_EQ(0, major);
  EXPECT_EQ(0, minor);
}

TEST(ParseVersionTest_80, ParsesEmptyString_80) {
  int major, minor;
  ParseVersion("", &major, &minor);
  EXPECT_EQ(0, major);
  EXPECT_EQ(0, minor);
}

TEST(ParseVersionTest_80, ParsesLargeVersion_80) {
  int major, minor;
  ParseVersion("10.20", &major, &minor);
  EXPECT_EQ(10, major);
  EXPECT_EQ(20, minor);
}

TEST(ParseVersionTest_80, ParsesVersionWithGitSuffix_80) {
  int major, minor;
  ParseVersion("1.8.2.git", &major, &minor);
  EXPECT_EQ(1, major);
  EXPECT_EQ(8, minor);
}

TEST(ParseVersionTest_80, ParsesCurrentNinjaVersion_80) {
  int major, minor;
  ParseVersion(kNinjaVersion, &major, &minor);
  EXPECT_GE(major, 0);
  EXPECT_GE(minor, 0);
}

// Tests for CheckNinjaVersion
TEST(CheckNinjaVersionTest_80, SameVersionDoesNotFatal_80) {
  // Passing the current ninja version should not cause Fatal
  EXPECT_NO_FATAL_FAILURE(CheckNinjaVersion(kNinjaVersion));
}

TEST(CheckNinjaVersionTest_80, OlderRequiredVersionDoesNotFatal_80) {
  // A very old required version should be fine (or at most a warning)
  EXPECT_NO_FATAL_FAILURE(CheckNinjaVersion("0.1"));
}

TEST(CheckNinjaVersionTest_80, ZeroVersionDoesNotFatal_80) {
  EXPECT_NO_FATAL_FAILURE(CheckNinjaVersion("0.0"));
}

TEST(CheckNinjaVersionTest_80, EmptyVersionDoesNotFatal_80) {
  // Empty string should parse as 0.0 which should be <= current version
  EXPECT_NO_FATAL_FAILURE(CheckNinjaVersion(""));
}

TEST(CheckNinjaVersionTest_80, SameMajorOlderMinorDoesNotFatal_80) {
  // Parse the current version first
  int cur_major, cur_minor;
  ParseVersion(kNinjaVersion, &cur_major, &cur_minor);
  
  // Construct a version with same major but minor = 0
  std::string older_version = std::to_string(cur_major) + ".0";
  EXPECT_NO_FATAL_FAILURE(CheckNinjaVersion(older_version));
}

TEST(CheckNinjaVersionTest_80, ExactCurrentVersionOK_80) {
  int cur_major, cur_minor;
  ParseVersion(kNinjaVersion, &cur_major, &cur_minor);
  
  std::string exact_version = std::to_string(cur_major) + "." + std::to_string(cur_minor);
  EXPECT_NO_FATAL_FAILURE(CheckNinjaVersion(exact_version));
}

// Test that a much newer required version causes Fatal (which calls exit)
// We test this using a death test
TEST(CheckNinjaVersionDeathTest_80, NewerMajorVersionCausesFatal_80) {
  int cur_major, cur_minor;
  ParseVersion(kNinjaVersion, &cur_major, &cur_minor);
  
  std::string newer_version = std::to_string(cur_major + 1) + ".0";
  EXPECT_DEATH(CheckNinjaVersion(newer_version), "ninja version.*incompatible");
}

TEST(CheckNinjaVersionDeathTest_80, NewerMinorVersionCausesFatal_80) {
  int cur_major, cur_minor;
  ParseVersion(kNinjaVersion, &cur_major, &cur_minor);
  
  std::string newer_version = std::to_string(cur_major) + "." + std::to_string(cur_minor + 1);
  EXPECT_DEATH(CheckNinjaVersion(newer_version), "ninja version.*incompatible");
}

TEST(CheckNinjaVersionDeathTest_80, MuchNewerVersionCausesFatal_80) {
  EXPECT_DEATH(CheckNinjaVersion("999.999"), "ninja version.*incompatible");
}
