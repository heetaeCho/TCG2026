// File: test/node_ref_set_scalar_test_223.cpp

#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/detail/node_ref.h"

namespace {

class NodeRefSetScalarTest_223 : public ::testing::Test {
 protected:
  YAML::detail::node_ref ref_;
};

TEST_F(NodeRefSetScalarTest_223, SetScalarStoresExactValue_223) {
  const std::string input = "hello";
  ASSERT_NO_THROW(ref_.set_scalar(input));
  EXPECT_EQ(ref_.scalar(), input);
}

TEST_F(NodeRefSetScalarTest_223, SetScalarAllowsEmptyString_223) {
  const std::string input;
  ASSERT_NO_THROW(ref_.set_scalar(input));
  EXPECT_EQ(ref_.scalar(), input);
  EXPECT_TRUE(ref_.scalar().empty());
}

TEST_F(NodeRefSetScalarTest_223, SetScalarOverwritesPreviousValue_223) {
  ASSERT_NO_THROW(ref_.set_scalar("first"));
  EXPECT_EQ(ref_.scalar(), "first");

  ASSERT_NO_THROW(ref_.set_scalar("second"));
  EXPECT_EQ(ref_.scalar(), "second");
}

TEST_F(NodeRefSetScalarTest_223, SetScalarPreservesEmbeddedNullBytes_223) {
  const std::string input("ab\0cd", 5);  // includes '\0' in the middle
  ASSERT_NO_THROW(ref_.set_scalar(input));

  const std::string out = ref_.scalar();
  EXPECT_EQ(out.size(), input.size());
  EXPECT_EQ(out, input);
  EXPECT_EQ(out[2], '\0');
}

TEST_F(NodeRefSetScalarTest_223, SetScalarHandlesUnicodeUtf8_223) {
  const std::string input = u8"안녕하세요 🌿 YAML";
  ASSERT_NO_THROW(ref_.set_scalar(input));
  EXPECT_EQ(ref_.scalar(), input);
}

TEST_F(NodeRefSetScalarTest_223, SetScalarHandlesLargeString_223) {
  const std::string input(1 << 20, 'x');  // 1 MiB
  ASSERT_NO_THROW(ref_.set_scalar(input));
  EXPECT_EQ(ref_.scalar().size(), input.size());
  EXPECT_EQ(ref_.scalar(), input);
}

TEST_F(NodeRefSetScalarTest_223, SetScalarDoesNotRequirePriorMarkDefined_223) {
  // Observable behavior requirement: call should succeed and value retrievable,
  // regardless of whether mark_defined() was called beforehand.
  ASSERT_NO_THROW(ref_.set_scalar("value-without-mark_defined"));
  EXPECT_EQ(ref_.scalar(), "value-without-mark_defined");
}

}  // namespace