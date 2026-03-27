// Object_getName_test_99.cpp
#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "poppler/Object.h"

namespace {

class ObjectGetNameTest_99 : public ::testing::Test {};

TEST_F(ObjectGetNameTest_99, ReturnsCStringForNameObject_99)
{
  Object o(objName, "FontName");
  const char *name = o.getName();

  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "FontName");
}

TEST_F(ObjectGetNameTest_99, ReturnsCStringForEmptyName_99)
{
  Object o(objName, "");
  const char *name = o.getName();

  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "");
}

TEST_F(ObjectGetNameTest_99, ReturnsCStringForLongName_99)
{
  const std::string longName(4096, 'A');
  Object o(objName, std::string_view(longName));
  const char *name = o.getName();

  ASSERT_NE(name, nullptr);
  EXPECT_EQ(std::string(name), longName);
}

TEST_F(ObjectGetNameTest_99, MoveConstructedNameStillReturnsName_99)
{
  Object src(objName, "MovedName");
  Object dst(std::move(src));

  const char *name = dst.getName();
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "MovedName");
}

TEST_F(ObjectGetNameTest_99, MoveAssignedNameStillReturnsName_99)
{
  Object src(objName, "AssignedName");
  Object dst; // objNone
  dst = std::move(src);

  const char *name = dst.getName();
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "AssignedName");
}

TEST_F(ObjectGetNameTest_99, GetNameOnNonNameTriggersTypeCheckOrReturnsNull_99)
{
  // Black-box: getName() is documented via OBJECT_TYPE_CHECK(objName) and is intended for objName.
  // In debug builds this often aborts (assert/death). In release builds it may return nullptr.
  Object o(false);

#if GTEST_HAS_DEATH_TEST
#ifndef NDEBUG
  EXPECT_DEATH_IF_SUPPORTED(
      {
        (void)o.getName();
      },
      "");
#else
  const char *name = o.getName();
  EXPECT_EQ(name, nullptr);
#endif
#else
  const char *name = o.getName();
  // Best-effort check when death tests are unavailable: it should not succeed for non-name.
  EXPECT_EQ(name, nullptr);
#endif
}

} // namespace