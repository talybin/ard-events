// Example usage for ard-events library by Vladimir Talybin.

#include "ard-events.h"

// Initialize objects from the lib
Ardevents ardevents;

void setup() {
    // Call functions on initialized library objects that require hardware
    ardevents.begin();
}

void loop() {
    // Use the library's initialized objects and functions
    ardevents.process();
}
