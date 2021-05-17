/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
/*- ------------------------------------------------------------------ -*/
/*-    Copyright (c) James W. Grenning -- All Rights Reserved          -*/
/*-    For use by owners of Test-Driven Development for Embedded C,    -*/
/*-    and attendees of Renaissance Software Consulting, Co. training  -*/
/*-    classes.                                                        -*/
/*-                                                                    -*/
/*-    Available at http://pragprog.com/titles/jgade/                  -*/
/*-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3                -*/
/*-                                                                    -*/
/*-    Authorized users may use this source code in your own           -*/
/*-    projects, however the source code may not be used to            -*/
/*-    create training material, courses, books, articles, and         -*/
/*-    the like. We make no guarantees that this source code is        -*/
/*-    fit for any purpose.                                            -*/
/*-                                                                    -*/
/*-    www.renaissancesoftware.net james@renaissancesoftware.net       -*/
/*- ------------------------------------------------------------------ -*/

#include <stdlib.h>
#include <memory.h>
#include "LightDriverSpy.h"
#include "common.h"


typedef struct LightDriverSpyStruct * LightDriverSpy;
typedef struct LightDriverSpyStruct
{
    LightDriverStruct base;
} LightDriverSpyStruct;

static void save(int id, int state);
static void destroy(LightDriver base);
static void update(int id, int state);
static void turnOn(LightDriver base);
static void turnOff(LightDriver base);

static int states[MAX_LIGHTS];
static int lastId;
static int lastState;

static LightDriverInterfaceStruct interface =
{
    .Destroy = destroy,
    .TurnOn = turnOn,
    .TurnOff = turnOff
};

void LightDriverSpy_Reset(void)
{
    int i;
    for (i = 0; i < MAX_LIGHTS; i++)
    {
        states[i] = LIGHT_STATE_UNKNOWN;
    }
    lastId = LIGHT_ID_UNKNOWN;
    lastState = LIGHT_STATE_UNKNOWN;
}

void LightDriverSpy_AddSpiesToController(void)
{
    int i;
    for (i = 0; i < MAX_LIGHTS; i++)
    {
        LightDriver spy = (LightDriver)LightDriverSpy_Create(i);
        LightController_Add(i, spy);
    }
}

LightDriver LightDriverSpy_Create(int id)
{
    LightDriverSpy self = calloc(1, sizeof(LightDriverSpyStruct));
    self->base.vtable = &interface;
    self->base.type = "Spy";
    self->base.id = id;
    return (LightDriver)self;
}

void LightDriverSpy_Destroy(LightDriver super)
{
    LightDriverSpy self = (LightDriverSpy)super;
    states[self->base.id] = LIGHT_STATE_UNKNOWN;
    free(self);
}

void LightDriverSpy_TurnOn(LightDriver super)
{
    LightDriverSpy self = (LightDriverSpy)super;
    save(self->base.id, LIGHT_ON);
}

void LightDriverSpy_TurnOff(LightDriver super)
{
    LightDriverSpy self = (LightDriverSpy)super;
    save(self->base.id, LIGHT_OFF);
}

int LightDriverSpy_GetState(int id)
{
    return states[id];
}

int LightDriverSpy_GetLastId(void)
{
    return lastId;
}

int LightDriverSpy_GetLastState(void)
{
    return lastState;
}

void LightDriverSpy_InstallInterface(void)
{
    LightDriver_SetInterface(&interface);
}

static void save(int id, int state)
{
    states[id] = state;
    lastId = id;
    lastState = state;
}

static void destroy(LightDriver base)
{
    free(base);
}
static void update(int id, int state)
{
    states[id] = state;
    lastId = id;
    lastState = state;
}
static void turnOn(LightDriver base)
{
    LightDriverSpy self = (LightDriverSpy)base;
    update(self->base.id, LIGHT_ON);
}
static void turnOff(LightDriver base)
{
    LightDriverSpy self = (LightDriverSpy)base;
    update(self->base.id, LIGHT_OFF);
}
