// FlateEncoder_test_1649.cpp
#include <gtest/gtest.h>

#include "FlateEncoder.h"
#include "Stream.h"

// These headers are commonly available in Poppler builds; used only to create a minimal Stream.
#include "Object.h"

namespace {

static Stream *MakeEmptyInputStream_1649(std::unique_ptr<Stream> &holder)
{
  // Create an empty in-memory stream as the input to FlateEncoder.
  static const unsigned char kEmptyBuf[] = {0};

  Object dict;
  dict.initNull();

  // MemStream constructor signatures can vary slightly across Poppler versions.
  // This matches common Poppler signatures used in many trees.
  holder = std::unique_ptr<Stream>(new MemStream(kEmptyBuf, 0, 0, std::move(dict)));
  return holder.get();
}

class FlateEncoderTest_1649 : public ::testing::Test {
protected:
  std::unique_ptr<Stream> inputHolder;
};

} // namespace

TEST_F(FlateEncoderTest_1649, GetKindReturnsStrWeird_1649)
{
  Stream *in = MakeEmptyInputStream_1649(inputHolder);
  FlateEncoder enc(in);

  EXPECT_EQ(enc.getKind(), strWeird);
}

TEST_F(FlateEncoderTest_1649, GetKindIsStableAcrossMultipleCalls_1649)
{
  Stream *in = MakeEmptyInputStream_1649(inputHolder);
  FlateEncoder enc(in);

  const StreamKind k1 = enc.getKind();
  const StreamKind k2 = enc.getKind();

  EXPECT_EQ(k1, strWeird);
  EXPECT_EQ(k2, strWeird);
  EXPECT_EQ(k1, k2);
}

TEST_F(FlateEncoderTest_1649, GetKindCallableOnConstObject_1649)
{
  Stream *in = MakeEmptyInputStream_1649(inputHolder);
  FlateEncoder enc(in);

  const FlateEncoder &cenc = enc;
  EXPECT_EQ(cenc.getKind(), strWeird);
}

TEST_F(FlateEncoderTest_1649, GetKindUnaffectedByRewindCall_1649)
{
  Stream *in = MakeEmptyInputStream_1649(inputHolder);
  FlateEncoder enc(in);

  // Observable behavior: regardless of whether rewind succeeds/fails, getKind is constant.
  (void)enc.rewind();

  EXPECT_EQ(enc.getKind(), strWeird);
}