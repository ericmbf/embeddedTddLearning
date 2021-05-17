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

#include "LightDriver.h"
#include "common.h"

static LightDriverInterface interface = NULL;

void LightDriver_SetInterface(LightDriverInterface i)
{
    interface = i;
}

void LightDriver_Destroy(LightDriver self)
{
    if (self && self->vtable && self->vtable->Destroy)
    {
        self->vtable->Destroy(self);
    }
}

void LightDriver_TurnOn(LightDriver self)
{
    if (self && self->vtable && self->vtable->TurnOn)
    {
        self->vtable->TurnOn(self);
    }
}

void LightDriver_TurnOff(LightDriver self)
{
    if (self && self->vtable && self->vtable->TurnOff)
    {
        self->vtable->TurnOff(self);
    }
}