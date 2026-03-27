// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for Exiv2::Iptcdatum::size()
// TEST_ID = 678

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>

#include <cstdint>
#include <string>

namespace {

// Helper: create a reasonable, commonly-valid IPTC key string.
// (We only rely on public construction of IptcKey via string.)
static Exiv2::IptcKey MakeKey_678() {
  return Exiv2::IptcKey("Iptc.Application2.ObjectName");
}

class IptcdatumTest_678 : public ::testing::Test {
 protected:
  Exiv2::IptcKey key_{MakeKey_678()};
};

}  // namespace

TEST_F(IptcdatumTest_678, SizeIsZeroWhenConstructedWithNullValue_678) {
  Exiv2::Iptcdatum d(key_, nullptr);
  EXPECT_EQ(d.size(), 0u);
}

TEST_F(IptcdatumTest_678, SizeBecomesNonZeroAfterSetValueNonEmptyString_678) {
  Exiv2::Iptcdatum d(key_, nullptr);
  const int rc = d.setValue(std::string("abc"));
  (void)rc;  // Return value is implementation-defined; don't assert it.
  EXPECT_GT(d.size(), 0u);
}

TEST_F(IptcdatumTest_678, SizeIsZeroAfterSetValueEmptyString_Boundary_678) {
  Exiv2::Iptcdatum d(key_, nullptr);
  const int rc = d.setValue(std::string(""));
  (void)rc;  // Return value is implementation-defined; don't assert it.
  EXPECT_EQ(d.size(), 0u);
}

TEST_F(IptcdatumTest_678, SizeIsZeroAfterSetValueNullPointer_Boundary_678) {
  Exiv2::Iptcdatum d(key_, nullptr);

  // First make it non-empty (so we can observe a change back to zero).
  (void)d.setValue(std::string("x"));
  ASSERT_GT(d.size(), 0u);

  // Now set null value pointer; behavior should be observable via size().
  d.setValue(nullptr);
  EXPECT_EQ(d.size(), 0u);
}

TEST_F(IptcdatumTest_678, CopyConstructorPreservesObservableSize_678) {
  Exiv2::Iptcdatum original(key_, nullptr);
  (void)original.setValue(std::string("hello"));
  ASSERT_GT(original.size(), 0u);

  Exiv2::Iptcdatum copy(original);
  EXPECT_EQ(copy.size(), original.size());
}

TEST_F(IptcdatumTest_678, CopyAssignmentPreservesObservableSize_678) {
  Exiv2::Iptcdatum a(key_, nullptr);
  Exiv2::Iptcdatum b(key_, nullptr);

  (void)a.setValue(std::string("hello"));
  ASSERT_GT(a.size(), 0u);

  (void)b.setValue(std::string(""));
  ASSERT_EQ(b.size(), 0u);

  b = a;
  EXPECT_EQ(b.size(), a.size());
}

TEST_F(IptcdatumTest_678, OperatorAssignStringUpdatesSize_678) {
  Exiv2::Iptcdatum d(key_, nullptr);
  ASSERT_EQ(d.size(), 0u);

  d = std::string("abc");
  EXPECT_GT(d.size(), 0u);

  d = std::string("");
  EXPECT_EQ(d.size(), 0u);
}

TEST_F(IptcdatumTest_678, OperatorAssignUint16UpdatesSize_NonZero_678) {
  Exiv2::Iptcdatum d(key_, nullptr);
  ASSERT_EQ(d.size(), 0u);

  d = static_cast<std::uint16_t>(0);
  // We don't assume exact encoding size; just that it stores something.
  EXPECT_GT(d.size(), 0u);
}