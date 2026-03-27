// =================================================================================================
// TestProjects/exiv2/src/minoltamn_int_test.cpp
// Unit tests for Exiv2::Internal::printMinoltaSonyTeleconverterModel
//
// The TEST_ID is 1036
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <sstream>
#include <string>

// Forward declaration (treat implementation as black box; test via public signature/observable output)
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyTeleconverterModel(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class MinoltaSonyTeleconverterModelTest_1036 : public ::testing::Test {
protected:
  static Exiv2::Value::UniquePtr makeUShortValue(uint16_t v) {
    // Use Exiv2's factory (do not rely on internal implementations).
    auto val = Exiv2::Value::create(Exiv2::unsignedShort);
    if (!val) return nullptr;
    // Reading from string is part of the Value public interface.
    (void)val->read(std::to_string(v));
    return val;
  }

  static std::string render(uint16_t v, const Exiv2::ExifData* md) {
    auto val = makeUShortValue(v);
    EXPECT_NE(val, nullptr);
    if (!val) return {};

    std::ostringstream os;
    std::ostream& ret = Exiv2::Internal::printMinoltaSonyTeleconverterModel(os, *val, md);

    // Verify the function returns the same stream reference.
    EXPECT_EQ(&ret, &os);
    // Verify the stream remains usable.
    EXPECT_TRUE(os.good());

    return os.str();
  }
};

TEST_F(MinoltaSonyTeleconverterModelTest_1036, PrintsKnownMapping_None_1036) {
  const std::string out = render(/*v=*/0, /*md=*/nullptr);
  ASSERT_FALSE(out.empty());
  EXPECT_NE(out.find("None"), std::string::npos);
}

TEST_F(MinoltaSonyTeleconverterModelTest_1036, PrintsKnownMapping_0x04ContainsExpectedToken_1036) {
  const std::string out = render(/*v=*/4, /*md=*/nullptr);
  ASSERT_FALSE(out.empty());
  // Expect tokens from the provided TagDetails strings (observable output).
  EXPECT_NE(out.find("1.4x"), std::string::npos);
  EXPECT_NE(out.find("0x04"), std::string::npos);
}

TEST_F(MinoltaSonyTeleconverterModelTest_1036, PrintsKnownMapping_0x05ContainsExpectedToken_1036) {
  const std::string out = render(/*v=*/5, /*md=*/nullptr);
  ASSERT_FALSE(out.empty());
  EXPECT_NE(out.find("2x"), std::string::npos);
  EXPECT_NE(out.find("0x05"), std::string::npos);
}

TEST_F(MinoltaSonyTeleconverterModelTest_1036, PrintsKnownMapping_72ContainsExpectedToken_1036) {
  const std::string out = render(/*v=*/72, /*md=*/nullptr);
  ASSERT_FALSE(out.empty());
  EXPECT_NE(out.find("2x"), std::string::npos);
  EXPECT_NE(out.find("APO"), std::string::npos);
}

TEST_F(MinoltaSonyTeleconverterModelTest_1036, UnknownValuePrintsSomethingReasonable_1036) {
  const std::string out = render(/*v=*/999, /*md=*/nullptr);
  ASSERT_FALSE(out.empty());

  // Black-box tolerant check: many Exiv2 printTag implementations either echo the numeric value
  // or print an "Unknown"/similar label. Accept either.
  const bool containsNumber = (out.find("999") != std::string::npos);
  const bool containsUnknown =
      (out.find("Unknown") != std::string::npos) || (out.find("unknown") != std::string::npos);
  EXPECT_TRUE(containsNumber || containsUnknown);
}

TEST_F(MinoltaSonyTeleconverterModelTest_1036, MetadataNullVsEmptyExifDataDoesNotChangeOutputForKnownValue_1036) {
  Exiv2::ExifData md;  // empty metadata, but valid pointer
  const std::string outNull = render(/*v=*/4, /*md=*/nullptr);
  const std::string outPtr = render(/*v=*/4, /*md=*/&md);

  ASSERT_FALSE(outNull.empty());
  ASSERT_FALSE(outPtr.empty());
  // For this tag printer, metadata is not expected to affect output for this specific tag mapping.
  EXPECT_EQ(outNull, outPtr);
}

TEST_F(MinoltaSonyTeleconverterModelTest_1036, ReturnsStreamReferenceAndKeepsStreamGood_1036) {
  auto val = makeUShortValue(/*v=*/160);
  ASSERT_NE(val, nullptr);

  Exiv2::ExifData md;
  std::ostringstream os;
  std::ostream& ret = Exiv2::Internal::printMinoltaSonyTeleconverterModel(os, *val, &md);

  EXPECT_EQ(&ret, &os);
  EXPECT_TRUE(os.good());
  EXPECT_FALSE(os.str().empty());
}

}  // namespace