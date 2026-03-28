// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_string_value_base_write_808.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

// Exiv2 header under test
#include "exiv2/value.hpp"

namespace {

class StringValueBaseTest_808 : public ::testing::Test {
 protected:
  static Exiv2::TypeId AnyTypeId() {
    // Avoid relying on any specific TypeId enumerator name/value.
    return static_cast<Exiv2::TypeId>(0);
  }
};

TEST_F(StringValueBaseTest_808, WriteOutputsCurrentValue_808) {
  Exiv2::StringValueBase v(AnyTypeId(), "ctor-seed");
  v.value_ = "hello";

  std::ostringstream os;
  std::ostream& ret = v.write(os);

  EXPECT_EQ(os.str(), "hello");
  EXPECT_EQ(&ret, &os);  // must return the same stream reference for chaining
}

TEST_F(StringValueBaseTest_808, WriteEmptyStringProducesNoOutput_808) {
  Exiv2::StringValueBase v(AnyTypeId(), "ctor-seed");
  v.value_.clear();

  std::ostringstream os;
  v.write(os);

  EXPECT_TRUE(os.str().empty());
}

TEST_F(StringValueBaseTest_808, WriteIsChainable_808) {
  Exiv2::StringValueBase v(AnyTypeId(), "ctor-seed");
  v.value_ = "abc";

  std::ostringstream os;
  v.write(os) << "-tail";

  EXPECT_EQ(os.str(), "abc-tail");
}

TEST_F(StringValueBaseTest_808, WritePreservesNonAsciiBytes_808) {
  Exiv2::StringValueBase v(AnyTypeId(), "ctor-seed");
  // UTF-8 bytes (e.g., "한글") stored in std::string.
  const std::string utf8 = u8"한글";
  v.value_ = utf8;

  std::ostringstream os;
  v.write(os);

  EXPECT_EQ(os.str(), utf8);
}

TEST_F(StringValueBaseTest_808, WriteHandlesEmbeddedNullBytes_808) {
  Exiv2::StringValueBase v(AnyTypeId(), "ctor-seed");

  std::string s;
  s.push_back('A');
  s.push_back('\0');
  s.push_back('B');
  v.value_ = s;

  std::ostringstream os;
  v.write(os);

  const std::string out = os.str();
  ASSERT_EQ(out.size(), 3u);
  EXPECT_EQ(out[0], 'A');
  EXPECT_EQ(out[1], '\0');
  EXPECT_EQ(out[2], 'B');
}

TEST_F(StringValueBaseTest_808, WriteLargeStringBoundary_808) {
  Exiv2::StringValueBase v(AnyTypeId(), "ctor-seed");
  const std::string big(1'000'000, 'x');  // boundary-ish: large but reasonable for unit test
  v.value_ = big;

  std::ostringstream os;
  v.write(os);

  EXPECT_EQ(os.str().size(), big.size());
  EXPECT_EQ(os.str().substr(0, 3), "xxx");
  EXPECT_EQ(os.str().substr(os.str().size() - 3), "xxx");
}

}  // namespace