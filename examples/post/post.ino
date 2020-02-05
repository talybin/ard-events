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

