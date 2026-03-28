#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstring>
#include <limits>

#include "exiv2/bmffimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;

// A mock/fake BasicIo implementation for testing purposes
class FakeBasicIo : public BasicIo {
 public:
  FakeBasicIo(const std::vector<uint8_t>& data) : data_(data), pos_(0), isOpen_(true) {}
  FakeBasicIo() : pos_(0), isOpen_(true) {}

  int open() override {
    isOpen_ = true;
    return 0;
  }

  int close() override {
    isOpen_ = false;
    return 0;
  }

  size_t write(const byte* data, size_t wcount) override {
    return 0;
  }

  size_t write(BasicIo& src) override {
    return 0;
  }

  int putb(byte data) override {
    return 0;
  }

  DataBuf read(size_t rcount) override {
    size_t avail = (pos_ < data_.size()) ? data_.size() - pos_ : 0;
    size_t toRead = std::min(rcount, avail);
    DataBuf buf(toRead);
    if (toRead > 0) {
      std::memcpy(buf.data(), data_.data() + pos_, toRead);
      pos_ += toRead;
    }
    return buf;
  }

  size_t read(byte* buf, size_t rcount) override {
    size_t avail = (pos_ < data_.size()) ? data_.size() - pos_ : 0;
    size_t toRead = std::min(rcount, avail);
    if (toRead > 0) {
      std::memcpy(buf, data_.data() + pos_, toRead);
      pos_ += toRead;
    }
    return toRead;
  }

  int getb() override {
    if (pos_ < data_.size()) {
      return data_[pos_++];
    }
    return EOF;
  }

  void transfer(BasicIo& src) override {}

  int seek(int64_t offset, Position pos) override {
    switch (pos) {
      case BasicIo::beg:
        if (offset >= 0 && static_cast<size_t>(offset) <= data_.size()) {
          pos_ = static_cast<size_t>(offset);
          return 0;
        }
        break;
      case BasicIo::cur:
        {
          int64_t newPos = static_cast<int64_t>(pos_) + offset;
          if (newPos >= 0 && static_cast<size_t>(newPos) <= data_.size()) {
            pos_ = static_cast<size_t>(newPos);
            return 0;
          }
        }
        break;
      case BasicIo::end:
        {
          int64_t newPos = static_cast<int64_t>(data_.size()) + offset;
          if (newPos >= 0 && static_cast<size_t>(newPos) <= data_.size()) {
            pos_ = static_cast<size_t>(newPos);
            return 0;
          }
        }
        break;
    }
    return 1;
  }

  byte* mmap(bool isWriteable) override {
    return data_.empty() ? nullptr : data_.data();
  }

  int munmap() override {
    return 0;
  }

  size_t tell() const override {
    return pos_;
  }

  size_t size() const override {
    return data_.size();
  }

  bool isopen() const override {
    return isOpen_;
  }

  int error() const override {
    return 0;
  }

  bool eof() const override {
    return pos_ >= data_.size();
  }

  const std::string& path() const override {
    static std::string p = "FakeBasicIo";
    return p;
  }

  void populateFakeData() override {}

  void setData(const std::vector<uint8_t>& data) {
    data_ = data;
    pos_ = 0;
  }

 private:
  std::vector<uint8_t> data_;
  size_t pos_;
  bool isOpen_;
};

class BmffImageParseTiffTest_1196 : public ::testing::Test {
 protected:
  void SetUp() override {}

  std::unique_ptr<BmffImage> createBmffImage(const std::vector<uint8_t>& data) {
    auto io = std::make_unique<FakeBasicIo>(data);
    return std::make_unique<BmffImage>(std::move(io), false, 100);
  }

  std::unique_ptr<BmffImage> createBmffImageEmpty() {
    auto io = std::make_unique<FakeBasicIo>();
    return std::make_unique<BmffImage>(std::move(io), false, 100);
  }
};

// Test: start > io_->size() should throw kerCorruptedMetadata
TEST_F(BmffImageParseTiffTest_1196, StartBeyondIoSizeThrows_1196) {
  std::vector<uint8_t> data(100, 0);
  auto image = createBmffImage(data);

  // start = 200 > size() = 100
  EXPECT_THROW(image->parseTiff(0, 10, 200), Exiv2::Error);
}

// Test: length > io_->size() - start should throw kerCorruptedMetadata
TEST_F(BmffImageParseTiffTest_1196, LengthExceedsAvailableThrows_1196) {
  std::vector<uint8_t> data(100, 0);
  auto image = createBmffImage(data);

  // start = 50, length = 60, available = 50
  EXPECT_THROW(image->parseTiff(0, 60, 50), Exiv2::Error);
}

// Test: start at boundary equal to io_->size(), length 0 should not throw
TEST_F(BmffImageParseTiffTest_1196, StartEqualsIoSizeLengthZeroNoThrow_1196) {
  std::vector<uint8_t> data(100, 0);
  auto image = createBmffImage(data);

  // start = 100, length = 0, start <= size is ok, length <= size - start = 0 is ok
  EXPECT_NO_THROW(image->parseTiff(0, 0, 100));
}

// Test: empty data (size=0), start=0, length=0 should not throw
TEST_F(BmffImageParseTiffTest_1196, EmptyDataZeroStartZeroLength_1196) {
  auto image = createBmffImageEmpty();
  EXPECT_NO_THROW(image->parseTiff(0, 0, 0));
}

// Test: empty data, start=0, length=1 should throw
TEST_F(BmffImageParseTiffTest_1196, EmptyDataNonZeroLengthThrows_1196) {
  auto image = createBmffImageEmpty();
  EXPECT_THROW(image->parseTiff(0, 1, 0), Exiv2::Error);
}

// Test: empty data, start=1, length=0 should throw
TEST_F(BmffImageParseTiffTest_1196, EmptyDataNonZeroStartThrows_1196) {
  auto image = createBmffImageEmpty();
  EXPECT_THROW(image->parseTiff(0, 0, 1), Exiv2::Error);
}

// Test: length too small (<=8) should result in no parsing (no crash)
TEST_F(BmffImageParseTiffTest_1196, LengthTooSmallForTiffNoCrash_1196) {
  std::vector<uint8_t> data(8, 0);
  auto image = createBmffImage(data);

  // length = 8, which means exif.size() == 8, condition exif.size() > 8 is false
  EXPECT_NO_THROW(image->parseTiff(0, 8, 0));
}

// Test: data with no TIFF marker (no 'II' or 'MM') should not crash and not modify exif
TEST_F(BmffImageParseTiffTest_1196, NoTiffMarkerNoCrash_1196) {
  std::vector<uint8_t> data(20, 0x41);  // All 'A' characters
  auto image = createBmffImage(data);

  EXPECT_NO_THROW(image->parseTiff(0, 20, 0));
  // No TIFF header found, so exifData should remain empty
  EXPECT_TRUE(image->exifData().empty());
}

// Test: data with 'II' TIFF marker - should attempt to decode
TEST_F(BmffImageParseTiffTest_1196, TiffMarkerIIPresentNoCrash_1196) {
  // Create data with 'II' at some offset, followed by TIFF-like data
  std::vector<uint8_t> data(50, 0);
  data[4] = 'I';
  data[5] = 'I';
  // TIFF header: 'II' followed by 42 (0x2A, 0x00 in little-endian)
  data[6] = 0x2A;
  data[7] = 0x00;
  // IFD offset (0 entries)
  data[8] = 0x08;
  data[9] = 0x00;
  data[10] = 0x00;
  data[11] = 0x00;

  auto image = createBmffImage(data);
  EXPECT_NO_THROW(image->parseTiff(0, 50, 0));
}

// Test: data with 'MM' TIFF marker - should attempt to decode
TEST_F(BmffImageParseTiffTest_1196, TiffMarkerMMPresentNoCrash_1196) {
  std::vector<uint8_t> data(50, 0);
  data[4] = 'M';
  data[5] = 'M';
  data[6] = 0x00;
  data[7] = 0x2A;  // Big-endian TIFF magic
  data[8] = 0x00;
  data[9] = 0x00;
  data[10] = 0x00;
  data[11] = 0x08;

  auto image = createBmffImage(data);
  EXPECT_NO_THROW(image->parseTiff(0, 50, 0));
}

// Test: io position is restored after parseTiff
TEST_F(BmffImageParseTiffTest_1196, IoPositionRestoredAfterParseTiff_1196) {
  std::vector<uint8_t> data(100, 0);
  auto io = std::make_unique<FakeBasicIo>(data);
  auto* ioPtr = io.get();

  auto image = std::make_unique<BmffImage>(std::move(io), false, 100);

  // Set io position to 42
  ioPtr->seek(42, BasicIo::beg);
  size_t posBefore = ioPtr->tell();
  EXPECT_EQ(posBefore, 42u);

  image->parseTiff(0, 20, 0);

  size_t posAfter = ioPtr->tell();
  EXPECT_EQ(posAfter, posBefore);
}

// Test: start = 0, length = io size (full data, but no TIFF header)
TEST_F(BmffImageParseTiffTest_1196, FullDataNoTiffHeader_1196) {
  std::vector<uint8_t> data(100, 0x30);  // All '0' characters, no II or MM
  auto image = createBmffImage(data);

  EXPECT_NO_THROW(image->parseTiff(0, 100, 0));
  EXPECT_TRUE(image->exifData().empty());
}

// Test: start with non-zero offset
TEST_F(BmffImageParseTiffTest_1196, NonZeroStartOffset_1196) {
  std::vector<uint8_t> data(200, 0);
  // Place TIFF marker at offset 104 (relative to start=100, at position 4)
  data[104] = 'I';
  data[105] = 'I';
  data[106] = 0x2A;
  data[107] = 0x00;

  auto image = createBmffImage(data);
  EXPECT_NO_THROW(image->parseTiff(0, 50, 100));
}

// Test: boundary - length exactly 9 bytes (minimum for search loop to execute)
TEST_F(BmffImageParseTiffTest_1196, LengthExactlyNineBytes_1196) {
  std::vector<uint8_t> data(9, 0);
  data[0] = 'I';
  data[1] = 'I';

  auto image = createBmffImage(data);
  EXPECT_NO_THROW(image->parseTiff(0, 9, 0));
}

// Test: 'II' at the very start of the buffer
TEST_F(BmffImageParseTiffTest_1196, TiffMarkerAtStartOfBuffer_1196) {
  std::vector<uint8_t> data(20, 0);
  data[0] = 'I';
  data[1] = 'I';
  data[2] = 0x2A;
  data[3] = 0x00;
  data[4] = 0x08;
  data[5] = 0x00;
  data[6] = 0x00;
  data[7] = 0x00;

  auto image = createBmffImage(data);
  EXPECT_NO_THROW(image->parseTiff(0, 20, 0));
}

// Test: 'MM' at the very end of searchable range
TEST_F(BmffImageParseTiffTest_1196, TiffMarkerNearEndOfBuffer_1196) {
  // size = 20, loop goes i from 0 to size-10 (i.e., 0..10)
  // Place 'MM' at offset 10
  std::vector<uint8_t> data(20, 0);
  data[10] = 'M';
  data[11] = 'M';
  data[12] = 0x00;
  data[13] = 0x2A;

  auto image = createBmffImage(data);
  EXPECT_NO_THROW(image->parseTiff(0, 20, 0));
}

// Test: parseTiff with two-arg overload (start defaults to current io position)
TEST_F(BmffImageParseTiffTest_1196, TwoArgParseTiffNoCrash_1196) {
  std::vector<uint8_t> data(50, 0);
  auto image = createBmffImage(data);

  EXPECT_NO_THROW(image->parseTiff(0, 50));
}

// Test: Very large start value that exceeds int64_t max
TEST_F(BmffImageParseTiffTest_1196, StartExceedsInt64MaxThrows_1196) {
  // We need a large enough io size - but practically we can't create that.
  // Instead, test with start = uint64_t max which is > size
  std::vector<uint8_t> data(100, 0);
  auto image = createBmffImage(data);

  uint64_t hugeStart = static_cast<uint64_t>(std::numeric_limits<int64_t>::max()) + 1;
  EXPECT_THROW(image->parseTiff(0, 0, hugeStart), Exiv2::Error);
}

// Test: length = 0 with valid start should not crash
TEST_F(BmffImageParseTiffTest_1196, ZeroLengthValidStart_1196) {
  std::vector<uint8_t> data(100, 0);
  auto image = createBmffImage(data);

  EXPECT_NO_THROW(image->parseTiff(0, 0, 50));
}

// Test: Both start and length are zero
TEST_F(BmffImageParseTiffTest_1196, BothZero_1196) {
  std::vector<uint8_t> data(10, 0);
  auto image = createBmffImage(data);

  EXPECT_NO_THROW(image->parseTiff(0, 0, 0));
}

// Test: Data contains single 'I' but not consecutive 'II'
TEST_F(BmffImageParseTiffTest_1196, SingleINotDouble_1196) {
  std::vector<uint8_t> data(20, 0);
  data[5] = 'I';
  data[6] = 'X';  // Not 'I', so no match

  auto image = createBmffImage(data);
  EXPECT_NO_THROW(image->parseTiff(0, 20, 0));
  EXPECT_TRUE(image->exifData().empty());
}

// Test: Data contains mixed 'I' and 'M' but not consecutive same chars
TEST_F(BmffImageParseTiffTest_1196, MixedIMNotMatching_1196) {
  std::vector<uint8_t> data(20, 0);
  data[5] = 'I';
  data[6] = 'M';
  data[7] = 'I';
  data[8] = 'M';

  auto image = createBmffImage(data);
  EXPECT_NO_THROW(image->parseTiff(0, 20, 0));
  EXPECT_TRUE(image->exifData().empty());
}

// Test: Various root_tag values should not cause crash
TEST_F(BmffImageParseTiffTest_1196, DifferentRootTagValues_1196) {
  std::vector<uint8_t> data(20, 0);
  data[0] = 'I';
  data[1] = 'I';
  data[2] = 0x2A;
  data[3] = 0x00;

  auto image = createBmffImage(data);
  EXPECT_NO_THROW(image->parseTiff(0x0110, 20, 0));

  auto image2 = createBmffImage(data);
  EXPECT_NO_THROW(image2->parseTiff(0xFFFF, 20, 0));
}
