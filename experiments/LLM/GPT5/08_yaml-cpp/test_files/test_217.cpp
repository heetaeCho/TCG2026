// TEST_ID: 217
#include <gtest/gtest.h>

#include <type_traits>

#include "yaml-cpp/node/detail/node_ref.h"

namespace {

using YAML::detail::node_ref;

class NodeRefMarkDefinedTest_217 : public ::testing::Test {};

TEST_F(NodeRefMarkDefinedTest_217, DefaultIsNotDefined_217) {
  node_ref ref;
  EXPECT_FALSE(ref.is_defined());
}

TEST_F(NodeRefMarkDefinedTest_217, MarkDefinedSetsDefined_217) {
  node_ref ref;
  ref.mark_defined();
  EXPECT_TRUE(ref.is_defined());
}

TEST_F(NodeRefMarkDefinedTest_217, MarkDefinedIsIdempotent_217) {
  node_ref ref;

  ref.mark_defined();
  const bool after_first = ref.is_defined();

  ref.mark_defined();
  const bool after_second = ref.is_defined();

  EXPECT_TRUE(after_first);
  EXPECT_EQ(after_first, after_second);
}

TEST_F(NodeRefMarkDefinedTest_217, MarkDefinedDoesNotAffectOtherInstance_217) {
  node_ref a;
  node_ref b;

  EXPECT_FALSE(a.is_defined());
  EXPECT_FALSE(b.is_defined());

  a.mark_defined();

  EXPECT_TRUE(a.is_defined());
  EXPECT_FALSE(b.is_defined());
}

TEST_F(NodeRefMarkDefinedTest_217, NotCopyable_217) {
  EXPECT_FALSE((std::is_copy_constructible<node_ref>::value));
  EXPECT_FALSE((std::is_copy_assignable<node_ref>::value));
}

TEST_F(NodeRefMarkDefinedTest_217, MarkDefinedDoesNotThrow_217) {
  node_ref ref;
  EXPECT_NO_THROW(ref.mark_defined());
}

}  // namespace