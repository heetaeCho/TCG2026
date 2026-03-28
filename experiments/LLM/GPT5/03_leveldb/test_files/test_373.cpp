// File: filter_block_builder_finish_test_373.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "table/filter_block.h"         // FilterBlockBuilder
#include "leveldb/slice.h"              // leveldb::Slice
#include "leveldb/filter_policy.h"      // leveldb::FilterPolicy

// kFilterBaseLg is defined in table/filter_block.cc; declare here for tests.
namespace leveldb { extern const size_t kFilterBaseLg; }

using ::testing::_;
using ::testing::Invoke;
using ::testing::AtLeast;

namespace {

// Simple Google Mock for FilterPolicy (external collaborator).
class MockFilterPolicy : public leveldb::FilterPolicy {
 public:
  // Provide a concrete Name() to avoid matching issues with const char*.
  const char* Name() const override { return "mock"; }

  MOCK_METHOD(void, CreateFilter,
              (const leveldb::Slice* keys, int n, std::string* dst),
              (const, override));

  MOCK_METHOD(bool, KeyMayMatch,
              (const leveldb::Slice& key, const leveldb::Slice& filter),
              (const, override));
};

class FilterBlockBuilderTest_373 : public ::testing::Test { };

}  // namespace

// Verifies Finish() layout on the simplest path: no keys added.
// Observable expectations (black-box):
//  - Result has 4 bytes of array offset followed by a single encoding byte.
//  - With no keys, array offset should be 0 (since nothing preceded the footer).
//  - The last byte equals kFilterBaseLg.
TEST_F(FilterBlockBuilderTest_373, Finish_NoKeys_WritesArrayOffsetAndParam_373) {
  // Policy is not consulted when there are no keys; nullptr is acceptable.
  leveldb::FilterBlockBuilder builder(/*policy=*/nullptr);

  leveldb::Slice out = builder.Finish();
  ASSERT_EQ(out.size(), 5u) << "Expected 4-byte array offset + 1-byte param";

  const unsigned char* bytes =
      reinterpret_cast<const unsigned char*>(out.data());

  // Little-endian 32-bit array offset should be zero.
  EXPECT_EQ(bytes[0], 0u);
  EXPECT_EQ(bytes[1], 0u);
  EXPECT_EQ(bytes[2], 0u);
  EXPECT_EQ(bytes[3], 0u);

  // Encoding parameter (last byte) should equal kFilterBaseLg.
  EXPECT_EQ(static_cast<size_t>(bytes[4]), leveldb::kFilterBaseLg);
}

// Verifies that if at least one key is added, Finish() triggers filter
// generation via the external FilterPolicy and still appends the expected
// footer (array offset + encoding param).
// We DO NOT assert the internal encoding; we only:
//  - check that CreateFilter() is invoked (external interaction);
//  - validate the last byte equals kFilterBaseLg;
//  - validate the stored array offset points somewhere within the slice;
//  - (optionally) ensure whatever the policy wrote appears before the footer.
TEST_F(FilterBlockBuilderTest_373, Finish_WithKey_InvokesPolicyAndWritesFooter_373) {
  MockFilterPolicy policy;

  // When GenerateFilter() runs, it will call policy.CreateFilter(...).
  // Append a recognizable byte sequence so we can observe it in the result.
  EXPECT_CALL(policy, CreateFilter(_, _, _))
      .Times(AtLeast(1))
      .WillRepeatedly(Invoke([](const leveldb::Slice* /*keys*/, int /*n*/,
                                std::string* dst) {
        dst->append("XMOCK");  // recognizable payload
      }));

  leveldb::FilterBlockBuilder builder(&policy);

  // Adding any key should make the builder have pending data,
  // causing Finish() to generate at least one filter.
  builder.AddKey(leveldb::Slice("a"));

  leveldb::Slice out = builder.Finish();
  ASSERT_GE(out.size(), 5u) << "Footer requires at least 5 bytes";

  const unsigned char* bytes =
      reinterpret_cast<const unsigned char*>(out.data());

  // Last byte equals kFilterBaseLg (encoding parameter).
  EXPECT_EQ(static_cast<size_t>(bytes[out.size() - 1]), leveldb::kFilterBaseLg);

  // Decode little-endian 32-bit array offset stored just before the last byte.
  uint32_t array_offset =
      static_cast<uint32_t>(bytes[out.size() - 5]) |
      (static_cast<uint32_t>(bytes[out.size() - 4]) << 8) |
      (static_cast<uint32_t>(bytes[out.size() - 3]) << 16) |
      (static_cast<uint32_t>(bytes[out.size() - 2]) << 24);

  // The array offset must point within the slice and not into the 5-byte footer.
  ASSERT_LE(array_offset, out.size() - 5)
      << "Array offset must point before the 4-byte offset table + 1-byte param";

  // Optional observable check: the policy's appended data should appear
  // somewhere before the 5-byte footer. We don't assert exact placement.
  const std::string payload(out.data(), out.size());
  const std::string needle = "XMOCK";
  const size_t pos = payload.find(needle);
  EXPECT_NE(pos, std::string::npos);
  if (pos != std::string::npos) {
    EXPECT_LT(pos, out.size() - 5) << "Policy payload should precede footer";
  }
}
