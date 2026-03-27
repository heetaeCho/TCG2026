// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdatum_copy_ctor_2164.cpp
//
// Unit tests for Exiv2::Exifdatum copy-constructor deep-copy behavior (black-box).
// TEST_ID: 2164

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>
#include <exiv2/tags.hpp>

#include <atomic>
#include <memory>
#include <string>

namespace {

// A small test-double for Exiv2::Value that lets us observe cloning and state changes
// through the public Value interface.
//
// NOTE: This is a collaborator/test double, not a re-implementation of Exifdatum.
class CloneCountingValue final : public Exiv2::Value {
 public:
  static std::atomic<int> clone_calls;

  explicit CloneCountingValue(Exiv2::TypeId typeId, std::string payload)
      : Exiv2::Value(typeId), payload_(std::move(payload)) {}

  // Make the "string value" observable.
  std::string toString() const override { return payload_; }
  std::string toString(size_t /*n*/) const override { return payload_; }

  // Allow Exifdatum::setValue(std::string) to update us if it delegates to Value::read(std::string).
  int read(const std::string& buf) override {
    payload_ = buf;
    return 0;  // success (observable only by changed toString())
  }

 private:
  const Exiv2::Value* clone_() override {
    ++clone_calls;
    return new CloneCountingValue(*this);
  }

  std::string payload_;
};

std::atomic<int> CloneCountingValue::clone_calls{0};

class ExifdatumCopyCtorTest_2164 : public ::testing::Test {
 protected:
  void SetUp() override { CloneCountingValue::clone_calls = 0; }

  static Exiv2::ExifKey MakeKey1() { return Exiv2::ExifKey("Exif.Image.Make"); }
  static Exiv2::ExifKey MakeKey2() { return Exiv2::ExifKey("Exif.Image.Model"); }
};

}  // namespace

TEST_F(ExifdatumCopyCtorTest_2164, CopyCtorClonesValue_2164) {
  const auto key = MakeKey1();

  // Use a TypeId that exists in Exiv2. "asciiString" is a commonly available one in Exiv2.
  // If your build uses different enum names, adjust accordingly.
  CloneCountingValue v(Exiv2::asciiString, "original");

  const Exiv2::Exifdatum d1(key, &v);
  const int clones_after_construct = CloneCountingValue::clone_calls.load();

  const Exiv2::Exifdatum d2(d1);

  // The copy-ctor in the provided snippet calls rhs.value_->clone() when rhs.value_ is non-null.
  EXPECT_GT(CloneCountingValue::clone_calls.load(), clones_after_construct);

  // Also check we can observe the copied content through the public API.
  EXPECT_EQ(d1.toString(), d2.toString());
}

TEST_F(ExifdatumCopyCtorTest_2164, CopyCtorDoesNotShareValueState_2164) {
  const auto key = MakeKey1();
  CloneCountingValue v(Exiv2::asciiString, "before");

  Exiv2::Exifdatum d1(key, &v);
  Exiv2::Exifdatum d2(d1);

  // Mutate only d1 through public interface.
  // We do NOT assume internal behavior beyond observable output:
  // if Exifdatum delegates to Value::read(string), d1 should change and d2 should not.
  const int rc = d1.setValue(std::string("after"));

  // Regardless of rc, d2 should remain a stable, independent copy of the original state.
  // If rc==0, we additionally expect d1 changed.
  if (rc == 0) {
    EXPECT_EQ(d1.toString(), "after");
  }
  EXPECT_EQ(d2.toString(), "before");
}

TEST_F(ExifdatumCopyCtorTest_2164, CopyCtorDoesNotShareKeyAfterRhsReassigned_2164) {
  // This verifies key deep-copy indirectly:
  // If the key were shared, changing d1's key via assignment from a different Exifdatum
  // could affect d2's key() as well. We only rely on public methods.
  CloneCountingValue v1(Exiv2::asciiString, "v1");
  CloneCountingValue v2(Exiv2::asciiString, "v2");

  Exiv2::Exifdatum d1(MakeKey1(), &v1);
  Exiv2::Exifdatum d2(d1);

  const std::string d2_key_before = d2.key();
  const std::string d2_group_before = d2.groupName();
  const auto d2_tag_before = d2.tag();

  // Reassign d1 from another datum with a different key.
  Exiv2::Exifdatum other(MakeKey2(), &v2);
  d1 = other;

  // d2 should remain the same as it was (independent copy).
  EXPECT_EQ(d2.key(), d2_key_before);
  EXPECT_EQ(d2.groupName(), d2_group_before);
  EXPECT_EQ(d2.tag(), d2_tag_before);
}

TEST_F(ExifdatumCopyCtorTest_2164, CopyCtorWithNullValueIsSafeAndIndependent_2164) {
  // Construct with a null value pointer (observable via getValue()).
  Exiv2::Exifdatum d1(MakeKey1(), nullptr);

  // Sanity: key-related calls should still be valid.
  EXPECT_FALSE(d1.key().empty());
  (void)d1.tag();  // should not crash

  Exiv2::Exifdatum d2(d1);

  // Both should report "no value" via the public getValue() API.
  auto v1 = d1.getValue();
  auto v2 = d2.getValue();
  EXPECT_FALSE(v1);
  EXPECT_FALSE(v2);

  // Changing d1 afterward (setting a value) should not retroactively give d2 a value.
  const int rc = d1.setValue(std::string("now-has-value"));
  (void)rc;

  auto v2_after = d2.getValue();
  EXPECT_FALSE(v2_after);
}

TEST_F(ExifdatumCopyCtorTest_2164, CopyCtorBoundary_KeyIndexDoesNotBleedAcrossCopies_2164) {
  // Boundary-ish: exercise ExifKey index behavior through Exifdatum::idx()
  // and ensure the copy remains stable after changing the original via reassignment.
  CloneCountingValue v(Exiv2::asciiString, "x");

  Exiv2::ExifKey k1 = MakeKey1();
  k1.setIdx(0);
  Exiv2::Exifdatum d1(k1, &v);
  Exiv2::Exifdatum d2(d1);

  const int idx_before = d2.idx();

  // Create another datum with a different idx and assign to d1 only.
  Exiv2::ExifKey k2 = MakeKey1();
  k2.setIdx(123);
  Exiv2::Exifdatum d1_replacement(k2, &v);
  d1 = d1_replacement;

  // d2 should keep its original idx (independent key copy).
  EXPECT_EQ(d2.idx(), idx_before);
}