
// Copyright University of Lyon, 2012 - 2017
// Distributed under the GNU Lesser General Public License Version 2.1 (LGPLv2)
// (Refer to accompanying file LICENSE.md or copy at
//  https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html )

#include "tile.hpp"
#include "../XMLParser/XMLParser.hpp"
#include "../Module.hpp"
#include "../../CityGMLTool/CityGMLTool.hpp"

namespace vcity
{
    ////////////////////////////////////////////////////////////////////////////////
    Tile::Tile()
        : m_root(nullptr)
    {
    }
    ////////////////////////////////////////////////////////////////////////////////
    Tile::Tile(const std::string& filepath)
        : m_root(nullptr)
    {
        vcity::Tile::loadT(filepath);
        //computeEnvelope();
    }
    ////////////////////////////////////////////////////////////////////////////////
    Tile::~Tile()
    {
        delete m_root;
    }
    ////////////////////////////////////////////////////////////////////////////////
    /*Tile::Tile(const TVec3d& pMin, const TVec3d& pMax)
        : m_envelope(pMin, pMax)
    {
    }*/
    ////////////////////////////////////////////////////////////////////////////////
    citygml::Envelope& Tile::getEnvelope()
    {
        //return m_envelope;
        return m_root->getEnvelope();
    }
    ////////////////////////////////////////////////////////////////////////////////
    const citygml::Envelope& Tile::getEnvelope() const
    {
        //return m_envelope;
        return m_root->getEnvelope();
    }
    ////////////////////////////////////////////////////////////////////////////////
    void Tile::computeEnvelope()
    {
        m_root->computeEnvelope();
        //m_envelope.merge(m_root->getEnvelope());
    }
    ////////////////////////////////////////////////////////////////////////////////
    /*void loadRec(citygml::CityObject* node, ReaderOsgCityGML& reader)
    {
        //FIXME: remove this method since all its code is commented out

        //node->computeEnvelope();
        /*osg::ref_ptr<osg::Group> grp = reader.createCityObject(node);
        if(node->getType() == citygml::COT_Building)
        {
            int yearOfConstruction = 0;
            int yearOfDemolition = 0;
            if(node->getAttribute("yearOfConstruction") != "")
            {
                std::istringstream(node->getAttribute("yearOfConstruction")) >> yearOfConstruction;
                grp->setUserValue("yearOfConstruction", yearOfConstruction);
            }
            if(node->getAttribute("yearOfDemolition") != "")
            {
                std::istringstream(node->getAttribute("yearOfDemolition")) >> yearOfDemolition;
                grp->setUserValue("yearOfDemolition", yearOfDemolition);
            }*/




            /*grp->getUserValue("yearOfConstruction", yearOfConstruction);
            grp->getUserValue("yearOfDemolition", yearOfDemolition);*/

            /*std::cout << "yearOfConstruction : " << yearOfConstruction << std::endl;
            std::cout << "yearOfDemolition : " << yearOfDemolition << std::endl;
            std::cout << "yearOfConstruction2 : " << node->getAttribute("yearOfConstruct
My Library
ion") << std::endl;
            std::cout << "yearOfDemolition2 : " << node->getAttribute("yearOfDemolition") << std::endl;*/
            //}

            //node->setOsgNode(grp);

            /*citygml::CityObjects& cityObjects = node->getChildren();
            citygml::CityObjects::iterator it = cityObjects.begin();
            for( ; it != cityObjects.end(); ++it)
            {
                loadRec(*it, reader);
            }
    }*/
    ////////////////////////////////////////////////////////////////////////////////
   void Tile::loadT(const std::string& filepath)
    {
        XMLParser* xmlparser = new XMLParser("xmlparser");
        citygml::ParserParams params;
        delete m_root;
        m_root = xmlparser->load(filepath, params);
        m_root->computeEnvelope();
        //std::cout << citygmlmodel->getEnvelope() << std::endl;

        m_citygmlFilePath = filepath;
  
        // set tile name
        static int id = 0;
        std::stringstream ss;
        std::string filename = filepath.substr(filepath.find_last_of("/\\") + 1);
        ss << id++ << "_" << filename;
        m_name = ss.str();
    }
    ////////////////////////////////////////////////////////////////////////////////
    citygml::CityModel* Tile::getCityModel()
    {
        return m_root;
    }
    ////////////////////////////////////////////////////////////////////////////////
    const citygml::CityModel* Tile::getCityModel() const
    {
        return m_root;
    }
    ////////////////////////////////////////////////////////////////////////////////
    const std::string& Tile::getName() const
    {
        return m_name;
    }
    ////////////////////////////////////////////////////////////////////////////////
    void Tile::setName(const std::string& name)
    {
        m_name = name;
    }
    ////////////////////////////////////////////////////////////////////////////////
    /*osg::ref_ptr<osg::Node> Tile::getOsgRoot()
    {
        return m_rootOsg;
    }*/
    ////////////////////////////////////////////////////////////////////////////////
    citygml::CityObject* getNodeRec(citygml::CityObject* node, const std::string& name)
    {
        citygml::CityObject* res = nullptr;
        if (node->getId() == name)
        {
            //std::cout << "found node " << name << std::endl;
            return node;
        }

        citygml::CityObjects& cityObjects = node->getChildren();
        citygml::CityObjects::iterator it = cityObjects.begin();
        for (; it != cityObjects.end(); ++it)
        {
            res = getNodeRec(*it, name);
            if (res) break;
        }

        return res;
    }
    ////////////////////////////////////////////////////////////////////////////////
    // FIXME: Remove this method
    /*citygml::CityObject* Tile::findNode(const std::string& name)
    {
        citygml::CityObject* res = NULL;
        citygml::CityObjects& cityObjects = m_root->getCityObjectsRoots();
        citygml::CityObjects::iterator it = cityObjects.begin();
        for( ; it != cityObjects.end(); ++it)
        {
            res = findNodeRec(*it, name);
            if(res) break;
        }
        return res;
    }*/
    ////////////////////////////////////////////////////////////////////////////////
    void Tile::deleteNode(const std::string& /*name*/)
    {

    }
    ////////////////////////////////////////////////////////////////////////////////
    void Tile::insertNode(citygml::CityObject* /*node*/)
    {

    }
    ////////////////////////////////////////////////////////////////////////////////
    void Tile::replaceNode(const std::string& /*name*/, citygml::CityObject* /*node*/)
    {

    }
    ////////////////////////////////////////////////////////////////////////////////
    citygml::CityObject* Tile::getNode(const URI& uri, bool inPickingMode)
    {
        return m_root->getNode(uri, inPickingMode);
        // FIXME: Remove the following commented out code
        /*std::string name = uri.getLastNode();
        citygml::CityObject* res = nullptr;
        citygml::CityObjects& cityObjects = m_root->getCityObjectsRoots();
        citygml::CityObjects::iterator it = cityObjects.begin();
        for( ; it != cityObjects.end(); ++it)
        {
            res = getNodeRec(*it, name);
            if(res) break;
        }
        return res;*/
    }
    ////////////////////////////////////////////////////////////////////////////////
    const std::string& Tile::getCityGMLfilePath() const
    {
        return m_citygmlFilePath;
    }
    ////////////////////////////////////////////////////////////////////////////////
} // namespace vcity
////////////////////////////////////////////////////////////////////////////////
