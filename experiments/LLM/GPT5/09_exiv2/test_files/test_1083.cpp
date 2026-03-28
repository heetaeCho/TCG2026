// =================================================================================================
// TEST_ID: 1083
// File: test_image_setComment_1083.cpp
//
// Unit tests for Exiv2::Image::setComment(const std::string&)
// Constraints: treat implementation as black box; verify only observable behavior via public API.
// =================================================================================================

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>

#include "image.hpp"
#include "basicio.hpp"

namespace {

// A small concrete Image for testing. We only need construction + comment()/setComment() behavior.
// If Exiv2::Image is already concrete in your build, this still works (just provides overrides).
class TestImage_1083 : public Exiv2::Image {
 public:
  TestImage_1083(Exiv2::ImageType type, uint16_t supportedMetadata, Exiv2::BasicIo::UniquePtr io)
      : Exiv2::Image(type, supportedMetadata, std::move(io)) {}

  // Provide harmless overrides in case these are pure virtual in some builds/configurations.
  void readMetadata() override {}
  void writeMetadata() override {}
  void printStructure(std::ostream&, Exiv2::PrintStructureOption, size_t) override {}
  const std::string mimeType() override { return "application/x-testimage"; }
};

static std::unique_ptr<TestImage_1083> makeImage_1083() {
  // Use MemIo as a simple in-memory BasicIo implementation (common in Exiv2 tests).
  Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo);
  // Use a conservative type; if your enum differs, adjust accordingly.
  return std::unique_ptr<TestImage_1083>(
      new TestImage_1083(Exiv2::ImageType::none, /*supportedMetadata=*/0, std::move(io)));
}

}  // namespace

class ImageSetCommentTest_1083 : public ::testing::Test {
 protected:
  void SetUp() override { img_ = makeImage_1083(); }
  std::unique_ptr<TestImage_1083> img_;
};

TEST_F(ImageSetCommentTest_1083, SetCommentStoresExactString_1083) {
  const std::string c = "hello world";
  img_->setComment(c);
  EXPECT_EQ(img_->comment(), c);
}

TEST_F(ImageSetCommentTest_1083, SetCommentAllowsEmptyString_1083) {
  img_->setComment(std::string{});
  EXPECT_EQ(img_->comment(), std::string{});
}

TEST_F(ImageSetCommentTest_1083, SetCommentOverwritesPreviousValue_1083) {
  img_->setComment("first");
  EXPECT_EQ(img_->comment(), "first");

  img_->setComment("second");
  EXPECT_EQ(img_->comment(), "second");
}

TEST_F(ImageSetCommentTest_1083, SetCommentHandlesUnicodeBytes_1083) {
  // Store UTF-8 bytes as std::string; validate round-trip equality.
  const std::string c = u8"코멘트 ✅ café";
  img_->setComment(c);
  EXPECT_EQ(img_->comment(), c);
}

TEST_F(ImageSetCommentTest_1083, SetCommentHandlesLargeInput_1083) {
  // Boundary-ish: a large string should be stored and retrievable without truncation.
  std::string big(1024 * 1024, 'x');  // 1 MiB
  big[0] = 'A';
  big[big.size() - 1] = 'Z';

  img_->setComment(big);
  const std::string out = img_->comment();

  EXPECT_EQ(out.size(), big.size());
  EXPECT_EQ(out.front(), 'A');
  EXPECT_EQ(out.back(), 'Z');
  EXPECT_EQ(out, big);
}

TEST_F(ImageSetCommentTest_1083, SetCommentDoesNotMutateInputString_1083) {
  std::string c = "mutable input";
  const std::string before = c;

  img_->setComment(c);

  // Observable requirement: caller's string should remain unchanged.
  EXPECT_EQ(c, before);
  EXPECT_EQ(img_->comment(), before);
}