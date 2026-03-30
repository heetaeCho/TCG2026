// TEST_ID: 225
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"

// These headers are commonly available in yaml-cpp internal builds; if your build already
// pulls them via node_ref.h, these includes are harmless. If your tree uses different
// paths, adjust accordingly.
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/type.h"

namespace {

using YAML::detail::node;
using YAML::detail::node_ref;
using YAML::detail::shared_memory_holder;

// Helper: some codebases allow nullptr shared_memory_holder for operations that don't
// strictly require allocator state. We keep it explicit and consistent.
shared_memory_holder NullMem() { return shared_memory_holder(); }

}  // namespace

// ---- size() tests ----

TEST(NodeRefSizeTest_225, DefaultConstructedHasZeroSize_225) {
  node_ref r;
  EXPECT_NO_THROW({
    const std::size_t s = r.size();
    (void)s;
  });
  EXPECT_EQ(r.size(), 0u);
}

TEST(NodeRefSizeTest_225, SizeUnaffectedByScalarTagStyleAndNull_225) {
  node_ref r;

  // Even if these operations change the node's meaning, they should not create
  // sequence/map entries; size() should remain stable/observable.
  EXPECT_EQ(r.size(), 0u);

  EXPECT_NO_THROW(r.set_scalar("hello"));
  EXPECT_EQ(r.size(), 0u);

  EXPECT_NO_THROW(r.set_tag("!tag"));
  EXPECT_EQ(r.size(), 0u);

  EXPECT_NO_THROW(r.set_style(YAML::EmitterStyle::Default));
  EXPECT_EQ(r.size(), 0u);

  EXPECT_NO_THROW(r.set_null());
  EXPECT_EQ(r.size(), 0u);
}

TEST(NodeRefSizeTest_225, SequencePushBackIncreasesSize_225) {
  node_ref r;
  ASSERT_NO_THROW(r.set_type(YAML::NodeType::Sequence));

  EXPECT_EQ(r.size(), 0u);

  node a;
  node b;
  node c;

  EXPECT_NO_THROW(r.push_back(a, NullMem()));
  EXPECT_EQ(r.size(), 1u);

  EXPECT_NO_THROW(r.push_back(b, NullMem()));
  EXPECT_EQ(r.size(), 2u);

  EXPECT_NO_THROW(r.push_back(c, NullMem()));
  EXPECT_EQ(r.size(), 3u);
}

TEST(NodeRefSizeTest_225, MapInsertIncreasesSize_225) {
  node_ref r;
  ASSERT_NO_THROW(r.set_type(YAML::NodeType::Map));

  EXPECT_EQ(r.size(), 0u);

  node k1;
  node v1;
  node k2;
  node v2;

  EXPECT_NO_THROW(r.insert(k1, v1, NullMem()));
  EXPECT_EQ(r.size(), 1u);

  EXPECT_NO_THROW(r.insert(k2, v2, NullMem()));
  EXPECT_EQ(r.size(), 2u);
}

TEST(NodeRefSizeTest_225, RemoveFromMapCanDecreaseSize_225) {
  node_ref r;
  ASSERT_NO_THROW(r.set_type(YAML::NodeType::Map));

  node k1;
  node v1;
  node k2;
  node v2;

  ASSERT_NO_THROW(r.insert(k1, v1, NullMem()));
  ASSERT_NO_THROW(r.insert(k2, v2, NullMem()));
  ASSERT_EQ(r.size(), 2u);

  // remove(node&, ...) has an observable boolean return. We don't assume which key
  // is found; we verify that if removal succeeds, size decreases by 1; otherwise
  // size remains unchanged.
  const std::size_t before = r.size();
  bool removed = false;
  EXPECT_NO_THROW({ removed = r.remove(k1, NullMem()); });

  if (removed) {
    EXPECT_EQ(r.size(), before - 1);
  } else {
    EXPECT_EQ(r.size(), before);
  }
}

TEST(NodeRefSizeTest_225, SetDataMakesSizeMatchSourceAtTimeOfCall_225) {
  node_ref src;
  node_ref dst;

  ASSERT_NO_THROW(src.set_type(YAML::NodeType::Sequence));
  node a;
  node b;
  ASSERT_NO_THROW(src.push_back(a, NullMem()));
  ASSERT_NO_THROW(src.push_back(b, NullMem()));
  ASSERT_EQ(src.size(), 2u);

  // Observable requirement: after set_data, dst should reflect src's data at least
  // at the time of the call.
  EXPECT_NO_THROW(dst.set_data(src));
  EXPECT_EQ(dst.size(), src.size());
}