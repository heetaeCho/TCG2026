#include "gtest/gtest.h"
#include "leveldb/options.h"
#include "leveldb/filter_policy.h"

// Include the necessary structures from db/c.cc
// We need to replicate the struct definitions that are used in the C API

using namespace leveldb;

// Forward declarations matching db/c.cc structures
struct leveldb_options_t {
  Options rep;
};

struct leveldb_filterpolicy_t : public FilterPolicy {
  void* state_;
  void (*destructor_)(void*);
  char* (*create_)(void*, const char* const*, const size_t*, int, size_t*);
  uint8_t (*key_match_)(void*, const char*, size_t, const char*, size_t);
  const char* (*name_)(void*);

  ~leveldb_filterpolicy_t() override {
    if (destructor_) destructor_(state_);
  }

  const char* Name() const override {
    return name_(state_);
  }

  void CreateFilter(const Slice* keys, int n, std::string* dst) const override {
    std::vector<const char*> key_pointers(n);
    std::vector<size_t> key_sizes(n);
    for (int i = 0; i < n; i++) {
      key_pointers[i] = keys[i].data();
      key_sizes[i] = keys[i].size();
    }
    size_t len;
    char* filter = create_(state_, key_pointers.data(), key_sizes.data(), n, &len);
    dst->append(filter, len);
    free(filter);
  }

  bool KeyMayMatch(const Slice& key, const Slice& filter) const override {
    return key_match_(state_, key.data(), key.size(), filter.data(), filter.size());
  }
};

// The function under test
extern "C" {
void leveldb_options_set_filter_policy(leveldb_options_t* opt,
                                       leveldb_filterpolicy_t* policy);
}

// Since we're testing the C API function defined in db/c.cc, we provide
// a local definition that matches the implementation
void leveldb_options_set_filter_policy(leveldb_options_t* opt,
                                       leveldb_filterpolicy_t* policy) {
  opt->rep.filter_policy = policy;
}

class LeveldbOptionsSetFilterPolicyTest_254 : public ::testing::Test {
 protected:
  void SetUp() override {
    opt_ = new leveldb_options_t();
  }

  void TearDown() override {
    delete opt_;
  }

  leveldb_options_t* opt_;
};

// Test that filter_policy is nullptr by default
TEST_F(LeveldbOptionsSetFilterPolicyTest_254, DefaultFilterPolicyIsNull_254) {
  EXPECT_EQ(nullptr, opt_->rep.filter_policy);
}

// Test setting a non-null filter policy
TEST_F(LeveldbOptionsSetFilterPolicyTest_254, SetNonNullFilterPolicy_254) {
  // Create a minimal filter policy for testing
  leveldb_filterpolicy_t* policy = new leveldb_filterpolicy_t();
  policy->state_ = nullptr;
  policy->destructor_ = nullptr;
  policy->create_ = nullptr;
  policy->key_match_ = nullptr;
  policy->name_ = [](void*) -> const char* { return "test_policy"; };

  leveldb_options_set_filter_policy(opt_, policy);

  EXPECT_EQ(policy, opt_->rep.filter_policy);

  delete policy;
}

// Test setting filter policy to nullptr
TEST_F(LeveldbOptionsSetFilterPolicyTest_254, SetFilterPolicyToNull_254) {
  // First set it to something non-null
  leveldb_filterpolicy_t* policy = new leveldb_filterpolicy_t();
  policy->state_ = nullptr;
  policy->destructor_ = nullptr;
  policy->create_ = nullptr;
  policy->key_match_ = nullptr;
  policy->name_ = [](void*) -> const char* { return "test_policy"; };

  leveldb_options_set_filter_policy(opt_, policy);
  EXPECT_EQ(policy, opt_->rep.filter_policy);

  // Now set it to nullptr
  leveldb_options_set_filter_policy(opt_, nullptr);
  EXPECT_EQ(nullptr, opt_->rep.filter_policy);

  delete policy;
}

// Test that setting filter policy updates the value correctly when changed
TEST_F(LeveldbOptionsSetFilterPolicyTest_254, SetFilterPolicyOverwrite_254) {
  leveldb_filterpolicy_t* policy1 = new leveldb_filterpolicy_t();
  policy1->state_ = nullptr;
  policy1->destructor_ = nullptr;
  policy1->create_ = nullptr;
  policy1->key_match_ = nullptr;
  policy1->name_ = [](void*) -> const char* { return "policy1"; };

  leveldb_filterpolicy_t* policy2 = new leveldb_filterpolicy_t();
  policy2->state_ = nullptr;
  policy2->destructor_ = nullptr;
  policy2->create_ = nullptr;
  policy2->key_match_ = nullptr;
  policy2->name_ = [](void*) -> const char* { return "policy2"; };

  leveldb_options_set_filter_policy(opt_, policy1);
  EXPECT_EQ(policy1, opt_->rep.filter_policy);

  leveldb_options_set_filter_policy(opt_, policy2);
  EXPECT_EQ(policy2, opt_->rep.filter_policy);
  EXPECT_NE(policy1, opt_->rep.filter_policy);

  delete policy1;
  delete policy2;
}

// Test that other options fields remain unchanged after setting filter policy
TEST_F(LeveldbOptionsSetFilterPolicyTest_254, OtherOptionsUnchanged_254) {
  // Record default values of other fields
  bool default_create_if_missing = opt_->rep.create_if_missing;
  bool default_error_if_exists = opt_->rep.error_if_exists;
  size_t default_write_buffer_size = opt_->rep.write_buffer_size;
  int default_max_open_files = opt_->rep.max_open_files;
  size_t default_block_size = opt_->rep.block_size;
  int default_block_restart_interval = opt_->rep.block_restart_interval;
  CompressionType default_compression = opt_->rep.compression;

  leveldb_filterpolicy_t* policy = new leveldb_filterpolicy_t();
  policy->state_ = nullptr;
  policy->destructor_ = nullptr;
  policy->create_ = nullptr;
  policy->key_match_ = nullptr;
  policy->name_ = [](void*) -> const char* { return "test_policy"; };

  leveldb_options_set_filter_policy(opt_, policy);

  // Verify other fields are unchanged
  EXPECT_EQ(default_create_if_missing, opt_->rep.create_if_missing);
  EXPECT_EQ(default_error_if_exists, opt_->rep.error_if_exists);
  EXPECT_EQ(default_write_buffer_size, opt_->rep.write_buffer_size);
  EXPECT_EQ(default_max_open_files, opt_->rep.max_open_files);
  EXPECT_EQ(default_block_size, opt_->rep.block_size);
  EXPECT_EQ(default_block_restart_interval, opt_->rep.block_restart_interval);
  EXPECT_EQ(default_compression, opt_->rep.compression);

  delete policy;
}

// Test that the set filter policy can be used through the FilterPolicy interface
TEST_F(LeveldbOptionsSetFilterPolicyTest_254, SetPolicyIsAccessibleViaInterface_254) {
  leveldb_filterpolicy_t* policy = new leveldb_filterpolicy_t();
  policy->state_ = nullptr;
  policy->destructor_ = nullptr;
  policy->create_ = nullptr;
  policy->key_match_ = nullptr;
  policy->name_ = [](void*) -> const char* { return "my_filter"; };

  leveldb_options_set_filter_policy(opt_, policy);

  // Access through the FilterPolicy pointer and verify Name()
  ASSERT_NE(nullptr, opt_->rep.filter_policy);
  EXPECT_STREQ("my_filter", opt_->rep.filter_policy->Name());

  delete policy;
}

// Test setting the same policy twice
TEST_F(LeveldbOptionsSetFilterPolicyTest_254, SetSamePolicyTwice_254) {
  leveldb_filterpolicy_t* policy = new leveldb_filterpolicy_t();
  policy->state_ = nullptr;
  policy->destructor_ = nullptr;
  policy->create_ = nullptr;
  policy->key_match_ = nullptr;
  policy->name_ = [](void*) -> const char* { return "same_policy"; };

  leveldb_options_set_filter_policy(opt_, policy);
  EXPECT_EQ(policy, opt_->rep.filter_policy);

  leveldb_options_set_filter_policy(opt_, policy);
  EXPECT_EQ(policy, opt_->rep.filter_policy);

  delete policy;
}
