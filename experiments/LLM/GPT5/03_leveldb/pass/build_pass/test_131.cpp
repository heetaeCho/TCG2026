// File: version_set_findfile_test_131.cc

#include <gtest/gtest.h>
#include <vector>
#include <set>
#include <string>
#include <cstring>

//
// ---- Minimal stubs for external collaborators (allowed by constraints) ----
// These are lightweight stand-ins so we can observe FindFile's behavior via its
// public interface. They do NOT replicate production internals.
//

namespace leveldb {

// --- Slice (string-view-like) ---
class Slice {
 public:
  Slice() : data_(""), size_(0) {}
  Slice(const char* d, size_t n) : data_(d), size_(n) {}
  Slice(const std::string& s) : data_(s.data()), size_(s.size()) {}
  Slice(const char* s) : data_(s), size_(std::strlen(s)) {}
  Slice(const Slice&) = default;
  Slice& operator=(const Slice&) = default;

  const char* data() const { return data_; }
  size_t size() const { return size_; }
  std::string ToString() const { return std::string(data_, size_); }

  // Lexicographic compare by bytes
  int compare(const Slice& b) const {
    const size_t min_len = size_ < b.size_ ? size_ : b.size_;
    int r = std::memcmp(data_, b.data_, min_len);
    if (r == 0) {
      if (size_ < b.size_) return -1;
      if (size_ > b.size_) return +1;
      return 0;
    }
    return r < 0 ? -1 : +1;
  }

 private:
  const char* data_;
  size_t size_;
};

// --- Minimal Comparator base (signature only) ---
class Comparator {
 public:
  virtual ~Comparator() = default;
  virtual const char* Name() const = 0;
  virtual int Compare(const Slice& a, const Slice& b) const = 0;
  virtual void FindShortestSeparator(std::string*, const Slice&) const {}
  virtual void FindShortSuccessor(std::string*) const {}
};

// --- A simple user comparator (bytewise) ---
class BytewiseComparator : public Comparator {
 public:
  const char* Name() const override { return "test.BytewiseComparator"; }
  int Compare(const Slice& a, const Slice& b) const override { return a.compare(b); }
};

// --- Minimal InternalKey that just wraps a user key for Encode() ---
class InternalKey {
 public:
  InternalKey() = default;
  explicit InternalKey(const Slice& user_key) : uk_(user_key.ToString()) {}
  Slice Encode() const { return Slice(uk_); }            // returns user key bytes
  Slice user_key() const { return Slice(uk_); }
 private:
  std::string uk_;
};

// --- InternalKeyComparator that compares by underlying user key bytes ---
class InternalKeyComparator : public Comparator {
 public:
  explicit InternalKeyComparator(const Comparator* user) : user_(user) {}
  const char* Name() const override { return "test.InternalKeyComparator"; }
  int Compare(const Slice& a, const Slice& b) const override {
    // In this stub, a and b are treated as already-encoded keys whose
    // user-key portion is the whole buffer.
    return user_->Compare(a, b);
  }
  // Unused virtual helpers kept for interface compatibility
  void FindShortestSeparator(std::string*, const Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}
  const Comparator* user_comparator() const { return user_; }
 private:
  const Comparator* user_;
};

// --- FileMetaData (only fields used) ---
struct FileMetaData {
  int refs = 0;
  int allowed_seeks = (1 << 30);
  uint64_t number = 0;
  uint64_t file_size = 0;
  InternalKey smallest;
  InternalKey largest;
  FileMetaData() = default;
};

} // namespace leveldb

//
// ---- Code under test (exact snippet from prompt; not re-implemented) ----
//

namespace leveldb {

int FindFile(const InternalKeyComparator& icmp,
             const std::vector<FileMetaData*>& files,
             const Slice& key) {
  uint32_t left = 0;
  uint32_t right = files.size();
  while (left < right) {
    uint32_t mid = (left + right) / 2;
    const FileMetaData* f = files[mid];
    if (icmp.InternalKeyComparator::Compare(f->largest.Encode(), key) < 0) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  return right;
}

} // namespace leveldb

//
// ---- Test Fixture ----
//

class FindFileTest_131 : public ::testing::Test {
 protected:
  leveldb::BytewiseComparator user_cmp_;
  leveldb::InternalKeyComparator icmp_{&user_cmp_};

  // Helper to build a vector of FileMetaData* with given "largest" keys
  std::vector<leveldb::FileMetaData*> MakeFiles(const std::vector<std::string>& largest_keys) {
    std::vector<leveldb::FileMetaData*> out;
    out.reserve(largest_keys.size());
    for (const auto& k : largest_keys) {
      auto* f = new leveldb::FileMetaData();
      f->largest = leveldb::InternalKey(leveldb::Slice(k));
      out.push_back(f);
    }
    return out;
  }

  // Helper to clean up
  static void FreeFiles(std::vector<leveldb::FileMetaData*>& files) {
    for (auto* f : files) delete f;
    files.clear();
  }
};

//
// ---- Tests ----
//

// Behavior: empty file list should yield index 0
TEST_F(FindFileTest_131, EmptyReturnsZero_131) {
  std::vector<leveldb::FileMetaData*> files;
  int idx = leveldb::FindFile(icmp_, files, leveldb::Slice("a"));
  EXPECT_EQ(idx, 0);
}

// Behavior: if key <= first file's largest, return 0
TEST_F(FindFileTest_131, KeyLessThanOrEqualFirstLargest_131) {
  auto files = MakeFiles({"b", "d", "f"});
  // key < "b" -> 0
  EXPECT_EQ(leveldb::FindFile(icmp_, files, leveldb::Slice("a")), 0);
  // key == "b" -> 0
  EXPECT_EQ(leveldb::FindFile(icmp_, files, leveldb::Slice("b")), 0);
  FreeFiles(files);
}

// Behavior: key between largest[i] and largest[i+1] returns i+1
TEST_F(FindFileTest_131, KeyBetweenLargestReturnsNextIndex_131) {
  auto files = MakeFiles({"b", "d", "f"});
  // "c" is > "b" and <= "d" -> index 1
  EXPECT_EQ(leveldb::FindFile(icmp_, files, leveldb::Slice("c")), 1);
  // "e" is > "d" and <= "f" -> index 2
  EXPECT_EQ(leveldb::FindFile(icmp_, files, leveldb::Slice("e")), 2);
  FreeFiles(files);
}

// Behavior: key equal to an interior largest returns that index
TEST_F(FindFileTest_131, KeyEqualToInteriorLargest_131) {
  auto files = MakeFiles({"b", "d", "f"});
  EXPECT_EQ(leveldb::FindFile(icmp_, files, leveldb::Slice("d")), 1);
  EXPECT_EQ(leveldb::FindFile(icmp_, files, leveldb::Slice("f")), 2);
  FreeFiles(files);
}

// Boundary: key greater than all largest values returns files.size()
TEST_F(FindFileTest_131, KeyGreaterThanAllReturnsSize_131) {
  auto files = MakeFiles({"b", "d", "f"});
  EXPECT_EQ(leveldb::FindFile(icmp_, files, leveldb::Slice("g")), 3);
  FreeFiles(files);
}

// Boundary: duplicate largest keys — should return first index >= key
TEST_F(FindFileTest_131, DuplicateLargestKeysReturnFirstMatch_131) {
  auto files = MakeFiles({"b", "d", "d", "f"});
  // For key "d", lower_bound behavior -> first "d" at index 1
  EXPECT_EQ(leveldb::FindFile(icmp_, files, leveldb::Slice("d")), 1);
  // For key between the duplicates (equal), still 1
  EXPECT_EQ(leveldb::FindFile(icmp_, files, leveldb::Slice("d")), 1);
  // For key just greater than "d" but <= "f" -> index 3
  EXPECT_EQ(leveldb::FindFile(icmp_, files, leveldb::Slice("e")), 3);
  FreeFiles(files);
}
