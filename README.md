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

## Call function once after specified time

Example:

```cpp
#include "ard-events.h"

void test() {
    // This will be called once 5 seconds after boot
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

## Documentation

TODO: Describe `Ardevents`

## Contributing

Here's how you can make changes to this library and eventually contribute those changes back.

To get started, [clone the library from GitHub to your local machine](https://help.github.com/articles/cloning-a-repository/).

Change the name of the library in `library.properties` to something different. You can add your name at then end.

Modify the sources in <src> and <examples> with the new behavior.

To compile an example, use `particle compile examples/usage` command in [Particle CLI](https://docs.particle.io/guide/tools-and-features/cli#update-your-device-remotely) or use our [Desktop IDE](https://docs.particle.io/guide/tools-and-features/dev/#compiling-code).

After your changes are done you can upload them with `particle library upload` or `Upload` command in the IDE. This will create a private (only visible by you) library that you can use in other projects. Do `particle library add ard-events_myname` to add the library to a project on your machine or add the ard-events_myname library to a project on the Web IDE or Desktop IDE.

At this point, you can create a [GitHub pull request](https://help.github.com/articles/about-pull-requests/) with your changes to the original library. 

If you wish to make your library public, use `particle library publish` or `Publish` command.

## LICENSE
Copyright 2020 Vladimir Talybin

Licensed under the <insert your choice of license here> license
