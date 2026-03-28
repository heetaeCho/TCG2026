// TEST_ID 1200
// File: test_bmffimage_readmetadata_1200.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>

// Exiv2 headers
#include "bmffimage.hpp"
#include "exif.hpp"
#include "iptc.hpp"
#include "xmp_exiv2.hpp"

namespace {

// A tiny BasicIo test double that is controllable and observable.
// We avoid inferring internal logic of BmffImage; we only observe public effects
// and BasicIo interactions.
class TestBasicIo : public Exiv2::BasicIo {
 public:
  explicit TestBasicIo(size_t size) : size_(size) {}

  // Controls
  void setThrowOnOpen(bool v) { throw_on_open_ = v; }
  void setThrowOnSize(bool v) { throw_on_size_ = v; }

  // Observations
  int openCalls() const { return open_calls_; }
  int closeCalls() const { return close_calls_; }
  int seekCalls() const { return seek_calls_; }
  int64_t lastSeekOffset() const { return last_seek_offset_; }

  // Exiv2::BasicIo
  int open() override {
    ++open_calls_;
    if (throw_on_open_) throw std::runtime_error("open failed");
    open_ = true;
    return 0;
  }

  int close() override {
    ++close_calls_;
    open_ = false;
    return 0;
  }

  int seek(int64_t offset, Position /*pos*/) override {
    ++seek_calls_;
    last_seek_offset_ = offset;
    return 0;
  }

  size_t size() override {
    if (throw_on_size_) throw std::runtime_error("size failed");
    return size_;
  }

  const bool isopen() override { return open_; }

  const int error() override { return 0; }

  const bool eof() override { return false; }

  const std::string& path() override { return path_; }

 private:
  size_t size_{0};
  bool open_{false};
  bool throw_on_open_{false};
  bool throw_on_size_{false};

  int open_calls_{0};
  int close_calls_{0};
  int seek_calls_{0};
  int64_t last_seek_offset_{0};

  std::string path_{"TestBasicIo"};
};

class BmffImageReadMetadataTest_1200 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::BmffImage> makeImageWithIo(TestBasicIo** out_io,
                                                          size_t io_size) {
    auto io = std::make_unique<TestBasicIo>(io_size);
    if (out_io) *out_io = io.get();
    // create=false is fine for these tests; max_box_depth choose a reasonable value.
    return std::make_unique<Exiv2::BmffImage>(std::move(io), /*create=*/false,
                                             /*max_box_depth=*/16);
  }

  static void seedSomeMetadata(Exiv2::BmffImage& img) {
    // Populate via public interface only.
    img.setComment("hello");

    // Exif/IPTC/XMP: Keep it minimal and robust.
    Exiv2::ExifData exif;
    exif["Exif.Image.Make"] = "UnitTest";
    img.setExifData(exif);

    Exiv2::IptcData iptc;
    iptc["Iptc.Application2.ObjectName"] = "UnitTest";
    img.setIptcData(iptc);

    Exiv2::XmpData xmp;
    xmp["Xmp.dc.title"] = "UnitTest";
    img.setXmpData(xmp);

    img.setXmpPacket("<?xpacket begin='x'?>unit-test<?xpacket end='w'?>");
  }
};

}  // namespace

TEST_F(BmffImageReadMetadataTest_1200, ClearsExistingMetadataWhenFileIsEmpty_1200) {
  TestBasicIo* io = nullptr;
  auto img = makeImageWithIo(&io, /*io_size=*/0);

  ASSERT_NE(img, nullptr);
  ASSERT_NE(io, nullptr);

  seedSomeMetadata(*img);

  ASSERT_FALSE(img->comment().empty());
  ASSERT_FALSE(img->exifData().empty());
  ASSERT_FALSE(img->iptcData().empty());
  ASSERT_FALSE(img->xmpData().empty());
  ASSERT_FALSE(img->xmpPacket().empty());

  // With an empty file, readMetadata() should be able to complete without
  // entering any parsing loop (observable: no seeks required).
  EXPECT_NO_THROW(img->readMetadata());

  // Observable behavior through public API: metadata has been cleared.
  EXPECT_TRUE(img->comment().empty());
  EXPECT_TRUE(img->exifData().empty());
  EXPECT_TRUE(img->iptcData().empty());
  EXPECT_TRUE(img->xmpData().empty());
  EXPECT_TRUE(img->xmpPacket().empty());

  // External interaction: open/close around metadata reading are typical.
  // We do not assume exact counts beyond minimal "at least once open".
  EXPECT_GE(io->openCalls(), 1);

  // For empty file, loop shouldn't run, so seeking is not required by the loop.
  // (readMetadata still might do internal seeks; we only assert a weak, safe bound.)
  EXPECT_EQ(io->seekCalls(), 0);
}

TEST_F(BmffImageReadMetadataTest_1200, CallsCloseOnScopeExitEvenWhenSizeThrows_1200) {
  TestBasicIo* io = nullptr;
  auto img = makeImageWithIo(&io, /*io_size=*/0);

  ASSERT_NE(img, nullptr);
  ASSERT_NE(io, nullptr);

  io->setThrowOnSize(true);

  // readMetadata should propagate observable exceptions from BasicIo.
  EXPECT_THROW(img->readMetadata(), std::runtime_error);

  // External interaction: IoCloser in readMetadata should ensure close happens
  // even on exception (observable via our BasicIo double).
  EXPECT_GE(io->openCalls(), 1);
  EXPECT_GE(io->closeCalls(), 1);
}

TEST_F(BmffImageReadMetadataTest_1200, PropagatesExceptionWhenOpenThrows_1200) {
  TestBasicIo* io = nullptr;
  auto img = makeImageWithIo(&io, /*io_size=*/0);

  ASSERT_NE(img, nullptr);
  ASSERT_NE(io, nullptr);

  io->setThrowOnOpen(true);

  // Observable error case: openOrThrow() ultimately depends on io_->open().
  EXPECT_THROW(img->readMetadata(), std::runtime_error);

  // If open throws, close may or may not be called depending on when RAII engages;
  // we only assert open was attempted.
  EXPECT_GE(io->openCalls(), 1);
}

TEST_F(BmffImageReadMetadataTest_1200, DoesNotModifyClearedStateWhenCalledTwiceOnEmptyFile_1200) {
  TestBasicIo* io = nullptr;
  auto img = makeImageWithIo(&io, /*io_size=*/0);

  ASSERT_NE(img, nullptr);
  ASSERT_NE(io, nullptr);

  EXPECT_NO_THROW(img->readMetadata());

  // After first call, metadata should be empty.
  EXPECT_TRUE(img->comment().empty());
  EXPECT_TRUE(img->exifData().empty());
  EXPECT_TRUE(img->iptcData().empty());
  EXPECT_TRUE(img->xmpData().empty());
  EXPECT_TRUE(img->xmpPacket().empty());

  // Seed metadata and ensure second call clears again (idempotent w.r.t. clearing).
  seedSomeMetadata(*img);
  ASSERT_FALSE(img->exifData().empty());

  EXPECT_NO_THROW(img->readMetadata());

  EXPECT_TRUE(img->comment().empty());
  EXPECT_TRUE(img->exifData().empty());
  EXPECT_TRUE(img->iptcData().empty());
  EXPECT_TRUE(img->xmpData().empty());
  EXPECT_TRUE(img->xmpPacket().empty());
}