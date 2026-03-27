#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <string>

#include "./TestProjects/exiv2/src/minoltamn_int.cpp"



namespace Exiv2 { namespace {



using ::testing::Eq;



TEST(ResolvedLensName, ValidLensWithSingleEntry) {

    std::ostringstream os;

    uint32_t lensId = 25620; // Minolta AF 50mm F1.4

    uint32_t index = 1;

    Exiv2::Internal::resolvedLensName(os, lensId, index);

    EXPECT_THAT(os.str(), Eq("Minolta AF 50mm F1.4 [New]"));

}



TEST(ResolvedLensName, ValidLensWithMultipleEntries) {

    std::ostringstream os;

    uint32_t lensId = 26281; // Minolta AF 80-200mm F2.8 HS-APO G

    uint32_t index = 1;

    Exiv2::Internal::resolvedLensName(os, lensId, index);

    EXPECT_THAT(os.str(), Eq("Minolta AF 80-200mm F2.8 HS-APO G"));

}



TEST(ResolvedLensName, LensWithIndexOutOfBounds) {

    std::ostringstream os;

    uint32_t lensId = 65535; // Manual lens | Sony E 50mm F1.8 OSS | E PZ 16-50mm F3.5-5.6 OSS

    uint32_t index = 10; // Out of bounds index

    Exiv2::Internal::resolvedLensName(os, lensId, index);

    EXPECT_THAT(os.str(), Eq("Manual lens | Sony E 50mm F1.8 OSS | E PZ 16-50mm F3.5-5.6 OSS"));

}



TEST(ResolvedLensName, LensNotFound) {

    std::ostringstream os;

    uint32_t lensId = 99999; // Non-existent lens ID

    uint32_t index = 1;

    Exiv2::Internal::resolvedLensName(os, lensId, index);

    EXPECT_THAT(os.str(), Eq(""));

}



TEST(ResolvedLensName, LensWithMultipleEntriesDifferentIndex) {

    std::ostringstream os;

    uint32_t lensId = 25640; // Minolta AF 50mm F2.8 Macro

    uint32_t index = 1;

    Exiv2::Internal::resolvedLensName(os, lensId, index);

    EXPECT_THAT(os.str(), Eq("Minolta AF 50mm F2.8 Macro | Sigma 50mm F2.8 EX Macro"));

}



TEST(ResolvedLensName, LensWithNoAlternative) {

    std::ostringstream os;

    uint32_t lensId = 26120; // Minolta AF 200mm F2.8 G

    uint32_t index = 0;

    Exiv2::Internal::resolvedLensName(os, lensId, index);

    EXPECT_THAT(os.str(), Eq("Minolta AF 200mm F2.8 G"));

}



} } // namespace Exiv2::
