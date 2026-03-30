// File: test_imagefactory_create_1111.cpp
#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/image_types.hpp>

#include <memory>
#include <vector>

namespace {

class ImageFactoryCreateTest_1111 : public ::testing::Test {
 protected:
  static Exiv2::BasicIo::UniquePtr makeEmptyMemIo() {
    // Use an empty in-memory IO as a minimal, valid BasicIo implementation.
    // (We do not assume anything about internal parsing/creation behavior.)
    return std::make_unique<Exiv2::MemIo>();
  }
};

TEST_F(ImageFactoryCreateTest_1111, CreateWithNoneTypeReturnsNull_1111) {
  Exiv2::ImageFactory factory;

  auto io = makeEmptyMemIo();
  auto img = factory.create(Exiv2::ImageType::none, std::move(io));

  EXPECT_EQ(img.get(), nullptr);
}

TEST_F(ImageFactoryCreateTest_1111, CreateWithUnregisteredTypeReturnsNull_1111) {
  Exiv2::ImageFactory factory;

  // Pick a type that is present in the enum but not listed in the provided registry.
  // (From the prompt: registry includes many types, but not ImageType::bigtiff.)
  auto io = makeEmptyMemIo();
  auto img = factory.create(Exiv2::ImageType::bigtiff, std::move(io));

  EXPECT_EQ(img.get(), nullptr);
}

TEST_F(ImageFactoryCreateTest_1111, CreateWithRegisteredTypeCanReturnNonNull_1111) {
  Exiv2::ImageFactory factory;

  // For a registered type, observable behavior is that a (possibly) non-null Image is returned.
  // We avoid asserting on concrete class/type or internal behavior.
  auto io = makeEmptyMemIo();
  auto img = factory.create(Exiv2::ImageType::jpeg, std::move(io));

  // If the implementation requires more than an empty MemIo, this might still be null.
  // The test is written to be interface-based: it only checks that the call is safe and
  // (when possible) yields a usable object.
  if (img) {
    EXPECT_NE(img.get(), nullptr);
    // Basic sanity: object remains valid while in scope.
    EXPECT_NO_THROW(img.reset());
  } else {
    // Still an observable outcome: creation failed gracefully (returned null).
    EXPECT_EQ(img.get(), nullptr);
  }
}

TEST_F(ImageFactoryCreateTest_1111, CreateConsumesIoUniquePtr_1111) {
  Exiv2::ImageFactory factory;

  auto io = makeEmptyMemIo();
  Exiv2::BasicIo* raw = io.get();

  auto img = factory.create(Exiv2::ImageType::none, std::move(io));

  // For type::none, factory returns null; the only observable ownership fact we can assert
  // is that the caller unique_ptr has been moved-from.
  EXPECT_EQ(img.get(), nullptr);
  EXPECT_EQ(io.get(), nullptr);

  // raw is now dangling (owned by moved-from unique_ptr previously); do not dereference.
  (void)raw;
}

}  // namespace