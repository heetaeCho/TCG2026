// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdatum_tostring_758.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <string>

namespace {

class ExifdatumTest_758 : public ::testing::Test {
 protected:
  static Exiv2::ExifKey MakeKey() {
    // Use a common key string that should exist in Exiv2.
    return Exiv2::ExifKey("Exif.Image.Make");
  }

  static Exiv2::Value::UniquePtr MakeAsciiValue(const std::string& s) {
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    // Rely only on public interface; if read() fails, v->toString() will still be observable.
    (void)v->read(s);
    return v;
  }
};

TEST_F(ExifdatumTest_758, ToStringReturnsEmptyWhenConstructedWithNullValue_758) {
  const Exiv2::ExifKey key = MakeKey();

  Exiv2::Exifdatum d(key, nullptr);

  EXPECT_EQ(d.toString(), std::string{});
}

TEST_F(ExifdatumTest_758, ToStringReturnsValueStringWhenConstructedWithValue_758) {
  const Exiv2::ExifKey key = MakeKey();
  auto v = MakeAsciiValue("Hello");

  Exiv2::Exifdatum d(key, v.get());

  EXPECT_EQ(d.toString(), std::string("Hello"));
}

TEST_F(ExifdatumTest_758, ToStringReturnsEmptyForEmptyStringValue_758) {
  const Exiv2::ExifKey key = MakeKey();
  auto v = MakeAsciiValue("");

  Exiv2::Exifdatum d(key, v.get());

  EXPECT_EQ(d.toString(), std::string{});
}

TEST_F(ExifdatumTest_758, ToStringDoesNotThrowWhenNoValueIsPresent_758) {
  const Exiv2::ExifKey key = MakeKey();
  Exiv2::Exifdatum d(key, nullptr);

  EXPECT_NO_THROW({
    const std::string s = d.toString();
    (void)s;
  });
}

TEST_F(ExifdatumTest_758, CopyConstructedObjectPreservesToStringObservation_758) {
  const Exiv2::ExifKey key = MakeKey();
  auto v = MakeAsciiValue("CopyMe");

  Exiv2::Exifdatum original(key, v.get());
  Exiv2::Exifdatum copy(original);

  EXPECT_EQ(original.toString(), std::string("CopyMe"));
  EXPECT_EQ(copy.toString(), std::string("CopyMe"));
}

TEST_F(ExifdatumTest_758, AssignedStringValueIsObservableViaToString_758) {
  const Exiv2::ExifKey key = MakeKey();
  Exiv2::Exifdatum d(key, nullptr);

  d = std::string("Assigned");

  EXPECT_EQ(d.toString(), std::string("Assigned"));
}

TEST_F(ExifdatumTest_758, AssignedEmptyStringValueIsObservableViaToString_758) {
  const Exiv2::ExifKey key = MakeKey();
  Exiv2::Exifdatum d(key, nullptr);

  d = std::string("");

  EXPECT_EQ(d.toString(), std::string{});
}

}  // namespace