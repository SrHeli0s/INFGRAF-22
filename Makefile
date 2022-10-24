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
CPPFLAGS = -I. -I${SRC} -I -O2 -std=c++11 -fmax-errors=1 # opciones compilación
#---------------------------------------------------------
# vars
SRC = ./src
MAIN = ${SRC}/main
TONE_MAPPING = ${SRC}/tone_mapping
PRIMITIVES = ${SRC}/primitives
PROGRAM = a.out
#---------------------------------------------------------
#directorio y clase para manejo de logs

SPHERE = ${PRIMITIVES}/sphere/Sphere
PLANE = ${PRIMITIVES}/plane/Plane
RAY = ${SRC}/ray/Ray
POINT = ${SRC}/point/Point
VEC3 = ${SRC}/vec3/Vec3
TRANSFORMATION = ${SRC}/transformation/Transformation
RGB = ${TONE_MAPPING}/rgb/Rgb
PPM = ${TONE_MAPPING}/ppm/PPM
IMAGE = ${TONE_MAPPING}/image/Image

all: ${MAIN}
#---------------------------------------------------------
# "linkar"
${MAIN}:  ${POINT}.o ${VEC3}.o ${SPHERE}.o ${PLANE}.o ${RAY}.o ${TRANSFORMATION}.o ${RGB}.o ${PPM}.o ${IMAGE}.o ${MAIN}.cpp
	${CC} -g ${MAIN}.cpp ${POINT}.o ${VEC3}.o ${SPHERE}.o ${PLANE}.o ${RAY}.o ${TRANSFORMATION}.o ${RGB}.o ${PPM}.o ${IMAGE}.o -o ${PROGRAM} ${CPPFLAGS} -pthread

#---------------------------------------------------------
# compilar
${POINT}.o: ${POINT}.hpp ${POINT}.cpp
	${CC} -c ${POINT}.cpp -o ${POINT}.o ${CPPFLAGS}

${VEC3}.o: ${VEC3}.hpp ${VEC3}.cpp 
	${CC} -c ${VEC3}.cpp -o ${VEC3}.o  ${CPPFLAGS}

${SPHERE}.o: ${SPHERE}.hpp ${SPHERE}.cpp
	${CC} -c ${SPHERE}.cpp -o ${SPHERE}.o ${CPPFLAGS}
	
${PLANE}.o: ${PLANE}.hpp ${PLANE}.cpp
	${CC} -c ${PLANE}.cpp -o ${PLANE}.o ${CPPFLAGS}

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

#---------------------------------------------------------
# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	$(RM) ${POINT}.o ${VEC3}.o ${SPHERE}.o ${PLANE}.o ${RAY}.o ${TRANSFORMATION}.o ${RGB}.o ${PPM}.o ${IMAGE}.o
	$(RM) ${PROGRAM}