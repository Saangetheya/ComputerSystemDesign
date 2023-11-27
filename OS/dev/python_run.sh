pip install opencv-python-headless pillow numpy
cd ./face/
python3 img.py
cp ./out/*.h  ./../../src/faces
cd ../../src/core
cp memory.txt ./../../dev/mem_vis
cd ../../dev/mem_vis
g++ mem_vis.cpp
./a.out
cd ../script
python3 mem_conv.py