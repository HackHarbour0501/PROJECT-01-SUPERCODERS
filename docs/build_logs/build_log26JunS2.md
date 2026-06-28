- Date: 26 June(Session 2)
Duration - 3 hours
Goal():
Restructuring the redislite project into a modular and scalable architecture using Cmake 

What I Did():
1. Project directory refactoring :
Added all the headers of dynamic array, linked list hashmap and redislite into include folder 
then added Redislite.cpp into the src folder .

2. Seperated the implementations files and the interface files.

3. Cmake Build Configurations 
created a cmakelist.txt

Challenges Faced:

CMake executable not found in the system environment.
Build process could not proceed due to missing build configuration tool.
Existing MinGW installation uses an older GCC version, which may limit support for newer C++ features.