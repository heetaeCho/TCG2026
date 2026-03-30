// SPDX-License-Identifier: GPL-2.0-or-later
// File: ./TestProjects/exiv2/tests/test_casiomn_int_casio2makernote_1353.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "casiomn_int.hpp"

#include "exif.hpp"
#include "types.hpp"
#include "value.hpp"

namespace {

// TEST_ID = 1353
class Casio2MakerNoteTest_1353 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeValue(Exiv2::TypeId type, const std::string& text) {
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(type);
    // Treat as black box: just use the public API to populate.
    // Some types may accept empty strings; if not, test cases will still validate "no crash/throw"
    // by choosing inputs that are typically parseable.
    if (v.get() != nullptr) {
      v->read(text);
    }
    return v;
  }
};

}  // namespace

// Compile-time sanity: tagList() must be callable in a constant expression context.
// (No assumptions about content; only that it is a constexpr function per interface.)
namespace {
constexpr auto kCasio2TagListPtr_1353 = Exiv2::Internal::Casio2MakerNote::tagList();
static_assert(kCasio2TagListPtr_1353 == Exiv2::Internal::Casio2MakerNote::tagList(),
              "Casio2MakerNote::tagList() should be stable in constexpr context");
}  // namespace

TEST_F(Casio2MakerNoteTest_1353, TagListIsCallableAndStableAcrossCalls_1353) {
  // Normal operation: calling tagList() should be safe and stable.
  const auto a = Exiv2::Internal::Casio2MakerNote::tagList();
  const auto b = Exiv2::Internal::Casio2MakerNote::tagList();

  // Observable behavior we can safely assert without knowing internals:
  // - The returned value is stable/equal across calls.
  EXPECT_EQ(a, b);

  // If it's a pointer-like value (common for tag lists), comparing to nullptr is valid.
  // If it's not pointer-like, this line will fail to compile; in that case, remove it.
  EXPECT_NE(a, nullptr);
}

TEST_F(Casio2MakerNoteTest_1353, Print0x2001ReturnsSameStreamReference_1353) {
  // Normal operation: function should return the same ostream reference passed in.
  std::ostringstream os;
  auto v = makeValue(Exiv2::unsignedShort, "1");
  ASSERT_NE(v.get(), nullptr);

  std::ostream& ret = Exiv2::Internal::Casio2MakerNote::print0x2001(os, *v, nullptr);
  EXPECT_EQ(&ret, &os);

  // Minimal observable behavior: stream remains usable after call.
  EXPECT_TRUE(os.good());
}

TEST_F(Casio2MakerNoteTest_1353, Print0x2022ReturnsSameStreamReference_1353) {
  // Normal operation: function should return the same ostream reference passed in.
  std::ostringstream os;
  auto v = makeValue(Exiv2::unsignedShort, "0");
  ASSERT_NE(v.get(), nullptr);

  std::ostream& ret = Exiv2::Internal::Casio2MakerNote::print0x2022(os, *v, nullptr);
  EXPECT_EQ(&ret, &os);
  EXPECT_TRUE(os.good());
}

TEST_F(Casio2MakerNoteTest_1353, PrintFunctionsHandleEmptyValueWithoutThrow_1353) {
  // Boundary/error-ish case: empty/blank input and nullptr ExifData pointer.
  // We do not assume exact output; only that the functions are robust via public interface.
  std::ostringstream os1;
  std::ostringstream os2;

  auto emptyAscii = makeValue(Exiv2::asciiString, "");
  ASSERT_NE(emptyAscii.get(), nullptr);

  EXPECT_NO_THROW({
    (void)Exiv2::Internal::Casio2MakerNote::print0x2001(os1, *emptyAscii, nullptr);
  });
  EXPECT_NO_THROW({
    (void)Exiv2::Internal::Casio2MakerNote::print0x2022(os2, *emptyAscii, nullptr);
  });

  EXPECT_TRUE(os1.good());
  EXPECT_TRUE(os2.good());
}