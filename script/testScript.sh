#/bin/bash

echo "Starting script...."

$c = 1
$c = $c + 1
cd "f$(c)"
cd "sf$(c)"

$x = $c * 64
$x = $x - 1
touch "s00$(x).txt"

cd ..
cd ..

echo "all done!"
