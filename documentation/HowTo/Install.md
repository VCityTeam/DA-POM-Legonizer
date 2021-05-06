# Installation

la bibliothèque `OSG (OpenScene Graph)` est seulement utilisé dans le module voxelizer.

## Step 1 - Cloner le dépôt

```bash
git clone https://github.com/VCityTeam/DA-POM.git
```

## Step 2 - Configuration du projet

### Windows

La bibliothèque [LibXML2](http://www.xmlsoft.org/index.html) est fournie dans le dossier [lib/](./lib). Pour résoudre les directives d'includes `#include <libxml/xxx.h>`, il faut indiquer à votre IDE le chemin vers `./lib/libxml2-2.9.3/include/libxml2/` ainsi que le chemin vers les `.lib` : `./lib/libxml2-2.9.3/lib/`.
La bibliothèque [OSG](http://www.openscenegraph.org/index.php/download-section/stable-releases/237-openscenegraph-3-6-5-release-download) doit être placé dans le dossier [lib/](./lib). Pour résoudre les directives d'includes `#include <osg/xxx.h>`, il faut indiquer à votre IDE le chemin vers `./lib/osg/include/osg/` ainsi que le chemin vers les `.lib` : `./lib/osg/lib/`.

Il ne reste plus qu'à indiquer à votre IDE les dépendances supplémentaires :
```
libxml2.lib
glu32.lib
```
Pour utiliser le moduler voxelizer, il faut placer la bibliothèque OSG, dans un nouveau répertoire `osg` tel qu'il existe un chemin `/lib/osg` 
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
    * Dans "Dépendances supplémentaires", rajoutez `libxml2.lib`, `osg.lib` et `glu32.lib`
* Pour que l'executable ait accès aux `.dll`, rajoutez dans la variable d'environnement `Path` les chemins ***absolu*** vers ces dossiers :
  * `./lib/libxml2-2.9.3/bin/`
  * `./lib/gdal-2.0.2/bin/`
  * `./lib/osg/bin/`
* Pour passer des arguments en ligne de commande dans Visual Studio :
  * Click droit sur le nom du projet > Propriétés
  * Dans l'onglet "Débogage" > "Arguments de la commande" : mettre vos arguments (ex: emplacement de fichier .gml) en séparant les arguments par des espaces

### Linux

Si vous n'avez pas [LibXML2](http://www.xmlsoft.org/index.html) d'installé : (sur Ubuntu)
Si vous n'avez pas [OSG](https://github.com/openscenegraph/OpenSceneGraph/tree/OpenSceneGraph-3.6.3) d'installé : (sur Ubuntu)

```bash
sudo apt install libxml2-dev
sudo add-apt-repository ppa:openmw/openmw
sudo apt update
sudo apt install openscenegraph-3.4
```

Les répertoires d'includes de la bibliothèque sont probablement dans : `/usr/include/libxml2` '/usr/include/osg/.


Ensuite, vous pouvez ouvrir le projet dans votre IDE favori mais la configuration des directives d'include, arguments de la ligne de commande, etc sera spécifique à votre IDE.

