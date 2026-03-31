#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h"
#include "Object.h"

// Since GfxFont's constructor is protected, we need a derived class for testing
// However, GfxFont is abstract (has pure virtual methods), so we need to implement them
class TestableGfxFont : public GfxFont {
public:
    TestableGfxFont(const char *tagA, Ref idA, std::optional<std::string> &&nameA,
                    GfxFontType typeA, Ref embFontIDA)
        : GfxFont(tagA, idA, std::move(nameA), typeA, embFontIDA) {}

    // Implement pure virtual methods
    const CharCodeToUnicode *getToUnicode() const override { return nullptr; }
    int getNextChar(const char *s, int len, CharCode *code,
                    const Unicode **u, int *uLen,
                    double *dx, double *dy, double *ox, double *oy) const override {
        return 0;
    }
    bool isCIDFont() const override { return false; }
    WritingMode getWMode() const override { return WritingMode::horizWritingMode; }
};

class GfxFontTest_1147 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that getEmbeddedFontID returns true and sets embID when embFontID is valid
TEST_F(GfxFontTest_1147, GetEmbeddedFontID_ValidRef_ReturnsTrue_1147) {
    Ref validRef = {42, 0};
    auto font = std::make_unique<TestableGfxFont>(
        "TestTag", Ref{1, 0}, std::optional<std::string>("TestFont"),
        fontType1, validRef);

    Ref resultRef;
    bool result = font->getEmbeddedFontID(&resultRef);

    EXPECT_TRUE(result);
    EXPECT_EQ(resultRef.num, 42);
    EXPECT_EQ(resultRef.gen, 0);
}

// Test that getEmbeddedFontID returns false when embFontID is INVALID
TEST_F(GfxFontTest_1147, GetEmbeddedFontID_InvalidRef_ReturnsFalse_1147) {
    Ref invalidRef = Ref::INVALID();
    auto font = std::make_unique<TestableGfxFont>(
        "TestTag", Ref{1, 0}, std::optional<std::string>("TestFont"),
        fontType1, invalidRef);

    Ref resultRef;
    bool result = font->getEmbeddedFontID(&resultRef);

    EXPECT_FALSE(result);
}

// Test that getEmbeddedFontID writes the INVALID ref to the output param even when returning false
TEST_F(GfxFontTest_1147, GetEmbeddedFontID_InvalidRef_SetsOutputToInvalid_1147) {
    Ref invalidRef = Ref::INVALID();
    auto font = std::make_unique<TestableGfxFont>(
        "TestTag", Ref{1, 0}, std::optional<std::string>("TestFont"),
        fontType1, invalidRef);

    Ref resultRef = {999, 999}; // Initialize with known values
    font->getEmbeddedFontID(&resultRef);

    EXPECT_EQ(resultRef.num, Ref::INVALID().num);
    EXPECT_EQ(resultRef.gen, Ref::INVALID().gen);
}

// Test with a valid Ref having non-zero generation number
TEST_F(GfxFontTest_1147, GetEmbeddedFontID_ValidRefWithGen_ReturnsTrue_1147) {
    Ref validRef = {10, 5};
    auto font = std::make_unique<TestableGfxFont>(
        "TestTag", Ref{1, 0}, std::optional<std::string>("TestFont"),
        fontType1, validRef);

    Ref resultRef;
    bool result = font->getEmbeddedFontID(&resultRef);

    EXPECT_TRUE(result);
    EXPECT_EQ(resultRef.num, 10);
    EXPECT_EQ(resultRef.gen, 5);
}

// Test invalidateEmbeddedFont makes getEmbeddedFontID return false
TEST_F(GfxFontTest_1147, InvalidateEmbeddedFont_MakesGetEmbeddedFontIDReturnFalse_1147) {
    Ref validRef = {42, 0};
    auto font = std::make_unique<TestableGfxFont>(
        "TestTag", Ref{1, 0}, std::optional<std::string>("TestFont"),
        fontType1, validRef);

    // First verify it's valid
    Ref resultRef;
    EXPECT_TRUE(font->getEmbeddedFontID(&resultRef));

    // Invalidate
    font->invalidateEmbeddedFont();

    // Now should return false
    EXPECT_FALSE(font->getEmbeddedFontID(&resultRef));
}

// Test getTag returns the tag passed in constructor
TEST_F(GfxFontTest_1147, GetTag_ReturnsConstructorTag_1147) {
    auto font = std::make_unique<TestableGfxFont>(
        "MyTag", Ref{1, 0}, std::optional<std::string>("TestFont"),
        fontType1, Ref::INVALID());

    EXPECT_EQ(font->getTag(), "MyTag");
}

// Test getID returns the id passed in constructor
TEST_F(GfxFontTest_1147, GetID_ReturnsConstructorID_1147) {
    Ref id = {7, 3};
    auto font = std::make_unique<TestableGfxFont>(
        "TestTag", id, std::optional<std::string>("TestFont"),
        fontType1, Ref::INVALID());

    const Ref *resultID = font->getID();
    EXPECT_EQ(resultID->num, 7);
    EXPECT_EQ(resultID->gen, 3);
}

// Test getName returns the name passed in constructor
TEST_F(GfxFontTest_1147, GetName_ReturnsConstructorName_1147) {
    auto font = std::make_unique<TestableGfxFont>(
        "TestTag", Ref{1, 0}, std::optional<std::string>("MyFontName"),
        fontType1, Ref::INVALID());

    const auto &name = font->getName();
    ASSERT_TRUE(name.has_value());
    EXPECT_EQ(name.value(), "MyFontName");
}

// Test getName with no name (nullopt)
TEST_F(GfxFontTest_1147, GetName_NoName_ReturnsNullopt_1147) {
    auto font = std::make_unique<TestableGfxFont>(
        "TestTag", Ref{1, 0}, std::nullopt,
        fontType1, Ref::INVALID());

    const auto &name = font->getName();
    EXPECT_FALSE(name.has_value());
}

// Test getType returns the type passed in constructor
TEST_F(GfxFontTest_1147, GetType_ReturnsConstructorType_1147) {
    auto font = std::make_unique<TestableGfxFont>(
        "TestTag", Ref{1, 0}, std::optional<std::string>("TestFont"),
        fontType1, Ref::INVALID());

    EXPECT_EQ(font->getType(), fontType1);
}

// Test matches with matching tag
TEST_F(GfxFontTest_1147, Matches_SameTag_ReturnsTrue_1147) {
    auto font = std::make_unique<TestableGfxFont>(
        "TestTag", Ref{1, 0}, std::optional<std::string>("TestFont"),
        fontType1, Ref::INVALID());

    EXPECT_TRUE(font->matches("TestTag"));
}

// Test matches with different tag
TEST_F(GfxFontTest_1147, Matches_DifferentTag_ReturnsFalse_1147) {
    auto font = std::make_unique<TestableGfxFont>(
        "TestTag", Ref{1, 0}, std::optional<std::string>("TestFont"),
        fontType1, Ref::INVALID());

    EXPECT_FALSE(font->matches("OtherTag"));
}

// Test isCIDFont returns false for non-CID font
TEST_F(GfxFontTest_1147, IsCIDFont_NonCID_ReturnsFalse_1147) {
    auto font = std::make_unique<TestableGfxFont>(
        "TestTag", Ref{1, 0}, std::optional<std::string>("TestFont"),
        fontType1, Ref::INVALID());

    EXPECT_FALSE(font->isCIDFont());
}

// Test getEmbeddedFontID with zero ref (which should be valid, not INVALID)
TEST_F(GfxFontTest_1147, GetEmbeddedFontID_ZeroRef_ReturnsTrue_1147) {
    Ref zeroRef = {0, 0};
    // Only if {0,0} != INVALID(), this should return true
    if (!(zeroRef == Ref::INVALID())) {
        auto font = std::make_unique<TestableGfxFont>(
            "TestTag", Ref{1, 0}, std::optional<std::string>("TestFont"),
            fontType1, zeroRef);

        Ref resultRef;
        bool result = font->getEmbeddedFontID(&resultRef);
        EXPECT_TRUE(result);
        EXPECT_EQ(resultRef.num, 0);
        EXPECT_EQ(resultRef.gen, 0);
    }
}
