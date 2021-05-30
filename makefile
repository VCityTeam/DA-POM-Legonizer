Legonizer: src/main.cpp src/Modules/Triangulate/* src/Modules/* src/Modules/Voxelizer/* src/Modules/Heightmap/* src/Modules/XMLParser/* src/CLI/*  src/CityModel/* src/CityGMLTool/*
	g++ src/main.cpp \
		src/Modules/Triangulate/*.cpp \
		src/Modules/Module.cpp \
		src/Modules/XMLParser/*.cpp \
		src/Modules/Voxelizer/*.cpp \
		src/Modules/Heightmap/*.cpp \
		src/Modules/Heightmap/filters/raytracing/*.cpp \
		src/CLI/CLI.cpp \
		src/CityModel/*.cpp \
		src/CityModel/ADE/*.cpp \
		src/CityModel/ADE/document/*.cpp \
		src/CityModel/ADE/temporal/*.cpp \
		src/CityGMLTool/*.cpp \
	-o Legonizer \
		-I src/Modules/Triangulate \
		-I src/Modules \
		-I src/Modules/XMLParser \
		-I src/Modules/Voxelizer \
		-I src/Modules/Heightmap \
		-I src/CLI \
		-I src/CityModel \
		-I src/CityGMLTool \
		-lxml2 -I/usr/include/libxml2 \
		-lgdal -I/usr/include/gdal \
        -lGL -lGLU -lGLEW -lpthread
