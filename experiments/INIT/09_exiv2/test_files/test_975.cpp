// File: test_pngimage_writeMetadata_975.cpp
// TEST_ID: 975

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "exiv2/pngimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

#include <memory>
#include <stdexcept>
#include <string>

namespace {

class MockBasicIo : public Exiv2::BasicIo {
 public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(void, transfer, (Exiv2::BasicIo& src), (override));

  // PngImage::writeMetadata() may use io_->path() when open() fails.
  const std::string& path() override { return path_; }
  void setPath(std::string p) { path_ = std::move(p); }

  // Provide concrete overrides for pure/virtuals that tests don't use.
  // (They should never be called by these tests; if they are, fail fast.)
  size_t write(const Exiv2::byte*, size_t) override { ADD_FAILURE(); return 0; }
  size_t write(Exiv2::BasicIo&) override { ADD_FAILURE(); return 0; }
  int putb(Exiv2::byte) override { ADD_FAILURE(); return -1; }
  Exiv2::DataBuf read(size_t) override { ADD_FAILURE(); return Exiv2::DataBuf(); }
  size_t read(Exiv2::byte*, size_t) override { ADD_FAILURE(); return 0; }
  int getb() override { ADD_FAILURE(); return -1; }
  int seek(int64_t, Exiv2::Position) override { ADD_FAILURE(); return -1; }
  Exiv2::byte* mmap(bool) override { ADD_FAILURE(); return nullptr; }
  int munmap() override { ADD_FAILURE(); return -1; }
  const size_t tell() override { ADD_FAILURE(); return 0; }
  const size_t size() override { ADD_FAILURE(); return 0; }
  const bool isopen() override { ADD_FAILURE(); return false; }
  const int error() override { ADD_FAILURE(); return 0; }
  const bool eof() override { ADD_FAILURE(); return false; }
  void populateFakeData() override { ADD_FAILURE(); }

 private:
  std::string path_{"mock.png"};
};

class PngImageWriteMetadataTest_975 : public ::testing::Test {
 protected:
  std::unique_ptr<Exiv2::PngImage> makeImage(std::unique_ptr<MockBasicIo> io) {
    // Keep raw pointer only for setting expectations before ownership transfer.
    return std::make_unique<Exiv2::PngImage>(std::move(io), /*create=*/false);
  }
};

TEST_F(PngImageWriteMetadataTest_975, OpenFailureThrowsExiv2Error_975) {
  auto io = std::make_unique<MockBasicIo>();
  io->setPath("cannot-open.png");

  EXPECT_CALL(*io, open()).WillOnce(::testing::Return(1));
  EXPECT_CALL(*io, close()).Times(0);
  EXPECT_CALL(*io, transfer(::testing::_)).Times(0);

  auto image = makeImage(std::move(io));

  // Observable behavior: writeMetadata throws when open() != 0.
  EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

TEST_F(PngImageWriteMetadataTest_975, SuccessfulPathCallsOpenCloseThenTransferWithMemIo_975) {
  auto io = std::make_unique<MockBasicIo>();
  MockBasicIo* ioRaw = io.get();

  auto image = makeImage(std::move(io));

  Exiv2::BasicIo* transferArg = nullptr;

  ::testing::InSequence seq;
  EXPECT_CALL(*ioRaw, open()).WillOnce(::testing::Return(0));
  EXPECT_CALL(*ioRaw, close()).WillOnce(::testing::Return(0));
  EXPECT_CALL(*ioRaw, transfer(::testing::_))
      .WillOnce(::testing::Invoke([&](Exiv2::BasicIo& src) {
        transferArg = &src;
      }));

  // If doWriteMetadata throws internally, this test may fail; however, with the
  // provided interface we only verify observable interactions on the happy path.
  EXPECT_NO_THROW(image->writeMetadata());

  ASSERT_NE(transferArg, nullptr);
  // Observable external interaction: transfer() is invoked with a MemIo source.
  EXPECT_NE(dynamic_cast<Exiv2::MemIo*>(transferArg), nullptr);
}

TEST_F(PngImageWriteMetadataTest_975, CloseReturnValueDoesNotPreventTransfer_975) {
  auto io = std::make_unique<MockBasicIo>();
  MockBasicIo* ioRaw = io.get();

  auto image = makeImage(std::move(io));

  ::testing::InSequence seq;
  EXPECT_CALL(*ioRaw, open()).WillOnce(::testing::Return(0));
  // Boundary-ish: close() returns non-zero; writeMetadata doesn't expose it.
  EXPECT_CALL(*ioRaw, close()).WillOnce(::testing::Return(123));
  EXPECT_CALL(*ioRaw, transfer(::testing::_)).Times(1);

  EXPECT_NO_THROW(image->writeMetadata());
}

TEST_F(PngImageWriteMetadataTest_975, TransferThrowsPropagatesAndCloseHappensBeforeTransfer_975) {
  auto io = std::make_unique<MockBasicIo>();
  MockBasicIo* ioRaw = io.get();

  auto image = makeImage(std::move(io));

  ::testing::InSequence seq;
  EXPECT_CALL(*ioRaw, open()).WillOnce(::testing::Return(0));
  EXPECT_CALL(*ioRaw, close()).WillOnce(::testing::Return(0));
  EXPECT_CALL(*ioRaw, transfer(::testing::_))
      .WillOnce(::testing::Invoke([](Exiv2::BasicIo&) {
        throw std::runtime_error("transfer failed");
      }));

  // Observable behavior: exceptions from transfer() propagate outward.
  EXPECT_THROW(image->writeMetadata(), std::runtime_error);
}

TEST_F(PngImageWriteMetadataTest_975, CloseThrowsPropagatesAndTransferNotCalled_975) {
  auto io = std::make_unique<MockBasicIo>();
  MockBasicIo* ioRaw = io.get();

  auto image = makeImage(std::move(io));

  ::testing::InSequence seq;
  EXPECT_CALL(*ioRaw, open()).WillOnce(::testing::Return(0));
  EXPECT_CALL(*ioRaw, close()).WillOnce(::testing::Invoke([]() -> int {
    throw std::runtime_error("close failed");
  }));
  EXPECT_CALL(*ioRaw, transfer(::testing::_)).Times(0);

  // Observable behavior: exceptions from close() propagate outward.
  EXPECT_THROW(image->writeMetadata(), std::runtime_error);
}

}  // namespace