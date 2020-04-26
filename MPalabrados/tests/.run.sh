touch tests//.timeout
CMD="valgrind --leak-check=full  valgrind --leak-check=full /home/jorge/Escritorio/MP/MPALABRADOS/MPalabrados/  -l ES -r 100 -p data/OPEN_ERROR.data 1> tests//.out10 2>&1"
eval $CMD
rm tests//.timeout
