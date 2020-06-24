/*  $Id$
 *
 *  Copyright (c) 2010 Anders Wallin (anders.e.e.wallin "at" gmail.com).
 *
 *  This file is part of OpenCAMlib
 *  (see https://github.com/aewallin/opencamlib).
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <cassert>

#include "bbox.hpp"
#include "point.hpp"
#include "triangle.hpp"

namespace ocl
{

//************* axis-aligned Bounding-Box **************/

Bbox::Bbox() {
    minpt = Point(0,0,0);
    maxpt = Point(0,0,0);
    initialized = false;
}
//              minx       maxx        miny       maxy       minz       maxz
Bbox::Bbox(double b1, double b2, double b3, double b4, double b5, double b6) {
    minpt = Point(b1,b3,b5);
    maxpt = Point(b2,b4,b6);
    initialized = true;
}

void Bbox::clear() {
    initialized = false;
}

bool Bbox::isInside(Point& p) const {
    assert( initialized );
    if (p.x > maxpt.x)
        return false;
    else if (p.x < minpt.x)
        return false;
    else if (p.y > maxpt.y)
        return false;
    else if (p.y < minpt.y)
        return false;
    else if (p.z > maxpt.z)
        return false;
    else if (p.z < minpt.z)
        return false;
    else
        return true;
}

/// add each vertex of the Triangle
void Bbox::addTriangle(const Triangle &t) {
    addPoint( t.p[0] );
    addPoint( t.p[1] );
    addPoint( t.p[2] );
    return;
}

/// does this Bbox overlap with b?
bool Bbox::overlaps(const Bbox& b) const {
    if  ( (this->maxpt.x < b.minpt.x) || (this->minpt.x > b.maxpt.x) )
        return false;
    else if ( (this->maxpt.y < b.minpt.y) || (this->minpt.y > b.maxpt.y) )
        return false;
    else if ( (this->maxpt.z < b.minpt.z) || (this->minpt.z > b.maxpt.z) )
        return false;
    else
        return true;
}

std::ostream &operator<<(std::ostream &stream, const Bbox b) {
  stream << " Bbox \n";
  stream << " min= "<< b.minpt <<"\n";
  stream << " max= "<< b.maxpt <<"\n";
  return stream;
}

} // end namespace
// end of file volume.cpp
