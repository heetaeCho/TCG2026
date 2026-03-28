// util_mount_point_translate_test_149.cc
#include "gtest/gtest.h"

#include <string>

#include "util.h"
#include "string_piece.h"

#if defined(__linux__) || defined(__GLIBC__)

using std::string;

// Fixture for MountPoint::translate tests.
class MountPointTest_149 : public ::testing::Test {
protected:
  MountPoint mp_;
  std::string device_id_storage_;
  std::string root_storage_;
  std::string mount_point_storage_;

  void SetUp() override {
    device_id_storage_ = "dev";
    root_storage_ = "/root";
    mount_point_storage_ = "/mnt";

    mp_.mountId = 1;
    mp_.parentId = 0;
    mp_.deviceId = StringPiece(device_id_storage_);
    mp_.root = StringPiece(root_storage_);
    mp_.mountPoint = StringPiece(mount_point_storage_);
    // Other fields are irrelevant for translate() and left at defaults.
  }
};

// Path not starting with root: should return empty string and not modify path.
TEST_F(MountPointTest_149, PathNotUnderRootReturnsEmptyAndKeepsPath_149) {
  string path = "/other/dir/file";
  const string original = path;

  string translated = mp_.translate(path);

  EXPECT_TRUE(translated.empty());
  EXPECT_EQ(original, path);  // path must remain unchanged
}

// Normal case: path is a subdirectory of root and gets translated.
TEST_F(MountPointTest_149, SubdirUnderRootIsTranslatedAndStripsRootPrefix_149) {
  string path = "/root/sub/dir";

  string translated = mp_.translate(path);

  // Implementation strips "/root" and prefixes mountPoint + "/".
  // After erasing "/root" (5 chars) from "/root/sub/dir" we get "/sub/dir".
  // Returned path is "/mnt" + "/" + "/sub/dir" == "/mnt//sub/dir".
  EXPECT_EQ("/mnt//sub/dir", translated);
  EXPECT_EQ("/sub/dir", path);  // input path is mutated
}

// Boundary: path exactly equal to root.
TEST_F(MountPointTest_149, PathEqualToRootMapsToMountPointRoot_149) {
  string path = "/root";

  string translated = mp_.translate(path);

  // "/root" with root "/root" becomes empty after erase; result is "/mnt/".
  EXPECT_EQ("/mnt/", translated);
  EXPECT_TRUE(path.empty());
}

// Boundary: root is "/" and simple subpath should map inside mount point.
TEST_F(MountPointTest_149, RootSlashSubpathTranslatedCorrectly_149) {
  static std::string root_slash = "/";
  mp_.root = StringPiece(root_slash);

  string path = "/foo/bar";

  string translated = mp_.translate(path);

  // Erasing "/" from "/foo/bar" leaves "foo/bar".
  EXPECT_EQ("/mnt/foo/bar", translated);
  EXPECT_EQ("foo/bar", path);
}

// Security/escape check: resulting path exactly ".." is rejected.
TEST_F(MountPointTest_149, RelativeParentPathExactlyDotDotIsRejected_149) {
  static std::string root_slash = "/";
  mp_.root = StringPiece(root_slash);

  string path = "/..";

  string translated = mp_.translate(path);

  EXPECT_TRUE(translated.empty());
  // After erase("/") the path becomes ".." and stays that way.
  EXPECT_EQ("..", path);
}

// Security/escape check: resulting path starting with "../" is rejected.
TEST_F(MountPointTest_149, RelativeParentPrefixIsRejected_149) {
  static std::string root_slash = "/";
  mp_.root = StringPiece(root_slash);

  string path = "/../escape";

  string translated = mp_.translate(path);

  EXPECT_TRUE(translated.empty());
  // After erase("/") the path becomes "../escape".
  EXPECT_EQ("../escape", path);
}

#endif  // defined(__linux__) || defined(__GLIBC__)
