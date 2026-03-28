// =================================================================================================
//  TEST_ID: 760
//  Unit tests for Exiv2::Exifdatum::toInt64(size_t)
//  File under test: ./TestProjects/exiv2/src/exif.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <limits>
#include <memory>

#include <exiv2/exif.hpp>
#include <exiv2/exifkey.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

namespace {

class ExifdatumToInt64Test_760 : public ::testing::Test {
 protected:
  static Exiv2::ExifKey MakeKey() {
    // Any syntactically valid Exif key is fine for constructing Exifdatum.
    return Exiv2::ExifKey("Exif.Image.Make");
  }

  struct SharedState {
    size_t calls = 0;
    size_t last_n = 0;
    int64_t ret = 0;
  };

  // A test double for Exiv2::Value that:
  // - records calls to toInt64(n)
  // - returns a configured value
  // - shares state across copies/clones, so Exifdatum's internal cloning is observable
  class RecordingValue : public Exiv2::Value {
   public:
    explicit RecordingValue(std::shared_ptr<SharedState> st, int64_t ret)
        : Exiv2::Value(Exiv2::unsignedLong), st_(std::move(st)) {
      if (st_) st_->ret = ret;
    }

    RecordingValue(const RecordingValue& rhs) = default;

    const int64_t toInt64(size_t n) override {
      if (st_) {
        st_->calls++;
        st_->last_n = n;
        return st_->ret;
      }
      return 0;
    }

   private:
    // Exiv2::Value clones via an internal virtual clone_().
    // Overriding a private virtual is fine in C++ (access control is not part of the override rules).
    const Exiv2::Value* clone_() override { return new RecordingValue(*this); }

    std::shared_ptr<SharedState> st_;
  };
};

TEST_F(ExifdatumToInt64Test_760, ReturnsMinusOneWhenValueIsNull_760) {
  const Exiv2::ExifKey key = MakeKey();

  // Construct with no Value (nullptr).
  Exiv2::Exifdatum d(key, nullptr);

  EXPECT_EQ(d.toInt64(0), -1);
  EXPECT_EQ(d.toInt64(1), -1);
  EXPECT_EQ(d.toInt64(std::numeric_limits<size_t>::max()), -1);
}

TEST_F(ExifdatumToInt64Test_760, DelegatesToValueToInt64AndReturnsItsResult_760) {
  const Exiv2::ExifKey key = MakeKey();

  auto st = std::make_shared<SharedState>();
  auto v = std::make_unique<RecordingValue>(st, /*ret=*/42);

  Exiv2::Exifdatum d(key, v.get());

  const int64_t out = d.toInt64(5);

  EXPECT_EQ(out, 42);
  ASSERT_EQ(st->calls, 1u);
  EXPECT_EQ(st->last_n, 5u);
}

TEST_F(ExifdatumToInt64Test_760, DelegationWorksForBoundaryIndexValues_760) {
  const Exiv2::ExifKey key = MakeKey();

  auto st = std::make_shared<SharedState>();
  auto v = std::make_unique<RecordingValue>(st, /*ret=*/-123);

  Exiv2::Exifdatum d(key, v.get());

  // n = 0 boundary
  EXPECT_EQ(d.toInt64(0), -123);
  EXPECT_EQ(st->calls, 1u);
  EXPECT_EQ(st->last_n, 0u);

  // n = max boundary
  EXPECT_EQ(d.toInt64(std::numeric_limits<size_t>::max()), -123);
  EXPECT_EQ(st->calls, 2u);
  EXPECT_EQ(st->last_n, std::numeric_limits<size_t>::max());
}

TEST_F(ExifdatumToInt64Test_760, CopyConstructionPreservesObservableToInt64Behavior_760) {
  const Exiv2::ExifKey key = MakeKey();

  auto st = std::make_shared<SharedState>();
  auto v = std::make_unique<RecordingValue>(st, /*ret=*/7);

  Exiv2::Exifdatum original(key, v.get());
  Exiv2::Exifdatum copy(original);

  EXPECT_EQ(copy.toInt64(3), 7);
  ASSERT_EQ(st->calls, 1u);
  EXPECT_EQ(st->last_n, 3u);

  EXPECT_EQ(original.toInt64(9), 7);
  ASSERT_EQ(st->calls, 2u);
  EXPECT_EQ(st->last_n, 9u);
}

TEST_F(ExifdatumToInt64Test_760, CopyAssignmentPreservesObservableToInt64Behavior_760) {
  const Exiv2::ExifKey key = MakeKey();

  auto st1 = std::make_shared<SharedState>();
  auto v1 = std::make_unique<RecordingValue>(st1, /*ret=*/111);
  Exiv2::Exifdatum a(key, v1.get());

  auto st2 = std::make_shared<SharedState>();
  auto v2 = std::make_unique<RecordingValue>(st2, /*ret=*/222);
  Exiv2::Exifdatum b(key, v2.get());

  // Sanity before assignment
  EXPECT_EQ(a.toInt64(1), 111);
  EXPECT_EQ(b.toInt64(2), 222);

  // Reset counters for clearer assertions
  st1->calls = 0;
  st2->calls = 0;

  b = a;

  EXPECT_EQ(b.toInt64(77), 111);
  ASSERT_EQ(st1->calls, 1u);
  EXPECT_EQ(st1->last_n, 77u);

  // After assignment, b should no longer be delegating to its old Value (observable via st2).
  EXPECT_EQ(st2->calls, 0u);
}

}  // namespace