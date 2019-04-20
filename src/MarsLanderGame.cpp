﻿#include <MarsLanderGame.h>
#include <statemachine/GameActive.h>
#include <statemachine/GameMainMenu.h>
#include <GlobalResources.h>

#include <iostream>

using namespace ExomoMarsLander;

MarsLanderGame::MarsLanderGame()
    : StateMachine(std::make_shared<GameMainMenu>())
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(800, 600), "~~~ Exomo MarsLander ~~~", sf::Style::Default, settings);
    // window.create(sf::VideoMode::getDesktopMode(), "~~~ Exomo MarsLander ~~~", sf::Style::Fullscreen);

    /* Für jeden Tastendruck soll nur ein Event erzeugt werden, wenn die Taste gedrückt bleibt werden keine wiederholten "KeyDown" events erzeugt. */
    window.setKeyRepeatEnabled(true);

    /* Verticale Synchronisation aktivieren, verhindert den tearing effekt */
    window.setVerticalSyncEnabled(true);

    /* Das Spiel geht ohne Maus, der Cursor soll im Fenster nicht sichtbar sein */
    window.setMouseCursorVisible(false);

    /*
    * Lade alle Ressourcen (Grafik, Sound, Schriftart, ...
    * Wenn eine Ressource nicht erfolgreich geladen wurde, wird eine exception geworfen die das Programm beendet.
    */
    GlobalResources::GetInstance().LoadResources();
}

MarsLanderGame::~MarsLanderGame()
{
}

void MarsLanderGame::run()
{
    /* Uhr starten. Alle Zeiten werden relativ zu diesem Zeitpunkt angegeben. */
    clock.restart();

    /* Hauptschleife in der das Spiel läuft. */
    while (window.isOpen())
    {
        sf::Time elapsed = clock.getElapsedTime();

        handleEvents();
        updateGame(elapsed);
        render();
    }
}

/* Events verarbeiten. Zum Beispiel Tastatureingaben. */
void MarsLanderGame::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        /*
         * Die Hauptklasse behandelt "Fenster geschlossen" selbst.
         * Alle anderen Events (vor allem Tastendrücke) werden vom aktuellen Zustand verarbeitet.
         */
        switch(event.type)
        {
        case sf::Event::Closed:
            /* Fenster soll geschlossen werden */
            window.close();
            break;

        default:
            /* Der aktuelle Zustand kann das Event verarbeiten. */
            currentState->handleEvent(event);
            break;
        }
    }
}

/* Spielstatus aktualisieren: Schlange bewegen, kollision berechnen, etc. */
void MarsLanderGame::updateGame(sf::Time elapsed)
{
    /* Der aktuelle Zustand kann seinen internen Status aktualisieren. */
    auto newState = currentState->updateGame(elapsed, currentState);
    if(newState != nullptr)
    {
        /*
         * Der aktuelle Zustand hat einen Zustandswechsel angefordert.
         * Der neue Zustand ersetzt den alten.
         */
         currentState = newState;
    }
}

void MarsLanderGame::render()
{
    /* Der aktuelle Zustand zeichnet in das Ausgabefenster. */
    currentState->render(window);
    window.display();
}
