// File: test/ostream_wrapper_row_test_27.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"

namespace {

class OstreamWrapperRowTest_27 : public ::testing::Test {
protected:
  std::ostringstream out;
};

TEST_F(OstreamWrapperRowTest_27, DefaultAndStreamConstructorsHaveSameInitialRow_27) {
  YAML::ostream_wrapper def;
  YAML::ostream_wrapper with_stream(out);

  EXPECT_EQ(def.row(), with_stream.row());
}

TEST_F(OstreamWrapperRowTest_27, EmptyWritesDoNotChangeRow_27) {
  YAML::ostream_wrapper w(out);
  const std::size_t before = w.row();

  EXPECT_NO_THROW(w.write(std::string()));
  EXPECT_EQ(w.row(), before);

  const char* empty = "";
  EXPECT_NO_THROW(w.write(empty, 0));
  EXPECT_EQ(w.row(), before);

  EXPECT_NO_THROW(w.write(empty, 0));
  EXPECT_EQ(w.row(), before);
}

TEST_F(OstreamWrapperRowTest_27, WritingWithoutNewlineDoesNotChangeRow_27) {
  YAML::ostream_wrapper w(out);
  const std::size_t before = w.row();

  EXPECT_NO_THROW(w.write("abc"));
  EXPECT_EQ(w.row(), before);

  const char data[] = {'x', 'y', 'z'};
  EXPECT_NO_THROW(w.write(data, sizeof(data)));
  EXPECT_EQ(w.row(), before);
}

TEST_F(OstreamWrapperRowTest_27, WritingNewlineIncreasesRow_27) {
  YAML::ostream_wrapper w(out);
  const std::size_t before = w.row();

  EXPECT_NO_THROW(w.write("a\n"));
  const std::size_t after = w.row();

  EXPECT_GT(after, before);
}

TEST_F(OstreamWrapperRowTest_27, MultipleNewlinesIncreaseRowMonotonically_27) {
  YAML::ostream_wrapper w(out);

  const std::size_t before = w.row();
  EXPECT_NO_THROW(w.write("line1\n"));
  const std::size_t after_one = w.row();

  EXPECT_GT(after_one, before);

  EXPECT_NO_THROW(w.write("line2\n"));
  const std::size_t after_two = w.row();

  EXPECT_GT(after_two, after_one);
}

TEST_F(OstreamWrapperRowTest_27, NewlineBehaviorIsConsistentAcrossWriteOverloads_27) {
  YAML::ostream_wrapper w(out);

  const std::size_t start = w.row();

  // std::string overload
  EXPECT_NO_THROW(w.write(std::string("x\n")));
  const std::size_t after_string = w.row();
  EXPECT_GT(after_string, start);

  // const char* + size overload
  const char buf[] = {'y', '\n'};
  EXPECT_NO_THROW(w.write(buf, sizeof(buf)));
  const std::size_t after_buf = w.row();
  EXPECT_GT(after_buf, after_string);
}

}  // namespace
