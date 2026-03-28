#include <gtest/gtest.h>

#include "exiv2/image.hpp"

#include "exiv2/iptc.hpp"



using namespace Exiv2;



class ImageTest_1076 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = BasicIo::createMemIo();

    Image image {ImageType::jpeg, MetadataId::all, std::move(io)};

};



TEST_F(ImageTest_1076, SetIptcDataWithEmptyIptcData_1076) {

    IptcData emptyIptcData;

    image.setIptcData(emptyIptcData);

}



TEST_F(ImageTest_1076, SetIptcDataWithNonEmptyIptcData_1076) {

    IptcData iptcData;

    iptcData.add(IptcKey("Iptc.Application2.Keywords"), new Value(U"testKeyword"));

    image.setIptcData(iptcData);

}



TEST_F(ImageTest_1076, SetIptcDataMultipleTimes_1076) {

    IptcData iptcData1;

    iptcData1.add(IptcKey("Iptc.Application2.Keywords"), new Value(U"testKeyword1"));

    

    IptcData iptcData2;

    iptcData2.add(IptcKey("Iptc.Application2.Keywords"), new Value(U"testKeyword2"));



    image.setIptcData(iptcData1);

    image.setIptcData(iptcData2);

}



TEST_F(ImageTest_1076, SetIptcDataWithLargeData_1076) {

    IptcData iptcData;

    for (int i = 0; i < 100; ++i) {

        std::string key = "Iptc.Application2.Keywords" + std::to_string(i);

        iptcData.add(IptcKey(key), new Value(U"largeKeyword"));

    }

    image.setIptcData(iptcData);

}
