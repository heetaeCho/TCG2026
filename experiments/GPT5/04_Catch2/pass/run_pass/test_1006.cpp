// File: tests/FilterSerializeTo_1006.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

// If you include real Catch2 headers in your environment, prefer those.
// The tests below rely only on the observable contract from the prompt:
//  - Filter holds vectors of unique_ptr<Pattern>
//  - serializeTo(std::ostream&) prints each required, then forbidden, space-separated
//
// Minimal shims for the collaborator (Pattern) and the unique_ptr type are
// avoided here; we define only what is necessary to exercise the public behavior
// without re-implementing any internal logic of Filter.

// ---- Begin: Minimal, test-only collaborator for Pattern printing ----
namespace Catch {
    // Test-only minimal Pattern interface that supports streaming.
    struct Pattern {
        virtual ~Pattern() = default;
        virtual void write(std::ostream& os) const = 0;
    };

    inline std::ostream& operator<<(std::ostream& os, Pattern const& p) {
        p.write(os);
        return os;
    }
}
// ---- End: Minimal, test-only collaborator for Pattern printing ----

// ---- Begin: Use the interface layout from the prompt ----
namespace Catch {
    namespace Detail {
        // Minimal test-usable unique_ptr with just what we need for construction/move.
        template <typename T>
        class unique_ptr {
        public:
            constexpr unique_ptr(std::nullptr_t = nullptr) noexcept : m_ptr(nullptr) {}
            explicit constexpr unique_ptr(T* ptr) noexcept : m_ptr(ptr) {}
            unique_ptr(unique_ptr const&) = delete;
            unique_ptr(unique_ptr&& rhs) noexcept : m_ptr(rhs.m_ptr) { rhs.m_ptr = nullptr; }
            unique_ptr& operator=(unique_ptr const&) = delete;
            unique_ptr& operator=(unique_ptr&& rhs) noexcept {
                if (this != &rhs) { reset(rhs.m_ptr); rhs.m_ptr = nullptr; }
                return *this;
            }
            ~unique_ptr() { reset(nullptr); }

            T* get() const noexcept { return m_ptr; }
            T* release() noexcept { T* p = m_ptr; m_ptr = nullptr; return p; }
            void reset(T* p) noexcept { if (m_ptr) delete m_ptr; m_ptr = p; }
            T& operator*() const noexcept { return *m_ptr; }
            T* operator->() const noexcept { return m_ptr; }
            explicit operator bool() const noexcept { return m_ptr != nullptr; }

        private:
            T* m_ptr;
        };
    } // namespace Detail

    class TestSpec {
    public:
        struct Filter {
            // Public members per prompt
            std::vector<Detail::unique_ptr<Pattern>> m_required;
            std::vector<Detail::unique_ptr<Pattern>> m_forbidden;

            // The function under test
            void serializeTo(std::ostream& out) const {
                bool first = true;
                for (auto const& pattern : m_required) {
                    if (!first) { out << ' '; }
                    out << *pattern;
                    first = false;
                }
                for (auto const& pattern : m_forbidden) {
                    if (!first) { out << ' '; }
                    out << *pattern;
                    first = false;
                }
            }
        };
    };
} // namespace Catch
// ---- End: Interface layout from the prompt ----

// ---- Test helper pattern that prints a fixed token ----
namespace {
    struct TokenPattern final : Catch::Pattern {
        explicit TokenPattern(std::string token) : token_(std::move(token)) {}
        void write(std::ostream& os) const override { os << token_; }
    private:
        std::string token_;
    };

    inline Catch::Detail::unique_ptr<Catch::Pattern> MakeToken(const std::string& s) {
        return Catch::Detail::unique_ptr<Catch::Pattern>(new TokenPattern(s));
    }
}

// ---- Test fixture ----
class FilterSerializeToTest_1006 : public ::testing::Test {
protected:
    Catch::TestSpec::Filter filter_;
    std::ostringstream out_;
};

// --- Tests ---

TEST_F(FilterSerializeToTest_1006, EmptyProducesEmptyString_1006) {
    // No required/forbidden patterns -> no output
    filter_.serializeTo(out_);
    EXPECT_EQ(out_.str(), "");
}

TEST_F(FilterSerializeToTest_1006, SingleRequired_NoExtraSpaces_1006) {
    filter_.m_required.push_back(MakeToken("A"));
    filter_.serializeTo(out_);
    EXPECT_EQ(out_.str(), "A");
    EXPECT_FALSE(out_.str().empty());
    // Assert no leading/trailing space
    EXPECT_NE(out_.str().front(), ' ');
    EXPECT_NE(out_.str().back(),  ' ');
}

TEST_F(FilterSerializeToTest_1006, MultipleRequired_SpaceSeparated_1006) {
    filter_.m_required.push_back(MakeToken("A"));
    filter_.m_required.push_back(MakeToken("B"));
    filter_.m_required.push_back(MakeToken("C"));

    filter_.serializeTo(out_);
    EXPECT_EQ(out_.str(), "A B C");
}

TEST_F(FilterSerializeToTest_1006, SingleForbidden_NoExtraSpaces_1006) {
    filter_.m_forbidden.push_back(MakeToken("X"));
    filter_.serializeTo(out_);
    EXPECT_EQ(out_.str(), "X");
    EXPECT_NE(out_.str().front(), ' ');
    EXPECT_NE(out_.str().back(),  ' ');
}

TEST_F(FilterSerializeToTest_1006, MultipleForbidden_SpaceSeparated_1006) {
    filter_.m_forbidden.push_back(MakeToken("X"));
    filter_.m_forbidden.push_back(MakeToken("Y"));
    filter_.m_forbidden.push_back(MakeToken("Z"));

    filter_.serializeTo(out_);
    EXPECT_EQ(out_.str(), "X Y Z");
}

TEST_F(FilterSerializeToTest_1006, RequiredThenForbidden_OrderAndSpaces_1006) {
    // Verify required come first, then forbidden, all single-space separated
    filter_.m_required.push_back(MakeToken("A"));
    filter_.m_required.push_back(MakeToken("B"));
    filter_.m_forbidden.push_back(MakeToken("X"));
    filter_.m_forbidden.push_back(MakeToken("Y"));

    filter_.serializeTo(out_);
    EXPECT_EQ(out_.str(), "A B X Y");
}

TEST_F(FilterSerializeToTest_1006, Boundary_InterleavedSizes_NoLeadingOrTrailingSpace_1006) {
    // Mixed sizes to ensure spacing logic handles transitions correctly
    filter_.m_required.push_back(MakeToken("R1"));
    filter_.m_forbidden.push_back(MakeToken("F1"));
    filter_.m_forbidden.push_back(MakeToken("F2"));

    filter_.serializeTo(out_);
    const auto s = out_.str();
    EXPECT_EQ(s, "R1 F1 F2");
    ASSERT_FALSE(s.empty());
    EXPECT_NE(s.front(), ' ');
    EXPECT_NE(s.back(),  ' ');
    // Ensure exactly two spaces present
    EXPECT_EQ(std::count(s.begin(), s.end(), ' '), 2);
}
