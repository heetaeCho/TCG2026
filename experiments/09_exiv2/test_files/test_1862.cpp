#include <gtest/gtest.h>

#include "exiv2/iptc.hpp"

#include "exiv2/xmp_exiv2.hpp"



namespace Exiv2 {

    void copyXmpToIptc(const XmpData& xmpData, IptcData& iptcData);

}



class CopyXmpToIptcTest : public ::testing::Test {

protected:

    Exiv2::XmpData xmpData;

    Exiv2::IptcData iptcData;



    void SetUp() override {

        // Setup any state needed for tests

        xmpData.clear();

        iptcData.clear();

    }

};



TEST_F(CopyXmpToIptcTest, CopyEmptyXmpToIptc_1862) {

    Exiv2::copyXmpToIptc(xmpData, iptcData);

    EXPECT_EQ(iptcData.size(), 0u);

}



TEST_F(CopyXmpToIptcTest, CopySingleXmpEntryToIptc_1862) {

    xmpData.add(Exiv2::XmpKey("Xmp.dc.title"), new Exiv2::Value("Sample Title"));

    Exiv2::copyXmpToIptc(xmpData, iptcData);

    EXPECT_EQ(iptcData.size(), 1u);

}



TEST_F(CopyXmpToIptcTest, CopyMultipleXmpEntriesToIptc_1862) {

    xmpData.add(Exiv2::XmpKey("Xmp.dc.title"), new Exiv2::Value("Sample Title"));

    xmpData.add(Exiv2::XmpKey("Xmp.dc.description"), new Exiv2::Value("Sample Description"));

    Exiv2::copyXmpToIptc(xmpData, iptcData);

    EXPECT_EQ(iptcData.size(), 2u);

}



TEST_F(CopyXmpToIptcTest, CopyXmpEntriesWithSameKey_1862) {

    xmpData.add(Exiv2::XmpKey("Xmp.dc.title"), new Exiv2::Value("First Title"));

    xmpData.add(Exiv2::XmpKey("Xmp.dc.title"), new Exiv2::Value("Second Title")); // Assuming XmpData allows duplicate keys

    Exiv2::copyXmpToIptc(xmpData, iptcData);

    EXPECT_EQ(iptcData.size(), 1u); // IptcData typically does not allow duplicate keys

}



TEST_F(CopyXmpToIptcTest, CopyXmpEntriesWithDifferentNamespaces_1862) {

    xmpData.add(Exiv2::XmpKey("Xmp.dc.title"), new Exiv2::Value("Sample Title"));

    xmpData.add(Exiv2::XmpKey("Xmp.iptc4xmpcore.City"), new Exiv2::Value("Sample City"));

    Exiv2::copyXmpToIptc(xmpData, iptcData);

    EXPECT_EQ(iptcData.size(), 2u); // Both should be converted if mappings exist

}



TEST_F(CopyXmpToIptcTest, CopyXmpEntriesWithNonConvertableKeys_1862) {

    xmpData.add(Exiv2::XmpKey("Xmp.dc.title"), new Exiv2::Value("Sample Title"));

    xmpData.add(Exiv2::XmpKey("Xmp.nonexistent.key"), new Exiv2::Value("Nonexistent Value")); // No mapping in IPTC

    Exiv2::copyXmpToIptc(xmpData, iptcData);

    EXPECT_EQ(iptcData.size(), 1u); // Only the mappable key should be converted

}



TEST_F(CopyXmpToIptcTest, CopyLargeXmpDataToIptc_1862) {

    for (int i = 0; i < 100; ++i) { // Adding many entries to XmpData

        xmpData.add(Exiv2::XmpKey("Xmp.dc.title" + std::to_string(i)), new Exiv2::Value("Sample Title " + std::to_string(i)));

    }

    Exiv2::copyXmpToIptc(xmpData, iptcData);

    EXPECT_EQ(iptcData.size(), 100u); // Assuming all entries are mappable

}



TEST_F(CopyXmpToIptcTest, CopyXmpEntriesWithSpecialCharacters_1862) {

    xmpData.add(Exiv2::XmpKey("Xmp.dc.title"), new Exiv2::Value("!@#$%^&*()_+"));

    Exiv2::copyXmpToIptc(xmpData, iptcData);

    EXPECT_EQ(iptcData.size(), 1u); // Special characters should not affect conversion

}



TEST_F(CopyXmpToIptcTest, CopyXmpEntriesWithEmptyValues_1862) {

    xmpData.add(Exiv2::XmpKey("Xmp.dc.title"), new Exiv2::Value(""));

    Exiv2::copyXmpToIptc(xmpData, iptcData);

    EXPECT_EQ(iptcData.size(), 0u); // Empty values might be ignored during conversion

}
