#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/filename.cc"



using namespace leveldb;



TEST(TempFileNameTest_333, ValidNumber_ReturnsCorrectFormat_333) {

  std::string dbname = "testdb";

  uint64_t number = 123;

  EXPECT_EQ(TempFileName(dbname, number), MakeFileName(dbname, number, "dbtmp"));

}



TEST(TempFileNameTest_333, BoundaryCondition_MinimumNumber_333) {

  std::string dbname = "testdb";

  uint64_t number = 1; // Minimum valid number as per assert(number > 0)

  EXPECT_EQ(TempFileName(dbname, number), MakeFileName(dbname, number, "dbtmp"));

}



TEST(TempFileNameTest_333, BoundaryCondition_MaximumNumber_333) {

  std::string dbname = "testdb";

  uint64_t number = UINT64_MAX; // Maximum possible value for uint64_t

  EXPECT_EQ(TempFileName(dbname, number), MakeFileName(dbname, number, "dbtmp"));

}



// Since the function asserts that number > 0, we cannot directly test invalid input.

// However, if the function were to handle such cases gracefully (e.g., by throwing an exception),

// we could include a test for it. As per the constraints and given implementation,

// we assume no handling of invalid numbers other than assertion.



// Example of how you might test an exceptional case if the function were designed to handle it:

// TEST(TempFileNameTest_333, ExceptionalCase_ZeroNumber_333) {

//   std::string dbname = "testdb";

//   uint64_t number = 0; // Invalid input

//   EXPECT_THROW(TempFileName(dbname, number), SomeExceptionType);

// }



// Since the function does not interact with external collaborators or use callbacks,

// there are no additional tests involving Google Mock.
