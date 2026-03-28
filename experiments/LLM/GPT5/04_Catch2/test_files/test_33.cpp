// File: filter_ostream_operator_tests_33.cpp

#include <gtest/gtest.h>
#include <sstream>

// Include the header that declares Catch::TestSpec::Filter and the operator<<
#include "catch2/catch_test_spec.hpp"

namespace {

using Catch::TestSpec;

class FilterOstreamTest_33 : public ::testing::Test {
protected:
    // Default-constructible aggregate; we do not rely on internal state.
    TestSpec::Filter filter_;
};

// [Normal] Streaming a default filter returns the same stream reference (chainable)
TEST_F(FilterOstreamTest_33, StreamReturnsSameStreamReference_33) {
    std::ostringstream oss;
    std::ostream& ret = (oss << filter_);
    EXPECT_EQ(&ret, static_cast<std::ostream*>(&oss));
}

// [Normal] Streaming can be chained with other outputs without breaking them
TEST_F(FilterOstreamTest_33, StreamIsChainableWithOtherWrites_33) {
    std::ostringstream oss;
    oss << "BEGIN:";
    oss << filter_;
    oss << ":END";

    const std::string s = oss.str();

    // We do not assert what the filter prints (black box); we only check
    // that our surrounding writes are intact and in order.
    ASSERT_GE(s.size(), std::string("BEGIN::END").size()); // at least our markers
    EXPECT_EQ(0u, s.find("BEGIN:"));                       // starts with prefix
    EXPECT_EQ(s.size() - 4u, s.rfind(":END"));             // ends with suffix
}

// [Boundary] Streaming an empty/default-constructed filter does not throw
TEST_F(FilterOstreamTest_33, StreamingDefaultConstructedFilterDoesNotThrow_33) {
    std::ostringstream oss;
    EXPECT_NO_THROW(oss << filter_);
}

// [Boundary] Supports multiple consecutive insertions into the same stream
TEST_F(FilterOstreamTest_33, MultipleConsecutiveInsertionsAppend_33) {
    std::ostringstream oss;
    oss << filter_;
    const auto after_first = oss.str();
    oss << filter_;
    const auto after_second = oss.str();

    // We don't know the exact content; we can only assert that the second
    // insertion did not shrink or corrupt previously written data.
    EXPECT_LE(after_first.size(), after_second.size());
}

// [Interaction with std::ostream state] Operator returns a usable stream for further writes
TEST_F(FilterOstreamTest_33, StreamRemainsUsableAfterInsertion_33) {
    std::ostringstream oss;
    (oss << filter_) << "tail";
    const std::string s = oss.str();
    ASSERT_GE(s.size(), std::string("tail").size());
    EXPECT_EQ(s.size() - 4u, s.rfind("tail"));
}

} // namespace
