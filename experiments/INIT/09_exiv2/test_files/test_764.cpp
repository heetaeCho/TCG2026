// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <string>

// Exiv2 headers
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// Some Exiv2 builds expose ExifKey via exifkey.hpp; include if available.
// (If your build already provides ExifKey from exif.hpp, this include is harmless.)
#if __has_include(<exiv2/exifkey.hpp>)
#include <exiv2/exifkey.hpp>
#endif

namespace {

// A controllable Value implementation for testing Exifdatum::sizeDataArea()
// without relying on Exiv2's internal Value subclasses.
class TestValueSizeDataArea : public Exiv2::Value {
 public:
  explicit TestValueSizeDataArea(std::size_t dataAreaSize)
      : Exiv2::Value(static_cast<Exiv2::TypeId>(0)), dataAreaSize_(dataAreaSize) {}

  std::size_t sizeDataArea() const override { return dataAreaSize_; }

 private:
  // Value::clone_() is a private virtual in the base; it can still be overridden.
  const Exiv2::Value* clone_() override { return new TestValueSizeDataArea(*this); }

  std::size_t dataAreaSize_{0};
};

// Helper to create a valid ExifKey for constructing Exifdatum.
// Using a well-known key string avoids relying on internal state.
inline Exiv2::ExifKey MakeExifKey() {
  return Exiv2::ExifKey("Exif.Image.Make");
}

}  // namespace

class ExifdatumTest_764 : public ::testing::Test {};

TEST_F(ExifdatumTest_764, SizeDataAreaReturnsZeroWhenConstructedWithNullValue_764) {
  const Exiv2::ExifKey key = MakeExifKey();
  Exiv2::Exifdatum datum(key, nullptr);

  EXPECT_EQ(datum.sizeDataArea(), 0u);
}

TEST_F(ExifdatumTest_764, SizeDataAreaReturnsDependencyValueWhenNonNull_764) {
  const Exiv2::ExifKey key = MakeExifKey();
  auto v = std::make_unique<TestValueSizeDataArea>(123u);

  Exiv2::Exifdatum datum(key, v.get());

  EXPECT_EQ(datum.sizeDataArea(), 123u);
}

TEST_F(ExifdatumTest_764, SizeDataAreaPropagatesZeroFromNonNullValue_764) {
  const Exiv2::ExifKey key = MakeExifKey();
  auto v = std::make_unique<TestValueSizeDataArea>(0u);

  Exiv2::Exifdatum datum(key, v.get());

  EXPECT_EQ(datum.sizeDataArea(), 0u);
}

TEST_F(ExifdatumTest_764, SizeDataAreaUpdatesAfterSetValueNullThenNonNull_764) {
  const Exiv2::ExifKey key = MakeExifKey();
  auto v1 = std::make_unique<TestValueSizeDataArea>(77u);
  auto v2 = std::make_unique<TestValueSizeDataArea>(5u);

  Exiv2::Exifdatum datum(key, v1.get());
  EXPECT_EQ(datum.sizeDataArea(), 77u);

  datum.setValue(nullptr);
  EXPECT_EQ(datum.sizeDataArea(), 0u);

  datum.setValue(v2.get());
  EXPECT_EQ(datum.sizeDataArea(), 5u);
}

TEST_F(ExifdatumTest_764, SizeDataAreaHandlesLargeSizeValue_764) {
  const Exiv2::ExifKey key = MakeExifKey();
  constexpr std::size_t kLarge = static_cast<std::size_t>(1024) * 1024 * 1024;  // 1 GiB
  auto v = std::make_unique<TestValueSizeDataArea>(kLarge);

  Exiv2::Exifdatum datum(key, v.get());

  EXPECT_EQ(datum.sizeDataArea(), kLarge);
}