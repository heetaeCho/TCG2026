// File: test_minoltamn_int_printMinoltaSonyDynamicRangeOptimizerMode_1031.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <sstream>
#include <string>

namespace Exiv2::Internal {
// Under test (implemented in ./TestProjects/exiv2/src/minoltamn_int.cpp)
std::ostream& printMinoltaSonyDynamicRangeOptimizerMode(std::ostream& os, const Value& value,
                                                       const ExifData* metadata);
}  // namespace Exiv2::Internal

namespace {

class MinoltaMnIntTest_1031 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeUShortValue(uint16_t v) {
    auto val = Exiv2::Value::create(Exiv2::unsignedShort);
    // Treat as black box: only use public interface.
    // Exiv2 Value::read(string) is part of the public API.
    val->read(std::to_string(static_cast<unsigned int>(v)));
    return val;
  }
};

TEST_F(MinoltaMnIntTest_1031, ReturnsSameStreamReference_1031) {
  auto value = makeUShortValue(0);
  Exiv2::ExifData md;

  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(os, *value, &md);

  EXPECT_EQ(&ret, &os);
}

TEST_F(MinoltaMnIntTest_1031, PrintsOffForZero_1031) {
  auto value = makeUShortValue(0);
  Exiv2::ExifData md;

  std::ostringstream os;
  Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(os, *value, &md);

  EXPECT_NE(os.str().find("Off"), std::string::npos);
}

TEST_F(MinoltaMnIntTest_1031, PrintsStandardForOne_1031) {
  auto value = makeUShortValue(1);
  Exiv2::ExifData md;

  std::ostringstream os;
  Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(os, *value, &md);

  EXPECT_NE(os.str().find("Standard"), std::string::npos);
}

TEST_F(MinoltaMnIntTest_1031, PrintsAdvancedAutoForTwo_1031) {
  auto value = makeUShortValue(2);
  Exiv2::ExifData md;

  std::ostringstream os;
  Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(os, *value, &md);

  EXPECT_NE(os.str().find("Advanced Auto"), std::string::npos);
}

TEST_F(MinoltaMnIntTest_1031, PrintsAdvancedLevelForThree_1031) {
  auto value = makeUShortValue(3);
  Exiv2::ExifData md;

  std::ostringstream os;
  Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(os, *value, &md);

  EXPECT_NE(os.str().find("Advanced Level"), std::string::npos);
}

TEST_F(MinoltaMnIntTest_1031, PrintsAutoFor4097_1031) {
  auto value = makeUShortValue(4097);
  Exiv2::ExifData md;

  std::ostringstream os;
  Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(os, *value, &md);

  EXPECT_NE(os.str().find("Auto"), std::string::npos);
}

TEST_F(MinoltaMnIntTest_1031, AcceptsNullMetadataPointer_1031) {
  auto value = makeUShortValue(1);

  std::ostringstream os;
  std::ostream& ret =
      Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(os, *value, nullptr);

  EXPECT_EQ(&ret, &os);
  // Observable behavior: should still print something meaningful for a known value.
  EXPECT_NE(os.str().find("Standard"), std::string::npos);
}

TEST_F(MinoltaMnIntTest_1031, BoundaryUnknownValueDoesNotCorruptStream_1031) {
  auto value = makeUShortValue(static_cast<uint16_t>(65535));
  Exiv2::ExifData md;

  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(os, *value, &md);

  EXPECT_EQ(&ret, &os);
  EXPECT_TRUE(os.good());
}

}  // namespace