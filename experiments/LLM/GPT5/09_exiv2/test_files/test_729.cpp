// File: test_exifdatum_value_729.cpp
// Unit tests for Exiv2::Exifdatum::value() const
//
// Constraints respected:
// - Treat implementation as black box
// - Only use public interface / observable behavior
// - No private state access

#include <gtest/gtest.h>

#include <exiv2/error.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <string>
#include <type_traits>
#include <utility>

namespace {

template <typename T, typename = void>
struct has_code_method : std::false_type {};
template <typename T>
struct has_code_method<T, std::void_t<decltype(std::declval<const T&>().code())>> : std::true_type {};

template <typename T, typename = void>
struct has_errorCode_method : std::false_type {};
template <typename T>
struct has_errorCode_method<T, std::void_t<decltype(std::declval<const T&>().errorCode())>> : std::true_type {};

static Exiv2::ExifKey MakeTestKey() {
  // Use a commonly valid Exif key string. This relies only on the public ExifKey API.
  return Exiv2::ExifKey("Exif.Image.Make");
}

static Exiv2::Value::UniquePtr MakeAsciiValue(const std::string& s) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::asciiString);
  // Value::read is public; use it to populate a value without assuming internal behavior.
  v->read(s);
  return v;
}

}  // namespace

class ExifdatumValueTest_729 : public ::testing::Test {};

TEST_F(ExifdatumValueTest_729, ThrowsWhenValueNotSet_729) {
  const Exiv2::ExifKey key = MakeTestKey();

  // Construct with no value provided.
  Exiv2::Exifdatum d(key, nullptr);

  EXPECT_THROW((void)d.value(), Exiv2::Error);
}

TEST_F(ExifdatumValueTest_729, ThrowsErrorCodeKerValueNotSetWhenValueNotSet_729) {
  const Exiv2::ExifKey key = MakeTestKey();
  Exiv2::Exifdatum d(key, nullptr);

  try {
    (void)d.value();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // Verify error code if the Error type exposes it (API differences across versions).
    if constexpr (has_code_method<Exiv2::Error>::value) {
      EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerValueNotSet);
    } else if constexpr (has_errorCode_method<Exiv2::Error>::value) {
      EXPECT_EQ(e.errorCode(), Exiv2::ErrorCode::kerValueNotSet);
    } else {
      SUCCEED() << "Exiv2::Error does not expose an error-code accessor in this build";
    }
  } catch (...) {
    FAIL() << "Expected Exiv2::Error (different exception type thrown)";
  }
}

TEST_F(ExifdatumValueTest_729, DoesNotThrowAfterSettingValueViaStringAssignment_729) {
  const Exiv2::ExifKey key = MakeTestKey();
  Exiv2::Exifdatum d(key, nullptr);

  d = std::string("Canon");

  EXPECT_NO_THROW((void)d.value());
}

TEST_F(ExifdatumValueTest_729, ValueReflectsAssignedStringViaToString_729) {
  const Exiv2::ExifKey key = MakeTestKey();
  Exiv2::Exifdatum d(key, nullptr);

  const std::string expected = "Canon";
  d = expected;

  // Observable behavior through public API: toString() should reflect current value.
  EXPECT_EQ(d.toString(), expected);
}

TEST_F(ExifdatumValueTest_729, DoesNotThrowWhenConstructedWithNonNullValuePointer_729) {
  const Exiv2::ExifKey key = MakeTestKey();
  const auto v = MakeAsciiValue("Nikon");

  // ctor takes const Value*; we treat it as black-box ownership/copy semantics.
  Exiv2::Exifdatum d(key, v.get());

  EXPECT_NO_THROW((void)d.value());
  EXPECT_EQ(d.toString(), "Nikon");
}

TEST_F(ExifdatumValueTest_729, CopyConstructedDatumPreservesValueObservably_729) {
  const Exiv2::ExifKey key = MakeTestKey();
  Exiv2::Exifdatum original(key, nullptr);
  original = std::string("Sony");

  Exiv2::Exifdatum copy(original);

  EXPECT_NO_THROW((void)copy.value());
  EXPECT_EQ(copy.toString(), "Sony");
}

TEST_F(ExifdatumValueTest_729, ValueCanBeAccessedRepeatedlyWithoutThrowing_729) {
  const Exiv2::ExifKey key = MakeTestKey();
  Exiv2::Exifdatum d(key, nullptr);
  d = std::string("Fujifilm");

  EXPECT_NO_THROW((void)d.value());
  EXPECT_NO_THROW((void)d.value());
  EXPECT_EQ(d.toString(), "Fujifilm");
}

TEST_F(ExifdatumValueTest_729, BoundaryEmptyStringIsAcceptedAndValueAccessible_729) {
  const Exiv2::ExifKey key = MakeTestKey();
  Exiv2::Exifdatum d(key, nullptr);

  d = std::string("");

  EXPECT_NO_THROW((void)d.value());
  EXPECT_EQ(d.toString(), "");
}