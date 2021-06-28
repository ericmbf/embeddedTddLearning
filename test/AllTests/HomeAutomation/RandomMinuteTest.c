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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "RandomMinute.h"

enum
{
    BOUND = 30
};

static void AssertMinuteIsInRange();

int minute;

TEST_GROUP(RandomMinute);

TEST_SETUP(RandomMinute)
{
    RandomMinute_Create(BOUND);
    srand(1);
}

TEST_TEAR_DOWN(RandomMinute)
{
    // RandomMinute_Destroy();
}

TEST(RandomMinute, GetIsInRange)
{
    for (int i = 0; i < 100; i++)
    {
        minute = RandomMinute_Get();
        AssertMinuteIsInRange();
    }
}

TEST(RandomMinute, AllValuesPossible)
{
    int hit[2 * BOUND + 1];
    memset(hit, 0, sizeof(hit));
    int i;
    for (i = 0; i < 600; i++)
    {
        minute = RandomMinute_Get();
        AssertMinuteIsInRange();
        hit[minute + BOUND]++;
    }
    for (i = 0; i < 2 * BOUND + 1; i++)
    {
        CHECK(hit[i] > 0);
    }
}

static void AssertMinuteIsInRange()
{
    if (minute < -BOUND || minute > BOUND)
    {
        char buffer[50];
        sprintf(buffer, "bad minute value: %d\n", minute);
        TEST_MESSAGE(buffer);
        TEST_FAIL_MESSAGE("Minute out of range");
    }
}