// TEST_ID 2153
// Unit tests for Exiv2::Jp2Image constructor behavior in jp2image.cpp
//
// Focus: observable interactions with the injected BasicIo when create==true.
// We treat implementation as a black box and only verify externally visible calls.

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "exiv2/jp2image.hpp"
#include "exiv2/basicio.hpp"

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::AtLeast;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

// Minimal mock: only the methods the constructor may touch.
class MockBasicIo : public Exiv2::BasicIo {
 public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(size_t, write, (const Exiv2::byte* data, size_t wcount), (override));

  // Provide no-op defaults for everything else if they ever get called unexpectedly.
  // (We keep StrictMock in tests where we want to ensure no extra calls.)
  MOCK_METHOD(size_t, write, (Exiv2::BasicIo& src), (override));
  MOCK_METHOD(Exiv2::DataBuf, read, (size_t rcount), (override));
  MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
  MOCK_METHOD(int, getb, (), (override));
  MOCK_METHOD(void, transfer, (Exiv2::BasicIo & src), (override));
  MOCK_METHOD(int, seek, (int64_t offset, Exiv2::Position pos), (override));
  MOCK_METHOD(Exiv2::byte*, mmap, (bool isWriteable), (override));
  MOCK_METHOD(int, munmap, (), (override));
  MOCK_METHOD(const size_t, tell, (), (override));
  MOCK_METHOD(const size_t, size, (), (override));
  MOCK_METHOD(const bool, isopen, (), (override));
  MOCK_METHOD(const int, error, (), (override));
  MOCK_METHOD(const bool, eof, (), (override));
  MOCK_METHOD(const std::string&, path, (), (override));
  MOCK_METHOD(void, populateFakeData, (), (override));
};

class Jp2ImageCtorTest_2153 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::BasicIo> MakeIo(MockBasicIo** out_raw) {
    auto p = std::make_unique<StrictMock<MockBasicIo>>();
    *out_raw = p.get();
    // Allow uninteresting calls on methods we don't focus on (keeps tests robust).
    // The constructor under test should only use open/close/write(data,count).
    EXPECT_CALL(**out_raw, write(::testing::An<Exiv2::BasicIo&>())).Times(0);
    EXPECT_CALL(**out_raw, read(_)).Times(0);
    EXPECT_CALL(**out_raw, read(_, _)).Times(0);
    EXPECT_CALL(**out_raw, getb()).Times(0);
    EXPECT_CALL(**out_raw, transfer(_)).Times(0);
    EXPECT_CALL(**out_raw, seek(_, _)).Times(0);
    EXPECT_CALL(**out_raw, mmap(_)).Times(0);
    EXPECT_CALL(**out_raw, munmap()).Times(0);
    EXPECT_CALL(**out_raw, tell()).Times(AnyNumber());
    EXPECT_CALL(**out_raw, size()).Times(AnyNumber());
    EXPECT_CALL(**out_raw, isopen()).Times(AnyNumber());
    EXPECT_CALL(**out_raw, error()).Times(AnyNumber());
    EXPECT_CALL(**out_raw, eof()).Times(AnyNumber());
    EXPECT_CALL(**out_raw, path()).Times(AnyNumber());
    EXPECT_CALL(**out_raw, populateFakeData()).Times(0);

    return p;
  }
};

TEST_F(Jp2ImageCtorTest_2153, CreateFalse_DoesNotOpenOrWrite_2153) {
  MockBasicIo* io_raw = nullptr;
  auto io = MakeIo(&io_raw);

  EXPECT_CALL(*io_raw, open()).Times(0);
  EXPECT_CALL(*io_raw, write(_, _)).Times(0);
  EXPECT_CALL(*io_raw, close()).Times(0);

  Exiv2::Jp2Image img(std::move(io), /*create=*/false);
  (void)img;
}

TEST_F(Jp2ImageCtorTest_2153, CreateTrue_OpenFails_DoesNotWrite_2153) {
  MockBasicIo* io_raw = nullptr;
  auto io = MakeIo(&io_raw);

  EXPECT_CALL(*io_raw, open()).Times(1).WillOnce(Return(1));  // non-zero => fail
  EXPECT_CALL(*io_raw, write(_, _)).Times(0);

  // Whether close() is called on open failure is not guaranteed by the interface,
  // so we do not assert on close() here.
  Exiv2::Jp2Image img(std::move(io), /*create=*/true);
  (void)img;
}

TEST_F(Jp2ImageCtorTest_2153, CreateTrue_OpenOk_WritesBlankAndCloses_2153) {
  MockBasicIo* io_raw = nullptr;
  auto io = MakeIo(&io_raw);

  // Based on the observed constructor: if create==true and open()==0,
  // it writes a fixed "blank jp2" buffer and uses IoCloser to close.
  InSequence seq;

  EXPECT_CALL(*io_raw, open()).Times(1).WillOnce(Return(0));

  EXPECT_CALL(*io_raw, write(_, _))
      .Times(1)
      .WillOnce([](const Exiv2::byte* data, size_t wcount) -> size_t {
        // We cannot access Jp2Blank directly (anonymous namespace), but we can
        // verify the observable write size and that a data pointer was provided.
        EXPECT_NE(data, nullptr);
        EXPECT_EQ(wcount, 249u);  // from provided global Jp2Blank array size
        return wcount;            // report successful write
      });

  EXPECT_CALL(*io_raw, close()).Times(1).WillOnce(Return(0));

  Exiv2::Jp2Image img(std::move(io), /*create=*/true);
  (void)img;
}

TEST_F(Jp2ImageCtorTest_2153, CreateTrue_OpenOk_WriteShort_StillCloses_2153) {
  MockBasicIo* io_raw = nullptr;
  auto io = MakeIo(&io_raw);

  InSequence seq;

  EXPECT_CALL(*io_raw, open()).Times(1).WillOnce(Return(0));

  EXPECT_CALL(*io_raw, write(_, _))
      .Times(1)
      .WillOnce([](const Exiv2::byte* data, size_t wcount) -> size_t {
        EXPECT_NE(data, nullptr);
        EXPECT_EQ(wcount, 249u);
        return wcount - 1;  // short write (error path is only debug-printed)
      });

  // IoCloser should still close even on short write.
  EXPECT_CALL(*io_raw, close()).Times(1).WillOnce(Return(0));

  // Constructor should not throw based on the given code (no exceptions shown).
  EXPECT_NO_THROW({
    Exiv2::Jp2Image img(std::move(io), /*create=*/true);
    (void)img;
  });
}

}  // namespace