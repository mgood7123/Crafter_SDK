cmake_minimum_required(VERSION 3.10.2)
project(PolygonDeformer)

add_library(PolygonDeformer STATIC
        PolygonDeformerBlueprint.cpp
)

target_link_libraries(PolygonDeformer PUBLIC Crafter_Magnum)
