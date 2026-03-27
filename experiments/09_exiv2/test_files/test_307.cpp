#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::NiceMock;



class MockMnHeader : public MnHeader {

public:

    MOCK_CONST_METHOD1(baseOffset, size_t(size_t));

};



class TiffIfdMakernoteTest_307 : public ::testing::Test {

protected:

    NiceMock<MockMnHeader> mockHeader;

    std::unique_ptr<MnHeader> pMockHeader = std::make_unique<NiceMock<MockMnHeader>>();

    TiffIfdMakernote tiffIfdMakernote{0x00, ifdGroupNone, ifdGroupNone, std::move(pMockHeader), false};

};



TEST_F(TiffIfdMakernoteTest_307, BaseOffsetReturnsZeroWhenNoHeader_307) {

    EXPECT_EQ(tiffIfdMakernote.baseOffset(), 0);

}



TEST_F(TiffIfdMakernoteTest_307, BaseOffsetDelegatesToHeader_307) {

    const size_t expectedOffset = 42;

    EXPECT_CALL(mockHeader, baseOffset(_)).WillOnce(::testing::Return(expectedOffset));

    EXPECT_EQ(tiffIfdMakernote.baseOffset(), expectedOffset);

}
