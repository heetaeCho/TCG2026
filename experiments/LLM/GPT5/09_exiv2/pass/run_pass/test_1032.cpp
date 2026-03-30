// File: test_minoltamn_int_printMinoltaSonyPrioritySetupShutterRelease_1032.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <ostream>
#include <sstream>
#include <string>
#include <memory>

namespace Exiv2::Internal {
// Function under test (implemented in src/minoltamn_int.cpp)
std::ostream& printMinoltaSonyPrioritySetupShutterRelease(std::ostream& os, const Exiv2::Value& value,
                                                         const Exiv2::ExifData* metadata);
}  // namespace Exiv2::Internal

namespace {

class MinoltaSonyPrioritySetupShutterReleaseTest_1032 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::Value> makeUShortValueOrFallback_() {
    // In Exiv2, TagDetails printer typically expects an integer-ish Value.
    // Prefer unsignedShort; if not available in this build, fall back to unsignedLong.
    try {
      auto v = Exiv2::Value::create(Exiv2::unsignedShort);
      if (v) return v;
    } catch (...) {
      // fall through
    }
    return Exiv2::Value::create(Exiv2::unsignedLong);
  }

  static std::string print_(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream os;
    Exiv2::Internal::printMinoltaSonyPrioritySetupShutterRelease(os, v, md);
    return os.str();
  }
};

TEST_F(MinoltaSonyPrioritySetupShutterReleaseTest_1032, PrintsKnownValue0_AsAf_1032) {
  auto v = makeUShortValueOrFallback_();
  ASSERT_TRUE(v);

  ASSERT_NO_THROW((void)v->read(std::string("0")));
  EXPECT_NO_THROW({
    const auto out = print_(*v, nullptr);
    EXPECT_FALSE(out.empty());
    EXPECT_NE(out.find("AF"), std::string::npos);
  });
}

TEST_F(MinoltaSonyPrioritySetupShutterReleaseTest_1032, PrintsKnownValue1_AsRelease_1032) {
  auto v = makeUShortValueOrFallback_();
  ASSERT_TRUE(v);

  ASSERT_NO_THROW((void)v->read(std::string("1")));
  EXPECT_NO_THROW({
    const auto out = print_(*v, nullptr);
    EXPECT_FALSE(out.empty());
    EXPECT_NE(out.find("Release"), std::string::npos);
  });
}

TEST_F(MinoltaSonyPrioritySetupShutterReleaseTest_1032, UnknownValue_PrintsSomethingReasonable_1032) {
  auto v = makeUShortValueOrFallback_();
  ASSERT_TRUE(v);

  ASSERT_NO_THROW((void)v->read(std::string("2")));
  EXPECT_NO_THROW({
    const auto out = print_(*v, nullptr);
    EXPECT_FALSE(out.empty());
    // For unknown values, Exiv2 printers often fall back to the numeric value or an "Unknown" string.
    // Accept either, but ensure it isn't incorrectly mapped to known labels.
    const bool has_numeric = (out.find("2") != std::string::npos);
    const bool has_unknown = (out.find("Unknown") != std::string::npos) || (out.find("unknown") != std::string::npos);
    EXPECT_TRUE(has_numeric || has_unknown);
    EXPECT_EQ(out.find("AF"), std::string::npos);
    EXPECT_EQ(out.find("Release"), std::string::npos);
  });
}

TEST_F(MinoltaSonyPrioritySetupShutterReleaseTest_1032, WithMetadataPointer_DoesNotCrash_1032) {
  auto v = makeUShortValueOrFallback_();
  ASSERT_TRUE(v);

  Exiv2::ExifData md;
  ASSERT_NO_THROW((void)v->read(std::string("0")));

  EXPECT_NO_THROW({
    const auto out = print_(*v, &md);
    EXPECT_FALSE(out.empty());
    EXPECT_NE(out.find("AF"), std::string::npos);
  });
}

TEST_F(MinoltaSonyPrioritySetupShutterReleaseTest_1032, EmptyValue_DoesNotThrow_1032) {
  auto v = makeUShortValueOrFallback_();
  ASSERT_TRUE(v);

  // Intentionally do not populate the Value. The behavior is implementation-defined;
  // we only verify it is safe and produces some output (or at least doesn't throw).
  EXPECT_NO_THROW({
    const auto out = print_(*v, nullptr);
    (void)out;  // output may be empty depending on printer behavior
  });
}

}  // namespace