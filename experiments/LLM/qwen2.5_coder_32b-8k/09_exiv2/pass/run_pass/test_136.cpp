#include <gtest/gtest.h>

#include "exiv2/value.hpp"

#include "exiv2/types.hpp"



namespace {



TEST(GetTypeTest_136, Uint16ReturnsUnsignedShort_136) {

    EXPECT_EQ(Exiv2::getType<uint16_t>(), Exiv2::unsignedShort);

}



}  // namespace
