// =================================================================================================
// TEST_ID: 2107
// Unit tests for EmitRDFArrayTag (./TestProjects/exiv2/xmpsdk/src/XMPMeta-Serialize.cpp)
// =================================================================================================

#include <gtest/gtest.h>

#include <string>

// Pull in XMP basic types and option bits.
#include "XMP_Const.h"
#include "XMP_BuildInfo.h"
#include "XMP_Environment.h"
#include "XMP_Utils.hpp"
#include "XMPMeta.hpp"

// NOTE: EmitRDFArrayTag is a `static` function in a .cpp file. To test it as a black box without
// accessing private state, we compile it into this test translation unit by including the .cpp.
// This makes the static symbol visible here without altering production code.
#include "xmpsdk/src/XMPMeta-Serialize.cpp"

namespace {

class EmitRDFArrayTagTest_2107 : public ::testing::Test {
protected:
  XMP_VarString out_;
  const char* nl_ = "\n";
  const char* indentStr_ = "  "; // two spaces
};

TEST_F(EmitRDFArrayTagTest_2107, EndTagWithEmptyArrayEmitsNothing_2107) {
  out_ = "prefix";
  EmitRDFArrayTag(/*arrayForm=*/kXMP_PropArrayIsUnordered, out_, nl_, indentStr_,
                  /*indent=*/0, /*arraySize=*/0, /*isStartTag=*/false);
  EXPECT_EQ(out_, "prefix");
}

TEST_F(EmitRDFArrayTagTest_2107, StartTagWithEmptyArrayIsSelfClosing_2107) {
  out_.clear();
  EmitRDFArrayTag(/*arrayForm=*/kXMP_PropArrayIsUnordered, out_, nl_, indentStr_,
                  /*indent=*/0, /*arraySize=*/0, /*isStartTag=*/true);
  EXPECT_EQ(out_, std::string("<rdf:Bag/>") + nl_);
}

TEST_F(EmitRDFArrayTagTest_2107, StartTagWithNonEmptyArrayIsNotSelfClosing_2107) {
  out_.clear();
  EmitRDFArrayTag(/*arrayForm=*/kXMP_PropArrayIsUnordered, out_, nl_, indentStr_,
                  /*indent=*/0, /*arraySize=*/3, /*isStartTag=*/true);
  EXPECT_EQ(out_, std::string("<rdf:Bag>") + nl_);
}

TEST_F(EmitRDFArrayTagTest_2107, EndTagWithNonEmptyArrayEmitsClosingTag_2107) {
  out_.clear();
  EmitRDFArrayTag(/*arrayForm=*/kXMP_PropArrayIsUnordered, out_, nl_, indentStr_,
                  /*indent=*/0, /*arraySize=*/1, /*isStartTag=*/false);
  EXPECT_EQ(out_, std::string("</rdf:Bag>") + nl_);
}

TEST_F(EmitRDFArrayTagTest_2107, IndentIsRepeatedIndentTimes_2107) {
  out_.clear();
  EmitRDFArrayTag(/*arrayForm=*/kXMP_PropArrayIsOrdered, out_, nl_, indentStr_,
                  /*indent=*/3, /*arraySize=*/2, /*isStartTag=*/true);

  // Expect 3 * indentStr_ then "<rdf:Seq>\n"
  EXPECT_EQ(out_, std::string("  ") + "  " + "  " + "<rdf:Seq>\n");
}

TEST_F(EmitRDFArrayTagTest_2107, AlternateArrayUsesAltTag_2107) {
  out_.clear();
  EmitRDFArrayTag(/*arrayForm=*/kXMP_PropArrayIsAlternate, out_, nl_, indentStr_,
                  /*indent=*/1, /*arraySize=*/5, /*isStartTag=*/true);
  EXPECT_EQ(out_, std::string("  <rdf:Alt>") + nl_);
}

TEST_F(EmitRDFArrayTagTest_2107, OrderedArrayUsesSeqTag_2107) {
  out_.clear();
  EmitRDFArrayTag(/*arrayForm=*/kXMP_PropArrayIsOrdered, out_, nl_, indentStr_,
                  /*indent=*/0, /*arraySize=*/5, /*isStartTag=*/true);
  EXPECT_EQ(out_, std::string("<rdf:Seq>") + nl_);
}

TEST_F(EmitRDFArrayTagTest_2107, UnorderedOrUnknownFormDefaultsToBag_2107) {
  out_.clear();

  // Use 0 option bits (no alternate/ordered bits set) => Bag.
  EmitRDFArrayTag(/*arrayForm=*/0, out_, nl_, indentStr_,
                  /*indent=*/0, /*arraySize=*/5, /*isStartTag=*/true);
  EXPECT_EQ(out_, std::string("<rdf:Bag>") + nl_);
}

TEST_F(EmitRDFArrayTagTest_2107, AlternateTakesPrecedenceOverOrdered_2107) {
  out_.clear();

  // Both bits set: should pick Alt (per observable output).
  EmitRDFArrayTag(/*arrayForm=*/(kXMP_PropArrayIsAlternate | kXMP_PropArrayIsOrdered),
                  out_, nl_, indentStr_,
                  /*indent=*/0, /*arraySize=*/2, /*isStartTag=*/true);
  EXPECT_EQ(out_, std::string("<rdf:Alt>") + nl_);
}

TEST_F(EmitRDFArrayTagTest_2107, NewlineAndIndentStringsAreAppendedVerbatim_2107) {
  out_.clear();

  const char* customNL = "\r\n";
  const char* customIndent = "\t";
  EmitRDFArrayTag(/*arrayForm=*/kXMP_PropArrayIsUnordered, out_, customNL, customIndent,
                  /*indent=*/2, /*arraySize=*/0, /*isStartTag=*/true);

  EXPECT_EQ(out_, std::string("\t\t<rdf:Bag/>") + "\r\n");
}

} // namespace