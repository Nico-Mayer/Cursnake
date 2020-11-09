# Cursnake

   Dieses Spiel Orientiert sich an dem Spiel Snake,
   welches 1997 auf dem Nokia 3310 erschienen ist.
   Eine Schlange fährt über den Bildschirm und kann
   mit ihrem Kopf Früchte essen die zufällig auf dem Bildschirm erscheinen.
   Isst die Schlange eine Frucht wird ihr Koerper um ein Element verlängert
   und man erhält 5 punkte.

   Sollte die Schlange mit ihrem Kopf sich selbst, oder die Wand(optional in den Einstellungen waehlbar)
   beruehren, ist das spiel vorbei.

   Ziel ist es so viele punkte wie moeglich zu erhalten ohne zu sterben.

   Recomendet Terminal Size: 100x40

   Das Spiel verfuegt über ein Haupt und ein Settings Menue,
   im Hauptmenue kann man das Spiel starten, zum Settings Menue navigieren und das Spiel beenden.

   Im Settings Menue hat man die Moeglichkeit, die Farbe und den Body Skin der Schlange zu veraendern
   und es ist möglich die Kollision mit der Wand ein und auszuschalten,
   was die Schwierigkeit des Spiels erhöht.


   Man navigiert durch das Menü mit den Tasten W A S D und kann mit der Enter Taste seine Auswahl bestaetigen.
   Im spiel Steuert man die Schlange ebenfalls mit W A S D, hat mit Space die Moeglichkeit das Spiel zu pausieren,
   und kann mit esc das Spiel abbrechen und gelangt wieder ins Hauptmenue.


   Sowohl im Haupt als auch Settings Menue befinden sich Animierte ASCII Fonts.
   Der Kopf der Schlange ändert seinen char dynamisch zu der Richtung in die sie sich bewegt.
   Menu Elemente Grafisch Annimiert duch Hervorhebung des Ausgewählten Menüpunkts,
   im Settings Menu Color Picker auch mit dynamischer vorschau der Farben.


   Die Schlange bewegt sich je nach User Input über den Bildschirm, dabei folgt jedes Element hinter dem Kopf seinem
   Vorgaenger, Kollisionen erkennt die Schlang, mit sich selbst, mit der Frucht die sie einsammelt, und je nach
   Einstellung stirbt die Schlange bei Kollision mit der Wand oder kann diese Passieren und kommt auf der
   gegenüberliegenden Seite wieder zum vorschein.

   Der Score erhöht sich mit jeder Frucht die von der Schlange gegessen wurde um 5.

Tastaturbelegung:
          Menü: W = Cursor nach Oben
                S = Cursor nach Unten
                A = Cursor nach Links
                D = Cursor nach Rechts
                Enter = Auswahl bestätigen
          
          Ingame: W = Schlange bewegt sich nach Oben
                  S = Schlange bewegt sich nach Unten
                  A = Schlange bewegt sich nach Links
                  D = Schlange bewegt sich nach Rechts

                  Space = Pausiert das Spiel
                  esc = Moglichkeit das spiel zu verlassen, man kommt zurück ins Hauptmenue

Benutzte Literatur, Links)

          Q0: Wissen und Grundlegende Informationen aus der NCurses Video-Tutorial reihe:
              http://schorsch.efi.fh-nuernberg.de/roettger/index.php/NCurses/NCurses-Tutorial
              (c) Stefan Roettger

          Q1: Verwendete ASCII FONTS:
              http://patorjk.com/software/taag/#p=testall&h=0&v=1&f=Alpha&t=Snake
          
          Q2: Grundidee und Anregung zum Menu Design:
              https://www.youtube.com/watch?v=3YiPdibiQHA&t=66s
             
          Q3: ASCII Art "Schlange" aus dem Haupt Menue:
              https://asciiart.website/index.php?art=animals/reptiles/snakes

          Q4: free Menu sound effects from: 
              https://www.fesliyanstudios.com

          Q5: start.wav: 
              https://www.sounds-resource.com/nintendo_switch/supersmashbrosultimate/sound/16073/

          Q6: save.wav exit.wav:
              https://www.sounds-resource.com/game_boy_gbc/pokemonredblueyellow/sound/17241/

Bekannte Bugs)
          1. Sollten Ingame 2 Tastatur eingaben zu schnell aufeinender folgen, kann es Passieren das die 
             Schlange Stirbt ohne tatsächlich kontakt mit einem Body Element gehabt zu haben.
          2. Das spiel läuft aktuell auf 40fps, und wurde auf einem leistungsstarken pc entwikelt, bei tests
             auf schwächeren Systemen Zuckt das Terminal Ingame.
          3. Frucht kann momentan noch in der Schlange Spwanen.
          
