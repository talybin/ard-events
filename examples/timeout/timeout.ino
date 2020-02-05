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

