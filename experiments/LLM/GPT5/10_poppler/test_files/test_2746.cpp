// ObjectStringCtorTest_2746.cpp
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "Object.h"
#include "GooString.h"

class ObjectStringCtorTest_2746 : public ::testing::Test {
protected:
  static std::unique_ptr<GooString> MakeGooString(const char *s) {
    // GooString has a ctor that takes const char* in Poppler.
    return std::unique_ptr<GooString>(new GooString(s));
  }

  static std::unique_ptr<GooString> MakeGooString(const std::string &s) {
    return std::unique_ptr<GooString>(new GooString(s.c_str()));
  }
};

TEST_F(ObjectStringCtorTest_2746, ConstructFromUniquePtr_SetsStringType_2746) {
  Object obj(MakeGooString("hello"));

  EXPECT_EQ(obj.getType(), objString);
  EXPECT_TRUE(obj.isString());

  const GooString *gs = obj.getString();
  ASSERT_NE(gs, nullptr);
  EXPECT_STREQ(gs->c_str(), "hello");
}

TEST_F(ObjectStringCtorTest_2746, ConstructWithEmptyString_IsStillString_2746) {
  Object obj(MakeGooString(""));

  EXPECT_EQ(obj.getType(), objString);
  EXPECT_TRUE(obj.isString());

  const GooString *gs = obj.getString();
  ASSERT_NE(gs, nullptr);
  EXPECT_STREQ(gs->c_str(), "");
}

TEST_F(ObjectStringCtorTest_2746, ConstructWithLongString_PreservesContent_2746) {
  const std::string long_str(4096, 'x');

  Object obj(MakeGooString(long_str));

  EXPECT_EQ(obj.getType(), objString);
  EXPECT_TRUE(obj.isString());

  const GooString *gs = obj.getString();
  ASSERT_NE(gs, nullptr);
  EXPECT_EQ(std::string(gs->c_str()), long_str);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(ObjectStringCtorTest_2746, ConstructWithNullUniquePtr_Death_2746) {
  // The constructor asserts on null.
  std::unique_ptr<GooString> null_str;
  EXPECT_DEATH(
      {
        Object obj(std::move(null_str));
        (void)obj;
      },
      "");
}
#endif