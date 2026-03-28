// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 2161
//
// Unit tests for Exiv2::Iptcdatum copy-constructor behavior (black-box).
//
// Constraints honored:
// - No re-implementation / inference of internal logic beyond observable effects.
// - Tests only use public interface.
// - No private state access.
// - Focus on normal, boundary, and observable error-ish cases.

#include <gtest/gtest.h>

#include <exiv2/datasets.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <memory>
#include <string>
#include <utility>

namespace {

class IptcdatumCopyCtorTest_2161 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::Value> MakeAsciiValue(const std::string& s) {
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    EXPECT_NE(v, nullptr);
    if (v) {
      // Public API: Value::read(string)
      (void)v->read(s);
    }
    return v;
  }

  static std::unique_ptr<Exiv2::Value> MakeUShortValue(uint16_t x) {
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    EXPECT_NE(v, nullptr);
    if (v) {
      // Public API: Value::read(string) exists; avoid assuming binary layout.
      (void)v->read(std::to_string(x));
    }
    return v;
  }
};

TEST_F(IptcdatumCopyCtorTest_2161, CopyCtor_PreservesKeyAndValueString_2161) {
  Exiv2::IptcKey key(/*tag=*/5, /*record=*/2);
  auto v = MakeAsciiValue("hello");

  Exiv2::Iptcdatum original(key, v.get());
  Exiv2::Iptcdatum copy(original);

  EXPECT_EQ(copy.key(), original.key());
  EXPECT_EQ(copy.familyName(), original.familyName());
  EXPECT_EQ(copy.groupName(), original.groupName());
  EXPECT_EQ(copy.tag(), original.tag());
  EXPECT_EQ(copy.record(), original.record());

  // Observable: value-related formatting.
  EXPECT_EQ(copy.toString(), original.toString());
  EXPECT_EQ(copy.toString(), std::string("hello"));
}

TEST_F(IptcdatumCopyCtorTest_2161, CopyCtor_DeepCopiesValue_ChangesToOriginalDoNotAffectCopy_2161) {
  Exiv2::IptcKey key(/*tag=*/7, /*record=*/2);
  auto v = MakeAsciiValue("before");

  Exiv2::Iptcdatum original(key, v.get());
  Exiv2::Iptcdatum copy(original);

  // Mutate original through public API.
  (void)original.setValue(std::string("after"));

  // Copy should remain unchanged if it truly owns a deep copy.
  EXPECT_EQ(copy.toString(), std::string("before"));

  // Sanity: original should reflect update (observable).
  EXPECT_EQ(original.toString(), std::string("after"));
}

TEST_F(IptcdatumCopyCtorTest_2161, CopyCtor_CopyRemainsValidAfterOriginalDestroyed_2161) {
  Exiv2::IptcKey key(/*tag=*/10, /*record=*/2);

  Exiv2::Iptcdatum copy = [&]() {
    auto v = MakeAsciiValue("scoped");
    Exiv2::Iptcdatum original(key, v.get());
    Exiv2::Iptcdatum localCopy(original);

    // Verify inside scope
    EXPECT_EQ(localCopy.key(), original.key());
    EXPECT_EQ(localCopy.toString(), std::string("scoped"));
    return localCopy;  // copy-construct / NRVO
  }();

  // After original is destroyed, copy should still be usable (key/value must not dangle).
  EXPECT_EQ(copy.key(), key.key());
  EXPECT_EQ(copy.tag(), key.tag());
  EXPECT_EQ(copy.record(), key.record());
  EXPECT_EQ(copy.toString(), std::string("scoped"));
}

TEST_F(IptcdatumCopyCtorTest_2161, CopyCtor_WithNullValuePointer_DoesNotThrowAndKeyAccessible_2161) {
  Exiv2::IptcKey key(/*tag=*/1, /*record=*/2);

  Exiv2::Iptcdatum original(key, /*pValue=*/nullptr);
  EXPECT_NO_THROW({
    Exiv2::Iptcdatum copy(original);
    EXPECT_EQ(copy.key(), original.key());
    EXPECT_EQ(copy.tag(), original.tag());
    EXPECT_EQ(copy.record(), original.record());

    // We avoid asserting specifics of value() / toString() when value is absent,
    // but we can safely probe getValue() without assuming semantics.
    auto gv = copy.getValue();
    // Either nullptr or a valid Value, but must not crash.
    (void)gv;
  });
}

TEST_F(IptcdatumCopyCtorTest_2161, CopyCtor_IndependentGetValueClones_DoNotAliasReturnedPointers_2161) {
  Exiv2::IptcKey key(/*tag=*/12, /*record=*/2);
  auto v = MakeUShortValue(42);

  Exiv2::Iptcdatum original(key, v.get());
  Exiv2::Iptcdatum copy(original);

  // getValue() is an observable API: it returns a unique_ptr. We can check independence of returned objects.
  auto ov = original.getValue();
  auto cv = copy.getValue();

  // We don't assume either is always non-null, but if both exist, they must be distinct objects.
  if (ov && cv) {
    EXPECT_NE(ov.get(), cv.get());
    // And their observable content should match initially.
    EXPECT_EQ(ov->toString(), cv->toString());
  }
}

}  // namespace