#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Forward declarations to match the expected types
class Annot {};
class Page {};

namespace Poppler {

class DocumentData {};

class FileAttachmentAnnotationPrivate {
public:
    std::shared_ptr<Annot> createNativeAnnot(::Page * /*destPage*/, DocumentData * /*doc*/)
    {
        return nullptr; // Not implemented
    }
};

} // namespace Poppler

// Test fixture
class FileAttachmentAnnotationPrivateTest_1414 : public ::testing::Test {
protected:
    Poppler::FileAttachmentAnnotationPrivate annotPrivate;
};

// Test that createNativeAnnot returns nullptr when both arguments are nullptr
TEST_F(FileAttachmentAnnotationPrivateTest_1414, CreateNativeAnnotReturnsNullptrWithNullArgs_1414)
{
    auto result = annotPrivate.createNativeAnnot(nullptr, nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that createNativeAnnot returns nullptr when destPage is valid but doc is nullptr
TEST_F(FileAttachmentAnnotationPrivateTest_1414, CreateNativeAnnotReturnsNullptrWithValidPageNullDoc_1414)
{
    Page page;
    auto result = annotPrivate.createNativeAnnot(&page, nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that createNativeAnnot returns nullptr when destPage is nullptr but doc is valid
TEST_F(FileAttachmentAnnotationPrivateTest_1414, CreateNativeAnnotReturnsNullptrWithNullPageValidDoc_1414)
{
    Poppler::DocumentData doc;
    auto result = annotPrivate.createNativeAnnot(nullptr, &doc);
    EXPECT_EQ(result, nullptr);
}

// Test that createNativeAnnot returns nullptr when both arguments are valid pointers
TEST_F(FileAttachmentAnnotationPrivateTest_1414, CreateNativeAnnotReturnsNullptrWithValidArgs_1414)
{
    Page page;
    Poppler::DocumentData doc;
    auto result = annotPrivate.createNativeAnnot(&page, &doc);
    EXPECT_EQ(result, nullptr);
}

// Test that the returned shared_ptr has use_count of 0 (since it's null)
TEST_F(FileAttachmentAnnotationPrivateTest_1414, CreateNativeAnnotReturnedSharedPtrHasZeroUseCount_1414)
{
    auto result = annotPrivate.createNativeAnnot(nullptr, nullptr);
    EXPECT_EQ(result.use_count(), 0);
}

// Test that createNativeAnnot can be called multiple times and consistently returns nullptr
TEST_F(FileAttachmentAnnotationPrivateTest_1414, CreateNativeAnnotConsistentlyReturnsNullptr_1414)
{
    for (int i = 0; i < 10; ++i) {
        auto result = annotPrivate.createNativeAnnot(nullptr, nullptr);
        EXPECT_EQ(result, nullptr);
    }
}

// Test that the returned shared_ptr evaluates to false in boolean context
TEST_F(FileAttachmentAnnotationPrivateTest_1414, CreateNativeAnnotReturnedPtrIsFalsy_1414)
{
    auto result = annotPrivate.createNativeAnnot(nullptr, nullptr);
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test that default construction of FileAttachmentAnnotationPrivate works
TEST_F(FileAttachmentAnnotationPrivateTest_1414, DefaultConstruction_1414)
{
    Poppler::FileAttachmentAnnotationPrivate obj;
    // Object should be constructible without issues
    auto result = obj.createNativeAnnot(nullptr, nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that the returned shared_ptr's get() returns nullptr
TEST_F(FileAttachmentAnnotationPrivateTest_1414, CreateNativeAnnotGetReturnsNullptr_1414)
{
    auto result = annotPrivate.createNativeAnnot(nullptr, nullptr);
    EXPECT_EQ(result.get(), nullptr);
}
