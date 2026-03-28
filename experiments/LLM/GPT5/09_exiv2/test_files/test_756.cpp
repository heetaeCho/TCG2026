// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdatum_count_756.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstddef>
#include <limits>
#include <memory>
#include <string>

namespace {

// A minimal Value implementation we can pass into Exifdatum.
// Note: Exifdatum takes a const Value* and may clone it internally, so we provide clone_().
class CountingValue final : public Exiv2::Value {
 public:
  explicit CountingValue(std::size_t c) : Exiv2::Value(static_cast<Exiv2::TypeId>(0)), c_(c) {}
  CountingValue(const CountingValue&) = default;
  ~CountingValue() override = default;

  const std::size_t count() override { return c_; }

 private:
  const Exiv2::Value* clone_() override { return new CountingValue(*this); }

  std::size_t c_;
};

}  // namespace

TEST(ExifdatumTest_756, CountReturnsZeroWhenConstructedWithNullValue_756) {
  const Exiv2::ExifKey key("Exif.Image.Make");
  const Exiv2::Exifdatum d(key, nullptr);

  EXPECT_EQ(d.count(), 0u);
}

TEST(ExifdatumTest_756, CountReturnsUnderlyingValueCount_756) {
  const Exiv2::ExifKey key("Exif.Image.Make");
  CountingValue v(3u);

  const Exiv2::Exifdatum d(key, &v);
  EXPECT_EQ(d.count(), 3u);
}

TEST(ExifdatumTest_756, CountOnCopiedObjectMatchesOriginal_756) {
  const Exiv2::ExifKey key("Exif.Image.Make");
  CountingValue v(7u);

  const Exiv2::Exifdatum original(key, &v);
  const Exiv2::Exifdatum copy(original);

  EXPECT_EQ(copy.count(), original.count());
}

TEST(ExifdatumTest_756, CountOnAssignedObjectMatchesRhs_756) {
  const Exiv2::ExifKey key1("Exif.Image.Make");
  const Exiv2::ExifKey key2("Exif.Image.Model");
  CountingValue v1(2u);
  CountingValue v2(9u);

  Exiv2::Exifdatum lhs(key1, &v1);
  const Exiv2::Exifdatum rhs(key2, &v2);

  lhs = rhs;

  EXPECT_EQ(lhs.count(), rhs.count());
}

TEST(ExifdatumTest_756, SelfAssignmentDoesNotChangeCount_756) {
  const Exiv2::ExifKey key("Exif.Image.Make");
  CountingValue v(11u);

  Exiv2::Exifdatum d(key, &v);
  const std::size_t before = d.count();

  d = d;

  EXPECT_EQ(d.count(), before);
}

TEST(ExifdatumTest_756, CountSupportsLargeSizeTValues_756) {
  const Exiv2::ExifKey key("Exif.Image.Make");
  const std::size_t big = (std::numeric_limits<std::size_t>::max)();

  CountingValue v(big);
  const Exiv2::Exifdatum d(key, &v);

  EXPECT_EQ(d.count(), big);
}