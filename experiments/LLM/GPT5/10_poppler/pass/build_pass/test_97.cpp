// Object_takeString_97_test.cc
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "Object.h"
#include "GooString.h"

namespace {

class ObjectTakeStringTest_97 : public ::testing::Test {};

TEST_F(ObjectTakeStringTest_97, TakeStringTransfersOwnershipAndNullsObject_97) {
  // Arrange
  Object obj(std::make_unique<GooString>("hello"));
  ASSERT_TRUE(obj.isString());
  const GooString *beforePtr = obj.getString();
  ASSERT_NE(beforePtr, nullptr);

  // Act
  std::unique_ptr<GooString> taken = obj.takeString();

  // Assert
  ASSERT_NE(taken, nullptr);
  EXPECT_EQ(taken.get(), beforePtr) << "takeString() should transfer the same underlying GooString pointer";
  EXPECT_TRUE(obj.isNull());
  EXPECT_EQ(obj.getType(), objNull);
  EXPECT_EQ(obj.getString(), nullptr);
}

TEST_F(ObjectTakeStringTest_97, TakeStringPreservesContent_97) {
  // Arrange
  const char kText[] = "Poppler test string";
  Object obj(std::make_unique<GooString>(kText));

  // Act
  std::unique_ptr<GooString> taken = obj.takeString();

  // Assert
  ASSERT_NE(taken, nullptr);
  EXPECT_STREQ(taken->c_str(), kText);
  EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTakeStringTest_97, TakeStringWithEmptyString_97) {
  // Arrange
  Object obj(std::make_unique<GooString>(""));
  ASSERT_TRUE(obj.isString());

  // Act
  std::unique_ptr<GooString> taken = obj.takeString();

  // Assert
  ASSERT_NE(taken, nullptr);
  EXPECT_STREQ(taken->c_str(), "");
  EXPECT_TRUE(obj.isNull());
  EXPECT_EQ(obj.getString(), nullptr);
}

TEST_F(ObjectTakeStringTest_97, TakeStringWithLargeString_97) {
  // Arrange
  std::string large(1 << 16, 'x'); // 65536 chars
  Object obj(std::make_unique<GooString>(large.c_str()));
  ASSERT_TRUE(obj.isString());

  // Act
  std::unique_ptr<GooString> taken = obj.takeString();

  // Assert
  ASSERT_NE(taken, nullptr);
  EXPECT_EQ(std::string(taken->c_str()), large);
  EXPECT_TRUE(obj.isNull());
}

#if GTEST_HAS_DEATH_TEST
TEST_F(ObjectTakeStringTest_97, TakeStringOnNonStringDies_97) {
  // Observable behavior (if enabled by build): OBJECT_TYPE_CHECK(objString) should terminate.
  // This is a black-box expectation based on the presence of OBJECT_TYPE_CHECK in takeString().
  Object obj(123); // int object, not a string
  ASSERT_TRUE(obj.isInt());

  EXPECT_DEATH(
      {
        auto s = obj.takeString();
        (void)s;
      },
      "");
}
#endif

} // namespace