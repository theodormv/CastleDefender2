#include "box.h"

Box::Box(float w, float h, float d, Vector3f position) : BoxCore(w, h, d) { center = new Vector3f(position); }

Box::Box(const Box& other) {}

Box::~Box() { delete center; }