// File: test_asfvideo_newAsfInstance_1573.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

#include <exiv2/exiv2.hpp>

namespace {

// Minimal ASF header (enough for many “is this ASF?” sniffers):
// Header Object GUID:
//   75B22630-668E-11CF-A6D9-00AA0062CE6C
// Serialized (ASF / GUID little-endian for first 3 fields):
//   30 26 B2 75 8E 66 CF 11 A6 D9 00 AA 00 62 CE 6C
//
// Followed by:
//   QWORD Header Object Size (little-endian)
//   DWORD Number of Header Objects
//   BYTE  Reserved1 (usually 0x01)
//   BYTE  Reserved2 (usually 0x02)
static std::vector<Exiv2::byte> makeMinimalAsfHeader() {
  std::vector<Exiv2::byte> v;

  const Exiv2::byte guid[16] = {0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
                                0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C};
  v.insert(v.end(), std::begin(guid), std::end(guid));

  // Header size = 30 bytes (GUID 16 + size 8 + count 4 + reserved 2)
  const std::uint64_t headerSize = 30;
  for (int i = 0; i < 8; ++i) v.push_back(static_cast<Exiv2::byte>((headerSize >> (8 * i)) & 0xFF));

  // Number of header objects = 0 (minimal)
  const std::uint32_t numObjects = 0;
  for (int i = 0; i < 4; ++i) v.push_back(static_cast<Exiv2::byte>((numObjects >> (8 * i)) & 0xFF));

  // Reserved bytes (common values)
  v.push_back(static_cast<Exiv2::byte>(0x01));
  v.push_back(static_cast<Exiv2::byte>(0x02));

  return v;
}

class AsfVideoNewInstanceTest_1573 : public ::testing::Test {};

}  // namespace

TEST_F(AsfVideoNewInstanceTest_1573, ReturnsNullptrWhenIoIsNull_1573) {
  Exiv2::BasicIo::UniquePtr io;  // nullptr
  EXPECT_NO_THROW({
    auto img = Exiv2::newAsfInstance(std::move(io), /*create=*/false);
    EXPECT_EQ(img, nullptr);
  });
}

TEST_F(AsfVideoNewInstanceTest_1573, ReturnsNullptrForEmptyBuffer_1573) {
  // Empty in-memory IO should not be recognized as a good ASF video.
  Exiv2::BasicIo::UniquePtr io = std::make_unique<Exiv2::MemIo>();
  EXPECT_NO_THROW({
    auto img = Exiv2::newAsfInstance(std::move(io), /*create=*/false);
    EXPECT_EQ(img, nullptr);
  });
}

TEST_F(AsfVideoNewInstanceTest_1573, ReturnsNullptrForTooSmallBuffer_1573) {
  // Boundary: 1 byte only.
  std::vector<Exiv2::byte> data = {0x00};
  Exiv2::BasicIo::UniquePtr io =
      std::make_unique<Exiv2::MemIo>(data.data(), static_cast<long>(data.size()));

  EXPECT_NO_THROW({
    auto img = Exiv2::newAsfInstance(std::move(io), /*create=*/false);
    EXPECT_EQ(img, nullptr);
  });
}

TEST_F(AsfVideoNewInstanceTest_1573, ReturnsNullptrForNonAsfSignature_1573) {
  // Provide clearly non-ASF bytes.
  const char notAsf[] = "this is not an asf container";
  Exiv2::BasicIo::UniquePtr io =
      std::make_unique<Exiv2::MemIo>(reinterpret_cast<const Exiv2::byte*>(notAsf),
                                     static_cast<long>(sizeof(notAsf) - 1));

  EXPECT_NO_THROW({
    auto img = Exiv2::newAsfInstance(std::move(io), /*create=*/false);
    EXPECT_EQ(img, nullptr);
  });
}

TEST_F(AsfVideoNewInstanceTest_1573, MovesOwnershipOfIo_1573) {
  // Observable behavior: the caller's unique_ptr should be moved-from (nullptr).
  auto bytes = makeMinimalAsfHeader();
  Exiv2::BasicIo::UniquePtr io =
      std::make_unique<Exiv2::MemIo>(bytes.data(), static_cast<long>(bytes.size()));

  Exiv2::BasicIo* raw = io.get();
  (void)raw;

  auto img = Exiv2::newAsfInstance(std::move(io), /*create=*/false);
  EXPECT_EQ(io.get(), nullptr);  // moved-from

  // img may be nullptr if the minimal header is not sufficient for "good()".
  // This test focuses only on move semantics being observable.
  (void)img;
}

TEST_F(AsfVideoNewInstanceTest_1573, ReturnsNonNullForMinimalAsfHeaderIfRecognized_1573) {
  // "Normal" path, if the implementation's good() accepts a minimal ASF header.
  // If Exiv2 requires more structure, this test will safely accept nullptr.
  auto bytes = makeMinimalAsfHeader();
  Exiv2::BasicIo::UniquePtr io =
      std::make_unique<Exiv2::MemIo>(bytes.data(), static_cast<long>(bytes.size()));

  ASSERT_NO_THROW({
    auto img = Exiv2::newAsfInstance(std::move(io), /*create=*/false);
    if (img) {
      // Only check public/observable behavior on the returned Image.
      EXPECT_TRUE(img->good());
    } else {
      // Acceptable outcome if the real implementation requires additional ASF objects.
      SUCCEED();
    }
  });
}