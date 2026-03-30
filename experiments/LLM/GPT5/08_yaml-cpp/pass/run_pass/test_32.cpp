// TEST_ID: 32
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"

namespace {

class OstreamWrapperInsertionTest_32 : public ::testing::Test {
 protected:
  std::ostringstream oss_;
  YAML::ostream_wrapper makeWrapperOnStream() { return YAML::ostream_wrapper(oss_); }
};

TEST_F(OstreamWrapperInsertionTest_32, ReturnsSameReference_32) {
  auto wrapper = makeWrapperOnStream();
  YAML::ostream_wrapper* before = &wrapper;

  YAML::ostream_wrapper& ret = (wrapper << std::string("abc"));

  EXPECT_EQ(before, &ret);
}

TEST_F(OstreamWrapperInsertionTest_32, WritesStringAndAdvancesPos_32) {
  auto wrapper = makeWrapperOnStream();

  const std::string s = "hello";
  const std::size_t before_pos = wrapper.pos();

  wrapper << s;

  EXPECT_EQ(wrapper.pos(), before_pos + s.size());
  ASSERT_NE(wrapper.str(), nullptr);
  EXPECT_EQ(std::string(wrapper.str()), s);
}

TEST_F(OstreamWrapperInsertionTest_32, EmptyStringDoesNotChangeStateOrOutput_32) {
  auto wrapper = makeWrapperOnStream();

  const std::size_t before_pos = wrapper.pos();
  const std::size_t before_row = wrapper.row();
  const std::size_t before_col = wrapper.col();
  const bool before_comment = wrapper.comment();
  const std::string before_str = wrapper.str() ? std::string(wrapper.str()) : std::string();

  wrapper << std::string("");

  EXPECT_EQ(wrapper.pos(), before_pos);
  EXPECT_EQ(wrapper.row(), before_row);
  EXPECT_EQ(wrapper.col(), before_col);
  EXPECT_EQ(wrapper.comment(), before_comment);
  ASSERT_NE(wrapper.str(), nullptr);
  EXPECT_EQ(std::string(wrapper.str()), before_str);
}

TEST_F(OstreamWrapperInsertionTest_32, SupportsChainingMultipleInsertions_32) {
  auto wrapper = makeWrapperOnStream();

  const std::string a = "ab";
  const std::string b = "CD";
  const std::string c = "123";
  const std::size_t before_pos = wrapper.pos();

  YAML::ostream_wrapper& ret = (wrapper << a) << b << c;

  EXPECT_EQ(&ret, &wrapper);
  EXPECT_EQ(wrapper.pos(), before_pos + a.size() + b.size() + c.size());
  ASSERT_NE(wrapper.str(), nullptr);
  EXPECT_EQ(std::string(wrapper.str()), a + b + c);
}

TEST_F(OstreamWrapperInsertionTest_32, NewlinesAffectPositionConsistentlyWithPos_32) {
  auto wrapper = makeWrapperOnStream();

  const std::string s = "a\nb\n";
  const std::size_t before_pos = wrapper.pos();

  wrapper << s;

  EXPECT_EQ(wrapper.pos(), before_pos + s.size());
  // row/col semantics are implementation-defined; only check they remain non-negative and observable.
  // (std::size_t is always non-negative)
  ASSERT_NE(wrapper.str(), nullptr);
  EXPECT_EQ(std::string(wrapper.str()), s);
}

TEST_F(OstreamWrapperInsertionTest_32, DoesNotImplicitlyEnableCommentFlag_32) {
  auto wrapper = makeWrapperOnStream();

  EXPECT_FALSE(wrapper.comment());
  wrapper << std::string("# not a comment mode toggle");
  EXPECT_FALSE(wrapper.comment());
}

TEST_F(OstreamWrapperInsertionTest_32, LargeStringInsertionUpdatesPosAndOutput_32) {
  auto wrapper = makeWrapperOnStream();

  const std::string big(4096, 'x');
  const std::size_t before_pos = wrapper.pos();

  wrapper << big;

  EXPECT_EQ(wrapper.pos(), before_pos + big.size());
  ASSERT_NE(wrapper.str(), nullptr);
  EXPECT_EQ(std::string(wrapper.str()), big);
}

TEST(OstreamWrapperInsertionStandaloneTest_32, DefaultConstructedWrapperAcceptsInsertion_32) {
  YAML::ostream_wrapper wrapper;

  const std::string s = "data";
  const std::size_t before_pos = wrapper.pos();

  EXPECT_NO_THROW(wrapper << s);

  EXPECT_EQ(wrapper.pos(), before_pos + s.size());
  ASSERT_NE(wrapper.str(), nullptr);
  EXPECT_EQ(std::string(wrapper.str()), s);
}

}  // namespace
