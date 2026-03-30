// File: HtmlLinks_test_2659.cpp

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <type_traits>

#include "TestProjects/poppler/utils/HtmlLinks.h"

// Poppler core string type
#include "goo/GooString.h"

namespace {

std::unique_ptr<GooString> MakeDest(const char *s)
{
  return std::make_unique<GooString>(s);
}

HtmlLink MakeLink(double x1, double y1, double x2, double y2, const char *dest)
{
  return HtmlLink(x1, y1, x2, y2, MakeDest(dest));
}

std::string GooToStdString(const GooString *gs)
{
  if (!gs) {
    return {};
  }
  return std::string(gs->c_str());
}

} // namespace

class HtmlLinksTest_2659 : public ::testing::Test {};

TEST_F(HtmlLinksTest_2659, TypeTraits_CopyAndAssignAreDeleted_2659)
{
  static_assert(!std::is_copy_constructible<HtmlLinks>::value,
                "HtmlLinks must not be copy-constructible");
  static_assert(!std::is_copy_assignable<HtmlLinks>::value,
                "HtmlLinks must not be copy-assignable");
}

TEST_F(HtmlLinksTest_2659, AddLinkThenGetLinkReturnsNonNull_2659)
{
  HtmlLinks links;

  HtmlLink link = MakeLink(1.0, 2.0, 3.0, 4.0, "destA");
  links.AddLink(link);

  const HtmlLink *p = links.getLink(0);
  ASSERT_NE(p, nullptr);

  EXPECT_DOUBLE_EQ(p->getX1(), 1.0);
  EXPECT_DOUBLE_EQ(p->getY1(), 2.0);
  EXPECT_DOUBLE_EQ(p->getX2(), 3.0);
  EXPECT_DOUBLE_EQ(p->getY2(), 4.0);

  auto start = p->getLinkStart();
  ASSERT_NE(start, nullptr);
  EXPECT_EQ(GooToStdString(start.get()), "destA");
}

TEST_F(HtmlLinksTest_2659, AddLinkWithTemporaryObject_2659)
{
  HtmlLinks links;

  // AddLink takes const HtmlLink&, so it should accept a temporary.
  links.AddLink(MakeLink(10.0, 20.0, 30.0, 40.0, "tmp"));

  const HtmlLink *p = links.getLink(0);
  ASSERT_NE(p, nullptr);

  auto start = p->getLinkStart();
  ASSERT_NE(start, nullptr);
  EXPECT_EQ(GooToStdString(start.get()), "tmp");
}

TEST_F(HtmlLinksTest_2659, AddMultipleLinksPreservesOrder_2659)
{
  HtmlLinks links;

  HtmlLink a = MakeLink(0.0, 0.0, 1.0, 1.0, "A");
  HtmlLink b = MakeLink(2.0, 2.0, 3.0, 3.0, "B");
  HtmlLink c = MakeLink(4.0, 4.0, 5.0, 5.0, "C");

  links.AddLink(a);
  links.AddLink(b);
  links.AddLink(c);

  const HtmlLink *p0 = links.getLink(0);
  const HtmlLink *p1 = links.getLink(1);
  const HtmlLink *p2 = links.getLink(2);

  ASSERT_NE(p0, nullptr);
  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);

  auto s0 = p0->getLinkStart();
  auto s1 = p1->getLinkStart();
  auto s2 = p2->getLinkStart();

  ASSERT_NE(s0, nullptr);
  ASSERT_NE(s1, nullptr);
  ASSERT_NE(s2, nullptr);

  EXPECT_EQ(GooToStdString(s0.get()), "A");
  EXPECT_EQ(GooToStdString(s1.get()), "B");
  EXPECT_EQ(GooToStdString(s2.get()), "C");
}

TEST_F(HtmlLinksTest_2659, InLinkFindsMatchingLinkAndReturnsIndex_2659)
{
  HtmlLinks links;

  // Two non-overlapping links.
  links.AddLink(MakeLink(0.0, 0.0, 10.0, 10.0, "L0"));
  links.AddLink(MakeLink(20.0, 20.0, 30.0, 30.0, "L1"));

  size_t idx = static_cast<size_t>(-1);

  // Query rectangle that should lie within the first link's bounds.
  const bool found = links.inLink(1.0, 1.0, 2.0, 2.0, idx);
  ASSERT_TRUE(found);
  EXPECT_EQ(idx, 0u);

  const HtmlLink *p = links.getLink(idx);
  ASSERT_NE(p, nullptr);
  auto s = p->getLinkStart();
  ASSERT_NE(s, nullptr);
  EXPECT_EQ(GooToStdString(s.get()), "L0");
}

TEST_F(HtmlLinksTest_2659, InLinkReturnsFalseWhenNoMatch_2659)
{
  HtmlLinks links;
  links.AddLink(MakeLink(0.0, 0.0, 10.0, 10.0, "L0"));

  size_t idx = 12345u;
  const bool found = links.inLink(100.0, 100.0, 101.0, 101.0, idx);
  EXPECT_FALSE(found);
}

TEST_F(HtmlLinksTest_2659, AddedLinkSurvivesAfterSourceDestroyed_2659)
{
  HtmlLinks links;

  {
    HtmlLink scoped = MakeLink(7.0, 8.0, 9.0, 10.0, "scopedDest");
    links.AddLink(scoped);
  } // original HtmlLink destroyed here

  const HtmlLink *p = links.getLink(0);
  ASSERT_NE(p, nullptr);

  auto s = p->getLinkStart();
  ASSERT_NE(s, nullptr);
  EXPECT_EQ(GooToStdString(s.get()), "scopedDest");
}

TEST_F(HtmlLinksTest_2659, GetLinkOutOfRangeReturnsNullptr_2659)
{
  HtmlLinks links;

  // Empty container
  EXPECT_EQ(links.getLink(0), nullptr);

  // After one insert, index 1 should be out-of-range
  links.AddLink(MakeLink(0.0, 0.0, 1.0, 1.0, "only"));
  EXPECT_EQ(links.getLink(1), nullptr);
}