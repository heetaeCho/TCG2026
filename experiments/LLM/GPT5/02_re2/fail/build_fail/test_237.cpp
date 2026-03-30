// File: empty_string_test_237.cc
#include <gtest/gtest.h>
#include <string>

// Assume the function is available in the re2 namespace.
namespace re2 {
std::string* empty_string();
}

class EmptyStringTest_237 : public ::testing::Test {
protected:
  std::string backup_;

  void SetUp() override {
    ASSERT_NE(re2::empty_string(), nullptr) << "empty_string() must not return null";
    backup_ = *re2::empty_string();  // Save current observable state.
  }

  void TearDown() override {
    // Restore observable state so tests don't interfere with each other.
    *re2::empty_string() = backup_;
  }
};

// Normal operation: returns a non-null pointer to an empty std::string by default.
TEST_F(EmptyStringTest_237, ReturnsNonNullAndEmpty_237) {
  std::string* p = re2::empty_string();
  ASSERT_NE(p, nullptr);
  EXPECT_TRUE(p->empty());
  EXPECT_EQ(p->size(), 0u);
  EXPECT_EQ(*p, std::string());
}

// Normal operation: multiple calls return the same address (stable storage).
TEST_F(EmptyStringTest_237, SamePointerAcrossCalls_237) {
  std::string* p1 = re2::empty_string();
  std::string* p2 = re2::empty_string();
  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);
  EXPECT_EQ(p1, p2);
}

// External interactions: mutating through the returned pointer persists and is visible to subsequent callers.
TEST_F(EmptyStringTest_237, MutationsPersistAcrossCalls_237) {
  std::string* p = re2::empty_string();
  *p = "hello";
  std::string* q = re2::empty_string();
  EXPECT_EQ(q, p);            // same storage
  EXPECT_EQ(*q, "hello");     // mutation visible
}

// Boundary condition: can hold a long string without truncation (std::string behavior).
TEST_F(EmptyStringTest_237, SupportsLargeAssignment_237) {
  const size_t N = 10000;
  std::string long_text(N, 'x');
  *re2::empty_string() = long_text;

  std::string* p = re2::empty_string();
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(p->size(), N);
  EXPECT_EQ(*p, long_text);
}

// Boundary + normal: standard string operations (append/clear) behave as expected on the returned object.
TEST_F(EmptyStringTest_237, StandardStringOpsWork_237) {
  std::string* p = re2::empty_string();
  p->clear();
  EXPECT_TRUE(p->empty());

  p->append("a");
  p->push_back('b');
  EXPECT_EQ(*p, "ab");

  p->clear();
  EXPECT_TRUE(p->empty());
  EXPECT_EQ(p->size(), 0u);
}

// Regression-style: ensure writing then clearing returns to an empty observable state.
TEST_F(EmptyStringTest_237, ClearRestoresEmptyState_237) {
  std::string* p = re2::empty_string();
  *p = "temporary";
  EXPECT_EQ(*p, "temporary");

  p->clear();
  EXPECT_TRUE(p->empty());
  EXPECT_EQ(*p, std::string());
}
