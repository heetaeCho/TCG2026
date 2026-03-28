#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class TiffImageEntryMock : public TiffImageEntry {

public:

    MOCK_METHOD(void, doAccept, (TiffVisitor & visitor), (override));

    MOCK_METHOD(size_t, doWrite, (IoWrapper & ioWrapper, ByteOrder byteOrder, size_t offset, size_t valueIdx, size_t dataIdx, size_t & imageIdx), (const override));

};



class TiffCopierTest_1644 : public ::testing::Test {

protected:

    std::unique_ptr<TiffImageEntryMock> mockTiffImageEntry;

    TiffComponent* pRoot = nullptr;

    uint32_t root = 0;

    const TiffHeaderBase* pHeader = nullptr;

    PrimaryGroups pPrimaryGroups;



    void SetUp() override {

        mockTiffImageEntry = std::make_unique<TiffImageEntryMock>();

    }

};



TEST_F(TiffCopierTest_1644, VisitImageEntry_CallsCopyObject_1644) {

    TiffCopier copier(pRoot, root, pHeader, pPrimaryGroups);

    EXPECT_CALL(*mockTiffImageEntry, doAccept(_)).WillOnce([this](TiffVisitor & visitor) { visitor.visitImageEntry(this->mockTiffImageEntry.get()); });



    mockTiffImageEntry->doAccept(copier);



    // Since visitImageEntry calls copyObject internally, we need to verify that copyObject is called.

    EXPECT_CALL(copier, copyObject(mockTiffImageEntry.get()));

}



TEST_F(TiffCopierTest_1644, VisitImageEntry_VerifyExternalInteraction_1644) {

    TiffCopier copier(pRoot, root, pHeader, pPrimaryGroups);

    EXPECT_CALL(*mockTiffImageEntry, doAccept(_)).WillOnce([this](TiffVisitor & visitor) { visitor.visitImageEntry(this->mockTiffImageEntry.get()); });



    mockTiffImageEntry->doAccept(copier);



    // Verify that copyObject is called with the correct parameter.

    EXPECT_CALL(copier, copyObject(mockTiffImageEntry.get()));

}
