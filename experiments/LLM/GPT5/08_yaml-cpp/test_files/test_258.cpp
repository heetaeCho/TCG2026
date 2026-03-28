// TEST_ID: 258
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"

namespace {

using YAML::detail::node;
using YAML::detail::shared_memory_holder;
using YAML::NodeType;

class NodeInsertTest_258 : public ::testing::Test {
 protected:
  static node MakeScalar(const std::string& s) {
    node n;
    n.set_scalar(s);
    return n;
  }
};

TEST_F(NodeInsertTest_258, InsertIntoEmptyNode_CreatesRetrievableMappingEntry_258) {
  shared_memory_holder mem;  // default/empty holder should be acceptable for tests

  node parent;
  node key = MakeScalar("k");
  node value = MakeScalar("v");

  ASSERT_NO_THROW(parent.insert(key, value, mem));

  EXPECT_GE(parent.size(), 1u);

  node* found = parent.get("k", mem);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->scalar(), "v");
}

TEST_F(NodeInsertTest_258, InsertMultipleDistinctKeys_AllEntriesAreRetrievable_258) {
  shared_memory_holder mem;

  node parent;
  node k1 = MakeScalar("k1");
  node v1 = MakeScalar("v1");
  node k2 = MakeScalar("k2");
  node v2 = MakeScalar("v2");

  ASSERT_NO_THROW(parent.insert(k1, v1, mem));
  ASSERT_NO_THROW(parent.insert(k2, v2, mem));

  EXPECT_GE(parent.size(), 2u);

  node* f1 = parent.get("k1", mem);
  ASSERT_NE(f1, nullptr);
  EXPECT_EQ(f1->scalar(), "v1");

  node* f2 = parent.get("k2", mem);
  ASSERT_NE(f2, nullptr);
  EXPECT_EQ(f2->scalar(), "v2");
}

TEST_F(NodeInsertTest_258, InsertWithEmptyScalarKeyAndValue_IsHandled_258) {
  shared_memory_holder mem;

  node parent;
  node key = MakeScalar("");
  node value = MakeScalar("");

  try {
    parent.insert(key, value, mem);
  } catch (...) {
    SUCCEED() << "insert() threw for empty key/value; acceptable as an observable error case.";
    return;
  }

  EXPECT_GE(parent.size(), 1u);
  node* found = parent.get("", mem);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->scalar(), "");
}

TEST_F(NodeInsertTest_258, InsertWhenParentIsPreTypedSequence_IsHandledOrThrows_258) {
  shared_memory_holder mem;

  node parent;
  parent.set_type(NodeType::Sequence);

  node key = MakeScalar("k");
  node value = MakeScalar("v");

  try {
    parent.insert(key, value, mem);
  } catch (...) {
    SUCCEED() << "insert() threw when parent was pre-typed as Sequence; acceptable observable error case.";
    return;
  }

  // If it didn't throw, it should still be usable in an observable way.
  EXPECT_GE(parent.size(), 1u);
  node* found = parent.get("k", mem);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->scalar(), "v");
}

TEST_F(NodeInsertTest_258, InsertDoesNotMutateKeyOrValueScalars_258) {
  shared_memory_holder mem;

  node parent;
  node key = MakeScalar("k");
  node value = MakeScalar("v");

  ASSERT_NO_THROW(parent.insert(key, value, mem));

  // Observable post-condition: key/value remain usable and keep their scalars.
  EXPECT_EQ(key.scalar(), "k");
  EXPECT_EQ(value.scalar(), "v");

  node* found = parent.get("k", mem);
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->scalar(), "v");
}

}  // namespace