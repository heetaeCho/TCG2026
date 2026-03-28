// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/memio.hpp>
#include <exiv2/rw2image.hpp>

namespace {

class Rw2InstanceTest_1582 : public ::testing::Test {};

TEST_F(Rw2InstanceTest_1582, ReturnsNullWhenIoIsNull_1582) {
  Exiv2::BasicIo::UniquePtr io;  // nullptr
  Exiv2::Image::UniquePtr image = Exiv2::newRw2Instance(std::move(io), false);
  EXPECT_EQ(nullptr, image.get());
}

TEST_F(Rw2InstanceTest_1582, CreateFlagDoesNotChangeNullBehavior_1582) {
  {
    Exiv2::BasicIo::UniquePtr io;  // nullptr
    Exiv2::Image::UniquePtr image = Exiv2::newRw2Instance(std::move(io), true);
    EXPECT_EQ(nullptr, image.get());
  }
  {
    Exiv2::BasicIo::UniquePtr io;  // nullptr
    Exiv2::Image::UniquePtr image = Exiv2::newRw2Instance(std::move(io), false);
    EXPECT_EQ(nullptr, image.get());
  }
}

TEST_F(Rw2InstanceTest_1582, MovesIoOwnershipAndNonNullImpliesGood_1582) {
  // Boundary/ownership: ensure the UniquePtr is moved into the factory.
  auto mem = std::make_unique<Exiv2::MemIo>();  // empty buffer; success not assumed
  Exiv2::BasicIo::UniquePtr io = std::move(mem);
  ASSERT_NE(nullptr, io.get());

  Exiv2::Image::UniquePtr image = Exiv2::newRw2Instance(std::move(io), false);

  // Observable move effect: moved-from unique_ptr becomes null.
  EXPECT_EQ(nullptr, io.get());

  // Observable factory contract: it only returns non-null when image->good() is true.
  if (image) {
    EXPECT_TRUE(image->good());

    // Type check (observable via RTTI): returned Image is expected to be an Rw2Image.
    auto* asRw2 = dynamic_cast<Exiv2::Rw2Image*>(image.get());
    EXPECT_NE(nullptr, asRw2);
  }
}

}  // namespace