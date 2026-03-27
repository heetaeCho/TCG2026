// File: db/c_filterpolicy_destroy_test_270.cc

#include <gtest/gtest.h>
#include <atomic>
#include <string>

// If your project exposes these via headers, prefer including them.
// The declarations below are only to make the test self-contained to compile
// in isolation; they do not re-implement any logic of the CUT.

struct Slice;                  // Forward decl; we never touch its internals.
class FilterPolicy {           // Minimal interface surface used by the CUT.
public:
  virtual ~FilterPolicy() = default;
  virtual const char* Name() const = 0;
  virtual void CreateFilter(const Slice* /*keys*/, int /*n*/, std::string* /*dst*/) const = 0;
  virtual bool KeyMayMatch(const Slice& /*key*/, const Slice& /*filter*/) const = 0;
};

// The type under test (base of instances that leveldb_filterpolicy_destroy deletes).
struct leveldb_filterpolicy_t : public FilterPolicy {
  // The real implementation defines these; we do NOT rely on them.
  // We provide pure-virtuals so our test subclass must implement them,
  // ensuring the vtable is resolvable without needing the production defs.
  ~leveldb_filterpolicy_t() override = default;
  virtual const char* Name() const override = 0;
  virtual void CreateFilter(const Slice* keys, int n, std::string* dst) const override = 0;
  virtual bool KeyMayMatch(const Slice& key, const Slice& filter) const override = 0;
};

// CUT: provided by production code (db/c.cc).
extern "C" void leveldb_filterpolicy_destroy(leveldb_filterpolicy_t* filter);

// ---------------------------- Test Doubles ---------------------------------

// A concrete test filter we can safely allocate/delete via the CUT.
// Its destructor toggles observable flags so we can assert behavior.
class TestFilter : public leveldb_filterpolicy_t {
public:
  TestFilter() { ++alive_count_; }
  ~TestFilter() override {
    dtor_called_ = true;
    --alive_count_;
  }

  const char* Name() const override { return "TestFilter"; }
  void CreateFilter(const Slice* /*keys*/, int /*n*/, std::string* /*dst*/) const override {}
  bool KeyMayMatch(const Slice& /*key*/, const Slice& /*filter*/) const override { return false; }

  // Observables
  static std::atomic<bool> dtor_called_;
  static std::atomic<int>  alive_count_;
};

std::atomic<bool> TestFilter::dtor_called_{false};
std::atomic<int>  TestFilter::alive_count_{0};

// -------------------------------- Fixture ----------------------------------

class FilterPolicyDestroyTest_270 : public ::testing::Test {
protected:
  void SetUp() override {
    TestFilter::dtor_called_ = false;
    TestFilter::alive_count_ = 0;
  }
};

// ------------------------------- Test Cases --------------------------------

// Verifies that deleting a valid object calls the most-derived destructor.
TEST_F(FilterPolicyDestroyTest_270, DestructorIsInvoked_270) {
  auto* fp = new TestFilter();  // Allocate an object the CUT will delete.
  ASSERT_EQ(TestFilter::alive_count_.load(), 1);

  // Act: destroy via the CUT (deletes through base pointer).
  leveldb_filterpolicy_destroy(fp);

  // Assert: most-derived dtor ran and object count reflects deletion.
  EXPECT_TRUE(TestFilter::dtor_called_.load());
  EXPECT_EQ(TestFilter::alive_count_.load(), 0);
}

// Verifies that passing nullptr is safe (no crash, no throw).
TEST_F(FilterPolicyDestroyTest_270, NullptrIsNoop_270) {
  // Expect no exception; GoogleTest will also fail the test if it crashes.
  EXPECT_NO_THROW(leveldb_filterpolicy_destroy(nullptr));
}

