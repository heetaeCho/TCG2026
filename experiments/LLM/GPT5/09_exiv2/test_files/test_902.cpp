// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_olympusmn_printEq0x0301_902.cpp

#include <gtest/gtest.h>

#include <exiv2/exiv2.hpp>

// Internal header (expected to exist in Exiv2 source tree)
#include "olympusmn_int.hpp"

#include <sstream>
#include <vector>

namespace {

using Exiv2::byte;

class OlympusMakerNotePrintEq0x0301Test_902 : public ::testing::Test {
 protected:
  Exiv2::Internal::OlympusMakerNote uut_;

  static Exiv2::Value::UniquePtr makeValue(Exiv2::TypeId typeId, const std::vector<byte>& raw) {
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(typeId);
    EXPECT_NE(v.get(), nullptr);
    // ByteOrder is irrelevant for unsignedByte, but required by the interface.
    ASSERT_NO_THROW(v->read(raw.data(), static_cast<long>(raw.size()), Exiv2::littleEndian));
    return v;
  }

  static std::string streamValue(const Exiv2::Value& v) {
    std::ostringstream os;
    os << v;
    return os.str();
  }

  std::string callPrint(const Exiv2::Value& v) {
    std::ostringstream os;
    uut_.printEq0x0301(os, v, nullptr);
    return os.str();
  }
};

TEST_F(OlympusMakerNotePrintEq0x0301Test_902, PrintsNoneForKnownCode00_902) {
  // 6 unsigned bytes; code uses element 0 and 2.
  auto v = makeValue(Exiv2::unsignedByte, std::vector<byte>{0, 0, 0, 0, 0, 0});

  const std::string out = callPrint(*v);
  EXPECT_EQ("None", out);
}

TEST_F(OlympusMakerNotePrintEq0x0301Test_902, PrintsEC14TeleconverterForKnownCode0004_902) {
  auto v = makeValue(Exiv2::unsignedByte, std::vector<byte>{0, 0, 4, 0, 0, 0});

  const std::string out = callPrint(*v);
  EXPECT_EQ("Olympus Zuiko Digital EC-14 1.4x Teleconverter", out);
}

TEST_F(OlympusMakerNotePrintEq0x0301Test_902, PrintsEX25ExtensionTubeForKnownCode0008_902) {
  auto v = makeValue(Exiv2::unsignedByte, std::vector<byte>{0, 0, 8, 0, 0, 0});

  const std::string out = callPrint(*v);
  EXPECT_EQ("Olympus EX-25 Extension Tube", out);
}

TEST_F(OlympusMakerNotePrintEq0x0301Test_902, PrintsEC20TeleconverterForKnownCode0016_902) {
  auto v = makeValue(Exiv2::unsignedByte, std::vector<byte>{0, 0, 16, 0, 0, 0});

  const std::string out = callPrint(*v);
  EXPECT_EQ("Olympus Zuiko Digital EC-20 2.0x Teleconverter", out);
}

TEST_F(OlympusMakerNotePrintEq0x0301Test_902, FallsBackToValueStreamForUnknownCode_902) {
  // Unknown combination (0, 3) at indices (0,2)
  auto v = makeValue(Exiv2::unsignedByte, std::vector<byte>{0, 0, 3, 0, 0, 0});

  const std::string expected = streamValue(*v);
  const std::string out = callPrint(*v);

  EXPECT_EQ(expected, out);
}

TEST_F(OlympusMakerNotePrintEq0x0301Test_902, FallsBackWhenCountIsNotSix_Boundary_902) {
  auto v = makeValue(Exiv2::unsignedByte, std::vector<byte>{0, 0, 4, 0, 0});  // count != 6

  const std::string expected = streamValue(*v);
  const std::string out = callPrint(*v);

  EXPECT_EQ(expected, out);
}

TEST_F(OlympusMakerNotePrintEq0x0301Test_902, FallsBackWhenTypeIsNotUnsignedByte_ErrorCase_902) {
  // 6 unsignedShort values => 12 bytes total (arbitrary data).
  auto v = makeValue(Exiv2::unsignedShort, std::vector<byte>{0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0});

  const std::string expected = streamValue(*v);
  const std::string out = callPrint(*v);

  EXPECT_EQ(expected, out);
}

}  // namespace