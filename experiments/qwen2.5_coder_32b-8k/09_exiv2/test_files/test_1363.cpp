#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



namespace Exiv2 {

    namespace Internal {

        bool isMakerIfd(IfdId ifdId);

    }

}



TEST(IsMakerIfdTest_1363, NormalOperation_MakerIfd_1363) {

    EXPECT_TRUE(Exiv2::Internal::isMakerIfd(Exiv2::IfdId::mnId));

    EXPECT_TRUE(Exiv2::Internal::isMakerIfd(Exiv2::IfdId::canonId));

    EXPECT_TRUE(Exiv2::Internal::isMakerIfd(Exiv2::IfdId::panaRawId));

}



TEST(IsMakerIfdTest_1363, NormalOperation_NonMakerIfd_1363) {

    EXPECT_FALSE(Exiv2::Internal::isMakerIfd(Exiv2::IfdId::ifd0Id));

    EXPECT_FALSE(Exiv2::Internal::isMakerIfd(Exiv2::IfdId::gpsId));

    EXPECT_FALSE(Exiv2::Internal::isMakerIfd(Exiv2::IfdId::subImage1Id));

}



TEST(IsMakerIfdTest_1363, BoundaryCondition_FirstElement_1363) {

    EXPECT_FALSE(Exiv2::Internal::isMakerIfd(Exiv2::IfdId::ifdIdNotSet));

}



TEST(IsMakerIfdTest_1363, BoundaryCondition_LastElement_1363) {

    EXPECT_FALSE(Exiv2::Internal::isMakerIfd(Exiv2::IfdId::lastId));

}
