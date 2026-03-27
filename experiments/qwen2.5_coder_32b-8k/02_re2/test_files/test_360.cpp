#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "regexp.h"



using namespace re2;



namespace {



class NamedCapturesWalkerTest : public ::testing::Test {

protected:

    NamedCapturesWalker walker;

};



TEST_F(NamedCapturesWalkerTest, TakeMap_ReturnsNullInitially_360) {

    EXPECT_EQ(walker.TakeMap(), nullptr);

}



TEST_F(NamedCapturesWalkerTest, PreVisit_DefaultImplementation_DoesNotStopTraversal_360) {

    bool stop = false;

    Regexp* dummy_regexp = nullptr; // Assuming a null pointer can be used as a dummy for this test

    walker.PreVisit(dummy_regexp, 0, &stop);

    EXPECT_FALSE(stop);

}



TEST_F(NamedCapturesWalkerTest, ShortVisit_DefaultImplementation_LogsErrorInDebugMode_360) {

#ifndef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION

    Regexp* dummy_regexp = nullptr; // Assuming a null pointer can be used as a dummy for this test

    EXPECT_DEATH(walker.ShortVisit(dummy_regexp, 0), "ShortVisit called");

#endif

}



} // namespace
