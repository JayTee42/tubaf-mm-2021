#!/bin/bash
if ! cmake -version; then
echo "cmake must be installed to continue... exiting!"
exit 1
fi
echo -e "\033[32m"
echo "================================="
echo "====== Preparing GLFW/GLAD ======"
echo "================================="
echo -e "\033[39m"
git clone https://github.com/glfw/glfw.git
cmake glfw/CMakeLists.txt
cd glfw
make
cd ..
git clone https://github.com/Dav1dde/glad.git
cd glad
python -m glad --generator c --out-path=../
cd ..
rm -rf glad
cp glfw/src/libglfw3.a src/
cp -r glfw/include/GLFW include/
rm -rf glfw
echo -e "\033[32m"
echo "======================================"
echo "====== Finished GLFW/GLAD Setup ======"
echo "======================================"
echo -e "\033[39m"
echo "Include following headers in your source file:"
echo "======================="
echo "#include <glad/glad.h>"
echo "#include <GLFW/glfw3.h>"
echo "======================="
echo "For MAC build with:"
echo -e "\033[33m"
echo "gcc main.c src/glad.c {additional c-files} -Iinclude -Lsrc -lglfw3 -framework AppKit -framework IOKit -framework CoreVideo"
echo -e "\033[39m"
