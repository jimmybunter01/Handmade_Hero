@echo off

mkdir ..\build
pushd ..\build
cl -Zi C:\Users\James\Documents\Handmade_Hero\code\win_32_handmade.cpp user32.lib Gdi32.lib
popd