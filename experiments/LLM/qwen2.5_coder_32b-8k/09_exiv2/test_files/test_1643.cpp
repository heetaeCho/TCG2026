#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class TiffCopierTest : public ::testing::Test {

protected:

    TiffComponent* mockRoot = nullptr;

    const TiffHeaderBase* mockHeader = nullptr;

    PrimaryGroups mockPrimaryGroups;

    TiffDataEntry* testDataEntry = new TiffDataEntry();



    TiffCopier copier;



    void SetUp() override {

        copier = TiffCopier(mockRoot, 0, mockHeader, std::move(mockPrimaryGroups));

    }



    void TearDown() override {

        delete testDataEntry;

    }

};



TEST_F(TiffCopierTest_1643, VisitDataEntry_CallsCopyObjectWithCorrectObject_1643) {

    EXPECT_CALL(*testDataEntry, doAccept(_)).WillOnce([this](TiffVisitor& visitor) {

        dynamic_cast<TiffCopier*>(&visitor)->copyObject(testDataEntry);

    });



    copier.visitDataEntry(testDataEntry);

}



TEST_F(TiffCopierTest_1643, VisitDataEntry_DoesNotCrashWithNull_1643) {

    EXPECT_NO_THROW(copier.visitDataEntry(nullptr));

}
