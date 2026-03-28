// File: test_tags_int_print0x8298_1394.cpp
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "tags_int.hpp"   // Exiv2::Internal::print0x8298
#include "value.hpp"      // Exiv2::Value
#include "types.hpp"      // Exiv2::byte (if needed by factory helpers)

namespace {

// Helper: create an Exiv2::Value that, when toString() is called, yields `s`.
// We intentionally avoid relying on any particular internal Value type details.
// Try a few common Exiv2 string-ish value types. If your build only supports one,
// keep the one that compiles in your environment.
static std::unique_ptr<Exiv2::Value> MakeStringValue(const std::string& s) {
  // Prefer AsciiValue for EXIF-like strings, fallback to StringValue.
  // Both are public API types in Exiv2.
  try {
    auto v = std::unique_ptr<Exiv2::Value>(new Exiv2::AsciiValue);
    v->read(s);
    return v;
  } catch (...) {
    auto v = std::unique_ptr<Exiv2::Value>(new Exiv2::StringValue);
    v->read(s);
    return v;
  }
}

static std::string CallPrint(const Exiv2::Value& v) {
  std::ostringstream oss;
  // ExifData* is not used by the observable contract here; pass nullptr.
  Exiv2::Internal::print0x8298(oss, v, nullptr);
  return oss.str();
}

}  // namespace

// The TEST_ID is 1394

TEST(Print0x8298Test_1394, NoNullByte_PrintsWholeString_1394) {
  auto v = MakeStringValue("Alice");
  ASSERT_NE(v, nullptr);
  EXPECT_EQ(CallPrint(*v), "Alice");
}

TEST(Print0x8298Test_1394, EmptyString_PrintsEmpty_1394) {
  auto v = MakeStringValue("");
  ASSERT_NE(v, nullptr);
  EXPECT_EQ(CallPrint(*v), "");
}

TEST(Print0x8298Test_1394, EmbeddedNull_PhotographerAndEditor_PrintsWithCommaSpace_1394) {
  std::string s;
  s += "Alice";
  s.push_back('\0');
  s += "Bob";
  auto v = MakeStringValue(s);
  ASSERT_NE(v, nullptr);

  EXPECT_EQ(CallPrint(*v), "Alice, Bob");
}

TEST(Print0x8298Test_1394, EmbeddedNull_EditorEmpty_PrintsOnlyPhotographer_1394) {
  std::string s;
  s += "Alice";
  s.push_back('\0');
  // editor part empty
  auto v = MakeStringValue(s);
  ASSERT_NE(v, nullptr);

  EXPECT_EQ(CallPrint(*v), "Alice");
}

TEST(Print0x8298Test_1394, EmbeddedNull_PhotographerSingleSpace_EditorNonEmpty_PrintsOnlyEditorNoComma_1394) {
  std::string s;
  s += " ";
  s.push_back('\0');
  s += "EditorName";
  auto v = MakeStringValue(s);
  ASSERT_NE(v, nullptr);

  // Photographer is exactly " " -> should not be printed, and no ", " before editor.
  EXPECT_EQ(CallPrint(*v), "EditorName");
}

TEST(Print0x8298Test_1394, EmbeddedNull_PhotographerSingleSpace_EditorEmpty_PrintsEmpty_1394) {
  std::string s;
  s += " ";
  s.push_back('\0');
  // editor empty
  auto v = MakeStringValue(s);
  ASSERT_NE(v, nullptr);

  EXPECT_EQ(CallPrint(*v), "");
}

TEST(Print0x8298Test_1394, NullAtStart_PhotographerEmpty_EditorPresent_PrintsLeadingCommaSpaceThenEditor_1394) {
  // Boundary: NUL at position 0 => photographer == "" (not " "), editor == "Bob"
  std::string s;
  s.push_back('\0');
  s += "Bob";
  auto v = MakeStringValue(s);
  ASSERT_NE(v, nullptr);

  // Based on observable output contract from implementation:
  // photographer != " " so it attempts to print photographer (empty => prints nothing),
  // and since editor non-empty and photographer != " " it inserts ", " then editor.
  EXPECT_EQ(CallPrint(*v), ", Bob");
}

TEST(Print0x8298Test_1394, MultipleNulls_OnlySplitsOnFirstNull_RemainderPrintedAsEditorWithEmbeddedNull_1394) {
  // Boundary: multiple NULs, only first is split point.
  std::string s;
  s += "Alice";
  s.push_back('\0');
  s += "Bob";
  s.push_back('\0');
  s += "Carol";
  auto v = MakeStringValue(s);
  ASSERT_NE(v, nullptr);

  // Editor string is "Bob\0Carol". When inserted into ostream, it will stop at the first '\0'
  // because it's a C-string in many ostream overloads? Actually std::string preserves embedded NULs
  // and operator<< prints full string size, including NULs (they may not be visible).
  // So, we assert prefix and size rather than exact visual content beyond the NUL.
  const std::string out = CallPrint(*v);
  ASSERT_GE(out.size(), std::string("Alice, Bob").size());
  EXPECT_EQ(out.rfind("Alice, Bob", 0), 0u);  // starts with "Alice, Bob"
}

TEST(Print0x8298Test_1394, ReturnValue_IsSameStreamObject_1394) {
  auto v = MakeStringValue("Alice");
  ASSERT_NE(v, nullptr);

  std::ostringstream oss;
  std::ostream& ref = Exiv2::Internal::print0x8298(oss, *v, nullptr);
  EXPECT_EQ(&ref, &oss);
}