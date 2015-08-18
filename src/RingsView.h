#include <pebble.h>
#ifndef RingsHeader 
#define RingsHeader

extern int Secondes;
extern int Minutes;
extern int Hours;

// Called Function for Calculating Ring Center  ...
GPoint getRingCenter(float Angle, uint16_t Radius, GPoint ScreenCenter);

// Called Function for rendering One ring ...
void drawRing(Layer *SelectedLayer, GContext* GraphicContex, int Value, int Radius, int CenterRadius, GPoint Center, GColor Colors[]);

// Called Function for rendering screen
void drawRings(Layer *SelectedLayer, GContext* GraphicContext);

#endif
