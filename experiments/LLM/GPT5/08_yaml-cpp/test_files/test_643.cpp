// TEST_ID: 643
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/detail/node_data.h"

namespace {

using YAML::detail::node_data;

class NodeDataSetTagTest_643 : public ::testing::Test {
 protected:
  node_data data_;
};

TEST_F(NodeDataSetTagTest_643, DefaultTagIsObservable_643) {
  // Verifies that tag() is callable on a default-constructed object and returns a value.
  // We don't assume what the default value *should* be beyond being observable.
  EXPECT_NO_THROW({
    (void)data_.tag();
  });
}

TEST_F(NodeDataSetTagTest_643, SetTagToNonEmptyString_643) {
  const std::string tag = "!mytag";
  ASSERT_NO_THROW(data_.set_tag(tag));
  EXPECT_EQ(data_.tag(), tag);
}

TEST_F(NodeDataSetTagTest_643, SetTagToEmptyString_643) {
  const std::string tag = "";
  ASSERT_NO_THROW(data_.set_tag(tag));
  EXPECT_EQ(data_.tag(), tag);
}

TEST_F(NodeDataSetTagTest_643, SetTagOverwritesPreviousValue_643) {
  const std::string first = "!first";
  const std::string second = "!second";

  ASSERT_NO_THROW(data_.set_tag(first));
  EXPECT_EQ(data_.tag(), first);

  ASSERT_NO_THROW(data_.set_tag(second));
  EXPECT_EQ(data_.tag(), second);
}

TEST_F(NodeDataSetTagTest_643, SetTagWithUnicodeContent_643) {
  const std::string tag = u8"!태그/ユニコード/✅";
  ASSERT_NO_THROW(data_.set_tag(tag));
  EXPECT_EQ(data_.tag(), tag);
}

TEST_F(NodeDataSetTagTest_643, SetTagWithLargeString_643) {
  const std::string tag(4096, 'x');  // boundary-ish: larger than typical small-string-optimization
  ASSERT_NO_THROW(data_.set_tag(tag));
  EXPECT_EQ(data_.tag(), tag);
}

TEST_F(NodeDataSetTagTest_643, SetTagDoesNotRequireStringLifetime_643) {
  // Ensures the value is stored such that it remains observable after the input goes out of scope.
  std::string observed;
  {
    std::string tag = "!scoped";
    ASSERT_NO_THROW(data_.set_tag(tag));
  }
  EXPECT_NO_THROW({ observed = data_.tag(); });
  EXPECT_EQ(observed, "!scoped");
}

}  // namespace