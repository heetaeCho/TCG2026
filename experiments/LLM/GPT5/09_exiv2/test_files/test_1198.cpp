// ============================================================================
// Unit tests for Exiv2::BmffImage::parseXmp
// File: ./TestProjects/exiv2/src/bmffimage_parsexmp_test.cpp
// TEST_ID: 1198
// ============================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "exiv2/bmffimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/xmp_exiv2.hpp"

using ::testing::HasSubstr;

namespace {

class VectorIo final : public Exiv2::BasicIo {
 public:
  explicit VectorIo(std::vector<Exiv2::byte> data)
      : data_(std::move(data)) {}

  // Controls for error/short-read simulation
  void setErrorFlag(bool v) { error_ = v ? 1 : 0; }
  void setMaxReadable(size_t maxReadable) { maxReadable_ = maxReadable; }

  // Observability helpers
  size_t tellCount() const { return tellCount_; }
  size_t seekCount() const { return seekCount_; }
  size_t readCount() const { return readCount_; }

  // ---- BasicIo overrides used by parseXmp ----
  size_t read(Exiv2::byte* buf, size_t rcount) override {
    ++readCount_;

    // Apply short-read limit if configured
    if (maxReadable_ != kNoLimit) {
      rcount = std::min(rcount, maxReadable_);
    }

    if (pos_ > data_.size()) {
      return 0;
    }

    const size_t avail = data_.size() - pos_;
    const size_t n = std::min(rcount, avail);
    if (n > 0) {
      std::memcpy(buf, data_.data() + pos_, n);
      pos_ += n;
    }
    return n;
  }

  int seek(int64_t offset, Position pos) override {
    ++seekCount_;
    int64_t base = 0;
    switch (pos) {
      case Exiv2::BasicIo::beg: base = 0; break;
      case Exiv2::BasicIo::cur: base = static_cast<int64_t>(pos_); break;
      case Exiv2::BasicIo::end: base = static_cast<int64_t>(data_.size()); break;
      default: base = 0; break;
    }
    const int64_t target = base + offset;
    if (target < 0) {
      pos_ = 0;
      return -1;
    }
    pos_ = static_cast<size_t>(target);
    return 0;
  }

  const size_t tell() override {
    ++tellCount_;
    return pos_;
  }

  const size_t size() override { return data_.size(); }

  const int error() override { return error_; }

  // ---- Other virtuals (minimal stubs) ----
  int open() override { return 0; }
  int close() override { return 0; }
  size_t write(const Exiv2::byte*, size_t) override { return 0; }
  size_t write(Exiv2::BasicIo&) override { return 0; }
  int putb(Exiv2::byte) override { return 0; }
  Exiv2::DataBuf read(size_t) override { return Exiv2::DataBuf(); }
  int getb() override { return -1; }
  void transfer(Exiv2::BasicIo&) override {}
  Exiv2::byte* mmap(bool) override { return nullptr; }
  int munmap() override { return 0; }
  const bool isopen() override { return true; }
  const bool eof() override { return pos_ >= data_.size(); }
  const std::string& path() override { return path_; }
  void populateFakeData() override {}

 private:
  static constexpr size_t kNoLimit = static_cast<size_t>(-1);

  std::vector<Exiv2::byte> data_;
  size_t pos_{0};
  int error_{0};
  size_t maxReadable_{kNoLimit};

  std::string path_{"VectorIo"};

  mutable size_t tellCount_{0};
  mutable size_t seekCount_{0};
  mutable size_t readCount_{0};
};

static std::vector<Exiv2::byte> ToBytes(const std::string& s) {
  return std::vector<Exiv2::byte>(reinterpret_cast<const Exiv2::byte*>(s.data()),
                                 reinterpret_cast<const Exiv2::byte*>(s.data()) + s.size());
}

class BmffImageParseXmpTest_1198 : public ::testing::Test {
 public:
  static void SetUpTestSuite() {
    // If XMP toolkit/init is required by this build, attempt to initialize.
    // We don't assert on the return value to avoid over-constraining across builds.
    (void)Exiv2::XmpParser::initialize(nullptr, nullptr);
  }

  static void TearDownTestSuite() {
    // Symmetric termination (safe even if initialize was a no-op in this build).
    Exiv2::XmpParser::terminate();
  }
};

static std::unique_ptr<Exiv2::BmffImage> MakeImageWithIo(std::unique_ptr<Exiv2::BasicIo> io) {
  // max_box_depth is irrelevant for parseXmp usage here.
  return std::make_unique<Exiv2::BmffImage>(std::move(io), /*create*/ false, /*max_box_depth*/ 1);
}

static int CodeAsInt(const Exiv2::Error& e) {
  // Exiv2::Error::code() is commonly an int in Exiv2; keep comparison robust.
  return static_cast<int>(e.code());
}

}  // namespace

TEST_F(BmffImageParseXmpTest_1198, ParsesValidXmpAndRestoresIoPosition_1198) {
  const std::string xmp =
      "<?xpacket begin=\"\xEF\xBB\xBF\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>\n"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">\n"
      " <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
      "  <rdf:Description xmlns:dc=\"http://purl.org/dc/elements/1.1/\">\n"
      "   <dc:title><rdf:Alt><rdf:li xml:lang=\"x-default\">Test</rdf:li></rdf:Alt></dc:title>\n"
      "  </rdf:Description>\n"
      " </rdf:RDF>\n"
      "</x:xmpmeta>\n"
      "<?xpacket end=\"w\"?>\n";

  auto vio = std::make_unique<VectorIo>(ToBytes(xmp));
  // Start with a non-zero position to verify restoration.
  ASSERT_EQ(vio->seek(2, Exiv2::BasicIo::beg), 0);
  const size_t restorePos = vio->tell();

  auto* vioRaw = vio.get();
  auto img = MakeImageWithIo(std::move(vio));

  ASSERT_NO_THROW(img->parseXmp(/*length*/ static_cast<uint64_t>(xmp.size()), /*start*/ 0));

  EXPECT_EQ(img->io().tell(), restorePos);

  // Observable effect: some XMP data should have been decoded into the image.
  // We only assert non-emptiness to avoid depending on specific keys.
  EXPECT_FALSE(img->xmpData().empty());

  // Basic interaction sanity: parseXmp must seek to start and later seek back.
  EXPECT_GE(vioRaw->seekCount(), 2u);
  EXPECT_GE(vioRaw->readCount(), 1u);
}

TEST_F(BmffImageParseXmpTest_1198, ThrowsCorruptedMetadataWhenStartBeyondSize_1198) {
  const std::string payload = "abcd";
  auto vio = std::make_unique<VectorIo>(ToBytes(payload));
  auto img = MakeImageWithIo(std::move(vio));

  try {
    img->parseXmp(/*length*/ 1, /*start*/ static_cast<uint64_t>(payload.size() + 1));
    FAIL() << "Expected Exiv2::Error";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(CodeAsInt(e), static_cast<int>(Exiv2::ErrorCode::kerCorruptedMetadata));
  }
}

TEST_F(BmffImageParseXmpTest_1198, ThrowsCorruptedMetadataWhenLengthExceedsAvailable_1198) {
  const std::string payload = "abcdef";
  auto vio = std::make_unique<VectorIo>(ToBytes(payload));
  auto img = MakeImageWithIo(std::move(vio));

  const uint64_t start = 2;
  const uint64_t lengthTooBig = static_cast<uint64_t>(payload.size() - start + 1);

  try {
    img->parseXmp(lengthTooBig, start);
    FAIL() << "Expected Exiv2::Error";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(CodeAsInt(e), static_cast<int>(Exiv2::ErrorCode::kerCorruptedMetadata));
  }
}

TEST_F(BmffImageParseXmpTest_1198, ThrowsInputDataReadFailedOnShortRead_1198) {
  const std::string xmp =
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\"></x:xmpmeta>";
  auto vio = std::make_unique<VectorIo>(ToBytes(xmp));
  // Force a short read: only allow 1 byte to be read, regardless of request.
  vio->setMaxReadable(1);

  auto img = MakeImageWithIo(std::move(vio));

  try {
    img->parseXmp(static_cast<uint64_t>(xmp.size()), 0);
    FAIL() << "Expected Exiv2::Error";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(CodeAsInt(e), static_cast<int>(Exiv2::ErrorCode::kerInputDataReadFailed));
  }
}

TEST_F(BmffImageParseXmpTest_1198, ThrowsFailedToReadImageDataWhenIoReportsError_1198) {
  const std::string xmp =
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\"></x:xmpmeta>";
  auto vio = std::make_unique<VectorIo>(ToBytes(xmp));
  // Ensure read returns full size, but the IO reports an error afterwards.
  vio->setErrorFlag(true);

  auto img = MakeImageWithIo(std::move(vio));

  try {
    img->parseXmp(static_cast<uint64_t>(xmp.size()), 0);
    FAIL() << "Expected Exiv2::Error";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(CodeAsInt(e), static_cast<int>(Exiv2::ErrorCode::kerFailedToReadImageData));
  }
}

TEST_F(BmffImageParseXmpTest_1198, ThrowsFailedToReadImageDataWhenXmpDecodeFails_1198) {
  // Intentionally invalid XMP packet to provoke decode failure.
  const std::string invalidXmp = "<x:xmpmeta><not-xml";
  auto vio = std::make_unique<VectorIo>(ToBytes(invalidXmp));
  auto img = MakeImageWithIo(std::move(vio));

  try {
    img->parseXmp(static_cast<uint64_t>(invalidXmp.size()), 0);
    FAIL() << "Expected Exiv2::Error";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(CodeAsInt(e), static_cast<int>(Exiv2::ErrorCode::kerFailedToReadImageData));
  }
}

TEST_F(BmffImageParseXmpTest_1198, Boundary_StartAtEndWithZeroLengthPropagatesDecodeFailure_1198) {
  // Boundary: start == size, length == 0 passes range checks, then decodes empty packet.
  const std::string payload = "anything";
  auto vio = std::make_unique<VectorIo>(ToBytes(payload));
  auto img = MakeImageWithIo(std::move(vio));

  try {
    img->parseXmp(/*length*/ 0, /*start*/ static_cast<uint64_t>(payload.size()));
    FAIL() << "Expected Exiv2::Error";
  } catch (const Exiv2::Error& e) {
    // parseXmp maps any decode failure to kerFailedToReadImageData.
    EXPECT_EQ(CodeAsInt(e), static_cast<int>(Exiv2::ErrorCode::kerFailedToReadImageData));
  }
}