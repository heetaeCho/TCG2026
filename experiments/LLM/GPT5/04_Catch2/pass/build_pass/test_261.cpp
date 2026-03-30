// File: stringmaker_string_view_convert_tests_261.cpp

#include <gtest/gtest.h>
#include <string>
#include <string_view>

//
// ===== Test-time shims for external dependencies =====
// We only define what is necessary to compile and to observe interactions.
//
namespace Catch {
namespace Detail {

// Minimal StringRef with the exact ctor used by the implementation
struct StringRef {
    const char* ptr;
    size_t len;
    StringRef(const char* p, size_t l) : ptr(p), len(l) {}
};

// Captured call info for verification in tests
static const char* g_last_ptr = nullptr;
static size_t g_last_len = 0;
static std::string g_next_return;

// Mocked collaborator function (observable side effect + controllable return)
inline std::string convertIntoString(const StringRef& ref) {
    g_last_ptr = ref.ptr;
    g_last_len = ref.len;
    return g_next_return;
}

} // namespace Detail
} // namespace Catch

//
// ===== Minimal declaration of the interface under test =====
// We only declare the specialization we are testing.
//
namespace Catch {

template <typename T> struct StringMaker; // primary

template <>
struct StringMaker<std::string_view> {
    static std::string convert(std::string_view str);
};

} // namespace Catch

//
// ===== Include the partial implementation under test =====
//
// The provided snippet defines
//   std::string StringMaker<std::string_view>::convert(std::string_view)
// that forwards to Detail::convertIntoString(StringRef(...)).
//
/*
File name : Catch2/src/catch2/catch_tostring.cpp

namespace Catch {
    std::string StringMaker<std::string_view>::convert(std::string_view str) {
        return Detail::convertIntoString( StringRef( str.data(), str.size() ) );
    }
}
*/
namespace Catch {
std::string StringMaker<std::string_view>::convert(std::string_view str) {
    return Detail::convertIntoString( Detail::StringRef( str.data(), str.size() ) );
}
} // namespace Catch

//
// ===== Test fixture =====
//
class StringMakerStringViewTest_261 : public ::testing::Test {
protected:
    void SetUp() override {
        // Clear captured info before each test
        Catch::Detail::g_last_ptr = nullptr;
        Catch::Detail::g_last_len = 0;
        Catch::Detail::g_next_return.clear();
    }
};

//
// ===== Tests =====
//

TEST_F(StringMakerStringViewTest_261, ForwardsNonEmptyViewPointerAndSize_261) {
    // Arrange
    std::string backing = "hello world";
    std::string_view sv(backing); // non-empty
    Catch::Detail::g_next_return = "SENTINEL";

    // Act
    std::string out = Catch::StringMaker<std::string_view>::convert(sv);

    // Assert: return value is whatever collaborator returned (black-box)
    EXPECT_EQ(out, "SENTINEL");

    // Assert: collaborator saw the correct pointer and size
    ASSERT_NE(Catch::Detail::g_last_ptr, nullptr);
    EXPECT_EQ(Catch::Detail::g_last_ptr, sv.data());
    EXPECT_EQ(Catch::Detail::g_last_len, sv.size());
}

TEST_F(StringMakerStringViewTest_261, ForwardsEmptyViewSizeZero_261) {
    // Arrange
    std::string_view sv; // empty
    Catch::Detail::g_next_return = "EMPTY-OK";

    // Act
    std::string out = Catch::StringMaker<std::string_view>::convert(sv);

    // Assert: returns collaborator's result
    EXPECT_EQ(out, "EMPTY-OK");

    // Assert: length forwarded is zero
    EXPECT_EQ(Catch::Detail::g_last_len, 0u);

    // Note: C++ standard permits data() to be non-null for empty views, so we do
    // not assert pointer equality/null-ness here — only that size is 0.
}

TEST_F(StringMakerStringViewTest_261, ForwardsSubrangeViewNotNullTerminated_261) {
    // Arrange: create a view into the middle (not null-terminated)
    std::string backing = "abcdef";
    const char* expected_ptr = backing.data() + 1; // points to 'b'
    std::string_view sv(expected_ptr, 3);          // "bcd"
    Catch::Detail::g_next_return = "SUBRANGE";

    // Act
    std::string out = Catch::StringMaker<std::string_view>::convert(sv);

    // Assert: returns collaborator's result
    EXPECT_EQ(out, "SUBRANGE");

    // Assert: collaborator saw the exact pointer and length of the view
    EXPECT_EQ(Catch::Detail::g_last_ptr, expected_ptr);
    EXPECT_EQ(Catch::Detail::g_last_len, 3u);
}

TEST_F(StringMakerStringViewTest_261, WorksWithStringLiteralView_261) {
    // Arrange: literal -> string_view
    const char* lit = "xyz";
    std::string_view sv(lit); // size 3
    Catch::Detail::g_next_return = "LITERAL";

    // Act
    std::string out = Catch::StringMaker<std::string_view>::convert(sv);

    // Assert
    EXPECT_EQ(out, "LITERAL");
    EXPECT_EQ(Catch::Detail::g_last_ptr, sv.data());
    EXPECT_EQ(Catch::Detail::g_last_len, 3u);
}
