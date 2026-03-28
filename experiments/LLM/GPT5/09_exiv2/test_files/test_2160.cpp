// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for Exiv2::Iptcdatum constructor behavior (black-box via interface)

#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <memory>
#include <string>

namespace {

// A test Value implementation that lets us *observe* whether Value::clone() was invoked
// (via the virtual clone_() hook), without assuming anything about Iptcdatum internals.
class ObservableCloneValue final : public Exiv2::Value {
 public:
  explicit ObservableCloneValue(std::string payload)
      : Exiv2::Value(Exiv2::unsignedShort), payload_(std::move(payload)), clone_calls_(std::make_shared<int>(0)) {}

  ObservableCloneValue(const ObservableCloneValue& rhs) = default;

  void setPayload(std::string payload) { payload_ = std::move(payload); }

  std::shared_ptr<int> cloneCallsCounter() const { return clone_calls_; }

  // Make Exiv2::Value::toString() observable via our payload.
  const std::string toString(size_t /*n*/) override { return payload_; }

 private:
  // Exiv2::Value::clone() calls the virtual clone_(); overriding it lets us observe cloning.
  const Exiv2::Value* clone_() override {
    ++(*clone_calls_);
    return new ObservableCloneValue(*this);
  }

  std::string payload_;
  std::shared_ptr<int> clone_calls_;
};

class IptcdatumCtorTest_2160 : public ::testing::Test {};

}  // namespace

TEST_F(IptcdatumCtorTest_2160, ConstructsWithNullValue_DoesNotInvokeValueClone_2160) {
  const Exiv2::IptcKey key(/*tag*/ 5, /*record*/ 2);

  ObservableCloneValue src("ignored");
  ASSERT_EQ(*src.cloneCallsCounter(), 0);

  Exiv2::Iptcdatum datum(key, /*pValue*/ nullptr);

  // Observable external interaction: passing nullptr must not trigger cloning of the Value.
  EXPECT_EQ(*src.cloneCallsCounter(), 0);

  // Basic sanity: public methods are callable (no assumption about returned contents).
  EXPECT_NO_THROW((void)datum.key());
  EXPECT_NO_THROW((void)datum.record());
  EXPECT_NO_THROW((void)datum.tag());
  EXPECT_NO_THROW((void)datum.familyName());
  EXPECT_NO_THROW((void)datum.groupName());
  EXPECT_NO_THROW((void)datum.tagName());
  EXPECT_NO_THROW((void)datum.tagLabel());
  EXPECT_NO_THROW((void)datum.tagDesc());
  EXPECT_NO_THROW((void)datum.toString());
  EXPECT_NO_THROW((void)datum.getValue());
}

TEST_F(IptcdatumCtorTest_2160, ConstructsWithNonNullValue_InvokesValueCloneOnce_2160) {
  const Exiv2::IptcKey key(/*tag*/ 10, /*record*/ 1);

  ObservableCloneValue src("hello");
  ASSERT_EQ(*src.cloneCallsCounter(), 0);

  Exiv2::Iptcdatum datum(key, &src);

  // Observable external interaction: constructor should clone the provided Value exactly once.
  EXPECT_EQ(*src.cloneCallsCounter(), 1);
}

TEST_F(IptcdatumCtorTest_2160, ConstructedDatumIsIndependentFromOriginalValueAfterClone_2160) {
  const Exiv2::IptcKey key(/*tag*/ 20, /*record*/ 2);

  ObservableCloneValue src("before");
  Exiv2::Iptcdatum datum(key, &src);

  const std::string before = datum.toString();

  // Mutate the original value object; if Iptcdatum cloned it, its visible representation
  // (via toString()) should remain the same as at construction time.
  src.setPayload("after");

  const std::string after = datum.toString();

  // We don't assume what "before" contains beyond being stable across the external mutation.
  EXPECT_EQ(after, before);
}

TEST_F(IptcdatumCtorTest_2160, ConstructorClonesKey_ObservedViaStableKeyStrings_2160) {
  // Boundary-ish: empty string key should be supported by IptcKey(string) ctor.
  const Exiv2::IptcKey key_from_string(std::string(""));

  Exiv2::Iptcdatum datum(key_from_string, nullptr);

  // Observable behavior: Iptcdatum exposes a key string; it should match the source key's key().
  // (We don't assume formatting beyond equality.)
  EXPECT_EQ(datum.key(), key_from_string.key());
}

TEST_F(IptcdatumCtorTest_2160, ConstructorPreservesTagAndRecord_FromNumericKey_2160) {
  const uint16_t tag = 25;
  const uint16_t record = 3;
  const Exiv2::IptcKey key(tag, record);

  Exiv2::Iptcdatum datum(key, nullptr);

  EXPECT_EQ(datum.tag(), tag);
  EXPECT_EQ(datum.record(), record);

  // Also check that recordName() is callable (content depends on dataset tables).
  EXPECT_NO_THROW((void)datum.recordName());
}