// TEST_ID: 263
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/detail/node.h"

namespace {

using YAML::detail::node;

// Helper: create a default/shared memory holder (implementation-defined in yaml-cpp).
static YAML::shared_memory_holder MakeMemory_263() {
  return YAML::shared_memory_holder{};
}

class NodeForceInsertTest_263 : public ::testing::Test {
 protected:
  YAML::shared_memory_holder mem_ = MakeMemory_263();
};

TEST_F(NodeForceInsertTest_263, ForceInsertIntoEmptyNodeCreatesEntry_263) {
  node n;
  node k;
  node v;

  k.set_scalar("key");
  v.set_scalar("value");

  const std::size_t before = n.size();
  EXPECT_NO_THROW(n.force_insert(k, v, mem_));

  EXPECT_EQ(n.size(), before + 1u);

  // Verify observable retrieval via the public interface.
  node lookup;
  lookup.set_scalar("key");
  node* got = n.get(lookup, mem_);
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got->scalar(), "value");
}

TEST_F(NodeForceInsertTest_263, ForceInsertSameKeyOverwritesValueWithoutGrowingSize_263) {
  node n;

  node k1;
  k1.set_scalar("dup");

  node v1;
  v1.set_scalar("first");

  ASSERT_NO_THROW(n.force_insert(k1, v1, mem_));
  ASSERT_EQ(n.size(), 1u);

  node v2;
  v2.set_scalar("second");

  // Force-inserting the same key again should be observable as either overwrite
  // or at least not increasing size (typical "force_insert" behavior).
  EXPECT_NO_THROW(n.force_insert(k1, v2, mem_));

  EXPECT_EQ(n.size(), 1u);

  node lookup;
  lookup.set_scalar("dup");
  node* got = n.get(lookup, mem_);
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got->scalar(), "second");
}

TEST_F(NodeForceInsertTest_263, ForceInsertAcceptsStringKeyAndNodeValue_263) {
  node n;

  node v;
  v.set_scalar("vv");

  EXPECT_NO_THROW(n.force_insert(std::string("sk"), v, mem_));
  EXPECT_EQ(n.size(), 1u);

  node* got = n.get(std::string("sk"), mem_);
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got->scalar(), "vv");
}

TEST_F(NodeForceInsertTest_263, ForceInsertAcceptsCStringKeyAndNodeValue_263) {
  node n;

  node v;
  v.set_scalar("val");

  EXPECT_NO_THROW(n.force_insert("ckey", v, mem_));
  EXPECT_EQ(n.size(), 1u);

  node* got = n.get("ckey", mem_);
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got->scalar(), "val");
}

TEST_F(NodeForceInsertTest_263, ForceInsertWithEmptyKeyAndEmptyScalarValueIsRetrievable_263) {
  node n;

  node k;
  k.set_scalar("");

  node v;
  v.set_scalar("");

  EXPECT_NO_THROW(n.force_insert(k, v, mem_));
  EXPECT_EQ(n.size(), 1u);

  node lookup;
  lookup.set_scalar("");
  node* got = n.get(lookup, mem_);
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got->scalar(), "");
}

TEST_F(NodeForceInsertTest_263, ForceInsertAfterNodeWasScalarStillAllowsRetrieval_263) {
  node n;
  n.set_scalar("was-scalar");

  node k;
  k.set_scalar("k");

  node v;
  v.set_scalar("v");

  // Observable behavior: call should not crash; afterward, inserted entry should be retrievable.
  EXPECT_NO_THROW(n.force_insert(k, v, mem_));

  node lookup;
  lookup.set_scalar("k");
  node* got = n.get(lookup, mem_);
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got->scalar(), "v");
}

TEST_F(NodeForceInsertTest_263, ForceInsertThenRemoveMakesKeyUnavailable_263) {
  node n;

  node k;
  k.set_scalar("rm");

  node v;
  v.set_scalar("x");

  ASSERT_NO_THROW(n.force_insert(k, v, mem_));
  ASSERT_EQ(n.size(), 1u);

  EXPECT_TRUE(n.remove(k, mem_));
  EXPECT_EQ(n.size(), 0u);

  node* got = n.get(k, mem_);
  EXPECT_EQ(got, nullptr);
}

}  // namespace