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
#include "LightController.h"
#include "LightDriverSpy.h"

TEST_GROUP(LightController);

static LightDriver spy;

TEST_SETUP(LightController)
{
    LightController_Create();
    LightDriverSpy_AddSpiesToController();
}

TEST_TEAR_DOWN(LightController)
{
    LightController_Destroy();
}

TEST(LightController, TurnOn)
{
	LightController_TurnOn(7);
	TEST_ASSERT_EQUAL_INT(LIGHT_ON, LightDriverSpy_GetState(7));
}