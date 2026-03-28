// -----------------------------------------------------------------------------
// TEST_ID 1356
// Unit tests for: Exiv2::Internal::SigmaMakerNote (sigmamn_int.hpp)
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

#include <sstream>
#include <type_traits>

#include "sigmamn_int.hpp"

namespace {

using Exiv2::ExifData;
using Exiv2::Internal::SigmaMakerNote;

class SigmaMakerNoteTest_1356 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeUShortValue(const char* txt) {
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    if (txt != nullptr) {
      (void)v->read(txt);  // do not assert on parsing semantics; just best-effort.
    }
    return v;
  }

  static Exiv2::Value::UniquePtr makeULongValue(const char* txt) {
    auto v = Exiv2::Value::create(Exiv2::unsignedLong);
    if (txt != nullptr) {
      (void)v->read(txt);
    }
    return v;
  }
};

TEST_F(SigmaMakerNoteTest_1356, TagList_IsCallableAndStableAcrossCalls_1356) {
  // Compile-time: callable and returns some object (usually a pointer/array view).
  using TagListT = decltype(SigmaMakerNote::tagList());
  (void)sizeof(TagListT);

  // Runtime: should be stable for repeated calls (common for static tag tables).
  const auto t1 = SigmaMakerNote::tagList();
  const auto t2 = SigmaMakerNote::tagList();

  // Without assuming exact type, require equality comparability at compile-time if possible.
  if constexpr (std::is_pointer_v<TagListT>) {
    EXPECT_NE(t1, nullptr);
    EXPECT_EQ(t1, t2);
  } else {
    // If not a raw pointer, we can still check that taking addresses of temporaries is avoided;
    // basic sanity: repeated calls produce equal values when equality exists.
    if constexpr (requires(TagListT a, TagListT b) { a == b; }) {
      EXPECT_TRUE(t1 == t2);
    } else {
      SUCCEED() << "tagList() return type has no operator==; stability not directly comparable.";
    }
  }
}

TEST_F(SigmaMakerNoteTest_1356, PrintStripLabel_ReturnsSameOstreamAndKeepsStreamUsable_1356) {
  std::stringstream ss;

  // Boundary-ish: empty value (0 components) is still an observable input.
  auto v = makeUShortValue(nullptr);

  std::ostream& out = SigmaMakerNote::printStripLabel(ss, *v, static_cast<const ExifData*>(nullptr));
  EXPECT_EQ(&out, &ss);
  EXPECT_TRUE(ss.good());
}

TEST_F(SigmaMakerNoteTest_1356, Print0x0008_ReturnsSameOstream_ForDifferentValues_1356) {
  std::stringstream ss1;
  std::stringstream ss2;

  auto vEmpty = makeULongValue(nullptr);
  auto vOne = makeULongValue("0");

  std::ostream& out1 = SigmaMakerNote::print0x0008(ss1, *vEmpty, static_cast<const ExifData*>(nullptr));
  std::ostream& out2 = SigmaMakerNote::print0x0008(ss2, *vOne, static_cast<const ExifData*>(nullptr));

  EXPECT_EQ(&out1, &ss1);
  EXPECT_EQ(&out2, &ss2);
  EXPECT_TRUE(ss1.good());
  EXPECT_TRUE(ss2.good());
}

TEST_F(SigmaMakerNoteTest_1356, Print0x0009_AcceptsExifDataPointerAndReturnsSameOstream_1356) {
  std::stringstream ss;
  ExifData exif;

  // Normal-ish: provide a value with some content and a non-null ExifData pointer.
  auto v = makeUShortValue("1");

  std::ostream& out = SigmaMakerNote::print0x0009(ss, *v, &exif);
  EXPECT_EQ(&out, &ss);
  EXPECT_TRUE(ss.good());
}

}  // namespace