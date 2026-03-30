// SPDX-License-Identifier: GPL-2.0-or-later

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

using namespace testing;

// NOTE: The function under test has internal linkage (static) in the production TU.
// To unit-test it as a black box, we include the implementation file so the symbol
// is available within this test translation unit.
//
// This does NOT re-implement any logic; it only makes the existing implementation callable.
#include "../src/fujimn_int.cpp"

namespace {

class FujiFaceElementTypesTest_626 : public ::testing::Test {
 protected:
  static std::string CallPrint(const Exiv2::Value& value) {
    std::ostringstream os;
    Exiv2::Internal::printFujiFaceElementTypes(os, value, /*ExifData*/ nullptr);
    return os.str();
  }

  static Exiv2::Value::UniquePtr MakeAsciiValue(const std::string& s) {
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    // AsciiValue supports read(std::string). We avoid assumptions about internal storage;
    // we only use the public Value interface and observable output.
    v->read(s);
    return v;
  }

  static Exiv2::Value::UniquePtr MakeUShortValue(const std::vector<uint16_t>& xs) {
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    for (uint16_t x : xs) {
      v->setUShort(x);
    }
    return v;
  }

  // Pick a code that is NOT present in the fujiFaceElementType table at runtime.
  // This avoids hard-coding the internal table content while still testing observable behavior.
  static bool FindUnknownTableCode(int64_t* out_code, int64_t start = 0, int64_t end = 4096) {
    for (int64_t code = start; code < end; ++code) {
      if (Exiv2::find(fujiFaceElementType, code) == nullptr) {
        *out_code = code;
        return true;
      }
    }
    return false;
  }

  // Find a digit character '0'..'9' whose numeric value (ch - '0') is NOT present in the table.
  // If all 0..9 are present, we will skip tests that depend on unknown-digit printing.
  static bool FindUnknownDigit(char* out_digit) {
    for (char d = '0'; d <= '9'; ++d) {
      const int64_t code = static_cast<int64_t>(d - '0');
      if (Exiv2::find(fujiFaceElementType, code) == nullptr) {
        *out_digit = d;
        return true;
      }
    }
    return false;
  }
};

TEST_F(FujiFaceElementTypesTest_626, NonSupportedTypePrintsValueWrappedInParens_626) {
  // Any type other than asciiString/unsignedShort should go through the "(value)" path.
  auto v = Exiv2::Value::create(Exiv2::unsignedByte);
  v->setUInt32(7);

  const std::string out = CallPrint(*v);

  ASSERT_GE(out.size(), 2u);
  EXPECT_EQ(out.front(), '(');
  EXPECT_EQ(out.back(), ')');
}

TEST_F(FujiFaceElementTypesTest_626, AsciiEmptyStringProducesNoOutput_626) {
  // For asciiString, elements are decremented by one for the null-escaped terminator.
  // With an empty string, the resulting element count should be zero -> no loop -> no output.
  auto v = MakeAsciiValue("");
  EXPECT_TRUE(CallPrint(*v).empty());
}

TEST_F(FujiFaceElementTypesTest_626, UShortZeroCountProducesNoOutput_626) {
  // A newly created unsignedShort value with no elements should print nothing.
  auto v = Exiv2::Value::create(Exiv2::unsignedShort);
  EXPECT_TRUE(CallPrint(*v).empty());
}

TEST_F(FujiFaceElementTypesTest_626, UShortUnknownCodePrintedAsRawNumberInParens_626) {
  int64_t unknown = -1;
  ASSERT_TRUE(FindUnknownTableCode(&unknown)) << "Could not find an unknown table code in search range";

  // Ensure the unknown fits in uint16_t for setUShort.
  ASSERT_GE(unknown, 0);
  ASSERT_LE(unknown, std::numeric_limits<uint16_t>::max());

  auto v = MakeUShortValue({static_cast<uint16_t>(unknown)});
  const std::string out = CallPrint(*v);

  EXPECT_EQ(out, "(" + std::to_string(unknown) + ")");
}

TEST_F(FujiFaceElementTypesTest_626, UShortMultipleValuesAreSpaceSeparated_626) {
  int64_t unknown1 = -1;
  int64_t unknown2 = -1;
  ASSERT_TRUE(FindUnknownTableCode(&unknown1, 0, 4096));
  ASSERT_TRUE(FindUnknownTableCode(&unknown2, unknown1 + 1, 4096));
  ASSERT_GE(unknown1, 0);
  ASSERT_GE(unknown2, 0);
  ASSERT_LE(unknown1, std::numeric_limits<uint16_t>::max());
  ASSERT_LE(unknown2, std::numeric_limits<uint16_t>::max());

  auto v = MakeUShortValue({static_cast<uint16_t>(unknown1), static_cast<uint16_t>(unknown2)});
  const std::string out = CallPrint(*v);

  EXPECT_EQ(out, "(" + std::to_string(unknown1) + ") (" + std::to_string(unknown2) + ")");
}

TEST_F(FujiFaceElementTypesTest_626, AsciiUnknownDigitPrintsOriginalIntegerValueInParens_626) {
  char d = '\0';
  if (!FindUnknownDigit(&d)) {
    GTEST_SKIP() << "All digit codes 0..9 are present in fujiFaceElementType; cannot force unknown-digit path.";
  }

  // Provide two characters so the implementation's "null escaped" adjustment still leaves elements >= 1.
  // Expected: unknown entries use "(" << value.toInt64(n) << ")" where toInt64(n) for asciiString
  // corresponds to the character code, not (ch - '0').
  std::string s;
  s.push_back(d);
  s.push_back(d);

  auto v = MakeAsciiValue(s);
  const std::string out = CallPrint(*v);

  const int64_t char_code = static_cast<unsigned char>(d);
  EXPECT_EQ(out, "(" + std::to_string(char_code) + ") (" + std::to_string(char_code) + ")");
}

TEST_F(FujiFaceElementTypesTest_626, AsciiSingleUnknownDigitHasNoLeadingOrTrailingSpaces_626) {
  char d = '\0';
  if (!FindUnknownDigit(&d)) {
    GTEST_SKIP() << "All digit codes 0..9 are present in fujiFaceElementType; cannot force unknown-digit path.";
  }

  std::string s;
  s.push_back(d);

  auto v = MakeAsciiValue(s);
  const std::string out = CallPrint(*v);

  ASSERT_FALSE(out.empty());
  EXPECT_NE(out.front(), ' ');
  EXPECT_NE(out.back(), ' ');
  EXPECT_THAT(out, Not(HasSubstr("  ")));  // no double spaces
}

}  // namespace