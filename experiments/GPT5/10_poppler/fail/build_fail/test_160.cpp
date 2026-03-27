// TEST_ID = 160
// Unit tests for CachedFileStream::getPos
//
// File: ./TestProjects/poppler/poppler/Stream.h
//
// Constraints respected:
// - Treat implementation as black box (no private access, no reimplementation of logic).
// - Use only public interfaces / observable behavior.
// - Provide normal + boundary + error-ish observable cases.

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Poppler headers (paths may vary depending on your test build setup).
#include "poppler/Stream.h"
#include "poppler/CachedFile.h"
#include "poppler/goo/GooString.h"
#include "poppler/Object.h"

namespace {

// ---------- Small detection helpers (to tolerate minor API differences) ----------

template <typename T>
struct has_decRefCnt {
  template <typename U>
  static auto test(int) -> decltype(std::declval<U&>().decRefCnt(), std::true_type{});
  template <typename>
  static auto test(...) -> std::false_type;
  static constexpr bool value = decltype(test<T>(0))::value;
};

template <typename T>
struct has_incRefCnt {
  template <typename U>
  static auto test(int) -> decltype(std::declval<U&>().incRefCnt(), std::true_type{});
  template <typename>
  static auto test(...) -> std::false_type;
  static constexpr bool value = decltype(test<T>(0))::value;
};

static std::shared_ptr<CachedFile> makeSharedCachedFileRaw(CachedFile* p) {
  // If CachedFile uses internal refcounting (older Poppler), prefer decRefCnt().
  if constexpr (has_decRefCnt<CachedFile>::value) {
    // Assume newly created CachedFile has refCnt=1 (typical); shared_ptr deleter will drop it.
    return std::shared_ptr<CachedFile>(p, [](CachedFile* x) { x->decRefCnt(); });
  } else {
    return std::shared_ptr<CachedFile>(p);
  }
}

// A simple in-memory CachedFileLoader implementation.
// It serves a fixed byte buffer and supports byte-range loads.
class InMemoryCachedFileLoader final : public CachedFileLoader {
public:
  explicit InMemoryCachedFileLoader(std::string data) : data_(std::move(data)) {}

  size_t init(GooString* /*uri*/, CachedFile* /*cachedFile*/) override {
    // Contract: return file length.
    return data_.size();
  }

  int load(const std::vector<ByteRange>& ranges, CachedFileWriter* writer) override {
    // Best-effort: write requested ranges sequentially.
    // Returns 0 on success.
    for (const auto& r : ranges) {
      const size_t off = static_cast<size_t>(r.offset);
      const size_t len = static_cast<size_t>(r.length);
      if (off >= data_.size()) {
        // Nothing to write for this range; still treat as success.
        continue;
      }
      const size_t n = std::min(len, data_.size() - off);
      (void)writer->write(data_.data() + off, n);
    }
    return 0;
  }

private:
  std::string data_;
};

// Create a CachedFile instance in a way that tolerates common signature variants.
static std::shared_ptr<CachedFile> CreateCachedFileFromMemory(std::string bytes) {
  // Keep the loader alive at least as long as CachedFile.
  // We'll hand it over via a shared_ptr captured in the custom deleter if needed.
  auto loader = std::make_shared<InMemoryCachedFileLoader>(std::move(bytes));

  // Some Poppler versions use: CachedFile(CachedFileLoader*, GooString*)
  // Others may have different ownership patterns; we try a couple of common ones.
  if constexpr (std::is_constructible_v<CachedFile, CachedFileLoader*, GooString*>) {
    auto* uri = new GooString("mem://cached-file");
    CachedFile* raw = new CachedFile(loader.get(), uri);

    // Ensure loader stays alive while CachedFile exists.
    // If CachedFile does not own uri, this is a leak; however, in common Poppler code
    // CachedFile takes ownership of uri (see header comments in older versions).
    // We avoid relying on that; this is test-only and mirrors typical usage.
    auto sp = makeSharedCachedFileRaw(raw);
    return std::shared_ptr<CachedFile>(sp.get(), [sp, loader](CachedFile*) mutable {
      // Drop sp first (invokes proper deleter), then loader.
      sp.reset();
      loader.reset();
    });
  } else if constexpr (std::is_constructible_v<CachedFile, CachedFileLoader*, std::unique_ptr<GooString>>) {
    auto uri = std::make_unique<GooString>("mem://cached-file");
    auto cf = std::make_shared<CachedFile>(loader.get(), std::move(uri));
    // Tie loader lifetime to cf.
    return std::shared_ptr<CachedFile>(cf.get(), [cf, loader](CachedFile*) mutable {
      (void)cf;
      loader.reset();
    });
  } else {
    // Last-resort: fail loudly at runtime with a clear message.
    // (We avoid compile-time static_assert that would block builds for variants.)
    ADD_FAILURE() << "Unsupported CachedFile constructor signature in this Poppler version.";
    return {};
  }
}

// Construct an Object that represents a null dictionary object in a tolerant way.
static Object MakeNullObject() {
  // Common Poppler pattern: Object(objNull)
  // If that constructor isn't available, try default + initNull().
  if constexpr (std::is_constructible_v<Object, ObjType>) {
    return Object(objNull);
  } else {
    Object o;
    // Some versions have initNull()
    if constexpr (requires(Object& x) { x.initNull(); }) {
      o.initNull();
    }
    return o;
  }
}

class CachedFileStreamTest_160 : public ::testing::Test {
protected:
  void SetUp() override {
    // Create deterministic contents.
    // Large enough to exercise buffering if implementation uses it.
    std::string data;
    data.reserve(4096);
    for (int i = 0; i < 4096; ++i) {
      data.push_back(static_cast<char>('A' + (i % 26)));
    }

    cachedFile_ = CreateCachedFileFromMemory(data);
    ASSERT_TRUE(static_cast<bool>(cachedFile_));

    const Goffset start = 0;
    const bool limited = false;
    const Goffset length = static_cast<Goffset>(data.size());

    Object dict = MakeNullObject();
    stream_ = std::make_unique<CachedFileStream>(cachedFile_, start, limited, length, std::move(dict));
  }

  std::shared_ptr<CachedFile> cachedFile_;
  std::unique_ptr<CachedFileStream> stream_;
};

}  // namespace

// ---- Normal operation ----

TEST_F(CachedFileStreamTest_160, InitialGetPosEqualsGetStart_160) {
  ASSERT_NE(stream_, nullptr);
  // Observable invariant: immediately after construction, position should be at start.
  EXPECT_EQ(stream_->getPos(), stream_->getStart());
}

TEST_F(CachedFileStreamTest_160, SetPosForwardUpdatesGetPos_160) {
  ASSERT_NE(stream_, nullptr);

  stream_->setPos(0, /*dir=*/0);
  EXPECT_EQ(stream_->getPos(), 0);

  stream_->setPos(17, /*dir=*/0);
  EXPECT_EQ(stream_->getPos(), 17);

  stream_->setPos(123, /*dir=*/0);
  EXPECT_EQ(stream_->getPos(), 123);
}

TEST_F(CachedFileStreamTest_160, ReadingACharAdvancesGetPosByOneWhenNotEof_160) {
  ASSERT_NE(stream_, nullptr);

  stream_->setPos(0, /*dir=*/0);
  const Goffset before = stream_->getPos();

  const int c = stream_->getChar();
  if (c == EOF) {
    // If EOF is returned at position 0 (unexpected for our in-memory data), at least verify
    // position doesn't move backwards.
    EXPECT_GE(stream_->getPos(), before);
  } else {
    // Typical stream behavior: consuming one char advances by 1.
    EXPECT_EQ(stream_->getPos(), before + 1);
  }
}

TEST_F(CachedFileStreamTest_160, LookCharDoesNotAdvanceGetPos_160) {
  ASSERT_NE(stream_, nullptr);

  stream_->setPos(10, /*dir=*/0);
  const Goffset before = stream_->getPos();

  (void)stream_->lookChar();
  EXPECT_EQ(stream_->getPos(), before);

  // Repeated lookChar should also not advance.
  (void)stream_->lookChar();
  EXPECT_EQ(stream_->getPos(), before);
}

// ---- Boundary conditions ----

TEST_F(CachedFileStreamTest_160, SetPosToEndThenGetCharReturnsEofOrKeepsPosAtEnd_160) {
  ASSERT_NE(stream_, nullptr);

  const Goffset endPos = stream_->getStart() + stream_->getLength();
  stream_->setPos(endPos, /*dir=*/0);
  EXPECT_EQ(stream_->getPos(), endPos);

  const int c = stream_->getChar();
  EXPECT_TRUE(c == EOF || stream_->getPos() >= endPos);
}

TEST_F(CachedFileStreamTest_160, RewindResetsGetPosToStart_160) {
  ASSERT_NE(stream_, nullptr);

  stream_->setPos(50, /*dir=*/0);
  ASSERT_EQ(stream_->getPos(), 50);

  const bool ok = stream_->rewind();
  // Even if rewind reports failure (implementation-dependent), we can still check
  // that getPos never goes negative and (on success) equals start.
  EXPECT_GE(stream_->getPos(), 0);
  if (ok) {
    EXPECT_EQ(stream_->getPos(), stream_->getStart());
  }
}

// ---- Error-ish / robustness cases (observable only) ----

TEST_F(CachedFileStreamTest_160, SetPosFromEndDirNegativeKeepsGetPosWithinStreamBounds_160) {
  ASSERT_NE(stream_, nullptr);

  // We do not assume exact "dir < 0" semantics; we only assert bounds that should hold
  // for a well-behaved stream.
  const Goffset len = stream_->getLength();
  stream_->setPos(1, /*dir=*/-1);
  const Goffset p1 = stream_->getPos();
  EXPECT_GE(p1, 0);
  EXPECT_LE(p1, stream_->getStart() + len);

  // Large "pos" from end should not produce out-of-range positions.
  stream_->setPos(len + 9999, /*dir=*/-1);
  const Goffset p2 = stream_->getPos();
  EXPECT_GE(p2, 0);
  EXPECT_LE(p2, stream_->getStart() + len);
}