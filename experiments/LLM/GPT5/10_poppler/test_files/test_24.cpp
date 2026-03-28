// TEST_ID: 24
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>

#include "TestProjects/poppler/goo/GooString.h"

namespace {

TEST(GooStringTest_24, SetCharUpdatesFirstCharacter_24) {
  GooString s("abc");
  ASSERT_EQ(s.toStr().size(), 3u);

  s.setChar(0, 'z');

  EXPECT_EQ(s.toStr(), std::string("zbc"));
  EXPECT_EQ(s.getChar(0), 'z');
  EXPECT_EQ(s.getChar(1), 'b');
  EXPECT_EQ(s.getChar(2), 'c');
}

TEST(GooStringTest_24, SetCharUpdatesMiddleCharacter_24) {
  GooString s("abcd");
  ASSERT_EQ(s.toStr().size(), 4u);

  s.setChar(2, 'X');

  EXPECT_EQ(s.toStr(), std::string("abXd"));
  EXPECT_EQ(s.getChar(2), 'X');
}

TEST(GooStringTest_24, SetCharUpdatesLastCharacter_24) {
  GooString s("hello");
  ASSERT_EQ(s.toStr().size(), 5u);

  s.setChar(s.toStr().size() - 1, '!');

  EXPECT_EQ(s.toStr(), std::string("hell!"));
  EXPECT_EQ(s.getChar(4), '!');
}

TEST(GooStringTest_24, SetCharCanWriteNullByteWithoutChangingSize_24) {
  const char raw[] = {'a', 'b', 'c'};
  GooString s(raw, 3);
  ASSERT_EQ(s.toStr().size(), 3u);

  s.setChar(1, '\0');

  EXPECT_EQ(s.toStr().size(), 3u);
  const std::string expected(std::string("a\0c", 3));
  EXPECT_EQ(s.toStr(), expected);
  EXPECT_EQ(s.getChar(0), 'a');
  EXPECT_EQ(s.getChar(1), '\0');
  EXPECT_EQ(s.getChar(2), 'c');
}

TEST(GooStringTest_24, SetCharAffectsCopyNotOriginal_24) {
  GooString original("abc");
  std::unique_ptr<GooString> copied = original.copy();
  ASSERT_NE(copied, nullptr);

  copied->setChar(1, 'Z');

  EXPECT_EQ(original.toStr(), std::string("abc"));
  EXPECT_EQ(copied->toStr(), std::string("aZc"));
}

TEST(GooStringTest_24, SetCharWorksAfterMoveConstruction_24) {
  GooString src("move");
  GooString dst(std::move(src));

  ASSERT_GE(dst.toStr().size(), 4u);
  dst.setChar(0, 'M');

  EXPECT_EQ(dst.getChar(0), 'M');
  EXPECT_EQ(dst.toStr().front(), 'M');
}

}  // namespace