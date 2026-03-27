// SPDX-License-Identifier: GPL-2.0-or-later
// The TEST_ID is 757
//
// Unit tests for Exiv2::Exifdatum::size() (black-box via public interface)

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <memory>
#include <string>

namespace {

class ExifdatumTest_757 : public ::testing::Test {
 protected:
  static Exiv2::ExifKey MakeKey() {
    // A commonly valid Exif key string in Exiv2.
    return Exiv2::ExifKey("Exif.Image.Make");
  }

  static Exiv2::Value::UniquePtr MakeAsciiValueWithString(const std::string& s) {
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    // Use the Value interface to populate it; we don't assume what "size()" means.
    // We only compare Exifdatum::size() to the corresponding Value::size().
    (void)v->read(s);
    return v;
  }
};

TEST_F(ExifdatumTest_757, SizeReturnsZeroWhenConstructedWithNullValue_757) {
  const Exiv2::ExifKey key = MakeKey();

  Exiv2::Exifdatum d(key, /*pValue=*/nullptr);

  EXPECT_EQ(d.size(), 0u);
}

TEST_F(ExifdatumTest_757, SizeMatchesProvidedValueSizeAfterConstruction_757) {
  const Exiv2::ExifKey key = MakeKey();

  auto v = MakeAsciiValueWithString("abc");
  const size_t expected = v->size();

  Exiv2::Exifdatum d(key, v.get());

  EXPECT_EQ(d.size(), expected);
}

TEST_F(ExifdatumTest_757, SizeMatchesProvidedValueSizeForEmptyString_757) {
  const Exiv2::ExifKey key = MakeKey();

  auto v = MakeAsciiValueWithString(std::string{});
  const size_t expected = v->size();

  Exiv2::Exifdatum d(key, v.get());

  EXPECT_EQ(d.size(), expected);
}

TEST_F(ExifdatumTest_757, SizePreservedByCopyConstruction_757) {
  const Exiv2::ExifKey key = MakeKey();

  auto v = MakeAsciiValueWithString("copy-me");
  Exiv2::Exifdatum original(key, v.get());
  const size_t expected = original.size();

  Exiv2::Exifdatum copied(original);

  EXPECT_EQ(copied.size(), expected);
}

TEST_F(ExifdatumTest_757, SizeFollowsCopyAssignmentFromOtherExifdatum_757) {
  const Exiv2::ExifKey key = MakeKey();

  auto v1 = MakeAsciiValueWithString("first");
  Exiv2::Exifdatum a(key, v1.get());

  auto v2 = MakeAsciiValueWithString("this is different");
  Exiv2::Exifdatum b(key, v2.get());
  const size_t expected = b.size();

  a = b;

  EXPECT_EQ(a.size(), expected);
}

TEST_F(ExifdatumTest_757, SetValueNullClearsSizeToZeroIfSupported_757) {
  const Exiv2::ExifKey key = MakeKey();

  auto v = MakeAsciiValueWithString("non-empty");
  Exiv2::Exifdatum d(key, v.get());
  ASSERT_NE(d.size(), 0u);

  // We don’t assume semantics beyond what’s observable. If nullptr is accepted,
  // size() should become 0 (consistent with Exifdatum::size() behavior).
  EXPECT_NO_THROW(d.setValue(nullptr));
  EXPECT_EQ(d.size(), 0u);
}

}  // namespace