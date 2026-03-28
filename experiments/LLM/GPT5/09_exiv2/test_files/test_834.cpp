// =================================================================================================
// TestProjects/exiv2/tests/test_xmptextvalue_read_834.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exiv2/value.hpp"
#include "exiv2/error.hpp"

namespace {

using Exiv2::ErrorCode;
using Exiv2::XmpTextValue;

class XmpTextValueTest_834 : public ::testing::Test {
 protected:
  XmpTextValue v_;
};

// Normal operation: no type= prefix => value should be the input, and no exception.
TEST_F(XmpTextValueTest_834, ReadWithoutTypePrefixStoresWholeString_834) {
  const std::string input = "hello world";
  EXPECT_NO_THROW({
    int rc = v_.read(input);
    EXPECT_EQ(0, rc);
  });

  std::ostringstream os;
  EXPECT_NO_THROW(v_.write(os));
  EXPECT_EQ(input, os.str());
}

// Normal operation: recognized array types should not throw and should strip the type header.
TEST_F(XmpTextValueTest_834, ReadTypeAltStripsHeaderAndStoresRemainder_834) {
  const std::string input = "type=Alt value part";
  EXPECT_NO_THROW({
    int rc = v_.read(input);
    EXPECT_EQ(0, rc);
  });

  std::ostringstream os;
  v_.write(os);
  EXPECT_EQ("value part", os.str());
}

TEST_F(XmpTextValueTest_834, ReadTypeBagStripsHeaderAndStoresRemainder_834) {
  const std::string input = "type=Bag payload";
  EXPECT_NO_THROW({
    int rc = v_.read(input);
    EXPECT_EQ(0, rc);
  });

  std::ostringstream os;
  v_.write(os);
  EXPECT_EQ("payload", os.str());
}

TEST_F(XmpTextValueTest_834, ReadTypeSeqStripsHeaderAndStoresRemainder_834) {
  const std::string input = "type=Seq 123";
  EXPECT_NO_THROW({
    int rc = v_.read(input);
    EXPECT_EQ(0, rc);
  });

  std::ostringstream os;
  v_.write(os);
  EXPECT_EQ("123", os.str());
}

// Boundary: type header with no remainder after the first space => stored value becomes empty.
TEST_F(XmpTextValueTest_834, ReadTypeAltWithNoRemainderStoresEmpty_834) {
  const std::string input = "type=Alt";
  EXPECT_NO_THROW({
    int rc = v_.read(input);
    EXPECT_EQ(0, rc);
  });

  std::ostringstream os;
  v_.write(os);
  EXPECT_EQ("", os.str());
}

// Boundary: header has a space but nothing after it.
TEST_F(XmpTextValueTest_834, ReadTypeAltWithTrailingSpaceStoresEmpty_834) {
  const std::string input = "type=Alt ";
  EXPECT_NO_THROW({
    int rc = v_.read(input);
    EXPECT_EQ(0, rc);
  });

  std::ostringstream os;
  v_.write(os);
  EXPECT_EQ("", os.str());
}

// Boundary: quoted type value should be accepted and stripped, then remainder parsed.
TEST_F(XmpTextValueTest_834, ReadTypeQuotedAltStripsQuotesAndParses_834) {
  const std::string input = "type=\"Alt\" abc";
  EXPECT_NO_THROW({
    int rc = v_.read(input);
    EXPECT_EQ(0, rc);
  });

  std::ostringstream os;
  v_.write(os);
  EXPECT_EQ("abc", os.str());
}

// Boundary: type present, remainder contains multiple spaces -> remainder is preserved as-is
// (i.e., starts right after the first separating space).
TEST_F(XmpTextValueTest_834, ReadTypeAltPreservesRemainderSpacing_834) {
  const std::string input = "type=Alt   spaced";
  EXPECT_NO_THROW({
    int rc = v_.read(input);
    EXPECT_EQ(0, rc);
  });

  std::ostringstream os;
  v_.write(os);
  EXPECT_EQ("  spaced", os.str());  // two spaces remain after the separator space
}

// Exceptional: unknown type should throw Exiv2::Error (observable) and should carry kerInvalidXmpText.
TEST_F(XmpTextValueTest_834, ReadUnknownTypeThrowsErrorWithKerInvalidXmpText_834) {
  const std::string input = "type=Nope some";
  try {
    (void)v_.read(input);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(ErrorCode::kerInvalidXmpText, e.code());
  } catch (...) {
    FAIL() << "Expected Exiv2::Error, got different exception type";
  }
}

// Exceptional/boundary: type token is empty ("type=") => should not throw, and stores whole input
// because the type is considered empty (no recognized type processing).
TEST_F(XmpTextValueTest_834, ReadTypeEmptyDoesNotThrowAndStoresWholeString_834) {
  const std::string input = "type=";
  EXPECT_NO_THROW({
    int rc = v_.read(input);
    EXPECT_EQ(0, rc);
  });

  std::ostringstream os;
  v_.write(os);
  EXPECT_EQ("type=", os.str());
}

// Boundary: type token contains quotes but empty inside => should not throw and stores whole string.
TEST_F(XmpTextValueTest_834, ReadTypeQuotedEmptyDoesNotThrowAndStoresWholeString_834) {
  const std::string input = "type=\"\" anything";
  EXPECT_NO_THROW({
    int rc = v_.read(input);
    EXPECT_EQ(0, rc);
  });

  std::ostringstream os;
  v_.write(os);
  EXPECT_EQ(input, os.str());
}

// Normal: Struct type should not throw and should strip the header and store remainder.
TEST_F(XmpTextValueTest_834, ReadTypeStructStripsHeaderAndStoresRemainder_834) {
  const std::string input = "type=Struct data";
  EXPECT_NO_THROW({
    int rc = v_.read(input);
    EXPECT_EQ(0, rc);
  });

  std::ostringstream os;
  v_.write(os);
  EXPECT_EQ("data", os.str());
}

// Normal/boundary: subsequent read() should overwrite previous value (observable via write()).
TEST_F(XmpTextValueTest_834, ReadSecondTimeOverwritesPreviousValue_834) {
  EXPECT_NO_THROW({
    EXPECT_EQ(0, v_.read("type=Alt first"));
  });
  {
    std::ostringstream os;
    v_.write(os);
    EXPECT_EQ("first", os.str());
  }

  EXPECT_NO_THROW({
    EXPECT_EQ(0, v_.read("second"));
  });
  {
    std::ostringstream os;
    v_.write(os);
    EXPECT_EQ("second", os.str());
  }
}

}  // namespace