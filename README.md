# Installation

## Step 1 - Cloner le dépôt

```bash
git clone https://github.com/VCityTeam/DA-POM-Legonizer.git
```

## Step 2 - Configuration du projet

### Windows

* La bibliothèque [LibXML2](http://www.xmlsoft.org/index.html) est fournie dans le dossier [lib/libxml2-2.9.3](./lib/libxml2-2.9.3).
* La bibliothèque [OSG](http://www.openscenegraph.org/) est fournie dans le dossier [lib/osg](./lib/osg).
* La bibliothèque [GDAL](https://gdal.org/) est fournie dans le dossier [lib/gdal-2.0.2](./lib/gdal-2.0.2).

Pour résoudre les directives d'includes comme par exemple : `#include <libxml/xxx.h>`, il faut indiquer à votre IDE le chemin vers `./lib/libxml2-2.9.3/include/libxml2/` ainsi que le chemin vers les `.lib` : `./lib/libxml2-2.9.3/lib/`.

Il ne reste plus qu'à indiquer à votre IDE les dépendances supplémentaires :
```
libxml2.lib
glu32.lib
osg.lib
gdal_i.lib
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
      * `./lib/gdal-2.0.2/include/`
      * `./lib/osg/include/`
    * Dans "Répertoires de bibliothèques", rajoutez les chemins ***absolu*** vers ces dossiers :
      * `./lib/libxml2-2.9.3/lib/`
      * `./lib/gdal-2.0.2/lib/`
      * `./lib/osg/lib/`
  * Sous "Éditeurs de liens", sélectionnez "entrée"
    * Dans "Dépendances supplémentaires", rajoutez `libxml2.lib`, `glu32.lib` et `osg.lib`.
* Pour que l'executable ait accès aux `.dll`, rajoutez dans la variable d'environnement `Path` les chemins ***absolu*** vers ces dossiers :
  * `./lib/libxml2-2.9.3/bin/`
  * `./lib/gdal-2.0.2/bin/`
  * `./lib/osg/bin/`
* Pour passer des arguments en ligne de commande dans Visual Studio :
  * Click droit sur le nom du projet > Propriétés
  * Dans l'onglet "Débogage" > "Arguments de la commande" : mettre vos arguments (ex: emplacement de fichier .gml) en séparant les arguments par des espaces
* Si jamais vous avez une erreur de redefinition de type : `Error 13 error C2086: 'int APIENTRY' : redefinition C:\Program Files\Microsoft Visual Studio 8\VC\PlatformSDK\include\GL\gl.h 1153`. Ajouté dans la page de propriétés du projet à l'onglet "C/C++" > "Préprocesseur" > "Définitions de préprocesseur" : `WIN32`.
### Linux

Si vous n'avez pas [LibXML2](http://www.xmlsoft.org/index.html) d'installé : (sur Ubuntu)

```bash
sudo apt install libxml2-dev
```

Le répertoire d'include de la bibliothèque sera probablement : `/usr/include/libxml2`.

Ensuite, vous pouvez ouvrir le projet dans votre IDE favori mais la configuration des directives d'include, arguments de la ligne de commande, etc sera spécifique à votre IDE.

# Modules

## Parser 

## Triangulate
### Objectif
Le but de ce module est de créer une liste de triangle à partir d'un fichier .gml ([Geography Markup Language](https://fr.wikipedia.org/wiki/Geography_Markup_Language)) qui doit être parsé soit par le module parser soit par la fonction `TileTriangleList`. Cette liste nous sera utile par la suite pour le lancer de rayon.
### Fonctionnement 
Une fois le fichier parsé nous obtenons un objet `CityModel`. Cet objet nous allons le parcourir jusqu’au polygone comme vous pouvez le voir ci-dessous. À partir du `
Polygon` nous allons utiliser les sommets (`vertices`) ainsi que les indices de sommets pour construire nos triangles afin de les ajouter notre liste de triangle.
### Fonctions
| Nom | Paramètre | Commentaire |
| --- | --- | --- |
| initTriangleList | CityModel | Créer notre liste de triangle. |
| TileTriangleList | string GMLFile | Créer notre liste de triangle. |
| printBaseTriangleList | ListTriangle | Créer un .obj afin de visualiser notre liste de triangle. |
| get[X/Y/Z][Max/Min] |  | Retourne la valeur maximale et minimale sur l’axe X, Y, Z d’une liste de triangle. |
### Screnshots

## Voxelizer

# Utilisation
### Exécution
#### Triangulate
```sh
cd DA-POM-Legonizer/x64/Debug
./<executable> [MYFILE.gml] --triangulate
```
#### Voxelizer
```sh
cd DA-POM/x64/Debug
./POM-Project.exe [MYFILE.gml] --voxelizer[OPTIONS] 
```

Exemple : 
``` ./data/citygml/99_MAIRIE_VAULX_EN_VELIN.gml --voxelizer 100 100 -1 1 1 ```

| Options | optionnel | type | par défaut | Commande |
| --- | --- | --- | --- | --- |
| Nombre de lancés de rayons de X | oui | int | 100 | mapSizeX |
| Nombre de lancés de rayons de Y | oui | int | 100 | mapSizeY |
| Nombre de découpage en hauteur | oui | int | 1 | horizontalStep |
| Mode de remaillage | oui | int | 1 | gridmode|
| Matériaux différents pour le sol et les bâtiments | oui | bool | 1 | material |

