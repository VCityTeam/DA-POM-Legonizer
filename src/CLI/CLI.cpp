#include "CLI.hpp"

CLI::CLI(int argc, char* argv[])
{
    this->_argc = argc;

    for (int i = 0 ; i < argc; i++)
    {
		std::string str(argv[i]);
		this->_argv.push_back(str);
		_cmdLine.append(argv[i]);
    }

	_citygmltool = new CityGMLTool();

	_cliParams.push_back(CLIParam("--help", "Prints usage."));
	_cliParams.push_back(CLIParam("--debug", "Turn on debug mode."));
<<<<<<< HEAD
	_cliParams.push_back(CLIParam("--triangulate", "Triangulate CityGML object")); 
	_cliParams.push_back(CLIParam("--voxelizer", "Voxelize a GML file", std::vector<bool>({ 1, 1, 1, 1, 1, 0})));
=======
	_cliParams.push_back(CLIParam("--triangulate", "Triangulate CityGML object"));
	_cliParams.push_back(CLIParam("--voxelizer", "Description", std::vector<bool>({ 1, 1, 1, 1, 1})));
>>>>>>> 57780e00953dcb4cc6213e82113705c844daf5e7

}

void CLI::run()
{
	// Print full command line
	for (int i = 0; i < _argc; i++)
	{
		std::cout << this->_argv.at(i) << " ";
	}
	std::cout << std::endl;

	parseCmdLine();
	processCmdLine();

	// Clean memory
	if (_citygmltool != nullptr)
		delete _citygmltool;
}

void CLI::parseCmdLine()
{
	// If no parameters : print usage
	if (this->_argc < 2)
	{
		outstream << "[ERROR]: No parameters found." << std::endl;
		usage();
	}

	// Check if there is a .gml file
	if (assertCityGMLFile())
	{
		// Check for CLI arguments
		for (int i = 0; i < _cliParams.size(); i++)
		{
			for (int j = 0; j < _argv.size(); j++)
			{
				if (_argv[j].size() == _cliParams[i]._name.size()
					&& _argv[j].compare(_argv[j].size() - _cliParams[i]._name.size(), _cliParams[i]._name.size(), _cliParams[i]._name) == 0)
				{
					_cliParams[i]._found = true;
					for (int k = 0; k < _cliParams[i]._argsRequirements.size(); k++)
					{
						j++;
						// If argument is true (REQUIRED)
						if (_cliParams[i]._argsRequirements[k])
						{
							if (j >= _argv.size())
							{
								outstream << "[ERROR]: Parsing arg: " << _cliParams[i]._name << " Argument REQUIRED not found. Exiting." << std::endl;
								usage();
							}
							else
							{
								_cliParams[i]._args.push_back(_argv[j]);
							}
						}
						// If argument is false (OPTIONAL)
						else
						{
							if (j < _argv.size())
							{
								_cliParams[i]._args.push_back(_argv[j]);
							}
						}
					}
				}
			}
		}
	}
	else
	{
		outstream << "[ERROR]: No CityGML file found. You may want to check the location of the file. Exiting." << std::endl;
		usage();
	}
}

void CLI::processCmdLine()
{
	// Process found arguments
	for (int i = 0; i < _cliParams.size(); i++)
	{
		if (_cliParams[i]._found)
		{
			std::string name = _cliParams[i]._name;
			if (name == "--help") {
				usage();
			}
			else if (name == "--debug") {
				_debugModule = true;

				std::cout << "Debug mode enabled" << std::endl;
			}
			else if (name == "--voxelizer") {
<<<<<<< HEAD
				std::string output;
				if (_cliParams[i]._args.size() == 6) {
					std::string toMatch = ".obj";
					if (_argv[1].size() >= toMatch.size() && _argv[1].compare(_argv[1].size() - toMatch.size(), toMatch.size(), toMatch) == 0)
					{
						this->_gmlFilename = this->_argv[6];
						std::cout << "Make sure your outPut nameFile end with '.obj'" << std::endl;
					}
=======
				if (_cliParams[i]._args.size() >= 5) {
					_citygmltool->voxelize(
						std::stoi(_cliParams[i]._args[0]),
						std::stoi(_cliParams[i]._args[1]),
						std::stoi(_cliParams[i]._args[2]),
						std::stoi(_cliParams[i]._args[3]),
						std::stoi(_cliParams[i]._args[4]),
						_gmlFilename);
				}
				else {
					std::cout << "Le nombre de parametre n'est pas correct" << std::endl;
>>>>>>> 57780e00953dcb4cc6213e82113705c844daf5e7
				}
				if(_debugModule)
					std::cout << "DEBUG MODE" << endl;
				_citygmltool->voxelize(
					std::stoi(_cliParams[i]._args[0]),
					std::stoi(_cliParams[i]._args[1]),
					std::stoi(_cliParams[i]._args[2]),
					std::stoi(_cliParams[i]._args[3]),
					std::stoi(_cliParams[i]._args[4]),
					_cliParams[i]._args[5],
					_debugModule);
			}
			else if (name == "--triangulate") {
				_citygmltool->triangulate(_gmlFilename);
			}
		}
	}
}

bool CLI::assertCityGMLFile()
{
	std::string toMatch = ".gml";
	if (_argv[1].size() >= toMatch.size() && _argv[1].compare(_argv[1].size() - toMatch.size(), toMatch.size(), toMatch) == 0)
	{
		this->_gmlFilename = this->_argv[1];

		return true;
	}



	return false;
}

void CLI::usage()
{
	std::cout << outstream.str() << std::endl << std::endl;

	std::cout << "Usage: " << std::endl;
	std::cout << "\t citygmltool <gitygmlfile> [options]" << std::endl;

	std::cout << "[options]: " << std::endl;

	for (int i = 0; i < _cliParams.size(); i++)
	{
		_cliParams[i].print();
	}

	exit(1);
}