// TEST_ID: 228
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node.h"

// These are commonly part of yaml-cpp; included defensively because push_back takes shared_memory_holder.
#include "yaml-cpp/node/ptr.h"

namespace {

class NodeRefPushBackTest_228 : public ::testing::Test {
protected:
  using node_ref = YAML::detail::node_ref;
  using node = YAML::detail::node;
  using shared_memory_holder = YAML::detail::shared_memory_holder;
};

TEST_F(NodeRefPushBackTest_228, PushBackDoesNotThrowOnFreshRef_228) {
  node_ref ref;
  node elem;
  shared_memory_holder mem;  // default/empty holder should be acceptable for black-box tests

  EXPECT_NO_THROW(ref.push_back(elem, mem));
}

TEST_F(NodeRefPushBackTest_228, PushBackIncreasesSizeByOne_228) {
  node_ref ref;
  node elem;
  shared_memory_holder mem;

  const std::size_t before = ref.size();
  ref.push_back(elem, mem);
  const std::size_t after = ref.size();

  EXPECT_EQ(after, before + 1);
}

TEST_F(NodeRefPushBackTest_228, MultiplePushBackAccumulatesSize_228) {
  node_ref ref;
  shared_memory_holder mem;

  node a;
  node b;
  node c;

  EXPECT_EQ(ref.size(), 0u);

  ref.push_back(a, mem);
  EXPECT_EQ(ref.size(), 1u);

  ref.push_back(b, mem);
  EXPECT_EQ(ref.size(), 2u);

  ref.push_back(c, mem);
  EXPECT_EQ(ref.size(), 3u);
}

TEST_F(NodeRefPushBackTest_228, BeginEndDistanceMatchesSizeAfterPushBack_228) {
  node_ref ref;
  shared_memory_holder mem;

  // Start empty
  EXPECT_EQ(ref.size(), 0u);
  EXPECT_EQ(ref.begin(), ref.end());

  // Add a few elements
  node a;
  node b;
  node c;
  ref.push_back(a, mem);
  ref.push_back(b, mem);
  ref.push_back(c, mem);

  ASSERT_EQ(ref.size(), 3u);
  EXPECT_NE(ref.begin(), ref.end());

  std::size_t count = 0;
  for (auto it = ref.begin(); it != ref.end(); ++it) {
    ++count;
    // We do not assume anything about iterator value semantics here (black-box).
  }
  EXPECT_EQ(count, ref.size());
}

TEST_F(NodeRefPushBackTest_228, ManyPushBackCallsProduceExpectedSize_228) {
  node_ref ref;
  shared_memory_holder mem;

  constexpr std::size_t kN = 100;
  EXPECT_EQ(ref.size(), 0u);

  for (std::size_t i = 0; i < kN; ++i) {
    node elem;
    ref.push_back(elem, mem);
  }

  EXPECT_EQ(ref.size(), kN);

  std::size_t count = 0;
  for (auto it = ref.begin(); it != ref.end(); ++it) {
    ++count;
  }
  EXPECT_EQ(count, kN);
}

}  // namespace