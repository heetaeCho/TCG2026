// File: db/c_filterpolicy_create_test_269.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <string>
#include <vector>

// Pull in the implementation and the concrete type so we can exercise the public
// virtual interface (Name / CreateFilter / KeyMayMatch) and the destructor.
#include "db/c.cc"

// -----------------------
// Test callback scaffolding
// -----------------------

namespace {

struct TestState {
  int id = 0;
};

static void* g_destructor_called_with = nullptr;

static int g_create_called = 0;
static void* g_create_state = nullptr;
static std::vector<std::string> g_create_keys;
static std::vector<size_t> g_create_lengths;

static int g_keymatch_called = 0;
static void* g_keymatch_state = nullptr;
static std::string g_km_key;
static std::string g_km_filter;

extern "C" {

static void test_destructor(void* state) {
  g_destructor_called_with = state;
}

static char* test_create(void* state,
                         const char* const* key_array,
                         const size_t* key_length_array,
                         int num_keys,
                         size_t* filter_length) {
  g_create_called++;
  g_create_state = state;
  g_create_keys.clear();
  g_create_lengths.clear();
  for (int i = 0; i < num_keys; ++i) {
    g_create_keys.emplace_back(std::string(key_array[i], key_length_array[i]));
    g_create_lengths.emplace_back(key_length_array[i]);
  }
  // Return an empty filter (no allocation) to avoid imposing any ownership
  // requirements on the implementation.
  *filter_length = 0;
  return nullptr;
}

static uint8_t test_keymatch(void* state,
                             const char* key,
                             size_t length,
                             const char* filter,
                             size_t filter_length) {
  g_keymatch_called++;
  g_keymatch_state = state;
  g_km_key.assign(key, length);
  g_km_filter.assign(filter, filter_length);

  // Deterministic return so we can assert propagation.
  // Return 1 for key "k1" in filter "F", else 0.
  if (g_km_key == "k1" && g_km_filter == "F") return 1;
  return 0;
}

static const char* test_name(void* /*state*/) {
  return "MyFilterPolicy";
}

} // extern "C"

class FilterPolicyCreateTest_269 : public ::testing::Test {
protected:
  void SetUp() override {
    g_destructor_called_with = nullptr;

    g_create_called = 0;
    g_create_state = nullptr;
    g_create_keys.clear();
    g_create_lengths.clear();

    g_keymatch_called = 0;
    g_keymatch_state = nullptr;
    g_km_key.clear();
    g_km_filter.clear();
  }
};

} // namespace

// -----------------------
// Tests
// -----------------------

TEST_F(FilterPolicyCreateTest_269, ReturnsNonNull_269) {
  TestState state{42};
  leveldb_filterpolicy_t* p = leveldb_filterpolicy_create(
      &state, &test_destructor, &test_create, &test_keymatch, &test_name);
  ASSERT_NE(p, nullptr);
  delete p;  // ensure no crash on destruction
}

TEST_F(FilterPolicyCreateTest_269, NameForwardsToCallback_269) {
  TestState state{7};
  leveldb_filterpolicy_t* p = leveldb_filterpolicy_create(
      &state, &test_destructor, &test_create, &test_keymatch, &test_name);

  // Call through the public virtual.
  const FilterPolicy* api = p;  // upcast to interface
  EXPECT_STREQ(api->Name(), "MyFilterPolicy");

  delete p;
}

TEST_F(FilterPolicyCreateTest_269, CreateFilter_ForwardsArgs_AndDoesNotAppendWhenEmpty_269) {
  TestState state{101};
  leveldb_filterpolicy_t* p = leveldb_filterpolicy_create(
      &state, &test_destructor, &test_create, &test_keymatch, &test_name);

  const FilterPolicy* api = p;

  // Prepare keys
  Slice keys_arr[2] = { Slice("foo"), Slice("barbaz") };

  std::string dst = "prefix:";
  api->CreateFilter(keys_arr, 2, &dst);

  // Callback was invoked with forwarded parameters
  EXPECT_EQ(g_create_called, 1);
  EXPECT_EQ(g_create_state, &state);
  ASSERT_EQ(g_create_keys.size(), 2u);
  EXPECT_EQ(g_create_keys[0], "foo");
  EXPECT_EQ(g_create_keys[1], "barbaz");
  ASSERT_EQ(g_create_lengths.size(), 2u);
  EXPECT_EQ(g_create_lengths[0], 3u);
  EXPECT_EQ(g_create_lengths[1], 6u);

  // Since our callback returned nullptr with length 0, the destination should be unchanged.
  EXPECT_EQ(dst, "prefix:");

  delete p;
}

TEST_F(FilterPolicyCreateTest_269, KeyMayMatch_ForwardsArgs_AndPropagatesReturn_269) {
  TestState state{202};
  leveldb_filterpolicy_t* p = leveldb_filterpolicy_create(
      &state, &test_destructor, &test_create, &test_keymatch, &test_name);

  const FilterPolicy* api = p;

  // Case 1: Should return true (1) for key "k1" in filter "F"
  bool r1 = api->KeyMayMatch(Slice("k1"), Slice("F"));
  EXPECT_TRUE(r1);
  EXPECT_EQ(g_keymatch_called, 1);
  EXPECT_EQ(g_keymatch_state, &state);
  EXPECT_EQ(g_km_key, "k1");
  EXPECT_EQ(g_km_filter, "F");

  // Case 2: Different inputs → should return false (0)
  bool r2 = api->KeyMayMatch(Slice("other"), Slice("F"));
  EXPECT_FALSE(r2);
  EXPECT_EQ(g_keymatch_called, 2);
  EXPECT_EQ(g_km_key, "other");
  EXPECT_EQ(g_km_filter, "F");

  delete p;
}

TEST_F(FilterPolicyCreateTest_269, Destructor_InvokesProvidedDestructorWithState_269) {
  TestState state{909};
  leveldb_filterpolicy_t* p = leveldb_filterpolicy_create(
      &state, &test_destructor, &test_create, &test_keymatch, &test_name);

  // Deleting the object should call the user-provided destructor with the same state pointer.
  delete p;
  EXPECT_EQ(g_destructor_called_with, &state);
}

TEST_F(FilterPolicyCreateTest_269, CanConstructWithNullCallbacks_ObjectStillConstructs_269) {
  // The interface allows passing nullptrs; we do not invoke any virtuals in this case.
  TestState state{0};
  leveldb_filterpolicy_t* p = leveldb_filterpolicy_create(
      &state, /*destructor=*/nullptr, /*create=*/nullptr,
      /*key_may_match=*/nullptr, /*name=*/nullptr);
  ASSERT_NE(p, nullptr);
  // Do NOT call Name/CreateFilter/KeyMayMatch — undefined behavior if callbacks are null.
  delete p;
}
