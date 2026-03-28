// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::PgfImage constructor (pgfimage.cpp)
// Constraints: black-box testing via public interface + observable BasicIo interactions.
// TEST_ID: 2203
// *****************************************************************

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"
#include "exiv2/pgfimage.hpp"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>

namespace {

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Return;
using ::testing::StrictMock;

// Mock collaborator: BasicIo
class MockBasicIo : public Exiv2::BasicIo {
 public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(size_t, write, (const Exiv2::byte* data, size_t wcount), (override));

  // Some toolchains may select other overloads; provide these with permissive defaults.
  MOCK_METHOD(size_t, write, (Exiv2::BasicIo& src), (override));
};

class PgfImageTest_2203 : public ::testing::Test {
 protected:
  static constexpr size_t kPgfBlankSize = 106;  // from provided global pgfBlank size
};

// Normal operation: create=false should not attempt to open/write/close.
TEST_F(PgfImageTest_2203, CreateFalse_DoesNotOpenWriteOrClose_2203) {
  auto mock = std::make_unique<StrictMock<MockBasicIo>>();
  auto* mockPtr = mock.get();

  EXPECT_CALL(*mockPtr, open()).Times(0);
  EXPECT_CALL(*mockPtr, write(_, _)).Times(0);
  EXPECT_CALL(*mockPtr, close()).Times(0);

  EXPECT_NO_THROW({
    Exiv2::PgfImage image(std::move(mock), /*create=*/false);
    (void)image;
  });
}

// Boundary/branch: create=true but open() fails (non-zero) -> no write and no IoCloser close().
TEST_F(PgfImageTest_2203, CreateTrue_OpenFails_NoWriteNoClose_2203) {
  auto mock = std::make_unique<StrictMock<MockBasicIo>>();
  auto* mockPtr = mock.get();

  EXPECT_CALL(*mockPtr, open()).Times(1).WillOnce(Return(1));
  EXPECT_CALL(*mockPtr, write(_, _)).Times(0);
  EXPECT_CALL(*mockPtr, close()).Times(0);

  EXPECT_NO_THROW({
    Exiv2::PgfImage image(std::move(mock), /*create=*/true);
    (void)image;
  });
}

// Normal operation: create=true and open()==0 -> writes pgfBlank (106 bytes) and closes via IoCloser.
TEST_F(PgfImageTest_2203, CreateTrue_OpenSucceeds_WritesPgfBlankAndCloses_2203) {
  auto mock = std::make_unique<StrictMock<MockBasicIo>>();
  auto* mockPtr = mock.get();

  std::vector<Exiv2::byte> captured;
  captured.resize(4, 0);

  EXPECT_CALL(*mockPtr, open()).Times(1).WillOnce(Return(0));
  EXPECT_CALL(*mockPtr, write(_, kPgfBlankSize))
      .Times(1)
      .WillOnce([&](const Exiv2::byte* data, size_t wcount) -> size_t {
        // Capture first 4 bytes of the buffer to verify it's the expected PGF header signature.
        if (data != nullptr && wcount >= 4) {
          std::memcpy(captured.data(), data, 4);
        }
        return wcount;  // simulate full write
      });
  EXPECT_CALL(*mockPtr, close()).Times(1).WillOnce(Return(0));

  EXPECT_NO_THROW({
    Exiv2::PgfImage image(std::move(mock), /*create=*/true);
    (void)image;
  });

  // Based on provided pgfBlank global: first four bytes are {80,71,70,54} == "PGF6".
  EXPECT_EQ(captured[0], static_cast<Exiv2::byte>(80));
  EXPECT_EQ(captured[1], static_cast<Exiv2::byte>(71));
  EXPECT_EQ(captured[2], static_cast<Exiv2::byte>(70));
  EXPECT_EQ(captured[3], static_cast<Exiv2::byte>(54));
}

// Exceptional/edge (observable): open()==0 but write returns short count -> still closes; no throw expected.
TEST_F(PgfImageTest_2203, CreateTrue_ShortWrite_StillCloses_NoThrow_2203) {
  auto mock = std::make_unique<StrictMock<MockBasicIo>>();
  auto* mockPtr = mock.get();

  EXPECT_CALL(*mockPtr, open()).Times(1).WillOnce(Return(0));
  EXPECT_CALL(*mockPtr, write(_, kPgfBlankSize)).Times(1).WillOnce(Return(kPgfBlankSize - 1));
  EXPECT_CALL(*mockPtr, close()).Times(1).WillOnce(Return(0));

  EXPECT_NO_THROW({
    Exiv2::PgfImage image(std::move(mock), /*create=*/true);
    (void)image;
  });
}

// Boundary: open()==0 but write returns 0 -> still closes; no throw expected.
TEST_F(PgfImageTest_2203, CreateTrue_WriteReturnsZero_StillCloses_NoThrow_2203) {
  auto mock = std::make_unique<StrictMock<MockBasicIo>>();
  auto* mockPtr = mock.get();

  EXPECT_CALL(*mockPtr, open()).Times(1).WillOnce(Return(0));
  EXPECT_CALL(*mockPtr, write(_, kPgfBlankSize)).Times(1).WillOnce(Return(0u));
  EXPECT_CALL(*mockPtr, close()).Times(1).WillOnce(Return(0));

  EXPECT_NO_THROW({
    Exiv2::PgfImage image(std::move(mock), /*create=*/true);
    (void)image;
  });
}

}  // namespace