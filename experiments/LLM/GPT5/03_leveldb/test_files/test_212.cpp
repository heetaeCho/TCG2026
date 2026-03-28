// File: db/c_comparator_test_212.cc

#include <gtest/gtest.h>
#include <string>

// Bring in Slice and the comparator wrapper declarations.
// In a real codebase you'd include the proper headers, but for this exercise
// we rely on the provided partials.
#include "leveldb/slice.h"
#include "db/c.cc"  // Provides struct leveldb_comparator_t definition

using leveldb::Slice;

namespace {

// Test helper context carried in comparator->state_.
struct TestContext {
  // For Compare callback verification:
  int compare_return = 0;
  void* last_state = nullptr;
  const char* last_a = nullptr;
  size_t last_a_size = 0;
  const char* last_b = nullptr;
  size_t last_b_size = 0;

  // For destructor callback verification:
  bool destructor_called = false;

  // For name callback verification:
  const char* name = "test.name";
};

// Callback implementations that operate only via the public state pointer.
int CompareCb(void* s,
              const char* a, size_t a_sz,
              const char* b, size_t b_sz) {
  auto* ctx = static_cast<TestContext*>(s);
  ctx->last_state   = s;
  ctx->last_a       = a;
  ctx->last_a_size  = a_sz;
  ctx->last_b       = b;
  ctx->last_b_size  = b_sz;
  return ctx->compare_return;
}

void DestructorCb(void* s) {
  auto* ctx = static_cast<TestContext*>(s);
  ctx->destructor_called = true;
}

const char* NameCb(void* s) {
  auto* ctx = static_cast<TestContext*>(s);
  return ctx->name;
}

struct ComparatorTest : public ::testing::Test {
  leveldb_comparator_t cmp{};
  TestContext ctx{};

  void SetUp() override {
    cmp.state_ = &ctx;
    cmp.compare_ = &CompareCb;
    cmp.destructor_ = &DestructorCb;
    cmp.name_ = &NameCb;
  }
};

}  // namespace

// ----- Normal operation: Compare forwards and returns callback value
TEST_F(ComparatorTest, Compare_ForwardsArgsAndReturn_212) {
  ctx.compare_return = -1;

  std::string sa = "alpha";
  std::string sb = "beta";
  Slice a(sa);
  Slice b(sb);

  const int ret = cmp.Compare(a, b);
  EXPECT_EQ(ret, -1);

  // Verify callback observed exactly what Compare forwarded.
  EXPECT_EQ(ctx.last_state, &ctx);
  EXPECT_EQ(ctx.last_a, a.data());
  EXPECT_EQ(ctx.last_a_size, a.size());
  EXPECT_EQ(ctx.last_b, b.data());
  EXPECT_EQ(ctx.last_b_size, b.size());
}

// ----- Boundary: empty slices
TEST_F(ComparatorTest, Compare_EmptySlices_212) {
  ctx.compare_return = 0;

  // Explicit empty with (ptr, len) constructor to ensure size=0 is forwarded.
  const char* dummy = "ignored";
  Slice a(dummy, 0);
  Slice b(dummy, 0);

  const int ret = cmp.Compare(a, b);
  EXPECT_EQ(ret, 0);

  EXPECT_EQ(ctx.last_a_size, 0u);
  EXPECT_EQ(ctx.last_b_size, 0u);
  // When size is 0, data() may be any valid pointer; only the size matters.
  // We deliberately do not assert on ctx.last_a/last_b pointer values here.
}

// ----- Boundary: binary data containing NULs and different lengths
TEST_F(ComparatorTest, Compare_BinaryDataAndSizes_212) {
  ctx.compare_return = 1;

  const char a_buf[3] = {'a', '\0', 'b'};
  const char b_buf[1] = {'x'};

  Slice a(a_buf, sizeof(a_buf));  // includes embedded NUL
  Slice b(b_buf, sizeof(b_buf));

  const int ret = cmp.Compare(a, b);
  EXPECT_EQ(ret, 1);

  EXPECT_EQ(ctx.last_a_size, sizeof(a_buf));
  EXPECT_EQ(ctx.last_b_size, sizeof(b_buf));
  EXPECT_EQ(memcmp(ctx.last_a, a_buf, sizeof(a_buf)), 0);
  EXPECT_EQ(memcmp(ctx.last_b, b_buf, sizeof(b_buf)), 0);
}

// ----- Name() returns what the name_ callback provides
TEST_F(ComparatorTest, Name_ReturnsCallbackResult_212) {
  ctx.name = "my.custom.comparator";
  EXPECT_STREQ(cmp.Name(), "my.custom.comparator");

  ctx.name = "another.name";
  EXPECT_STREQ(cmp.Name(), "another.name");
}

// ----- Destructor must invoke the provided destructor_ callback with state_
TEST_F(ComparatorTest, Destructor_InvokesCallback_212) {
  // Allocate a fresh comparator to trigger its destructor deterministically.
  auto* heap_cmp = new leveldb_comparator_t{};
  TestContext local_ctx{};
  heap_cmp->state_ = &local_ctx;
  heap_cmp->compare_ = &CompareCb;
  heap_cmp->destructor_ = &DestructorCb;
  heap_cmp->name_ = &NameCb;

  EXPECT_FALSE(local_ctx.destructor_called);
  delete heap_cmp;  // should call DestructorCb(&local_ctx)
  EXPECT_TRUE(local_ctx.destructor_called);
}

// ----- Smoketests for separator/successor hooks: they should be callable safely
TEST_F(ComparatorTest, FindShortestSeparator_Smoke_212) {
  std::string start = "key1";
  Slice limit("keyZ");
  // We do not assert specific mutation semantics (black-box),
  // only that the call is safe and does not crash.
  cmp.FindShortestSeparator(&start, limit);
  // start remains a valid string; no further assumption.
  SUCCEED();
}

TEST_F(ComparatorTest, FindShortSuccessor_Smoke_212) {
  std::string key = "keyMiddle";
  cmp.FindShortSuccessor(&key);
  SUCCEED();
}
