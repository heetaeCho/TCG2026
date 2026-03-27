#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"



namespace Exiv2 {

    class IptcKey;

    class Value;

}



using namespace Exiv2;



class IptcdatumTest_668 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize an IptcKey object

        key = std::make_unique<IptcKey>("IPTC.Test.Key");

        // Create an Iptcdatum object using the IptcKey

        iptcdatum = std::make_unique<Iptcdatum>(*key, nullptr);

    }



    std::unique_ptr<IptcKey> key;

    std::unique_ptr<Iptcdatum> iptcdatum;

};



TEST_F(IptcdatumTest_668, FamilyName_ReturnsCorrectValue_668) {

    EXPECT_STREQ(iptcdatum->familyName(), "IPTC");

}



TEST_F(IptcdatumTest_668, FamilyName_ReturnsEmptyStringWhenKeyIsNull_668) {

    Iptcdatum datumWithoutKey(IptcKey("", 0), nullptr);

    EXPECT_STREQ(datumWithoutKey.familyName(), "");

}
