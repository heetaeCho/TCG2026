// File: tests/reporter_helpers_defaultListListeners_822.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

// SUT header(s)
#include "catch2/reporters/catch_reporter_helpers.hpp"

// Minimal public types used by the SUT interface.
// We assume ListenerDescription exposes `name` and `description` fields that are
// convertible to std::string (as implied by the production code).
// Include the real header if available; otherwise, this forward declaration
// matches the public surface used by the SUT.
#include "catch2/internal/catch_list.hpp"
#include "catch2/internal/catch_stringref.hpp"

using Catch::defaultListListeners;

// A tiny helper to build ListenerDescription without relying on any private state.
// If the real ListenerDescription provides a constructor, prefer using it directly.
static Catch::ListenerDescription makeDesc(const std::string& name,
                                           const std::string& description) {
    Catch::ListenerDescription d;
    // Assign through the public fields used by the SUT (name/description).
    d.name = Catch::StringRef{name.c_str(), name.size()};
    d.description = Catch::StringRef{description.c_str(), description.size()};
    return d;
}

// Custom streambuf to observe flushes caused by std::flush manipulator.
// We verify only whether a flush was requested (observable via rdbuf()->pubsync()).
class FlushCountingStringBuf : public std::stringbuf {
public:
    int sync() override {
        ++flush_count_;
        return std::stringbuf::sync();
    }
    int flushCount() const { return flush_count_; }
private:
    int flush_count_ = 0;
};

// ========== Tests ==========

TEST(DefaultListListeners_822, EmptyDescriptions_PrintsHeaderOnly_822) {
    std::ostringstream out;
    std::vector<Catch::ListenerDescription> descs;

    defaultListListeners(out, descs);

    const std::string s = out.str();
    // Exactly the header and trailing newline, because early-return prevents
    // the final extra newline + flush.
    EXPECT_EQ(s, std::string("Registered listeners:\n"));
}

TEST(DefaultListListeners_822, SingleListener_PrintsHeaderAndEntry_822) {
    FlushCountingStringBuf buf;
    std::ostream out(&buf);

    std::vector<Catch::ListenerDescription> descs;
    descs.push_back(makeDesc("Alpha", "Does A"));

    defaultListListeners(out, descs);

    const std::string s = static_cast<std::string>(buf.str());

    // Must include the header.
    EXPECT_NE(s.find("Registered listeners:\n"), std::string::npos);
    // Must include the listener name (with a colon added by SUT).
    EXPECT_NE(s.find("Alpha:"), std::string::npos);
    // Must include the description text somewhere.
    EXPECT_NE(s.find("Does A"), std::string::npos);

    // For non-empty input, SUT writes an extra '\n' at the end and flushes.
    ASSERT_FALSE(s.empty());
    EXPECT_GE(buf.flushCount(), 1);
    EXPECT_GE(s.size(), 2u);
    EXPECT_EQ(s.substr(s.size() - 2), std::string("\n\n"));
}

TEST(DefaultListListeners_822, MultipleListeners_AllEntriesAppear_822) {
    std::ostringstream out;

    std::vector<Catch::ListenerDescription> descs;
    descs.push_back(makeDesc("A", "first"));
    descs.push_back(makeDesc("LongestName", "second"));
    descs.push_back(makeDesc("Mid", "third"));

    defaultListListeners(out, descs);

    const std::string s = out.str();

    // Header present
    EXPECT_NE(s.find("Registered listeners:\n"), std::string::npos);

    // All names (with trailing ':') present
    EXPECT_NE(s.find("A:"), std::string::npos);
    EXPECT_NE(s.find("LongestName:"), std::string::npos);
    EXPECT_NE(s.find("Mid:"), std::string::npos);

    // All descriptions present
    EXPECT_NE(s.find("first"), std::string::npos);
    EXPECT_NE(s.find("second"), std::string::npos);
    EXPECT_NE(s.find("third"), std::string::npos);

    // Since our descriptions are short, each entry should fit on one line.
    // Expected newlines: header(1) + each entry(1) + final extra(1) = 1 + 3 + 1 = 5
    // We only assert a lower bound of 5 to avoid coupling to internal wrapping.
    size_t nlCount = std::count(s.begin(), s.end(), '\n');
    EXPECT_GE(nlCount, 5u);

    // Ends with a blank line for non-empty input.
    ASSERT_GE(s.size(), 2u);
    EXPECT_EQ(s.substr(s.size() - 2), std::string("\n\n"));
}

TEST(DefaultListListeners_822, VeryLongNameAndDescription_DoesNotThrow_822) {
    FlushCountingStringBuf buf;
    std::ostream out(&buf);

    std::string longName(200, 'N');
    std::string longDesc(300, 'D');

    std::vector<Catch::ListenerDescription> descs;
    descs.push_back(makeDesc(longName, longDesc));

    // Should not throw or crash; we only check observable output contains data.
    ASSERT_NO_THROW(defaultListListeners(out, descs));

    const std::string s = static_cast<std::string>(buf.str());
    EXPECT_NE(s.find("Registered listeners:\n"), std::string::npos);
    // Name printed with ":" appended by SUT
    EXPECT_NE(s.find(std::string(longName + ":")), std::string::npos);
    // Description content appears somewhere (may be wrapped)
    EXPECT_NE(s.find(std::string(10, 'D')), std::string::npos);

    // Non-empty path flushes.
    EXPECT_GE(buf.flushCount(), 1);
    // Should still end in a blank line.
    ASSERT_GE(s.size(), 2u);
    EXPECT_EQ(s.substr(s.size() - 2), std::string("\n\n"));
}

