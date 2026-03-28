// File: run_mapper_test_58.cc

#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

// Forward declaration of the function under test.
namespace glomap {
int RunMapper(int argc, char** argv);
}  // namespace glomap

class RunMapperTest_58 : public ::testing::Test {
protected:
  void SetUp() override { std::remove(existing_db_path_.c_str()); }

  void TearDown() override { std::remove(existing_db_path_.c_str()); }

  void CreateDummyDatabaseFile() {
    std::ofstream ofs(existing_db_path_, std::ios::out | std::ios::trunc);
    ofs << "dummy";
  }

  std::string existing_db_path_ = "test_db_58.db";
};

// Error case: database_path does not exist → should fail before any further work.
TEST_F(RunMapperTest_58, ReturnsFailureWhenDatabaseDoesNotExist_58) {
  const char* argv[] = {
      "program_name",
      "--database_path=non_existing_db_58.db",
      "--output_path=output_58",
  };
  int argc = static_cast<int>(sizeof(argv) / sizeof(argv[0]));

  int result = glomap::RunMapper(argc, const_cast<char**>(argv));

  EXPECT_EQ(EXIT_FAILURE, result);
}

// Error case: invalid constraint_type with an existing database file.
TEST_F(RunMapperTest_58, ReturnsFailureForInvalidConstraintType_58) {
  // Ensure the database file exists so we get past the file-existence check.
  CreateDummyDatabaseFile();

  const char* argv[] = {
      "program_name",
      ("--database_path=" + existing_db_path_).c_str(),
      "--output_path=output_58",
      "--constraint_type=INVALID_CONSTRAINT_58",
  };
  int argc = static_cast<int>(sizeof(argv) / sizeof(argv[0]));

  int result = glomap::RunMapper(argc, const_cast<char**>(argv));

  EXPECT_EQ(EXIT_FAILURE, result);
}

// Error case: invalid output_format with an existing database file.
TEST_F(RunMapperTest_58, ReturnsFailureForInvalidOutputFormat_58) {
  // Ensure the database file exists so we get past the file-existence check.
  CreateDummyDatabaseFile();

  const char* argv[] = {
      "program_name",
      ("--database_path=" + existing_db_path_).c_str(),
      "--output_path=output_58",
      "--output_format=csv_58",  // Not "bin" or "txt" → should be rejected.
  };
  int argc = static_cast<int>(sizeof(argv) / sizeof(argv[0]));

  int result = glomap::RunMapper(argc, const_cast<char**>(argv));

  EXPECT_EQ(EXIT_FAILURE, result);
}
