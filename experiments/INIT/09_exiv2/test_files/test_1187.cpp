// TEST_ID 1187
// File: test_psdimage_writeMetadata_1187.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "exiv2/psdimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::Throw;

namespace {

class MockBasicIo : public Exiv2::BasicIo {
 public:
  MockBasicIo() = default;

  // Methods used by PsdImage::writeMetadata() implementation.
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(void, transfer, (Exiv2::BasicIo& src), (override));
  MOCK_METHOD(const std::string&, path, (), (override));

  // Provide harmless defaults for other virtual methods (not expected to be used here).
  size_t write(const Exiv2::byte*, size_t) override { return 0; }
  size_t write(Exiv2::BasicIo&) override { return 0; }
  int putb(Exiv2::byte) override { return 0; }
  Exiv2::DataBuf read(size_t) override { return Exiv2::DataBuf(); }
  size_t read(Exiv2::byte*, size_t) override { return 0; }
  int getb() override { return -1; }
  int seek(int64_t, Exiv2::Position) override { return 0; }
  Exiv2::byte* mmap(bool) override { return nullptr; }
  int munmap() override { return 0; }
  const size_t tell() override { return 0; }
  const size_t size() override { return 0; }
  const bool isopen() override { return true; }
  const int error() override { return 0; }
  const bool eof() override { return false; }
  void populateFakeData() override {}

  std::string path_{"mock://psd"};
};

class PsdImageWriteMetadataTest_1187 : public ::testing::Test {
 protected:
  static std::unique_ptr<NiceMock<MockBasicIo>> MakeIo() {
    auto io = std::make_unique<NiceMock<MockBasicIo>>();
    ON_CALL(*io, path()).WillByDefault(ReturnRef(io->path_));
    ON_CALL(*io, open()).WillByDefault(Return(0));
    ON_CALL(*io, close()).WillByDefault(Return(0));
    return io;
  }
};

TEST_F(PsdImageWriteMetadataTest_1187, ThrowsWhenOpenFails_1187) {
  auto io = MakeIo();

  EXPECT_CALL(*io, open()).WillOnce(Return(1));
  EXPECT_CALL(*io, close()).Times(0);
  EXPECT_CALL(*io, transfer(_)).Times(0);

  Exiv2::PsdImage image(std::unique_ptr<Exiv2::BasicIo>(io.release()));

  EXPECT_THROW(image.writeMetadata(), Exiv2::Error);
}

TEST_F(PsdImageWriteMetadataTest_1187, CallsOpenThenCloseThenTransferOnSuccess_1187) {
  auto io = MakeIo();

  // Ensure we can tolerate an additional close() call from any RAII closer.
  {
    InSequence seq;

    EXPECT_CALL(*io, open()).WillOnce(Return(0));

    // First explicit close (before transfer) occurs in sequence.
    EXPECT_CALL(*io, close()).WillOnce(Return(0)).RetiresOnSaturation();

    // transfer should happen after that explicit close.
    EXPECT_CALL(*io, transfer(_)).WillOnce([](Exiv2::BasicIo& src) {
      // Observable, interface-only check: the source is a BasicIo (likely MemIo).
      // We avoid asserting internal details; just ensure it's a valid reference.
      (void)src;
    });
  }

  // Allow any extra close calls (e.g., from IoCloser destructor) without over-specifying.
  EXPECT_CALL(*io, close()).Times(AnyNumber()).WillRepeatedly(Return(0));

  Exiv2::PsdImage image(std::unique_ptr<Exiv2::BasicIo>(io.release()));

  EXPECT_NO_THROW(image.writeMetadata());
}

TEST_F(PsdImageWriteMetadataTest_1187, StillAttemptsTransferEvenIfCloseReturnsError_1187) {
  auto io = MakeIo();

  EXPECT_CALL(*io, open()).WillOnce(Return(0));

  // close() return value is ignored by the shown implementation; it should still call transfer().
  EXPECT_CALL(*io, close()).WillOnce(Return(42)).RetiresOnSaturation();
  EXPECT_CALL(*io, close()).Times(AnyNumber()).WillRepeatedly(Return(0));

  EXPECT_CALL(*io, transfer(_)).Times(1);

  Exiv2::PsdImage image(std::unique_ptr<Exiv2::BasicIo>(io.release()));

  EXPECT_NO_THROW(image.writeMetadata());
}

TEST_F(PsdImageWriteMetadataTest_1187, ClosesIoIfTransferThrows_1187) {
  auto io = MakeIo();

  EXPECT_CALL(*io, open()).WillOnce(Return(0));

  // close() should be called at least once (explicit close before transfer, and/or via RAII).
  EXPECT_CALL(*io, close()).Times(AtLeast(1)).WillRepeatedly(Return(0));

  EXPECT_CALL(*io, transfer(_)).WillOnce(Throw(Exiv2::Error(Exiv2::ErrorCode::kerTransferFailed)));

  Exiv2::PsdImage image(std::unique_ptr<Exiv2::BasicIo>(io.release()));

  EXPECT_THROW(image.writeMetadata(), Exiv2::Error);
}

}  // namespace