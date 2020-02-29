// You do not need to change this file.
// The display module provides graphics for the sketch program.

// A display structure needs to be created by calling newDisplay, and then
// needs to be passed to each sketching function.
struct display;
typedef struct display display;

// Create a display object representing a plain white window of a given size.
display *newDisplay(char *title, int width, int height);

// Make recent changes appear on screen.
void show(display *d);

// Pause for the given number of milliseconds.
void pause(display *d, int ms);

// Clear the display to white.
void clear(display *d);

// Wait for a key press.
char key(display *d);

// Hold the display for a few seconds, then shut down.
void end(display *d);

//color the cell accordingly (dead or alive)
void colorCell( display *d, int x, int y, int color);
