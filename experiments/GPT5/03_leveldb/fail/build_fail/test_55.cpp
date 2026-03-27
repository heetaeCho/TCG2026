// File: db/internal_key_comparator_compare_internalkey_test.cc

#include "db/dbformat.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

namespace leveldb {

// Minimal mock that lets us observe the slice-based Compare.
// We mock all virtuals to keep StrictMock happy, but only expect calls to Compare(Slice, Slice).
class MockInternalKeyComparator : public InternalKeyComparator {
 public:
  explicit MockInternalKeyComparator(const Comparator* c = nullptr)
      : InternalKeyComparator(c) {}

  MOCK_METHOD(const char*, Name, (), (const, override));
  MOCK_METHOD(int, Compare, (const Slice& a, const Slice& b), (const, override));
  MOCK_METHOD(void, FindShortestSeparator, (std::string* start, const Slice& limit),
              (const, override));
  MOCK_METHOD(void, FindShortSuccessor, (std::string* key), (const, override));
};

// Test fixture (kept simple in case future cases need common setup).
class InternalKeyComparatorTest_55 : public ::testing::Test {};


// Verifies that Compare(InternalKey, InternalKey) delegates to Compare(Slice, Slice)
// with slices obtained from a.Encode() and b.Encode(), and returns the slice-compare result.
TEST_F(InternalKeyComparatorTest_55, DelegatesToSliceCompare_AndPreservesOrder_55) {
  StrictMock<MockInternalKeyComparator> cmp(nullptr);

  // Two keys; we treat InternalKey as a black box and rely only on its public interface.
  InternalKey a;  // default-constructed; Encode() must be valid to call
  InternalKey b;

  // Capture the slices we expect to be forwarded.
  const Slice a_enc = a.Encode();
  const Slice b_enc = b.Encode();

  // Expect exactly one call to the slice-based Compare and check the forwarded arguments.
  EXPECT_CALL(cmp, Compare(_, _))
      .WillOnce([&](const Slice& lhs, const Slice& rhs) {
        // Verify argument order and identity against the encoded slices.
        EXPECT_EQ(lhs.data(), a_enc.data());
        EXPECT_EQ(lhs.size(), a_enc.size());
        EXPECT_EQ(rhs.data(), b_enc.data());
        EXPECT_EQ(rhs.size(), b_enc.size());
        return 0;  // arbitrary result to be propagated back
      });

  const int result = cmp.Compare(a, b);  // calls the inline overload under test
  EXPECT_EQ(result, 0);
}


// Verifies the result from Compare(InternalKey, InternalKey) exactly matches
// what the slice-based Compare returns (negative case).
TEST_F(InternalKeyComparatorTest_55, PropagatesNegativeReturnValue_55) {
  StrictMock<MockInternalKeyComparator> cmp(nullptr);
  InternalKey a;
  InternalKey b;

  EXPECT_CALL(cmp, Compare(_, _)).WillOnce(Return(-7));
  EXPECT_EQ(cmp.Compare(a, b), -7);
}


// Verifies zero is propagated unchanged.
TEST_F(InternalKeyComparatorTest_55, PropagatesZeroReturnValue_55) {
  StrictMock<MockInternalKeyComparator> cmp(nullptr);
  InternalKey a;
  InternalKey b;

  EXPECT_CALL(cmp, Compare(_, _)).WillOnce(Return(0));
  EXPECT_EQ(cmp.Compare(a, b), 0);
}


// Verifies positive values are propagated unchanged.
TEST_F(InternalKeyComparatorTest_55, PropagatesPositiveReturnValue_55) {
  StrictMock<MockInternalKeyComparator> cmp(nullptr);
  InternalKey a;
  InternalKey b;

  EXPECT_CALL(cmp, Compare(_, _)).WillOnce(Return(42));
  EXPECT_EQ(cmp.Compare(a, b), 42);
}

}  // namespace leveldb
