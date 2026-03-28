#include <gtest/gtest.h>

#include <array>

#include "PentaxLensDatabase.h" // Assuming this header contains the necessary functions and definitions



// Test if the database correctly identifies known lenses

TEST(PentaxLensDatabaseTest, KnownLenses) {

    std::array<std::pair<int, std::string>, 5> testLenses = {{

        {70, "smc PENTAX-FA* 28-70mm F2.8 AL"},

        {1543, "smc PENTAX-FA 28-70mm F4AL"},

        {2069, "Sigma 17-50mm F2.8 EX DC OS HSM"},

        {5377, "01 Standard Prime 8.5mm F1.9"},

        {5635, "03 Fish-eye 3.2mm F5.6"}

    }};



    for (const auto& [id, name] : testLenses) {

        EXPECT_EQ(getLensNameById(id), name);

    }

}



// Test if the database returns an empty string or a placeholder for unknown lens IDs

TEST(PentaxLensDatabaseTest, UnknownLenses) {

    std::array<int, 3> invalidIds = {9999, 0, 65536};



    for (const auto& id : invalidIds) {

        EXPECT_TRUE(getLensNameById(id).empty() || getLensNameById(id) == "Unknown Lens");

    }

}



// Test boundary values

TEST(PentaxLensDatabaseTest, BoundaryValues) {

    EXPECT_EQ(getLensNameById(0), ""); // Assuming 0 is not a valid ID and should return empty string

    EXPECT_EQ(getLensNameById(2560), "645 A Series Lens");

    EXPECT_EQ(getLensNameById(3348), "HD PENTAX-D FA 645 90mm F2.8 ED AW SR");

    EXPECT_EQ(getLensNameById(65535), ""); // Assuming 65535 is not a valid ID and should return empty string

}



// Test performance with a large number of requests (optional, for stress testing)

TEST(PentaxLensDatabaseTest, PerformanceStress) {

    const int numTests = 1000;

    for (int i = 0; i < numTests; ++i) {

        int randomId = rand() % 65536; // Random ID between 0 and 65535

        std::string name = getLensNameById(randomId);

        EXPECT_TRUE(!name.empty() || name == "Unknown Lens");

    }

}
