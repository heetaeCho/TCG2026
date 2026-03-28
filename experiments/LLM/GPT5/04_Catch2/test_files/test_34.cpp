// File: test_testspec_ostream_34.cpp
#include <gtest/gtest.h>
#include <sstream>

// SUT header (path from your build; adjust if needed)
#include "catch2/catch_test_spec.hpp"

using Catch::TestSpec;

namespace {

// We intentionally do not inspect or depend on TestSpec's internals or its
// serialized content. All checks are on observable stream behavior only.

TEST(TestSpecOstream_34, ReturnsSameStream_34) {
    const TestSpec spec;               // treat as black box, default-constructed
    std::ostringstream os;

    std::ostream& returned = (os << spec);

    // The insertion operator must return the same stream by reference.
    EXPECT_EQ(&returned, static_cast<std::ostream*>(&os));
}

TEST(TestSpecOstream_34, SupportsChaining_34) {
    const TestSpec spec;
    std::ostringstream os;

    // Chaining should work because operator<< returns std::ostream&.
    (os << spec) << "TAIL";

    // We do not assume anything about what TestSpec prints.
    // We only assert that subsequent insertions appear after it.
    const std::string s = os.str();
    ASSERT_GE(s.size(), std::size_t{4});  // "TAIL" is 4 chars; ensures something was written or at least tail is present
    ASSERT_GE(s.size(), std::string("TAIL").size());
    // Check the stream ends with what we appended after writing the TestSpec.
    EXPECT_EQ(s.substr(s.size() - 4), "TAIL");
}

TEST(TestSpecOstream_34, PreservesFailbitState_34) {
    const TestSpec spec;
    std::ostringstream os;

    // Put the stream into a failed state beforehand.
    os.setstate(std::ios::failbit);
    ASSERT_TRUE(os.fail());

    // Inserting the TestSpec into a failed stream should not clear the state,
    // and must still return the same stream reference.
    std::ostream& ret = (os << spec);
    EXPECT_EQ(&ret, static_cast<std::ostream*>(&os));
    EXPECT_TRUE(os.fail());  // state is preserved (observable via the public stream API)
}

} // namespace
