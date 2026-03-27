// File: tests/options_set_filter_policy_test.cc

#include <gtest/gtest.h>

// Minimal forward declarations strictly from the provided interface.
// (We are not re-implementing any logic; just declaring types/signatures to compile tests.)

namespace leveldb {
struct FilterPolicy;  // opaque here
struct Options {
  // Only the member we need for observable verification, as exposed by the provided interface.
  const FilterPolicy* filter_policy = nullptr;
  Options() = default;
};
}  // namespace leveldb

// C API wrapper types from db/c.cc (per provided partials)
struct leveldb_filterpolicy_t : public leveldb::FilterPolicy {
  // Concrete definition exists in the production codebase; we don't rely on its internals.
  virtual ~leveldb_filterpolicy_t() = default;
  virtual const char* Name() const = 0;
  virtual void CreateFilter(const class leveldb::Slice* keys, int n, std::string* dst) const = 0;
  virtual bool KeyMayMatch(const class leveldb::Slice& key, const class leveldb::Slice& filter) const = 0;
};

struct leveldb_options_t {
  leveldb::Options rep;
};

// Target function under test (from db/c.cc)
void leveldb_options_set_filter_policy(leveldb_options_t* opt, leveldb_filterpolicy_t* policy);

// ---------- Test Fixture ----------
class OptionsFilterPolicyTest_254 : public ::testing::Test {
protected:
  leveldb_options_t opt_;
};

// ---------- Tests ----------

// Verifies: setting a non-null policy pointer is reflected via the public member in Options.
TEST_F(OptionsFilterPolicyTest_254, SetsNonNullPolicyPointer_254) {
  // Arrange
  // Create a concrete policy pointer without depending on behavior.
  // We cannot instantiate an abstract type directly, so we create a trivial concrete subclass
  // that satisfies pure-virtuals without asserting on behavior (no internal simulation).
  struct DummyPolicy : leveldb_filterpolicy_t {
    const char* Name() const override { return "DummyPolicy"; }
    void CreateFilter(const leveldb::Slice*, int, std::string*) const override {}
    bool KeyMayMatch(const leveldb::Slice&, const leveldb::Slice&) const override { return false; }
  } policy;

  ASSERT_EQ(opt_.rep.filter_policy, nullptr) << "Precondition: default filter_policy should be null";

  // Act
  leveldb_options_set_filter_policy(&opt_, &policy);

  // Assert
  EXPECT_EQ(opt_.rep.filter_policy, &policy);
}

// Verifies: setting nullptr clears the policy pointer (boundary case).
TEST_F(OptionsFilterPolicyTest_254, SetsNullPolicyPointer_254) {
  // Arrange
  struct DummyPolicy : leveldb_filterpolicy_t {
    const char* Name() const override { return "DummyPolicy"; }
    void CreateFilter(const leveldb::Slice*, int, std::string*) const override {}
    bool KeyMayMatch(const leveldb::Slice&, const leveldb::Slice&) const override { return false; }
  } policy;

  leveldb_options_set_filter_policy(&opt_, &policy);
  ASSERT_NE(opt_.rep.filter_policy, nullptr) << "Precondition: policy should be set";

  // Act
  leveldb_options_set_filter_policy(&opt_, nullptr);

  // Assert
  EXPECT_EQ(opt_.rep.filter_policy, nullptr);
}

// Verifies: calling again with a different policy overwrites the previous one (idempotent replace).
TEST_F(OptionsFilterPolicyTest_254, OverwritesExistingPolicyPointer_254) {
  // Arrange
  struct DummyPolicyA : leveldb_filterpolicy_t {
    const char* Name() const override { return "PolicyA"; }
    void CreateFilter(const leveldb::Slice*, int, std::string*) const override {}
    bool KeyMayMatch(const leveldb::Slice&, const leveldb::Slice&) const override { return false; }
  } policy_a;

  struct DummyPolicyB : leveldb_filterpolicy_t {
    const char* Name() const override { return "PolicyB"; }
    void CreateFilter(const leveldb::Slice*, int, std::string*) const override {}
    bool KeyMayMatch(const leveldb::Slice&, const leveldb::Slice&) const override { return false; }
  } policy_b;

  leveldb_options_set_filter_policy(&opt_, &policy_a);
  ASSERT_EQ(opt_.rep.filter_policy, &policy_a) << "Precondition: first policy should be set";

  // Act
  leveldb_options_set_filter_policy(&opt_, &policy_b);

  // Assert
  EXPECT_EQ(opt_.rep.filter_policy, &policy_b);
}
