// File: linkdestinationprivate_test_2764.cc

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// NOTE:
// LinkDestinationPrivate is a private/internal type in Poppler Qt5 code.
// In the real codebase, it should be available via an internal header.
// If your tree uses a different internal header name/path, adjust this include.
#include "poppler-link-private.h"

namespace {

class LinkDestinationPrivateTest_2764 : public ::testing::Test {};

TEST_F(LinkDestinationPrivateTest_2764, DefaultConstructibleTrait_2764)
{
    EXPECT_TRUE((std::is_default_constructible<Poppler::LinkDestinationPrivate>::value));
}

TEST_F(LinkDestinationPrivateTest_2764, DefaultConstructionDoesNotThrow_2764)
{
    EXPECT_NO_THROW({
        Poppler::LinkDestinationPrivate obj;
        (void)obj;
    });
}

TEST_F(LinkDestinationPrivateTest_2764, HeapConstructionAndDeletionDoesNotThrow_2764)
{
    Poppler::LinkDestinationPrivate *p = nullptr;
    EXPECT_NO_THROW({
        p = new Poppler::LinkDestinationPrivate();
    });
    ASSERT_NE(p, nullptr);

    EXPECT_NO_THROW({
        delete p;
    });
}

TEST_F(LinkDestinationPrivateTest_2764, CopyAndMoveAreWellFormed_2764)
{
    // These are purely interface-level checks: if the type supports these operations,
    // the expressions compile and can be exercised without observing private state.
    EXPECT_TRUE((std::is_copy_constructible<Poppler::LinkDestinationPrivate>::value));
    EXPECT_TRUE((std::is_move_constructible<Poppler::LinkDestinationPrivate>::value));

    Poppler::LinkDestinationPrivate a;
    EXPECT_NO_THROW({
        Poppler::LinkDestinationPrivate b(a);
        (void)b;
    });

    EXPECT_NO_THROW({
        Poppler::LinkDestinationPrivate c(std::move(a));
        (void)c;
    });
}

} // namespace