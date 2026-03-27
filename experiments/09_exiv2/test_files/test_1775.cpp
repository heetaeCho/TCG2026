#include <gtest/gtest.h>

#include "crwimage_int.hpp"

#include "exiv2/image.hpp"



using namespace Exiv2::Internal;

using namespace Exiv2;



class CiffHeaderTest_1775 : public ::testing::Test {

protected:

    std::unique_ptr<BasicIo> io = BasicIo::AutoPtr(new FileIo());

    Image image{ImageType::jpeg, 0x1F, std::move(io)};

    CiffHeader ciffHeader;

};



TEST_F(CiffHeaderTest_1775, DecodeCallsDecodeOnRootDirIfNotNull_1775) {

    auto mockComponent = std::make_unique<CiffComponent>();

    EXPECT_CALL(*mockComponent, decode(::testing::Ref(image), littleEndian)).Times(1);



    ciffHeader.pRootDir_.reset(mockComponent.release());

    ciffHeader.decode(image);

}



TEST_F(CiffHeaderTest_1775, DecodeDoesNothingIfRootDirIsNull_1775) {

    ciffHeader.pRootDir_.reset(nullptr);

    EXPECT_NO_THROW(ciffHeader.decode(image));

}



TEST_F(CiffHeaderTest_1775, ByteOrderIsLittleEndianByDefault_1775) {

    EXPECT_EQ(ciffHeader.byteOrder(), littleEndian);

}
