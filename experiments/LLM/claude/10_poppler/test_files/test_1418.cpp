#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Forward declarations to match the partial code's dependencies
class Annot {};
class Page {};

namespace Poppler {
class DocumentData {};
}

// Include or redefine the class under test based on the provided interface
namespace Poppler {

class MovieAnnotationPrivate {
public:
    std::shared_ptr<Annot> createNativeAnnot(::Page * /*destPage*/, DocumentData * /*doc*/)
    {
        return nullptr; // Not implemented
    }
};

} // namespace Poppler

// Test fixture
class MovieAnnotationPrivateTest_1418 : public ::testing::Test {
protected:
    Poppler::MovieAnnotationPrivate movieAnnotPrivate;
};

// Test that createNativeAnnot returns nullptr when both arguments are nullptr
TEST_F(MovieAnnotationPrivateTest_1418, CreateNativeAnnotReturnsNullWithNullArgs_1418)
{
    auto result = movieAnnotPrivate.createNativeAnnot(nullptr, nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that createNativeAnnot returns nullptr when destPage is non-null but doc is null
TEST_F(MovieAnnotationPrivateTest_1418, CreateNativeAnnotReturnsNullWithNonNullPage_1418)
{
    ::Page page;
    auto result = movieAnnotPrivate.createNativeAnnot(&page, nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that createNativeAnnot returns nullptr when destPage is null but doc is non-null
TEST_F(MovieAnnotationPrivateTest_1418, CreateNativeAnnotReturnsNullWithNonNullDoc_1418)
{
    Poppler::DocumentData doc;
    auto result = movieAnnotPrivate.createNativeAnnot(nullptr, &doc);
    EXPECT_EQ(result, nullptr);
}

// Test that createNativeAnnot returns nullptr when both arguments are valid non-null pointers
TEST_F(MovieAnnotationPrivateTest_1418, CreateNativeAnnotReturnsNullWithBothValidArgs_1418)
{
    ::Page page;
    Poppler::DocumentData doc;
    auto result = movieAnnotPrivate.createNativeAnnot(&page, &doc);
    EXPECT_EQ(result, nullptr);
}

// Test that the returned shared_ptr has use_count of 0 (null shared_ptr)
TEST_F(MovieAnnotationPrivateTest_1418, CreateNativeAnnotReturnedPtrUseCountIsZero_1418)
{
    auto result = movieAnnotPrivate.createNativeAnnot(nullptr, nullptr);
    EXPECT_EQ(result.use_count(), 0);
}

// Test that createNativeAnnot can be called multiple times consistently
TEST_F(MovieAnnotationPrivateTest_1418, CreateNativeAnnotConsistentlyReturnsNull_1418)
{
    for (int i = 0; i < 10; ++i) {
        auto result = movieAnnotPrivate.createNativeAnnot(nullptr, nullptr);
        EXPECT_EQ(result, nullptr);
    }
}

// Test that the returned shared_ptr evaluates to false in boolean context
TEST_F(MovieAnnotationPrivateTest_1418, CreateNativeAnnotReturnedPtrIsFalsy_1418)
{
    auto result = movieAnnotPrivate.createNativeAnnot(nullptr, nullptr);
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test that MovieAnnotationPrivate can be default constructed
TEST_F(MovieAnnotationPrivateTest_1418, DefaultConstructible_1418)
{
    Poppler::MovieAnnotationPrivate instance;
    // If we get here, default construction succeeded
    auto result = instance.createNativeAnnot(nullptr, nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that the returned shared_ptr's get() returns nullptr
TEST_F(MovieAnnotationPrivateTest_1418, CreateNativeAnnotGetReturnsNullptr_1418)
{
    auto result = movieAnnotPrivate.createNativeAnnot(nullptr, nullptr);
    EXPECT_EQ(result.get(), nullptr);
}
