# TEST DE VELOCIDAD DE LAS MATRICES M Y M-MOÑO

rm testVelocidadGrandeRes.csv
# rm testVelocidadChicoRes.csv
touch testVelocidadGrandeRes.csv
# touch testVelocidadChicoRes.csv

# Genero los tests
python generarTestsVelocidad.py

# echo "TEST DE IMAGENES CHICAS"
# # Corro los tests de imagenes chicas y los agrego a testVelocidadChicoRes.csv
# for i in {1..41};
#     do
#     echo "test de imagenes chicas numero $i";
#     ./testvelocidad 50 < tests/testVelocidadRed$i.in >> testVelocidadChicoRes.csv;
#     echo "test de imagenes chicas numero $i TERMINADO";
# done;
# echo "test de imagenes chicas terminado"

echo "TEST DE IMAGENES GRANDES"
# Corro los tests de imagenes grandes y los agrego a testVelocidadChicoRes.csv
for i in {1..41};
    do
    echo "test grande numero $i";
    ./testvelocidad 5 < tests/testVelocidad$i.in >> testVelocidadGrandeRes.csv;
    echo "test grande numero $i TERMINADO";
done;