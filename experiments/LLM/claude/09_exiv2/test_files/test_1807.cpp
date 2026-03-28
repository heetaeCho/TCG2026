#include <gtest/gtest.h>
#include <cerrno>
#include <string>

// Include the necessary Exiv2 headers
#include "exiv2/exiv2.hpp"

// If the function is declared in futils.hpp or a similar header
// we need to include it. Based on the namespace and common Exiv2 structure:
#include "exiv2/futils.hpp"

class StrErrorTest_1807 : public ::testing::Test {
protected:
  int saved_errno_;

  void SetUp() override {
    saved_errno_ = errno;
  }

  void TearDown() override {
    errno = saved_errno_;
  }
};

// Test that strError returns a non-empty string for a common errno value
TEST_F(StrErrorTest_1807, ReturnsNonEmptyStringForValidErrno_1807) {
  errno = ENOENT;  // No such file or directory
  std::string result = Exiv2::strError();
  EXPECT_FALSE(result.empty());
}

// Test that strError includes the errno value in the returned string
TEST_F(StrErrorTest_1807, ContainsErrnoValueInOutput_1807) {
  errno = ENOENT;
  std::string result = Exiv2::strError();
  // The format is "{message} (errno = {value})"
  // ENOENT is typically 2
  std::string expected_suffix = "(errno = " + std::to_string(ENOENT) + ")";
  EXPECT_NE(result.find(expected_suffix), std::string::npos)
      << "Result was: " << result;
}

// Test that strError works when errno is 0
TEST_F(StrErrorTest_1807, WorksWithErrnoZero_1807) {
  errno = 0;
  std::string result = Exiv2::strError();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("(errno = 0)"), std::string::npos)
      << "Result was: " << result;
}

// Test with EACCES (Permission denied)
TEST_F(StrErrorTest_1807, WorksWithEACCES_1807) {
  errno = EACCES;
  std::string result = Exiv2::strError();
  EXPECT_FALSE(result.empty());
  std::string expected_suffix = "(errno = " + std::to_string(EACCES) + ")";
  EXPECT_NE(result.find(expected_suffix), std::string::npos)
      << "Result was: " << result;
}

// Test with EINVAL (Invalid argument)
TEST_F(StrErrorTest_1807, WorksWithEINVAL_1807) {
  errno = EINVAL;
  std::string result = Exiv2::strError();
  EXPECT_FALSE(result.empty());
  std::string expected_suffix = "(errno = " + std::to_string(EINVAL) + ")";
  EXPECT_NE(result.find(expected_suffix), std::string::npos)
      << "Result was: " << result;
}

// Test with EEXIST (File exists)
TEST_F(StrErrorTest_1807, WorksWithEEXIST_1807) {
  errno = EEXIST;
  std::string result = Exiv2::strError();
  EXPECT_FALSE(result.empty());
  std::string expected_suffix = "(errno = " + std::to_string(EEXIST) + ")";
  EXPECT_NE(result.find(expected_suffix), std::string::npos)
      << "Result was: " << result;
}

// Test with ENOMEM (Out of memory)
TEST_F(StrErrorTest_1807, WorksWithENOMEM_1807) {
  errno = ENOMEM;
  std::string result = Exiv2::strError();
  EXPECT_FALSE(result.empty());
  std::string expected_suffix = "(errno = " + std::to_string(ENOMEM) + ")";
  EXPECT_NE(result.find(expected_suffix), std::string::npos)
      << "Result was: " << result;
}

// Test with ERANGE (Result too large)
TEST_F(StrErrorTest_1807, WorksWithERANGE_1807) {
  errno = ERANGE;
  std::string result = Exiv2::strError();
  EXPECT_FALSE(result.empty());
  std::string expected_suffix = "(errno = " + std::to_string(ERANGE) + ")";
  EXPECT_NE(result.find(expected_suffix), std::string::npos)
      << "Result was: " << result;
}

// Test that the output format matches the expected pattern: "... (errno = N)"
TEST_F(StrErrorTest_1807, OutputFormatContainsParenthesizedErrno_1807) {
  errno = ENOENT;
  std::string result = Exiv2::strError();
  // Check for the pattern "(errno = "
  EXPECT_NE(result.find("(errno = "), std::string::npos)
      << "Result was: " << result;
  // Check it ends with ")"
  EXPECT_EQ(result.back(), ')')
      << "Result was: " << result;
}

// Test that different errno values produce different output strings
TEST_F(StrErrorTest_1807, DifferentErrnoProducesDifferentOutput_1807) {
  errno = ENOENT;
  std::string result1 = Exiv2::strError();

  errno = EACCES;
  std::string result2 = Exiv2::strError();

  EXPECT_NE(result1, result2);
}

// Test with EIO (Input/output error)
TEST_F(StrErrorTest_1807, WorksWithEIO_1807) {
  errno = EIO;
  std::string result = Exiv2::strError();
  EXPECT_FALSE(result.empty());
  std::string expected_suffix = "(errno = " + std::to_string(EIO) + ")";
  EXPECT_NE(result.find(expected_suffix), std::string::npos)
      << "Result was: " << result;
}

// Test that calling strError multiple times with the same errno gives consistent results
TEST_F(StrErrorTest_1807, ConsistentResultsForSameErrno_1807) {
  errno = ENOENT;
  std::string result1 = Exiv2::strError();
  errno = ENOENT;
  std::string result2 = Exiv2::strError();
  EXPECT_EQ(result1, result2);
}
