// File: test_jpegbase_2176.cpp
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>
#include <vector>

#include "exiv2/basicio.hpp"
#include "exiv2/jpgimage.hpp"
#include "exiv2/image.hpp"

namespace {

// Test adapter to access JpegBase's protected constructor.
class TestJpegBase_2176 final : public Exiv2::JpegBase {
 public:
  using Exiv2::JpegBase::JpegBase;  // inherit protected ctor, make it public here
};

class JpegBaseTest_2176 : public ::testing::Test {};

static Exiv2::BasicIo::UniquePtr MakeMemIo_2176() {
  // MemIo is a concrete BasicIo in Exiv2.
  return Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo());
}

TEST_F(JpegBaseTest_2176, IsNotCopyConstructible_2176) {
  static_assert(!std::is_copy_constructible_v<TestJpegBase_2176>,
                "JpegBase (via Image) should be non-copyable");
  SUCCEED();
}

TEST_F(JpegBaseTest_2176, TransfersIoOwnership_2176) {
  auto io = MakeMemIo_2176();
  auto* raw = io.get();

  const Exiv2::byte* initData = nullptr;
  const size_t dataSize = 0;

  TestJpegBase_2176 img(Exiv2::ImageType::jpeg, std::move(io), /*create=*/false, initData, dataSize);

  // Observable behavior: Image::io() should refer to the same BasicIo instance passed in.
  EXPECT_EQ(&img.io(), raw);
}

TEST_F(JpegBaseTest_2176, ImageTypeMatchesConstructorArg_2176) {
  auto io = MakeMemIo_2176();

  const Exiv2::byte* initData = nullptr;
  const size_t dataSize = 0;

  TestJpegBase_2176 img(Exiv2::ImageType::jpeg, std::move(io), /*create=*/false, initData, dataSize);

  EXPECT_EQ(img.imageType(), Exiv2::ImageType::jpeg);
}

TEST_F(JpegBaseTest_2176, SupportsExpectedMetadataFlags_2176) {
  auto io = MakeMemIo_2176();

  const Exiv2::byte* initData = nullptr;
  const size_t dataSize = 0;

  TestJpegBase_2176 img(Exiv2::ImageType::jpeg, std::move(io), /*create=*/false, initData, dataSize);

  // Observable behavior through Image public API: supportsMetadata(...) reflects supportedMetadata
  // passed by JpegBase to Image (mdExif|mdIptc|mdXmp|mdComment).
  EXPECT_TRUE(img.supportsMetadata(Exiv2::mdExif));
  EXPECT_TRUE(img.supportsMetadata(Exiv2::mdIptc));
  EXPECT_TRUE(img.supportsMetadata(Exiv2::mdXmp));
  EXPECT_TRUE(img.supportsMetadata(Exiv2::mdComment));
}

TEST_F(JpegBaseTest_2176, CreateFalseDoesNotRequireInitData_2176) {
  auto io = MakeMemIo_2176();

  // Boundary-ish: nullptr + size 0 should be acceptable when create==false.
  EXPECT_NO_THROW({
    TestJpegBase_2176 img(Exiv2::ImageType::jpeg, std::move(io), /*create=*/false,
                          /*initData=*/nullptr, /*dataSize=*/0);
    (void)img;
  });
}

TEST_F(JpegBaseTest_2176, CreateFalseIgnoresInitDataAndSize_2176) {
  auto io = MakeMemIo_2176();

  // Boundary-ish: non-null initData with a non-zero size, but create==false.
  std::vector<Exiv2::byte> init(1024, static_cast<Exiv2::byte>(0xAB));

  EXPECT_NO_THROW({
    TestJpegBase_2176 img(Exiv2::ImageType::jpeg, std::move(io), /*create=*/false,
                          init.data(), init.size());
    (void)img;
  });
}

}  // namespace