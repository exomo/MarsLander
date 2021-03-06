#ifndef GLOBALRESOURCES_H
#define GLOBALRESOURCES_H

#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace ExomoMarsLander
{
    /* Exception-Klasse für Fehler beim Laden der Ressourcen */
    class resource_exception : public std::runtime_error
    {
    public:
        resource_exception(std::string resourcePath)
            : std::runtime_error("Could not load resource: " + resourcePath)
        {
        }

    private:
        std::string resourcePath;
    };

    /*
    * Ein globaler Ressourcen-Manager, der alle benötigten Datein wie Schriftarten, Grafiken Sound, etc.
    * lädt. Alle Komponenten können die Ressourcen verwenden, damit nicht jeder die Dateien neu laden muss.
    */
    class GlobalResources
    {
        public:
            /* Lade alle Ressourcen aus den Dateien. */
            void LoadResources();

            /* Zugriffsmethoden für die einzelnen Resourcen. */
            const sf::Font& GetFont() const;
            const sf::Texture& GetSpaceship() const;
            const sf::Texture& GetSpace() const;
            const sf::Texture& GetPlanet() const;
            const sf::Texture& GetSurface() const;
            const sf::Texture& GetFlame() const;
            const sf::SoundBuffer& GetEngineSound() const;


            /* Einfache Singleton-Implementierung, mit der immer auf die selbe statische Instanz zugegriffen wird. */
            static GlobalResources& GetInstance()
            {
                static GlobalResources instance;
                return instance;
            }

        protected:
        private:
            /*
            * Privater Konstruktor verhindert, dass andere Klassen neue Instanzen von GlobalResources
            * erzeugen. Es darf nur eine Instanz geben, auf die mit GetInstance() zugegriffen wird.
            */
            GlobalResources() = default;

            /* Die eigentlichen Ressourcen. */
            sf::Font textFont;

            sf::Texture spaceshipTexture;
            sf::Texture spaceTexture;
            sf::Texture planetTexture;
            sf::Texture surfaceTexture;
            sf::Texture flameTexture;

            sf::SoundBuffer engineSound;
    };

}

#endif // GLOBALRESOURCES_H
