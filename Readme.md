# MSP430: development platform for [PlatformIO](http://platformio.org)

The MSP-EXP430FR4133 LaunchPad™ Development Kit is an easy-to-use evaluation module (EVM) for
the MSP430FR4133 microcontroller. It contains everything needed to start developing on
the MSP430™ ultra-low-power (ULP) FRAM-based microcontroller (MCU) platform using platformio and vscode integration, with uploading and debug using mspdebug and msp430-gdb.

This project uses the codes examples from book 
Test-Driven Development for Embedded C from James Grenning.

* [notes.json](File with all launch's necessary to run unit testing on native or target. Please, replace your launch.json file on ".vscode" folder o root project directory.

# Requirements

1. [Install PlatformIO](http://platformio.org)
2. Vscode
3. Installed mspdebug version 0.25
4. Installed msp430-gdb
5. Include unity_fixture.h in the same directory from unity test headers platformIO, to recognize the project structure from tests.(Using Test Runners).

## Environment used to run unit testing on target

```ini
[env:msp430_unit_test]
platform = timsp430
board = lpmsp430fr4133
...
```

## Environment used to run the unit testing on deskop native

```ini
env:native]
platform = native
src_filter = +<*> -<.git/> -<.svn/>
...
```
