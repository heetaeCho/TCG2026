// StructElement_getAttributeMapEntry_1777_test.cc
#include <gtest/gtest.h>

#include <cstring>

// Include the implementation file to access the local static inline helper.
// This keeps the function as a black box (we do not re-implement it).
#include "poppler/StructElement.cc"

namespace {

class GetAttributeMapEntryTest_1777 : public ::testing::Test {
protected:
  static AttributeMapEntry MakeEntry(Attribute::Type type, const char *name)
  {
    AttributeMapEntry e{};
    e.type = type;

    // AttributeMapEntry is known (from the implementation) to have a name field,
    // since getAttributeMapEntry dereferences entry->name.
    e.name = name;

    // Other fields are irrelevant for lookup; keep them neutral.
    e.defval = nullptr;
    e.inherit = false;
    e.check = nullptr;
    return e;
  }

  static AttributeMapEntry MakeSentinel()
  {
    return MakeEntry(Attribute::Unknown, "sentinel");
  }
};

TEST_F(GetAttributeMapEntryTest_1777, FindsEntryInFirstList_1777)
{
  static AttributeMapEntry list1[] = {
      MakeEntry(Attribute::Type::String, "Alpha"),
      MakeEntry(Attribute::Type::Integer, "Beta"),
      MakeSentinel(),
  };
  static const AttributeMapEntry *entryLists[] = {list1, nullptr};

  const AttributeMapEntry *found = getAttributeMapEntry(entryLists, "Beta");
  ASSERT_NE(found, nullptr);
  EXPECT_STREQ(found->name, "Beta");
  EXPECT_EQ(found->type, Attribute::Type::Integer);
}

TEST_F(GetAttributeMapEntryTest_1777, FindsEntryInSecondListWhenNotInFirst_1777)
{
  static AttributeMapEntry list1[] = {
      MakeEntry(Attribute::Type::String, "Alpha"),
      MakeSentinel(),
  };
  static AttributeMapEntry list2[] = {
      MakeEntry(Attribute::Type::Integer, "Gamma"),
      MakeEntry(Attribute::Type::Boolean, "Delta"),
      MakeSentinel(),
  };
  static const AttributeMapEntry *entryLists[] = {list1, list2, nullptr};

  const AttributeMapEntry *found = getAttributeMapEntry(entryLists, "Delta");
  ASSERT_NE(found, nullptr);
  EXPECT_STREQ(found->name, "Delta");
  EXPECT_EQ(found->type, Attribute::Type::Boolean);
}

TEST_F(GetAttributeMapEntryTest_1777, ReturnsNullWhenNameNotFound_1777)
{
  static AttributeMapEntry list1[] = {
      MakeEntry(Attribute::Type::String, "Alpha"),
      MakeEntry(Attribute::Type::Integer, "Beta"),
      MakeSentinel(),
  };
  static const AttributeMapEntry *entryLists[] = {list1, nullptr};

  EXPECT_EQ(getAttributeMapEntry(entryLists, "DoesNotExist"), nullptr);
}

TEST_F(GetAttributeMapEntryTest_1777, ReturnsNullForEmptyEntryListArray_1777)
{
  // Boundary: entryLists contains only the required nullptr terminator.
  static const AttributeMapEntry *entryLists[] = {nullptr};

  EXPECT_EQ(getAttributeMapEntry(entryLists, "Anything"), nullptr);
}

TEST_F(GetAttributeMapEntryTest_1777, StopsAtUnknownSentinelWithinAList_1777)
{
  // Boundary: An entry after the Unknown sentinel should not be considered.
  static AttributeMapEntry list1[] = {
      MakeEntry(Attribute::Type::String, "Alpha"),
      MakeSentinel(),
      // If the function incorrectly continues past sentinel, it might find this.
      MakeEntry(Attribute::Type::Integer, "Hidden"),
      MakeSentinel(),
  };
  static const AttributeMapEntry *entryLists[] = {list1, nullptr};

  EXPECT_EQ(getAttributeMapEntry(entryLists, "Hidden"), nullptr);
}

#ifndef NDEBUG
TEST_F(GetAttributeMapEntryTest_1777, DeathOnNullEntryListPointer_1777)
{
  // Implementation asserts(entryList).
  EXPECT_DEATH_IF_SUPPORTED(getAttributeMapEntry(nullptr, "Alpha"), "");
}

TEST_F(GetAttributeMapEntryTest_1777, DeathOnNullEntryNameInList_1777)
{
  static AttributeMapEntry list1[] = {
      MakeEntry(Attribute::Type::String, nullptr), // assert(entry->name)
      MakeSentinel(),
  };
  static const AttributeMapEntry *entryLists[] = {list1, nullptr};

  EXPECT_DEATH_IF_SUPPORTED(getAttributeMapEntry(entryLists, "Alpha"), "");
}
#endif

} // namespace