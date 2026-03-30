// AnnotationAppearancePrivate_test_2771.cc
#include <gtest/gtest.h>

#include "poppler-annotation-private.h"

namespace Poppler {

class AnnotationAppearancePrivateTest_2771 : public ::testing::Test {};

TEST_F(AnnotationAppearancePrivateTest_2771, ConstructWithNullAnnotDoesNotThrow_2771)
{
    // Observable behavior: construction should be safe with a null pointer.
    EXPECT_NO_THROW({
        AnnotationAppearancePrivate priv(nullptr);
        (void)priv;
    });
}

TEST_F(AnnotationAppearancePrivateTest_2771, MultipleConstructionsWithNullAnnotAreSafe_2771)
{
    // Boundary-ish: repeated construction/destruction with nullptr should remain safe.
    EXPECT_NO_THROW({
        for (int i = 0; i < 1000; ++i) {
            AnnotationAppearancePrivate priv(nullptr);
            (void)priv;
        }
    });
}

TEST_F(AnnotationAppearancePrivateTest_2771, ConstructTemporaryWithNullAnnotIsSafe_2771)
{
    // Another boundary: temporary object lifetime.
    EXPECT_NO_THROW({
        (void)AnnotationAppearancePrivate(nullptr);
    });
}

} // namespace Poppler