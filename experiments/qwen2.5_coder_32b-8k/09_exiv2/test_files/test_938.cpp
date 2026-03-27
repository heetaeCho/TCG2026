#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/canonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::NiceMock;



class MockExifData : public Exiv2::ExifData {

public:

    MOCK_CONST_METHOD0(begin, iterator());

    MOCK_CONST_METHOD0(end, iterator());

};



TEST(CanonMakerNoteTagListHdr_938, ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListHdr();

    EXPECT_EQ(result, CanonMakerNote::tagInfoHdr_);

}



TEST(CanonMakerNotePrintFunctions_938, PrintFiFileNumber_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printFiFileNumber(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintFocalLength_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printFocalLength(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, Print0x0008_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::print0x0008(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, Print0x000a_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::print0x000a(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, Print0x000c_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::print0x000c(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintCs0x0002_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printCs0x0002(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintCsLensType_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printCsLensType(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintCsLens_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printCsLens(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintLe0x0000_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printLe0x0000(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintSi0x0001_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printSi0x0001(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintSi0x0002_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printSi0x0002(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintSi0x0003_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printSi0x0003(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintSi0x0009_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printSi0x0009(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintSi0x000c_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printSi0x000c(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintSi0x000d_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printSi0x000d(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintSi0x000e_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printSi0x000e(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintSi0x0013_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printSi0x0013(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintSi0x0015_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printSi0x0015(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintSi0x0016_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printSi0x0016(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintSi0x0017_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printSi0x0017(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintSi0x0018_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printSi0x0018(os, value, nullptr);

}



TEST(CanonMakerNotePrintFunctions_938, PrintFiFocusDistance_DoesNotCrashOnNullMetadata_938) {

    std::ostringstream os;

    Exiv2::Value value; // Assuming Value can be default constructed

    CanonMakerNote::printFiFocusDistance(os, value, nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagList_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagList();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListCs_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListCs();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListSi_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListSi();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListPa_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListPa();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListCf_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListCf();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListPi_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListPi();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListTi_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListTi();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListFi_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListFi();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListPr_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListPr();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListMv_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListMv();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListMc_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListMc();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListFcd3_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListFcd3();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListWbi_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListWbi();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListCo_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListCo();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListFcd2_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListFcd2();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListFcd1_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListFcd1();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListAs_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListAs();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListCbi_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListCbi();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListFl_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListFl();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListMo_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListMo();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListPreI_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListPreI();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListCi_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListCi();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListAfMiAdj_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListAfMiAdj();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListVigCor_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListVigCor();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListVigCor2_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListVigCor2();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListLiOp_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListLiOp();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListLe_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListLe();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListAm_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListAm();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListMe_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListMe();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListFil_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListFil();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListAfC_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListAfC();

    EXPECT_TRUE(result != nullptr);

}



TEST(CanonMakerNoteTagLists_938, TagListRawB_ReturnsStaticArray_938) {

    const auto& result = CanonMakerNote::tagListRawB();

    EXPECT_TRUE(result != nullptr);

}
