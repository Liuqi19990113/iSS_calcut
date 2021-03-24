#control the version
cmake_minimum_required (VERSION 2.8)

#project name
project(sample_cut)

aux_source_directory(./src source_file)

add_executable(../sample_cut ${source_file})


