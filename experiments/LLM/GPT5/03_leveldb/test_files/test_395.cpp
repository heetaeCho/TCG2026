// File: table/footer_set_index_handle_test_395.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include "table/format.h"

namespace leveldb {

class FooterTest_395 : public ::testing::Test {
 protected:
  static BlockHandle MakeHandle(uint64_t offset, uint64_t size) {
    BlockHandle h;
    h.set_offset(offset);
    h.set_size(size);
    return h;
  }
};

// [Normal] Setting a typical handle is reflected via index_handle()
TEST_F(FooterTest_395, SetIndexHandleStoresValues_395) {
  Footer f;
  BlockHandle in = MakeHandle(/*offset=*/123u, /*size=*/456u);

  f.set_index_handle(in);

  const BlockHandle& out = f.index_handle();
  EXPECT_EQ(out.offset(), 123u);
  EXPECT_EQ(out.size(), 456u);
}

// [Boundary] Default-constructed BlockHandle is accepted and reflected
TEST_F(FooterTest_395, SetIndexHandleWithDefaultConstructedHandle_395) {
  Footer f;
  BlockHandle def;  // use as-is; compare only through public getters

  f.set_index_handle(def);

  const BlockHandle& out = f.index_handle();
  EXPECT_EQ(out.offset(), def.offset());
  EXPECT_EQ(out.size(), def.size());
}

// [Boundary] Extreme values (0 and max) round-trip via the public API
TEST_F(FooterTest_395, SetIndexHandleBoundaryValues_395) {
  Footer f;
  const uint64_t kZero = 0u;
  const uint64_t kMax  = std::numeric_limits<uint64_t>::max();

  BlockHandle in = MakeHandle(kZero, kMax);
  f.set_index_handle(in);

  const BlockHandle& out = f.index_handle();
  EXPECT_EQ(out.offset(), kZero);
  EXPECT_EQ(out.size(), kMax);
}

// [Isolation] Changing the original after set_index_handle() does not affect stored handle
TEST_F(FooterTest_395, SetIndexHandleStoresCopyNotAlias_395) {
  Footer f;
  BlockHandle source = MakeHandle(111u, 222u);
  f.set_index_handle(source);

  // Mutate the original object after setting
  source.set_offset(999u);
  source.set_size(888u);

  const BlockHandle& out = f.index_handle();
  EXPECT_EQ(out.offset(), 111u);
  EXPECT_EQ(out.size(), 222u);
}

// [Independence] set_metaindex_handle() does not change index_handle()
TEST_F(FooterTest_395, MetaindexChangesDoNotAffectIndexHandle_395) {
  Footer f;

  BlockHandle idx = MakeHandle(10u, 20u);
  f.set_index_handle(idx);

  BlockHandle meta = MakeHandle(30u, 40u);
  f.set_metaindex_handle(meta);

  const BlockHandle& out_idx = f.index_handle();
  EXPECT_EQ(out_idx.offset(), 10u);
  EXPECT_EQ(out_idx.size(), 20u);
}

}  // namespace leveldb
