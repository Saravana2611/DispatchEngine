echo "Starting CMake build"
cmake -S . -B build/
echo "CMake Build is successful"

echo "Starting build"
make -C build/
echo "Build is successful"