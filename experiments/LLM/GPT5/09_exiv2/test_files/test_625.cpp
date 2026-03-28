// TEST_ID 625
// Unit tests for: Exiv2::Internal::printFujiDriveSetting (from fujimn_int.cpp)
//
// Notes:
// - The function under test has internal linkage (static). To test it as a black box via its
//   observable output, we include the .cpp directly so the symbol is available in this TU.
// - We do NOT re-implement or infer internal logic beyond what is observable through the
//   function’s output formatting and the Value/ExifData public interfaces.

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>

// Include the implementation file to access the static function in this translation unit.
#include "TestProjects/exiv2/src/fujimn_int.cpp"

namespace {

class FujiDriveSettingTest_625 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::Value> MakeULongValue(uint32_t v) {
    auto val = Exiv2::Value::create(Exiv2::unsignedLong);
    // Use the public Value interface to set data; treat internals as black box.
    val->read(std::to_string(v));
    return val;
  }

  static std::unique_ptr<Exiv2::Value> MakeAsciiValue(const std::string& s) {
    auto val = Exiv2::Value::create(Exiv2::asciiString);
    val->read(s);
    return val;
  }

  static uint32_t Pack(byte b1, byte b2, byte b3, byte fps) {
    return static_cast<uint32_t>(b1) |
           (static_cast<uint32_t>(b2) << 8) |
           (static_cast<uint32_t>(b3) << 16) |
           (static_cast<uint32_t>(fps) << 24);
  }

  static std::string Print(const Exiv2::Value& v) {
    std::ostringstream os;
    // Third parameter (ExifData*) is unused in the provided implementation; pass nullptr.
    Exiv2::Internal::printFujiDriveSetting(os, v, nullptr);
    return os.str();
  }

  // Pick one "known" byte1 value from the fujiDriveSettingByte1 lookup table if present.
  // This avoids hard-coding a specific Fuji mapping while still exercising the "known value" path.
  static bool TryGetKnownByte1(byte& out_b1) {
    // fujiDriveSettingByte1 is expected to be a tag detail table with a sentinel at the end.
    // We only rely on its existence and the fact it contains at least one label/value pair.
    for (const auto* p = fujiDriveSettingByte1; p && p->label_ != nullptr; ++p) {
      // Prefer a non-zero value so we can also trigger the "(byte2, byte3)" suffix behavior.
      if (p->val_ != 0) {
        out_b1 = static_cast<byte>(p->val_);
        return true;
      }
    }
    // Fallback: if only zero exists, still allow it.
    for (const auto* p = fujiDriveSettingByte1; p && p->label_ != nullptr; ++p) {
      out_b1 = static_cast<byte>(p->val_);
      return true;
    }
    return false;
  }
};

TEST_F(FujiDriveSettingTest_625, KnownByte1_PrintsNonNumericLabelPrefix_625) {
  byte known_b1 = 0;
  if (!TryGetKnownByte1(known_b1)) {
    GTEST_SKIP() << "fujiDriveSettingByte1 table appears empty or unavailable in this build.";
  }

  auto v = MakeULongValue(Pack(known_b1, /*b2=*/0, /*b3=*/0, /*fps=*/0));
  const std::string out = Print(*v);

  // For known byte1 values, output should not start with the numeric "(<byte1>)" form.
  // (We don't assert the exact label text to avoid locale/translation dependence.)
  ASSERT_FALSE(out.empty());
  EXPECT_NE(out.front(), '(') << "Expected a non-numeric label for a known byte1; got: " << out;
}

TEST_F(FujiDriveSettingTest_625, UnknownByte1_PrintsNumericInParens_625) {
  // Choose a value unlikely to be present; if it is present, adjust to another.
  byte b1 = static_cast<byte>(0xFE);
  if (Exiv2::find(fujiDriveSettingByte1, b1) != nullptr) {
    b1 = static_cast<byte>(0xFD);
  }
  if (Exiv2::find(fujiDriveSettingByte1, b1) != nullptr) {
    b1 = static_cast<byte>(0xFC);
  }

  auto v = MakeULongValue(Pack(b1, /*b2=*/0, /*b3=*/0, /*fps=*/0));
  const std::string out = Print(*v);

  EXPECT_NE(out.find("(" + std::to_string(static_cast<int>(b1)) + ")"), std::string::npos)
      << "Expected numeric (byte1) formatting for unknown byte1; got: " << out;
}

TEST_F(FujiDriveSettingTest_625, FpsNonZero_AppendsFpsSuffix_625) {
  byte known_b1 = 0;
  if (!TryGetKnownByte1(known_b1)) {
    GTEST_SKIP() << "fujiDriveSettingByte1 table appears empty or unavailable in this build.";
  }

  const byte fps = 24;
  auto v = MakeULongValue(Pack(known_b1, /*b2=*/0, /*b3=*/0, fps));
  const std::string out = Print(*v);

  EXPECT_NE(out.find(", 24 fps"), std::string::npos) << "Expected fps suffix; got: " << out;
}

TEST_F(FujiDriveSettingTest_625, FpsZero_DoesNotAppendFpsSuffix_625) {
  byte known_b1 = 0;
  if (!TryGetKnownByte1(known_b1)) {
    GTEST_SKIP() << "fujiDriveSettingByte1 table appears empty or unavailable in this build.";
  }

  auto v = MakeULongValue(Pack(known_b1, /*b2=*/0, /*b3=*/0, /*fps=*/0));
  const std::string out = Print(*v);

  EXPECT_EQ(out.find(" fps"), std::string::npos) << "Did not expect any fps suffix; got: " << out;
}

TEST_F(FujiDriveSettingTest_625, Byte1NonZero_AppendsUnknownTuple_625) {
  // Use an unknown byte1 to ensure we control the printed prefix, but any non-zero byte1
  // should append ", (byte2, byte3)" per the observable formatting.
  byte b1 = static_cast<byte>(0x7B);
  if (Exiv2::find(fujiDriveSettingByte1, b1) != nullptr) {
    b1 = static_cast<byte>(0x7C);
  }

  const byte b2 = 0x12;
  const byte b3 = 0x34;

  auto v = MakeULongValue(Pack(b1, b2, b3, /*fps=*/0));
  const std::string out = Print(*v);

  EXPECT_NE(out.find(", (18, 52)"), std::string::npos)
      << "Expected appended unknown tuple (byte2, byte3); got: " << out;
}

TEST_F(FujiDriveSettingTest_625, Byte1Zero_DoesNotAppendUnknownTuple_625) {
  // Boundary: byte1 == 0 should not append ", (byte2, byte3)" even if b2/b3 are non-zero.
  const byte b1 = 0;
  const byte b2 = 0xAA;
  const byte b3 = 0xBB;

  auto v = MakeULongValue(Pack(b1, b2, b3, /*fps=*/0));
  const std::string out = Print(*v);

  EXPECT_EQ(out.find(", ("), std::string::npos)
      << "Did not expect unknown tuple when byte1==0; got: " << out;
}

TEST_F(FujiDriveSettingTest_625, NonNumericValue_Throws_625) {
  // Exceptional/error case: Value::toUint32() may throw when underlying type/content
  // is not convertible. This is observable through the interface via an exception.
  auto v = MakeAsciiValue("not-a-number");
  EXPECT_THROW((void)Print(*v), Exiv2::Error);
}

}  // namespace