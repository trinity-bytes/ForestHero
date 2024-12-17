#pragma once
#include "windows.h" // acceder a la api de windows
#include "mmsystem.h" // para playsound

#pragma comment(lib, "winmm.lib") // libreria de PlaySound

using namespace std;
using namespace System;

void DetenerMusica() 
{
    PlaySound(NULL, 0, 0);  // Detener cualquier sonido en reproducción
}

void RepSkibididevs()
{
    DetenerMusica();
    PlaySound(TEXT("Resources/Music/sonidoSkibidiDevs.wav"), NULL, SND_SYNC);
}

void RepIntroPressStart()
{
    DetenerMusica();
    PlaySound(TEXT("Resources/Music/musicaIntroPressStart.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void RepIniciandoMenu()
{
    PlaySound(TEXT("Resources/Music/sonidoIniciandoMenuP.wav"), NULL, SND_SYNC);
}

void RepMenuPrincipal() 
{
    DetenerMusica();
    PlaySound(TEXT("Resources/Music/musicaMenuPrincipal.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void RepMenuSecundario() 
{
    DetenerMusica();
    PlaySound(TEXT("Resources/Music/musicaMenuSecundario.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void RepSeleccionIniciarJuego()
{
    PlaySound(TEXT("Resources/Music/sonidoSeleccionIniciarJuego.wav"), NULL, SND_SYNC);
}

void RepSeleccionMenuSecundario()
{
    PlaySound(TEXT("Resources/Music/sonidoSeleccionMenuSecundario.wav"), NULL, SND_SYNC);
}


void RepNivelNormal() 
{
    DetenerMusica();
    PlaySound(TEXT("Resources/Music/musicaNivelNormal.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void RepNivelParteFinal() 
{
    DetenerMusica();
    PlaySound(TEXT("Resources/Music/musicaNivelFinalBoss.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void RepGODerrota() 
{
    PlaySound(TEXT("Resources/Music/sonidoDerrota.wav"), NULL, SND_SYNC);
}

void RepGOVictoria() 
{
    PlaySound(TEXT("Resources/Music/sonidoGanasteuu.wav"), NULL, SND_SYNC);
}

void RepSalirNivel() 
{
    PlaySound(TEXT("Resources/Music/sonidoSalirNivel.wav"), NULL, SND_SYNC);
}

void RepWinner() 
{
    DetenerMusica();
    PlaySound(TEXT("Resources/Music/musicWinner.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void RepLoser() 
{
    DetenerMusica();
    PlaySound(TEXT("Resources/Music/musicLoser.wav"), NULL, SND_ASYNC | SND_LOOP);
}

void RepSalirJuego() 
{
    PlaySound(TEXT("Resources/Music/sonidoSalirJuego.wav"), NULL, SND_SYNC);
}