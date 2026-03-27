// File: empty_named_groups_test_238.cc
#include <gtest/gtest.h>
#include <map>
#include <string>

// Include the implementation unit directly so we can access the internal-linkage function.
// We are NOT re-implementing any logic; just including the real code under test.
#include "TestProjects/re2/re2/re2.cc"

namespace {

class EmptyNamedGroupsTest_238 : public ::testing::Test {
 protected:
  // Utility to ensure we don't leak state between tests if we mutate via the public pointer.
  struct ClearGuard {
    std::map<std::string, int>* m;
    explicit ClearGuard(std::map<std::string, int>* mp) : m(mp) {}
    ~ClearGuard() { if (m) m->clear(); }
  };
};

}  // namespace

// Verifies the function returns a valid (non-null) pointer.
TEST_F(EmptyNamedGroupsTest_238, ReturnsNonNull_238) {
  std::map<std::string, int>* ptr = re2::empty_named_groups();
  ASSERT_NE(ptr, nullptr);
}

// Verifies the pointed-to map is initially empty (observable via the interface).
TEST_F(EmptyNamedGroupsTest_238, InitiallyEmpty_238) {
  std::map<std::string, int>* ptr = re2::empty_named_groups();
  ASSERT_NE(ptr, nullptr);
  EXPECT_TRUE(ptr->empty());
  EXPECT_EQ(ptr->size(), 0u);
}

// Verifies the returned pointer is stable across multiple calls (same address).
TEST_F(EmptyNamedGroupsTest_238, PointerStableAcrossCalls_238) {
  std::map<std::string, int>* a = re2::empty_named_groups();
  std::map<std::string, int>* b = re2::empty_named_groups();
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_EQ(a, b);
}

// Verifies that changes made through the returned pointer are observable on subsequent calls.
// (And cleans up after itself to avoid leaking state between tests.)
TEST_F(EmptyNamedGroupsTest_238, ModificationVisibleAcrossCalls_238) {
  std::map<std::string, int>* first = re2::empty_named_groups();
  ASSERT_NE(first, nullptr);
  EmptyNamedGroupsTest_238::ClearGuard guard(first);  // ensure cleanup

  // Map should start empty according to interface-observable behavior.
  ASSERT_TRUE(first->empty());

  // Modify via the public pointer.
  first->insert({"alpha", 1});
  first->insert({"beta", 2});

  // A subsequent call should observe the same mutations if the pointer targets shared storage.
  std::map<std::string, int>* second = re2::empty_named_groups();
  ASSERT_NE(second, nullptr);
  EXPECT_EQ(first, second);
  EXPECT_EQ(second->size(), 2u);
  EXPECT_EQ(second->at("alpha"), 1);
  EXPECT_EQ(second->at("beta"), 2);
}

// Verifies that clearing via the returned pointer results in an empty map (observable effect).
TEST_F(EmptyNamedGroupsTest_238, ClearEmptiesMap_238) {
  std::map<std::string, int>* ptr = re2::empty_named_groups();
  ASSERT_NE(ptr, nullptr);

  // Populate, then clear, verifying observable behavior only.
  ptr->insert({"k", 42});
  ASSERT_FALSE(ptr->empty());

  ptr->clear();
  EXPECT_TRUE(ptr->empty());
  EXPECT_EQ(ptr->size(), 0u);
}
