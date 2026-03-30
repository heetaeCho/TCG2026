// ============================================================================
// TEST_ID: 1065
// Unit tests for Exiv2::Image::printIFDStructure (black-box via public interface)
// File: test_image_print_ifd_structure_1065.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

// A tiny concrete Image so we can call the member under test.
class TestImage_1065 : public Exiv2::Image {
 public:
  explicit TestImage_1065(std::unique_ptr<Exiv2::BasicIo> io)
      : Exiv2::Image(static_cast<Exiv2::ImageType>(0), /*supportedMetadata=*/0, std::move(io)) {}
  ~TestImage_1065() override = default;
};

// Helpers to write little-endian integers into a byte buffer.
static void WriteLE16(std::vector<Exiv2::byte>& buf, size_t off, uint16_t v) {
  ASSERT_GE(buf.size(), off + 2u);
  buf[off + 0] = static_cast<Exiv2::byte>(v & 0xff);
  buf[off + 1] = static_cast<Exiv2::byte>((v >> 8) & 0xff);
}
static void WriteLE32(std::vector<Exiv2::byte>& buf, size_t off, uint32_t v) {
  ASSERT_GE(buf.size(), off + 4u);
  buf[off + 0] = static_cast<Exiv2::byte>(v & 0xff);
  buf[off + 1] = static_cast<Exiv2::byte>((v >> 8) & 0xff);
  buf[off + 2] = static_cast<Exiv2::byte>((v >> 16) & 0xff);
  buf[off + 3] = static_cast<Exiv2::byte>((v >> 24) & 0xff);
}

// A simple BasicIo that serves bytes from an in-memory buffer, and whose read()
// does NOT advance position (useful to deterministically trigger the "visits"
// corruption path by returning a constant tell()).
class NonAdvancingMemIo_1065 : public Exiv2::BasicIo {
 public:
  explicit NonAdvancingMemIo_1065(std::vector<Exiv2::byte> data, std::string path = "NonAdvancingMemIo_1065")
      : data_(std::move(data)), path_(std::move(path)) {}

  int open() override {
    is_open_ = true;
    return 0;
  }
  int close() override {
    is_open_ = false;
    return 0;
  }

  size_t write(const Exiv2::byte*, size_t) override { return 0; }
  size_t write(Exiv2::BasicIo&) override { return 0; }
  int putb(Exiv2::byte) override { return 0; }

  Exiv2::DataBuf read(size_t rcount) override {
    Exiv2::DataBuf b(rcount);
    (void)read(b.data(), rcount);
    return b;
  }

  size_t read(Exiv2::byte* buf, size_t rcount) override {
    if (!buf) return 0;
    const size_t pos = static_cast<size_t>(pos_);
    const size_t avail = (pos < data_.size()) ? (data_.size() - pos) : 0u;
    const size_t n = std::min(rcount, avail);
    if (n > 0) {
      std::memcpy(buf, data_.data() + pos, n);
    }
    // IMPORTANT: do not advance pos_ (non-advancing).
    return n;
  }

  int getb() override { return -1; }
  void transfer(Exiv2::BasicIo&) override {}

  int seek(int64_t offset, Position pos) override {
    int64_t base = 0;
    if (pos == Exiv2::BasicIo::beg) base = 0;
    else if (pos == Exiv2::BasicIo::cur) base = pos_;
    else if (pos == Exiv2::BasicIo::end) base = static_cast<int64_t>(data_.size());
    const int64_t np = base + offset;
    if (np < 0) return 1;
    pos_ = np;
    return 0;
  }

  Exiv2::byte* mmap(bool) override { return nullptr; }
  int munmap() override { return 0; }

  const size_t tell() override { return static_cast<size_t>(pos_); }
  const size_t size() override { return data_.size(); }

  const bool isopen() override { return is_open_; }
  const int error() override { return 0; }
  const bool eof() override { return false; }

  const std::string& path() override { return path_; }

  void populateFakeData() override {}

 private:
  std::vector<Exiv2::byte> data_;
  std::string path_;
  bool is_open_ = true;
  int64_t pos_ = 0;
};

class ImagePrintIFDStructureTest_1065 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::MemIo> MakeMemIo(const std::vector<Exiv2::byte>& bytes) {
    return std::make_unique<Exiv2::MemIo>(bytes.data(), bytes.size());
  }
};

}  // namespace

TEST_F(ImagePrintIFDStructureTest_1065, PrintsBasicStructureForSingleShortEntry_1065) {
  // Build a minimal TIFF IFD:
  //   [0..1]   dirLength = 1
  //   [2..13]  entry #0: tag=0x0100, type=3 (unsignedShort), count=1, value=0x002A (in offset field)
  //   [14..17] nextIFD = 0
  std::vector<Exiv2::byte> bytes(2 + 12 + 4, 0);
  WriteLE16(bytes, 0, 1);          // dirLength
  WriteLE16(bytes, 2, 0x0100);     // tag
  WriteLE16(bytes, 4, 3);          // type unsignedShort
  WriteLE32(bytes, 6, 1);          // count
  WriteLE32(bytes, 10, 0x0000002A);  // value (fits in 4 bytes for count*size<=4)
  WriteLE32(bytes, 14, 0);         // nextIFD

  auto mem = MakeMemIo(bytes);
  TestImage_1065 img(std::make_unique<Exiv2::MemIo>(bytes.data(), bytes.size()));

  std::ostringstream out;
  ASSERT_NO_THROW(img.printIFDStructure(*mem, out, Exiv2::kpsBasic,
                                       /*start=*/0, /*bSwap=*/false, /*c=*/'I', /*depth=*/1));

  const std::string s = out.str();
  // We don't assume exact formatting; just verify key observable markers.
  EXPECT_NE(s.find("STRUCTURE OF TIFF FILE"), std::string::npos);
  EXPECT_NE(s.find("address | tag |"), std::string::npos);
  EXPECT_NE(s.find("END "), std::string::npos);
  // Tag hex should appear.
  EXPECT_NE(s.find("0x0100"), std::string::npos);
}

TEST_F(ImagePrintIFDStructureTest_1065, ThrowsTiffDirectoryTooLargeWhenDirLengthExceeds500_1065) {
  // Only need the first 2 bytes (dirLength). Set to 501 (>500).
  std::vector<Exiv2::byte> bytes(2, 0);
  WriteLE16(bytes, 0, 501);

  auto mem = MakeMemIo(bytes);
  TestImage_1065 img(std::make_unique<Exiv2::MemIo>(bytes.data(), bytes.size()));

  std::ostringstream out;
  EXPECT_THROW(
      img.printIFDStructure(*mem, out, Exiv2::kpsBasic,
                            /*start=*/0, /*bSwap=*/false, /*c=*/'I', /*depth=*/1),
      Exiv2::Error);
}

TEST_F(ImagePrintIFDStructureTest_1065, ThrowsInvalidTypeValueOnInvalidTiffType_1065) {
  // One directory entry with an invalid type value.
  std::vector<Exiv2::byte> bytes(2 + 12 + 4, 0);
  WriteLE16(bytes, 0, 1);           // dirLength
  WriteLE16(bytes, 2, 0x0100);      // tag
  WriteLE16(bytes, 4, 0xFFFF);      // invalid type
  WriteLE32(bytes, 6, 1);           // count
  WriteLE32(bytes, 10, 0);          // offset/value
  WriteLE32(bytes, 14, 0);          // nextIFD

  auto mem = MakeMemIo(bytes);
  TestImage_1065 img(std::make_unique<Exiv2::MemIo>(bytes.data(), bytes.size()));

  std::ostringstream out;
  EXPECT_THROW(
      img.printIFDStructure(*mem, out, Exiv2::kpsBasic,
                            /*start=*/0, /*bSwap=*/false, /*c=*/'I', /*depth=*/1),
      Exiv2::Error);
}

TEST_F(ImagePrintIFDStructureTest_1065, ThrowsInvalidMallocWhenComputedAllocationExceedsIoSize_1065) {
  // Force (size*count)+pad+20 > io.size() to trigger kerInvalidMalloc.
  // Use type=unsignedLong (4 bytes), count=1000 -> allocate64 ~= 4020.
  // Provide a much smaller io.size(), e.g. 100 bytes.
  std::vector<Exiv2::byte> bytes(100, 0);
  WriteLE16(bytes, 0, 1);        // dirLength
  WriteLE16(bytes, 2, 0x0100);   // tag
  WriteLE16(bytes, 4, 4);        // type unsignedLong
  WriteLE32(bytes, 6, 1000);     // count
  WriteLE32(bytes, 10, 0);       // offset/value
  // nextIFD already 0 due to initialization (at [14..17], within 100 bytes)

  auto mem = MakeMemIo(bytes);
  TestImage_1065 img(std::make_unique<Exiv2::MemIo>(bytes.data(), bytes.size()));

  std::ostringstream out;
  EXPECT_THROW(
      img.printIFDStructure(*mem, out, Exiv2::kpsBasic,
                            /*start=*/0, /*bSwap=*/false, /*c=*/'I', /*depth=*/1),
      Exiv2::Error);
}

TEST_F(ImagePrintIFDStructureTest_1065, ThrowsCorruptedMetadataWhenVisitAddressRepeats_1065) {
  // Build IFD with dirLength=2 so the loop executes twice.
  // Use NonAdvancingMemIo so tell() doesn't change between iterations,
  // causing visits.contains(io.tell()) to be true on the second iteration.
  std::vector<Exiv2::byte> bytes(2 + 12 * 2 + 4, 0);
  WriteLE16(bytes, 0, 2);           // dirLength=2

  // Entry 0: valid short
  WriteLE16(bytes, 2, 0x0100);      // tag
  WriteLE16(bytes, 4, 3);           // type unsignedShort
  WriteLE32(bytes, 6, 1);           // count
  WriteLE32(bytes, 10, 0x2A);       // value

  // Entry 1 (won't be reached successfully due to visit repetition)
  WriteLE16(bytes, 14, 0x0101);
  WriteLE16(bytes, 16, 3);
  WriteLE32(bytes, 18, 1);
  WriteLE32(bytes, 22, 0x2B);

  // nextIFD=0
  WriteLE32(bytes, 26, 0);

  NonAdvancingMemIo_1065 io(std::move(bytes));
  TestImage_1065 img(std::make_unique<Exiv2::MemIo>());  // Image's internal io_ unused here

  std::ostringstream out;
  EXPECT_THROW(
      img.printIFDStructure(io, out, Exiv2::kpsBasic,
                            /*start=*/0, /*bSwap=*/false, /*c=*/'I', /*depth=*/1),
      Exiv2::Error);
}

TEST_F(ImagePrintIFDStructureTest_1065, RecursiveOptionPrintsNestedIfdWhenExifIfdPointerPresent_1065) {
  // IFD0 at offset 0: one entry ExifTag (0x8769), type=unsignedLong, count=1, offset=subIFD (100)
  // SubIFD at offset 100: one short entry, nextIFD=0.
  std::vector<Exiv2::byte> bytes(200, 0);

  // IFD0
  WriteLE16(bytes, 0, 1);          // dirLength=1
  WriteLE16(bytes, 2, 0x8769);     // ExifTag pointer
  WriteLE16(bytes, 4, 4);          // type unsignedLong
  WriteLE32(bytes, 6, 1);          // count=1
  WriteLE32(bytes, 10, 100);       // offset to subIFD
  WriteLE32(bytes, 14, 0);         // nextIFD=0

  // SubIFD at offset 100
  WriteLE16(bytes, 100, 1);        // dirLength=1
  WriteLE16(bytes, 102, 0x0100);   // tag
  WriteLE16(bytes, 104, 3);        // type unsignedShort
  WriteLE32(bytes, 106, 1);        // count=1
  WriteLE32(bytes, 110, 1);        // value=1
  WriteLE32(bytes, 114, 0);        // nextIFD=0

  auto mem = MakeMemIo(bytes);
  TestImage_1065 img(std::make_unique<Exiv2::MemIo>(bytes.data(), bytes.size()));

  std::ostringstream out;
  ASSERT_NO_THROW(img.printIFDStructure(*mem, out, Exiv2::kpsRecursive,
                                       /*start=*/0, /*bSwap=*/false, /*c=*/'I', /*depth=*/1));

  const std::string s = out.str();
  // In recursive mode we expect multiple structure blocks.
  const auto first = s.find("STRUCTURE OF TIFF FILE");
  ASSERT_NE(first, std::string::npos);
  const auto second = s.find("STRUCTURE OF TIFF FILE", first + 1);
  EXPECT_NE(second, std::string::npos);

  // Ensure both END markers appear at least twice (top and nested).
  const auto end1 = s.find("END ");
  ASSERT_NE(end1, std::string::npos);
  const auto end2 = s.find("END ", end1 + 1);
  EXPECT_NE(end2, std::string::npos);
}