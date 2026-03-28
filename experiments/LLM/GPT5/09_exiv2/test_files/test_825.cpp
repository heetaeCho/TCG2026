// File: test_commentvalue_detectcharset_825.cpp

#include <gtest/gtest.h>

#include <string>

#include "exiv2/value.hpp"

namespace {

// Focused fixture for CommentValue::detectCharset behavior.
class CommentValueDetectCharsetTest_825 : public ::testing::Test {
 protected:
  Exiv2::CommentValue cv_;
};

TEST_F(CommentValueDetectCharsetTest_825, Utf8Bom_StripsPrefixAndReturnsUtf8_825) {
  std::string c("\xEF\xBB\xBF" "Hello", 3 + 5);

  const char* cs = cv_.detectCharset(c);

  ASSERT_NE(cs, nullptr);
  EXPECT_STREQ(cs, "UTF-8");
  EXPECT_EQ(c, "Hello");
}

TEST_F(CommentValueDetectCharsetTest_825, Utf8BomOnly_StripsToEmptyAndReturnsUtf8_825) {
  std::string c("\xEF\xBB\xBF", 3);

  const char* cs = cv_.detectCharset(c);

  ASSERT_NE(cs, nullptr);
  EXPECT_STREQ(cs, "UTF-8");
  EXPECT_TRUE(c.empty());
}

TEST_F(CommentValueDetectCharsetTest_825, Ucs2LeBom_StripsPrefixAndReturnsUcs2Le_825) {
  std::string c("\xFF\xFE" "AB", 2 + 2);

  const char* cs = cv_.detectCharset(c);

  ASSERT_NE(cs, nullptr);
  EXPECT_STREQ(cs, "UCS-2LE");
  EXPECT_EQ(c, "AB");
}

TEST_F(CommentValueDetectCharsetTest_825, Ucs2BeBom_StripsPrefixAndReturnsUcs2Be_825) {
  std::string c("\xFE\xFF" "CD", 2 + 2);

  const char* cs = cv_.detectCharset(c);

  ASSERT_NE(cs, nullptr);
  EXPECT_STREQ(cs, "UCS-2BE");
  EXPECT_EQ(c, "CD");
}

TEST_F(CommentValueDetectCharsetTest_825, NoBom_DoesNotModifyStringAndReturnsUcs2Variant_825) {
  std::string c("Plain ASCII");

  const std::string original = c;
  const char* cs = cv_.detectCharset(c);

  ASSERT_NE(cs, nullptr);
  // Fallback depends on internal byte order; we only assert it's one of the documented outputs.
  EXPECT_TRUE(std::string(cs) == "UCS-2LE" || std::string(cs) == "UCS-2BE");
  EXPECT_EQ(c, original);
}

TEST_F(CommentValueDetectCharsetTest_825, NoBom_CanBeCalledOnConstObject_825) {
  const Exiv2::CommentValue cv_const;

  std::string c("No BOM");
  const std::string original = c;

  const char* cs = cv_const.detectCharset(c);

  ASSERT_NE(cs, nullptr);
  EXPECT_TRUE(std::string(cs) == "UCS-2LE" || std::string(cs) == "UCS-2BE");
  EXPECT_EQ(c, original);
}

}  // namespace