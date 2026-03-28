// TEST_ID 2205
// File: test_epsimage_ctor_2205.cpp

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string_view>

// Exiv2 public headers
#include <exiv2/basicio.hpp>
#include <exiv2/epsimage.hpp>
#include <exiv2/error.hpp>

namespace {

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

// Mock only external collaborator (BasicIo). Do not simulate internal state.
class MockBasicIo : public Exiv2::BasicIo {
public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(size_t, write, (const Exiv2::byte* data, size_t wcount), (override));
  MOCK_METHOD(size_t, write, (Exiv2::BasicIo& src), (override));
  MOCK_METHOD(int, putb, (Exiv2::byte data), (override));
  MOCK_METHOD(Exiv2::DataBuf, read, (size_t rcount), (override));
  MOCK_METHOD(size_t, read, (Exiv2::byte* buf, size_t rcount), (override));
  MOCK_METHOD(int, getb, (), (override));
  MOCK_METHOD(void, transfer, (Exiv2::BasicIo& src), (override));
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

class EpsImageCtorTest_2205 : public ::testing::Test {
protected:
  static constexpr std::string_view kExpectedBlank =
      "%!PS-Adobe-3.0 EPSF-3.0\n%%BoundingBox: 0 0 0 0\n";
};

TEST_F(EpsImageCtorTest_2205, CreateFalse_DoesNotOpenOrWrite_2205) {
  auto io = std::make_unique<StrictMock<MockBasicIo>>();

  // If create == false, constructor should not open/write.
  EXPECT_CALL(*io, open()).Times(0);
  EXPECT_CALL(*io, write(_, _)).Times(0);

  EXPECT_NO_THROW({
    Exiv2::EpsImage img(std::move(io), /*create=*/false);
    (void)img;
  });
}

TEST_F(EpsImageCtorTest_2205, CreateTrue_OpenFails_DoesNotWriteAndDoesNotThrow_2205) {
  auto io = std::make_unique<StrictMock<MockBasicIo>>();

  // If open() != 0, constructor should not attempt to write blank EPS.
  EXPECT_CALL(*io, open()).Times(1).WillOnce(Return(1));
  EXPECT_CALL(*io, write(_, _)).Times(0);

  EXPECT_NO_THROW({
    Exiv2::EpsImage img(std::move(io), /*create=*/true);
    (void)img;
  });
}

TEST_F(EpsImageCtorTest_2205, CreateTrue_OpenSucceeds_WritesBlankOnce_2205) {
  auto io = std::make_unique<StrictMock<MockBasicIo>>();

  EXPECT_CALL(*io, open()).Times(1).WillOnce(Return(0));

  // Verify external interaction: write called with the expected byte count.
  EXPECT_CALL(*io, write(_, kExpectedBlank.size()))
      .Times(1)
      .WillOnce(Return(kExpectedBlank.size()));

  EXPECT_NO_THROW({
    Exiv2::EpsImage img(std::move(io), /*create=*/true);
    (void)img;
  });
}

TEST_F(EpsImageCtorTest_2205, CreateTrue_OpenSucceeds_WriteShort_ThrowsError_2205) {
  auto io = std::make_unique<StrictMock<MockBasicIo>>();

  EXPECT_CALL(*io, open()).Times(1).WillOnce(Return(0));

  // Boundary/error: write returns fewer bytes than requested => observable exception.
  EXPECT_CALL(*io, write(_, kExpectedBlank.size()))
      .Times(1)
      .WillOnce(Return(kExpectedBlank.size() - 1));

  EXPECT_THROW(
      {
        Exiv2::EpsImage img(std::move(io), /*create=*/true);
        (void)img;
      },
      Exiv2::Error);
}

TEST_F(EpsImageCtorTest_2205, CreateTrue_OpenSucceeds_WriteZero_ThrowsError_2205) {
  auto io = std::make_unique<StrictMock<MockBasicIo>>();

  EXPECT_CALL(*io, open()).Times(1).WillOnce(Return(0));
  EXPECT_CALL(*io, write(_, kExpectedBlank.size())).Times(1).WillOnce(Return(0u));

  EXPECT_THROW(
      {
        Exiv2::EpsImage img(std::move(io), /*create=*/true);
        (void)img;
      },
      Exiv2::Error);
}

}  // namespace