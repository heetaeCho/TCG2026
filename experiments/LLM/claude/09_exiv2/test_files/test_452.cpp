#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

// Minimal stubs for Exiv2 types needed by the interface
namespace Exiv2 {

// Minimal i18n macro stub
#ifndef _
#define _(x) x
#endif

class ExifData {};

class Value {
public:
    virtual ~Value() = default;
    virtual std::string toString() const = 0;
    
    friend std::ostream& operator<<(std::ostream& os, const Value& v) {
        return os << v.toString();
    }
};

class StringValue : public Value {
public:
    explicit StringValue(const std::string& s) : str_(s) {}
    std::string toString() const override { return str_; }
private:
    std::string str_;
};

namespace Internal {

class Nikon1MakerNote {
public:
    std::ostream& print0x0007(std::ostream& os, const Value& value, const ExifData*) {
        std::string focus = value.toString();
        if (focus == "AF-C  ")
            return os << _("Continuous autofocus");
        if (focus == "AF-S  ")
            return os << _("Single autofocus");
        if (focus == "AF-A  ")
            return os << _("Automatic");
        return os << "(" << value << ")";
    }
};

} // namespace Internal
} // namespace Exiv2

// Test fixture
class Nikon1MakerNoteTest_452 : public ::testing::Test {
protected:
    Exiv2::Internal::Nikon1MakerNote maker_;
    std::ostringstream os_;
};

// Test: AF-C with trailing spaces returns "Continuous autofocus"
TEST_F(Nikon1MakerNoteTest_452, Print0x0007_AFC_ContinuousAutofocus_452) {
    Exiv2::StringValue val("AF-C  ");
    maker_.print0x0007(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "Continuous autofocus");
}

// Test: AF-S with trailing spaces returns "Single autofocus"
TEST_F(Nikon1MakerNoteTest_452, Print0x0007_AFS_SingleAutofocus_452) {
    Exiv2::StringValue val("AF-S  ");
    maker_.print0x0007(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "Single autofocus");
}

// Test: AF-A with trailing spaces returns "Automatic"
TEST_F(Nikon1MakerNoteTest_452, Print0x0007_AFA_Automatic_452) {
    Exiv2::StringValue val("AF-A  ");
    maker_.print0x0007(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "Automatic");
}

// Test: Unknown value returns fallback format "(value)"
TEST_F(Nikon1MakerNoteTest_452, Print0x0007_UnknownValue_FallbackFormat_452) {
    Exiv2::StringValue val("UNKNOWN");
    maker_.print0x0007(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "(UNKNOWN)");
}

// Test: Empty string returns fallback format "()"
TEST_F(Nikon1MakerNoteTest_452, Print0x0007_EmptyString_FallbackFormat_452) {
    Exiv2::StringValue val("");
    maker_.print0x0007(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "()");
}

// Boundary: AF-C without trailing spaces should not match and fall through
TEST_F(Nikon1MakerNoteTest_452, Print0x0007_AFC_NoTrailingSpaces_Fallback_452) {
    Exiv2::StringValue val("AF-C");
    maker_.print0x0007(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "(AF-C)");
}

// Boundary: AF-S without trailing spaces should not match and fall through
TEST_F(Nikon1MakerNoteTest_452, Print0x0007_AFS_NoTrailingSpaces_Fallback_452) {
    Exiv2::StringValue val("AF-S");
    maker_.print0x0007(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "(AF-S)");
}

// Boundary: AF-A without trailing spaces should not match and fall through
TEST_F(Nikon1MakerNoteTest_452, Print0x0007_AFA_NoTrailingSpaces_Fallback_452) {
    Exiv2::StringValue val("AF-A");
    maker_.print0x0007(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "(AF-A)");
}

// Boundary: AF-C with only one trailing space should not match
TEST_F(Nikon1MakerNoteTest_452, Print0x0007_AFC_OneTrailingSpace_Fallback_452) {
    Exiv2::StringValue val("AF-C ");
    maker_.print0x0007(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "(AF-C )");
}

// Test: Lowercase af-c should not match
TEST_F(Nikon1MakerNoteTest_452, Print0x0007_Lowercase_AFC_Fallback_452) {
    Exiv2::StringValue val("af-c  ");
    maker_.print0x0007(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "(af-c  )");
}

// Test: nullptr ExifData is acceptable (no crash)
TEST_F(Nikon1MakerNoteTest_452, Print0x0007_NullExifData_NoCrash_452) {
    Exiv2::StringValue val("AF-C  ");
    EXPECT_NO_THROW(maker_.print0x0007(os_, val, nullptr));
    EXPECT_EQ(os_.str(), "Continuous autofocus");
}

// Test: Return value is the same ostream reference
TEST_F(Nikon1MakerNoteTest_452, Print0x0007_ReturnsOstream_452) {
    Exiv2::StringValue val("AF-C  ");
    std::ostream& result = maker_.print0x0007(os_, val, nullptr);
    EXPECT_EQ(&result, &os_);
}

// Test: Random string with special characters
TEST_F(Nikon1MakerNoteTest_452, Print0x0007_SpecialChars_Fallback_452) {
    Exiv2::StringValue val("!@#$%");
    maker_.print0x0007(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "(!@#$%)");
}

// Test: AF-C with three trailing spaces should not match (expects exactly two)
TEST_F(Nikon1MakerNoteTest_452, Print0x0007_AFC_ThreeTrailingSpaces_Fallback_452) {
    Exiv2::StringValue val("AF-C   ");
    maker_.print0x0007(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "(AF-C   )");
}

// Test: Only spaces
TEST_F(Nikon1MakerNoteTest_452, Print0x0007_OnlySpaces_Fallback_452) {
    Exiv2::StringValue val("      ");
    maker_.print0x0007(os_, val, nullptr);
    EXPECT_EQ(os_.str(), "(      )");
}
