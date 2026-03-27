// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

namespace {

// Fixture dedicated to Exiv2::Exifdatum::getValue()
class ExifdatumGetValueTest_763 : public ::testing::Test {
 protected:
  // Use a well-known, valid Exif key string (public API).
  Exiv2::ExifKey MakeKey() const { return Exiv2::ExifKey("Exif.Image.Make"); }

  static Exiv2::Value::UniquePtr MakeAsciiValue(const std::string& s) {
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    // Rely only on public API; ignore the exact parsing details.
    (void)v->read(s);
    return v;
  }
};

TEST_F(ExifdatumGetValueTest_763, ReturnsNullptrWhenNoValue_763) {
  const Exiv2::ExifKey key = MakeKey();

  // Construct with nullptr value (public API allows const Value*).
  const Exiv2::Exifdatum datum(key, /*pValue=*/nullptr);

  auto cloned = datum.getValue();
  EXPECT_EQ(cloned, nullptr);
}

TEST_F(ExifdatumGetValueTest_763, ReturnsNonNullCloneWhenValueProvided_763) {
  const Exiv2::ExifKey key = MakeKey();
  auto input = MakeAsciiValue("Canon");

  const Exiv2::Exifdatum datum(key, input.get());

  auto cloned = datum.getValue();
  ASSERT_NE(cloned, nullptr);

  // Observable behavior through Value public API.
  EXPECT_EQ(cloned->typeId(), input->typeId());
  EXPECT_EQ(cloned->toString(), input->toString());
}

TEST_F(ExifdatumGetValueTest_763, EachCallReturnsIndependentObject_763) {
  const Exiv2::ExifKey key = MakeKey();
  auto input = MakeAsciiValue("Nikon");

  const Exiv2::Exifdatum datum(key, input.get());

  auto v1 = datum.getValue();
  auto v2 = datum.getValue();

  ASSERT_NE(v1, nullptr);
  ASSERT_NE(v2, nullptr);

  // At minimum, ownership should be distinct.
  EXPECT_NE(v1.get(), v2.get());

  // Mutating one returned Value should not mutate the other (observable via toString()).
  const std::string original = v2->toString();
  (void)v1->read("Different");
  EXPECT_EQ(v2->toString(), original);
}

TEST_F(ExifdatumGetValueTest_763, HandlesEmptyStringValue_763) {
  const Exiv2::ExifKey key = MakeKey();
  auto input = MakeAsciiValue("");

  const Exiv2::Exifdatum datum(key, input.get());
  auto cloned = datum.getValue();

  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->typeId(), input->typeId());
  EXPECT_EQ(cloned->toString(), input->toString());
}

TEST_F(ExifdatumGetValueTest_763, HandlesLargeStringValue_763) {
  const Exiv2::ExifKey key = MakeKey();
  const std::string big(4096, 'A');
  auto input = MakeAsciiValue(big);

  const Exiv2::Exifdatum datum(key, input.get());
  auto cloned = datum.getValue();

  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->typeId(), input->typeId());
  EXPECT_EQ(cloned->toString(), input->toString());
}

}  // namespace