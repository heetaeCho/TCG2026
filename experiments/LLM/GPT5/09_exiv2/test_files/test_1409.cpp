// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_tags_int_print0xa300_1409.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <sstream>
#include <string>

namespace Exiv2 {
namespace Internal {
// Function under test (implemented in src/tags_int.cpp)
std::ostream& print0xa300(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class FakeNumericValue final : public Exiv2::Value {
 public:
  explicit FakeNumericValue(uint32_t v)
      : Exiv2::Value(typeIdFromFactory_()), v_(v) {}

  const size_t count() override { return 1; }
  const std::string toString(size_t /*n*/) override { return std::to_string(v_); }
  const int64_t toInt64(size_t /*n*/) override { return static_cast<int64_t>(v_); }
  const uint32_t toUint32(size_t /*n*/) override { return v_; }

 private:
  static Exiv2::TypeId typeIdFromFactory_() {
    // Pick any valid TypeId without assuming internals: ask the library for a Value instance and reuse its type.
    auto tmp = Exiv2::Value::create(Exiv2::unsignedLong);
    return tmp ? tmp->typeId() : Exiv2::unsignedLong;
  }

  uint32_t v_;
};

}  // namespace

TEST(Print0xa300Test_1409, ReturnsSameStreamReference_1409) {
  FakeNumericValue v(1);
  std::ostringstream os;

  std::ostream& ret = Exiv2::Internal::print0xa300(os, v, nullptr);

  EXPECT_EQ(&ret, &os);
}

TEST(Print0xa300Test_1409, KnownValue1PrintsFilmScanner_1409) {
  FakeNumericValue v(1);
  std::ostringstream os;

  Exiv2::Internal::print0xa300(os, v, nullptr);
  const std::string out = os.str();

  // Based on provided TagDetails for exifFileSource:
  // {1, "Film scanner"}
  EXPECT_NE(out.find("Film scanner"), std::string::npos);
}

TEST(Print0xa300Test_1409, KnownValue2PrintsReflexionPrintScanner_1409) {
  FakeNumericValue v(2);
  std::ostringstream os;

  Exiv2::Internal::print0xa300(os, v, nullptr);
  const std::string out = os.str();

  // Based on provided TagDetails for exifFileSource:
  // {2, "Reflexion print scanner"}
  EXPECT_NE(out.find("Reflexion print scanner"), std::string::npos);
}

TEST(Print0xa300Test_1409, OutOfRangeValueDoesNotCrashAndProducesSomeOutput_1409) {
  FakeNumericValue v(999);
  Exiv2::ExifData md;  // also verify non-null metadata pointer is accepted
  std::ostringstream os;

  Exiv2::Internal::print0xa300(os, v, &md);

  // Don't assume exact formatting for unknown values; just verify it behaved safely and wrote something.
  EXPECT_FALSE(os.str().empty());
}