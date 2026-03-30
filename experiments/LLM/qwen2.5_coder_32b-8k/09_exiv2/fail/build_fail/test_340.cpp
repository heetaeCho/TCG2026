#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"

#include "tiffvisitor_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class TiffImageEntryTest_340 : public ::testing::Test {

protected:

    TiffImageEntry entry_;

};



TEST_F(TiffImageEntryTest_340, DoAcceptCallsVisitImageEntry_340) {

    MockTiffVisitor visitor;

    EXPECT_CALL(visitor, visitImageEntry(&entry_));

    entry_.doAccept(visitor);

}



class MockTiffVisitor : public TiffVisitor {

public:

    MOCK_METHOD(void, visitEntry, (TiffEntry* object), (override));

    MOCK_METHOD(void, visitDataEntry, (TiffDataEntry* object), (override));

    MOCK_METHOD(void, visitImageEntry, (TiffImageEntry* object), (override));

    MOCK_METHOD(void, visitSizeEntry, (TiffSizeEntry* object), (override));

    MOCK_METHOD(void, visitDirectory, (TiffDirectory* object), (override));

    MOCK_METHOD(void, visitDirectoryNext, (TiffDirectory* object), (override));

    MOCK_METHOD(void, visitDirectoryEnd, (TiffDirectory* object), (override));

    MOCK_METHOD(void, visitSubIfd, (TiffSubIfd* object), (override));

    MOCK_METHOD(void, visitMnEntry, (TiffMnEntry* object), (override));

    MOCK_METHOD(void, visitIfdMakernote, (TiffIfdMakernote* object), (override));

    MOCK_METHOD(void, visitIfdMakernoteEnd, (TiffIfdMakernote* object), (override));

    MOCK_METHOD(void, visitBinaryArray, (TiffBinaryArray* object), (override));

    MOCK_METHOD(void, visitBinaryArrayEnd, (TiffBinaryArray* object), (override));

    MOCK_METHOD(void, visitBinaryElement, (TiffBinaryElement* object), (override));

};
