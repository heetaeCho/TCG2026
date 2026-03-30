// SPDX-License-Identifier: (GPL-2.0-or-later OR BSD-3-Clause)
// File: test_image_clearMetadata_1067.cpp

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {

class SpyImage : public Exiv2::Image {
 public:
  explicit SpyImage(Exiv2::BasicIo::UniquePtr io)
      : Exiv2::Image(static_cast<Exiv2::ImageType>(0), /*supportedMetadata=*/0, std::move(io)) {}

  // Configure throwing behavior for exceptional/error-case observability.
  void setThrowOn(const std::string& methodName, bool enabled) {
    throwOn_ = methodName;
    throwEnabled_ = enabled;
  }

  const std::vector<std::string>& calls() const { return calls_; }
  void resetCalls() { calls_.clear(); }

  // Overrides to observe interactions from clearMetadata().
  void clearExifData() override { recordOrThrow("clearExifData"); }
  void clearIptcData() override { recordOrThrow("clearIptcData"); }
  void clearXmpPacket() override { recordOrThrow("clearXmpPacket"); }
  void clearXmpData() override { recordOrThrow("clearXmpData"); }
  void clearComment() override { recordOrThrow("clearComment"); }
  void clearIccProfile() override { recordOrThrow("clearIccProfile"); }

 private:
  void recordOrThrow(const char* name) {
    calls_.push_back(name);
    if (throwEnabled_ && throwOn_ == name) {
      throw std::runtime_error(std::string("boom: ") + name);
    }
  }

  std::vector<std::string> calls_;
  std::string throwOn_;
  bool throwEnabled_{false};
};

class ImageClearMetadataTest_1067 : public ::testing::Test {
 protected:
  static Exiv2::BasicIo::UniquePtr MakeIo() {
    // MemIo is commonly available in Exiv2 and provides an in-memory BasicIo.
    return Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo());
  }

  SpyImage MakeSpy() { return SpyImage(MakeIo()); }
};

}  // namespace

TEST_F(ImageClearMetadataTest_1067, ClearMetadataCallsAllClearMethodsInOrder_1067) {
  auto img = MakeSpy();

  img.clearMetadata();

  const std::vector<std::string> expected = {
      "clearExifData",
      "clearIptcData",
      "clearXmpPacket",
      "clearXmpData",
      "clearComment",
      "clearIccProfile",
  };
  EXPECT_EQ(img.calls(), expected);
}

TEST_F(ImageClearMetadataTest_1067, ClearMetadataCanBeCalledMultipleTimes_1067) {
  auto img = MakeSpy();

  img.clearMetadata();
  const auto first = img.calls();

  img.resetCalls();
  img.clearMetadata();
  const auto second = img.calls();

  EXPECT_EQ(first.size(), 6u);
  EXPECT_EQ(second.size(), 6u);
  EXPECT_EQ(first, second);
}

TEST_F(ImageClearMetadataTest_1067, ClearMetadataPropagatesExceptionAndStopsFurtherCalls_1067) {
  auto img = MakeSpy();
  img.setThrowOn("clearXmpPacket", true);

  EXPECT_THROW(img.clearMetadata(), std::runtime_error);

  // We can observe which interactions happened before the exception was raised.
  const std::vector<std::string> expectedPrefix = {
      "clearExifData",
      "clearIptcData",
      "clearXmpPacket",
  };
  ASSERT_GE(img.calls().size(), expectedPrefix.size());
  EXPECT_TRUE(std::equal(expectedPrefix.begin(), expectedPrefix.end(), img.calls().begin()));

  // If an exception occurs at clearXmpPacket, later methods should not be reached in that call.
  for (size_t i = expectedPrefix.size(); i < img.calls().size(); ++i) {
    EXPECT_NE(img.calls()[i], "clearXmpData");
    EXPECT_NE(img.calls()[i], "clearComment");
    EXPECT_NE(img.calls()[i], "clearIccProfile");
  }
}