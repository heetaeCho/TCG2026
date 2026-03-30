// File: FileStream_lookChar_tests_150.cpp
#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "poppler/Stream.h"
#include "goo/gfile.h"
#include "poppler/Object.h"

namespace {

// Create a small temp file with given bytes and return its path.
static std::string writeTempFile_150(const std::vector<unsigned char> &bytes) {
  // Use a reasonably-unique filename.
  std::string path = "poppler_filestream_lookchar_150.tmp";

  std::ofstream os(path, std::ios::binary | std::ios::trunc);
  EXPECT_TRUE(os.good());
  if (!bytes.empty()) {
    os.write(reinterpret_cast<const char *>(bytes.data()),
             static_cast<std::streamsize>(bytes.size()));
  }
  os.close();
  EXPECT_TRUE(os.good() || !os.fail()); // close() should not fail
  return path;
}

// Open a GooFile from a path. This uses a commonly-available Poppler API.
// If your local Poppler snapshot uses a different signature, adjust here.
static GooFile *openGooFile_150(const std::string &path) {
  int errCode = 0;
  GooFile *f = GooFile::open(path.c_str(), &errCode);
  EXPECT_NE(f, nullptr) << "GooFile::open failed, errCode=" << errCode;
  return f;
}

static std::unique_ptr<FileStream> makeFileStream_150(const std::string &path,
                                                      Goffset start,
                                                      bool limited,
                                                      Goffset length) {
  GooFile *gf = openGooFile_150(path);
  // FileStream takes ownership of GooFile in Poppler; do not delete gf here.
  Object dict; // default/null dict is sufficient for these interface-only tests
  return std::make_unique<FileStream>(gf, start, limited, length, std::move(dict));
}

} // namespace

class FileStreamLookCharTest_150 : public ::testing::Test {
protected:
  void TearDown() override {
    // Best-effort cleanup of temp files created by tests.
    // (If a test failed before setting tmpPath_, nothing happens.)
    if (!tmpPath_.empty()) {
      std::remove(tmpPath_.c_str());
      tmpPath_.clear();
    }
  }

  std::string tmpPath_;
};

TEST_F(FileStreamLookCharTest_150, LookCharReturnsFirstByteWithoutConsuming_150) {
  tmpPath_ = writeTempFile_150({'A', 'B', 'C'});
  auto fs = makeFileStream_150(tmpPath_, /*start=*/0, /*limited=*/false, /*length=*/0);

  const Goffset pos0 = fs->getPos();

  int c1 = fs->lookChar();
  EXPECT_EQ(c1, static_cast<int>('A'));

  // lookChar should not advance position.
  EXPECT_EQ(fs->getPos(), pos0);

  // Repeated lookChar should return the same next byte.
  int c2 = fs->lookChar();
  EXPECT_EQ(c2, static_cast<int>('A'));
  EXPECT_EQ(fs->getPos(), pos0);
}

TEST_F(FileStreamLookCharTest_150, LookCharThenGetCharConsumesAndAdvances_150) {
  tmpPath_ = writeTempFile_150({'A', 'B', 'C'});
  auto fs = makeFileStream_150(tmpPath_, /*start=*/0, /*limited=*/false, /*length=*/0);

  EXPECT_EQ(fs->lookChar(), static_cast<int>('A'));
  const Goffset pos0 = fs->getPos();

  // getChar should return the same byte and advance.
  EXPECT_EQ(fs->getChar(), static_cast<int>('A'));
  EXPECT_GT(fs->getPos(), pos0);

  // Now next byte should be visible via lookChar.
  EXPECT_EQ(fs->lookChar(), static_cast<int>('B'));
}

TEST_F(FileStreamLookCharTest_150, LookCharOnEmptyFileReturnsEOF_150) {
  tmpPath_ = writeTempFile_150({});
  auto fs = makeFileStream_150(tmpPath_, /*start=*/0, /*limited=*/false, /*length=*/0);

  EXPECT_EQ(fs->lookChar(), EOF);

  // Calling again should still be EOF and should not crash.
  EXPECT_EQ(fs->lookChar(), EOF);
}

TEST_F(FileStreamLookCharTest_150, LookCharAtEndAfterReadingAllReturnsEOF_150) {
  tmpPath_ = writeTempFile_150({'X'});
  auto fs = makeFileStream_150(tmpPath_, /*start=*/0, /*limited=*/false, /*length=*/0);

  EXPECT_EQ(fs->lookChar(), static_cast<int>('X'));
  EXPECT_EQ(fs->getChar(), static_cast<int>('X'));

  // Now at end.
  EXPECT_EQ(fs->lookChar(), EOF);
}

TEST_F(FileStreamLookCharTest_150, LookCharHonorsLimitedLengthBoundary_150) {
  tmpPath_ = writeTempFile_150({'A', 'B', 'C'});

  // Limit stream to length 1 from start.
  auto fs = makeFileStream_150(tmpPath_, /*start=*/0, /*limited=*/true, /*length=*/1);

  // Within limit: 'A'
  EXPECT_EQ(fs->lookChar(), static_cast<int>('A'));
  EXPECT_EQ(fs->getChar(), static_cast<int>('A'));

  // Past limit: should be EOF (observable boundary behavior).
  EXPECT_EQ(fs->lookChar(), EOF);
  EXPECT_EQ(fs->getChar(), EOF);
}

TEST_F(FileStreamLookCharTest_150, LookCharDoesNotChangeStartOrReportedStart_150) {
  tmpPath_ = writeTempFile_150({'A', 'B', 'C'});
  auto fs = makeFileStream_150(tmpPath_, /*start=*/0, /*limited=*/false, /*length=*/0);

  const Goffset start0 = fs->getStart();
  (void)fs->lookChar();
  EXPECT_EQ(fs->getStart(), start0);

  // Also check that lookChar doesn't affect getPos.
  const Goffset pos0 = fs->getPos();
  (void)fs->lookChar();
  EXPECT_EQ(fs->getPos(), pos0);
}