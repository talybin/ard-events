# ARD-EVENTS

A Particle library for simple timer event processing. With this library you may hold execution of code until specified timeout or simply after calling method is complete (execute later).

## Get started

In order this library to work you will need to setup processing of events. Event processor go thru handlers in event queue and, if there something to do, invoke the handler. This is done by call to `ard::process_events()`. The best place to put processor is in `loop()` function.

```cpp
#include "ard-events.h"

void loop() {
    ard::process_events();
}
```

You can call processor at any time (and place) to execute current events. For example in loop that takes a long time to execute.

### Call function once after specified time

Example:

```cpp
#include "ard-events.h"

void test() {
    // This will be called once, 5 seconds after boot
}

void setup()
{
    // Call test() function after 5 seconds
    ard::set_timeout(5000, test);
    
    // ... or you can call inline function (lambda)
    ard::set_timeout(3500, [] {
        // This will be called after 3.5 seconds
    });
}

void loop() {
    ard::process_events();
}
```

### Call function every specified time

Like `ard::set_timeout` it supports both inline and non-inline functions.

```cpp
#include "ard-events.h"

void setup() {
    // Call lambda every 5 seconds
    ard::set_interval(5000, [] {
        // Do something
    });
}

void loop() {
    ard::process_events();
}
```

### Execute later

Run function later, on next call to `ard::process_events()`. Supports inline and non-inline functions.

```cpp
#include "ard-events.h"

void setup() {
    // Post execute
    ard::post([] {
        // This will be executed first enter in loop()
        // (first time processor is called)
    });
}

void loop() {
    ard::process_events();
}
```

## Documentation

Documentation can be generated with [Doxygen](http://doxygen.nl/). Doxyfile included.

## LICENSE

Licensed under the MIT license.

