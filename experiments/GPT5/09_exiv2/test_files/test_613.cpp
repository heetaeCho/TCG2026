// File: test_remoteio_size_613.cpp

#include <gtest/gtest.h>
#include <exiv2/basicio.hpp>

using namespace Exiv2;

/*
 * TEST_ID: 613
 * Focus: Observable behavior of RemoteIo::size()
 * Constraints:
 *  - Black-box testing only
 *  - No assumptions about internal storage
 *  - No inference of side effects
 */

class RemoteIoTest_613 : public ::testing::Test {
protected:
    RemoteIo io;
};

/*
 * Normal operation:
 * size() should be callable on a default-constructed object
 */
TEST_F(RemoteIoTest_613, SizeCallableOnDefaultConstruction_613) {
    EXPECT_NO_THROW({
        volatile size_t s = io.size();
        (void)s;
    });
}

/*
 * Boundary condition:
 * size() should be >= 0 (size_t contract)
 */
TEST_F(RemoteIoTest_613, SizeIsNonNegative_613) {
    size_t s = io.size();
    EXPECT_GE(s, static_cast<size_t>(0));
}

/*
 * Normal operation:
 * size() should be stable across repeated calls if no other operations occur
 */
TEST_F(RemoteIoTest_613, SizeIsStableAcrossMultipleCalls_613) {
    size_t first = io.size();
    size_t second = io.size();
    size_t third = io.size();

    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
}

/*
 * Boundary condition:
 * Calling size() before open() should be safe
 */
TEST_F(RemoteIoTest_613, SizeCallableBeforeOpen_613) {
    EXPECT_NO_THROW({
        size_t s = io.size();
        (void)s;
    });
}

/*
 * Exceptional / robustness case:
 * size() remains callable after open() and close(), regardless of return codes
 */
TEST_F(RemoteIoTest_613, SizeCallableAfterOpenAndClose_613) {
    io.open();
    EXPECT_NO_THROW({
        size_t s1 = io.size();
        (void)s1;
    });

    io.close();
    EXPECT_NO_THROW({
        size_t s2 = io.size();
        (void)s2;
    });
}

/*
 * External interaction safety:
 * populateFakeData() is a public method — size() must remain callable after it
 * (No assumption about whether size changes)
 */
TEST_F(RemoteIoTest_613, SizeCallableAfterPopulateFakeData_613) {
    io.populateFakeData();

    EXPECT_NO_THROW({
        size_t s = io.size();
        (void)s;
    });
}

/*
 * Boundary condition:
 * size() should not change merely by calling it
 */
TEST_F(RemoteIoTest_613, SizeDoesNotMutateState_613) {
    size_t before = io.size();
    io.size();
    io.size();
    size_t after = io.size();

    EXPECT_EQ(before, after);
}