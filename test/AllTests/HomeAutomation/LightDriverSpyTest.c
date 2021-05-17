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
#include "LightDriverSpy.h"

TEST_GROUP(LightDriverSpy);

static LightDriver lightDriverSpy;

TEST_SETUP(LightDriverSpy)
{
    LightDriverSpy_Reset();
    lightDriverSpy = LightDriverSpy_Create(1);
    LightDriverSpy_InstallInterface();
}

TEST_TEAR_DOWN(LightDriverSpy)
{
    LightDriverSpy_Destroy(lightDriverSpy);
}

TEST(LightDriverSpy, Create)
{
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetState(1));
}

TEST(LightDriverSpy, On)
{
    // LightDriverSpy_TurnOn(lightDriverSpy);
    LightDriver_TurnOn(lightDriverSpy);
    LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetState(1));
}

TEST(LightDriverSpy, LightStateUnknownAfterCreate)
{
    LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightDriverSpy_GetState(1));
}

TEST(LightDriverSpy, Off)
{
    LightDriver_TurnOff(lightDriverSpy);
    LONGS_EQUAL(LIGHT_OFF, LightDriverSpy_GetState(1));
}

TEST(LightDriverSpy, RecordsLastIdLastTurnOn)
{
    LightDriver_TurnOff(lightDriverSpy);
    LONGS_EQUAL(1, LightDriverSpy_GetLastId());
    LONGS_EQUAL(LIGHT_OFF, LightDriverSpy_GetLastState());
}

TEST(LightDriverSpy, RecordsLastIdLastTurnOff)
{
    LightDriver_TurnOn(lightDriverSpy);
    LONGS_EQUAL(1, LightDriverSpy_GetLastId());
    LONGS_EQUAL(LIGHT_ON, LightDriverSpy_GetLastState());
}