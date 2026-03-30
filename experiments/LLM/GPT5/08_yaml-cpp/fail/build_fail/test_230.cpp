// TEST_ID: 230
// File: node_ref_get_tests_230.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/memory.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"

namespace {

using namespace YAML::detail;

class NodeRefGetTest_230 : public ::testing::Test {
 protected:
  shared_memory_holder mem_{new memory_holder};
};

TEST_F(NodeRefGetTest_230, GetMissingKeyOnFreshNodeRefReturnsNull_230) {
  node_ref ref;

  node* out = ref.get("missing", mem_);
  EXPECT_EQ(out, nullptr);

  out = ref.get(std::string("also-missing"), mem_);
  EXPECT_EQ(out, nullptr);
}

TEST_F(NodeRefGetTest_230, ForceInsertStringKeyThenGetReturnsNonNull_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  ref.force_insert(std::string("k"), std::string("v"), mem_);

  node* out = ref.get(std::string("k"), mem_);
  ASSERT_NE(out, nullptr);

  // Observable behavior: returned node is usable via its public interface.
  EXPECT_EQ(out->scalar(), "v");
}

TEST_F(NodeRefGetTest_230, GetSupportsDifferentKeyTypesForSameLogicalKey_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  ref.force_insert(std::string("k"), std::string("v"), mem_);

  node* out1 = ref.get("k", mem_);  // const char*
  ASSERT_NE(out1, nullptr);
  EXPECT_EQ(out1->scalar(), "v");

  node* out2 = ref.get(std::string("k"), mem_);
  ASSERT_NE(out2, nullptr);
  EXPECT_EQ(out2->scalar(), "v");
}

TEST_F(NodeRefGetTest_230, GetWithEmptyStringKeyWorksWhenPresent_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  ref.force_insert(std::string(""), std::string("empty-key-value"), mem_);

  node* out = ref.get(std::string(""), mem_);
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->scalar(), "empty-key-value");
}

TEST_F(NodeRefGetTest_230, GetWithIntegerKeyFindsValueWhenInsertedWithIntegerKey_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  ref.force_insert(1, std::string("one"), mem_);
  ref.force_insert(2, std::string("two"), mem_);

  node* out1 = ref.get(1, mem_);
  ASSERT_NE(out1, nullptr);
  EXPECT_EQ(out1->scalar(), "one");

  node* out2 = ref.get(2, mem_);
  ASSERT_NE(out2, nullptr);
  EXPECT_EQ(out2->scalar(), "two");

  node* missing = ref.get(3, mem_);
  EXPECT_EQ(missing, nullptr);
}

TEST_F(NodeRefGetTest_230, GetAfterRemoveReturnsNull_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);

  ref.force_insert(std::string("k"), std::string("v"), mem_);
  ASSERT_NE(ref.get("k", mem_), nullptr);

  EXPECT_TRUE(ref.remove("k", mem_));
  EXPECT_EQ(ref.get("k", mem_), nullptr);

  // Removing again should be an observable "not found" style result.
  EXPECT_FALSE(ref.remove("k", mem_));
}

TEST_F(NodeRefGetTest_230, GetCallableOnConstNodeRef_230) {
  node_ref ref;
  ref.set_type(NodeType::Map);
  ref.force_insert(std::string("k"), std::string("v"), mem_);

  const node_ref& cref = ref;
  node* out = cref.get(std::string("k"), mem_);
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->scalar(), "v");
}

}  // namespace