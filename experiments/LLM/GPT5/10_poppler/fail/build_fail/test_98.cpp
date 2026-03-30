// Object_getHexString_test_98.cpp
#include <gtest/gtest.h>

#include "poppler/Object.h"
#include "poppler/GooString.h"

namespace {

// Test fixture for TEST_ID 98
class ObjectGetHexStringTest_98 : public ::testing::Test {};

TEST_F(ObjectGetHexStringTest_98, ReturnsPointerForHexString_98) {
  Object obj(objHexString, std::string_view("4E6F7768657265")); // "Nowhere" in hex, content not interpreted here
  const GooString *s = obj.getHexString();
  ASSERT_NE(s, nullptr);

  // Basic observable property: length matches what we passed in.
  // (We are not asserting any internal decoding/encoding rules.)
  EXPECT_EQ(s->getLength(), 16);
}

TEST_F(ObjectGetHexStringTest_98, WorksWithEmptyHexString_98) {
  Object obj(objHexString, std::string_view(""));
  const GooString *s = obj.getHexString();
  ASSERT_NE(s, nullptr);
  EXPECT_EQ(s->getLength(), 0);
}

TEST_F(ObjectGetHexStringTest_98, WorksWithLargeHexString_98) {
  std::string big(4096, 'A');
  Object obj(objHexString, std::string_view(big));
  const GooString *s = obj.getHexString();
  ASSERT_NE(s, nullptr);
  EXPECT_EQ(s->getLength(), static_cast<int>(big.size()));
}

TEST_F(ObjectGetHexStringTest_98, StillAccessibleAfterMove_98) {
  Object src(objHexString, std::string_view("ABCD"));
  Object moved(std::move(src));

  const GooString *s = moved.getHexString();
  ASSERT_NE(s, nullptr);
  EXPECT_EQ(s->getLength(), 4);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(ObjectGetHexStringTest_98, DeathOnWrongType_Bool_98) {
  Object obj(true);
  EXPECT_DEATH(
      {
        (void)obj.getHexString();
      },
      ".*");
}

TEST_F(ObjectGetHexStringTest_98, DeathOnWrongType_String_98) {
  Object obj(std::string("not-hex-string-type"));
  EXPECT_DEATH(
      {
        (void)obj.getHexString();
      },
      ".*");
}

TEST_F(ObjectGetHexStringTest_98, DeathOnNullObject_98) {
  Object obj = Object::null();
  EXPECT_DEATH(
      {
        (void)obj.getHexString();
      },
      ".*");
}
#endif

} // namespace