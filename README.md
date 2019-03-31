# MarsLander #

## Was ist das? ##
Ein kleines Spiel für einen Programmierwettbewerb im NGB.
[Zum Thread](https://ngb.to/threads/40532-Aufgabenstellung-Programmierwettbewerb-Nr-4)

## Wie starte ich das Spiel? ##
Noch gar nicht

## Wie Spiele ich das Spiel ##
Auch noch nicht

## Wie kann ich das Spiel selbst bauen? ##
Auf jeden Fall muss das Git Repository irgendwo hin geklont werden oder über den "DOWNLOAD ZIP" Button heruntergeladen und irgendwo hin entpackt werden. Das geklonte oder entpackte Verzeichnis wird ab jetzt das Source Code Verzeichnis genannt.
 
### Abhängigkeiten ###
Zum Bauen wird [CMake](https://cmake.org/) und ein aktueller C++ Compiler benötigt (ich verwende eine MinGW W64 g++ 8.1.0 für Windows und g++ 4.9.2 für debian Linux).

Als Grafikbibliothek wird [SFML](http://www.sfml-dev.org/index.php) verwendet. Für Linux kann dafür das Paket sfml-dev über den Paketmanager installieren, für Windows können die Bibliotheken für einige Compiler von der [SFML Download-Seite](http://www.sfml-dev.org/download/sfml/2.3.2/) heruntergeladen oder selbst gebaut werden (Source ist ebenfalls auf der Download-Seite).

### Bauen für Windows ###
Da unter Windows die Bibliotheken nicht an einem Standardpfad sind, muss das Verzeichnis angegeben werden, in dem SFML installiert ist. Die geschieht durch setzen der Umgebungsvariablen SFML_ROOT. Man kann die Variable global als Windows-Umgebungsvariable setzen, oder temporär in einer Konsole. Im Beispiel hier wird der Einfachheit halber die Konsolenvariante gewählt. Im Beispiel befindet sich SFML in C:\Libraries\SFML. Zum Bauen wird MinGW verwendet und nur die Debug Version gebaut. Alle Befehle werden in dem Verzeichnis des Source Codes ausgeführt. (CMake Experten werden mir jetzt vielleicht sagen dass das schlecht ist, aber ihr könnt es ja besser machen, als "keep it simple" Anleitung reicht das so)  Andere Generatoren sollten auch funktionieren, habe ich aber nicht getestet.

    SET SFML_ROOT=C:\Libraries\SFML
    cmake -DCMAKE_BUILD_TYPE=Debug -G"MinGW Makefiles" .
    cmake --build .

Um das Spiel auch ausführen zu können müssen noch die SFML DLLs in das Source Verzeichnis (bzw. das Install Verzeichnis) kopiert werden (für die Debug Version, Release entsprechend ohne "-d"):
* sfml-audio-d-2.dll
* sfml-graphics-d-2.dll
* sfml-system-d-2.dll
* sfml-window-d-2.dll
* openal32.dll

Dann kann marslander.exe gestartet werden.

### Bauen für Linux ###
Unter Linux findet CMake SFML in den Standardpfaden, wenn also keine selbstgebaute Version an einem speziellen Ort verwendet werden soll ist nichts weiter notwendig. Zum Bauen wird hier der Standardcompiler g++ mit Unix makefile verwendet und nur die Debug Version gebaut. Alle Befehle werden in dem Verzeichnis des Source Codes ausgeführt.

    cmake -DCMAKE_BUILD_TYPE=Debug -G"Unix Makefiles" .
    cmake --build .

Wenn alles erfolgreich gebaut wurde kann das Spiel direkt mit ./marslander gestartet werden.