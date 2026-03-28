// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for Exiv2::ExifTags::taglist(std::ostream&)
// The TEST_ID is 1329

#include <gtest/gtest.h>

#include <exiv2/tags.hpp>

#include <sstream>
#include <string>

namespace {

class ExifTagsTaglistTest_1329 : public ::testing::Test {};

TEST_F(ExifTagsTaglistTest_1329, OutputsNonEmptyAndEndsWithNewline_1329) {
  std::ostringstream os;

  ASSERT_NO_THROW(Exiv2::ExifTags::taglist(os));

  const std::string out = os.str();
  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.back(), '\n');
  EXPECT_NE(out.find('\n'), std::string::npos);
}

TEST_F(ExifTagsTaglistTest_1329, IsDeterministicAcrossCalls_1329) {
  std::ostringstream os1;
  std::ostringstream os2;

  ASSERT_NO_THROW(Exiv2::ExifTags::taglist(os1));
  ASSERT_NO_THROW(Exiv2::ExifTags::taglist(os2));

  EXPECT_EQ(os1.str(), os2.str());
}

TEST_F(ExifTagsTaglistTest_1329, AppendsToExistingStreamContent_1329) {
  std::ostringstream os;
  const std::string prefix = "prefix-line\n";
  os << prefix;

  ASSERT_NO_THROW(Exiv2::ExifTags::taglist(os));

  const std::string out = os.str();
  ASSERT_GE(out.size(), prefix.size());
  EXPECT_EQ(out.compare(0, prefix.size(), prefix), 0);
  EXPECT_GT(out.size(), prefix.size());
}

TEST_F(ExifTagsTaglistTest_1329, DoesNotThrowWhenStreamHasFailOrBadBits_1329) {
  std::ostringstream os;

  // Put the stream into a failing state; writing should become a no-op.
  os.setstate(std::ios::failbit);

  EXPECT_NO_THROW(Exiv2::ExifTags::taglist(os));
  EXPECT_TRUE(os.fail());

  // Also test "badbit" (more severe) state.
  std::ostringstream os2;
  os2.setstate(std::ios::badbit);

  EXPECT_NO_THROW(Exiv2::ExifTags::taglist(os2));
  EXPECT_TRUE(os2.bad());
}

}  // namespace