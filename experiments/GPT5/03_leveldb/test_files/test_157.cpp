// File: version_set_by_smallest_key_test_157.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

//
// Minimal includes / forward declarations to keep tests black-box.
// We do not rely on or inspect any internal state.
//

namespace leveldb {

// Forward declarations to match the production interfaces we exercise.
class Slice;                // We don't need its definition for these tests.
class InternalKey;          // We use references only; content is irrelevant here.

// Comparator interface (matches LevelDB-style API shape just for constructing mocks).
class Comparator {
 public:
  virtual ~Comparator() = default;
  virtual const char* Name() const = 0;
  virtual int Compare(const Slice&, const Slice&) const = 0;
  virtual void FindShortestSeparator(std::string*, const Slice&) const = 0;
  virtual void FindShortSuccessor(std::string*) const = 0;
};

// InternalKeyComparator as used by BySmallestKey.
// We only need the constructor and the InternalKey overload of Compare.
class InternalKeyComparator : public Comparator {
 public:
  explicit InternalKeyComparator(const Comparator* /*user*/) {}
  // Comparator interface (not used in these tests).
  const char* Name() const override { return "test"; }
  int Compare(const Slice&, const Slice&) const override { return 0; }
  void FindShortestSeparator(std::string*, const Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}
  // The overload we care about:
  virtual int Compare(const InternalKey& a, const InternalKey& b) const {
    // Real logic is in production; tests will mock this method.
    (void)a; (void)b;
    return 0;
  }
};

// From version_edit.h (only the parts we use).
struct FileMetaData {
 public:
  int refs;
  int allowed_seeks;
  uint64_t number;
  uint64_t file_size;
  InternalKey smallest;
  InternalKey largest;

  FileMetaData()
      : refs(0), 
        allowed_seeks(1 << 30),
        number(0),
        file_size(0) {}
};

// From version_set.cc (only the comparator we test).
struct VersionSet {
  struct Builder {
    struct BySmallestKey {
      const InternalKeyComparator* internal_comparator;  // injected dependency
      bool operator()(FileMetaData* f1, FileMetaData* f2) const;
    };
  };
};

// The observable implementation as provided in the prompt snippet.
inline bool VersionSet::Builder::BySmallestKey::operator()(FileMetaData* f1, FileMetaData* f2) const {
  int r = internal_comparator->Compare(f1->smallest, f2->smallest);
  if (r != 0) {
    return (r < 0);
  } else {
    return (f1->number < f2->number);
  }
}

}  // namespace leveldb

// ---------------------- Mocks & Test Fixture ----------------------

namespace {

using ::testing::_;
using ::testing::Return;

class MockInternalKeyComparator : public leveldb::InternalKeyComparator {
 public:
  // Provide a do-nothing user comparator just to satisfy the base constructor.
  class DummyUserComparator : public leveldb::Comparator {
   public:
    const char* Name() const override { return "dummy"; }
    int Compare(const leveldb::Slice&, const leveldb::Slice&) const override { return 0; }
    void FindShortestSeparator(std::string*, const leveldb::Slice&) const override {}
    void FindShortSuccessor(std::string*) const override {}
  };

  MockInternalKeyComparator() : leveldb::InternalKeyComparator(&dummy_) {}

  // Mock the InternalKey overload used by BySmallestKey.
  MOCK_METHOD(int, Compare, (const leveldb::InternalKey& a, const leveldb::InternalKey& b), (const, override));

 private:
  DummyUserComparator dummy_;
};

class BySmallestKeyTest_157 : public ::testing::Test {
 protected:
  leveldb::FileMetaData f1_;
  leveldb::FileMetaData f2_;
  MockInternalKeyComparator mikc_;
  leveldb::VersionSet::Builder::BySmallestKey comp_{&mikc_};
};

}  // namespace

// ----------------------------- Tests -----------------------------

// Different smallest keys: internal comparator says f1 < f2  => operator() returns true.
TEST_F(BySmallestKeyTest_157, ReturnsTrueWhenSmallestKeyIsLess_157) {
  f1_.number = 100;
  f2_.number = 200;

  EXPECT_CALL(mikc_, Compare(::testing::Ref(f1_.smallest), ::testing::Ref(f2_.smallest)))
      .WillOnce(Return(-1));  // f1.smallest < f2.smallest

  EXPECT_TRUE(comp_(&f1_, &f2_));
}

// Different smallest keys: internal comparator says f1 > f2  => operator() returns false.
TEST_F(BySmallestKeyTest_157, ReturnsFalseWhenSmallestKeyIsGreater_157) {
  f1_.number = 100;
  f2_.number = 200;

  EXPECT_CALL(mikc_, Compare(::testing::Ref(f1_.smallest), ::testing::Ref(f2_.smallest)))
      .WillOnce(Return(+1));  // f1.smallest > f2.smallest

  EXPECT_FALSE(comp_(&f1_, &f2_));
}

// Equal smallest keys (Compare == 0) and f1.number < f2.number => true (tiebreak by number).
TEST_F(BySmallestKeyTest_157, TiebreakByNumberWhenKeysEqual_157) {
  f1_.number = 123;
  f2_.number = 456;

  EXPECT_CALL(mikc_, Compare(::testing::Ref(f1_.smallest), ::testing::Ref(f2_.smallest)))
      .WillOnce(Return(0));  // keys equal

  EXPECT_TRUE(comp_(&f1_, &f2_));
}

// Equal smallest keys (Compare == 0) and f1.number == f2.number => false (not strictly less).
TEST_F(BySmallestKeyTest_157, ReturnsFalseWhenKeysEqualAndNumbersEqual_157) {
  f1_.number = 777;
  f2_.number = 777;

  EXPECT_CALL(mikc_, Compare(::testing::Ref(f1_.smallest), ::testing::Ref(f2_.smallest)))
      .WillOnce(Return(0));  // keys equal

  EXPECT_FALSE(comp_(&f1_, &f2_));
}
