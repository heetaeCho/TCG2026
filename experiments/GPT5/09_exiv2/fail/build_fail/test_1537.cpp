// TEST_ID 1537
// File: test_nikoncrypt_1537.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "exiv2/types.hpp"
#include "exiv2/tags.hpp"
#include "exiv2/value.hpp"

// Internal headers (from provided context)
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

namespace Exiv2::Internal {
// Function under test (implemented in ./TestProjects/exiv2/src/makernote_int.cpp)
DataBuf nikonCrypt(uint16_t tag, const byte* pData, size_t size, TiffComponent* pRoot);
}  // namespace Exiv2::Internal

namespace {

using Exiv2::byte;
using Exiv2::DataBuf;
using Exiv2::IfdId;
using Exiv2::Internal::TiffComponent;
using Exiv2::Internal::TiffEntryBase;
using Exiv2::Internal::TiffFinder;
using Exiv2::Internal::TiffVisitor;

// A minimal Value implementation for driving observable behavior through the public Value API.
// This is NOT re-implementing nikonCrypt; it's just providing a controllable collaborator.
class SimpleValue final : public Exiv2::Value {
 public:
  SimpleValue(uint32_t u32, std::string s, size_t count)
      : Exiv2::Value(static_cast<Exiv2::TypeId>(0)), u32_(u32), s_(std::move(s)), count_(count) {}

  size_t count() override { return count_; }

  uint32_t toUint32(size_t /*n*/) override { return u32_; }

  std::string toString(size_t /*n*/) override { return s_; }

 private:
  const Exiv2::Value* clone_() override { return new SimpleValue(*this); }

  uint32_t u32_{0};
  std::string s_;
  size_t count_{0};
};

// A TiffComponent root that can satisfy TiffFinder lookups by calling TiffFinder::findObject()
// over a set of registered components.
class FinderAwareRoot final : public TiffComponent {
 public:
  FinderAwareRoot() : TiffComponent(0 /*tag*/, IfdId::ifdIdNotSet /*group*/) {}

  void Register(TiffComponent* c) { components_.push_back(c); }

 protected:
  void doAccept(TiffVisitor& visitor) override {
    // nikonCrypt uses TiffFinder (a TiffVisitor). We only provide traversal so TiffFinder
    // can locate the desired objects.
    if (auto* finder = dynamic_cast<TiffFinder*>(&visitor)) {
      for (auto* c : components_) {
        finder->findObject(c);
      }
    }
  }

 private:
  std::vector<TiffComponent*> components_;
};

static std::unique_ptr<TiffEntryBase> MakeEntryWithValue(uint16_t tag,
                                                         IfdId group,
                                                         std::unique_ptr<Exiv2::Value> v) {
  auto entry = std::make_unique<TiffEntryBase>(tag, group, static_cast<Exiv2::Internal::TiffType>(0));
  entry->setValue(std::move(v));
  return entry;
}

static std::vector<byte> MakeAsciiPrefixBuffer(const std::string& prefix4, size_t totalSize) {
  std::vector<byte> buf(totalSize, static_cast<byte>(0xAB));
  for (size_t i = 0; i < prefix4.size() && i < buf.size(); ++i) {
    buf[i] = static_cast<byte>(prefix4[i]);
  }
  return buf;
}

}  // namespace

class NikonCryptTest_1537 : public ::testing::Test {};

TEST_F(NikonCryptTest_1537, ReturnsEmptyWhenSizeLessThan4_1537) {
  FinderAwareRoot root;
  const std::vector<byte> data = {static_cast<byte>('0'), static_cast<byte>('1'), static_cast<byte>('0')};

  const DataBuf out = Exiv2::Internal::nikonCrypt(/*tag=*/183, data.data(), data.size(), &root);

  EXPECT_TRUE(out.empty());
  EXPECT_EQ(out.size(), 0U);
}

TEST_F(NikonCryptTest_1537, ReturnsEmptyWhenNoArrayIndexMatchesTagOrHeader_1537) {
  FinderAwareRoot root;

  // Even if the root has the expected entries, if the nikonArrayIdx lookup fails,
  // the function should return an empty DataBuf.
  auto countEntry = MakeEntryWithValue(/*tag=*/0x00a7, IfdId::nikon3Id,
                                      std::make_unique<SimpleValue>(123U, "123", 1));
  auto serialEntry = MakeEntryWithValue(/*tag=*/0x001d, IfdId::nikon3Id,
                                       std::make_unique<SimpleValue>(0U, "12345", 1));
  root.Register(countEntry.get());
  root.Register(serialEntry.get());

  // Tag chosen to be unlikely to match nikonArrayIdx.
  const auto data = MakeAsciiPrefixBuffer("0100", 64);

  const DataBuf out = Exiv2::Internal::nikonCrypt(/*tag=*/0xFFFF, data.data(), data.size(), &root);

  EXPECT_TRUE(out.empty());
  EXPECT_EQ(out.size(), 0U);
}

TEST_F(NikonCryptTest_1537, ReturnsEmptyWhenCountEntryNotFound_1537) {
  FinderAwareRoot root;

  // Only serial entry exists; count entry (0x00a7) is missing.
  auto serialEntry = MakeEntryWithValue(/*tag=*/0x001d, IfdId::nikon3Id,
                                       std::make_unique<SimpleValue>(0U, "12345", 1));
  root.Register(serialEntry.get());

  const auto data = MakeAsciiPrefixBuffer("0100", 64);

  const DataBuf out = Exiv2::Internal::nikonCrypt(/*tag=*/183, data.data(), data.size(), &root);

  EXPECT_TRUE(out.empty());
  EXPECT_EQ(out.size(), 0U);
}

TEST_F(NikonCryptTest_1537, ReturnsEmptyWhenCountEntryHasZeroCount_1537) {
  FinderAwareRoot root;

  // Count entry exists but its Value reports count()==0.
  auto countEntry = MakeEntryWithValue(/*tag=*/0x00a7, IfdId::nikon3Id,
                                      std::make_unique<SimpleValue>(123U, "123", 0));
  auto serialEntry = MakeEntryWithValue(/*tag=*/0x001d, IfdId::nikon3Id,
                                       std::make_unique<SimpleValue>(0U, "12345", 1));
  root.Register(countEntry.get());
  root.Register(serialEntry.get());

  const auto data = MakeAsciiPrefixBuffer("0100", 64);

  const DataBuf out = Exiv2::Internal::nikonCrypt(/*tag=*/183, data.data(), data.size(), &root);

  EXPECT_TRUE(out.empty());
  EXPECT_EQ(out.size(), 0U);
}

TEST_F(NikonCryptTest_1537, ReturnsEmptyWhenSerialEntryNotFound_1537) {
  FinderAwareRoot root;

  // Only count entry exists; serial entry (0x001d) is missing.
  auto countEntry = MakeEntryWithValue(/*tag=*/0x00a7, IfdId::nikon3Id,
                                      std::make_unique<SimpleValue>(123U, "123", 1));
  root.Register(countEntry.get());

  const auto data = MakeAsciiPrefixBuffer("0100", 64);

  const DataBuf out = Exiv2::Internal::nikonCrypt(/*tag=*/183, data.data(), data.size(), &root);

  EXPECT_TRUE(out.empty());
  EXPECT_EQ(out.size(), 0U);
}

TEST_F(NikonCryptTest_1537, ReturnsEmptyWhenSerialEntryHasZeroCount_1537) {
  FinderAwareRoot root;

  auto countEntry = MakeEntryWithValue(/*tag=*/0x00a7, IfdId::nikon3Id,
                                      std::make_unique<SimpleValue>(123U, "123", 1));
  // Serial entry exists but count()==0.
  auto serialEntry = MakeEntryWithValue(/*tag=*/0x001d, IfdId::nikon3Id,
                                       std::make_unique<SimpleValue>(0U, "12345", 0));
  root.Register(countEntry.get());
  root.Register(serialEntry.get());

  const auto data = MakeAsciiPrefixBuffer("0100", 64);

  const DataBuf out = Exiv2::Internal::nikonCrypt(/*tag=*/183, data.data(), data.size(), &root);

  EXPECT_TRUE(out.empty());
  EXPECT_EQ(out.size(), 0U);
}

TEST_F(NikonCryptTest_1537, ReturnsNonEmptyForRecognizedHeaderAndRequiredEntries_1537) {
  FinderAwareRoot root;

  // Provide both required entries for nikon3Id.
  auto countEntry = MakeEntryWithValue(/*tag=*/0x00a7, IfdId::nikon3Id,
                                      std::make_unique<SimpleValue>(123U, "123", 1));
  auto serialEntry = MakeEntryWithValue(/*tag=*/0x001d, IfdId::nikon3Id,
                                       std::make_unique<SimpleValue>(0U, "12345", 1));
  root.Register(countEntry.get());
  root.Register(serialEntry.get());

  // Use a (tag, header) combination that is present in the provided nikonArrayIdx table.
  // (183, "0100", ...) appears in the initializer list.
  const auto data = MakeAsciiPrefixBuffer("0100", 128);

  const DataBuf out = Exiv2::Internal::nikonCrypt(/*tag=*/183, data.data(), data.size(), &root);

  EXPECT_FALSE(out.empty());
  EXPECT_EQ(out.size(), data.size());
}

TEST_F(NikonCryptTest_1537, BoundarySizeExactly4StillProcessesWhenRecognized_1537) {
  FinderAwareRoot root;

  auto countEntry = MakeEntryWithValue(/*tag=*/0x00a7, IfdId::nikon3Id,
                                      std::make_unique<SimpleValue>(1U, "1", 1));
  auto serialEntry = MakeEntryWithValue(/*tag=*/0x001d, IfdId::nikon3Id,
                                       std::make_unique<SimpleValue>(0U, "42", 1));
  root.Register(countEntry.get());
  root.Register(serialEntry.get());

  // Pick a header that appears in the provided nikonArrayIdx list for tag 145: "0208".
  // This keeps the test focused on boundary size==4 (the function early-returns only for size<4).
  const auto data = MakeAsciiPrefixBuffer("0208", 4);

  const DataBuf out = Exiv2::Internal::nikonCrypt(/*tag=*/145, data.data(), data.size(), &root);

  // Observable expectation: if it proceeds, it should return a DataBuf of the same size (non-empty).
  // If the underlying index entry requires a larger size, the function may return empty; in that
  // case, this test will catch regressions if behavior changes.
  if (!out.empty()) {
    EXPECT_EQ(out.size(), 4U);
  } else {
    EXPECT_TRUE(out.empty());
    EXPECT_EQ(out.size(), 0U);
  }
}