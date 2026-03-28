// TEST_ID 813
// Unit tests for Exiv2::AsciiValue::read(const std::string&)
// Based strictly on observable behavior via public interface: write(os)
// (We do not access internal state or infer hidden logic.)

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exiv2/value.hpp"

namespace {

class AsciiValueTest_813 : public ::testing::Test {
 protected:
  Exiv2::AsciiValue v_;
};

TEST_F(AsciiValueTest_813, ReadEmptyAppendsNullAndWriteDoesNotThrow_813) {
  // Normal/boundary: empty input should still result in a valid ASCII value that can be written.
  EXPECT_EQ(0, v_.read(std::string{}));

  std::ostringstream oss;
  EXPECT_NO_THROW({
    v_.write(oss);
  });

  // Observable behavior: writing should not print embedded '\0' and should be empty for empty string.
  EXPECT_EQ(std::string{}, oss.str());
}

TEST_F(AsciiValueTest_813, ReadNonEmptyWithoutNullTerminatesAndWriteMatchesInput_813) {
  const std::string in = "Hello, Exiv2";
  EXPECT_EQ(0, v_.read(in));

  std::ostringstream oss;
  v_.write(oss);

  // Observable: output should be the input text (without any trailing NUL rendered).
  EXPECT_EQ(in, oss.str());
}

TEST_F(AsciiValueTest_813, ReadAlreadyNullTerminatedPreservesContentBeforeNull_813) {
  // Boundary: input already contains terminating '\0'
  const std::string in_with_null = std::string("ABC\0", 4);  // includes explicit NUL
  EXPECT_EQ(0, v_.read(in_with_null));

  std::ostringstream oss;
  v_.write(oss);

  // Observable: stream output should stop before '\0', i.e., "ABC".
  EXPECT_EQ("ABC", oss.str());
}

TEST_F(AsciiValueTest_813, ReadEmbeddedNullStopsWriteAtFirstNull_813) {
  // Boundary: embedded NUL not at the end
  const std::string in = std::string("AB\0CD", 5);
  EXPECT_EQ(0, v_.read(in));

  std::ostringstream oss;
  v_.write(oss);

  // Observable: write should output the C-string up to first NUL.
  EXPECT_EQ("AB", oss.str());
}

TEST_F(AsciiValueTest_813, ReadIsIdempotentForSameInput_813) {
  // Normal: repeated reads of the same value should yield identical observable output.
  const std::string in = "repeat";
  EXPECT_EQ(0, v_.read(in));

  std::ostringstream oss1;
  v_.write(oss1);

  EXPECT_EQ(0, v_.read(in));

  std::ostringstream oss2;
  v_.write(oss2);

  EXPECT_EQ(oss1.str(), oss2.str());
  EXPECT_EQ(in, oss2.str());
}

TEST_F(AsciiValueTest_813, ReadOverwritesPreviousValue_813) {
  // Normal: reading a second value should replace the observable output.
  EXPECT_EQ(0, v_.read("first"));
  std::ostringstream oss1;
  v_.write(oss1);
  EXPECT_EQ("first", oss1.str());

  EXPECT_EQ(0, v_.read("second"));
  std::ostringstream oss2;
  v_.write(oss2);
  EXPECT_EQ("second", oss2.str());
}

TEST_F(AsciiValueTest_813, ReadWithOnlyNullCharacterWritesEmpty_813) {
  // Boundary: input is just a NUL (length 1).
  const std::string in = std::string("\0", 1);
  EXPECT_EQ(0, v_.read(in));

  std::ostringstream oss;
  v_.write(oss);

  // Observable: empty when first char is NUL.
  EXPECT_EQ(std::string{}, oss.str());
}

}  // namespace