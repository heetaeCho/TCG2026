// File: test_iptcdatum_copy_663.cpp
#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

namespace {

struct SpyState {
  int calls = 0;
  Exiv2::byte* lastBuf = nullptr;
  Exiv2::ByteOrder lastOrder = Exiv2::invalidByteOrder;
  size_t ret = 0;
};

// A minimal Value test-double that lets us observe copy(buf, byteOrder) calls.
// It also overrides clone_() so that if Iptcdatum clones the passed Value,
// the cloned instance shares the same SpyState (observable by the test).
class SpyValue : public Exiv2::Value {
 public:
  explicit SpyValue(size_t ret, std::shared_ptr<SpyState> st = std::make_shared<SpyState>())
      : Exiv2::Value(static_cast<Exiv2::TypeId>(0)), st_(std::move(st)) {
    st_->ret = ret;
  }

  std::shared_ptr<SpyState> state() const { return st_; }

  size_t copy(Exiv2::byte* buf, Exiv2::ByteOrder byteOrder) override {
    st_->calls++;
    st_->lastBuf = buf;
    st_->lastOrder = byteOrder;
    return st_->ret;
  }

 private:
  // Value::clone() calls the private virtual clone_(); overriding is allowed.
  const Exiv2::Value* clone_() override { return new SpyValue(*this); }

  std::shared_ptr<SpyState> st_;
};

class IptcdatumTest_663 : public ::testing::Test {
 protected:
  static Exiv2::IptcKey MakeKey() {
    // Most Exiv2 builds accept string keys like this.
    return Exiv2::IptcKey("Iptc.Application2.ObjectName");
  }
};

TEST_F(IptcdatumTest_663, CopyReturnsZeroWhenNoValue_663) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum d(key, nullptr);

  std::vector<Exiv2::byte> buf(8, 0);

  EXPECT_EQ(d.copy(buf.data(), Exiv2::littleEndian), 0u);
  EXPECT_EQ(d.copy(nullptr, Exiv2::bigEndian), 0u);
}

TEST_F(IptcdatumTest_663, CopyForwardsBufferAndByteOrderAndReturnsValueResult_663) {
  const Exiv2::IptcKey key = MakeKey();

  SpyValue spy(/*ret=*/7);
  auto st = spy.state();

  Exiv2::Iptcdatum d(key, &spy);

  std::vector<Exiv2::byte> buf(16, 0);

  const size_t ret = d.copy(buf.data(), Exiv2::littleEndian);
  EXPECT_EQ(ret, 7u);

  EXPECT_EQ(st->calls, 1);
  EXPECT_EQ(st->lastBuf, buf.data());
  EXPECT_EQ(st->lastOrder, Exiv2::littleEndian);
}

TEST_F(IptcdatumTest_663, CopyAcceptsNullBufferAndStillDelegatesWhenValuePresent_663) {
  const Exiv2::IptcKey key = MakeKey();

  SpyValue spy(/*ret=*/3);
  auto st = spy.state();

  Exiv2::Iptcdatum d(key, &spy);

  const size_t ret = d.copy(nullptr, Exiv2::bigEndian);
  EXPECT_EQ(ret, 3u);

  EXPECT_EQ(st->calls, 1);
  EXPECT_EQ(st->lastBuf, nullptr);
  EXPECT_EQ(st->lastOrder, Exiv2::bigEndian);
}

TEST_F(IptcdatumTest_663, CopyMultipleCallsAreIndependentlyForwarded_663) {
  const Exiv2::IptcKey key = MakeKey();

  SpyValue spy(/*ret=*/11);
  auto st = spy.state();

  Exiv2::Iptcdatum d(key, &spy);

  std::vector<Exiv2::byte> a(4, 0);
  std::vector<Exiv2::byte> b(5, 0);

  EXPECT_EQ(d.copy(a.data(), Exiv2::littleEndian), 11u);
  EXPECT_EQ(st->calls, 1);
  EXPECT_EQ(st->lastBuf, a.data());
  EXPECT_EQ(st->lastOrder, Exiv2::littleEndian);

  EXPECT_EQ(d.copy(b.data(), Exiv2::bigEndian), 11u);
  EXPECT_EQ(st->calls, 2);
  EXPECT_EQ(st->lastBuf, b.data());
  EXPECT_EQ(st->lastOrder, Exiv2::bigEndian);
}

}  // namespace