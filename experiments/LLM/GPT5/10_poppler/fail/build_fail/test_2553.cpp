// File: poppler-structure-element-convert-border-style-test_2553.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

// Include Poppler public headers for the enum + GType.
#include <poppler.h>

// Include Poppler core Object API used by convert_border_style().
#include "poppler/Object.h"

// Include the .cc directly so we can test the file-local static function.
#include "./TestProjects/poppler/glib/poppler-structure-element.cc"

namespace {

class ConvertBorderStyleTest_2553 : public ::testing::Test {
protected:
  void SetUp() override {
    // Needed for reliable EXPECT_DEATH with GLib assertions.
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
  }

  static std::vector<std::string> FirstNicks_4() {
    std::vector<std::string> out;

    // POPPLER_TYPE_STRUCTURE_BORDER_STYLE should exist as PopplerStructureBorderStyle is a public enum.
    GType t = POPPLER_TYPE_STRUCTURE_BORDER_STYLE;
    ASSERT_NE(t, G_TYPE_INVALID);

    auto *klass = static_cast<GEnumClass *>(g_type_class_ref(t));
    ASSERT_NE(klass, nullptr);

    // Collect distinct nicks (skip any null pointers).
    for (int i = 0; klass->values[i].value_name != nullptr; ++i) {
      const char *nick = klass->values[i].value_nick;
      if (nick && *nick) {
        out.emplace_back(nick);
      }
      if (out.size() >= 4) {
        break;
      }
    }

    g_type_class_unref(klass);

    // If for some reason we couldn't extract 4 (should not happen), pad with duplicates.
    while (out.size() < 4 && !out.empty()) {
      out.push_back(out.back());
    }
    return out;
  }

  static Object MakeNameObject(const std::string &nick) {
    // Object has a (ObjType, string_view) constructor; use objName.
    return Object(objName, std::string_view(nick));
  }

  static Object MakeArrayObjectWithN(size_t n) {
    // Build an Array through Object::arrayAdd, which requires an actual array Object.
    // In Poppler core, Array is constructed with an XRef*; commonly nullptr is accepted.
    auto *arr = new Array(nullptr);
    Object arrObj(arr);

    auto nicks = FirstNicks_4();
    for (size_t i = 0; i < n; ++i) {
      Object elem = MakeNameObject(nicks[i % nicks.size()]);
      arrObj.arrayAdd(std::move(elem));
    }
    return arrObj;
  }
};

TEST_F(ConvertBorderStyleTest_2553, NullObjectAsserts_2553) {
  PopplerStructureBorderStyle values[4] = {};
  EXPECT_DEATH(convert_border_style(nullptr, values), ".*");
}

TEST_F(ConvertBorderStyleTest_2553, NullValuesAsserts_2553) {
  Object obj = MakeNameObject(FirstNicks_4().front());
  EXPECT_DEATH(convert_border_style(&obj, nullptr), ".*");
}

TEST_F(ConvertBorderStyleTest_2553, ArrayLengthNotFourAsserts_2553) {
  // The implementation asserts arrayGetLength() == 4.
  Object arrObj = MakeArrayObjectWithN(3);
  PopplerStructureBorderStyle values[4] = {};
  EXPECT_DEATH(convert_border_style(&arrObj, values), ".*");
}

TEST_F(ConvertBorderStyleTest_2553, NonArraySetsAllSidesToSameValue_2553) {
  auto nicks = FirstNicks_4();
  ASSERT_FALSE(nicks.empty());

  Object obj = MakeNameObject(nicks[0]);

  PopplerStructureBorderStyle values[4] = {
      POPPLER_STRUCTURE_BORDER_STYLE_OUTSET,
      POPPLER_STRUCTURE_BORDER_STYLE_INSET,
      POPPLER_STRUCTURE_BORDER_STYLE_DOUBLE,
      POPPLER_STRUCTURE_BORDER_STYLE_SOLID,
  };

  convert_border_style(&obj, values);

  // Observable behavior: all four outputs match name_to_enum applied to the input object.
  PopplerStructureBorderStyle expected = name_to_enum<PopplerStructureBorderStyle>(&obj);

  EXPECT_EQ(values[0], expected);
  EXPECT_EQ(values[1], expected);
  EXPECT_EQ(values[2], expected);
  EXPECT_EQ(values[3], expected);

  // And they are all equal to each other.
  EXPECT_EQ(values[0], values[1]);
  EXPECT_EQ(values[1], values[2]);
  EXPECT_EQ(values[2], values[3]);
}

TEST_F(ConvertBorderStyleTest_2553, ArrayMapsEachOfFourEntriesIndependently_2553) {
  auto nicks = FirstNicks_4();
  ASSERT_GE(nicks.size(), 4u);

  auto *arr = new Array(nullptr);
  Object arrObj(arr);

  // Add four potentially-distinct enum nicks.
  arrObj.arrayAdd(MakeNameObject(nicks[0]));
  arrObj.arrayAdd(MakeNameObject(nicks[1]));
  arrObj.arrayAdd(MakeNameObject(nicks[2]));
  arrObj.arrayAdd(MakeNameObject(nicks[3]));

  ASSERT_EQ(arrObj.arrayGetLength(), 4);

  PopplerStructureBorderStyle values[4] = {
      POPPLER_STRUCTURE_BORDER_STYLE_NONE,
      POPPLER_STRUCTURE_BORDER_STYLE_NONE,
      POPPLER_STRUCTURE_BORDER_STYLE_NONE,
      POPPLER_STRUCTURE_BORDER_STYLE_NONE,
  };

  convert_border_style(&arrObj, values);

  // Observable behavior: each output corresponds to name_to_enum on the respective array entry.
  for (int i = 0; i < 4; ++i) {
    Object item = arrObj.arrayGet(i);
    PopplerStructureBorderStyle expected = name_to_enum<PopplerStructureBorderStyle>(&item);
    EXPECT_EQ(values[i], expected) << "index=" << i;
  }
}

} // namespace