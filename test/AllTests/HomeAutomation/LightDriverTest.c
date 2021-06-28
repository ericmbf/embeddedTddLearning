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
#include "LightDriver.h"

#define NONSENSE_POINTER (LightDriver)~0

static void shouldNotBeCalled(LightDriver self);

static LightDriver savedDriver = NONSENSE_POINTER;

static LightDriverInterfaceStruct interface =
{
    shouldNotBeCalled,
    shouldNotBeCalled,
    shouldNotBeCalled
};

static LightDriverStruct testDriver =
{
    "testDriver",
    13
};

TEST_GROUP(LightDriver);

TEST_SETUP(LightDriver)
{
}

TEST_TEAR_DOWN(LightDriver)
{
}

TEST(LightDriver, NullDriverDoesNotCrash)
{
    LightDriver_SetInterface(&interface);
    LightDriver_TurnOn(NULL);
    LightDriver_TurnOff(NULL);
    LightDriver_Destroy(NULL);
    TEST_ASSERT_POINTERS_EQUAL(NONSENSE_POINTER, savedDriver);
}

TEST(LightDriver, NullInterfaceDoesNotCrash)
{
    LightDriver_SetInterface(NULL);
    LightDriver_TurnOn(&testDriver);
    LightDriver_TurnOff(&testDriver);
    LightDriver_Destroy(&testDriver);
    TEST_ASSERT_POINTERS_EQUAL(NONSENSE_POINTER, savedDriver);
}

static void shouldNotBeCalled(LightDriver self)
{
    savedDriver = self;
}
