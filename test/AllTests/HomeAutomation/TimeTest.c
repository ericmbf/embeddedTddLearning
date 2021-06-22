//- ------------------------------------------------------------------
//-    Copyright (c) James W. Grenning -- All Rights Reserved
//-    For use by owners of Test-Driven Development for Embedded C,
//-    and attendees of Renaissance Software Consulting, Co. training
//-    classes.
//-
//-    Available at http://pragprog.com/titles/jgade/
//-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3
//-
//-    Authorized users may use this source code in your own
//-    projects, however the source code may not be used to
//-    create training material, courses, books, articles, and
//-    the like. We make no guarantees that this source code is
//-    fit for any purpose.
//-
//-    www.renaissancesoftware.net james@renaissancesoftware.net
//- ------------------------------------------------------------------
#include "unity_fixture.h"
#include "TimeService.h"

enum
{
    TIME_UNKNOWN = -1,
};

static void givenThatItIs(E_DAY_t day);
static void CheckThatTimeMatches(E_DAY_t day);
static void CheckThatTimeDoesNotMatch(E_DAY_t day);

Time time;

TEST_GROUP(Time);

TEST_SETUP(Time)
{
    TimeService_Create();
}

TEST_TEAR_DOWN(Time)
{
    TimeService_Destroy();
}

TEST(Time, ExactMatch)
{
    givenThatItIs(MONDAY);
    CheckThatTimeMatches(MONDAY);
    givenThatItIs(TUESDAY);
    CheckThatTimeMatches(TUESDAY);
    givenThatItIs(WEDNESDAY);
    CheckThatTimeMatches(WEDNESDAY);
    givenThatItIs(THURSDAY);
    CheckThatTimeMatches(THURSDAY);
    givenThatItIs(FRIDAY);
    CheckThatTimeMatches(FRIDAY);
    givenThatItIs(SATURDAY);
    CheckThatTimeMatches(SATURDAY);
    givenThatItIs(SUNDAY);
    CheckThatTimeMatches(SUNDAY);
}

TEST(Time, WeekendDays)
{
    givenThatItIs(SATURDAY);
    CheckThatTimeMatches(WEEKEND);
    givenThatItIs(SUNDAY);
    CheckThatTimeMatches(WEEKEND);
}

TEST(Time, NotWeekendDays)
{
    givenThatItIs(MONDAY);
    CheckThatTimeDoesNotMatch(WEEKEND);
    givenThatItIs(TUESDAY);
    CheckThatTimeDoesNotMatch(WEEKEND);
    givenThatItIs(WEDNESDAY);
    CheckThatTimeDoesNotMatch(WEEKEND);
    givenThatItIs(THURSDAY);
    CheckThatTimeDoesNotMatch(WEEKEND);
    givenThatItIs(FRIDAY);
}

TEST(Time, WeekDays)
{
    givenThatItIs(MONDAY);
    CheckThatTimeMatches(WEEKDAY);
    givenThatItIs(TUESDAY);
    CheckThatTimeMatches(WEEKDAY);
    givenThatItIs(WEDNESDAY);
    CheckThatTimeMatches(WEEKDAY);
    givenThatItIs(THURSDAY);
    CheckThatTimeMatches(WEEKDAY);
    givenThatItIs(FRIDAY);
}

TEST(Time, NotWeekDays)
{
    givenThatItIs(SATURDAY);
    CheckThatTimeDoesNotMatch(WEEKDAY);
    givenThatItIs(SUNDAY);
    CheckThatTimeDoesNotMatch(WEEKDAY);
}

TEST(Time, Everyday)
{
    givenThatItIs(SATURDAY);
    CheckThatTimeMatches(EVERYDAY);
    givenThatItIs(SUNDAY);
    CheckThatTimeMatches(EVERYDAY);
    givenThatItIs(MONDAY);
    CheckThatTimeMatches(EVERYDAY);
    givenThatItIs(TUESDAY);
    CheckThatTimeMatches(EVERYDAY);
    givenThatItIs(WEDNESDAY);
    CheckThatTimeMatches(EVERYDAY);
    givenThatItIs(THURSDAY);
    CheckThatTimeMatches(EVERYDAY);
    givenThatItIs(FRIDAY);
}

static void givenThatItIs(E_DAY_t day)
{
    FakeTimeService_SetDay(day);
}

static void CheckThatTimeMatches(E_DAY_t day)
{
    TimeService_GetTime(&time);
    CHECK(Time_MatchesDayOfWeek(&time, day));
}

static void CheckThatTimeDoesNotMatch(E_DAY_t day)
{
    TimeService_GetTime(&time);
    CHECK(!Time_MatchesDayOfWeek(&time, day));
}