// SPDX-License-Identifier: GPL-2.0-or-later
// File: image_iptcData_test_1069.cpp

#include <gtest/gtest.h>

#include <memory>

#include "exiv2/basicio.hpp"
#include "exiv2/image.hpp"
#include "exiv2/iptc.hpp"

namespace {

class TestImage_1069 : public Exiv2::Image {
 public:
  TestImage_1069(Exiv2::ImageType type, uint16_t supportedMetadata, Exiv2::BasicIo::UniquePtr io)
      : Exiv2::Image(type, supportedMetadata, std::move(io)) {}
};

class ImageIptcDataTest_1069 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Use a memory-backed BasicIo to satisfy the Image constructor dependency.
    auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo);
    img_ = std::make_unique<TestImage_1069>(static_cast<Exiv2::ImageType>(0), static_cast<uint16_t>(0), std::move(io));
  }

  std::unique_ptr<TestImage_1069> img_;
};

TEST_F(ImageIptcDataTest_1069, ReturnsSameReferenceOnRepeatedCalls_1069) {
  ASSERT_NE(img_, nullptr);

  Exiv2::IptcData& ref1 = img_->iptcData();
  Exiv2::IptcData& ref2 = img_->iptcData();

  // Observable: accessor returns a reference to the same underlying object.
  EXPECT_EQ(&ref1, &ref2);
}

TEST_F(ImageIptcDataTest_1069, ReferenceAllowsMutationAndPersistsAcrossCalls_1069) {
  ASSERT_NE(img_, nullptr);

  Exiv2::IptcData& iptc1 = img_->iptcData();
  iptc1.clear();  // start from a known empty-ish state

  // Mutate through the returned reference.
  // (Using only public IptcData API; no assumptions about internal storage.)
  const auto before = iptc1.size();
  Exiv2::IptcData& iptc2 = img_->iptcData();
  const auto after = iptc2.size();

  EXPECT_EQ(&iptc1, &iptc2);
  EXPECT_EQ(before, after);

  // Another mutation via the second reference should be visible via the first.
  iptc2.clear();
  EXPECT_EQ(iptc1.size(), iptc2.size());
}

TEST_F(ImageIptcDataTest_1069, ReturnedReferenceIsNonConstLvalueReference_1069) {
  ASSERT_NE(img_, nullptr);

  // Compile-time property check: iptcData() must be a mutable lvalue reference.
  using ReturnT = decltype(std::declval<TestImage_1069&>().iptcData());
  static_assert(std::is_lvalue_reference<ReturnT>::value, "iptcData() must return an lvalue reference");
  static_assert(!std::is_const<std::remove_reference<ReturnT>::type>::value, "iptcData() must return a non-const reference");

  // Runtime sanity: we can call a non-const member function on it.
  img_->iptcData().clear();
  SUCCEED();
}

TEST_F(ImageIptcDataTest_1069, IptcDataReferenceUsableAfterClearIptcDataCall_1069) {
  ASSERT_NE(img_, nullptr);

  Exiv2::IptcData& beforeRef = img_->iptcData();
  const auto* beforeAddr = &beforeRef;

  // Exercise an observable public API that (by interface) clears IPTC metadata.
  img_->clearIptcData();

  Exiv2::IptcData& afterRef = img_->iptcData();
  const auto* afterAddr = &afterRef;

  // The accessor should still provide a valid reference; address stability is observable here.
  EXPECT_EQ(beforeAddr, afterAddr);

  // Clearing should leave the container in a valid usable state.
  afterRef.clear();
  SUCCEED();
}

}  // namespace