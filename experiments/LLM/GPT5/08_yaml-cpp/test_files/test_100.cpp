// TEST_ID: 100
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "stream.h"
#include "streamcharsource.h"

namespace {

class StreamCharSourceTest_100 : public ::testing::Test {
protected:
  static YAML::Stream MakeStreamFrom(const std::string& s, std::istringstream& iss) {
    iss.str(s);
    iss.clear();
    return YAML::Stream(iss);
  }
};

TEST_F(StreamCharSourceTest_100, BoolTrueAtStartForNonEmptyStream_100) {
  std::istringstream iss;
  auto stream = MakeStreamFrom("abc", iss);

  YAML::StreamCharSource src(stream);

  EXPECT_TRUE(static_cast<bool>(src));
  EXPECT_FALSE(!src);
}

TEST_F(StreamCharSourceTest_100, BoolFalseForEmptyStream_100) {
  std::istringstream iss;
  auto stream = MakeStreamFrom("", iss);

  YAML::StreamCharSource src(stream);

  EXPECT_FALSE(static_cast<bool>(src));
  EXPECT_TRUE(!src);
}

TEST_F(StreamCharSourceTest_100, IndexingReturnsExpectedCharacters_100) {
  std::istringstream iss;
  auto stream = MakeStreamFrom("abc", iss);

  YAML::StreamCharSource src(stream);

  ASSERT_TRUE(static_cast<bool>(src));
  EXPECT_EQ(src[0], 'a');
  EXPECT_EQ(src[1], 'b');
  EXPECT_EQ(src[2], 'c');
}

TEST_F(StreamCharSourceTest_100, OperatorPlusDoesNotModifyOriginalAndAdvancesOffset_100) {
  std::istringstream iss;
  auto stream = MakeStreamFrom("abc", iss);

  YAML::StreamCharSource src(stream);
  auto advanced = src + 1;

  ASSERT_TRUE(static_cast<bool>(src));
  ASSERT_TRUE(static_cast<bool>(advanced));

  EXPECT_EQ(src[0], 'a');       // original unchanged
  EXPECT_EQ(advanced[0], 'b');  // advanced view
}

TEST_F(StreamCharSourceTest_100, OperatorPlusIsComposable_100) {
  std::istringstream iss;
  auto stream = MakeStreamFrom("abcd", iss);

  YAML::StreamCharSource src(stream);

  auto plus2 = src + 2;
  auto plus1plus1 = (src + 1) + 1;

  ASSERT_TRUE(static_cast<bool>(plus2));
  ASSERT_TRUE(static_cast<bool>(plus1plus1));

  EXPECT_EQ(plus2[0], 'c');
  EXPECT_EQ(plus1plus1[0], 'c');
}

TEST_F(StreamCharSourceTest_100, BoolBecomesFalseWhenOffsetPastEnd_100) {
  std::istringstream iss;
  auto stream = MakeStreamFrom("abc", iss);

  YAML::StreamCharSource src(stream);

  // Offset exactly at size (past the last valid index)
  auto past_end = src + 3;

  EXPECT_FALSE(static_cast<bool>(past_end));
  EXPECT_TRUE(!past_end);
}

TEST_F(StreamCharSourceTest_100, CopyConstructorPreservesViewAndOffset_100) {
  std::istringstream iss;
  auto stream = MakeStreamFrom("abc", iss);

  YAML::StreamCharSource src(stream);
  auto advanced = src + 1;

  YAML::StreamCharSource copy(advanced);

  EXPECT_EQ(static_cast<bool>(copy), static_cast<bool>(advanced));
  if (static_cast<bool>(copy)) {
    EXPECT_EQ(copy[0], advanced[0]);
    EXPECT_EQ(copy[0], 'b');
  }
}

TEST_F(StreamCharSourceTest_100, MoveConstructorProducesUsableObject_100) {
  std::istringstream iss;
  auto stream = MakeStreamFrom("abc", iss);

  YAML::StreamCharSource src(stream);
  auto advanced = src + 1;

  YAML::StreamCharSource moved(std::move(advanced));

  EXPECT_TRUE(static_cast<bool>(moved));
  EXPECT_EQ(moved[0], 'b');
}

}  // namespace
