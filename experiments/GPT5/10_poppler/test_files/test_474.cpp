// TEST_ID: 474
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "poppler/GfxState.h"

using ::testing::_;
using ::testing::Throw;

namespace {

class MockGfxColorSpace : public GfxColorSpace {
public:
  MOCK_METHOD(void, createMapping,
              (std::vector<std::unique_ptr<GfxSeparationColorSpace>> * separationList,
               size_t maxSepComps),
              (override));
};

class GfxIndexedColorSpaceTest_474 : public ::testing::Test {};

TEST_F(GfxIndexedColorSpaceTest_474, CreateMapping_ForwardsArgsToBase_474) {
  auto base = std::make_unique<MockGfxColorSpace>();
  auto *basePtr = base.get();

  GfxIndexedColorSpace cs(std::move(base), /*indexHighA=*/0);

  std::vector<std::unique_ptr<GfxSeparationColorSpace>> separationList;
  const size_t maxSepComps = 7;

  EXPECT_CALL(*basePtr, createMapping(&separationList, maxSepComps)).Times(1);

  cs.createMapping(&separationList, maxSepComps);
}

TEST_F(GfxIndexedColorSpaceTest_474, CreateMapping_AllowsNullListPointer_474) {
  auto base = std::make_unique<MockGfxColorSpace>();
  auto *basePtr = base.get();

  GfxIndexedColorSpace cs(std::move(base), /*indexHighA=*/1);

  const size_t maxSepComps = 0;

  EXPECT_CALL(*basePtr, createMapping(nullptr, maxSepComps)).Times(1);

  cs.createMapping(nullptr, maxSepComps);
}

TEST_F(GfxIndexedColorSpaceTest_474, CreateMapping_ForwardsLargeMaxSepComps_474) {
  auto base = std::make_unique<MockGfxColorSpace>();
  auto *basePtr = base.get();

  GfxIndexedColorSpace cs(std::move(base), /*indexHighA=*/255);

  std::vector<std::unique_ptr<GfxSeparationColorSpace>> separationList;
  const size_t maxSepComps = static_cast<size_t>(-1);

  EXPECT_CALL(*basePtr, createMapping(&separationList, maxSepComps)).Times(1);

  cs.createMapping(&separationList, maxSepComps);
}

TEST_F(GfxIndexedColorSpaceTest_474, CreateMapping_PropagatesExceptionFromBase_474) {
  auto base = std::make_unique<MockGfxColorSpace>();
  auto *basePtr = base.get();

  GfxIndexedColorSpace cs(std::move(base), /*indexHighA=*/2);

  std::vector<std::unique_ptr<GfxSeparationColorSpace>> separationList;
  const size_t maxSepComps = 3;

  EXPECT_CALL(*basePtr, createMapping(&separationList, maxSepComps))
      .WillOnce(Throw(std::runtime_error("base error")));

  EXPECT_THROW(cs.createMapping(&separationList, maxSepComps), std::runtime_error);
}

} // namespace