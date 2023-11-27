eval "$(conda shell.bash hook)"
conda activate base 
cd ./face/
python img.py
cp ./out/*.h  ./../../src/faces
cd ../../src/core
cp memory.txt ./../../dev/mem_vis
cd ../../dev/mem_vis
g++ mem_vis.cpp 
./a.out 
cd ../script
python mem_conv.py