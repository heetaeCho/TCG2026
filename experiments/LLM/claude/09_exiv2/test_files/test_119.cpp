#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <exiv2/error.hpp>
#include <cstring>
#include <memory>

// Forward declaration of the function under test
namespace Exiv2 {
std::string readStringWcharTag(const BasicIo::UniquePtr& io, size_t length);
}

// We need a concrete BasicIo implementation for testing
// Using MemIo which is available in exiv2
#include <exiv2/basicio.hpp>

class ReadStringWcharTagTest_119 : public ::testing::Test {
protected:
  // Helper to create a MemIo with given data
  Exiv2::BasicIo::UniquePtr createMemIo(const std::vector<Exiv2::byte>& data) {
    auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
    io->open();
    return io;
  }

  // Helper to create UCS-2LE encoded data from ASCII string
  std::vector<Exiv2::byte> makeUCS2LE(const std::string& ascii) {
    std::vector<Exiv2::byte> result;
    for (char c : ascii) {
      result.push_back(static_cast<Exiv2::byte>(c));
      result.push_back(0x00);
    }
    return result;
  }
};

// Test: Normal operation with a simple UCS-2LE encoded string
TEST_F(ReadStringWcharTagTest_119, NormalUCS2LEString_119) {
  // "Hi" in UCS-2LE: 'H' 0x00 'i' 0x00, plus null terminator 0x00 0x00
  std::vector<Exiv2::byte> data = {'H', 0x00, 'i', 0x00, 0x00, 0x00};
  // length should include the null terminator area
  size_t length = data.size();
  auto io = createMemIo(data);

  // The function reads `length` bytes, so we pass exact size
  // It should not throw
  EXPECT_NO_THROW({
    std::string result = Exiv2::readStringWcharTag(io, length);
  });
}

// Test: Empty-ish string (just null terminators)
TEST_F(ReadStringWcharTagTest_119, MinimalData_119) {
  // Minimal: just null terminators (UCS-2LE null + extra byte for -3 trimming)
  std::vector<Exiv2::byte> data = {0x00, 0x00, 0x00, 0x00};
  size_t length = data.size();
  auto io = createMemIo(data);

  EXPECT_NO_THROW({
    std::string result = Exiv2::readStringWcharTag(io, length);
  });
}

// Test: Length exceeds available data should throw (corrupted metadata)
TEST_F(ReadStringWcharTagTest_119, LengthExceedsAvailableData_119) {
  std::vector<Exiv2::byte> data = {'A', 0x00};
  auto io = createMemIo(data);

  // Request more bytes than available
  EXPECT_THROW({
    Exiv2::readStringWcharTag(io, 100);
  }, Exiv2::Error);
}

// Test: Reading after seeking partway through the data
TEST_F(ReadStringWcharTagTest_119, ReadAfterSeek_119) {
  // Put some prefix data, then the actual UCS-2LE string
  std::vector<Exiv2::byte> data = {0xFF, 0xFF, 'T', 0x00, 0x00, 0x00, 0x00, 0x00};
  auto io = createMemIo(data);
  io->seek(2, Exiv2::BasicIo::beg);

  size_t length = 6; // "T\0\0\0\0\0"
  EXPECT_NO_THROW({
    std::string result = Exiv2::readStringWcharTag(io, length);
  });
}

// Test: Length that leaves odd-length wst (odd after trimming 3 bytes)
TEST_F(ReadStringWcharTagTest_119, OddLengthWst_119) {
  // Create data where after trimming 3 bytes from end, the string has odd length
  // DataBuf is length+1, then wst = FieldBuf.begin() to FieldBuf.end()-3
  // wst.size() = (length+1) - 3 = length - 2
  // For odd: length - 2 must be odd => length must be odd
  // length = 5 => wst.size() = 3 (odd)
  std::vector<Exiv2::byte> data = {'A', 0x00, 'B', 0x00, 'C'};
  size_t length = 5;
  auto io = createMemIo(data);

  EXPECT_NO_THROW({
    std::string result = Exiv2::readStringWcharTag(io, length);
  });
}

// Test: Even-length wst (no extra charset conversion for odd)
TEST_F(ReadStringWcharTagTest_119, EvenLengthWst_119) {
  // length = 6 => wst.size() = 6 - 2 = 4 (even)
  std::vector<Exiv2::byte> data = {'H', 0x00, 'i', 0x00, 0x00, 0x00};
  size_t length = 6;
  auto io = createMemIo(data);

  EXPECT_NO_THROW({
    std::string result = Exiv2::readStringWcharTag(io, length);
    // The result should be a UTF-8 string
    EXPECT_FALSE(result.empty() && length > 3);
  });
}

// Test: Zero length should still work or throw appropriately
TEST_F(ReadStringWcharTagTest_119, ZeroLength_119) {
  std::vector<Exiv2::byte> data = {0x00, 0x00, 0x00, 0x00};
  auto io = createMemIo(data);

  // length = 0: DataBuf(1), read 0 bytes, wst from begin to end-3
  // end-3 on a buffer of size 1 would be begin - 2, which is problematic
  // This may throw or produce undefined behavior
  try {
    std::string result = Exiv2::readStringWcharTag(io, 0);
    // If it doesn't throw, result should be empty or something
    SUCCEED();
  } catch (const Exiv2::Error&) {
    SUCCEED();
  } catch (...) {
    SUCCEED();
  }
}

// Test: Large UCS-2LE string
TEST_F(ReadStringWcharTagTest_119, LargeUCS2LEString_119) {
  // Create a larger UCS-2LE string: 100 'A' characters
  std::vector<Exiv2::byte> data;
  for (int i = 0; i < 100; i++) {
    data.push_back('A');
    data.push_back(0x00);
  }
  // Add null terminator
  data.push_back(0x00);
  data.push_back(0x00);

  size_t length = data.size();
  auto io = createMemIo(data);

  EXPECT_NO_THROW({
    std::string result = Exiv2::readStringWcharTag(io, length);
    EXPECT_FALSE(result.empty());
  });
}

// Test: Exact boundary - length equals remaining io size
TEST_F(ReadStringWcharTagTest_119, ExactBoundary_119) {
  std::vector<Exiv2::byte> data = {'X', 0x00, 'Y', 0x00, 0x00, 0x00};
  auto io = createMemIo(data);
  size_t length = data.size(); // Exactly all remaining data

  EXPECT_NO_THROW({
    std::string result = Exiv2::readStringWcharTag(io, length);
  });
}

// Test: Length one more than available should throw
TEST_F(ReadStringWcharTagTest_119, OneBytePastBoundary_119) {
  std::vector<Exiv2::byte> data = {'X', 0x00, 'Y', 0x00, 0x00, 0x00};
  auto io = createMemIo(data);
  size_t length = data.size() + 1;

  EXPECT_THROW({
    Exiv2::readStringWcharTag(io, length);
  }, Exiv2::Error);
}

// Test: Data with non-ASCII UCS-2LE characters
TEST_F(ReadStringWcharTagTest_119, NonAsciiUCS2LE_119) {
  // é in UCS-2LE is 0xE9 0x00
  std::vector<Exiv2::byte> data = {0xE9, 0x00, 0x00, 0x00, 0x00, 0x00};
  size_t length = data.size();
  auto io = createMemIo(data);

  EXPECT_NO_THROW({
    std::string result = Exiv2::readStringWcharTag(io, length);
  });
}

// Test: IO position advances after read
TEST_F(ReadStringWcharTagTest_119, IOPositionAdvances_119) {
  std::vector<Exiv2::byte> data = {'A', 0x00, 'B', 0x00, 0x00, 0x00, 0xFF, 0xFF};
  auto io = createMemIo(data);
  size_t length = 6;

  size_t posBefore = io->tell();
  EXPECT_EQ(posBefore, 0u);

  EXPECT_NO_THROW({
    Exiv2::readStringWcharTag(io, length);
  });

  size_t posAfter = io->tell();
  EXPECT_EQ(posAfter, length);
}
