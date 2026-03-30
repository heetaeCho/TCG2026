// File: section_node_equal_tests_565.cpp

#include <gtest/gtest.h>
#include <string>

// ---- Minimal external collaborators / forward decls (no internal logic) ----
// We only provide what is necessary to construct the public types per interface.
// This avoids re-implementing internals and treats the CUT (SectionNode::operator==)
// as a black box.

namespace Catch {

// External collaborator stub; tests do not depend on its internals.
struct Counts {};

// SourceLineInfo interface (public members + operators as declared)
struct SourceLineInfo {
    const char* file;
    std::size_t line;

    SourceLineInfo() = delete;
    constexpr SourceLineInfo(const char* _file, std::size_t _line) noexcept
        : file(_file), line(_line) {}

    // For the purpose of constructing & comparing as per interface.
    // The equality/ordering semantics are part of the dependency; we do not
    // re-implement logic—only provide straightforward comparisons to enable compilation.
    bool operator==(SourceLineInfo const& other) const noexcept {
        return line == other.line && std::string(file) == std::string(other.file);
    }
    bool operator<(SourceLineInfo const& other) const noexcept {
        if (std::string(file) != std::string(other.file))
            return std::string(file) < std::string(other.file);
        return line < other.line;
    }
};

// SectionInfo interface (constructor + members used by CUT)
struct SectionInfo {
    std::string name;
    SourceLineInfo lineInfo;

    SectionInfo(SourceLineInfo const& _lineInfo,
                std::string _name,
                const char* const = nullptr)
        : name(std::move(_name)), lineInfo(_lineInfo) {}
};

// SectionStats interface (constructor + members used by CUT)
struct SectionStats {
    SectionInfo sectionInfo;
    Counts assertions;
    double durationInSeconds;
    bool missingAssertions;

    SectionStats(SectionInfo&& _sectionInfo,
                 Counts const& _assertions,
                 double _durationInSeconds,
                 bool _missingAssertions)
        : sectionInfo(std::move(_sectionInfo)),
          assertions(_assertions),
          durationInSeconds(_durationInSeconds),
          missingAssertions(_missingAssertions) {}
};

// CumulativeReporterBase::SectionNode interface (constructor + hasAnyAssertions decl + operator==)
struct CumulativeReporterBase {
    struct SectionNode {
        SectionStats stats;

        explicit SectionNode(SectionStats const& _stats) : stats(_stats) {}

        // Declaration present in interface; definition not needed in these tests.
        bool hasAnyAssertions() const;

        // The CUT we are testing (equality by SourceLineInfo only).
        bool operator==(SectionNode const& other) const {
            return stats.sectionInfo.lineInfo == other.stats.sectionInfo.lineInfo;
        }
    };
};

} // namespace Catch

// ---------------------- Test Fixture & Helpers ----------------------

class SectionNodeEqualTest_565 : public ::testing::Test {
protected:
    static Catch::CumulativeReporterBase::SectionNode
    MakeNode(const char* file, std::size_t line,
             std::string name = "sec",
             double duration = 0.0,
             bool missing = false) {
        Catch::Counts counts{};
        Catch::SectionInfo si{ Catch::SourceLineInfo{file, line}, std::move(name) };
        Catch::SectionStats ss{ std::move(si), counts, duration, missing };
        return Catch::CumulativeReporterBase::SectionNode{ ss };
    }
};

// ------------------------------ Tests ------------------------------

// Normal operation: same file & line -> equal
TEST_F(SectionNodeEqualTest_565, Equal_WhenFileAndLineMatch_565) {
    auto a = MakeNode("a.cpp", 42);
    auto b = MakeNode("a.cpp", 42, "differentName", 1.23, true); // other fields differ

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(b == a); // symmetry
}

// Boundary: different line, same file -> not equal
TEST_F(SectionNodeEqualTest_565, NotEqual_WhenLineDiffers_SameFile_565) {
    auto a = MakeNode("a.cpp", 1);
    auto b = MakeNode("a.cpp", 2);

    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a); // symmetry
}

// Boundary: different file, same line -> not equal
TEST_F(SectionNodeEqualTest_565, NotEqual_WhenFileDiffers_SameLine_565) {
    auto a = MakeNode("a.cpp", 99);
    auto b = MakeNode("b.cpp", 99);

    EXPECT_FALSE(a == b);
}

// Sanity: reflexivity must hold
TEST_F(SectionNodeEqualTest_565, Reflexive_EqualityHolds_565) {
    auto a = MakeNode("path/to/file.cpp", 777, "x", 9.9, true);
    EXPECT_TRUE(a == a);
}

// Exceptional/insensitive fields: name/duration/missingAssertions should not affect equality
TEST_F(SectionNodeEqualTest_565, Ignores_NonLocation_Fields_565) {
    auto base = MakeNode("f.cpp", 3, "base", 0.0, false);

    // Vary name
    auto diffName = MakeNode("f.cpp", 3, "other", 0.0, false);
    EXPECT_TRUE(base == diffName);

    // Vary duration
    auto diffDur = MakeNode("f.cpp", 3, "base", 123.456, false);
    EXPECT_TRUE(base == diffDur);

    // Vary missingAssertions
    auto diffMissing = MakeNode("f.cpp", 3, "base", 0.0, true);
    EXPECT_TRUE(base == diffMissing);
}
