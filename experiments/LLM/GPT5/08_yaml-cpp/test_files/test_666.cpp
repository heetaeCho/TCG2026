// TEST_ID: 666
#include <gtest/gtest.h>

#include <cstddef>
#include <stdexcept>
#include <vector>

// --- Test seam for remove_idx<std::size_t> delegation ---
// We declare the primary template (with a default Enable=void) and provide a full
// specialization for <std::size_t, void> that records calls.
// This lets us verify YAML::detail::remove(...) delegates correctly, without
// re-implementing yaml-cpp logic.
namespace YAML {
namespace detail {

struct node;  // forward decl (the production header uses node*)

template <typename Key, typename Enable = void>
struct remove_idx;

// Full specialization used by YAML::detail::remove(...) for non-negative keys.
template <>
struct remove_idx<std::size_t, void> {
  inline static int call_count = 0;
  inline static const std::vector<node*>* last_sequence_addr = nullptr;
  inline static const std::size_t* last_key_addr = nullptr;
  inline static std::size_t last_key_value = 0;
  inline static std::size_t* last_seqSize_addr = nullptr;

  inline static bool return_value = false;
  inline static bool should_throw = false;

  static void Reset() {
    call_count = 0;
    last_sequence_addr = nullptr;
    last_key_addr = nullptr;
    last_key_value = 0;
    last_seqSize_addr = nullptr;
    return_value = false;
    should_throw = false;
  }

  static bool remove(std::vector<node*>& sequence, const std::size_t& key,
                     std::size_t& seqSize) {
    ++call_count;
    last_sequence_addr = &sequence;
    last_key_addr = &key;
    last_key_value = key;
    last_seqSize_addr = &seqSize;

    if (should_throw) {
      throw std::runtime_error("remove_idx forced throw");
    }
    return return_value;
  }
};

}  // namespace detail
}  // namespace YAML

// Include after the seam so YAML::detail::remove uses our specialization.
#include "yaml-cpp/node/detail/impl.h"

namespace {

class DetailRemoveTest_666 : public ::testing::Test {
 protected:
  void SetUp() override { YAML::detail::remove_idx<std::size_t, void>::Reset(); }
};

TEST_F(DetailRemoveTest_666, NegativeKeyReturnsFalseAndDoesNotDelegate_666) {
  std::vector<YAML::detail::node*> seq = {nullptr, nullptr};
  std::size_t seqSize = 2;

  const int key = -1;
  const bool result = YAML::detail::remove(seq, key, seqSize);

  EXPECT_FALSE(result);
  EXPECT_EQ(YAML::detail::remove_idx<std::size_t, void>::call_count, 0);

  // Negative path should not touch arguments in any observable way.
  EXPECT_EQ(seq.size(), 2u);
  EXPECT_EQ(seqSize, 2u);
}

TEST_F(DetailRemoveTest_666, ZeroKeyDelegatesWithCastAndPropagatesTrue_666) {
  std::vector<YAML::detail::node*> seq = {nullptr};
  std::size_t seqSize = 1;

  YAML::detail::remove_idx<std::size_t, void>::return_value = true;

  const int key = 0;
  const bool result = YAML::detail::remove(seq, key, seqSize);

  EXPECT_TRUE(result);
  EXPECT_EQ(YAML::detail::remove_idx<std::size_t, void>::call_count, 1);

  EXPECT_EQ(YAML::detail::remove_idx<std::size_t, void>::last_sequence_addr,
            &seq);
  EXPECT_EQ(YAML::detail::remove_idx<std::size_t, void>::last_seqSize_addr,
            &seqSize);
  EXPECT_EQ(YAML::detail::remove_idx<std::size_t, void>::last_key_value,
            static_cast<std::size_t>(key));
}

TEST_F(DetailRemoveTest_666, PositiveKeyDelegatesWithCastAndPropagatesFalse_666) {
  std::vector<YAML::detail::node*> seq = {nullptr, nullptr, nullptr};
  std::size_t seqSize = 3;

  YAML::detail::remove_idx<std::size_t, void>::return_value = false;

  const int key = 2;
  const bool result = YAML::detail::remove(seq, key, seqSize);

  EXPECT_FALSE(result);
  EXPECT_EQ(YAML::detail::remove_idx<std::size_t, void>::call_count, 1);
  EXPECT_EQ(YAML::detail::remove_idx<std::size_t, void>::last_key_value,
            static_cast<std::size_t>(key));
}

TEST_F(DetailRemoveTest_666, LargeNonNegativeKeyIsPassedAsSizeT_666) {
  std::vector<YAML::detail::node*> seq;
  std::size_t seqSize = 0;

  YAML::detail::remove_idx<std::size_t, void>::return_value = true;

  const int key = 123456789;  // large but non-negative
  const bool result = YAML::detail::remove(seq, key, seqSize);

  EXPECT_TRUE(result);
  EXPECT_EQ(YAML::detail::remove_idx<std::size_t, void>::call_count, 1);
  EXPECT_EQ(YAML::detail::remove_idx<std::size_t, void>::last_key_value,
            static_cast<std::size_t>(key));
}

TEST_F(DetailRemoveTest_666, NonNegativeKeyPropagatesExceptionFromRemoveIdx_666) {
  std::vector<YAML::detail::node*> seq = {nullptr};
  std::size_t seqSize = 1;

  YAML::detail::remove_idx<std::size_t, void>::should_throw = true;

  const int key = 0;
  EXPECT_THROW((void)YAML::detail::remove(seq, key, seqSize), std::runtime_error);
  EXPECT_EQ(YAML::detail::remove_idx<std::size_t, void>::call_count, 1);
}

TEST_F(DetailRemoveTest_666, NegativeKeyDoesNotTriggerExceptionFromRemoveIdx_666) {
  std::vector<YAML::detail::node*> seq = {nullptr};
  std::size_t seqSize = 1;

  YAML::detail::remove_idx<std::size_t, void>::should_throw = true;

  const int key = -10;
  EXPECT_NO_THROW({
    const bool result = YAML::detail::remove(seq, key, seqSize);
    EXPECT_FALSE(result);
  });

  EXPECT_EQ(YAML::detail::remove_idx<std::size_t, void>::call_count, 0);
}

}  // namespace