#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/basicio.hpp"
#include "exiv2/image.hpp"
#include <cstring>

// We need access to isEpsType
namespace Exiv2 {
bool isEpsType(BasicIo& iIo, bool advance);
}

// Mock class for BasicIo
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
  MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
  MOCK_METHOD(Exiv2::byte*, mmap, (bool isWriteable), (override));
  MOCK_METHOD(int, munmap, (), (override));
  MOCK_METHOD(size_t, tell, (), (const, override));
  MOCK_METHOD(size_t, size, (), (const, override));
  MOCK_METHOD(bool, isopen, (), (const, override));
  MOCK_METHOD(int, error, (), (const, override));
  MOCK_METHOD(bool, eof, (), (const, override));
  MOCK_METHOD(const std::string&, path, (), (const, override));
  MOCK_METHOD(void, populateFakeData, (), (override));
};

class IsEpsTypeTest_1756 : public ::testing::Test {
 protected:
  MockBasicIo mockIo;
};

// Test: Valid EPS first line "%!PS-Adobe-3.0 EPSF-3.0" with advance=false
TEST_F(IsEpsTypeTest_1756, ValidEpsFirstLine_NoAdvance_1756) {
  const std::string epsHeader = "%!PS-Adobe-3.0 EPSF-3.0";
  // The bufSize is the max of all epsFirstLine entries' sizes
  // "%!PS-Adobe-3.0 EPSF-3.0 " is 25 chars (with trailing space)
  // So bufSize should be 25
  size_t bufSize = 25;

  Exiv2::DataBuf buf(reinterpret_cast<const Exiv2::byte*>(epsHeader.c_str()), bufSize);
  // Pad remaining bytes with zeros
  std::vector<Exiv2::byte> data(bufSize, 0);
  std::memcpy(data.data(), epsHeader.c_str(), epsHeader.size());
  Exiv2::DataBuf returnBuf(data.data(), bufSize);

  EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, read(bufSize)).WillOnce(testing::Return(returnBuf));
  EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
  // advance=false, so seek should be called to restore position
  EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg)).WillOnce(testing::Return(0));

  bool result = Exiv2::isEpsType(mockIo, false);
  EXPECT_TRUE(result);
}

// Test: Valid EPS first line "%!PS-Adobe-3.0 EPSF-3.0" with advance=true
TEST_F(IsEpsTypeTest_1756, ValidEpsFirstLine_WithAdvance_1756) {
  const std::string epsHeader = "%!PS-Adobe-3.0 EPSF-3.0";
  size_t bufSize = 25;

  std::vector<Exiv2::byte> data(bufSize, 0);
  std::memcpy(data.data(), epsHeader.c_str(), epsHeader.size());
  Exiv2::DataBuf returnBuf(data.data(), bufSize);

  EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, read(bufSize)).WillOnce(testing::Return(returnBuf));
  EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
  // advance=true and matched, so seek should NOT be called
  EXPECT_CALL(mockIo, seek(testing::_, testing::_)).Times(0);

  bool result = Exiv2::isEpsType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: Valid EPS first line with trailing space "%!PS-Adobe-3.0 EPSF-3.0 " with advance=true
TEST_F(IsEpsTypeTest_1756, ValidEpsFirstLineTrailingSpace_WithAdvance_1756) {
  const std::string epsHeader = "%!PS-Adobe-3.0 EPSF-3.0 ";
  size_t bufSize = 25;

  std::vector<Exiv2::byte> data(bufSize, 0);
  std::memcpy(data.data(), epsHeader.c_str(), std::min(epsHeader.size(), bufSize));
  Exiv2::DataBuf returnBuf(data.data(), bufSize);

  EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, read(bufSize)).WillOnce(testing::Return(returnBuf));
  EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, seek(testing::_, testing::_)).Times(0);

  bool result = Exiv2::isEpsType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: Valid EPS 3.1 first line "%!PS-Adobe-3.1 EPSF-3.0" with advance=true
TEST_F(IsEpsTypeTest_1756, ValidEps31FirstLine_WithAdvance_1756) {
  const std::string epsHeader = "%!PS-Adobe-3.1 EPSF-3.0";
  size_t bufSize = 25;

  std::vector<Exiv2::byte> data(bufSize, 0);
  std::memcpy(data.data(), epsHeader.c_str(), std::min(epsHeader.size(), bufSize));
  Exiv2::DataBuf returnBuf(data.data(), bufSize);

  EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, read(bufSize)).WillOnce(testing::Return(returnBuf));
  EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, seek(testing::_, testing::_)).Times(0);

  bool result = Exiv2::isEpsType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: DOS EPS signature with advance=true
TEST_F(IsEpsTypeTest_1756, ValidDosEpsSignature_WithAdvance_1756) {
  size_t bufSize = 25;
  std::vector<Exiv2::byte> data(bufSize, 0);
  // DOS EPS signature: \xC5\xD0\xD3\xC6
  data[0] = 0xC5;
  data[1] = 0xD0;
  data[2] = 0xD3;
  data[3] = 0xC6;
  Exiv2::DataBuf returnBuf(data.data(), bufSize);

  EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, read(bufSize)).WillOnce(testing::Return(returnBuf));
  EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, seek(testing::_, testing::_)).Times(0);

  bool result = Exiv2::isEpsType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: DOS EPS signature with advance=false
TEST_F(IsEpsTypeTest_1756, ValidDosEpsSignature_NoAdvance_1756) {
  size_t bufSize = 25;
  std::vector<Exiv2::byte> data(bufSize, 0);
  data[0] = 0xC5;
  data[1] = 0xD0;
  data[2] = 0xD3;
  data[3] = 0xC6;
  Exiv2::DataBuf returnBuf(data.data(), bufSize);

  EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(42));
  EXPECT_CALL(mockIo, read(bufSize)).WillOnce(testing::Return(returnBuf));
  EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
  // advance=false -> seek to restore
  EXPECT_CALL(mockIo, seek(42, Exiv2::BasicIo::beg)).WillOnce(testing::Return(0));

  bool result = Exiv2::isEpsType(mockIo, false);
  EXPECT_TRUE(result);
}

// Test: Invalid/non-EPS data with advance=false
TEST_F(IsEpsTypeTest_1756, InvalidData_NoAdvance_1756) {
  size_t bufSize = 25;
  std::vector<Exiv2::byte> data(bufSize, 'X');
  Exiv2::DataBuf returnBuf(data.data(), bufSize);

  EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(10));
  EXPECT_CALL(mockIo, read(bufSize)).WillOnce(testing::Return(returnBuf));
  EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
  // Not matched, so seek to restore
  EXPECT_CALL(mockIo, seek(10, Exiv2::BasicIo::beg)).WillOnce(testing::Return(0));

  bool result = Exiv2::isEpsType(mockIo, false);
  EXPECT_FALSE(result);
}

// Test: Invalid/non-EPS data with advance=true
TEST_F(IsEpsTypeTest_1756, InvalidData_WithAdvance_1756) {
  size_t bufSize = 25;
  std::vector<Exiv2::byte> data(bufSize, 'X');
  Exiv2::DataBuf returnBuf(data.data(), bufSize);

  EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(10));
  EXPECT_CALL(mockIo, read(bufSize)).WillOnce(testing::Return(returnBuf));
  EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
  // Not matched, so seek to restore even if advance=true
  EXPECT_CALL(mockIo, seek(10, Exiv2::BasicIo::beg)).WillOnce(testing::Return(0));

  bool result = Exiv2::isEpsType(mockIo, true);
  EXPECT_FALSE(result);
}

// Test: IO error during read
TEST_F(IsEpsTypeTest_1756, IoErrorDuringRead_1756) {
  size_t bufSize = 25;
  Exiv2::DataBuf returnBuf(bufSize);

  EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(5));
  EXPECT_CALL(mockIo, read(bufSize)).WillOnce(testing::Return(returnBuf));
  EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(1));  // IO error
  EXPECT_CALL(mockIo, seek(5, Exiv2::BasicIo::beg)).WillOnce(testing::Return(0));

  bool result = Exiv2::isEpsType(mockIo, true);
  EXPECT_FALSE(result);
}

// Test: Short read (buffer size mismatch)
TEST_F(IsEpsTypeTest_1756, ShortRead_1756) {
  size_t bufSize = 25;
  // Return a buffer that is smaller than expected
  Exiv2::DataBuf returnBuf(10);

  EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, read(bufSize)).WillOnce(testing::Return(returnBuf));
  EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg)).WillOnce(testing::Return(0));

  bool result = Exiv2::isEpsType(mockIo, true);
  EXPECT_FALSE(result);
}

// Test: Partial DOS EPS signature (only 3 of 4 bytes match)
TEST_F(IsEpsTypeTest_1756, PartialDosEpsSignature_1756) {
  size_t bufSize = 25;
  std::vector<Exiv2::byte> data(bufSize, 0);
  data[0] = 0xC5;
  data[1] = 0xD0;
  data[2] = 0xD3;
  data[3] = 0x00;  // Wrong byte
  Exiv2::DataBuf returnBuf(data.data(), bufSize);

  EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, read(bufSize)).WillOnce(testing::Return(returnBuf));
  EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg)).WillOnce(testing::Return(0));

  bool result = Exiv2::isEpsType(mockIo, false);
  EXPECT_FALSE(result);
}

// Test: Almost matching EPS header but slightly different
TEST_F(IsEpsTypeTest_1756, AlmostMatchingEpsHeader_1756) {
  // Use "%!PS-Adobe-3.0 EPSF-3.1" which is not in the known list
  const std::string almostEps = "%!PS-Adobe-3.0 EPSF-3.1";
  size_t bufSize = 25;
  std::vector<Exiv2::byte> data(bufSize, 0);
  std::memcpy(data.data(), almostEps.c_str(), std::min(almostEps.size(), bufSize));
  Exiv2::DataBuf returnBuf(data.data(), bufSize);

  EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, read(bufSize)).WillOnce(testing::Return(returnBuf));
  EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg)).WillOnce(testing::Return(0));

  bool result = Exiv2::isEpsType(mockIo, true);
  EXPECT_FALSE(result);
}

// Test: Empty buffer content (all zeros)
TEST_F(IsEpsTypeTest_1756, EmptyBufferContent_1756) {
  size_t bufSize = 25;
  std::vector<Exiv2::byte> data(bufSize, 0);
  Exiv2::DataBuf returnBuf(data.data(), bufSize);

  EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, read(bufSize)).WillOnce(testing::Return(returnBuf));
  EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg)).WillOnce(testing::Return(0));

  bool result = Exiv2::isEpsType(mockIo, false);
  EXPECT_FALSE(result);
}

// Test: Tell returns non-zero position, verifying restore behavior
TEST_F(IsEpsTypeTest_1756, RestorePositionOnNoMatch_1756) {
  size_t bufSize = 25;
  std::vector<Exiv2::byte> data(bufSize, 'A');
  Exiv2::DataBuf returnBuf(data.data(), bufSize);

  size_t originalPos = 12345;
  EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(originalPos));
  EXPECT_CALL(mockIo, read(bufSize)).WillOnce(testing::Return(returnBuf));
  EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, seek(static_cast<int64_t>(originalPos), Exiv2::BasicIo::beg))
      .WillOnce(testing::Return(0));

  bool result = Exiv2::isEpsType(mockIo, true);
  EXPECT_FALSE(result);
}

// Test: Valid EPS with data following the header
TEST_F(IsEpsTypeTest_1756, ValidEpsWithTrailingData_1756) {
  size_t bufSize = 25;
  std::string fullData = "%!PS-Adobe-3.0 EPSF-3.0\n";
  // Ensure it's exactly bufSize
  while (fullData.size() < bufSize) fullData += 'Z';
  fullData.resize(bufSize);

  Exiv2::DataBuf returnBuf(reinterpret_cast<const Exiv2::byte*>(fullData.data()), bufSize);

  EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, read(bufSize)).WillOnce(testing::Return(returnBuf));
  EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
  // advance=true and matched, no seek
  EXPECT_CALL(mockIo, seek(testing::_, testing::_)).Times(0);

  bool result = Exiv2::isEpsType(mockIo, true);
  EXPECT_TRUE(result);
}

// Test: Zero-size read return (empty DataBuf)
TEST_F(IsEpsTypeTest_1756, ZeroSizeReadReturn_1756) {
  size_t bufSize = 25;
  Exiv2::DataBuf returnBuf;  // empty/default

  EXPECT_CALL(mockIo, tell()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, read(bufSize)).WillOnce(testing::Return(returnBuf));
  EXPECT_CALL(mockIo, error()).WillOnce(testing::Return(0));
  EXPECT_CALL(mockIo, seek(0, Exiv2::BasicIo::beg)).WillOnce(testing::Return(0));

  bool result = Exiv2::isEpsType(mockIo, true);
  EXPECT_FALSE(result);
}
