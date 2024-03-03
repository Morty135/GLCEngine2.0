To use GLCEngine on your computer make sure that the CMakeLists.txt are compatable with your setup. By default you should be able to compile on most linux and windows computers.
Make sure that you cloned all the libraries to the include directory. If you didnt clone them open the terminal and do so.
the commands are:
cd include
git clone https://github.com/g-truc/glm
git clone https://github.com/assimp/assimp
git clone https://github.com/glfw/glfw
you will also need glad in the include dirrectory. Here is the glad download link: https://glad.dav1d.de/
Select the core version 4.5 to make it work with the current preincluded shaders. If you feel like using a different version just rewrite the version in the shaders and in the main.cpp.
