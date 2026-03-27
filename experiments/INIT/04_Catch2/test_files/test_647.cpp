// File: string_streams_release_tests_647.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <vector>

// Assume the real headers are available in your build.
// If paths differ, adjust includes accordingly.
#include "catch2/internal/catch_reusable_string_stream.cpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using Catch::StringStreams;

class StringStreamsTest_647 : public ::testing::Test {
protected:
    StringStreams ss_;
};

// Verifies that release() restores the stream's formatting state from m_referenceStream
TEST_F(StringStreamsTest_647, ReleaseRestoresFormatting_647) {
    // Arrange: create a stream and intentionally change its formatting
    const std::size_t idx = ss_.add();
    auto& os = *ss_.m_streams[idx];

    // Make the stream have different formatting than the reference
    os.setf(std::ios::dec, std::ios::basefield);
    os.setf(std::ios::showpos);
    os.unsetf(std::ios::uppercase);
    os.precision(2);
    os.fill('~');
    os.width(3);

    // Configure reference stream to a known, distinct format
    ss_.m_referenceStream.setf(std::ios::hex, std::ios::basefield);
    ss_.m_referenceStream.setf(std::ios::showbase);
    ss_.m_referenceStream.setf(std::ios::uppercase);
    ss_.m_referenceStream.unsetf(std::ios::showpos);
    ss_.m_referenceStream.precision(7);
    ss_.m_referenceStream.fill('*');
    ss_.m_referenceStream.width(11);

    // Act
    ss_.release(idx);

    // Assert: formatting matches reference
    EXPECT_EQ(os.flags(), ss_.m_referenceStream.flags());
    EXPECT_EQ(os.precision(), ss_.m_referenceStream.precision());
    EXPECT_EQ(os.fill(), ss_.m_referenceStream.fill());
    EXPECT_EQ(os.width(), ss_.m_referenceStream.width());
}

// Verifies that release() records the index into m_unused exactly once per call
TEST_F(StringStreamsTest_647, ReleasePushesIndexToUnused_647) {
    const std::size_t idx = ss_.add();
    const auto before_size = ss_.m_unused.size();

    ss_.release(idx);

    ASSERT_EQ(ss_.m_unused.size(), before_size + 1);
    EXPECT_EQ(ss_.m_unused.back(), idx);
}

// Calling release() twice on the same index pushes it twice (observable behavior)
TEST_F(StringStreamsTest_647, ReleaseCalledTwicePushesTwice_647) {
    const std::size_t idx = ss_.add();
    const auto before_size = ss_.m_unused.size();

    ss_.release(idx);
    ss_.release(idx);

    ASSERT_EQ(ss_.m_unused.size(), before_size + 2);
    EXPECT_EQ(ss_.m_unused[ss_.m_unused.size() - 2], idx);
    EXPECT_EQ(ss_.m_unused.back(), idx);
}

// Functional check: after release, the stream behaves according to reference formatting during output
TEST_F(StringStreamsTest_647, ReleasedStreamUsesReferenceFormattingOnOutput_647) {
    const std::size_t idx = ss_.add();
    auto& os = *ss_.m_streams[idx];

    // Give the stream some conflicting formatting
    os.setf(std::ios::dec, std::ios::basefield);
    os.unsetf(std::ios::showbase);
    os.unsetf(std::ios::uppercase);
    os.precision(3);
    os.fill('?');

    // Set reference to hex + showbase + uppercase
    ss_.m_referenceStream.setf(std::ios::hex, std::ios::basefield);
    ss_.m_referenceStream.setf(std::ios::showbase);
    ss_.m_referenceStream.setf(std::ios::uppercase);

    // Act: release should copy the reference formatting to the stream
    ss_.release(idx);

    // Clear content/state and perform a write to observe formatting behavior
    os.str(std::string{});
    os.clear();
    os << 255;

    // With hex + showbase + uppercase, 255 should format as "0XFF"
    EXPECT_EQ(os.str(), "0XFF");
}
