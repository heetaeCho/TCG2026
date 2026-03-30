// File: table/footer_index_handle_test.cc

#include "table/format.h"
#include "gtest/gtest.h"

namespace leveldb {

class FooterIndexHandleTest_394 : public ::testing::Test {
 protected:
  Footer f_;
};

// [Normal] After setting an index handle, the getter should expose the same
// observable values through the BlockHandle public API.
TEST_F(FooterIndexHandleTest_394, ReturnsSetHandleValues_394) {
  BlockHandle h;
  // Choose distinct values to make mismatches obvious.
  const uint64_t kOffset = 12345u;
  const uint64_t kSize   = 67890u;

  // These calls rely only on BlockHandle's public interface.
  h.set_offset(kOffset);
  h.set_size(kSize);

  f_.set_index_handle(h);

  const BlockHandle& got = f_.index_handle();
  EXPECT_EQ(got.offset(), kOffset);
  EXPECT_EQ(got.size(),   kSize);
}

// [Behavior] The returned reference should be stable across calls
// (i.e., not a reference to a temporary).
TEST_F(FooterIndexHandleTest_394, ReturnsStableReference_394) {
  BlockHandle h;
  h.set_offset(1);
  h.set_size(2);
  f_.set_index_handle(h);

  const BlockHandle* p1 = &f_.index_handle();
  const BlockHandle* p2 = &f_.index_handle();
  EXPECT_EQ(p1, p2);
}

// [Isolation] Mutating the source BlockHandle after set_index_handle()
// must not alter the Footer's stored (observable) handle values.
TEST_F(FooterIndexHandleTest_394, StoredHandleUnaffectedBySourceMutation_394) {
  BlockHandle src;
  src.set_offset(100);
  src.set_size(200);
  f_.set_index_handle(src);

  // Mutate the original after setting it on Footer.
  src.set_offset(999);
  src.set_size(888);

  const BlockHandle& got = f_.index_handle();
  EXPECT_EQ(got.offset(), 100u);
  EXPECT_EQ(got.size(),   200u);
}

// [Boundary] Large values should round-trip via the setter/getter without truncation.
TEST_F(FooterIndexHandleTest_394, LargeValuesRoundTrip_394) {
  BlockHandle h;
  const uint64_t kLargeOffset = static_cast<uint64_t>(1ULL << 60); // a very large offset
  const uint64_t kLargeSize   = static_cast<uint64_t>((1ULL << 40) + 1234);

  h.set_offset(kLargeOffset);
  h.set_size(kLargeSize);

  f_.set_index_handle(h);

  const BlockHandle& got = f_.index_handle();
  EXPECT_EQ(got.offset(), kLargeOffset);
  EXPECT_EQ(got.size(),   kLargeSize);
}

}  // namespace leveldb
