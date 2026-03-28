#include <gtest/gtest.h>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <climits>

// Declaration of the function under test
std::string GetWorkingDirectory();

TEST(GetWorkingDirectoryTest_158, ReturnsNonEmptyString_158) {
  std::string cwd = GetWorkingDirectory();
  EXPECT_FALSE(cwd.empty());
}

TEST(GetWorkingDirectoryTest_158, ReturnsAbsolutePath_158) {
  std::string cwd = GetWorkingDirectory();
  EXPECT_EQ('/', cwd[0]);
}

TEST(GetWorkingDirectoryTest_158, DoesNotContainNullTerminator_158) {
  std::string cwd = GetWorkingDirectory();
  // The string should have been resized to strlen, so size() should match
  // the actual content length with no embedded null characters.
  EXPECT_EQ(cwd.find('\0'), std::string::npos);
}

TEST(GetWorkingDirectoryTest_158, MatchesGetcwdResult_158) {
  char buf[PATH_MAX];
  char* expected = getcwd(buf, sizeof(buf));
  ASSERT_NE(expected, nullptr);
  
  std::string cwd = GetWorkingDirectory();
  EXPECT_EQ(cwd, std::string(expected));
}

TEST(GetWorkingDirectoryTest_158, ConsistentOnMultipleCalls_158) {
  std::string cwd1 = GetWorkingDirectory();
  std::string cwd2 = GetWorkingDirectory();
  EXPECT_EQ(cwd1, cwd2);
}

TEST(GetWorkingDirectoryTest_158, ReflectsDirectoryChange_158) {
  std::string original = GetWorkingDirectory();
  
  // Change to root directory
  int rc = chdir("/tmp");
  ASSERT_EQ(rc, 0);
  
  std::string tmp_cwd = GetWorkingDirectory();
  
  // Restore original directory
  rc = chdir(original.c_str());
  ASSERT_EQ(rc, 0);
  
  // /tmp might be a symlink, so resolve both
  char resolved_tmp[PATH_MAX];
  char resolved_cwd[PATH_MAX];
  ASSERT_NE(realpath("/tmp", resolved_tmp), nullptr);
  ASSERT_NE(realpath(tmp_cwd.c_str(), resolved_cwd), nullptr);
  
  EXPECT_EQ(std::string(resolved_tmp), std::string(resolved_cwd));
}

TEST(GetWorkingDirectoryTest_158, StringSizeMatchesContent_158) {
  std::string cwd = GetWorkingDirectory();
  // Verify that size() equals the length of the C string content
  EXPECT_EQ(cwd.size(), strlen(cwd.c_str()));
}

TEST(GetWorkingDirectoryTest_158, NoTrailingSlashUnlessRoot_158) {
  std::string cwd = GetWorkingDirectory();
  if (cwd.size() > 1) {
    EXPECT_NE(cwd.back(), '/');
  }
}
