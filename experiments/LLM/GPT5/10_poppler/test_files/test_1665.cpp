// DeviceNRecoder_test_1665.cc
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

#if __has_include("poppler/Stream.h")
#include "poppler/Stream.h"
#include "poppler/Object.h"
#include "poppler/GfxState.h"
#else
#include "Stream.h"
#include "Object.h"
#include "GfxState.h"
#endif

// DeviceNRecoder is implemented in PSOutputDev.cc (not a public header in many builds).
// Including the .cc makes the class visible for black-box tests of its public interface.
#if __has_include("PSOutputDev.cc")
#include "PSOutputDev.cc"
#elif __has_include("poppler/PSOutputDev.cc")
#include "poppler/PSOutputDev.cc"
#else
// If your build system places sources elsewhere, add the correct include path for PSOutputDev.cc.
#include "PSOutputDev.cc"
#endif

namespace {

class DeviceNRecoderTest_1665 : public ::testing::Test {
protected:
  // Keep the backing buffer alive for the lifetime of the stream (MemStream typically references it).
  std::vector<unsigned char> backing_;

  std::unique_ptr<Stream> MakeMemStream(const std::string &data) {
    backing_.assign(data.begin(), data.end());

    Object dict;
    // Poppler's Object API has changed across versions; support common variants.
#if defined(POPPLER_CPP) || defined(POPPLER_OBJECT_H) || defined(OBJECT_H)
    // Try newer Object::null() first when available.
    // If not available, fall back to legacy initNull / objNull.
#endif

#if defined(POPPLER_HAS_OBJECT_NULL) || (defined(__cpp_lib_optional) && __has_include("poppler/Object.h"))
    // Some versions provide Object::null()
    // (If this doesn't compile in your tree, the fallbacks below should.)
    dict = Object::null();
#elif defined(objNull)
    dict = Object(objNull);
#else
    // Legacy: initNull()
    dict.initNull();
#endif

    // Common MemStream constructor used across many Poppler versions:
    // MemStream(unsigned char *bufA, Goffset startA, Goffset lengthA, Object &&dictA)
    return std::unique_ptr<Stream>(
        new MemStream(backing_.data(), 0, (Goffset)backing_.size(), std::move(dict)));
  }

  std::unique_ptr<GfxColorSpace> MakeDeviceRGBColorSpace() {
    // Common Poppler API: GfxColorSpace::create(csDeviceRGB)
    return std::unique_ptr<GfxColorSpace>(GfxColorSpace::create(csDeviceRGB));
  }

  std::unique_ptr<GfxImageColorMap> MakeColorMap8bitRGB() {
    auto cs = MakeDeviceRGBColorSpace();
    // decode may be nullptr (meaning default decode) in many implementations.
    // If your tree requires a non-null decode Object, adjust this helper accordingly.
    auto cmap = std::unique_ptr<GfxImageColorMap>(new GfxImageColorMap(8, /*decode=*/nullptr, cs.get()));
    // GfxImageColorMap stores the colorspace pointer; ownership is usually not transferred.
    // Keep cs alive by releasing it only after cmap is destroyed is tricky; instead, keep cs
    // alive by leaking it intentionally into Poppler ownership where appropriate.
    // Many Poppler implementations treat the colorspace as owned externally; to avoid UAF,
    // release cs and rely on Poppler's internal ownership rules for DeviceRGB.
    cs.release();
    return cmap;
  }
};

TEST_F(DeviceNRecoderTest_1665, GetKindReturnsStrWeird_1665) {
  auto str = MakeMemStream("abcd");
  auto cmap = MakeColorMap8bitRGB();

  DeviceNRecoder recoder(str.get(), /*widthA=*/1, /*heightA=*/1, cmap.get());
  EXPECT_EQ(recoder.getKind(), strWeird);
}

TEST_F(DeviceNRecoderTest_1665, GetKindIsStableAcrossMultipleCalls_1665) {
  auto str = MakeMemStream("xyz");
  auto cmap = MakeColorMap8bitRGB();

  DeviceNRecoder recoder(str.get(), /*widthA=*/1, /*heightA=*/1, cmap.get());

  const StreamKind k1 = recoder.getKind();
  const StreamKind k2 = recoder.getKind();
  const StreamKind k3 = recoder.getKind();

  EXPECT_EQ(k1, strWeird);
  EXPECT_EQ(k2, strWeird);
  EXPECT_EQ(k3, strWeird);
}

TEST_F(DeviceNRecoderTest_1665, GetKindViaBaseClassPointer_1665) {
  auto str = MakeMemStream("data");
  auto cmap = MakeColorMap8bitRGB();

  DeviceNRecoder recoder(str.get(), /*widthA=*/2, /*heightA=*/2, cmap.get());

  // Verify observable polymorphic behavior through Stream interface.
  Stream *asStream = &recoder;
  EXPECT_EQ(asStream->getKind(), strWeird);

  // Also through FilterStream if available via RTTI.
  FilterStream *asFilter = dynamic_cast<FilterStream *>(asStream);
  ASSERT_NE(asFilter, nullptr);
  EXPECT_EQ(asFilter->getKind(), strWeird);
}

TEST_F(DeviceNRecoderTest_1665, BoundarySmallDimensionsStillReportKind_1665) {
  auto str = MakeMemStream("p");
  auto cmap = MakeColorMap8bitRGB();

  DeviceNRecoder recoder(str.get(), /*widthA=*/1, /*heightA=*/1, cmap.get());
  EXPECT_EQ(recoder.getKind(), strWeird);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(DeviceNRecoderTest_1665, DeathOnNullStreamIfCheckedByImplementation_1665) {
  auto cmap = MakeColorMap8bitRGB();

  // If the implementation enforces non-null inputs (assert/abort), this is observable.
  // If it does not, the test will fail; adjust/remove based on your build's behavior.
  ASSERT_DEATH({ DeviceNRecoder recoder(nullptr, 1, 1, cmap.get()); (void)recoder.getKind(); }, ".*");
}

TEST_F(DeviceNRecoderTest_1665, DeathOnNullColorMapIfCheckedByImplementation_1665) {
  auto str = MakeMemStream("q");

  // If the implementation enforces non-null inputs (assert/abort), this is observable.
  // If it does not, the test will fail; adjust/remove based on your build's behavior.
  ASSERT_DEATH({ DeviceNRecoder recoder(str.get(), 1, 1, nullptr); (void)recoder.getKind(); }, ".*");
}
#endif  // GTEST_HAS_DEATH_TEST

}  // namespace