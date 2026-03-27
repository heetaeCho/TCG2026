// File: yaml-cpp/node/detail/impl_test_665.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "yaml-cpp/node/detail/impl.h"

namespace {

using NodePtr = YAML::detail::node*;

class RemoveFunctionTest_665 : public ::testing::Test {
protected:
  static NodePtr Ptr(std::uintptr_t v) {
    return reinterpret_cast<NodePtr>(v);
  }

  static std::vector<NodePtr> MakeSeq(std::initializer_list<std::uintptr_t> vals) {
    std::vector<NodePtr> out;
    out.reserve(vals.size());
    for (auto v : vals) out.push_back(Ptr(v));
    return out;
  }
};

TEST_F(RemoveFunctionTest_665, RemoveOnEmptySequenceReturnsFalseAndNoSeqSizeChange_665) {
  std::vector<NodePtr> seq;
  std::size_t seqSize = 0;

  const bool ok = YAML::detail::remove(seq, static_cast<std::size_t>(0), seqSize);

  EXPECT_FALSE(ok);
  EXPECT_TRUE(seq.empty());
  EXPECT_EQ(seqSize, 0u);
}

TEST_F(RemoveFunctionTest_665, KeyEqualToVectorSizeReturnsFalseAndDoesNotModify_665) {
  auto seq = MakeSeq({0x10, 0x11, 0x12});
  const auto before = seq;
  std::size_t seqSize = 3;

  const bool ok = YAML::detail::remove(seq, static_cast<std::size_t>(3), seqSize);

  EXPECT_FALSE(ok);
  EXPECT_EQ(seq.size(), before.size());
  EXPECT_EQ(seq, before);
  EXPECT_EQ(seqSize, 3u);
}

TEST_F(RemoveFunctionTest_665, KeyGreaterThanVectorSizeReturnsFalseAndDoesNotModify_665) {
  auto seq = MakeSeq({0x21, 0x22});
  const auto before = seq;
  std::size_t seqSize = 2;

  const bool ok = YAML::detail::remove(seq, static_cast<std::size_t>(99), seqSize);

  EXPECT_FALSE(ok);
  EXPECT_EQ(seq, before);
  EXPECT_EQ(seqSize, 2u);
}

TEST_F(RemoveFunctionTest_665, RemovesFirstElementAndDecrementsSeqSizeWhenSeqSizeGreaterThanKey_665) {
  auto seq = MakeSeq({0x31, 0x32, 0x33});
  std::size_t seqSize = 3;

  const bool ok = YAML::detail::remove(seq, static_cast<std::size_t>(0), seqSize);

  ASSERT_TRUE(ok);
  ASSERT_EQ(seq.size(), 2u);
  EXPECT_EQ(seq[0], Ptr(0x32));
  EXPECT_EQ(seq[1], Ptr(0x33));
  EXPECT_EQ(seqSize, 2u);  // seqSize > key(0) so it should decrement
}

TEST_F(RemoveFunctionTest_665, RemovesMiddleElementAndPreservesRelativeOrder_665) {
  auto seq = MakeSeq({0x41, 0x42, 0x43, 0x44});
  std::size_t seqSize = 4;

  const bool ok = YAML::detail::remove(seq, static_cast<std::size_t>(1), seqSize);

  ASSERT_TRUE(ok);
  ASSERT_EQ(seq.size(), 3u);
  EXPECT_EQ(seq[0], Ptr(0x41));
  EXPECT_EQ(seq[1], Ptr(0x43));
  EXPECT_EQ(seq[2], Ptr(0x44));
  EXPECT_EQ(seqSize, 3u);  // seqSize > key(1)
}

TEST_F(RemoveFunctionTest_665, RemovesLastElementAndDecrementsSeqSizeWhenSeqSizeGreaterThanKey_665) {
  auto seq = MakeSeq({0x51, 0x52, 0x53});
  std::size_t seqSize = 3;

  const bool ok = YAML::detail::remove(seq, static_cast<std::size_t>(2), seqSize);

  ASSERT_TRUE(ok);
  ASSERT_EQ(seq.size(), 2u);
  EXPECT_EQ(seq[0], Ptr(0x51));
  EXPECT_EQ(seq[1], Ptr(0x52));
  EXPECT_EQ(seqSize, 2u);  // seqSize > key(2)
}

TEST_F(RemoveFunctionTest_665, SeqSizeNotDecrementedWhenSeqSizeEqualsKey_665) {
  auto seq = MakeSeq({0x61, 0x62, 0x63});
  std::size_t seqSize = 1;  // equals key below

  const bool ok = YAML::detail::remove(seq, static_cast<std::size_t>(1), seqSize);

  ASSERT_TRUE(ok);
  ASSERT_EQ(seq.size(), 2u);
  EXPECT_EQ(seq[0], Ptr(0x61));
  EXPECT_EQ(seq[1], Ptr(0x63));
  EXPECT_EQ(seqSize, 1u);  // seqSize > key is false when seqSize == key
}

TEST_F(RemoveFunctionTest_665, SeqSizeNotDecrementedWhenSeqSizeLessThanKey_665) {
  auto seq = MakeSeq({0x71, 0x72, 0x73, 0x74});
  std::size_t seqSize = 1;  // less than key below

  const bool ok = YAML::detail::remove(seq, static_cast<std::size_t>(3), seqSize);

  ASSERT_TRUE(ok);
  ASSERT_EQ(seq.size(), 3u);
  EXPECT_EQ(seq[0], Ptr(0x71));
  EXPECT_EQ(seq[1], Ptr(0x72));
  EXPECT_EQ(seq[2], Ptr(0x73));
  EXPECT_EQ(seqSize, 1u);  // seqSize > key is false when seqSize < key
}

TEST_F(RemoveFunctionTest_665, MultipleRemovalsUpdateVectorAndSeqSizeAccordingly_665) {
  auto seq = MakeSeq({0x81, 0x82, 0x83, 0x84});
  std::size_t seqSize = 4;

  ASSERT_TRUE(YAML::detail::remove(seq, static_cast<std::size_t>(1), seqSize));  // remove 0x82
  EXPECT_EQ(seqSize, 3u);
  ASSERT_EQ(seq.size(), 3u);
  EXPECT_EQ(seq[0], Ptr(0x81));
  EXPECT_EQ(seq[1], Ptr(0x83));
  EXPECT_EQ(seq[2], Ptr(0x84));

  ASSERT_TRUE(YAML::detail::remove(seq, static_cast<std::size_t>(1), seqSize));  // remove 0x83
  EXPECT_EQ(seqSize, 2u);
  ASSERT_EQ(seq.size(), 2u);
  EXPECT_EQ(seq[0], Ptr(0x81));
  EXPECT_EQ(seq[1], Ptr(0x84));
}

}  // namespace