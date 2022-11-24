#!/bin/bash -x
echo -n 'It is good to collect things,' > abc
ls -Fli abc
ln abc xyz
ln -s xyz ghi
echo ' but it is better to go on walks.' >> xyz
cat abc
ls -Fli abc xyz ghi
rm abc
ls -Fli xyz ghi
rm xyz
ls -Fli ghi
