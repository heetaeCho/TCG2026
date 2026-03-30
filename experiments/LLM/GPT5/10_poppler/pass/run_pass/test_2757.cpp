// Object_string_ctor_test_2757.cpp

#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "Object.h"
#include "GooString.h"

namespace {

class ObjectTest_2757 : public ::testing::Test {};

TEST_F(ObjectTest_2757, ConstructFromUniquePtrGooString_SetsStringTypeAndKeepsPointer_2757) {
  auto s = std::make_unique<GooString>("hello");
  GooString *raw = s.get();

  Object obj(std::move(s));

  EXPECT_EQ(s.get(), nullptr);                 // moved-from unique_ptr
  EXPECT_EQ(obj.getType(), objString);
  EXPECT_TRUE(obj.isString());
  EXPECT_NE(obj.getString(), nullptr);
  EXPECT_EQ(obj.getString(), raw);             // ownership transferred into Object
}

TEST_F(ObjectTest_2757, ConstructFromUniquePtrGooString_AllowsEmptyString_2757) {
  auto s = std::make_unique<GooString>("");
  GooString *raw = s.get();

  Object obj(std::move(s));

  EXPECT_EQ(obj.getType(), objString);
  EXPECT_TRUE(obj.isString());
  EXPECT_EQ(obj.getString(), raw);
}

TEST_F(ObjectTest_2757, ConstructFromUniquePtrGooString_AllowsLargeString_2757) {
  std::string big(1 << 16, 'a'); // 65536 chars (boundary-ish: large but reasonable)
  auto s = std::make_unique<GooString>(big.c_str());
  GooString *raw = s.get();

  Object obj(std::move(s));

  EXPECT_EQ(obj.getType(), objString);
  EXPECT_TRUE(obj.isString());
  EXPECT_EQ(obj.getString(), raw);
}

TEST_F(ObjectTest_2757, TakeString_ReturnsSamePointer_2757) {
  auto s = std::make_unique<GooString>("take-me");
  GooString *raw = s.get();

  Object obj(std::move(s));
  std::unique_ptr<GooString> taken = obj.takeString();

  EXPECT_NE(taken.get(), nullptr);
  EXPECT_EQ(taken.get(), raw);
}

#ifndef NDEBUG
TEST_F(ObjectTest_2757, ConstructFromNullUniquePtr_Death_2757) {
  std::unique_ptr<GooString> nullStr;
  EXPECT_DEATH({ Object obj(std::move(nullStr)); }, ".*");
}
#else
TEST_F(ObjectTest_2757, ConstructFromNullUniquePtr_SkippedInReleaseBuild_2757) {
  GTEST_SKIP() << "Constructor uses assert(); death test is only reliable in debug builds (NDEBUG not set).";
}
#endif

} // namespace