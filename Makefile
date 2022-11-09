#---------------------------------------------------------
# File: Makefile.mk
# Date: septiembre 2022
# Author: César Borja y Marcos Garralaga - Informática Gráfica
# Coms: 
#---------------------------------------------------------

#---------------------------------------------------------
# macros
RM = /bin/rm -f  # para limpiar
CC = g++         # compilador
#---------------------------------------------------------
# opciones compilación y enlazado ("linkado")
CPPFLAGS = -I. -I${SRC} -I -O2 -std=c++11 -g -fmax-errors=1 # opciones compilación
#---------------------------------------------------------
SRC = ./src
PROGRAM = a.out
STL_PROGRAM = STLconverter.out
#---------------------------------------------------------
MAIN = ${SRC}/main
POINT = ${SRC}/point/Point
VEC3 = ${SRC}/vec3/Vec3

PRIMITIVE = ${SRC}/primitives/Primitive
SPHERE = ${SRC}/primitives/sphere/Sphere
PLANE = ${SRC}/primitives/plane/Plane
TRIANGLE = ${SRC}/primitives/triangle/Triangle
STL = ${SRC}/primitives/stl/Stl
SPRITE = ${SRC}/primitives/sprite/Sprite

TRANSFORMATION = ${SRC}/transformation/Transformation
RGB = ${SRC}/tone_mapping/rgb/Rgb
PPM = ${SRC}/tone_mapping/ppm/PPM
IMAGE = ${SRC}/tone_mapping/image/Image
UTILS = ${SRC}/utils/Utils
CONCURRENTQUEUE = ${SRC}/utils/ConcurrentQueue
CAMERA = ${SRC}/render/camera/Camera
RAY = ${SRC}/render/ray/Ray
SCENE = ${SRC}/render/scene/Scene
POINTLIGHT = ${SRC}/render/light/point_light/PointLight


all: ${MAIN} 
#---------------------------------------------------------
# "linkar"
${MAIN}:  ${POINT}.o ${VEC3}.o ${SPHERE}.o ${PLANE}.o ${TRIANGLE}.o ${RAY}.o ${POINTLIGHT}.o ${TRANSFORMATION}.o ${RGB}.o ${PPM}.o ${IMAGE}.o ${UTILS}.o ${CAMERA}.o ${SCENE}.o ${STL}.o ${SPRITE}.o ${MAIN}.cpp
	${CC} -g ${MAIN}.cpp ${POINT}.o ${VEC3}.o ${SPHERE}.o ${PLANE}.o ${TRIANGLE}.o ${RAY}.o ${POINTLIGHT}.o ${TRANSFORMATION}.o ${RGB}.o ${PPM}.o ${IMAGE}.o ${UTILS}.o ${CAMERA}.o ${SCENE}.o ${STL}.o ${SPRITE}.o -o ${PROGRAM} ${CPPFLAGS} -pthread
#---------------------------------------------------------
# compilar
${POINT}.o: ${POINT}.hpp ${POINT}.cpp
	${CC} -c ${POINT}.cpp -o ${POINT}.o ${CPPFLAGS}

${VEC3}.o: ${VEC3}.hpp ${VEC3}.cpp 
	${CC} -c ${VEC3}.cpp -o ${VEC3}.o  ${CPPFLAGS}

${SPHERE}.o: ${SPHERE}.hpp ${PRIMITIVE}.hpp ${SPHERE}.cpp
	${CC} -c ${SPHERE}.cpp -o ${SPHERE}.o ${CPPFLAGS}
	
${PLANE}.o: ${PLANE}.hpp ${PRIMITIVE}.hpp ${PLANE}.cpp
	${CC} -c ${PLANE}.cpp -o ${PLANE}.o ${CPPFLAGS}

${TRIANGLE}.o: ${TRIANGLE}.hpp ${PRIMITIVE}.hpp ${TRIANGLE}.cpp
	${CC} -c ${TRIANGLE}.cpp -o ${TRIANGLE}.o ${CPPFLAGS}

${STL}.o: ${STL}.hpp ${STL}.cpp
	${CC} -c ${CPPFLAGS} ${FLAGSOCK} ${STL}.cpp -o ${STL}.o

${SPRITE}.o: ${SPRITE}.hpp ${SPRITE}.cpp
	${CC} -c ${CPPFLAGS} ${FLAGSOCK} ${SPRITE}.cpp -o ${SPRITE}.o


${RAY}.o: ${RAY}.hpp ${RAY}.cpp
	${CC} -c ${RAY}.cpp -o ${RAY}.o ${CPPFLAGS}

${TRANSFORMATION}.o: ${TRANSFORMATION}.hpp ${TRANSFORMATION}.cpp
	${CC} -c ${CPPFLAGS} ${FLAGSOCK} ${TRANSFORMATION}.cpp -o ${TRANSFORMATION}.o

${RGB}.o: ${RGB}.hpp ${RGB}.cpp
	${CC} -c ${CPPFLAGS} ${FLAGSOCK} ${RGB}.cpp -o ${RGB}.o

${PPM}.o: ${PPM}.hpp ${PPM}.cpp
	${CC} -c ${CPPFLAGS} ${FLAGSOCK} ${PPM}.cpp -o ${PPM}.o

${IMAGE}.o: ${IMAGE}.hpp ${IMAGE}.cpp
	${CC} -c ${CPPFLAGS} ${FLAGSOCK} ${IMAGE}.cpp -o ${IMAGE}.o

${UTILS}.o: ${UTILS}.hpp ${UTILS}.cpp
	${CC} -c ${CPPFLAGS} ${FLAGSOCK} ${UTILS}.cpp -o ${UTILS}.o

${CAMERA}.o: ${CAMERA}.hpp ${CONCURRENTQUEUE}.hpp ${CAMERA}.cpp
	${CC} -c ${CPPFLAGS} ${FLAGSOCK} ${CAMERA}.cpp -o ${CAMERA}.o

${SCENE}.o: ${SCENE}.hpp ${SCENE}.cpp
	${CC} -c ${CPPFLAGS} ${FLAGSOCK} ${SCENE}.cpp -o ${SCENE}.o

${POINTLIGHT}.o: ${POINTLIGHT}.hpp ${POINTLIGHT}.cpp
	${CC} -c ${CPPFLAGS} ${FLAGSOCK} ${POINTLIGHT}.cpp -o ${POINTLIGHT}.o

#---------------------------------------------------------
# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	$(RM) ${POINT}.o ${VEC3}.o ${SPHERE}.o ${PLANE}.o ${TRIANGLE}.o ${RAY}.o ${POINTLIGHT}.o ${TRANSFORMATION}.o ${RGB}.o ${PPM}.o ${IMAGE}.o ${UTILS}.o ${CAMERA}.o ${SCENE}.o ${STL}.o ${SPRITE}.o
	$(RM) ${PROGRAM}