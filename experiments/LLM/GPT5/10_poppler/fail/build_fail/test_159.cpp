// SPDX-License-Identifier: GPL-2.0-or-later
// File: CachedFileStream_lookChar_tests_159.cc
//
// Unit tests for CachedFileStream::lookChar() (black-box).
//
// The TEST_ID is 159.

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "poppler/Stream.h"
#include "poppler/CachedFile.h"
#include "goo/GooString.h"
#include "poppler/Object.h"

using ::testing::_;
using ::testing::AllOf;
using ::testing::AtLeast;
using ::testing::ByMove;
using ::testing::DoAll;
using ::testing::ElementsAre;
using ::testing::Eq;
using ::testing::Field;
using ::testing::InSequence;
using ::testing::Invoke;
using ::testing::Return;

namespace {

class MockCachedFileLoader : public CachedFileLoader {
public:
  MOCK_METHOD(size_t, init, (GooString * uri, CachedFile * cachedFile), (override));
  MOCK_METHOD(int, load, (const std::vector<ByteRange>& ranges, CachedFileWriter* writer), (override));
};

// Simple deterministic in-memory loader (no gmock needed).
class InMemoryCachedFileLoader : public CachedFileLoader {
public:
  explicit InMemoryCachedFileLoader(std::vector<unsigned char> data) : data_(std::move(data)) {}

  size_t init(GooString* /*uri*/, CachedFile* /*cachedFile*/) override { return data_.size(); }

  int load(const std::vector<ByteRange>& ranges, CachedFileWriter* writer) override {
    // Serve requested ranges in ascending offset order. This is an implementation detail of the
    // loader only; tests do not depend on internal caching details.
    std::vector<ByteRange> sorted = ranges;
    std::sort(sorted.begin(), sorted.end(),
              [](const ByteRange& a, const ByteRange& b) { return a.offset < b.offset; });

    for (const auto& r : sorted) {
      const size_t off = r.offset;
      const size_t len = static_cast<size_t>(r.length);
      if (off > data_.size()) return 1;
      const size_t avail = data_.size() - off;
      const size_t toWrite = std::min(avail, len);
      if (toWrite > 0) {
        writer->write(reinterpret_cast<const char*>(data_.data() + off), toWrite);
      }
    }
    return 0;
  }

private:
  std::vector<unsigned char> data_;
};

struct CachedFileDeleter {
  void operator()(CachedFile* p) const {
    if (p) {
      // CachedFile is ref-counted in Poppler; decRefCnt() will delete when it reaches zero.
      p->decRefCnt();
    }
  }
};

static std::shared_ptr<CachedFile> makeCachedFile(std::unique_ptr<CachedFileLoader> loader,
                                                  const std::string& uriStr) {
  // CachedFile keeps a pointer to the loader; ensure the loader outlives CachedFile by
  // storing it in a shared_ptr control block via aliasing.
  //
  // We'll create CachedFile with raw pointers, then create a shared_ptr<CachedFile> whose
  // deleter calls decRefCnt(). We also keep the loader alive by sharing ownership with a
  // small wrapper object.
  struct Holder {
    explicit Holder(std::unique_ptr<CachedFileLoader> l) : loader(std::move(l)) {}
    std::unique_ptr<CachedFileLoader> loader;
  };

  auto holder = std::make_shared<Holder>(std::move(loader));
  auto* uri = new GooString(uriStr.c_str());

  auto* raw = new CachedFile(holder->loader.get(), uri);
  // The CachedFile internal ref count is managed by incRefCnt/decRefCnt; the constructor
  // initializes it appropriately in Poppler. We rely on decRefCnt() in the deleter.

  std::shared_ptr<CachedFile> cf(raw, CachedFileDeleter{});
  // Keep holder alive as long as cf is alive.
  return std::shared_ptr<CachedFile>(holder, cf.get());
}

static Object makeNullObject() {
  // Poppler Object APIs differ slightly across versions. The repo in this prompt uses
  // rvalue Object&& in some constructors; Object(objNull) is commonly supported.
  return Object(objNull);
}

class CachedFileStreamTest_159 : public ::testing::Test {
protected:
  std::vector<unsigned char> bytes_{
      0x00, 0x41, 0x7F, 0x80, 0xFF, 0x42,
  };

  std::unique_ptr<CachedFileStream> makeStream(Goffset start, bool limited, Goffset length) {
    auto loader = std::make_unique<InMemoryCachedFileLoader>(bytes_);
    auto cachedFile = makeCachedFile(std::move(loader), "mem://CachedFileStreamTest_159");
    return std::make_unique<CachedFileStream>(cachedFile, start, limited, length, makeNullObject());
  }
};

} // namespace

TEST_F(CachedFileStreamTest_159, LookCharReturnsFirstByteWithoutAdvancing_159) {
  auto s = makeStream(/*start=*/0, /*limited=*/true, /*length=*/static_cast<Goffset>(bytes_.size()));

  const Goffset posBefore = s->getPos();
  const int c1 = s->lookChar();
  const Goffset posAfter = s->getPos();

  ASSERT_NE(c1, EOF);
  EXPECT_EQ(c1, 0x00);
  EXPECT_EQ(posBefore, posAfter) << "lookChar() must not advance the stream position";
}

TEST_F(CachedFileStreamTest_159, LookCharIsIdempotentAtSamePosition_159) {
  auto s = makeStream(/*start=*/0, /*limited=*/true, /*length=*/static_cast<Goffset>(bytes_.size()));

  const int c1 = s->lookChar();
  const int c2 = s->lookChar();

  ASSERT_NE(c1, EOF);
  EXPECT_EQ(c1, c2);
  EXPECT_EQ(s->getPos(), static_cast<Goffset>(0));
}

TEST_F(CachedFileStreamTest_159, LookCharReflectsNextByteAfterGetChar_159) {
  auto s = makeStream(/*start=*/0, /*limited=*/true, /*length=*/static_cast<Goffset>(bytes_.size()));

  const int firstLook = s->lookChar();
  ASSERT_NE(firstLook, EOF);
  EXPECT_EQ(firstLook, 0x00);

  const int firstGet = s->getChar();
  ASSERT_NE(firstGet, EOF);
  EXPECT_EQ(firstGet, 0x00);

  const int secondLook = s->lookChar();
  ASSERT_NE(secondLook, EOF);
  EXPECT_EQ(secondLook, 0x41);
}

TEST_F(CachedFileStreamTest_159, LookCharReturnsUnsignedByteValues_159) {
  auto s = makeStream(/*start=*/0, /*limited=*/true, /*length=*/static_cast<Goffset>(bytes_.size()));

  // Advance to the 0x80 byte.
  for (int i = 0; i < 3; ++i) {
    ASSERT_NE(s->getChar(), EOF);
  }

  const int c = s->lookChar();
  ASSERT_NE(c, EOF);
  EXPECT_EQ(c, 0x80);

  // Advance to the 0xFF byte and verify it is returned as 255, not -1.
  ASSERT_NE(s->getChar(), EOF); // consume 0x80
  const int cff = s->lookChar();
  ASSERT_NE(cff, EOF);
  EXPECT_EQ(cff, 0xFF);
}

TEST_F(CachedFileStreamTest_159, LookCharReturnsEofAtEndOfLimitedStream_159) {
  auto s = makeStream(/*start=*/0, /*limited=*/true, /*length=*/static_cast<Goffset>(bytes_.size()));

  // Consume all bytes.
  for (size_t i = 0; i < bytes_.size(); ++i) {
    ASSERT_NE(s->getChar(), EOF);
  }

  EXPECT_EQ(s->lookChar(), EOF);
}

TEST_F(CachedFileStreamTest_159, LookCharReturnsEofForZeroLengthLimitedStream_159) {
  auto s = makeStream(/*start=*/0, /*limited=*/true, /*length=*/0);

  EXPECT_EQ(s->lookChar(), EOF);
  EXPECT_EQ(s->getChar(), EOF);
}

TEST_F(CachedFileStreamTest_159, LookCharAtLastByteThenEof_159) {
  ASSERT_FALSE(bytes_.empty());
  const Goffset last = static_cast<Goffset>(bytes_.size() - 1);

  auto s = makeStream(/*start=*/last, /*limited=*/true, /*length=*/1);

  const int lastLook = s->lookChar();
  ASSERT_NE(lastLook, EOF);
  EXPECT_EQ(lastLook, bytes_.back());

  const int lastGet = s->getChar();
  ASSERT_NE(lastGet, EOF);
  EXPECT_EQ(lastGet, bytes_.back());

  EXPECT_EQ(s->lookChar(), EOF);
}

TEST_F(CachedFileStreamTest_159, LookCharDoesNotTriggerExtraLoadsWhenRepeated_159) {
  // Verify external interaction via a mock loader: first lookChar should force a load,
  // a second lookChar at the same position should not require another load.
  auto mockLoader = std::make_unique<MockCachedFileLoader>();
  MockCachedFileLoader* mockPtr = mockLoader.get();

  // Prepare data.
  const std::vector<unsigned char> local{0x12, 0x34, 0x56};

  // init() should be called to report the length.
  EXPECT_CALL(*mockPtr, init(_, _)).WillOnce(Return(local.size()));

  // load() should be called at least once to satisfy the first read.
  // We don't assert exact ranges; that's an internal caching detail. We only require that
  // some load happens, and that repeating lookChar without advancing doesn't require more.
  EXPECT_CALL(*mockPtr, load(_, _))
      .WillOnce(Invoke([&](const std::vector<ByteRange>& /*ranges*/, CachedFileWriter* writer) {
        writer->write(reinterpret_cast<const char*>(local.data()), local.size());
        return 0;
      }));

  auto cachedFile = makeCachedFile(std::move(mockLoader), "mem://mock/CachedFileStreamTest_159");
  auto s = std::make_unique<CachedFileStream>(cachedFile, /*start=*/0, /*limited=*/true,
                                              /*length=*/static_cast<Goffset>(local.size()),
                                              makeNullObject());

  const int c1 = s->lookChar();
  const int c2 = s->lookChar();

  EXPECT_EQ(c1, 0x12);
  EXPECT_EQ(c2, 0x12);
}

TEST_F(CachedFileStreamTest_159, LookCharAfterSetPosReflectsNewPosition_159) {
  auto s = makeStream(/*start=*/0, /*limited=*/true, /*length=*/static_cast<Goffset>(bytes_.size()));

  // Move to the 2nd element (0x41).
  s->setPos(/*pos=*/1, /*dir=*/0);
  EXPECT_EQ(s->lookChar(), 0x41);

  // Move to the 5th element (0xFF).
  s->setPos(/*pos=*/4, /*dir=*/0);
  EXPECT_EQ(s->lookChar(), 0xFF);
}