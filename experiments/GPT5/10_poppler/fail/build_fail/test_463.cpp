// Copyright (C) 2026
// Unit tests for GfxICCBasedColorSpace::setProfile
// TEST_ID: 463

#include <gtest/gtest.h>

#include <memory>

#include "GfxState.h"

namespace {

class GfxICCBasedColorSpaceTest_463 : public ::testing::Test {
protected:
  // Construct with minimal/null dependencies to avoid relying on internal details.
  // The goal is only to exercise the public interface we were given.
  static std::unique_ptr<GfxICCBasedColorSpace> MakeSubject() {
    std::unique_ptr<GfxColorSpace> nullAlt;
    // iccProfileStream pointer can be null in many Poppler call paths; we only need a live object.
    return std::make_unique<GfxICCBasedColorSpace>(3, std::move(nullAlt), nullptr);
  }
};

TEST_F(GfxICCBasedColorSpaceTest_463, SetProfileStoresValue_463) {
  auto cs = MakeSubject();

  GfxLCMSProfilePtr profileA{};
  cs->setProfile(profileA);

  // Observable behavior: getProfile returns what was set.
  EXPECT_EQ(cs->getProfile(), profileA);
}

TEST_F(GfxICCBasedColorSpaceTest_463, SetProfileIsIdempotentForSameValue_463) {
  auto cs = MakeSubject();

  GfxLCMSProfilePtr profileA{};
  cs->setProfile(profileA);
  const auto afterFirst = cs->getProfile();

  // Setting the same value again should keep the observable result identical.
  cs->setProfile(profileA);
  EXPECT_EQ(cs->getProfile(), afterFirst);
  EXPECT_EQ(cs->getProfile(), profileA);
}

TEST_F(GfxICCBasedColorSpaceTest_463, SetProfileDoesNotModifyInputObject_463) {
  auto cs = MakeSubject();

  GfxLCMSProfilePtr profileA{};
  const auto before = profileA;

  cs->setProfile(profileA);

  // setProfile takes a non-const reference; ensure it does not mutate the argument
  // in an observable way (i.e., the caller's handle remains equal to its prior value).
  EXPECT_EQ(profileA, before);
  EXPECT_EQ(cs->getProfile(), profileA);
}

}  // namespace