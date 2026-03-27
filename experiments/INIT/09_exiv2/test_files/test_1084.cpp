// File: test_image_setIccProfile_1084.cpp
// Unit tests for Exiv2::Image::setIccProfile(DataBuf&&, bool)
//
// TEST_ID: 1084

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <vector>

#include "exiv2/image.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"

namespace {

// Minimal concrete Image for testing construction.
// We avoid relying on any ImageType enumerator names by static_cast-ing.
class TestImage_1084 : public Exiv2::Image {
 public:
  explicit TestImage_1084(std::unique_ptr<Exiv2::BasicIo> io)
      : Exiv2::Image(static_cast<Exiv2::ImageType>(0), /*supportedMetadata=*/0, std::move(io)) {}

  ~TestImage_1084() override = default;
};

static std::unique_ptr<TestImage_1084> makeImage_1084() {
  // Image::setIccProfile doesn't require IO interaction, but Image needs a BasicIo.
  // MemIo is a standard Exiv2 in-memory BasicIo implementation.
  auto io = std::make_unique<Exiv2::MemIo>();
  return std::make_unique<TestImage_1084>(std::move(io));
}

static Exiv2::DataBuf makeBuf_1084(const std::vector<Exiv2::byte>& v) {
  if (v.empty()) return Exiv2::DataBuf();
  return Exiv2::DataBuf(v.data(), v.size());
}

}  // namespace

TEST(ImageSetIccProfileTest_1084, SetsProfileWhenValidationOff_1084) {
  auto img = makeImage_1084();

  const std::vector<Exiv2::byte> bytes = {
      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
  };
  Exiv2::DataBuf buf = makeBuf_1084(bytes);

  EXPECT_NO_THROW(img->setIccProfile(std::move(buf), /*bTestValid=*/false));

  EXPECT_TRUE(img->iccProfileDefined());
  EXPECT_EQ(img->iccProfile().size(), bytes.size());
  if (!bytes.empty()) {
    EXPECT_EQ(img->iccProfile().read_uint8(0), bytes[0]);
    EXPECT_EQ(img->iccProfile().read_uint8(bytes.size() - 1), bytes.back());
  }
}

TEST(ImageSetIccProfileTest_1084, EmptyProfileIsAcceptedAndStored_1084) {
  auto img = makeImage_1084();

  Exiv2::DataBuf empty;
  EXPECT_NO_THROW(img->setIccProfile(std::move(empty), /*bTestValid=*/false));

  // Observable behavior: resulting buffer size should be 0.
  EXPECT_EQ(img->iccProfile().size(), 0u);

  // Defined-ness for empty is implementation-defined; accept either.
  // (This assertion is intentionally non-prescriptive.)
  EXPECT_TRUE(img->iccProfile().empty());
}

TEST(ImageSetIccProfileTest_1084, SecondCallReplacesPreviouslyStoredProfile_1084) {
  auto img = makeImage_1084();

  const std::vector<Exiv2::byte> first = {0x01, 0x02, 0x03, 0x04};
  const std::vector<Exiv2::byte> second = {0xaa, 0xbb, 0xcc};

  EXPECT_NO_THROW(img->setIccProfile(makeBuf_1084(first), /*bTestValid=*/false));
  ASSERT_TRUE(img->iccProfileDefined());
  ASSERT_EQ(img->iccProfile().size(), first.size());
  EXPECT_EQ(img->iccProfile().read_uint8(0), first[0]);

  EXPECT_NO_THROW(img->setIccProfile(makeBuf_1084(second), /*bTestValid=*/false));
  EXPECT_TRUE(img->iccProfileDefined());
  EXPECT_EQ(img->iccProfile().size(), second.size());
  if (!second.empty()) {
    EXPECT_EQ(img->iccProfile().read_uint8(0), second[0]);
    EXPECT_EQ(img->iccProfile().read_uint8(second.size() - 1), second.back());
  }
}

TEST(ImageSetIccProfileTest_1084, WithValidationOnProfileIsAssignedEvenIfValidationThrows_1084) {
  auto img = makeImage_1084();

  // Intentionally "junk" data: validation may throw (observable), but assignment happens first.
  const std::vector<Exiv2::byte> junk(32, static_cast<Exiv2::byte>(0x7f));
  Exiv2::DataBuf buf = makeBuf_1084(junk);

  bool threw = false;
  try {
    img->setIccProfile(std::move(buf), /*bTestValid=*/true);
  } catch (...) {
    threw = true;
  }

  // Regardless of whether validation threw, the stored profile should reflect the moved-in data.
  EXPECT_EQ(img->iccProfile().size(), junk.size());
  if (!junk.empty()) {
    EXPECT_EQ(img->iccProfile().read_uint8(0), junk[0]);
    EXPECT_EQ(img->iccProfile().read_uint8(junk.size() - 1), junk.back());
  }

  // Keep the test meaningful without assuming a specific validation behavior.
  SUCCEED() << "Validation " << (threw ? "threw" : "did not throw") << "; profile assignment verified.";
}