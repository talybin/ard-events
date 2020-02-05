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

