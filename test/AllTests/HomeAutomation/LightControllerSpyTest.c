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
#include "LightControllerSpy.h"

#if 0

TEST_GROUP(LightControllerSpy);
   
TEST_SETUP(LightControllerSpy)
{
    LightController_Create();
}

TEST_TEAR_DOWN(LightControllerSpy)
{
    LightController_Destroy();
}

TEST(LightControllerSpy, Create)
{
    TEST_ASSERT_EQUAL_INT(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

TEST(LightControllerSpy, RememberTheLastLightIdControlled)
{
    LightController_On(10);
    TEST_ASSERT_EQUAL_INT(10, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT(LIGHT_ON, LightControllerSpy_GetLastState());
}

TEST(LightControllerSpy, RememberAllLightStates)
{
    LightController_On(10);
    LightController_Off(12);
    TEST_ASSERT_EQUAL_INT(LIGHT_ON, LightControllerSpy_GetLightState(10));
    TEST_ASSERT_EQUAL_INT(LIGHT_OFF, LightControllerSpy_GetLightState(12));
}
#endif