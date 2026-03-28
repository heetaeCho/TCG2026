// File: test/node/detail/node_ref_mark_test_212.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/mark.h"
#include "yaml-cpp/node/detail/node_ref.h"

namespace {

class NodeRefMarkTest_212 : public ::testing::Test {};

TEST_F(NodeRefMarkTest_212, DefaultIsNullMark_212) {
  YAML::detail::node_ref ref;

  EXPECT_NO_THROW((void)ref.mark());
  EXPECT_EQ(ref.mark(), YAML::Mark::null_mark());
}

TEST_F(NodeRefMarkTest_212, SetMarkThenMarkReturnsSameValue_212) {
  YAML::detail::node_ref ref;

  const YAML::Mark m(1, 2, 3);
  EXPECT_NO_THROW(ref.set_mark(m));
  EXPECT_NO_THROW((void)ref.mark());

  EXPECT_EQ(ref.mark(), m);
}

TEST_F(NodeRefMarkTest_212, MarkCanBeUpdatedMultipleTimes_212) {
  YAML::detail::node_ref ref;

  const YAML::Mark m1(4, 5, 6);
  const YAML::Mark m2(7, 8, 9);

  ref.set_mark(m1);
  EXPECT_EQ(ref.mark(), m1);

  ref.set_mark(m2);
  EXPECT_EQ(ref.mark(), m2);
}

TEST_F(NodeRefMarkTest_212, SetDataCopiesMarkFromOtherNodeRef_212) {
  YAML::detail::node_ref src;
  YAML::detail::node_ref dst;

  const YAML::Mark m(10, 20, 30);
  src.set_mark(m);

  EXPECT_NE(dst.mark(), m);  // dst is default-initialized
  EXPECT_NO_THROW(dst.set_data(src));
  EXPECT_EQ(dst.mark(), m);
}

TEST_F(NodeRefMarkTest_212, MarkOnConstObjectIsObservable_212) {
  YAML::detail::node_ref ref;
  const YAML::Mark m(11, 22, 33);
  ref.set_mark(m);

  const YAML::detail::node_ref& cref = ref;
  EXPECT_NO_THROW((void)cref.mark());
  EXPECT_EQ(cref.mark(), m);
}

}  // namespace
``