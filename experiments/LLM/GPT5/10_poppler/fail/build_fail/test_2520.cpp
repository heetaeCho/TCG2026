// File: poppler-structure-element-name-to-enum-test_2520.cc
//
// Unit tests for name_to_enum() in poppler-structure-element.cc
//
// Notes:
// - We treat the implementation as a black box and only test observable behavior:
//   * correct enum mapping for valid names
//   * process-abort behavior for nullptr / invalid names (g_assert / g_assert_not_reached)
// - We include the .cc to access the internal static template, as is common in Poppler unit tests.

#include <gtest/gtest.h>

#include <glib.h>

// Ensure we can build Object instances representing PDF Name objects.
#include "poppler/Object.h"

// Include the implementation unit to access the internal static template name_to_enum().
#include "glib/poppler-structure-element.cc"

namespace {

// A small test enum used only for instantiating name_to_enum<EnumType>().
enum class TestEnum_2520 {
  kAlpha = 1,
  kBeta = 2,
  kGamma = 3,
};

} // namespace

// Provide EnumNameValue<TestEnum_2520>::values mapping with a nullptr sentinel.
// This relies on EnumNameValue being defined in poppler-structure-element.cc (included above).
template <>
const EnumNameValue<TestEnum_2520> EnumNameValue<TestEnum_2520>::values[] = {
    {"Alpha", TestEnum_2520::kAlpha},
    {"Beta", TestEnum_2520::kBeta},
    {"Gamma", TestEnum_2520::kGamma},
    {nullptr, static_cast<TestEnum_2520>(0)} // sentinel
};

class NameToEnumTest_2520 : public ::testing::Test {
protected:
  // Helper to create a PDF "Name" Object.
  static Object MakeName(const char *name) {
    // Object has ctor: Object(ObjType typeA, const char *v)
    // For name objects, ObjType is expected to be objName.
    return Object(objName, name);
  }
};

TEST_F(NameToEnumTest_2520, ReturnsMappedValueForValidNames_2520) {
  Object alpha = MakeName("Alpha");
  Object beta = MakeName("Beta");
  Object gamma = MakeName("Gamma");

  EXPECT_EQ(name_to_enum<TestEnum_2520>(&alpha), TestEnum_2520::kAlpha);
  EXPECT_EQ(name_to_enum<TestEnum_2520>(&beta), TestEnum_2520::kBeta);
  EXPECT_EQ(name_to_enum<TestEnum_2520>(&gamma), TestEnum_2520::kGamma);
}

TEST_F(NameToEnumTest_2520, BoundaryFirstAndLastMapping_2520) {
  Object first = MakeName("Alpha");
  Object last = MakeName("Gamma");

  EXPECT_EQ(name_to_enum<TestEnum_2520>(&first), TestEnum_2520::kAlpha);
  EXPECT_EQ(name_to_enum<TestEnum_2520>(&last), TestEnum_2520::kGamma);
}

TEST_F(NameToEnumTest_2520, DeathOnNullptrNameValue_2520) {
  // g_assert(name_value != nullptr) should abort the process.
  EXPECT_DEATH(
      {
        (void)name_to_enum<TestEnum_2520>(nullptr);
      },
      ".*");
}

TEST_F(NameToEnumTest_2520, DeathOnInvalidNameValue_2520) {
  // A valid-looking Name object, but not present in the mapping => g_assert_not_reached().
  Object unknown = MakeName("NotInMapping");

  EXPECT_DEATH(
      {
        (void)name_to_enum<TestEnum_2520>(&unknown);
      },
      ".*");
}

TEST_F(NameToEnumTest_2520, DeathWhenObjectIsNotAName_2520) {
  // Construct a non-Name Object; isName(item->name) should never match, causing g_assert_not_reached().
  Object not_a_name(std::string("Alpha"));

  EXPECT_DEATH(
      {
        (void)name_to_enum<TestEnum_2520>(&not_a_name);
      },
      ".*");
}