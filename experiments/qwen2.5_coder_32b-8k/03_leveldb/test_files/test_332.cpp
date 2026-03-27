#include <gtest/gtest.h>

#include "db/filename.h"



namespace leveldb {



class FilenameTest_332 : public ::testing::Test {};



TEST_F(FilenameTest_332, LockFileName_NormalOperation_332) {

  std::string dbname = "testdb";

  std::string expected = "testdb/LOCK";

  EXPECT_EQ(LockFileName(dbname), expected);

}



TEST_F(FilenameTest_332, LockFileName_EmptyString_332) {

  std::string dbname = "";

  std::string expected = "/LOCK";

  EXPECT_EQ(LockFileName(dbname), expected);

}



TEST_F(FilenameTest_332, LockFileName_SlashEnding_332) {

  std::string dbname = "testdb/";

  std::string expected = "testdb//LOCK";

  EXPECT_EQ(LockFileName(dbname), expected);

}



}  // namespace leveldb
