// Copyright University of Lyon, 2012 - 2017
// Distributed under the GNU Lesser General Public License Version 2.1 (LGPLv2)
// (Refer to accompanying file LICENSE.md or copy at
//  https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html )

#ifndef __TRIANGLE_HPP__
#define __TRIANGLE_HPP__

#include "../../CityModel/CityGML.hpp"
//#include "libcitygml/citygml.hpp"
//#include "libcitygml/utils/tile.hpp"
//#include "citygmlutils_export.h"
#ifdef _MSC_VER
#pragma warning(disable: 4251) // VC++ DLL jejune complains on STL _Id member
#endif

/**
*	@brief A triangle created from a citygml polygon
*/
struct Triangle
{
    /**
    *	@brief Build a new triangle
    *	@param a First point of the triangle
    *	@param b Second point of the triangle
    *	@param c Third point of the triangle
    */
    Triangle(TVec3d a = TVec3d(0.0, 0.0, 0.0), TVec3d b = TVec3d(0.0, 0.0, 0.0), TVec3d c = TVec3d(0.0, 0.0, 0.0));

    TVec3d GetNormal();

    TVec3d a; ///< First point of the triangle
    TVec3d b; ///< Second point of the triangle
    TVec3d c; ///< Third point of the triangle

    citygml::CityObjectsType objectType;
    citygml::CityObjectsType subObjectType;
    std::string objectId;
    std::string polygonId;
    std::string tileFile;
};

/**
*	A list of triangle
*/
struct TriangleList
{
    /**
    *	@brief Build a new collection of triangle
    */
    TriangleList(std::vector<Triangle*> triangles = std::vector<Triangle*>());
    ~TriangleList();

    public : 

        int getSize() { return triangles.size(); };
        std::vector<Triangle*> triangles;///< Triangles of the list
};

/**
*	@brief Construit la liste de triangle a partir d'un CITYMODEL
*	@param CityModel obtenu en parsant notre fichier .gml
*	@return La liste de triangle 
*/
TriangleList* BuildListTriangle(const citygml::CityModel* cityModel);

/**
*	@brief Construit la liste de triangle a partir du fichier .gml
*	@param fichier .gml
*	@return La liste de triangle
*/
TriangleList* BuildListTriangleTile(std::string& gmlFilename);

#endif
