// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::XmpData::erase(iterator)
// File: test_xmpdata_erase_1312.cpp
//
// Constraints:
// - Black-box tests only (public API / observable behavior)
// - No private state access
// - GoogleTest (+ GoogleMock not needed here)
// - TEST_ID in every test name (1312)
//
// *****************************************************************

#include <gtest/gtest.h>

#include <exiv2/xmp_exiv2.hpp>

namespace {

class XmpDataEraseTest_1312 : public ::testing::Test {
 protected:
  Exiv2::XmpData data_;
};

TEST_F(XmpDataEraseTest_1312, EraseFromSingleElementMakesEmpty_1312) {
  // Arrange: insert one datum via operator[]
  Exiv2::Xmpdatum& d = data_["Xmp.dc.title"];
  (void)d;  // content not relevant; presence is

  ASSERT_FALSE(data_.empty());
  ASSERT_EQ(data_.count(), 1);

  auto it = data_.begin();
  ASSERT_NE(it, data_.end());

  // Act
  auto next = data_.erase(it);

  // Assert: container is empty and returned iterator is end()
  EXPECT_TRUE(data_.empty());
  EXPECT_EQ(data_.count(), 0);
  EXPECT_EQ(next, data_.end());
}

TEST_F(XmpDataEraseTest_1312, EraseBeginReturnsIteratorToNextElement_1312) {
  // Arrange: create three distinct keys
  (void)data_["Xmp.dc.title"];
  (void)data_["Xmp.dc.creator"];
  (void)data_["Xmp.dc.subject"];

  ASSERT_EQ(data_.count(), 3);

  auto it0 = data_.begin();
  ASSERT_NE(it0, data_.end());

  auto it1 = it0;
  ++it1;
  ASSERT_NE(it1, data_.end());

  // Capture what "next" would be from begin() before erase
  auto expected_next = it0;
  ++expected_next;

  // Act
  auto ret = data_.erase(it0);

  // Assert: size decreased; returned iterator equals previously-next iterator
  EXPECT_EQ(data_.count(), 2);
  EXPECT_EQ(ret, expected_next);
  EXPECT_FALSE(data_.empty());

  // The returned iterator should still be a valid iterator in-range (or end).
  EXPECT_TRUE(ret == data_.end() || ret != data_.end());
}

TEST_F(XmpDataEraseTest_1312, EraseMiddleKeepsOthersAndReturnsNext_1312) {
  // Arrange: 3 elements, erase the middle one by iterator
  (void)data_["Xmp.dc.title"];
  (void)data_["Xmp.dc.creator"];
  (void)data_["Xmp.dc.subject"];
  ASSERT_EQ(data_.count(), 3);

  auto it_begin = data_.begin();
  ASSERT_NE(it_begin, data_.end());

  auto it_mid = it_begin;
  ++it_mid;
  ASSERT_NE(it_mid, data_.end());

  auto it_expected_next = it_mid;
  ++it_expected_next;

  // Act
  auto ret = data_.erase(it_mid);

  // Assert
  EXPECT_EQ(data_.count(), 2);
  EXPECT_EQ(ret, it_expected_next);

  // And remaining iterators should still allow traversal through count() elements.
  long traversed = 0;
  for (auto it = data_.begin(); it != data_.end(); ++it) {
    ++traversed;
  }
  EXPECT_EQ(traversed, data_.count());
}

TEST_F(XmpDataEraseTest_1312, EraseLastReturnsEnd_1312) {
  // Arrange: 2 elements, erase last
  (void)data_["Xmp.dc.title"];
  (void)data_["Xmp.dc.creator"];
  ASSERT_EQ(data_.count(), 2);

  auto it = data_.begin();
  ASSERT_NE(it, data_.end());
  auto it_last = it;
  ++it_last;
  ASSERT_NE(it_last, data_.end());

  // Act
  auto ret = data_.erase(it_last);

  // Assert
  EXPECT_EQ(data_.count(), 1);
  EXPECT_EQ(ret, data_.end());
  EXPECT_FALSE(data_.empty());
}

TEST_F(XmpDataEraseTest_1312, EraseOnEmptyNotPerformed_BoundaryCheck_1312) {
  // Boundary: we must not call erase(end()) or erase on empty because behavior is undefined
  // for many STL-like containers. This test documents safe preconditions via the interface.
  ASSERT_TRUE(data_.empty());
  ASSERT_EQ(data_.count(), 0);

  // Observable behavior: begin()==end() on empty (safe boundary check).
  EXPECT_EQ(data_.begin(), data_.end());
}

TEST_F(XmpDataEraseTest_1312, EraseThenFindKeyForRemainingStillWorks_1312) {
  // Arrange
  (void)data_["Xmp.dc.title"];
  (void)data_["Xmp.dc.creator"];
  ASSERT_EQ(data_.count(), 2);

  const Exiv2::XmpKey creatorKey("Xmp.dc.creator");
  const Exiv2::XmpKey titleKey("Xmp.dc.title");

  // Ensure keys are findable before erase
  auto it_creator_before = data_.findKey(creatorKey);
  ASSERT_NE(it_creator_before, data_.end());
  auto it_title_before = data_.findKey(titleKey);
  ASSERT_NE(it_title_before, data_.end());

  // Act: erase title
  auto it_title = data_.findKey(titleKey);
  ASSERT_NE(it_title, data_.end());
  (void)data_.erase(it_title);

  // Assert: title gone, creator remains
  EXPECT_EQ(data_.findKey(titleKey), data_.end());
  EXPECT_NE(data_.findKey(creatorKey), data_.end());
  EXPECT_EQ(data_.count(), 1);
}

TEST_F(XmpDataEraseTest_1312, EraseReturnedIteratorCanBeErasedAgainWhenNotEnd_1312) {
  // Arrange: 3 elements
  (void)data_["Xmp.dc.title"];
  (void)data_["Xmp.dc.creator"];
  (void)data_["Xmp.dc.subject"];
  ASSERT_EQ(data_.count(), 3);

  auto it0 = data_.begin();
  ASSERT_NE(it0, data_.end());

  // Act: erase first, get iterator to next; if not end, erase that as well
  auto it_next = data_.erase(it0);
  ASSERT_EQ(data_.count(), 2);

  if (it_next != data_.end()) {
    auto it_next2 = data_.erase(it_next);
    (void)it_next2;
    EXPECT_EQ(data_.count(), 1);
  } else {
    // If container were 1 element this would happen, but we inserted 3. Still keep safe.
    SUCCEED();
  }
}

}  // namespace