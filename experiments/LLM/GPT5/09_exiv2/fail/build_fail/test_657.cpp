// File: test_quicktimevideo_readmetadata_657.cpp
// TEST_ID: 657

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/quicktimevideo.hpp>

#include <memory>
#include <string>

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

// A minimal mock for the observable interactions used by QuickTimeVideo::readMetadata()
// in the provided snippet (open/path/size/error/eof).
class MockBasicIo : public Exiv2::BasicIo {
 public:
  ~MockBasicIo() override = default;

  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(const std::string&, path, (), (override));
  MOCK_METHOD(const size_t, size, (), (override));
  MOCK_METHOD(const int, error, (), (override));
  MOCK_METHOD(const bool, eof, (), (override));

  // Provide default behaviors for other virtuals that might be touched indirectly in some builds.
  // (We keep them non-mocked to avoid over-constraining.)
  size_t write(const Exiv2::byte*, size_t) override { return 0; }
  size_t write(Exiv2::BasicIo&) override { return 0; }
  int putb(Exiv2::byte) override { return 0; }
  Exiv2::DataBuf read(size_t) override { return Exiv2::DataBuf(); }
  size_t read(Exiv2::byte*, size_t) override { return 0; }
  int getb() override { return -1; }
  void transfer(Exiv2::BasicIo&) override {}
  int seek(int64_t, Exiv2::Position) override { return 0; }
  Exiv2::byte* mmap(bool) override { return nullptr; }
  int munmap() override { return 0; }
  const size_t tell() override { return 0; }
  const bool isopen() override { return false; }
  void populateFakeData() override {}
};

class QuickTimeVideoReadMetadataTest_657 : public ::testing::Test {
 protected:
  static constexpr size_t kMaxRecursionDepth = 8;
};

TEST_F(QuickTimeVideoReadMetadataTest_657, ReadMetadataThrowsWhenOpenFails_657) {
  auto io = std::make_unique<StrictMock<MockBasicIo>>();

  static const std::string kPath = "dummy.mov";

  // readMetadata() first calls open(); on failure it throws immediately and uses path() in the error.
  EXPECT_CALL(*io, open()).WillOnce(Return(1));
  EXPECT_CALL(*io, path()).WillOnce(Return(::testing::Ref(kPath)));

  // Ensure we don't accidentally proceed to size()/error()/eof() when open fails.
  EXPECT_CALL(*io, size()).Times(0);
  EXPECT_CALL(*io, error()).Times(0);
  EXPECT_CALL(*io, eof()).Times(0);

  Exiv2::QuickTimeVideo video(std::move(io), kMaxRecursionDepth);

  EXPECT_THROW(video.readMetadata(), Exiv2::Error);
}

TEST_F(QuickTimeVideoReadMetadataTest_657, ReadMetadataOpenFailureDoesNotQuerySize_657) {
  auto io = std::make_unique<StrictMock<MockBasicIo>>();

  static const std::string kEmptyPath;

  EXPECT_CALL(*io, open()).WillOnce(Return(-1));
  EXPECT_CALL(*io, path()).WillOnce(Return(::testing::Ref(kEmptyPath)));

  // Boundary-ish: even if size() would be valid, it must not be queried on open failure.
  EXPECT_CALL(*io, size()).Times(0);

  // Allow close() to be called or not (implementation detail / RAII differences across builds).
  EXPECT_CALL(*io, close()).Times(AnyNumber());

  Exiv2::QuickTimeVideo video(std::move(io), kMaxRecursionDepth);

  EXPECT_THROW(video.readMetadata(), Exiv2::Error);
}

}  // namespace