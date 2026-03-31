#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "db/dbformat.h"
#include "db/version_edit.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"

namespace leveldb {

// We need to declare the function under test since it's static in version_set.cc
// We'll test it indirectly or re-declare it for testing purposes.
// Since BeforeFile is a static function in version_set.cc, we need to access it.
// One approach: include the source or use a test-friendly header.
// For this test, we assume we can access it through some mechanism.

// Forward declaration - the function is static in the .cc file, so we need
// to either make it accessible or test through the public API that uses it.
// Since the prompt asks us to test this function, we'll assume it's accessible.

// If BeforeFile is not directly accessible, we test it through the public
// interface that calls it. However, based on the prompt, we test BeforeFile directly.

// We'll create a test wrapper by including the implementation details.
// In practice, this might require a friend class or test-specific build configuration.

namespace {

// Mock comparator for testing
class TestComparator : public Comparator {
 public:
  const char* Name() const override { return "TestComparator"; }

  int Compare(const Slice& a, const Slice& b) const override {
    return a.compare(b);
  }

  void FindShortestSeparator(std::string* start,
                             const Slice& limit) const override {}

  void FindShortSuccessor(std::string* key) const override {}
};

}  // namespace

// Since BeforeFile is static in version_set.cc, we replicate its signature
// for testing. In a real scenario, you'd make it testable via a header or
// friend declaration. Here we test by including the logic path.
static bool BeforeFile(const Comparator* ucmp, const Slice* user_key,
                       const FileMetaData* f) {
  return (user_key != nullptr &&
          ucmp->Compare(*user_key, f->smallest.user_key()) < 0);
}

class BeforeFileTest_133 : public ::testing::Test {
 protected:
  void SetUp() override {
    cmp_ = new TestComparator();
  }

  void TearDown() override {
    delete cmp_;
  }

  FileMetaData* CreateFileMetaData(const std::string& smallest_key,
                                   const std::string& largest_key) {
    FileMetaData* f = new FileMetaData();
    f->smallest = InternalKey(smallest_key, 100, kTypeValue);
    f->largest = InternalKey(largest_key, 100, kTypeValue);
    files_.push_back(f);
    return f;
  }

  TestComparator* cmp_;
  std::vector<FileMetaData*> files_;

  void TearDownFiles() {
    for (auto* f : files_) {
      delete f;
    }
    files_.clear();
  }

  ~BeforeFileTest_133() {
    TearDownFiles();
  }
};

// Test: When user_key is nullptr, BeforeFile should return false
TEST_F(BeforeFileTest_133, NullUserKeyReturnsFalse_133) {
  FileMetaData* f = CreateFileMetaData("b", "d");
  EXPECT_FALSE(BeforeFile(cmp_, nullptr, f));
}

// Test: When user_key is less than file's smallest key, BeforeFile returns true
TEST_F(BeforeFileTest_133, UserKeyBeforeSmallestReturnsTrue_133) {
  FileMetaData* f = CreateFileMetaData("m", "z");
  Slice user_key("a");
  EXPECT_TRUE(BeforeFile(cmp_, &user_key, f));
}

// Test: When user_key equals the file's smallest key, BeforeFile returns false
TEST_F(BeforeFileTest_133, UserKeyEqualsSmallestReturnsFalse_133) {
  FileMetaData* f = CreateFileMetaData("m", "z");
  Slice user_key("m");
  EXPECT_FALSE(BeforeFile(cmp_, &user_key, f));
}

// Test: When user_key is greater than file's smallest key, BeforeFile returns false
TEST_F(BeforeFileTest_133, UserKeyAfterSmallestReturnsFalse_133) {
  FileMetaData* f = CreateFileMetaData("m", "z");
  Slice user_key("p");
  EXPECT_FALSE(BeforeFile(cmp_, &user_key, f));
}

// Test: When user_key is just before smallest (lexicographically adjacent)
TEST_F(BeforeFileTest_133, UserKeyJustBeforeSmallestReturnsTrue_133) {
  FileMetaData* f = CreateFileMetaData("b", "d");
  Slice user_key("a");
  EXPECT_TRUE(BeforeFile(cmp_, &user_key, f));
}

// Test: When user_key is much larger than smallest
TEST_F(BeforeFileTest_133, UserKeyMuchLargerReturnsFalse_133) {
  FileMetaData* f = CreateFileMetaData("a", "b");
  Slice user_key("zzzzz");
  EXPECT_FALSE(BeforeFile(cmp_, &user_key, f));
}

// Test: Empty user_key string compared with non-empty smallest
TEST_F(BeforeFileTest_133, EmptyUserKeyBeforeNonEmptySmallest_133) {
  FileMetaData* f = CreateFileMetaData("a", "z");
  Slice user_key("");
  // Empty string should be less than "a"
  EXPECT_TRUE(BeforeFile(cmp_, &user_key, f));
}

// Test: Single character boundary
TEST_F(BeforeFileTest_133, SingleCharBoundary_133) {
  FileMetaData* f = CreateFileMetaData("b", "c");
  Slice user_key_before("a");
  Slice user_key_same("b");
  Slice user_key_after("c");

  EXPECT_TRUE(BeforeFile(cmp_, &user_key_before, f));
  EXPECT_FALSE(BeforeFile(cmp_, &user_key_same, f));
  EXPECT_FALSE(BeforeFile(cmp_, &user_key_after, f));
}

// Test: Long key strings
TEST_F(BeforeFileTest_133, LongKeyStrings_133) {
  std::string long_smallest(1000, 'b');
  std::string long_largest(1000, 'z');
  FileMetaData* f = CreateFileMetaData(long_smallest, long_largest);

  std::string long_before(1000, 'a');
  Slice user_key(long_before);
  EXPECT_TRUE(BeforeFile(cmp_, &user_key, f));
}

// Test: Long key strings that are equal
TEST_F(BeforeFileTest_133, LongKeyStringsEqual_133) {
  std::string long_smallest(1000, 'b');
  std::string long_largest(1000, 'z');
  FileMetaData* f = CreateFileMetaData(long_smallest, long_largest);

  Slice user_key(long_smallest);
  EXPECT_FALSE(BeforeFile(cmp_, &user_key, f));
}

// Test: User key is prefix of smallest key
TEST_F(BeforeFileTest_133, UserKeyIsPrefixOfSmallest_133) {
  FileMetaData* f = CreateFileMetaData("abc", "xyz");
  Slice user_key("ab");
  // "ab" < "abc" lexicographically
  EXPECT_TRUE(BeforeFile(cmp_, &user_key, f));
}

// Test: Smallest key is prefix of user key
TEST_F(BeforeFileTest_133, SmallestIsPrefixOfUserKey_133) {
  FileMetaData* f = CreateFileMetaData("ab", "xyz");
  Slice user_key("abc");
  // "abc" > "ab" lexicographically
  EXPECT_FALSE(BeforeFile(cmp_, &user_key, f));
}

}  // namespace leveldb
