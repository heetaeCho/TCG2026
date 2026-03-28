#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

using IgnorePolicy = YAML::jkj::dragonbox::policy::sign::ignore;

struct DummyFp {
  int value{};
  friend bool operator==(const DummyFp& a, const DummyFp& b) { return a.value == b.value; }
};

TEST(DragonboxSignIgnoreTest_333, ReturnsInputUnchanged_ForUnsignedInt_333) {
  const unsigned r = 123u;
  const auto out = IgnorePolicy::handle_sign<int>(-1, r);
  EXPECT_EQ(out, r);
}

TEST(DragonboxSignIgnoreTest_333, ReturnsInputUnchanged_ForZero_333) {
  const std::uint64_t r = 0;
  const auto out = IgnorePolicy::handle_sign<std::int32_t>(0, r);
  EXPECT_EQ(out, r);
}

TEST(DragonboxSignIgnoreTest_333, ReturnsInputUnchanged_ForMaxValue_333) {
  const std::uint64_t r = (std::numeric_limits<std::uint64_t>::max)();
  const auto out = IgnorePolicy::handle_sign<std::int64_t>((std::numeric_limits<std::int64_t>::min)(), r);
  EXPECT_EQ(out, r);
}

TEST(DragonboxSignIgnoreTest_333, ReturnsInputUnchanged_ForCustomType_333) {
  const DummyFp r{42};
  const auto out = IgnorePolicy::handle_sign<std::int64_t>(-999, r);
  EXPECT_EQ(out, r);
}

TEST(DragonboxSignIgnoreTest_333, WorksInConstexprContext_333) {
  constexpr std::uint32_t r = 777u;
  constexpr auto out = IgnorePolicy::handle_sign<std::int32_t>(-1, r);
  static_assert(out == r, "ignore::handle_sign must return the input unchanged");
  EXPECT_EQ(out, r);
}

TEST(DragonboxSignIgnoreTest_333, IsNoexcept_333) {
  static_assert(noexcept(IgnorePolicy::handle_sign<std::int32_t>(-1, 1u)),
                "ignore::handle_sign should be noexcept");

  // Also exercise at runtime.
  EXPECT_TRUE((noexcept(IgnorePolicy::handle_sign<std::int32_t>(-1, 1u))));
}

TEST(DragonboxSignIgnoreTest_333, PreservesType_333) {
  const std::uint16_t r = 5;
  using OutT = decltype(IgnorePolicy::handle_sign<std::int32_t>(-1, r));
  static_assert(std::is_same<OutT, std::uint16_t>::value, "Return type must match UnsignedDecimalFp type");
  EXPECT_EQ(IgnorePolicy::handle_sign<std::int32_t>(-1, r), r);
}

}  // namespace