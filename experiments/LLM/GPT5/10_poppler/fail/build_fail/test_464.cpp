// TEST_ID = 464
// File: GfxICCBasedColorSpace_getProfile_test.cpp

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>
#include <utility>

#include "poppler/GfxState.h"

// ----------------------------------------------------------------------------
// Test-only helpers / stubs
// ----------------------------------------------------------------------------

namespace {

class DummyColorSpace final : public GfxColorSpace {
public:
  DummyColorSpace() = default;
  ~DummyColorSpace() override = default;

  // Minimal, no-assumption implementations for abstract interface.
  const std::unique_ptr<GfxColorSpace> copy() override { return std::make_unique<DummyColorSpace>(); }

  void getGray(const GfxColor * /*color*/, GfxGray *gray) override
  {
    if (gray) {
      gray->c = 0.0;
    }
  }

  void getRGB(const GfxColor * /*color*/, GfxRGB *rgb) override
  {
    if (rgb) {
      rgb->r = 0.0;
      rgb->g = 0.0;
      rgb->b = 0.0;
    }
  }

  void getCMYK(const GfxColor * /*color*/, GfxCMYK *cmyk) override
  {
    if (cmyk) {
      cmyk->c = 0.0;
      cmyk->m = 0.0;
      cmyk->y = 0.0;
      cmyk->k = 0.0;
    }
  }

  void getDeviceN(const GfxColor * /*color*/, GfxColor * /*deviceN*/) override {}

  void getRGBLine(unsigned char * /*in*/, unsigned int * /*out*/, int /*length*/) override {}
  void getRGBLine(unsigned char * /*in*/, unsigned char * /*out*/, int /*length*/) override {}
  void getRGBXLine(unsigned char * /*in*/, unsigned char * /*out*/, int /*length*/) override {}
  void getCMYKLine(unsigned char * /*in*/, unsigned char * /*out*/, int /*length*/) override {}
  void getDeviceNLine(unsigned char * /*in*/, unsigned char * /*out*/, int /*length*/) override {}

  bool useGetRGBLine() override { return false; }
  bool useGetCMYKLine() override { return false; }
  bool useGetDeviceNLine() override { return false; }

  void getDefaultColor(GfxColor * /*color*/) override {}
  void getDefaultRanges(double * /*decodeLow*/, double * /*decodeRange*/, int /*maxImgPixel*/) override {}

  GfxColorSpaceMode getMode() const override { return csDeviceRGB; }
  int getNComps() const override { return 3; }
};

template <typename T>
struct is_shared_ptr : std::false_type {};
template <typename U>
struct is_shared_ptr<std::shared_ptr<U>> : std::true_type {};

template <typename T>
struct is_unique_ptr : std::false_type {};
template <typename U, typename D>
struct is_unique_ptr<std::unique_ptr<U, D>> : std::true_type {};

// Best-effort way to create a non-null "sentinel" profile value without relying on Poppler internals.
// If we cannot safely construct a non-null value for the concrete T, we will skip the test.
template <typename T>
T MakeSentinelProfileOrSkip()
{
  if constexpr (std::is_pointer_v<T>) {
    return reinterpret_cast<T>(static_cast<uintptr_t>(0x1));
  } else if constexpr (is_shared_ptr<T>::value) {
    using Elem = typename T::element_type;
    // Non-owning shared_ptr with no-op deleter.
    return T(reinterpret_cast<Elem *>(static_cast<uintptr_t>(0x1)), [](Elem *) {});
  } else if constexpr (is_unique_ptr<T>::value) {
    using Ptr = T;
    using Elem = typename Ptr::element_type;
    using Del = typename Ptr::deleter_type;
    if constexpr (std::is_default_constructible_v<Del>) {
      // Non-owning unique_ptr with default-constructed deleter (must be safe/no-op in practice).
      // If Poppler's deleter is not default constructible, we skip above.
      return Ptr(reinterpret_cast<Elem *>(static_cast<uintptr_t>(0x1)), Del{});
    } else {
      GTEST_SKIP() << "Cannot construct a non-null unique_ptr-based profile (deleter not default-constructible).";
    }
  } else {
    GTEST_SKIP() << "Unknown GfxLCMSProfilePtr representation; cannot construct a non-null sentinel value.";
  }
}

} // namespace

// ----------------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------------

class GfxICCBasedColorSpaceTest_464 : public ::testing::Test {
protected:
  static std::unique_ptr<GfxICCBasedColorSpace> MakeSubject()
  {
    Ref ref{};
    auto alt = std::make_unique<DummyColorSpace>();

    // Use the public constructor that accepts an alternate color space.
    return std::make_unique<GfxICCBasedColorSpace>(3, std::move(alt), &ref);
  }
};

TEST_F(GfxICCBasedColorSpaceTest_464, GetProfile_IsStableAcrossCalls_464)
{
  auto cs = MakeSubject();

  const auto p1 = cs->getProfile();
  const auto p2 = cs->getProfile();

  EXPECT_EQ(p1, p2);
}

TEST_F(GfxICCBasedColorSpaceTest_464, SetProfile_ThenGetProfile_ReturnsSameValue_464)
{
  auto cs = MakeSubject();

  using ProfileT = decltype(cs->getProfile());
  ProfileT sentinel = MakeSentinelProfileOrSkip<ProfileT>();

  cs->setProfile(sentinel);

  EXPECT_EQ(cs->getProfile(), sentinel);
}

TEST_F(GfxICCBasedColorSpaceTest_464, SetProfile_CanResetBackToDefaultConstructedValue_464)
{
  auto cs = MakeSubject();

  using ProfileT = decltype(cs->getProfile());
  ProfileT sentinel = MakeSentinelProfileOrSkip<ProfileT>();

  cs->setProfile(sentinel);
  ASSERT_EQ(cs->getProfile(), sentinel);

  ProfileT reset{}; // boundary/reset case (commonly "null" for pointer-like types)
  cs->setProfile(reset);

  EXPECT_EQ(cs->getProfile(), reset);
}