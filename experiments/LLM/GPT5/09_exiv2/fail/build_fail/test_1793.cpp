// =================================================================================================
// File:        test_ciffcomponent_remove_1793.cpp
// Description: Unit tests for Exiv2::Internal::CiffComponent::remove forwarding behavior
// TEST_ID:     1793
// =================================================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "crwimage_int.hpp"  // Exiv2::Internal::CiffComponent, CrwDirs

#include <cstdint>
#include <stdexcept>

namespace {

using ::testing::_;
using ::testing::Throw;

class MockCiffComponent_1793 : public Exiv2::Internal::CiffComponent {
public:
  MockCiffComponent_1793() = default;

protected:
  MOCK_METHOD(void, doRemove, (Exiv2::Internal::CrwDirs& crwDirs, uint16_t crwTagId), (override));
};

class CiffComponentRemoveTest_1793 : public ::testing::Test {
protected:
  MockCiffComponent_1793 sut_;
};

TEST_F(CiffComponentRemoveTest_1793, ForwardsCallsDoRemove_1793) {
  Exiv2::Internal::CrwDirs dirs{};
  const uint16_t tagId = 0x1234;

  EXPECT_CALL(sut_, doRemove(::testing::Ref(dirs), tagId)).Times(1);

  sut_.remove(dirs, tagId);
}

TEST_F(CiffComponentRemoveTest_1793, ForwardsZeroTagId_1793) {
  Exiv2::Internal::CrwDirs dirs{};
  const uint16_t tagId = 0;

  EXPECT_CALL(sut_, doRemove(::testing::Ref(dirs), tagId)).Times(1);

  sut_.remove(dirs, tagId);
}

TEST_F(CiffComponentRemoveTest_1793, ForwardsMaxTagId_1793) {
  Exiv2::Internal::CrwDirs dirs{};
  const uint16_t tagId = static_cast<uint16_t>(0xFFFF);

  EXPECT_CALL(sut_, doRemove(::testing::Ref(dirs), tagId)).Times(1);

  sut_.remove(dirs, tagId);
}

TEST_F(CiffComponentRemoveTest_1793, PropagatesExceptionFromDoRemove_1793) {
  Exiv2::Internal::CrwDirs dirs{};
  const uint16_t tagId = 0x00AA;

  EXPECT_CALL(sut_, doRemove(::testing::Ref(dirs), tagId))
      .WillOnce(Throw(std::runtime_error("doRemove failed")));

  EXPECT_THROW(sut_.remove(dirs, tagId), std::runtime_error);
}

}  // namespace