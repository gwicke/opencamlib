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

#ifndef BBOX_H
#define BBOX_H

#include "point.hpp"

#include <cassert>

namespace ocl
{

class Triangle;

/// axis-aligned bounding-box
class Bbox {
    public:
        /// default constructor
        Bbox();
        /// explicit constructor
        Bbox(double b1, double b2, double b3, double b4, double b5, double b6);
        virtual ~Bbox() {};


        // access bounding box values as a vector:
        //  0    1    2    3    4    5
        // [minx maxx miny maxy minz maxz]
        inline double operator[](const unsigned int idx) const{
            switch(idx) {
                case 0:
                    return minpt.x;
                    break;
                case 1:
                    return maxpt.x;
                    break;
                case 2:
                    return minpt.y;
                    break;
                case 3:
                    return maxpt.y;
                    break;
                case 4:
                    return minpt.z;
                    break;
                case 5:
                    return maxpt.z;
                    break;
                default:
                    break;
            }
            assert(0);
            return -1;
        }

        /// return true if Point p is inside this Bbox
        bool isInside(Point& p) const;

        /// return true if *this overlaps Bbox b
        bool overlaps(const Bbox& other) const;

        /// reset the Bbox (sets initialized=false)
        void clear();

        /// Add a Point to the Bbox.
        /// This enlarges the Bbox so that p is contained within it.
        inline void addPoint(const Point& p) {
            if (!initialized) {
                maxpt = p;
                minpt = p;
                initialized = true;
            } else {
                if (p.x > maxpt.x)
                    maxpt.x = p.x;
                if (p.x < minpt.x)
                    minpt.x = p.x;

                if (p.y > maxpt.y)
                    maxpt.y = p.y;
                if (p.y < minpt.y)
                    minpt.y = p.y;

                if (p.z > maxpt.z)
                    maxpt.z = p.z;
                if (p.z < minpt.z)
                    minpt.z = p.z;
            }
        }

        /// Add each vertex of a Triangle to the Bbox.
        /// This enlarges the Bbox so that the Triangle is contained within it.
        /// Calls addPoint() for each vertex of the Triangle.
        void addTriangle(const Triangle& t);

        friend std::ostream &operator<<(std::ostream& stream, const Bbox b);

//DATA
        /// the maximum point
        Point maxpt;
        /// the minimum point
        Point minpt;
    private:
        /// false until one Point or one Triangle has been added
        bool initialized;
};

} // end namespace
#endif
// end file bbox.h
