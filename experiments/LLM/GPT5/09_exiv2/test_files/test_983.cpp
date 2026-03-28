// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for: Exiv2::newMrwInstance (mrwimage.cpp)
// The TEST_ID is 983

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/mrwimage.hpp>  // declares Exiv2::newMrwInstance / MrwImage factory

#include <cstdint>
#include <memory>
#include <vector>

namespace {

// Helper: build a MemIo containing arbitrary bytes (invalid MRW on purpose).
static Exiv2::BasicIo::UniquePtr makeMemIo(const std::vector<Exiv2::byte>& bytes) {
  // Exiv2::MemIo commonly supports construction from (const byte*, long).
  return Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo(bytes.data(), static_cast<long>(bytes.size())));
}

class MrwImageFactoryTest_983 : public ::testing::Test {};

}  // namespace

TEST_F(MrwImageFactoryTest_983, NullIoReturnsNull_983) {
  Exiv2::BasicIo::UniquePtr io;  // nullptr
  auto image = Exiv2::newMrwInstance(std::move(io), /*create=*/false);
  EXPECT_EQ(nullptr, image.get());
}

TEST_F(MrwImageFactoryTest_983, ConsumesUniquePtrEvenWhenReturningNull_983) {
  Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo);
  ASSERT_NE(nullptr, io.get());

  auto image = Exiv2::newMrwInstance(std::move(io), /*create=*/false);

  // Observable caller-side behavior: std::move should leave io empty regardless of outcome.
  EXPECT_EQ(nullptr, io.get());
  EXPECT_EQ(nullptr, image.get());  // empty MemIo should not be a valid MRW image
}

TEST_F(MrwImageFactoryTest_983, InvalidContentReturnsNull_CreateFalse_983) {
  const std::vector<Exiv2::byte> not_mrw = {
      static_cast<Exiv2::byte>('N'), static_cast<Exiv2::byte>('O'),
      static_cast<Exiv2::byte>('T'), static_cast<Exiv2::byte>('M'),
      static_cast<Exiv2::byte>('R'), static_cast<Exiv2::byte>('W'),
  };
  auto io = makeMemIo(not_mrw);

  auto image = Exiv2::newMrwInstance(std::move(io), /*create=*/false);
  EXPECT_EQ(nullptr, image.get());
}

TEST_F(MrwImageFactoryTest_983, InvalidContentReturnsNull_CreateTrue_983) {
  // Boundary/flag-variation: same invalid input, but with create=true.
  const std::vector<Exiv2::byte> not_mrw = {
      0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
  };
  auto io = makeMemIo(not_mrw);

  auto image = Exiv2::newMrwInstance(std::move(io), /*create=*/true);
  EXPECT_EQ(nullptr, image.get());
}