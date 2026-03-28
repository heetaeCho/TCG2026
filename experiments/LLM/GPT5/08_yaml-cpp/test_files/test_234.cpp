// TEST_ID: 234
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/detail/node_ref.h"

namespace YAML {
namespace detail {

class NodeRefForceInsertTest_234 : public ::testing::Test {
protected:
  // Use a default-constructed holder; tests only rely on observable behavior.
  shared_memory_holder mem_{};
};

TEST_F(NodeRefForceInsertTest_234, ForceInsertAddsNewKeyIncreasesSize_234) {
  node_ref ref;

  const std::size_t before = ref.size();
  ref.force_insert(std::string("k"), std::string("v"), mem_);
  const std::size_t after = ref.size();

  EXPECT_EQ(after, before + 1u);

  // Also verify key becomes retrievable (observable via public interface).
  EXPECT_NE(ref.get(std::string("k"), mem_), nullptr);
}

TEST_F(NodeRefForceInsertTest_234, ForceInsertSameKeyDoesNotIncreaseSize_234) {
  node_ref ref;

  ref.force_insert(std::string("k"), std::string("v1"), mem_);
  const std::size_t after_first = ref.size();

  // Force insert again with same key (value may be overwritten; we only assert size behavior).
  ref.force_insert(std::string("k"), std::string("v2"), mem_);
  const std::size_t after_second = ref.size();

  EXPECT_EQ(after_second, after_first);
  EXPECT_NE(ref.get(std::string("k"), mem_), nullptr);
}

TEST_F(NodeRefForceInsertTest_234, ForceInsertEmptyStringKeyIsAccepted_234) {
  node_ref ref;

  const std::size_t before = ref.size();
  ref.force_insert(std::string(""), std::string("v"), mem_);

  EXPECT_EQ(ref.size(), before + 1u);
  EXPECT_NE(ref.get(std::string(""), mem_), nullptr);
}

TEST_F(NodeRefForceInsertTest_234, ForceInsertNonStringKeyTypeCanBeRetrieved_234) {
  node_ref ref;

  const int key = 1;
  ref.force_insert(key, std::string("v"), mem_);

  EXPECT_NE(ref.get(key, mem_), nullptr);
  EXPECT_EQ(ref.size(), 1u);
}

TEST_F(NodeRefForceInsertTest_234, ForceInsertThenRemoveUpdatesSizeAndReturnValue_234) {
  node_ref ref;

  ref.force_insert(std::string("k"), std::string("v"), mem_);
  ASSERT_NE(ref.get(std::string("k"), mem_), nullptr);

  const std::size_t before_remove = ref.size();
  EXPECT_TRUE(ref.remove(std::string("k"), mem_));
  EXPECT_EQ(ref.size(), (before_remove > 0u ? before_remove - 1u : 0u));
  EXPECT_EQ(ref.get(std::string("k"), mem_), nullptr);

  // Removing again should be an observable "error-ish" case: return false.
  EXPECT_FALSE(ref.remove(std::string("k"), mem_));
}

}  // namespace detail
}  // namespace YAML