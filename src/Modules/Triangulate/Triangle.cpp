// Copyright University of Lyon, 2012 - 2017
// Distributed under the GNU Lesser General Public License Version 2.1 (LGPLv2)
// (Refer to accompanying file LICENSE.md or copy at
//  https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html )

#include "Triangle.hpp"
#include "../../CityModel/Vecs.hpp" 
#include "tile.hpp"

//Triangle

Triangle::Triangle(TVec3d a, TVec3d b, TVec3d c)
{
    this->a = a;
    this->b = b;
    this->c = c;
    objectType = citygml::CityObjectsType::COT_All;
    subObjectType = citygml::CityObjectsType::COT_All;
}

TVec3d Triangle::GetNormal()
{
    TVec3d normal = (b - a).cross(c - a);
    return normal / normal.length();
}


//TriangleList

TriangleList::TriangleList(std::vector<Triangle*> triangles)
{
    this->triangles = triangles;
}

TriangleList::~TriangleList()
{
    for(unsigned int i = 0 ; i < triangles.size() ; ++i)
        delete triangles[i];
}

TriangleList* BuildListTriangle(const citygml::CityModel* cityModel) {

    std::vector<Triangle*> triangles;
	for (citygml::CityObject* obj : cityModel->getCityObjectsRoots()) //For each city object
    {
		if (obj->getType() == citygml::COT_Building) //We only take building or terrain
		{
		    for (citygml::CityObject* object : obj->getChildren())//On parcourt les objets (Wall, Roof, ...) du batiment
		        for (citygml::Geometry* Geometry : object->getGeometries()) //pour chaque geometrie
		            for (citygml::Polygon* PolygonCityGML : Geometry->getPolygons()) //Pour chaque polygone
		            {
                        const std::vector<TVec3d>& vert = PolygonCityGML->getVertices();
                        //const std::vector<unsigned int>& ind = (const std::vector<unsigned int>)vert.size();
                        const std::vector<unsigned int>& ind = PolygonCityGML->getIndices();

                        //std::cout <<ind.size() << std::endl;
						
                        for (unsigned int i = 0; i < ind.size() / 3; i++)//Push all triangle of the polygon in our list
                        {
                            TVec3d a = vert[ind[i * 3 + 0]];
                            TVec3d b = vert[ind[i * 3 + 1]];
                            TVec3d c = vert[ind[i * 3 + 2]];
                            Triangle* t = new Triangle(a, b, c);
		
                            t->subObjectType = object->getType();
                            t->objectType = obj->getType();
                            t->objectId = obj->getId();
                            t->polygonId = PolygonCityGML->getId();

                            triangles.push_back(t);
                        }
                    }
        } 
        else if ((obj->getType() == citygml::COT_SolitaryVegetationObject) || (obj->getType() == citygml::COT_TINRelief) ||(obj->getType() == citygml::COT_WaterBody))
        {
            for (citygml::Geometry* Geometry : obj->getGeometries()) //pour chaque geometrie
                for (citygml::Polygon* PolygonCityGML : Geometry->getPolygons()) //Pour chaque polygone
                {
                    //Get triangle list
                    const std::vector<TVec3d>& vert = PolygonCityGML->getVertices();
                    const std::vector<unsigned int>& ind = PolygonCityGML->getIndices();

                    for (unsigned int i = 0; i < ind.size() / 3; i++)//Push all triangle of the polygon in our list
                    {
                        TVec3d a = vert[ind[i * 3 + 0]];
                        TVec3d b = vert[ind[i * 3 + 1]];
                        TVec3d c = vert[ind[i * 3 + 2]];

                        Triangle* t = new Triangle(a, b, c);
                        t->objectType = obj->getType();
                        t->objectId = obj->getId();
                        t->polygonId = PolygonCityGML->getId();

                        triangles.push_back(t);
                    }
                }
        }
    }
    return new TriangleList(triangles);
}

TriangleList* BuildListTriangleTile(std::string& gmlFilename)
{
    std::vector<Triangle*> triangles;

    vcity::Tile* tile = new vcity::Tile(gmlFilename);

    citygml::CityModel* model = tile->getCityModel();

    for (citygml::CityObject* obj : model->getCityObjectsRoots()) //For each city object
    {

        if (obj->getType() == citygml::COT_Building) //We only take building or terrain
        {
            for (citygml::CityObject* object : obj->getChildren())//On parcourt les objets (Wall, Roof, ...) du batiment
                for (citygml::Geometry* Geometry : object->getGeometries()) //pour chaque geometrie
                    for (citygml::Polygon* PolygonCityGML : Geometry->getPolygons()) //Pour chaque polygone
                    {
                        //Get triangle list
                        const std::vector<TVec3d>& vert = PolygonCityGML->getVertices();
                        const std::vector<unsigned int>& ind = PolygonCityGML->getIndices();

                        for (unsigned int i = 0; i < ind.size() / 3; i++)//Push all triangle of the polygon in our list
                        {
                            TVec3d a = vert[ind[i * 3 + 0]];
                            TVec3d b = vert[ind[i * 3 + 1]];
                            TVec3d c = vert[ind[i * 3 + 2]];

                            // If all vertices of current triangle are below given zMin

                            Triangle* t = new Triangle(a, b, c);
                            t->subObjectType = object->getType();
                            t->objectType = obj->getType();
                            t->objectId = obj->getId();
                            t->polygonId = PolygonCityGML->getId();
                            t->tileFile = gmlFilename;

                            triangles.push_back(t);
                        }
                    }
        }
        // #CityObjectType
        // We check if the current cityobject is the same type of the wanted type of cityobject given in parameter
        // Exemple : (obj->getType() == citygml::COT_<MyType> && objectType == citygml::COT_<MyType>
        else if ((obj->getType() == citygml::COT_SolitaryVegetationObject) || (obj->getType() == citygml::COT_TINRelief) || (obj->getType() == citygml::COT_WaterBody))
        {
            for (citygml::Geometry* Geometry : obj->getGeometries()) //pour chaque geometrie
                for (citygml::Polygon* PolygonCityGML : Geometry->getPolygons()) //Pour chaque polygone
                {
                    //Get triangle list
                    const std::vector<TVec3d>& vert = PolygonCityGML->getVertices();
                    const std::vector<unsigned int>& ind = PolygonCityGML->getIndices();

                    for (unsigned int i = 0; i < ind.size() / 3; i++)//Push all triangle of the polygon in our list
                    {
                        TVec3d a = vert[ind[i * 3 + 0]];
                        TVec3d b = vert[ind[i * 3 + 1]];
                        TVec3d c = vert[ind[i * 3 + 2]];

                        // If all vertices of current triangle are below given zMin

                        Triangle* t = new Triangle(a, b, c);
                        t->objectType = obj->getType();
                        t->objectId = obj->getId();
                        t->polygonId = PolygonCityGML->getId();
                        t->tileFile = gmlFilename;

                        triangles.push_back(t);
                    }
                }
        }
    }

    delete tile;
    return new TriangleList(triangles);
}




