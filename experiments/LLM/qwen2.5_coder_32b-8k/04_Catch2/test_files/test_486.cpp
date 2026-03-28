#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_random_seed_generation.hpp"



namespace Catch {

    std::uint32_t generateRandomSeed(GenerateFrom from);

}



using namespace Catch;



TEST(generateRandomSeedTest_486, GenerateFromTime_ReturnsNonZeroValue_486) {

    EXPECT_NE(generateRandomSeed(GenerateFrom::Time), 0U);

}



TEST(generateRandomSeedTest_486, GenerateFromDefault_ReturnsNonZeroValue_486) {

    EXPECT_NE(generateRandomSeed(GenerateFrom::Default), 0U);

}



TEST(generateRandomSeedTest_486, GenerateFromRandomDevice_ReturnsNonZeroValue_486) {

    EXPECT_NE(generateRandomSeed(GenerateFrom::RandomDevice), 0U);

}



TEST(generateRandomSeedTest_486, InvalidGenerateFrom_ThrowsError_486) {

    EXPECT_THROW(generateRandomSeed(static_cast<GenerateFrom>(3)), std::logic_error);

}
