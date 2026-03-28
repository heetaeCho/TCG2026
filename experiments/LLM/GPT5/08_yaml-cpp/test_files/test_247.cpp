// test_node_set_data_247.cpp
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/mark.h"
#include "yaml-cpp/node/type.h"
#include "yaml-cpp/emitterstyle.h"

namespace YAML {
namespace detail {

class NodeSetDataTest_247 : public ::testing::Test {};

TEST_F(NodeSetDataTest_247, UndefinedRhsDoesNotModifyLhs_247) {
  node lhs;
  lhs.set_scalar("lhs-value");
  lhs.set_tag("!lhs");
  lhs.set_style(EmitterStyle::value::DoubleQuoted);
  lhs.set_mark(Mark(3, 7));

  const auto lhs_defined_before = lhs.is_defined();
  const auto lhs_type_before = lhs.type();
  const auto lhs_scalar_before = lhs.scalar();
  const auto lhs_tag_before = lhs.tag();
  const auto lhs_style_before = lhs.style();
  const auto lhs_mark_before = lhs.mark();

  node rhs;  // expected (in yaml-cpp) to be undefined by default
  EXPECT_FALSE(rhs.is_defined());

  lhs.set_data(rhs);

  // When rhs is not defined, set_data should be a no-op (observable behavior).
  EXPECT_EQ(lhs.is_defined(), lhs_defined_before);
  EXPECT_EQ(lhs.type(), lhs_type_before);
  EXPECT_EQ(lhs.scalar(), lhs_scalar_before);
  EXPECT_EQ(lhs.tag(), lhs_tag_before);
  EXPECT_EQ(lhs.style(), lhs_style_before);
  EXPECT_EQ(lhs.mark(), lhs_mark_before);
}

TEST_F(NodeSetDataTest_247, DefinedRhsCopiesObservableProperties_247) {
  node rhs;
  rhs.set_scalar("hello");
  rhs.set_tag("!greeting");
  rhs.set_style(EmitterStyle::value::DoubleQuoted);
  rhs.set_mark(Mark(1, 2));

  ASSERT_TRUE(rhs.is_defined());

  node lhs;
  EXPECT_FALSE(lhs.is_defined());

  lhs.set_data(rhs);

  EXPECT_TRUE(lhs.is_defined());
  EXPECT_EQ(lhs.type(), rhs.type());
  EXPECT_EQ(lhs.scalar(), rhs.scalar());
  EXPECT_EQ(lhs.tag(), rhs.tag());
  EXPECT_EQ(lhs.style(), rhs.style());
  EXPECT_EQ(lhs.mark(), rhs.mark());
}

TEST_F(NodeSetDataTest_247, OverwritesExistingLhsDataWhenRhsDefined_247) {
  node lhs;
  lhs.set_scalar("old");
  lhs.set_tag("!old");
  lhs.set_style(EmitterStyle::value::Plain);
  lhs.set_mark(Mark(9, 9));
  ASSERT_TRUE(lhs.is_defined());

  node rhs;
  rhs.set_scalar("new");
  rhs.set_tag("!new");
  rhs.set_style(EmitterStyle::value::SingleQuoted);
  rhs.set_mark(Mark(4, 5));
  ASSERT_TRUE(rhs.is_defined());

  lhs.set_data(rhs);

  EXPECT_TRUE(lhs.is_defined());
  EXPECT_EQ(lhs.type(), rhs.type());
  EXPECT_EQ(lhs.scalar(), rhs.scalar());
  EXPECT_EQ(lhs.tag(), rhs.tag());
  EXPECT_EQ(lhs.style(), rhs.style());
  EXPECT_EQ(lhs.mark(), rhs.mark());
}

TEST_F(NodeSetDataTest_247, SelfSetDataDoesNotChangeObservableState_247) {
  node n;
  n.set_scalar("self");
  n.set_tag("!self");
  n.set_style(EmitterStyle::value::Literal);
  n.set_mark(Mark(6, 8));
  ASSERT_TRUE(n.is_defined());

  const auto before_defined = n.is_defined();
  const auto before_type = n.type();
  const auto before_scalar = n.scalar();
  const auto before_tag = n.tag();
  const auto before_style = n.style();
  const auto before_mark = n.mark();

  n.set_data(n);

  EXPECT_EQ(n.is_defined(), before_defined);
  EXPECT_EQ(n.type(), before_type);
  EXPECT_EQ(n.scalar(), before_scalar);
  EXPECT_EQ(n.tag(), before_tag);
  EXPECT_EQ(n.style(), before_style);
  EXPECT_EQ(n.mark(), before_mark);
}

TEST_F(NodeSetDataTest_247, CopiesNullTypeWhenRhsIsNull_247) {
  node rhs;
  rhs.set_null();
  ASSERT_TRUE(rhs.is_defined());
  ASSERT_EQ(rhs.type(), NodeType::Null);

  node lhs;
  lhs.set_scalar("non-null");
  ASSERT_TRUE(lhs.is_defined());

  lhs.set_data(rhs);

  EXPECT_TRUE(lhs.is_defined());
  EXPECT_EQ(lhs.type(), NodeType::Null);
  EXPECT_EQ(lhs.type(), rhs.type());
  EXPECT_EQ(lhs.tag(), rhs.tag());
  EXPECT_EQ(lhs.style(), rhs.style());
  EXPECT_EQ(lhs.mark(), rhs.mark());
}

}  // namespace detail
}  // namespace YAML