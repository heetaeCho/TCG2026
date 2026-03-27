// Object_string_rvalue_ctor_test_2747.cc
#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include "Object.h"
#include "goo/GooString.h"

namespace {

class ObjectStringCtorTest_2747 : public ::testing::Test {};

static std::string MakeLargeString_2747(size_t n, char ch = 'x')
{
  return std::string(n, ch);
}

TEST_F(ObjectStringCtorTest_2747, ConstructsStringObjectAndPreservesContent_2747)
{
  const std::string expected = "hello poppler";
  std::string s = expected;

  Object obj(std::move(s));

  EXPECT_TRUE(obj.isString());
  EXPECT_EQ(obj.getType(), objString);

  const GooString *gs = obj.getString();
  ASSERT_NE(gs, nullptr);

  // GooString in Poppler is byte string; c_str() should be NUL-terminated.
  EXPECT_STREQ(gs->c_str(), expected.c_str());
  EXPECT_EQ(gs->getLength(), static_cast<int>(expected.size()));
}

TEST_F(ObjectStringCtorTest_2747, AcceptsEmptyString_2747)
{
  std::string s;

  Object obj(std::move(s));

  EXPECT_TRUE(obj.isString());
  EXPECT_EQ(obj.getType(), objString);

  const GooString *gs = obj.getString();
  ASSERT_NE(gs, nullptr);
  EXPECT_EQ(gs->getLength(), 0);
  EXPECT_STREQ(gs->c_str(), "");
}

TEST_F(ObjectStringCtorTest_2747, PreservesEmbeddedNullBytes_2747)
{
  // Build a string with embedded NULs: "A\0B\0C" (5 bytes).
  const char raw[] = {'A', '\0', 'B', '\0', 'C'};
  const std::string expected(raw, sizeof(raw));
  std::string s = expected;

  Object obj(std::move(s));

  EXPECT_TRUE(obj.isString());
  EXPECT_EQ(obj.getType(), objString);

  const GooString *gs = obj.getString();
  ASSERT_NE(gs, nullptr);
  ASSERT_EQ(gs->getLength(), static_cast<int>(expected.size()));

  // Compare bytes (cannot use STREQ due to embedded NULs).
  EXPECT_EQ(std::memcmp(gs->c_str(), expected.data(), expected.size()), 0);
}

TEST_F(ObjectStringCtorTest_2747, HandlesLargeString_2747)
{
  // Large-but-reasonable size for a unit test.
  const std::string expected = MakeLargeString_2747(1u << 20, 'z'); // 1 MiB
  std::string s = expected;

  Object obj(std::move(s));

  EXPECT_TRUE(obj.isString());
  EXPECT_EQ(obj.getType(), objString);

  const GooString *gs = obj.getString();
  ASSERT_NE(gs, nullptr);
  ASSERT_EQ(gs->getLength(), static_cast<int>(expected.size()));
  EXPECT_EQ(std::memcmp(gs->c_str(), expected.data(), expected.size()), 0);
}

TEST_F(ObjectStringCtorTest_2747, GetStringIsStableAcrossMultipleCalls_2747)
{
  std::string s = "stable";
  Object obj(std::move(s));

  const GooString *a = obj.getString();
  const GooString *b = obj.getString();

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  // Observable expectation: repeated access returns a valid string view of same content.
  EXPECT_EQ(a->getLength(), b->getLength());
  EXPECT_STREQ(a->c_str(), b->c_str());
}

} // namespace