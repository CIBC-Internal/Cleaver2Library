#-------------------------------------------------------------------
#
# // Cleaver - A MultiMaterial Conforming Tetrahedral Meshing Library
# -- Library CMakeList
#
# Primary Author: Jonathan Bronson (bronson@sci.utah.edu)
#
#-------------------------------------------------------------------
#-------------------------------------------------------------------
#
# Copyright (c) 2011, 2012, Scientific Computing & Imaging Institute
# and the University of Utah. All Rights Reserved.
#
# Redistribution and use in source and binary forms is strictly
# prohibited without the direct consent of the author.
#
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#-------------------------------------------------------------------
#-------------------------------------------------------------------

PROJECT(cleaverlib)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# project version
SET(${PROJECT_NAME}_MAJOR_VERSION 0)
SET(${PROJECT_NAME}_MINOR_VERSION 1)
SET(${PROJECT_NAME}_PATCH_LEVEL 0)

# project options
OPTION(BUILD_SHARED_LIBS OFF)

# Add Teem library includes
INCLUDE_DIRECTORIES(${Teem_BINARY_DIR}/include)

# source files
FILE(GLOB Cleaver_SOURCE_FILES *.c*)
FILE(GLOB Cleaver_HEADER_FILES *.h)
SET(Cleaver_API_HEADER_FILES
    Cleaver.h
    CleaverMesher.h
    CleaverMesherImpl.h
    Octree.h            # remove on release
    AbstractField.h
    AbstractScalarField.h
    ScalarField.h
    SizingFieldCreator.h
    SizingFieldOracle.h
    ConstantField.h
    InverseField.h
    ScaledField.h
    AbstractVolume.h
    Volume.h
    TetMesh.h
    Vertex.h
    Geometry.h
    HalfEdge.h
    HalfFace.h
    Face.h
    Tet.h
    BoundingBox.h
    vec3.h
    Timer.h
    Status.h
    )

ADD_DEFINITIONS(-DTETLIBRARY)

# Add library includes
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/include)

SET(SCI_CLEAVER2_INCLUDE "${CMAKE_SOURCE_DIR}/src/lib")
SET(SCI_CLEAVER2_LIBRARY cleaver2 CACHE INTERNAL "Cleaver 2 library" FORCE)

# output library
ADD_LIBRARY(${SCI_CLEAVER2_LIBRARY} STATIC ${Cleaver_HEADER_FILES} ${Cleaver_SOURCE_FILES})
TARGET_LINK_LIBRARIES(${SCI_CLEAVER2_LIBRARY} jsoncpp)

set(SCI_CLEAVER2_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/src/lib)
set(CLEAVER2_USE_FILE "${CMAKE_SOURCE_DIR}/UseCleaver2.cmake")

CONFIGURE_FILE("${CMAKE_SOURCE_DIR}/CMake/Cleaver2Config.cmake.in"
  "${CMAKE_BINARY_DIR}/Cleaver2Config.cmake" @ONLY IMMEDIATE)
#EXPORT(TARGETS ${SCI_CLEAVER2_LIBRARY} FILE Cleaver2Exports.cmake)
