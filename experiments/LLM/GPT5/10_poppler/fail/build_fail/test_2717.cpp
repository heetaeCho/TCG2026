// getInfoDate_test_2717.cc
#include <gtest/gtest.h>

#include <optional>
#include <string>

#include "poppler/Dict.h"
#include "poppler/Object.h"
#include "goo/GooString.h"

// pdftohtml.cc is a utility that typically defines its own main().
// To unit-test internal (static) helpers like getInfoDate(), we include the .cc
// into this test translation unit and rename its main symbol to avoid conflicts.
#define main pdftohtml_main_2717
#include "utils/pdftohtml.cc"
#undef main

namespace {

class GetInfoDateTest_2717 : public ::testing::Test {
protected:
  Dict MakeEmptyDict() { return Dict(nullptr); }

  static Object MakeStringObject(const char *s) {
    return Object(std::make_unique<GooString>(s));
  }
};

TEST_F(GetInfoDateTest_2717, ReturnsNulloptWhenKeyMissing_2717) {
  Dict dict(nullptr);

  const std::optional<std::string> v = getInfoDate(&dict, "CreationDate");
  EXPECT_FALSE(v.has_value());
}

TEST_F(GetInfoDateTest_2717, ReturnsNulloptWhenValueIsNotString_2717) {
  Dict dict(nullptr);
  dict.add("CreationDate", Object(123)); // non-string

  const std::optional<std::string> v = getInfoDate(&dict, "CreationDate");
  EXPECT_FALSE(v.has_value());
}

TEST_F(GetInfoDateTest_2717, ReturnsOriginalStringWhenDateParsingFails_2717) {
  Dict dict(nullptr);
  dict.add("CreationDate", MakeStringObject("NotADate"));

  const std::optional<std::string> v = getInfoDate(&dict, "CreationDate");
  ASSERT_TRUE(v.has_value());
  EXPECT_EQ(*v, "NotADate");
}

TEST_F(GetInfoDateTest_2717, ReturnsFormattedIsoLikeStringWhenDateParsingSucceeds_2717) {
  Dict dict(nullptr);
  // Use a canonical PDF date style string (commonly accepted by Poppler parsers).
  // We only assert the observable output format that getInfoDate() produces.
  dict.add("CreationDate", MakeStringObject("D:20240224123456Z"));

  const std::optional<std::string> v = getInfoDate(&dict, "CreationDate");
  ASSERT_TRUE(v.has_value());

  // Expected fixed formatting used by getInfoDate(): "%Y-%m-%dT%H:%M:%S+00:00"
  // We choose a time unlikely to be normalized by mktime.
  EXPECT_EQ(*v, "2024-02-24T12:34:56+00:00");
}

TEST_F(GetInfoDateTest_2717, EmptyStringIsReturnedAsEmptyString_2717) {
  Dict dict(nullptr);
  dict.add("ModDate", MakeStringObject(""));

  const std::optional<std::string> v = getInfoDate(&dict, "ModDate");
  ASSERT_TRUE(v.has_value());
  EXPECT_EQ(*v, "");
}

} // namespace