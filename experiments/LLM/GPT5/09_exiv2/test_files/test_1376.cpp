// File: test_tags_int_tagNumber_1376.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include <exiv2/error.hpp>

// The function under test lives in src/tags_int.cpp (Internal namespace).
// Prefer including the internal header if your build exposes it; otherwise
// this forward declaration matches the provided signature.
namespace Exiv2 {
  // IfdId is defined somewhere in Exiv2 public headers; we only need it as a type.
  // Forward-declaring as an enum is not safe without the exact definition,
  // so we rely on the real definition being visible via includes pulled in by error.hpp
  // in the project build. If your build requires it, include the proper header
  // (e.g., <exiv2/tags.hpp> or <exiv2/types.hpp>) above.
  enum IfdId : int;  // works if IfdId is an unscoped enum with int underlying type
  namespace Internal {
    uint16_t tagNumber(const std::string& tagName, IfdId ifdId);
  }
}  // namespace Exiv2

namespace {

class TagNumberTest_1376 : public ::testing::Test {
 protected:
  // Use a stable, valid IfdId value without relying on specific enumerators.
  // This keeps the test focused on tagNumber's observable behavior.
  static Exiv2::IfdId SomeIfdId() {
    return static_cast<Exiv2::IfdId>(0);
  }
};

TEST_F(TagNumberTest_1376, ReturnsParsedValueForValidHexTag_1376) {
  const auto ifdId = SomeIfdId();

  // Valid 4-digit hex with "0x" prefix should be accepted.
  EXPECT_EQ(static_cast<uint16_t>(0x0000), Exiv2::Internal::tagNumber("0x0000", ifdId));
  EXPECT_EQ(static_cast<uint16_t>(0x0001), Exiv2::Internal::tagNumber("0x0001", ifdId));
  EXPECT_EQ(static_cast<uint16_t>(0x00ff), Exiv2::Internal::tagNumber("0x00ff", ifdId));
  EXPECT_EQ(static_cast<uint16_t>(0xffff), Exiv2::Internal::tagNumber("0xffff", ifdId));
}

TEST_F(TagNumberTest_1376, AcceptsUppercaseHexDigits_1376) {
  const auto ifdId = SomeIfdId();

  EXPECT_EQ(static_cast<uint16_t>(0x00ab), Exiv2::Internal::tagNumber("0x00AB", ifdId));
  EXPECT_EQ(static_cast<uint16_t>(0xabcd), Exiv2::Internal::tagNumber("0xABCD", ifdId));
}

TEST_F(TagNumberTest_1376, ThrowsKerInvalidTagForMissing0xPrefix_1376) {
  const auto ifdId = SomeIfdId();

  try {
    (void)Exiv2::Internal::tagNumber("0001", ifdId);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    // Observable error case: invalid tag name should surface kerInvalidTag.
    EXPECT_EQ(Exiv2::ErrorCode::kerInvalidTag, e.code());
  }
}

TEST_F(TagNumberTest_1376, ThrowsKerInvalidTagForNonHexCharacters_1376) {
  const auto ifdId = SomeIfdId();

  const char* const bad_inputs[] = {
      "0x0g01",  // 'g' is not hex
      "0xzzzz",  // non-hex
      "0x12_3",  // underscore
      "0x12 3",  // whitespace
  };

  for (const auto* s : bad_inputs) {
    try {
      (void)Exiv2::Internal::tagNumber(std::string(s), ifdId);
      FAIL() << "Expected Exiv2::Error for input: " << s;
    } catch (const Exiv2::Error& e) {
      EXPECT_EQ(Exiv2::ErrorCode::kerInvalidTag, e.code()) << "input: " << s;
    }
  }
}

TEST_F(TagNumberTest_1376, ThrowsKerInvalidTagForWrongHexWidth_1376) {
  const auto ifdId = SomeIfdId();

  // Boundary / format enforcement: requires exactly 4 hex digits after 0x.
  const char* const bad_width[] = {
      "0x",        // empty
      "0x0",       // 1 digit
      "0x00",      // 2 digits
      "0x000",     // 3 digits
      "0x00000",   // 5 digits
      "0x10000",   // would exceed 16-bit if interpreted, but should be rejected by width
      "0x000000",  // 6 digits
  };

  for (const auto* s : bad_width) {
    try {
      (void)Exiv2::Internal::tagNumber(std::string(s), ifdId);
      FAIL() << "Expected Exiv2::Error for input: " << s;
    } catch (const Exiv2::Error& e) {
      EXPECT_EQ(Exiv2::ErrorCode::kerInvalidTag, e.code()) << "input: " << s;
    }
  }
}

TEST_F(TagNumberTest_1376, ThrowsKerInvalidTagForClearlyNonHexNonTagString_1376) {
  const auto ifdId = SomeIfdId();

  // If the name is neither a known tag nor a valid hex literal, it should be rejected.
  // We avoid assuming any particular tag table contents by using a clearly invalid token.
  try {
    (void)Exiv2::Internal::tagNumber("not_a_tag", ifdId);
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(Exiv2::ErrorCode::kerInvalidTag, e.code());
  }
}

}  // namespace