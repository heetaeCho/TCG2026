// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 2167
//
// Unit tests for Exiv2::CommentValue (constructor behavior in value.cpp)
// Constraints respected:
// - Treat implementation as black box
// - Only use public interface / observable behavior
// - No private state access

#include <gtest/gtest.h>

#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

namespace {

class CommentValueTest_2167 : public ::testing::Test {
 protected:
  static std::string ToWrittenString(const Exiv2::CommentValue& v) {
    std::ostringstream os;
    v.write(os);
    return os.str();
  }
};

TEST_F(CommentValueTest_2167, ConstructWithStringMatchesReadOnDefault_2167) {
  const std::string input = "simple comment";

  Exiv2::CommentValue constructed(input);

  Exiv2::CommentValue readLater;
  ASSERT_NO_THROW({
    const int rc = readLater.read(input);
    (void)rc;  // black box: only ensure callable
  });

  EXPECT_EQ(ToWrittenString(constructed), ToWrittenString(readLater));
  EXPECT_EQ(constructed.size(), readLater.size());
  EXPECT_EQ(constructed.count(), readLater.count());
}

TEST_F(CommentValueTest_2167, EmptyStringConstructionIsConsistent_2167) {
  const std::string input;

  Exiv2::CommentValue constructed(input);

  Exiv2::CommentValue readLater;
  const int rc = readLater.read(input);
  (void)rc;

  EXPECT_EQ(ToWrittenString(constructed), ToWrittenString(readLater));
  EXPECT_EQ(constructed.size(), readLater.size());
  EXPECT_EQ(constructed.count(), readLater.count());
}

TEST_F(CommentValueTest_2167, LargeStringConstructionIsConsistent_2167) {
  const std::string input(10000, 'x');  // boundary-ish without being too heavy

  Exiv2::CommentValue constructed(input);

  Exiv2::CommentValue readLater;
  const int rc = readLater.read(input);
  (void)rc;

  EXPECT_EQ(ToWrittenString(constructed), ToWrittenString(readLater));
  EXPECT_EQ(constructed.size(), readLater.size());
  EXPECT_EQ(constructed.count(), readLater.count());
}

TEST_F(CommentValueTest_2167, EmbeddedNullBytesAreHandledConsistently_2167) {
  const char raw[] = {'A', 'B', 'C', '\0', 'D', 'E', 'F'};
  const std::string input(raw, sizeof(raw));

  Exiv2::CommentValue constructed(input);

  Exiv2::CommentValue readLater;
  const int rc = readLater.read(input);
  (void)rc;

  EXPECT_EQ(ToWrittenString(constructed), ToWrittenString(readLater));
  EXPECT_EQ(constructed.size(), readLater.size());
  EXPECT_EQ(constructed.count(), readLater.count());
}

TEST_F(CommentValueTest_2167, CopyThenReadByteBufferProducesEquivalentWrite_2167) {
  const std::string input = "roundtrip via copy/read(byte*)";

  Exiv2::CommentValue original(input);

  const size_t sz = original.size();
  std::vector<Exiv2::byte> buf(sz == 0 ? 1 : sz);

  // copy() returns the number of bytes written (observable); buffer size is based on size().
  const size_t written = original.copy(buf.data(), Exiv2::littleEndian);

  Exiv2::CommentValue roundTripped;
  const int rc = roundTripped.read(buf.data(), written, Exiv2::littleEndian);
  (void)rc;

  EXPECT_EQ(ToWrittenString(original), ToWrittenString(roundTripped));
  EXPECT_EQ(original.size(), roundTripped.size());
  EXPECT_EQ(original.count(), roundTripped.count());
}

TEST_F(CommentValueTest_2167, CloneProducesEquivalentObservableState_2167) {
  const std::string input = "clone me";
  Exiv2::CommentValue original(input);

  auto cloned = original.clone();
  ASSERT_NE(cloned.get(), nullptr);

  // Compare observable behavior via write/size/count.
  const auto* asComment = dynamic_cast<const Exiv2::CommentValue*>(cloned.get());
  ASSERT_NE(asComment, nullptr);

  EXPECT_EQ(ToWrittenString(original), ToWrittenString(*asComment));
  EXPECT_EQ(original.size(), asComment->size());
  EXPECT_EQ(original.count(), asComment->count());
}

TEST_F(CommentValueTest_2167, CommentAndCharsetApisAreCallable_2167) {
  const std::string input = "charset probing input";
  Exiv2::CommentValue v(input);

  EXPECT_NO_THROW({
    const std::string s1 = v.comment("UTF-8");
    const std::string s2 = v.comment("Ascii");
    (void)s1;
    (void)s2;
  });

  EXPECT_NO_THROW({
    const auto cs = v.charsetId();
    (void)cs;
  });

  EXPECT_NO_THROW({
    std::string tmp = input;
    const char* p = v.detectCharset(tmp);
    (void)p;
  });
}

}  // namespace