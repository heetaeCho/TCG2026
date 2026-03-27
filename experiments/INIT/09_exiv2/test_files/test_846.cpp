// File: test_xmparrayvalue_846.cpp
// Unit tests for Exiv2::XmpArrayValue (black-box, interface-only)
//
// TEST_ID: 846

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "exiv2/value.hpp"

namespace {

class XmpArrayValueTest_846 : public ::testing::Test {
 protected:
  // Avoid depending on specific TypeId enumerators that may vary across builds.
  static Exiv2::TypeId AnyTypeId() { return static_cast<Exiv2::TypeId>(0); }
};

TEST_F(XmpArrayValueTest_846, WriteOnDefaultConstructedIsEmpty_846) {
  Exiv2::XmpArrayValue v(AnyTypeId());

  std::ostringstream oss;
  const std::string before = oss.str();

  // Call via const reference to exercise the const-qualified write overload.
  const Exiv2::XmpArrayValue& cv = v;
  cv.write(oss);

  EXPECT_EQ(oss.str(), before);
}

TEST_F(XmpArrayValueTest_846, WriteReturnsSameStreamReference_846) {
  Exiv2::XmpArrayValue v(AnyTypeId());
  std::ostringstream oss;

  const Exiv2::XmpArrayValue& cv = v;

  std::ostream& ret = cv.write(oss);

  // Observable behavior: write returns a reference to the same stream passed in.
  EXPECT_EQ(&ret, static_cast<std::ostream*>(&oss));
}

TEST_F(XmpArrayValueTest_846, WriteDoesNotModifyExistingStreamContentWhenEmpty_846) {
  Exiv2::XmpArrayValue v(AnyTypeId());
  std::ostringstream oss;

  oss << "prefix";
  const std::string before = oss.str();

  const Exiv2::XmpArrayValue& cv = v;
  cv.write(oss);

  EXPECT_EQ(oss.str(), before);
}

TEST_F(XmpArrayValueTest_846, MultipleWritesAreIdempotentWhenEmpty_846) {
  Exiv2::XmpArrayValue v(AnyTypeId());
  std::ostringstream oss;

  const Exiv2::XmpArrayValue& cv = v;

  cv.write(oss);
  const std::string after_first = oss.str();

  cv.write(oss);
  const std::string after_second = oss.str();

  EXPECT_EQ(after_first, after_second);
  EXPECT_TRUE(oss.good());
}

}  // namespace