// table/footer_metaindex_handle_test.cc
#include "table/format.h"
#include "gtest/gtest.h"
#include <cstdint>
#include <limits>
#include <string>

namespace leveldb {

// NOTE: These tests rely ONLY on the public interface exposed by the headers:
// - Footer::set_metaindex_handle(const BlockHandle&)
// - Footer::metaindex_handle() const
// - (optionally) Footer::EncodeTo(std::string*) const
// - (optionally) Footer::DecodeFrom(Slice*)
// - BlockHandle's observable getters/setters (offset(), size(), set_offset(), set_size())
// No assumptions are made about internal state or implementation details.

class FooterMetaindexHandleTest_392 : public ::testing::Test {
protected:
  static BlockHandle MakeBH(uint64_t off, uint64_t sz) {
    BlockHandle h;
    // Using only observable setters
    h.set_offset(off);
    h.set_size(sz);
    return h;
  }
};

// [Normal operation] Setting a handle then reading it back should expose the same observable values.
TEST_F(FooterMetaindexHandleTest_392, GetterReturnsWhatWasSet_392) {
  Footer f;
  BlockHandle in = MakeBH(/*off=*/123, /*sz=*/456);
  f.set_metaindex_handle(in);

  const BlockHandle& out = f.metaindex_handle();
  EXPECT_EQ(out.offset(), 123u);
  EXPECT_EQ(out.size(), 456u);
}

// [Boundary] Zero values should be preserved.
TEST_F(FooterMetaindexHandleTest_392, PreservesZeroOffsetAndSize_392) {
  Footer f;
  BlockHandle in = MakeBH(/*off=*/0, /*sz=*/0);
  f.set_metaindex_handle(in);

  const BlockHandle& out = f.metaindex_handle();
  EXPECT_EQ(out.offset(), 0u);
  EXPECT_EQ(out.size(), 0u);
}

// [Boundary] Large values should be preserved (upper edge of uint64_t typical for BlockHandle).
TEST_F(FooterMetaindexHandleTest_392, PreservesLargeOffsetAndSize_392) {
  Footer f;
  const uint64_t kMax = std::numeric_limits<uint64_t>::max();
  // Use two large-but-different numbers to ensure both fields are verified.
  const uint64_t kOff = kMax - 1;
  const uint64_t kSize = kMax - 17;

  BlockHandle in = MakeBH(kOff, kSize);
  f.set_metaindex_handle(in);

  const BlockHandle& out = f.metaindex_handle();
  EXPECT_EQ(out.offset(), kOff);
  EXPECT_EQ(out.size(), kSize);
}

// [Isolation] Modifying the source BlockHandle after setting should not affect the Footer's stored value
// (i.e., setter should observe-by-value semantics from a caller's perspective).
TEST_F(FooterMetaindexHandleTest_392, SetterDoesNotAliasCallerObject_392) {
  Footer f;
  BlockHandle src = MakeBH(/*off=*/10, /*sz=*/20);
  f.set_metaindex_handle(src);

  // Mutate the source after setting it into Footer.
  src.set_offset(999);
  src.set_size(888);

  const BlockHandle& out = f.metaindex_handle();
  EXPECT_EQ(out.offset(), 10u);
  EXPECT_EQ(out.size(), 20u);
}

// [Round-trip] If Footer supports EncodeTo/DecodeFrom, a round-trip should preserve the handle.
// This validates externally observable serialization/deserialization behavior.
TEST_F(FooterMetaindexHandleTest_392, EncodeDecodeRoundTrip_PreservesMetaindex_392) {
  Footer original;
  BlockHandle in = MakeBH(/*off=*/777, /*sz=*/888);
  original.set_metaindex_handle(in);

  std::string encoded;
  original.EncodeTo(&encoded);

  Slice s(encoded);
  Footer decoded;
  ASSERT_TRUE(decoded.DecodeFrom(&s).ok());

  const BlockHandle& out = decoded.metaindex_handle();
  EXPECT_EQ(out.offset(), 777u);
  EXPECT_EQ(out.size(), 888u);
}

}  // namespace leveldb
