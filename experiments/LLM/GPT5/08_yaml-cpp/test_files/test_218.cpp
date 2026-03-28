// TEST_ID: 218
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"

namespace {

using YAML::detail::node_ref;

static void ExpectMarksEqual(const YAML::Mark& a, const YAML::Mark& b) {
  EXPECT_EQ(a.pos, b.pos);
  EXPECT_EQ(a.line, b.line);
  EXPECT_EQ(a.column, b.column);
}

// Try to find an alternate NodeType::value that can be set without throwing and
// results in a different observable type(). If none found, returns false.
static bool TrySetDifferentType(node_ref& n) {
  const auto original = n.type();
  for (int i = 0; i <= 16; ++i) {
    try {
      auto candidate = static_cast<YAML::NodeType::value>(i);
      n.set_type(candidate);
      if (n.type() != original) return true;
    } catch (...) {
      // Ignore and continue trying other values.
    }
  }
  return false;
}

// Same idea for EmitterStyle::value.
static bool TrySetDifferentStyle(node_ref& n) {
  const auto original = n.style();
  for (int i = 0; i <= 16; ++i) {
    try {
      auto candidate = static_cast<YAML::EmitterStyle::value>(i);
      n.set_style(candidate);
      if (n.style() != original) return true;
    } catch (...) {
      // Ignore and continue trying other values.
    }
  }
  return false;
}

class NodeRefSetDataTest_218 : public ::testing::Test {};

TEST_F(NodeRefSetDataTest_218, CopiesObservableStateFromRhs_218) {
  node_ref rhs;
  node_ref lhs;

  // Configure RHS with observable state through public API.
  rhs.mark_defined();

  YAML::Mark m;
  m.pos = 3;
  m.line = 1;
  m.column = 2;
  rhs.set_mark(m);

  rhs.set_tag("!test");
  rhs.set_scalar("value");

  // Attempt to also make type/style different-from-default via only public API.
  (void)TrySetDifferentType(rhs);
  (void)TrySetDifferentStyle(rhs);

  // Ensure LHS has different state beforehand so the copy is observable.
  lhs.set_tag("!other");
  lhs.set_scalar("other");
  lhs.mark_defined();
  YAML::Mark m2;
  m2.pos = 30;
  m2.line = 10;
  m2.column = 20;
  lhs.set_mark(m2);
  (void)TrySetDifferentType(lhs);
  (void)TrySetDifferentStyle(lhs);

  ASSERT_NO_THROW(lhs.set_data(rhs));

  // After set_data, observable getters should match rhs.
  EXPECT_EQ(lhs.is_defined(), rhs.is_defined());
  ExpectMarksEqual(lhs.mark(), rhs.mark());
  EXPECT_EQ(lhs.tag(), rhs.tag());
  EXPECT_EQ(lhs.scalar(), rhs.scalar());
  EXPECT_EQ(lhs.type(), rhs.type());
  EXPECT_EQ(lhs.style(), rhs.style());
  EXPECT_EQ(lhs.size(), rhs.size());
}

TEST_F(NodeRefSetDataTest_218, OverwritesExistingState_218) {
  node_ref rhs;
  node_ref lhs;

  lhs.mark_defined();
  lhs.set_tag("!old");
  lhs.set_scalar("old_scalar");

  rhs.set_tag("!new");
  rhs.set_scalar("new_scalar");

  ASSERT_NO_THROW(lhs.set_data(rhs));

  EXPECT_EQ(lhs.tag(), rhs.tag());
  EXPECT_EQ(lhs.scalar(), rhs.scalar());
  EXPECT_EQ(lhs.is_defined(), rhs.is_defined());
}

TEST_F(NodeRefSetDataTest_218, SelfSetDataDoesNotChangeObservableState_218) {
  node_ref n;

  n.mark_defined();

  YAML::Mark m;
  m.pos = 7;
  m.line = 8;
  m.column = 9;
  n.set_mark(m);

  n.set_tag("!self");
  n.set_scalar("self_scalar");
  (void)TrySetDifferentType(n);
  (void)TrySetDifferentStyle(n);

  const bool defined_before = n.is_defined();
  const YAML::Mark mark_before = n.mark();
  const std::string tag_before = n.tag();
  const std::string scalar_before = n.scalar();
  const auto type_before = n.type();
  const auto style_before = n.style();
  const std::size_t size_before = n.size();

  ASSERT_NO_THROW(n.set_data(n));

  EXPECT_EQ(n.is_defined(), defined_before);
  ExpectMarksEqual(n.mark(), mark_before);
  EXPECT_EQ(n.tag(), tag_before);
  EXPECT_EQ(n.scalar(), scalar_before);
  EXPECT_EQ(n.type(), type_before);
  EXPECT_EQ(n.style(), style_before);
  EXPECT_EQ(n.size(), size_before);
}

TEST_F(NodeRefSetDataTest_218, CanCopyFromDefaultConstructedRhs_218) {
  node_ref rhs;  // default state
  node_ref lhs;

  // Put LHS into a clearly different state first.
  lhs.mark_defined();
  lhs.set_tag("!nondefault");
  lhs.set_scalar("nondefault");
  YAML::Mark m;
  m.pos = 1;
  m.line = 2;
  m.column = 3;
  lhs.set_mark(m);

  ASSERT_NO_THROW(lhs.set_data(rhs));

  // LHS should now match RHS's observable state.
  EXPECT_EQ(lhs.is_defined(), rhs.is_defined());
  ExpectMarksEqual(lhs.mark(), rhs.mark());
  EXPECT_EQ(lhs.tag(), rhs.tag());
  EXPECT_EQ(lhs.scalar(), rhs.scalar());
  EXPECT_EQ(lhs.type(), rhs.type());
  EXPECT_EQ(lhs.style(), rhs.style());
  EXPECT_EQ(lhs.size(), rhs.size());
}

}  // namespace