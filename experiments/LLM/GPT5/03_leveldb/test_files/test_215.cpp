// File: db/c_filterpolicy_test_215.cc
#include "gtest/gtest.h"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "leveldb/filter_policy.h"
#include "leveldb/slice.h"

// The class under test (from db/c.cc)
struct leveldb_filterpolicy_t : public leveldb::FilterPolicy {
  // Public collaborators (from the provided partial/deps snippet)
  void* state_{nullptr};
  const char* (*name_)(void*) = nullptr;
  char* (*create_)(void*, const char* const*, const size_t*, int, size_t*) = nullptr;
  uint8_t (*key_match_)(void*, const char*, size_t, const char*, size_t) = nullptr;

  ~leveldb_filterpolicy_t() override = default;

  // Methods under test
  const char* Name() const override;
  void CreateFilter(const leveldb::Slice* keys, int n, std::string* dst) const override;
  bool KeyMayMatch(const leveldb::Slice& key, const leveldb::Slice& filter) const override;
};

// ---------------------- Test Fixture ----------------------
class FilterPolicyTest_215 : public ::testing::Test {
 protected:
  // Shared capture fields to verify external-callback interactions
  struct Captures {
    // For Name()
    void* name_state = nullptr;

    // For CreateFilter()
    void* create_state = nullptr;
    int create_n = -1;
    std::vector<std::string> create_keys_data;
    std::vector<size_t> create_keys_sizes;

    // For KeyMayMatch()
    void* match_state = nullptr;
    std::string match_key_data;
    size_t match_key_size = 0;
    std::string match_filter_data;
    size_t match_filter_size = 0;
  } caps;

  leveldb_filterpolicy_t policy;

  void SetUp() override {
    policy.state_ = &caps;
    policy.name_ = &NameCb;
    policy.create_ = &CreateCb;
    policy.key_match_ = &MatchCb;
  }

  // ---- External collaborator implementations ----

  static const char* NameCb(void* s) {
    auto* caps = static_cast<Captures*>(s);
    caps->name_state = s;
    // Return a stable C-string literal to avoid lifetime issues.
    return "c-api-filterpolicy";
  }

  static char* CreateCb(void* s,
                        const char* const* keys,
                        const size_t* key_sizes,
                        int n,
                        size_t* out_len) {
    auto* caps = static_cast<Captures*>(s);
    caps->create_state = s;
    caps->create_n = n;
    caps->create_keys_data.clear();
    caps->create_keys_sizes.clear();
    for (int i = 0; i < n; ++i) {
      caps->create_keys_data.emplace_back(std::string(keys[i], key_sizes[i]));
      caps->create_keys_sizes.emplace_back(key_sizes[i]);
    }

    // Produce a small filter byte sequence. Allocate with malloc since
    // the C wrapper typically frees via free().
    static const char kPayload[] = "FILTER_BYTES";
    const size_t len = sizeof(kPayload) - 1;
    char* buf = static_cast<char*>(std::malloc(len));
    std::memcpy(buf, kPayload, len);
    *out_len = len;
    return buf;
  }

  // This variable controls what MatchCb returns (to test both paths).
  static uint8_t& MatchReturnRef() {
    static uint8_t ret = 1;
    return ret;
  }

  static uint8_t MatchCb(void* s,
                         const char* key, size_t key_len,
                         const char* filter, size_t filter_len) {
    auto* caps = static_cast<Captures*>(s);
    caps->match_state = s;
    caps->match_key_data.assign(key, key_len);
    caps->match_key_size = key_len;
    caps->match_filter_data.assign(filter, filter_len);
    caps->match_filter_size = filter_len;
    return MatchReturnRef();
  }
};

// ---------------------- Tests ----------------------

TEST_F(FilterPolicyTest_215, NameReturnsCallbackValue_215) {
  // Act
  const char* name = policy.Name();

  // Assert: callback was invoked with state, and return value is exposed
  EXPECT_STREQ("c-api-filterpolicy", name);
  EXPECT_EQ(&caps, caps.name_state);
}

TEST_F(FilterPolicyTest_215, CreateFilter_PassesKeysAndAppendsToDst_215) {
  // Arrange: two keys
  leveldb::Slice keys[2] = { leveldb::Slice("k1", 2), leveldb::Slice("k\0x", 3) };
  std::string dst = "prefix:";

  // Act
  policy.CreateFilter(keys, 2, &dst);

  // Assert: external callback saw the exact keys and sizes
  ASSERT_EQ(&caps, caps.create_state);
  ASSERT_EQ(2, caps.create_n);
  ASSERT_EQ(2u, caps.create_keys_data.size());
  ASSERT_EQ(2u, caps.create_keys_sizes.size());
  EXPECT_EQ(std::string("k1", 2), caps.create_keys_data[0]);
  EXPECT_EQ(2u, caps.create_keys_sizes[0]);
  EXPECT_EQ(std::string("k\0x", 3), caps.create_keys_data[1]);
  EXPECT_EQ(3u, caps.create_keys_sizes[1]);

  // And dst contains previous contents plus the produced filter bytes
  EXPECT_TRUE(dst.rfind("prefix:", 0) == 0);  // still starts with "prefix:"
  EXPECT_NE(std::string::npos, dst.find("FILTER_BYTES"));
}

TEST_F(FilterPolicyTest_215, CreateFilter_WithZeroKeys_ProducesFilter_215) {
  // Arrange: no keys
  std::string dst;

  // Act
  policy.CreateFilter(nullptr, 0, &dst);

  // Assert: still calls through with n=0 and appends some bytes
  EXPECT_EQ(0, caps.create_n);
  EXPECT_FALSE(dst.empty());
  EXPECT_NE(std::string::npos, dst.find("FILTER_BYTES"));
}

TEST_F(FilterPolicyTest_215, KeyMayMatch_ReturnsTrueFromCallback_215) {
  // Arrange
  FilterPolicyTest_215::MatchReturnRef() = 1;  // force "true"
  const leveldb::Slice key("hello");
  const leveldb::Slice filter("FILTER_BYTES");

  // Act
  const bool may = policy.KeyMayMatch(key, filter);

  // Assert: return value and parameter wiring
  EXPECT_TRUE(may);
  EXPECT_EQ(&caps, caps.match_state);
  EXPECT_EQ("hello", caps.match_key_data);
  EXPECT_EQ(5u, caps.match_key_size);
  EXPECT_EQ("FILTER_BYTES", caps.match_filter_data);
  EXPECT_EQ(std::strlen("FILTER_BYTES"), caps.match_filter_size);
}

TEST_F(FilterPolicyTest_215, KeyMayMatch_ReturnsFalseFromCallback_215) {
  // Arrange
  FilterPolicyTest_215::MatchReturnRef() = 0;  // force "false"
  const leveldb::Slice key("x");
  const leveldb::Slice filter("");

  // Act
  const bool may = policy.KeyMayMatch(key, filter);

  // Assert: return value and parameter wiring
  EXPECT_FALSE(may);
  EXPECT_EQ(&caps, caps.match_state);
  EXPECT_EQ("x", caps.match_key_data);
  EXPECT_EQ(1u, caps.match_key_size);
  EXPECT_EQ("", caps.match_filter_data);
  EXPECT_EQ(0u, caps.match_filter_size);
}
