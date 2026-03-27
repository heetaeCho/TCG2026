// File: test_image_clearComment_1082.cpp
// TEST_ID: 1082

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>

#include <memory>
#include <string>
#include <utility>

namespace {

class TestImageForClearComment_1082 : public Exiv2::Image {
 public:
  TestImageForClearComment_1082(Exiv2::ImageType type, uint16_t supportedMetadata, Exiv2::BasicIo::UniquePtr io)
      : Exiv2::Image(type, supportedMetadata, std::move(io)) {}

  // Implement required virtuals to make the base instantiable in tests.
  // These are not under test here.
  void readMetadata() override {}
  void writeMetadata() override {}
  const std::string mimeType() const override { return "application/x-test"; }
};

class ImageClearCommentTest_1082 : public ::testing::Test {
 protected:
  static std::unique_ptr<TestImageForClearComment_1082> MakeImage() {
    // MemIo is a common in-memory BasicIo implementation in Exiv2.
    // We only need a valid BasicIo instance for construction.
    auto io = Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo);
    return std::unique_ptr<TestImageForClearComment_1082>(
        new TestImageForClearComment_1082(Exiv2::ImageType::none, 0, std::move(io)));
  }
};

}  // namespace

TEST_F(ImageClearCommentTest_1082, ClearsPreviouslySetComment_1082) {
  auto img = MakeImage();
  ASSERT_NE(img, nullptr);

  img->setComment("hello");
  EXPECT_EQ(img->comment(), "hello");

  img->clearComment();
  EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageClearCommentTest_1082, ClearOnEmptyCommentKeepsEmpty_1082) {
  auto img = MakeImage();
  ASSERT_NE(img, nullptr);

  // Default comment should be empty; clearing should keep it empty.
  EXPECT_TRUE(img->comment().empty());

  img->clearComment();
  EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageClearCommentTest_1082, ClearCommentIsIdempotent_1082) {
  auto img = MakeImage();
  ASSERT_NE(img, nullptr);

  img->setComment("once");
  img->clearComment();
  EXPECT_TRUE(img->comment().empty());

  // Second clear should still be safe and keep empty.
  img->clearComment();
  EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageClearCommentTest_1082, ClearsLargeCommentString_1082) {
  auto img = MakeImage();
  ASSERT_NE(img, nullptr);

  const std::string large(64 * 1024, 'x');  // 64 KiB
  img->setComment(large);
  EXPECT_EQ(img->comment().size(), large.size());

  img->clearComment();
  EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageClearCommentTest_1082, ClearsCommentContainingNullBytes_1082) {
  auto img = MakeImage();
  ASSERT_NE(img, nullptr);

  const std::string withNulls = std::string("ab\0cd", 5);
  img->setComment(withNulls);
  EXPECT_EQ(img->comment().size(), withNulls.size());
  EXPECT_EQ(img->comment(), withNulls);

  img->clearComment();
  EXPECT_TRUE(img->comment().empty());
}