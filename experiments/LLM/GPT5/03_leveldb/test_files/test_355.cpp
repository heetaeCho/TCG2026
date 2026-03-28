// File: memtable_key_comparator_test_355.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <unordered_map>
#include <functional>

//
// ---- Test doubles for external collaborators (allowed by constraints) ----
// We only fake collaborators that KeyComparator depends on:
//   1) GetLengthPrefixedSlice(const char*)
//   2) InternalKeyComparator (as a Comparator)
//
// We DO NOT touch or reimplement MemTable::KeyComparator internals.
//

namespace leveldb {

// Minimal Slice satisfying KeyComparator’s observable needs.
class Slice {
 public:
  Slice() : data_(""), size_(0) {}
  Slice(const char* d, size_t n) : data_(d), size_(n) {}
  explicit Slice(const std::string& s) : data_(s.data()), size_(s.size()) {}

  const char* data() const { return data_; }
  size_t size() const { return size_; }
  std::string ToString() const { return std::string(data_, size_); }
 private:
  const char* data_;
  size_t size_;
};

// Minimal Comparator interface (as in LevelDB).
class Comparator {
 public:
  virtual ~Comparator() = default;
  virtual int Compare(const Slice& a, const Slice& b) const = 0;
  virtual const char* Name() const = 0;
  virtual void FindShortestSeparator(std::string*, const Slice&) const {}
  virtual void FindShortSuccessor(std::string*) const {}
};

// ---- Fake registry to control what GetLengthPrefixedSlice returns ----
static std::unordered_map<const char*, Slice> g_lp_registry;

static void RegisterLP(const char* ptr, const Slice& s) {
  g_lp_registry[ptr] = s;
}

static void ClearLPRegistry() {
  g_lp_registry.clear();
}

// Test-double for the free function used by KeyComparator.
Slice GetLengthPrefixedSlice(const char* p) {
  auto it = g_lp_registry.find(p);
  if (it == g_lp_registry.end()) {
    return Slice(); // empty by default if not registered
  }
  return it->second;
}

// ---- Fake InternalKeyComparator that simply delegates to an injected functor ----
class InternalKeyComparator : public Comparator {
 public:
  using CompareFn = std::function<int(const Slice&, const Slice&)>;

  explicit InternalKeyComparator(const Comparator* /*user*/) {} // unused
  explicit InternalKeyComparator(CompareFn fn) : fn_(std::move(fn)) {}

  int Compare(const Slice& a, const Slice& b) const override {
    return fn_ ? fn_(a, b) : 0;
  }
  const char* Name() const override { return "FakeInternalKeyComparator"; }

 private:
  CompareFn fn_;
};

// ---- Minimal MemTable::KeyComparator declaration mirroring production API ----
// (We do NOT re-implement operator(); it is linked from the production .cc)
struct MemTable {
  struct KeyComparator {
    const InternalKeyComparator comparator;
    explicit KeyComparator(const InternalKeyComparator& c) : comparator(c) {}
    int operator()(const char* a, const char* b) const;  // implemented in prod
  };
};

} // namespace leveldb

using namespace leveldb;

// ----------------------------- Test Fixture -----------------------------
class MemTableKeyComparatorTest_355 : public ::testing::Test {
 protected:
  void TearDown() override { ClearLPRegistry(); }
};

// ------------------------------- Test Cases -------------------------------

// Verifies KeyComparator forwards decoded slices to the comparator and
// returns its result.
TEST_F(MemTableKeyComparatorTest_355, ForwardsToComparator_ReturnsResult_355) {
  // Arrange: create two distinct "length-prefixed" pointers and register slices.
  static const char kA[] = "ignored-payload-a";
  static const char kB[] = "ignored-payload-b";
  RegisterLP(kA, Slice(std::string("user-key-1")));
  RegisterLP(kB, Slice(std::string("user-key-2")));

  // Comparator functor that checks it received exactly our registered slices,
  // and returns a sentinel result.
  const int kSentinel = 7;
  InternalKeyComparator icmp(
      InternalKeyComparator::CompareFn([&](const Slice& a, const Slice& b) {
        EXPECT_EQ(a.ToString(), "user-key-1");
        EXPECT_EQ(b.ToString(), "user-key-2");
        return kSentinel;
      }));

  MemTable::KeyComparator kc(icmp);

  // Act
  int result = kc(kA, kB);

  // Assert
  EXPECT_EQ(result, kSentinel);
}

// When both pointers decode to the *same* slice, the comparator should
// see identical inputs. We return 0 to emulate equality.
TEST_F(MemTableKeyComparatorTest_355, SameSlice_YieldsEqualityFromComparator_355) {
  static const char kSame[] = "ignored-payload-same";
  RegisterLP(kSame, Slice(std::string("dup-key")));

  InternalKeyComparator icmp(
      InternalKeyComparator::CompareFn([&](const Slice& a, const Slice& b) {
        EXPECT_EQ(a.ToString(), "dup-key");
        EXPECT_EQ(b.ToString(), "dup-key");
        return 0;  // equality per fake comparator
      }));

  MemTable::KeyComparator kc(icmp);

  int result = kc(kSame, kSame);
  EXPECT_EQ(result, 0);
}

// If the decoder yields an empty slice (e.g., unregistered pointer),
// KeyComparator should still pass that empty slice to the comparator.
// We return a unique value to assert the path is exercised.
TEST_F(MemTableKeyComparatorTest_355, UnregisteredPointer_DecodesToEmptySlice_355) {
  static const char kUnknown1[] = "u1";
  static const char kUnknown2[] = "u2";
  // Note: Not registering these -> GetLengthPrefixedSlice returns empty Slice().

  InternalKeyComparator icmp(
      InternalKeyComparator::CompareFn([&](const Slice& a, const Slice& b) {
        EXPECT_EQ(a.size(), 0u);
        EXPECT_EQ(b.size(), 0u);
        return -3;  // arbitrary sentinel indicating "both empty" in our fake
      }));

  MemTable::KeyComparator kc(icmp);

  int result = kc(kUnknown1, kUnknown2);
  EXPECT_EQ(result, -3);
}

// Boundary-ish check: large keys (to ensure no truncation by KeyComparator).
TEST_F(MemTableKeyComparatorTest_355, LargeKeys_AreForwardedIntact_355) {
  const std::string bigA(4096, 'A');
  const std::string bigB(4096, 'B');

  static const char kA[] = "ptrA";
  static const char kB[] = "ptrB";
  RegisterLP(kA, Slice(bigA));
  RegisterLP(kB, Slice(bigB));

  InternalKeyComparator icmp(
      InternalKeyComparator::CompareFn([&](const Slice& a, const Slice& b) {
        EXPECT_EQ(a.size(), bigA.size());
        EXPECT_EQ(b.size(), bigB.size());
        EXPECT_EQ(a.ToString(), bigA);
        EXPECT_EQ(b.ToString(), bigB);
        // Return negative to simulate comparator saying A < B.
        return -1;
      }));

  MemTable::KeyComparator kc(icmp);

  int result = kc(kA, kB);
  EXPECT_LT(result, 0);
}
