// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for ./TestProjects/exiv2/src/iptc.cpp (Iptcdatum::operator=)
// The TEST_ID is 686

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

#include "exiv2/iptc.hpp"
#include "exiv2/value.hpp"
#include "exiv2/datasets.hpp"

namespace {

// A small test double for Exiv2::Value to make cloning observable without relying on Exiv2 internals.
// This is an external collaborator passed into Iptcdatum via the public constructor interface.
class TestValue final : public Exiv2::Value {
 public:
  static inline int clone_calls = 0;

  explicit TestValue(std::string text)
      : Exiv2::Value(Exiv2::invalidTypeId), text_(std::move(text)) {}

  std::string text() const { return text_; }

  // Make the stored representation visible through the public interface used by Iptcdatum.
  const std::string toString(size_t /*n*/) override { return text_; }
  const std::ostream& write(std::ostream& os) override {
    os << text_;
    return os;
  }

 private:
  // Exiv2::Value::clone() calls clone_() virtually. Overriding is allowed even if clone_ is private
  // in the base (access control does not prevent overriding a virtual).
  const Exiv2::Value* clone_() override {
    ++clone_calls;
    return new TestValue(*this);
  }

  std::string text_;
};

// Helper: create an Iptcdatum with a stable key and a test value.
static Exiv2::Iptcdatum MakeDatum(uint16_t tag, uint16_t record, const std::string& text) {
  Exiv2::IptcKey key(tag, record);
  auto* v = new TestValue(text);  // Iptcdatum takes ownership via setValue/ctor in Exiv2.
  return Exiv2::Iptcdatum(key, v);
}

class IptcdatumTest_686 : public ::testing::Test {
 protected:
  void SetUp() override { TestValue::clone_calls = 0; }
};

TEST_F(IptcdatumTest_686, SelfAssignmentDoesNotCloneOrChangeObservableState_686) {
  auto d = MakeDatum(/*tag=*/5, /*record=*/2, "alpha");

  const std::string before_key = d.key();
  const std::string before_str = d.toString();

  d = d;  // self-assignment

  EXPECT_EQ(d.key(), before_key);
  EXPECT_EQ(d.toString(), before_str);
  EXPECT_EQ(TestValue::clone_calls, 0) << "Self-assignment should not deep-clone collaborators";
}

TEST_F(IptcdatumTest_686, AssignmentReturnsLhsReference_686) {
  auto lhs = MakeDatum(/*tag=*/10, /*record=*/1, "lhs");
  auto rhs = MakeDatum(/*tag=*/11, /*record=*/1, "rhs");

  Exiv2::Iptcdatum* ret = &(lhs = rhs);
  EXPECT_EQ(ret, &lhs);
}

TEST_F(IptcdatumTest_686, AssignmentCopiesKeyAndValueObservably_686) {
  auto lhs = MakeDatum(/*tag=*/20, /*record=*/2, "before");
  auto rhs = MakeDatum(/*tag=*/21, /*record=*/2, "after");

  const std::string rhs_key = rhs.key();
  const std::string rhs_str = rhs.toString();

  lhs = rhs;

  EXPECT_EQ(lhs.key(), rhs_key);
  EXPECT_EQ(lhs.toString(), rhs_str);

  // Deep copy should require cloning at least the value (and also the key in the provided snippet).
  EXPECT_GE(TestValue::clone_calls, 1);
}

TEST_F(IptcdatumTest_686, AssignmentDeepCopiesValueSoLaterRhsMutationDoesNotAffectLhs_686) {
  auto lhs = MakeDatum(/*tag=*/30, /*record=*/3, "lhs0");
  auto rhs = MakeDatum(/*tag=*/31, /*record=*/3, "rhs0");

  lhs = rhs;
  const std::string lhs_after_assign = lhs.toString();

  // Mutate rhs through its public interface (no assumptions about internal representation).
  rhs = std::string("rhs1");

  EXPECT_EQ(lhs.toString(), lhs_after_assign)
      << "lhs should remain independent after assignment (deep copy observable via toString())";
  EXPECT_NE(rhs.toString(), lhs.toString());
}

TEST_F(IptcdatumTest_686, AssignedObjectRemainsUsableAfterRhsDestroyed_686) {
  Exiv2::Iptcdatum lhs = MakeDatum(/*tag=*/40, /*record=*/4, "init");

  std::string expected_key;
  std::string expected_str;

  {
    auto rhs = MakeDatum(/*tag=*/41, /*record=*/4, "scoped");
    expected_key = rhs.key();
    expected_str = rhs.toString();

    lhs = rhs;
  }  // rhs destroyed here

  // If assignment performed a deep copy, lhs should still be usable and preserve rhs' observable data.
  EXPECT_EQ(lhs.key(), expected_key);
  EXPECT_EQ(lhs.toString(), expected_str);
}

TEST_F(IptcdatumTest_686, AssignmentFromDatumWithNullValueIsRobustIfConstructorAcceptsNull_686) {
  Exiv2::IptcKey keyA(50, 5);
  Exiv2::IptcKey keyB(51, 5);

  Exiv2::Iptcdatum lhs(keyA, new TestValue("non-null"));

  // Some Exiv2 constructors accept nullptr for Value; if not supported in this build, this test
  // will fail at construction time and should be adjusted alongside the production contract.
  Exiv2::Iptcdatum rhs(keyB, /*pValue=*/nullptr);

  EXPECT_NO_THROW(lhs = rhs);

  // Only check that public queries are safe to call; do not assume specific return values.
  EXPECT_NO_THROW((void)lhs.key());
  EXPECT_NO_THROW((void)lhs.toString());
  EXPECT_NO_THROW((void)lhs.size());
  EXPECT_NO_THROW((void)lhs.count());
  EXPECT_NO_THROW((void)lhs.getValue());
}

}  // namespace