// Copyright University of Lyon, 2012 - 2017
// Distributed under the GNU Lesser General Public License Version 2.1 (LGPLv2)
// (Refer to accompanying file LICENSE.md or copy at
//  https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html )

#ifndef __RAY_HPP__
#define __RAY_HPP__


#include "../../../../CityModel/Vecs.hpp"
#include "../../filters_export.h"

struct Hit;
struct RayCollection;
struct ViewPoint;
struct Triangle;

/**
*	@brief A simple ray
*/
struct Ray
{
    /**
    *	@brief Build a new ray
    *	@param ori Origin of the ray
    *	@param dir Direction of the ray
    *   @param Id oh the ray
    */
    Ray(TVec3d ori = TVec3d(0.0,0.0,0.0),TVec3d dir = TVec3d(1.0,1.0,1.0), int id = -1);

    /**
    *	@brief To know if the ray instersect a given triangle
    *	@param triangle The triangle to intersect
    *	@param hit Information about the intersection will be stored in it
    *	@return True if this ray intersect with the triangle, false otherwise
    */
    bool Intersect(Triangle* triangle, Hit* hit = nullptr);



    static float DotCross(TVec3d v0, TVec3d v1, TVec3d v2);
    static TVec3d Normalized(TVec3d vec);

    int id;///< Id of the ray
	TVec2d fragCoord;///< Fragment coordinate of the ray
	TVec3d ori;///< Origin of the ray
	TVec3d dir;///< Direction of the ray
	TVec3d inv_dir;///< inv Direction of the ray
	int sign[3];
};


#endif
