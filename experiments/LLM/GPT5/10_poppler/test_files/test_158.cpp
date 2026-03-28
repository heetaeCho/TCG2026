// TEST_ID is 158
// Unit tests for CachedFileStream::getChar (poppler/Stream.h)

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "CachedFile.h"
#include "Stream.h"
#include "goo/GooString.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::SaveArg;

namespace {

class MockCachedFileLoader : public CachedFileLoader {
public:
  MOCK_METHOD(size_t, init, (GooString *uri, CachedFile *cachedFile), (override));
  MOCK_METHOD(int, load, (const std::vector<ByteRange> &ranges, CachedFileWriter *writer), (override));
};

class CachedFileStreamTest_158 : public ::testing::Test {
protected:
  static Object MakeNullDict() {
    Object dict;
    dict.initNull();
    return dict;
  }

  // Creates a CachedFileStream backed by a mocked CachedFileLoader.
  // - data: bytes the loader will provide
  // - start: stream start offset
  // - limited/length: stream limits
  //
  // The mock loader's load() will write requested byte ranges from `data` into the writer.
  std::unique_ptr<CachedFileStream> MakeStream(const std::vector<unsigned char> &data, Goffset start,
                                               bool limited, Goffset length) {
    data_ = data;
    seenRanges_.clear();

    // uri and CachedFile lifetime:
    // CachedFile has a private destructor; in production it's managed via ref counting.
    // For the purpose of these unit tests, we intentionally keep it alive for the test duration
    // and avoid deleting it.
    uri_.reset(new GooString("mock://cached-file"));

    loader_ = std::make_unique<NiceMock<MockCachedFileLoader>>();

    EXPECT_CALL(*loader_, init(_, _))
        .WillOnce([&](GooString * /*uri*/, CachedFile * /*cachedFile*/) { return data_.size(); });

    // Default: successful loads that write out the requested bytes.
    ON_CALL(*loader_, load(_, _))
        .WillByDefault([&](const std::vector<ByteRange> &ranges, CachedFileWriter *writer) -> int {
          // Record ranges for interaction verification.
          seenRanges_.insert(seenRanges_.end(), ranges.begin(), ranges.end());

          // Write each requested range sequentially into the writer.
          for (const auto &r : ranges) {
            const size_t off = static_cast<size_t>(r.offset);
            const size_t len = static_cast<size_t>(r.length);

            if (off > data_.size()) {
              // Out-of-range request: write nothing for this range.
              continue;
            }
            const size_t canWrite = std::min(len, data_.size() - off);
            if (canWrite > 0) {
              const char *ptr = reinterpret_cast<const char *>(data_.data() + off);
              (void)writer->write(ptr, canWrite);
            }
          }
          return 0;
        });

    auto *cfRaw = new CachedFile(loader_.get(), uri_.get());
    // Avoid deletion; CachedFile's destructor is private and ref-count managed.
    std::shared_ptr<CachedFile> cf(cfRaw, [](CachedFile *) {});

    Object dict = MakeNullDict();
    return std::make_unique<CachedFileStream>(cf, start, limited, length, std::move(dict));
  }

  // Returns true if any observed ByteRange covers `pos`.
  bool AnyRangeCovers(Goffset pos) const {
    const auto p = static_cast<Guint>(pos);
    for (const auto &r : seenRanges_) {
      const Guint start = r.offset;
      const Guint end = start + r.length; // unsigned wrap is fine for typical sizes here
      if (r.length != 0 && start <= p && p < end) return true;
    }
    return false;
  }

  std::vector<unsigned char> data_;
  std::vector<ByteRange> seenRanges_;

  std::unique_ptr<GooString> uri_;
  std::unique_ptr<NiceMock<MockCachedFileLoader>> loader_;
};

TEST_F(CachedFileStreamTest_158, ReadsBytesInOrderAndThenEOF_158) {
  const std::vector<unsigned char> bytes = {0x00, 0x01, 0x7f, 0x80, 0xff};
  auto s = MakeStream(bytes, /*start=*/0, /*limited=*/true, /*length=*/static_cast<Goffset>(bytes.size()));

  EXPECT_EQ(s->getChar(), 0);
  EXPECT_EQ(s->getChar(), 1);
  EXPECT_EQ(s->getChar(), 127);
  EXPECT_EQ(s->getChar(), 128);
  EXPECT_EQ(s->getChar(), 255);
  EXPECT_EQ(s->getChar(), EOF);
  EXPECT_EQ(s->getChar(), EOF); // stays at EOF
}

TEST_F(CachedFileStreamTest_158, RespectsStartOffsetAndLengthLimit_158) {
  const std::vector<unsigned char> bytes = {'A', 'B', 'C', 'D', 'E'};
  auto s = MakeStream(bytes, /*start=*/2, /*limited=*/true, /*length=*/2);

  EXPECT_EQ(s->getChar(), 'C');
  EXPECT_EQ(s->getChar(), 'D');
  EXPECT_EQ(s->getChar(), EOF);
}

TEST_F(CachedFileStreamTest_158, Interaction_LoadProvidesDataCoveringFirstReadPosition_158) {
  const std::vector<unsigned char> bytes = {'x', 'y', 'z'};
  const Goffset start = 1;
  auto s = MakeStream(bytes, /*start=*/start, /*limited=*/true, /*length=*/2);

  // Force at least one load call by setting an explicit expectation (while still using default behavior).
  EXPECT_CALL(*loader_, load(_, _)).Times(AtLeast(1));

  EXPECT_EQ(s->getChar(), 'y');

  // Verify that the loader was asked for a range that covers the requested stream start position.
  EXPECT_TRUE(AnyRangeCovers(start));
}

TEST_F(CachedFileStreamTest_158, WhenLoaderFails_GetCharReturnsEOF_158) {
  const std::vector<unsigned char> bytes = {'a', 'b', 'c'};
  auto s = MakeStream(bytes, /*start=*/0, /*limited=*/true, /*length=*/3);

  // Override: loader fails to load any data.
  ON_CALL(*loader_, load(_, _)).WillByDefault(Return(1));

  EXPECT_EQ(s->getChar(), EOF);
}

TEST_F(CachedFileStreamTest_158, ZeroLengthStreamReturnsEOF_158) {
  const std::vector<unsigned char> bytes = {'n', 'o', 'p'};
  auto s = MakeStream(bytes, /*start=*/0, /*limited=*/true, /*length=*/0);

  EXPECT_EQ(s->getChar(), EOF);
  EXPECT_EQ(s->getChar(), EOF);
}

} // namespace