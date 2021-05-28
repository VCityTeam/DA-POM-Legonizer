# Legonizer

Bonjour,  bienvenue sur le projet Legonizer. Ce projet a pour but de recuperer des données géographiques de les traitées ( Trianguler et Voxelizer ) pour obtenir une représentation en légo des données. Dans ce projet il y a deux modules principaux, la triangulisation et la voxelisation d'un mesh.

*******
### Table des matières  
* [Installation](#installation)
* [Modules](#modules)
* [Debug](#debug)
* [Triangulate](#triangulate)
* [Heightmap](#heightmap)
* [Voxelizer](#voxelizer)

*******


# Installation

## Step 1 - Cloner le dépôt

```bash
git clone https://github.com/VCityTeam/DA-POM-Legonizer.git
```

## Step 2 - Configuration du projet

### Windows

* La bibliothèque [LibXML2](http://www.xmlsoft.org/index.html) est fournie dans le dossier [lib/libxml2-2.9.3](./lib/libxml2-2.9.3).

Pour résoudre les directives d'includes comme par exemple : `#include <libxml/xxx.h>`, il faut indiquer à votre IDE le chemin vers `./lib/libxml2-2.9.3/include/libxml2/` ainsi que le chemin vers les `.lib` : `./lib/libxml2-2.9.3/lib/`.

Il ne reste plus qu'à indiquer à votre IDE les dépendances supplémentaires :
```
libxml2.lib
glu32.lib
```

#### Avec Visual Studio (testé avec vs2017 & vs2019)

Pour démarrer rapidement avec Visual Studio :
* Ouvrir Visual Studio
* (Vous pouvez vous aider de la page [suivante](https://docs.microsoft.com/fr-fr/cpp/build/how-to-create-a-cpp-project-from-existing-code?view=msvc-160))
* Fichier > Nouveau > Projet à partir de code existant
  * Suivez les étapes de l'assistant
  * Dans "Emplacement du fichier projet", mettre le dossier cloné précédemment
  * "Type de projet" : "Projet d'application console"
  * Configuration Debug : rien à rajouter
  * Configuration Release : rien à rajouter
* Sélectionnez la configuration `x64`
* Ensuite, Click droit sur le nom du projet > Propriétés
  * Sélectionnez "Répertoires VC++"
    * Dans "Répertoires Include", rajoutez les chemins ***absolu*** vers ces dossiers :
      * `./lib/libxml2-2.9.3/include/libxml2/`
    * Dans "Répertoires de bibliothèques", rajoutez les chemins ***absolu*** vers ces dossiers :
      * `./lib/libxml2-2.9.3/lib/`
  * Sous "Éditeurs de liens", sélectionnez "entrée"
    * Dans "Dépendances supplémentaires", rajoutez `libxml2.lib`, `glu32.lib`.
* Pour que l'executable ait accès aux `.dll`, rajoutez dans la variable d'environnement `Path` les chemins ***absolu*** vers ces dossiers :
  * `./lib/libxml2-2.9.3/bin/`
* Pour passer des arguments en ligne de commande dans Visual Studio :
  * Click droit sur le nom du projet > Propriétés
  * Dans l'onglet "Débogage" > "Arguments de la commande" : mettre vos arguments (ex: emplacement de fichier .gml) en séparant les arguments par des espaces
* Si jamais vous avez une erreur de redefinition de type : `Error 13 error C2086: 'int APIENTRY' : redefinition C:\Program Files\Microsoft Visual Studio 8\VC\PlatformSDK\include\GL\gl.h 1153`. Ajouté dans la page de propriétés du projet à l'onglet "C/C++" > "Préprocesseur" > "Définitions de préprocesseur" : `WIN32`.
### Linux

Si vous n'avez pas [LibXML2](http://www.xmlsoft.org/index.html) d'installé (sur Ubuntu) : 

```bash
sudo apt install libxml2-dev
```

Le répertoire d'include de la bibliothèque sera probablement : `/usr/include/libxml2`.

```bash
sudo apt-get install libglew-dev
```

Puis ```make```



*******

# Modules

* ## Debug
  * ### Execution
    ```sh
    cd DA-POM-Legonizer/x64/Debug
    ./<executable> [MYFILE.gml] --debug [Modulename] [parametres]
    ```

  * ### Objectif
    Permet d'afficher des informations en plus dans les modules Triangulate et Voxelizer

* ## [Triangulate](https://github.com/VCityTeam/DA-POM-Legonizer/wiki/Triangulate)
  * ### Exécution
    ```sh
    cd DA-POM-Legonizer/x64/Debug
    ./<executable> [MYFILE.gml] --triangulate
    ```
  * ### Objectif
    Le but de ce module est de créer une liste de triangle à partir d'un fichier .gml ([Geography Markup Language](https://fr.wikipedia.org/wiki/Geography_Markup_Language)). Ce fichier est parsé dans la fonction `initTriangleList`. Cette liste nous sera utile par la suite pour le lancer de rayon.
  * ### Fonctionnement 
    Une fois le fichier parsé nous obtenons un objet `CityModel`. Cet objet nous allons le parcourir jusqu’au polygone. À partir du `Polygon` nous allons utiliser les sommets (`vertices`) ainsi que les indices de sommets pour construire nos triangles afin de les ajouter notre liste de triangle.       


* ## [Heightmap](https://github.com/VCityTeam/DA-POM-Legonizer/wiki/Heightmap)
  * ### Exécution
    ```sh
    cd DA-POM-Legonizer/x64/Debug
    ./<executable> [MYFILE.gml] --heightmap[OPTIONS] 
    ```
    #### Exemples : 
      * ``` ./data/citygml/99_MAIRIE_VAULX_EN_VELIN.gml --heightmap 100 100 50 ``` 
      * ``` ./data/citygml/99_MAIRIE_VAULX_EN_VELIN.gml --heightmap 100 100 50 output/result.csv ```
  
  * ### Objectifs
    Transformer un fichier GML en une heightmap
    
  * ### Paramètres
  
    | Options | optionnel | type | par défaut | Commande |
    | --- | --- | --- | --- | --- |
    | Nombre de lancés de rayons de X | non | int | 100 | mapSizeX |
    | Nombre de lancés de rayons de Y | non | int | 100 | mapSizeY |
    | Nombre de découpage en hauteur | non | int | 50 | horizontalStep |
    | Nom de fichier en sortie de la heigtmap (.csv) | oui | std::string | output/heightmap.csv| fileNameCSV
    
* ## [Voxelizer](https://github.com/VCityTeam/DA-POM-Legonizer/wiki/Voxelizer)
  * ### Exécution
    ```sh
    cd DA-POM-Legonizer/x64/Debug
    ./<executable> [MYFILE.gml] --voxelizer[OPTIONS] 
    ```
    #### Exemples : 
      * ``` ./data/citygml/99_MAIRIE_VAULX_EN_VELIN.gml --voxelizer 100 100 50 1 1 0``` 
      * ``` ./data/citygml/99_MAIRIE_VAULX_EN_VELIN.gml --voxelizer 100 100 50 1 1 0 output/result ```
      * ``` ./data/citygml/99_MAIRIE_VAULX_EN_VELIN.gml --voxelizer 100 100 50 1 1 0 output/result output/heightmap.csv ```
  
  * ### Objectifs
    Transformer un fichier GML en une heightmap puis en un maillage voxélisé en .obj
    
  * ### Paramètres
  
    | Options | optionnel | type | par défaut | Commande |
    | --- | --- | --- | --- | --- |
    | Nombre de lancés de rayons de X | non | int | 100 | mapSizeX |
    | Nombre de lancés de rayons de Y | non | int | 100 | mapSizeY |
    | Nombre de découpage en hauteur | non | int | 50 | horizontalStep |
    | Mode de remaillage | non | int | 1 | gridmode|
    | Matériaux différents pour le sol et les bâtiments | non | bool | 1 | material |
    | Ecrit un obj pour chaque hauteur | non | bool | 1 | stepByStep |
    | Nom de fichier en sortie (.obj) | oui | std::string | output/result | outPutFileName
    | Nom de fichier en sortie de la heigtmap (.csv) | oui | std::string | output/heightmap.csv| fileNameCSV


###### Auteur : *Rémi Lhoste et Julian Sorrenti*.
