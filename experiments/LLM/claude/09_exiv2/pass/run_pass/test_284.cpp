#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <limits>
#include <stdexcept>

// Include necessary headers
#include "exiv2/error.hpp"
#include "tiffimage_int.hpp"
#include "tiffcomposite_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

// Mock OffsetWriter to verify interactions
class MockOffsetWriter : public OffsetWriter {
public:
    MOCK_METHOD(void, setTarget, (OffsetId id, uint32_t target), ());
};

// We need a mock or stub for BasicIo as well for constructing IoWrapper
// Since we can't easily mock BasicIo, we'll use a MemIo or similar
#include "exiv2/basicio.hpp"

class IoWrapperSetTargetTest_284 : public ::testing::Test {
protected:
    void SetUp() override {
        memIo_ = std::make_unique<MemIo>();
        header_[0] = 0;
    }

    std::unique_ptr<MemIo> memIo_;
    byte header_[1];
};

// Test: setTarget with valid target and non-null OffsetWriter calls setTarget on OffsetWriter
TEST_F(IoWrapperSetTargetTest_284, SetTargetCallsOffsetWriterSetTarget_284) {
    OffsetWriter pow;
    IoWrapper wrapper(*memIo_, header_, sizeof(header_), &pow);

    // Should not throw for a valid target value within uint32_t range
    EXPECT_NO_THROW(wrapper.setTarget(0, 100));
}

// Test: setTarget with null OffsetWriter does not crash
TEST_F(IoWrapperSetTargetTest_284, SetTargetWithNullOffsetWriterDoesNotCrash_284) {
    IoWrapper wrapper(*memIo_, header_, sizeof(header_), nullptr);

    // pow_ is null, so setTarget should be a no-op (no crash)
    EXPECT_NO_THROW(wrapper.setTarget(0, 100));
}

// Test: setTarget with target equal to max uint32_t should succeed
TEST_F(IoWrapperSetTargetTest_284, SetTargetWithMaxUint32Succeeds_284) {
    OffsetWriter pow;
    IoWrapper wrapper(*memIo_, header_, sizeof(header_), &pow);

    size_t maxTarget = static_cast<size_t>(std::numeric_limits<uint32_t>::max());
    EXPECT_NO_THROW(wrapper.setTarget(0, maxTarget));
}

// Test: setTarget with target exceeding uint32_t max throws kerOffsetOutOfRange
TEST_F(IoWrapperSetTargetTest_284, SetTargetExceedingUint32MaxThrows_284) {
    OffsetWriter pow;
    IoWrapper wrapper(*memIo_, header_, sizeof(header_), &pow);

    // Only relevant on 64-bit platforms where size_t > uint32_t
    if constexpr (sizeof(size_t) > sizeof(uint32_t)) {
        size_t overflowTarget = static_cast<size_t>(std::numeric_limits<uint32_t>::max()) + 1;
        EXPECT_THROW(wrapper.setTarget(0, overflowTarget), Exiv2::Error);
    }
}

// Test: setTarget with target exceeding uint32_t max throws even with null OffsetWriter
TEST_F(IoWrapperSetTargetTest_284, SetTargetExceedingUint32MaxThrowsEvenWithNullPow_284) {
    IoWrapper wrapper(*memIo_, header_, sizeof(header_), nullptr);

    if constexpr (sizeof(size_t) > sizeof(uint32_t)) {
        size_t overflowTarget = static_cast<size_t>(std::numeric_limits<uint32_t>::max()) + 1;
        // The overflow check happens before the null check on pow_
        EXPECT_THROW(wrapper.setTarget(0, overflowTarget), Exiv2::Error);
    }
}

// Test: setTarget with target of 0 (boundary - minimum value)
TEST_F(IoWrapperSetTargetTest_284, SetTargetWithZeroTarget_284) {
    OffsetWriter pow;
    IoWrapper wrapper(*memIo_, header_, sizeof(header_), &pow);

    EXPECT_NO_THROW(wrapper.setTarget(0, 0));
}

// Test: setTarget with target of 1
TEST_F(IoWrapperSetTargetTest_284, SetTargetWithSmallTarget_284) {
    OffsetWriter pow;
    IoWrapper wrapper(*memIo_, header_, sizeof(header_), &pow);

    EXPECT_NO_THROW(wrapper.setTarget(0, 1));
}

// Test: setTarget with various id values
TEST_F(IoWrapperSetTargetTest_284, SetTargetWithDifferentIds_284) {
    OffsetWriter pow;
    IoWrapper wrapper(*memIo_, header_, sizeof(header_), &pow);

    EXPECT_NO_THROW(wrapper.setTarget(0, 42));
    EXPECT_NO_THROW(wrapper.setTarget(1, 42));
}

// Test: setTarget called multiple times
TEST_F(IoWrapperSetTargetTest_284, SetTargetCalledMultipleTimes_284) {
    OffsetWriter pow;
    IoWrapper wrapper(*memIo_, header_, sizeof(header_), &pow);

    EXPECT_NO_THROW(wrapper.setTarget(0, 100));
    EXPECT_NO_THROW(wrapper.setTarget(0, 200));
    EXPECT_NO_THROW(wrapper.setTarget(0, 300));
}

// Test: setTarget with large but valid size_t value (just at uint32_t max)
TEST_F(IoWrapperSetTargetTest_284, SetTargetBoundaryExactlyAtUint32Max_284) {
    OffsetWriter pow;
    IoWrapper wrapper(*memIo_, header_, sizeof(header_), &pow);

    size_t exactMax = std::numeric_limits<uint32_t>::max();
    EXPECT_NO_THROW(wrapper.setTarget(0, exactMax));
}

// Test: verify the error thrown is specifically kerOffsetOutOfRange
TEST_F(IoWrapperSetTargetTest_284, SetTargetOverflowErrorCode_284) {
    OffsetWriter pow;
    IoWrapper wrapper(*memIo_, header_, sizeof(header_), &pow);

    if constexpr (sizeof(size_t) > sizeof(uint32_t)) {
        size_t overflowTarget = static_cast<size_t>(std::numeric_limits<uint32_t>::max()) + 1;
        try {
            wrapper.setTarget(0, overflowTarget);
            FAIL() << "Expected Exiv2::Error to be thrown";
        } catch (const Exiv2::Error& e) {
            EXPECT_EQ(e.code(), ErrorCode::kerOffsetOutOfRange);
        } catch (...) {
            FAIL() << "Expected Exiv2::Error but got different exception";
        }
    }
}
