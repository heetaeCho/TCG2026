// File: table/footer_set_metaindex_handle_test.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <limits>
#include "table/format.h"

using leveldb::BlockHandle;
using leveldb::Footer;

namespace {

// Verifies that setting the metaindex handle stores the same observable values
// accessible through the public getters.
TEST(FooterTest_393, SetMetaindexStoresCopy_393) {
  Footer f;
  BlockHandle h;
  h.set_offset(123u);
  h.set_size(456u);

  f.set_metaindex_handle(h);

  const BlockHandle& got = f.metaindex_handle();
  EXPECT_EQ(got.offset(), h.offset());
  EXPECT_EQ(got.size(), h.size());
}

// Verifies that setting the metaindex handle does not modify the index handle.
// We only compare against a freshly default-constructed BlockHandle via getters.
TEST(FooterTest_393, SetMetaindexDoesNotAffectIndexHandle_393) {
  Footer f;
  BlockHandle before;  // default-constructed reference for comparison

  BlockHandle meta;
  meta.set_offset(10u);
  meta.set_size(20u);
  f.set_metaindex_handle(meta);

  const BlockHandle& idx = f.index_handle();
  EXPECT_EQ(idx.offset(), before.offset());
  EXPECT_EQ(idx.size(), before.size());
}

// Verifies that subsequent calls overwrite the previous metaindex handle value.
TEST(FooterTest_393, SetMetaindexOverwritesPreviousValue_393) {
  Footer f;

  BlockHandle first;
  first.set_offset(1u);
  first.set_size(2u);
  f.set_metaindex_handle(first);

  BlockHandle second;
  second.set_offset(100u);
  second.set_size(200u);
  f.set_metaindex_handle(second);

  const BlockHandle& got = f.metaindex_handle();
  EXPECT_EQ(got.offset(), second.offset());
  EXPECT_EQ(got.size(), second.size());
}

// Verifies that Footer stores a copy, not an alias: mutating the original
// BlockHandle after setting should not change the stored metaindex handle.
TEST(FooterTest_393, SetMetaindexCopiesNotAliases_393) {
  Footer f;

  BlockHandle source;
  source.set_offset(111u);
  source.set_size(222u);
  f.set_metaindex_handle(source);

  // Mutate the original after setting.
  source.set_offset(999u);
  source.set_size(888u);

  const BlockHandle& got = f.metaindex_handle();
  EXPECT_EQ(got.offset(), 111u);
  EXPECT_EQ(got.size(), 222u);
}

// Boundary values are accepted and observable through getters.
TEST(FooterTest_393, SetMetaindexAcceptsBoundaryValues_393) {
  Footer f;

  BlockHandle h;
  h.set_offset(0u);
  h.set_size(std::numeric_limits<uint64_t>::max());
  f.set_metaindex_handle(h);

  const BlockHandle& got = f.metaindex_handle();
  EXPECT_EQ(got.offset(), 0u);
  EXPECT_EQ(got.size(), std::numeric_limits<uint64_t>::max());
}

}  // namespace
