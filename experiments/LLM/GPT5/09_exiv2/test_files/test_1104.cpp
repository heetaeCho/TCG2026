// =================================================================================================
// TEST_ID: 1104
// Unit tests for Exiv2::ImageFactory::getType(BasicIo&)
// File-under-test: ./TestProjects/exiv2/src/image.cpp
// =================================================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/image_types.hpp>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

namespace {

using ::testing::Return;

class MockBasicIo : public Exiv2::BasicIo {
public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));

  // Provide harmless defaults for other virtuals that might be touched by type-checkers in registry.
  // (We keep them minimal; tests that use MockBasicIo only validate the early-open-failure path.)
  MOCK_METHOD(size_t, write, (const Exiv2::byte*, size_t), (override));
  MOCK_METHOD(size_t, write, (Exiv2::BasicIo&), (override));
  MOCK_METHOD(int, putb, (Exiv2::byte), (override));
  MOCK_METHOD(Exiv2::DataBuf, read, (size_t), (override));
  MOCK_METHOD(size_t, read, (Exiv2::byte*, size_t), (override));
  MOCK_METHOD(int, getb, (), (override));
  MOCK_METHOD(void, transfer, (Exiv2::BasicIo&), (override));
  MOCK_METHOD(int, seek, (int64_t, Exiv2::Position), (override));
  MOCK_METHOD(Exiv2::byte*, mmap, (bool), (override));
  MOCK_METHOD(int, munmap, (), (override));
  MOCK_METHOD(const size_t, tell, (), (override));
  MOCK_METHOD(const size_t, size, (), (override));
  MOCK_METHOD(const bool, isopen, (), (override));
  MOCK_METHOD(const int, error, (), (override));
  MOCK_METHOD(const bool, eof, (), (override));
  MOCK_METHOD(const std::string&, path, (), (override));
  MOCK_METHOD(void, populateFakeData, (), (override));
};

class ImageFactoryGetTypeTest_1104 : public ::testing::Test {
protected:
  static std::unique_ptr<Exiv2::MemIo> MakeMemIo(const std::vector<Exiv2::byte>& bytes) {
    const Exiv2::byte* ptr = bytes.empty() ? nullptr : bytes.data();
    // MemIo typically takes non-const pointer in older Exiv2; const_cast keeps the test portable.
    return std::make_unique<Exiv2::MemIo>(const_cast<Exiv2::byte*>(ptr), bytes.size());
  }
};

TEST_F(ImageFactoryGetTypeTest_1104, OpenFailureReturnsNoneAndDoesNotClose_1104) {
  MockBasicIo io;

  EXPECT_CALL(io, open()).WillOnce(Return(1));
  EXPECT_CALL(io, close()).Times(0);

  Exiv2::ImageFactory factory;
  const auto t = factory.getType(io);

  EXPECT_EQ(t, Exiv2::ImageType::none);
}

TEST_F(ImageFactoryGetTypeTest_1104, OpenSucceedsWithUnknownDataReturnsNoneAndClosesIo_1104) {
  // Data that should not match any known type.
  std::vector<Exiv2::byte> bytes = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
  auto io = MakeMemIo(bytes);

  Exiv2::ImageFactory factory;
  const auto type = factory.getType(*io);

  EXPECT_EQ(type, Exiv2::ImageType::none);
  // IoCloser is expected to close the io before returning.
  EXPECT_FALSE(io->isopen());
}

TEST_F(ImageFactoryGetTypeTest_1104, DetectsGifFromHeader_1104) {
  // Minimal GIF header ("GIF89a") plus a little padding.
  std::vector<Exiv2::byte> bytes = {
      'G','I','F','8','9','a',
      0x01, 0x00, 0x01, 0x00, 0x80, 0x00, 0x00
  };
  auto io = MakeMemIo(bytes);

  Exiv2::ImageFactory factory;
  const auto before = io->tell();
  const auto type = factory.getType(*io);
  const auto after = io->tell();

  EXPECT_EQ(type, Exiv2::ImageType::gif);
  EXPECT_FALSE(io->isopen());
  // getType passes advance=false to the registry check; observable expectation is no net position change.
  EXPECT_EQ(before, after);
}

TEST_F(ImageFactoryGetTypeTest_1104, BoundaryShortBuffersReturnNoneAndClose_1104) {
  Exiv2::ImageFactory factory;

  for (size_t len = 0; len < 6; ++len) {
    std::vector<Exiv2::byte> bytes(len, Exiv2::byte{0});
    auto io = MakeMemIo(bytes);

    const auto before = io->tell();
    const auto type = factory.getType(*io);
    const auto after = io->tell();

    EXPECT_EQ(type, Exiv2::ImageType::none) << "len=" << len;
    EXPECT_FALSE(io->isopen()) << "len=" << len;
    EXPECT_EQ(before, after) << "len=" << len;
  }
}

TEST_F(ImageFactoryGetTypeTest_1104, SubsequentCallsOnSameIoAreIndependent_1104) {
  // Valid GIF header; calling getType twice should consistently report the same type.
  std::vector<Exiv2::byte> bytes = {'G','I','F','8','9','a', 0x00, 0x00, 0x00, 0x00};
  auto io = MakeMemIo(bytes);

  Exiv2::ImageFactory factory;

  const auto t1 = factory.getType(*io);
  EXPECT_EQ(t1, Exiv2::ImageType::gif);
  EXPECT_FALSE(io->isopen());

  const auto t2 = factory.getType(*io);
  EXPECT_EQ(t2, Exiv2::ImageType::gif);
  EXPECT_FALSE(io->isopen());
}

}  // namespace