// TEST_ID 816
// Unit tests for Exiv2::CommentValue::CharsetInfo (value.cpp / value.hpp)

#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <utility>

#include "exiv2/value.hpp"

namespace {

// Helper dispatchers that work whether CharsetInfo APIs are static or instance methods.
// (We only use public interfaces; no private state access.)

using CharsetId = Exiv2::CommentValue::CharsetId;
using CharsetInfo = Exiv2::CommentValue::CharsetInfo;

template <typename T>
static auto CallCodeDispatch(int, CharsetId id) -> decltype(T::code(id)) {
  return T::code(id);
}
template <typename T>
static auto CallCodeDispatch(long, CharsetId id) -> decltype(std::declval<T&>().code(id)) {
  T info{};
  return info.code(id);
}
static const char* CallCode(CharsetId id) {
  return CallCodeDispatch<CharsetInfo>(0, id);
}

template <typename T>
static auto CallNameDispatch(int, CharsetId id) -> decltype(T::name(id)) {
  return T::name(id);
}
template <typename T>
static auto CallNameDispatch(long, CharsetId id) -> decltype(std::declval<T&>().name(id)) {
  T info{};
  return info.name(id);
}
static const char* CallName(CharsetId id) {
  return CallNameDispatch<CharsetInfo>(0, id);
}

template <typename T>
static auto CharsetIdByCodeDispatch(int, const std::string& code) -> decltype(T::charsetIdByCode(code)) {
  return T::charsetIdByCode(code);
}
template <typename T>
static auto CharsetIdByCodeDispatch(long, const std::string& code)
      -> decltype(std::declval<T&>().charsetIdByCode(code)) {
  T info{};
  return info.charsetIdByCode(code);
}
static CharsetId CharsetIdByCode(const std::string& code) {
  return CharsetIdByCodeDispatch<CharsetInfo>(0, code);
}

template <typename T>
static auto CharsetIdByNameDispatch(int, const std::string& name) -> decltype(T::charsetIdByName(name)) {
  return T::charsetIdByName(name);
}
template <typename T>
static auto CharsetIdByNameDispatch(long, const std::string& name)
      -> decltype(std::declval<T&>().charsetIdByName(name)) {
  T info{};
  return info.charsetIdByName(name);
}
static CharsetId CharsetIdByName(const std::string& name) {
  return CharsetIdByNameDispatch<CharsetInfo>(0, name);
}

static bool IsKnownId(CharsetId id) {
  return id == Exiv2::CommentValue::ascii || id == Exiv2::CommentValue::jis ||
         id == Exiv2::CommentValue::unicode || id == Exiv2::CommentValue::undefined;
}

}  // namespace

class CharsetInfoTest_816 : public ::testing::Test {};

TEST_F(CharsetInfoTest_816, CodeReturnsNonNullForKnownCharsetIds_816) {
  const CharsetId ids[] = {Exiv2::CommentValue::ascii, Exiv2::CommentValue::jis,
                           Exiv2::CommentValue::unicode, Exiv2::CommentValue::undefined};

  for (CharsetId id : ids) {
    const char* code = CallCode(id);
    ASSERT_NE(code, nullptr) << "code() returned nullptr for id=" << static_cast<int>(id);
    EXPECT_NE(std::string(code), std::string())
        << "code() returned empty string for id=" << static_cast<int>(id);
  }
}

TEST_F(CharsetInfoTest_816, NameReturnsNonNullForKnownCharsetIds_816) {
  const CharsetId ids[] = {Exiv2::CommentValue::ascii, Exiv2::CommentValue::jis,
                           Exiv2::CommentValue::unicode, Exiv2::CommentValue::undefined};

  for (CharsetId id : ids) {
    const char* name = CallName(id);
    ASSERT_NE(name, nullptr) << "name() returned nullptr for id=" << static_cast<int>(id);
    EXPECT_NE(std::string(name), std::string())
        << "name() returned empty string for id=" << static_cast<int>(id);
  }
}

TEST_F(CharsetInfoTest_816, CodeOutOfRangeMapsToSameAsUndefined_816) {
  // Boundary: ids at/above lastCharsetId should not cause undefined behavior via interface.
  const char* undefined_code = CallCode(Exiv2::CommentValue::undefined);
  ASSERT_NE(undefined_code, nullptr);

  // Exactly lastCharsetId
  const char* last_code = CallCode(Exiv2::CommentValue::lastCharsetId);
  ASSERT_NE(last_code, nullptr);
  EXPECT_STREQ(last_code, undefined_code);

  // Known "invalid" enum value
  const char* invalid_code = CallCode(Exiv2::CommentValue::invalidCharsetId);
  ASSERT_NE(invalid_code, nullptr);
  EXPECT_STREQ(invalid_code, undefined_code);

  // Far out-of-range value (avoid negative casts).
  const auto huge = static_cast<CharsetId>(9999);
  const char* huge_code = CallCode(huge);
  ASSERT_NE(huge_code, nullptr);
  EXPECT_STREQ(huge_code, undefined_code);
}

TEST_F(CharsetInfoTest_816, CharsetIdByCodeRoundTripsToCanonicalCode_816) {
  const CharsetId ids[] = {Exiv2::CommentValue::ascii, Exiv2::CommentValue::jis,
                           Exiv2::CommentValue::unicode, Exiv2::CommentValue::undefined};

  for (CharsetId original : ids) {
    const char* code = CallCode(original);
    ASSERT_NE(code, nullptr);

    const CharsetId parsed = CharsetIdByCode(std::string(code));

    // Observable contract: parsing its own code should produce an id that maps back to the same code.
    const char* code2 = CallCode(parsed);
    ASSERT_NE(code2, nullptr);
    EXPECT_STREQ(code2, code);
  }
}

TEST_F(CharsetInfoTest_816, CharsetIdByNameRoundTripsToCanonicalName_816) {
  const CharsetId ids[] = {Exiv2::CommentValue::ascii, Exiv2::CommentValue::jis,
                           Exiv2::CommentValue::unicode, Exiv2::CommentValue::undefined};

  for (CharsetId original : ids) {
    const char* name = CallName(original);
    ASSERT_NE(name, nullptr);

    const CharsetId parsed = CharsetIdByName(std::string(name));

    // Observable contract: parsing its own name should produce an id that maps back to the same name.
    const char* name2 = CallName(parsed);
    ASSERT_NE(name2, nullptr);
    EXPECT_STREQ(name2, name);
  }
}

TEST_F(CharsetInfoTest_816, CharsetIdByCodeUnknownStringDoesNotReturnKnownCharset_816) {
  const CharsetId parsed = CharsetIdByCode("this_is_not_a_real_charset_code_816");

  // Error/exceptional case: unknown input should not claim to be a known non-undefined charset.
  // (We avoid assuming which specific "invalid" enum is used; we only assert it isn't a known one.)
  EXPECT_FALSE(IsKnownId(parsed)) << "Unexpectedly mapped unknown code to a known charset id="
                                  << static_cast<int>(parsed);
}

TEST_F(CharsetInfoTest_816, CharsetIdByNameUnknownStringDoesNotReturnKnownCharset_816) {
  const CharsetId parsed = CharsetIdByName("this_is_not_a_real_charset_name_816");

  // Error/exceptional case: unknown input should not claim to be a known non-undefined charset.
  EXPECT_FALSE(IsKnownId(parsed)) << "Unexpectedly mapped unknown name to a known charset id="
                                  << static_cast<int>(parsed);
}