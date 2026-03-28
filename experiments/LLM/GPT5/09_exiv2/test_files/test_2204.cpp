// File: test_xmpsidecar_constructor_2204.cpp
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstring>
#include <memory>
#include <string>

#include "exiv2/basicio.hpp"
#include "exiv2/xmpsidecar.hpp"

namespace {

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

class MockBasicIo : public Exiv2::BasicIo {
 public:
  MOCK_METHOD(int, open, (), (override));
  MOCK_METHOD(int, close, (), (override));
  MOCK_METHOD(size_t, write, (const Exiv2::byte* data, size_t wcount), (override));

  // Provide stubs for commonly pure-virtual-in-real-life implementations if needed.
  // (These are virtual in the interface; tests here don't rely on them.)
};

MATCHER_P2(ByteBufferEq, expected, expected_len, "buffer equals expected bytes") {
  const auto* actual = reinterpret_cast<const unsigned char*>(arg);
  const auto* exp = reinterpret_cast<const unsigned char*>(expected);
  return std::memcmp(actual, exp, expected_len) == 0;
}

// From the prompt (implementation file global): the constructor writes this header when create==true and open()==0.
static constexpr const char kXmlHeader[] =
    "<?xpacket begin=\"\357\273\277\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>\n";
static constexpr size_t kXmlHdrCnt = sizeof(kXmlHeader) - 1;

class XmpSidecarTest_2204 : public ::testing::Test {};

TEST_F(XmpSidecarTest_2204, CreateFalseDoesNotOpenOrWrite_2204) {
  auto io = std::make_unique<StrictMock<MockBasicIo>>();
  auto* io_ptr = io.get();

  // If constructor touches IO when create==false, StrictMock will fail.
  Exiv2::XmpSidecar sidecar(std::move(io), /*create=*/false);

  (void)io_ptr;  // keep for readability; no direct use.
}

TEST_F(XmpSidecarTest_2204, CreateTrueOpenSuccessWritesXmlHeader_2204) {
  auto io = std::make_unique<StrictMock<MockBasicIo>>();
  auto* io_ptr = io.get();

  EXPECT_CALL(*io_ptr, open()).WillOnce(Return(0));
  EXPECT_CALL(*io_ptr,
              write(ByteBufferEq(kXmlHeader, kXmlHdrCnt), kXmlHdrCnt))
      .WillOnce(Return(kXmlHdrCnt));
  // The implementation uses an IoCloser local object only in the success branch,
  // so close() should be called once when open()==0 (via that RAII).
  EXPECT_CALL(*io_ptr, close()).WillOnce(Return(0));

  Exiv2::XmpSidecar sidecar(std::move(io), /*create=*/true);
}

TEST_F(XmpSidecarTest_2204, CreateTrueOpenFailureDoesNotWrite_2204) {
  auto io = std::make_unique<StrictMock<MockBasicIo>>();
  auto* io_ptr = io.get();

  EXPECT_CALL(*io_ptr, open()).WillOnce(Return(1));
  // No write() and no close() expected because the success-branch RAII isn't created.

  Exiv2::XmpSidecar sidecar(std::move(io), /*create=*/true);
}

TEST_F(XmpSidecarTest_2204, CreateTrueOpenSuccessWriteSizeIsExactHeaderCount_2204) {
  auto io = std::make_unique<StrictMock<MockBasicIo>>();
  auto* io_ptr = io.get();

  EXPECT_CALL(*io_ptr, open()).WillOnce(Return(0));
  EXPECT_CALL(*io_ptr, write(_, kXmlHdrCnt)).WillOnce(Return(kXmlHdrCnt));
  EXPECT_CALL(*io_ptr, close()).WillOnce(Return(0));

  Exiv2::XmpSidecar sidecar(std::move(io), /*create=*/true);
}

}  // namespace