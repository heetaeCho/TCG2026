// filter_block_builder_addkey_test_372.cc
#include <gtest/gtest.h>
#include <string>
#include <vector>

namespace leveldb {

// ---- Minimal Slice needed by AddKey (test scaffold only) ----
class Slice {
 public:
  Slice() : data_(""), size_(0) {}
  Slice(const char* d, size_t n) : data_(d), size_(n) {}
  Slice(const std::string& s) : data_(s.data()), size_(s.size()) {}
  Slice(const char* s) : data_(s), size_(strlen(s)) {}
  const char* data() const { return data_; }
  size_t size() const { return size_; }
 private:
  const char* data_;
  size_t size_;
};

// ---- Forward declaration for dependency used by the CUT ----
class FilterPolicy {};

// ---- CUT declaration (as per provided header) ----
class FilterBlockBuilder {
 private:
  const FilterPolicy* policy_;
  std::string keys_;
  std::vector<size_t> start_;
  std::string result_;
  std::vector<Slice> tmp_keys_;
  std::vector<uint32_t> filter_offsets_;

 public:
  explicit FilterBlockBuilder(const FilterPolicy* policy) : policy_(policy) {}

  void StartBlock(uint64_t /*block_offset*/); // not used here
  void AddKey(const Slice& key);
  Slice Finish(); // not used here

 private:
  void GenerateFilter(); // not used here
};

// ---- CUT partial implementation provided (AddKey only) ----
void FilterBlockBuilder::AddKey(const Slice& key) {
  Slice k = key;
  start_.push_back(keys_.size());
  keys_.append(k.data(), k.size());
}

}  // namespace leveldb

// -------------------- Tests --------------------

using leveldb::FilterBlockBuilder;
using leveldb::FilterPolicy;
using leveldb::Slice;

TEST(FilterBlockBuilderTest_372, AddKey_WithCString_372) {
  FilterPolicy* policy = nullptr; // policy unused by AddKey
  FilterBlockBuilder b(policy);

  // Should accept a C-string key without throwing or crashing.
  b.AddKey(Slice("hello"));
  SUCCEED();
}

TEST(FilterBlockBuilderTest_372, AddKey_WithStdString_372) {
  FilterPolicy* policy = nullptr;
  FilterBlockBuilder b(policy);

  std::string k = "abc123";
  b.AddKey(Slice(k));
  SUCCEED();
}

TEST(FilterBlockBuilderTest_372, AddKey_WithEmptySlice_372) {
  FilterPolicy* policy = nullptr;
  FilterBlockBuilder b(policy);

  // Explicit empty key
  Slice empty("", 0);
  b.AddKey(empty);
  SUCCEED();
}

TEST(FilterBlockBuilderTest_372, AddKey_WithBinaryData_372) {
  FilterPolicy* policy = nullptr;
  FilterBlockBuilder b(policy);

  // Key containing embedded NUL bytes should be accepted.
  const char raw[] = {'A', '\0', 'B', '\0', 'C'};
  Slice bin(raw, sizeof(raw));
  b.AddKey(bin);
  SUCCEED();
}

TEST(FilterBlockBuilderTest_372, AddKey_WithLargeKey_372) {
  FilterPolicy* policy = nullptr;
  FilterBlockBuilder b(policy);

  // Large key boundary (e.g., ~1MB) should be accepted.
  std::string large(1 << 20, 'x'); // 1 MiB
  b.AddKey(Slice(large));
  SUCCEED();
}
