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
SRC=./src
MAIN = ${SRC}/main
PROGRAM = a.out
#---------------------------------------------------------
#directorio y clase para manejo de logs

POINT=${SRC}/point/Point
VEC3=${SRC}/vec3/Vec3
SPHERE =${SRC}/sphere/Sphere
TRANSFORMATION = ${SRC}/transformation/Transformation
RGB = ${SRC}/tone_mapping/rgb/Rgb
PPMREADER = ${SRC}/tone_mapping/ppm/PPMreader
PPMWRITER = ${SRC}/tone_mapping/ppm/PPMwriter

all: ${MAIN}
#---------------------------------------------------------
# "linkar"
${MAIN}:  ${POINT}.o ${VEC3}.o ${SPHERE}.o ${TRANSFORMATION}.o ${RGB}.o ${PPMREADER}.o ${PPMWRITER}.o ${MAIN}.cpp
	${CC} -g ${MAIN}.cpp ${POINT}.o ${VEC3}.o ${SPHERE}.o ${TRANSFORMATION}.o ${RGB}.o ${PPMREADER}.o ${PPMWRITER}.o -o ${PROGRAM} ${CPPFLAGS} -pthread

#---------------------------------------------------------
# compilar
${POINT}.o: ${POINT}.hpp ${POINT}.cpp
	${CC} -c ${POINT}.cpp -o ${POINT}.o ${CPPFLAGS}

${VEC3}.o: ${VEC3}.hpp ${VEC3}.cpp 
	${CC} -c ${VEC3}.cpp -o ${VEC3}.o  ${CPPFLAGS}

${SPHERE}.o: ${SPHERE}.hpp ${SPHERE}.cpp
	${CC} -c ${SPHERE}.cpp -o ${SPHERE}.o ${CPPFLAGS}

${TRANSFORMATION}.o: ${TRANSFORMATION}.hpp ${TRANSFORMATION}.cpp
	${CC} -c ${CPPFLAGS} ${FLAGSOCK} ${TRANSFORMATION}.cpp -o ${TRANSFORMATION}.o

${RGB}.o: ${RGB}.hpp ${RGB}.cpp
	${CC} -c ${CPPFLAGS} ${FLAGSOCK} ${RGB}.cpp -o ${RGB}.o

${PPMREADER}.o: ${PPMREADER}.hpp ${PPMREADER}.cpp
	${CC} -c ${CPPFLAGS} ${FLAGSOCK} ${PPMREADER}.cpp -o ${PPMREADER}.o

${PPMWRITER}.o: ${PPMWRITER}.hpp ${PPMWRITER}.cpp
	${CC} -c ${CPPFLAGS} ${FLAGSOCK} ${PPMWRITER}.cpp -o ${PPMWRITER}.o

#---------------------------------------------------------
# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	$(RM) ${POINT}.o ${VEC3}.o ${SPHERE}.o ${TRANSFORMATION}.o ${RGB}.o ${PPMREADER}.o ${PPMWRITER}.o
	$(RM) ${PROGRAM}