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
    SATURDAY = 7
};

TEST_GROUP(FakeTimeService);

TEST_SETUP(FakeTimeService)
{
    TimeService_Create();
}

TEST_TEAR_DOWN(FakeTimeService)
{
    TimeService_Destroy();
}

TEST(FakeTimeService, Create)
{
    Time time;
    TimeService_GetTime(&time);
    TEST_ASSERT_EQUAL_INT(TIME_UNKNOWN, time.minuteOfDay);
    TEST_ASSERT_EQUAL_INT(TIME_UNKNOWN, time.dayOfWeek);
}

TEST(FakeTimeService, Set)
{
    Time time;
    FakeTimeService_SetMinute(42);
    FakeTimeService_SetDay(SATURDAY);
    TimeService_GetTime(&time);
    TEST_ASSERT_EQUAL_INT(42, time.minuteOfDay);
    TEST_ASSERT_EQUAL_INT(SATURDAY, time.dayOfWeek);
}