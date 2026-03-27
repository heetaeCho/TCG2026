// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <sstream>
#include <string>

// The production code is in ./src/minoltamn_int.cpp. In many Exiv2 builds this
// function is declared in an internal header; to keep this test resilient even
// when that header isn't exported here, we forward-declare the interface exactly.
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyBoolValue(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class MinoltaSonyBoolPrintTest_1027 : public ::testing::Test {
protected:
  static Exiv2::Value::UniquePtr makeUShortValueFromString(const std::string& s) {
    // Exiv2 commonly supports constructing a Value via Value::create(TypeId) and feeding it via read(string).
    // We intentionally do not assume anything beyond those public APIs.
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    EXPECT_NE(v.get(), nullptr);
    if (v) {
      (void)v->read(s);
    }
    return v;
  }

  static std::string printToString(const Exiv2::Value& value, const Exiv2::ExifData* md) {
    std::ostringstream oss;
    Exiv2::Internal::printMinoltaSonyBoolValue(oss, value, md);
    return oss.str();
  }
};

}  // namespace

TEST_F(MinoltaSonyBoolPrintTest_1027, PrintsOffForZero_1027) {
  auto v = makeUShortValueFromString("0");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = printToString(*v, nullptr);
  EXPECT_EQ(out, "Off");
}

TEST_F(MinoltaSonyBoolPrintTest_1027, PrintsOnForOne_1027) {
  auto v = makeUShortValueFromString("1");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = printToString(*v, nullptr);
  EXPECT_EQ(out, "On");
}

TEST_F(MinoltaSonyBoolPrintTest_1027, ReturnsSameStreamReference_1027) {
  auto v = makeUShortValueFromString("1");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream oss;
  std::ostream& ret = Exiv2::Internal::printMinoltaSonyBoolValue(oss, *v, nullptr);

  EXPECT_EQ(&ret, static_cast<std::ostream*>(&oss));
  EXPECT_EQ(oss.str(), "On");
}

TEST_F(MinoltaSonyBoolPrintTest_1027, NullMetadataDoesNotAffectBasicMapping_1027) {
  auto v0 = makeUShortValueFromString("0");
  auto v1 = makeUShortValueFromString("1");
  ASSERT_NE(v0.get(), nullptr);
  ASSERT_NE(v1.get(), nullptr);

  Exiv2::ExifData md;  // provided but not required for this mapping

  const std::string out0_null = printToString(*v0, nullptr);
  const std::string out0_md = printToString(*v0, &md);
  const std::string out1_null = printToString(*v1, nullptr);
  const std::string out1_md = printToString(*v1, &md);

  EXPECT_EQ(out0_null, "Off");
  EXPECT_EQ(out0_md, "Off");
  EXPECT_EQ(out1_null, "On");
  EXPECT_EQ(out1_md, "On");
}

TEST_F(MinoltaSonyBoolPrintTest_1027, DifferentInputsProduceDifferentOutputsForKnownValues_1027) {
  auto v0 = makeUShortValueFromString("0");
  auto v1 = makeUShortValueFromString("1");
  ASSERT_NE(v0.get(), nullptr);
  ASSERT_NE(v1.get(), nullptr);

  const std::string out0 = printToString(*v0, nullptr);
  const std::string out1 = printToString(*v1, nullptr);

  EXPECT_NE(out0, out1);
  EXPECT_EQ(out0, "Off");
  EXPECT_EQ(out1, "On");
}

TEST_F(MinoltaSonyBoolPrintTest_1027, UnknownValueDoesNotMapToOffOrOn_1027) {
  auto v = makeUShortValueFromString("2");
  ASSERT_NE(v.get(), nullptr);

  const std::string out = printToString(*v, nullptr);

  // We avoid assuming the exact fallback formatting for unknown values.
  // The only observable guarantee we test is that "2" does not get mislabeled as the known "Off"/"On".
  EXPECT_FALSE(out.empty());
  EXPECT_NE(out, "Off");
  EXPECT_NE(out, "On");
}