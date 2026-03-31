#include <string>
#include "gtest/gtest.h"

// Forward declaration based on the provided interface
namespace leveldb {
std::string CurrentFileName(const std::string& dbname);
}

// Test fixture
class FilenameTest_331 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(FilenameTest_331, CurrentFileName_BasicPath_331) {
  std::string result = leveldb::CurrentFileName("/tmp/testdb");
  EXPECT_EQ(result, "/tmp/testdb/CURRENT");
}

TEST_F(FilenameTest_331, CurrentFileName_SimpleDbName_331) {
  std::string result = leveldb::CurrentFileName("mydb");
  EXPECT_EQ(result, "mydb/CURRENT");
}

TEST_F(FilenameTest_331, CurrentFileName_NestedPath_331) {
  std::string result = leveldb::CurrentFileName("/home/user/data/leveldb");
  EXPECT_EQ(result, "/home/user/data/leveldb/CURRENT");
}

TEST_F(FilenameTest_331, CurrentFileName_RelativePath_331) {
  std::string result = leveldb::CurrentFileName("./data/db");
  EXPECT_EQ(result, "./data/db/CURRENT");
}

TEST_F(FilenameTest_331, CurrentFileName_SingleCharDbName_331) {
  std::string result = leveldb::CurrentFileName("x");
  EXPECT_EQ(result, "x/CURRENT");
}

// Boundary condition tests

TEST_F(FilenameTest_331, CurrentFileName_EmptyDbName_331) {
  std::string result = leveldb::CurrentFileName("");
  EXPECT_EQ(result, "/CURRENT");
}

TEST_F(FilenameTest_331, CurrentFileName_TrailingSlash_331) {
  // The function simply appends "/CURRENT", so a trailing slash results in double slash
  std::string result = leveldb::CurrentFileName("/tmp/testdb/");
  EXPECT_EQ(result, "/tmp/testdb//CURRENT");
}

TEST_F(FilenameTest_331, CurrentFileName_RootPath_331) {
  std::string result = leveldb::CurrentFileName("/");
  EXPECT_EQ(result, "//CURRENT");
}

TEST_F(FilenameTest_331, CurrentFileName_DotPath_331) {
  std::string result = leveldb::CurrentFileName(".");
  EXPECT_EQ(result, "./CURRENT");
}

TEST_F(FilenameTest_331, CurrentFileName_DoubleDotPath_331) {
  std::string result = leveldb::CurrentFileName("..");
  EXPECT_EQ(result, "../CURRENT");
}

TEST_F(FilenameTest_331, CurrentFileName_PathWithSpaces_331) {
  std::string result = leveldb::CurrentFileName("/tmp/my db");
  EXPECT_EQ(result, "/tmp/my db/CURRENT");
}

TEST_F(FilenameTest_331, CurrentFileName_PathWithSpecialChars_331) {
  std::string result = leveldb::CurrentFileName("/tmp/db-test_01.v2");
  EXPECT_EQ(result, "/tmp/db-test_01.v2/CURRENT");
}

TEST_F(FilenameTest_331, CurrentFileName_LongPath_331) {
  std::string longPath(1000, 'a');
  std::string result = leveldb::CurrentFileName(longPath);
  EXPECT_EQ(result, longPath + "/CURRENT");
}

TEST_F(FilenameTest_331, CurrentFileName_ReturnContainsCURRENT_331) {
  std::string result = leveldb::CurrentFileName("anydb");
  // Verify the result ends with "/CURRENT"
  std::string suffix = "/CURRENT";
  ASSERT_GE(result.size(), suffix.size());
  EXPECT_EQ(result.substr(result.size() - suffix.size()), suffix);
}

TEST_F(FilenameTest_331, CurrentFileName_ReturnStartsWithDbName_331) {
  std::string dbname = "/some/path";
  std::string result = leveldb::CurrentFileName(dbname);
  EXPECT_EQ(result.substr(0, dbname.size()), dbname);
}

TEST_F(FilenameTest_331, CurrentFileName_ExactLength_331) {
  std::string dbname = "testdb";
  std::string result = leveldb::CurrentFileName(dbname);
  // Length should be dbname.size() + strlen("/CURRENT") = 6 + 8 = 14
  EXPECT_EQ(result.size(), dbname.size() + 8);
}
