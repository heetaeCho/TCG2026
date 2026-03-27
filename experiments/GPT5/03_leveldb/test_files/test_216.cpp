// File: filterpolicy_createfilter_keymaymatch_test_216.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

// Assume the production headers are available in your build.
// Minimal forward declarations to compile the tests against the real codebase.
namespace leveldb {
class Slice;
class FilterPolicy;
}

// The class under test (public surface based on the prompt).
struct leveldb_filterpolicy_t : public leveldb::FilterPolicy {
  // Function-pointer collaborators exposed by the interface.
  char*   (*create_)(void*, const char* const*, const size_t*, int, size_t*);
  uint8_t (*key_match_)(void*, const char*, size_t, const char*, size_t);

  // Black-boxed methods under test.
  const char* Name() const override;  // Not tested here (behavior unspecified)
  void CreateFilter(const leveldb::Slice* keys, int n, std::string* dst) const override;
  bool KeyMayMatch(const leveldb::Slice& key, const leveldb::Slice& filter) const override;

  // The implementation calls with an opaque state pointer; our fakes ignore it.
  void* state_ = nullptr;
};

namespace leveldb {
// Minimal Slice usage: we only need construction from std::string / const char* and data()/size().
class Slice {
 public:
  Slice() : data_(""), size_(0) {}
  Slice(const char* d, size_t n) : data_(d), size_(n) {}
  Slice(const std::string& s) : data_(s.data()), size_(s.size()) {}
  Slice(const char* s) : data_(s), size_(std::char_traits<char>::length(s)) {}

  const char* data() const { return data_; }
  size_t size() const { return size_; }
 private:
  const char* data_;
  size_t size_;
};
}  // namespace leveldb

// ---------- Test Helpers (external collaborators) ----------

struct CreateCallCapture {
  // Captured inputs
  std::vector<std::string> keys_as_strings;
  std::vector<size_t> sizes;
  int n = -1;
  int call_count = 0;

  // Output to return
  std::string filter_to_return;

  void reset() {
    keys_as_strings.clear();
    sizes.clear();
    n = -1;
    call_count = 0;
    filter_to_return.clear();
  }
};

static CreateCallCapture g_create_capture;

// Fake create_ that records arguments and returns an owned buffer the callee must append and free.
static char* FakeCreate(void* /*state*/, const char* const* keys, const size_t* sizes,
                        int n, size_t* out_len) {
  g_create_capture.call_count++;
  g_create_capture.n = n;
  g_create_capture.keys_as_strings.clear();
  g_create_capture.sizes.clear();
  for (int i = 0; i < n; ++i) {
    g_create_capture.keys_as_strings.emplace_back(std::string(keys[i], sizes[i]));
    g_create_capture.sizes.emplace_back(sizes[i]);
  }
  // Allocate a heap buffer the implementation is expected to append and free.
  const std::string& payload = g_create_capture.filter_to_return;
  *out_len = payload.size();
  char* buf = static_cast<char*>(std::malloc(payload.size()));
  if (!payload.empty()) {
    std::memcpy(buf, payload.data(), payload.size());
  }
  return buf;
}

// Capture for key_match_ calls.
struct MatchCallCapture {
  std::string key;
  std::string filter;
  int call_count = 0;
  bool result_to_return = false;
  void reset() { key.clear(); filter.clear(); call_count = 0; result_to_return = false; }
};
static MatchCallCapture g_match_capture;

static uint8_t FakeKeyMatch(void* /*state*/, const char* key, size_t key_len,
                            const char* filter, size_t filter_len) {
  g_match_capture.call_count++;
  g_match_capture.key.assign(key, key_len);
  g_match_capture.filter.assign(filter, filter_len);
  return g_match_capture.result_to_return ? 1 : 0;
}

// ---------- Test Fixture ----------

class FilterPolicyTest_216 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_create_capture.reset();
    g_match_capture.reset();
    uut_.create_ = &FakeCreate;
    uut_.key_match_ = &FakeKeyMatch;
    uut_.state_ = nullptr;  // Opaque; not used by our fakes
  }
  leveldb_filterpolicy_t uut_;
};

// ---------- Tests ----------

// Normal operation: CreateFilter appends exactly what the collaborator returns,
// preserving existing content and forwarding correct key pointers/sizes.
TEST_F(FilterPolicyTest_216, CreateFilter_AppendsReturnedPayloadAndForwardsInputs_216) {
  using leveldb::Slice;

  // Arrange
  std::string existing = "prefix:";
  std::string expected_payload = "FILTER_DATA";
  g_create_capture.filter_to_return = expected_payload;

  std::vector<Slice> keys = { Slice("a"), Slice("bb") };

  std::string dst = existing;

  // Act
  uut_.CreateFilter(keys.data(), static_cast<int>(keys.size()), &dst);

  // Assert: appended payload and preserved prefix
  EXPECT_EQ(dst, existing + expected_payload);

  // Assert: collaborator called once with correct n and key material
  ASSERT_EQ(g_create_capture.call_count, 1);
  ASSERT_EQ(g_create_capture.n, 2);
  ASSERT_EQ(g_create_capture.keys_as_strings.size(), 2u);
  ASSERT_EQ(g_create_capture.sizes.size(), 2u);
  EXPECT_EQ(g_create_capture.keys_as_strings[0], "a");
  EXPECT_EQ(g_create_capture.keys_as_strings[1], "bb");
  EXPECT_EQ(g_create_capture.sizes[0], 1u);
  EXPECT_EQ(g_create_capture.sizes[1], 2u);
}

// Boundary condition: keys containing empty strings and embedded NUL bytes
// must be forwarded with exact sizes (not strlen-based truncation).
TEST_F(FilterPolicyTest_216, CreateFilter_ForwardsEmptyAndBinaryKeysPrecisely_216) {
  using leveldb::Slice;

  // Arrange
  // key2 contains an embedded NUL: "x\0y"
  const char key2_raw[] = {'x', '\0', 'y'};
  std::string binary_key(key2_raw, key2_raw + 3);
  std::vector<Slice> keys = { Slice(""), Slice(binary_key) };

  g_create_capture.filter_to_return = "X";  // minimal non-empty to exercise append
  std::string dst;

  // Act
  uut_.CreateFilter(keys.data(), static_cast<int>(keys.size()), &dst);

  // Assert: appended payload
  EXPECT_EQ(dst, "X");

  // Assert: exact forwarding of sizes and content including embedded NUL
  ASSERT_EQ(g_create_capture.call_count, 1);
  ASSERT_EQ(g_create_capture.n, 2);
  ASSERT_EQ(g_create_capture.keys_as_strings.size(), 2u);
  ASSERT_EQ(g_create_capture.sizes.size(), 2u);

  EXPECT_EQ(g_create_capture.sizes[0], 0u);
  EXPECT_EQ(g_create_capture.keys_as_strings[0], std::string());  // empty

  EXPECT_EQ(g_create_capture.sizes[1], 3u);
  EXPECT_EQ(g_create_capture.keys_as_strings[1], binary_key);
}

// Normal operation: KeyMayMatch should delegate to key_match_ and propagate boolean result,
// forwarding exact byte sequences and lengths (binary-safe).
TEST_F(FilterPolicyTest_216, KeyMayMatch_DelegatesAndPropagatesResult_216) {
  using leveldb::Slice;

  // Arrange
  const char key_raw[] = {'K', 'E', 'Y', '\0', 'Z'};
  const char filter_raw[] = {'F', 'I', 'L', 'T', 'E', 'R'};
  leveldb::Slice key(std::string(key_raw, sizeof(key_raw)));
  leveldb::Slice filter(std::string(filter_raw, sizeof(filter_raw)));

  // Case 1: collaborator returns true
  g_match_capture.result_to_return = true;

  // Act / Assert
  EXPECT_TRUE(uut_.KeyMayMatch(key, filter));

  ASSERT_EQ(g_match_capture.call_count, 1);
  EXPECT_EQ(g_match_capture.key, std::string(key_raw, sizeof(key_raw)));
  EXPECT_EQ(g_match_capture.filter, std::string(filter_raw, sizeof(filter_raw)));

  // Case 2: collaborator returns false
  g_match_capture.result_to_return = false;
  EXPECT_FALSE(uut_.KeyMayMatch(key, filter));
  EXPECT_EQ(g_match_capture.call_count, 2);  // called again
}

