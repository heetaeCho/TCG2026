// sanitychecks_checkICCProfile_test_2635.cc
#include <gtest/gtest.h>

#include <lcms2.h>
#include <type_traits>
#include <memory>
#include <string>

// Poppler type alias (GfxLCMSProfilePtr) is expected to be available from GfxState.h in Poppler.
#include "poppler/GfxState.h"

// ---- lcms stubs (to deterministically exercise branches) ----
namespace {

struct LcmsStubState {
  // Intent support toggles:
  // - relative/absolute/saturation are checked with UsedDirection
  // - perceptual is checked with LCMS_USED_AS_OUTPUT (constant), regardless of UsedDirection
  bool relativeSupported = false;
  bool absoluteSupported = false;
  bool saturationSupported = false;
  bool perceptualSupportedWhenOutput = false;

  cmsColorSpaceSignature colorSpace = cmsSigRgbData;
};

LcmsStubState g_lcms;

extern "C" cmsBool my_cmsIsIntentSupported(cmsHPROFILE /*profile*/,
                                          cmsUInt32Number intent,
                                          cmsUInt32Number direction)
{
  switch (intent) {
    case INTENT_RELATIVE_COLORIMETRIC:
      return g_lcms.relativeSupported ? 1 : 0;
    case INTENT_ABSOLUTE_COLORIMETRIC:
      return g_lcms.absoluteSupported ? 1 : 0;
    case INTENT_SATURATION:
      return g_lcms.saturationSupported ? 1 : 0;
    case INTENT_PERCEPTUAL:
      // In the implementation under test, perceptual is queried with LCMS_USED_AS_OUTPUT.
      if (direction == LCMS_USED_AS_OUTPUT) {
        return g_lcms.perceptualSupportedWhenOutput ? 1 : 0;
      }
      return 0;
    default:
      return 0;
  }
}

extern "C" cmsColorSpaceSignature my_cmsGetColorSpace(cmsHPROFILE /*profile*/)
{
  return g_lcms.colorSpace;
}

// Helper to create a valid-looking GfxLCMSProfilePtr without depending on real lcms behavior.
// We do allocate a real profile so the pointer is non-null; our stubbed lcms calls ignore it.
using CmsProfileT = std::remove_pointer_t<cmsHPROFILE>;

GfxLCMSProfilePtr MakeProfilePtr()
{
  cmsHPROFILE h = cmsCreate_sRGBProfile();
  EXPECT_NE(h, nullptr);
  return GfxLCMSProfilePtr(reinterpret_cast<CmsProfileT *>(h),
                           [](CmsProfileT *p) {
                             if (p) {
                               cmsCloseProfile(reinterpret_cast<cmsHPROFILE>(p));
                             }
                           });
}

void ResetStubState()
{
  g_lcms = LcmsStubState{};
}

}  // namespace

// Map the production code's lcms calls to our stubs in THIS translation unit.
#define cmsIsIntentSupported my_cmsIsIntentSupported
#define cmsGetColorSpace     my_cmsGetColorSpace

// Include the implementation file to ensure the macro overrides apply.
#include "TestProjects/poppler/utils/sanitychecks.cc"

#undef cmsIsIntentSupported
#undef cmsGetColorSpace

// ---- Tests ----

class CheckICCProfileTest_2635 : public ::testing::Test {
protected:
  void SetUp() override { ResetStubState(); }
};

TEST_F(CheckICCProfileTest_2635, NullProfilePrintsCouldNotOpenAndReturnsFalse_2635)
{
  testing::internal::CaptureStderr();
  const bool ok = checkICCProfile(GfxLCMSProfilePtr{}, "missing.icc", LCMS_USED_AS_OUTPUT, cmsSigRgbData);
  const std::string err = testing::internal::GetCapturedStderr();

  EXPECT_FALSE(ok);
  EXPECT_NE(err.find("Could not open the ICC profile"), std::string::npos);
  EXPECT_NE(err.find("\"missing.icc\""), std::string::npos);
}

TEST_F(CheckICCProfileTest_2635, UnsupportedIntentsOutputDirectionPrintsNotOutputProfile_2635)
{
  auto profile = MakeProfilePtr();
  // All intents unsupported by default.

  testing::internal::CaptureStderr();
  const bool ok = checkICCProfile(profile, "out.icc", LCMS_USED_AS_OUTPUT, cmsSigRgbData);
  const std::string err = testing::internal::GetCapturedStderr();

  EXPECT_FALSE(ok);
  EXPECT_NE(err.find("is not an output profile"), std::string::npos);
  EXPECT_NE(err.find("\"out.icc\""), std::string::npos);
}

TEST_F(CheckICCProfileTest_2635, UnsupportedIntentsInputDirectionPrintsNotInputProfile_2635)
{
  auto profile = MakeProfilePtr();
  // All intents unsupported by default.

  testing::internal::CaptureStderr();
  const bool ok = checkICCProfile(profile, "in.icc", LCMS_USED_AS_INPUT, cmsSigRgbData);
  const std::string err = testing::internal::GetCapturedStderr();

  EXPECT_FALSE(ok);
  EXPECT_NE(err.find("is not an input profile"), std::string::npos);
  EXPECT_NE(err.find("\"in.icc\""), std::string::npos);
}

TEST_F(CheckICCProfileTest_2635, UnsupportedIntentsOtherDirectionPrintsNotSuitable_2635)
{
  auto profile = MakeProfilePtr();
  // Use a direction value that is neither LCMS_USED_AS_OUTPUT nor LCMS_USED_AS_INPUT.
  const cmsUInt32Number kOtherDirection = 0;

  testing::internal::CaptureStderr();
  const bool ok = checkICCProfile(profile, "other.icc", kOtherDirection, cmsSigRgbData);
  const std::string err = testing::internal::GetCapturedStderr();

  EXPECT_FALSE(ok);
  EXPECT_NE(err.find("is not suitable"), std::string::npos);
  EXPECT_NE(err.find("\"other.icc\""), std::string::npos);
}

TEST_F(CheckICCProfileTest_2635, ColorSpaceMismatchPrintsExpectedSpecificMessage_2635)
{
  auto profile = MakeProfilePtr();

  // Make intents supported so we reach the color space check.
  g_lcms.relativeSupported = true;

  // Return RGB, but expect CMYK.
  g_lcms.colorSpace = cmsSigRgbData;

  testing::internal::CaptureStderr();
  const bool ok = checkICCProfile(profile, "space.icc", LCMS_USED_AS_OUTPUT, cmsSigCmykData);
  const std::string err = testing::internal::GetCapturedStderr();

  EXPECT_FALSE(ok);
  EXPECT_NE(err.find("is not a CMYK profile"), std::string::npos);
  EXPECT_NE(err.find("\"space.icc\""), std::string::npos);
}

TEST_F(CheckICCProfileTest_2635, ReturnsTrueWhenIntentSupportedAndColorSpaceMatches_2635)
{
  auto profile = MakeProfilePtr();

  g_lcms.relativeSupported = true;
  g_lcms.colorSpace = cmsSigRgbData;

  testing::internal::CaptureStderr();
  const bool ok = checkICCProfile(profile, "ok.icc", LCMS_USED_AS_INPUT, cmsSigRgbData);
  const std::string err = testing::internal::GetCapturedStderr();

  EXPECT_TRUE(ok);
  EXPECT_TRUE(err.empty());
}

TEST_F(CheckICCProfileTest_2635, PerceptualIntentOnlyCountsWhenCheckedAsOutput_2635)
{
  auto profile = MakeProfilePtr();

  // Only perceptual is supported, and only when queried with LCMS_USED_AS_OUTPUT.
  g_lcms.perceptualSupportedWhenOutput = true;
  g_lcms.colorSpace = cmsSigRgbData;

  // With UsedDirection == output, perceptual should make the "intent supported" check pass.
  {
    testing::internal::CaptureStderr();
    const bool ok = checkICCProfile(profile, "perceptual_out.icc", LCMS_USED_AS_OUTPUT, cmsSigRgbData);
    const std::string err = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(ok);
    EXPECT_TRUE(err.empty());
  }

  // With UsedDirection == input, the perceptual query in the implementation still uses OUTPUT;
  // our stub only returns true when direction == OUTPUT, so this still passes the intent check.
  // We verify it stays observable (i.e., still returns true here as well).
  {
    testing::internal::CaptureStderr();
    const bool ok = checkICCProfile(profile, "perceptual_in.icc", LCMS_USED_AS_INPUT, cmsSigRgbData);
    const std::string err = testing::internal::GetCapturedStderr();
    EXPECT_TRUE(ok);
    EXPECT_TRUE(err.empty());
  }
}