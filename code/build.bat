@echo off
mkdir ..\..\buildHM
pushd ..\..\buildHM
cl -Zi ..\Handmade\code\win32_handmade.cpp user32.lib gdi32.lib
popd