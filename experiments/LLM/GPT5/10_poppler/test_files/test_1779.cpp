// StructElement_getOwnerMapEntry_tests_1779.cc
#include <gtest/gtest.h>

#include <cstddef>
#include <utility>

// NOTE:
// getOwnerMapEntry() is a static inline function in StructElement.cc (not exposed via a header).
// To test the provided interface directly, we include the implementation file so the function is
// available in this translation unit.
#include "StructElement.cc"

namespace {

TEST(GetOwnerMapEntryTest_1779, KnownNameReturnsNonNullAndExpectedOwner_1779)
{
  const OwnerMapEntry *e = getOwnerMapEntry("XML-1.00");
  ASSERT_NE(e, nullptr);
  EXPECT_EQ(e->owner, Attribute::XML_1_00);

  e = getOwnerMapEntry("HTML-4.01");
  ASSERT_NE(e, nullptr);
  EXPECT_EQ(e->owner, Attribute::HTML_4_01);

  e = getOwnerMapEntry("UserProperties");
  ASSERT_NE(e, nullptr);
  EXPECT_EQ(e->owner, Attribute::UserProperties);
}

TEST(GetOwnerMapEntryTest_1779, AllKnownOwnerMapNamesResolve_1779)
{
  const std::pair<const char *, Attribute::Owner> kCases[] = {
      {"XML-1.00", Attribute::XML_1_00},
      {"HTML-3.20", Attribute::HTML_3_20},
      {"HTML-4.01", Attribute::HTML_4_01},
      {"OEB-1.00", Attribute::OEB_1_00},
      {"RTF-1.05", Attribute::RTF_1_05},
      {"CSS-1.00", Attribute::CSS_1_00},
      {"CSS-2.00", Attribute::CSS_2_00},
      {"Layout", Attribute::Layout},
      {"PrintField", Attribute::PrintField},
      {"Table", Attribute::Table},
      {"List", Attribute::List},
      {"UserProperties", Attribute::UserProperties},
  };

  for (const auto &tc : kCases) {
    const OwnerMapEntry *e = getOwnerMapEntry(tc.first);
    ASSERT_NE(e, nullptr) << "Expected non-null for name: " << tc.first;
    EXPECT_EQ(e->owner, tc.second) << "Unexpected owner for name: " << tc.first;
  }
}

TEST(GetOwnerMapEntryTest_1779, UnknownNameReturnsNull_1779)
{
  EXPECT_EQ(getOwnerMapEntry("NotARealOwner"), nullptr);
  EXPECT_EQ(getOwnerMapEntry("XML-1.01"), nullptr);
  EXPECT_EQ(getOwnerMapEntry("HTML-4.0"), nullptr);
}

TEST(GetOwnerMapEntryTest_1779, EmptyStringReturnsNull_1779)
{
  EXPECT_EQ(getOwnerMapEntry(""), nullptr);
}

TEST(GetOwnerMapEntryTest_1779, CaseSensitivityIsObservable_1779)
{
  // Provided names are case-sensitive strings (e.g., "Layout", "Table").
  EXPECT_EQ(getOwnerMapEntry("layout"), nullptr);
  EXPECT_EQ(getOwnerMapEntry("TABLE"), nullptr);

  const OwnerMapEntry *e = getOwnerMapEntry("Layout");
  ASSERT_NE(e, nullptr);
  EXPECT_EQ(e->owner, Attribute::Layout);
}

TEST(GetOwnerMapEntryTest_1779, SameNameReturnsSameEntryAddress_1779)
{
  const OwnerMapEntry *e1 = getOwnerMapEntry("Table");
  const OwnerMapEntry *e2 = getOwnerMapEntry("Table");
  ASSERT_NE(e1, nullptr);
  ASSERT_NE(e2, nullptr);

  // Since the function returns a pointer to an entry, repeated calls should be consistent.
  EXPECT_EQ(e1, e2);
}

TEST(GetOwnerMapEntryTest_1779, DifferentNamesReturnDifferentEntryAddressesWhenBothFound_1779)
{
  const OwnerMapEntry *a = getOwnerMapEntry("CSS-1.00");
  const OwnerMapEntry *b = getOwnerMapEntry("CSS-2.00");
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  EXPECT_NE(a, b);
}

} // namespace