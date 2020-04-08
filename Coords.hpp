#ifndef COORDS_HPP
#define COORDS_HPP

struct Coords {
  // Structure for coordinates
  Coords(double xin, double yin, double zin) : x(xin),y(yin),z(zin) {}
  Coords(double xin, double yin) : x(xin), y(yin), z(0.0) {}
  Coords() : x(0.0), y(0.0), z(0.0){}
  ~Coords(){}
  double x,y,z;
};

#endif
