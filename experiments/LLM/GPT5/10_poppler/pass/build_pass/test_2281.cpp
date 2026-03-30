// GooString_setChar_test_2281.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <string>

#include "goo/GooString.h"

namespace {

class GooStringSetCharTest_2281 : public ::testing::Test {
protected:
  static std::string AsStdString(const GooString &s) {
    return s.toStr();
  }
};

TEST_F(GooStringSetCharTest_2281, SetCharUpdatesCharacterAtIndex_2281) {
  GooString s("hello");

  s.setChar(1u, 'a');

  EXPECT_EQ(s.getChar(0u), 'h');
  EXPECT_EQ(s.getChar(1u), 'a');
  EXPECT_EQ(s.getChar(2u), 'l');
  EXPECT_EQ(AsStdString(s), "hallo");
}

TEST_F(GooStringSetCharTest_2281, SetCharAtFirstIndex_2281) {
  GooString s("world");

  s.setChar(0u, 'M');

  EXPECT_EQ(AsStdString(s), "Morld");
  EXPECT_EQ(s.getChar(0u), 'M');
}

TEST_F(GooStringSetCharTest_2281, SetCharAtLastIndex_2281) {
  GooString s("test");

  const size_t last = AsStdString(s).size() - 1u;
  s.setChar(last, '!');

  EXPECT_EQ(AsStdString(s), "tes!");
  EXPECT_EQ(s.getChar(last), '!');
}

TEST_F(GooStringSetCharTest_2281, SetCharDoesNotModifyOtherIndices_2281) {
  GooString s("abcde");

  s.setChar(2u, 'Z');

  EXPECT_EQ(s.getChar(0u), 'a');
  EXPECT_EQ(s.getChar(1u), 'b');
  EXPECT_EQ(s.getChar(2u), 'Z');
  EXPECT_EQ(s.getChar(3u), 'd');
  EXPECT_EQ(s.getChar(4u), 'e');
  EXPECT_EQ(AsStdString(s), "abZde");
}

TEST_F(GooStringSetCharTest_2281, SetCharAllowsEmbeddedNullCharacter_2281) {
  GooString s("ABCDE");
  const size_t original_size = AsStdString(s).size();

  s.setChar(2u, '\0');

  // Verify size is unchanged and the character is set as requested.
  EXPECT_EQ(AsStdString(s).size(), original_size);
  EXPECT_EQ(s.getChar(2u), '\0');

  // Also verify neighboring characters remain intact.
  EXPECT_EQ(s.getChar(1u), 'B');
  EXPECT_EQ(s.getChar(3u), 'D');

  // Verify via toStr() element access as well (std::string can contain '\0').
  const std::string view = AsStdString(s);
  ASSERT_EQ(view.size(), original_size);
  EXPECT_EQ(view[2u], '\0');
}

TEST_F(GooStringSetCharTest_2281, MultipleSetCharCallsApplyInOrder_2281) {
  GooString s("012345");

  s.setChar(0u, 'A');
  s.setChar(3u, 'B');
  s.setChar(5u, 'C');

  EXPECT_EQ(AsStdString(s), "A12B4C");
  EXPECT_EQ(s.getChar(0u), 'A');
  EXPECT_EQ(s.getChar(3u), 'B');
  EXPECT_EQ(s.getChar(5u), 'C');
}

} // namespace