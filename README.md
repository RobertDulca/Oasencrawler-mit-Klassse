# Oasencrawler-mit-Klassse #

Verwenden Sie das erste Beispiel als Basis und erweitern Sie die structs zu Klassen.
Folgende Punkte müssen dabei beachtet werden:
* Verwenden Sie nun statt structs Klassen. Beachten Sie dabei die richtige Verwendung
von Zugriffsmodifikatoren, Gettern/Settern, den verschiedenen Konstruktoren und Destruktoren sowie der sinnvollen Strukturierung von Funktionen und Daten.
* Bilden Sie Ihre Klassen in einem entsprechenden Diagramm ab.
* Uberprüfen Sie alle Parameterübergaben an Funktionen und Benutzereingaben auf Fehler und verhindern Sie so, dass Ihr Programm bei ungültigen Eingaben nicht mehr
richtig funktioniert, Eingaben sollen so lange wiederholt werden, bis sie korrekt sind
und der Spielfluss erst dann fortgesetzt werden.
* Testen Sie Ihren Code ausgiebig und berücksichtigen Sie Randbedingungen.

## Stufe 1 ##

* Die Spielwelt: Verwenden Sie ein zweidimensionales Array mit den Dimensionen 5x5
um die einzelnen Spielfelder darzustellen. Je nachdem, welcher Wert gespeichert wird,
handelt es sich um ein anderes Feld. Die Spielwelt soll zu Beginn zufällig generiert
werden, verwenden Sie dazu die rand()-Funktion um zufällige Werte zu generieren und
damit bestimmen zu können, welche Art von Feld erstellt wird. Es gibt verschiedene
Typen von Feldern mit ihren jeweiligen Wahrscheinlichkeiten bei der Erstellung:
  * Leere Felder 4/10 : Betritt ein Charakter ein leeres Feld passiert nichts.
  * Gefahren 4/10 : Betritt ein Charakter Gefahrenfelder, wird er mit einer Wahrscheinlichkeit von 1/6 verletzt und verliert einen Lebenspunkt, hat er dann keine Lebenspunkte mehr, verliert er das Spiel.
  * Brunnen 1/10 : Der Charakter kann sich ausruhen und erhält einen Lebenspunkt.
  * Relikte 1/10 : Der Charakter erhält einen Reliktpunkt, gibt es dann keine Relikte mehr, gewinnt er das Spiel. Bei der Erstellung der Welt muss sichergestellt werden, dass zumindest ein Relikt vorhanden ist.

   Alle Felder werden zu leeren Feldern, nachdem der Charakter sie betreten hat.
   
* Der Charakter: Der Charakter verfügt über einen Lebenspunkte- und Reliktpunktewert. Weiters soll seine Position in der Spielwelt durch eine x- und y-Koordinate angegeben werden. Zu Beginn hat der Charakter 5 Lebens- und 0 Reliktpunkte. Er startet bei den Koordinaten (0|0) Nachdem die Spielwelt erstellt wurde, soll es möglich sein, den Charakter durch Benutzereingaben zu steuern. Nach jeder Bewegung soll das Feld, auf das sich der Charakter bewegt hat, abgehandelt werden, solange bis eine der Abbruchbedingungen für das Spiel erreicht wurde.

* Erweitern Sie das Spiel um einen oder mehrere Gegner, die den Charakter jagen und das
Spiel so erschweren.

* Implementieren Sie ein Verlaufssystem, das es dem Spiel erlaubt, die wichtigen Ereignisse
(gefundene Relikte, erlittener und geheilter Schaden, Interaktion mit Gegnern) zu speichern
und diese dann am Ende ausgibt, um so den Spielverlauf noch einmal zusammenzufassen.


## Stufe 2 ##

Der Charakter soll nun zusätzlich drei verschiedene Attribute besitzen. Die Gefahrenfelder
sollen einem dieser Attribute entsprechen. Betritt der Charakter nun ein Gefahrenfeld, muss
er mit seinem entsprechenden Attribut eine Probe bestehen, wie diese aussieht, können Sie
selbst gestalten. Besteht er diese Probe, verliert er keinen Lebenspunkt.
Zusätzlich soll der Charakter bei Brunnen und Relikten Gegenstände finden können. Diese
Gegenstände entsprechen ebenfalls einem der drei Attribute und haben einen Effekt, der
ausgelöst wird, wenn der Charakter auf ein Gefahrenfeld des entsprechenden Attributs geht,
auch hier sollen Sie den Effekt selbst gestalten. Zum Beispiel könnte er einen Unsichtbarkeitstrank finden, der ihn eine fehlgeschlagene Attributsprobe ignorieren lässt und dann abgelegt
wird.

## Stufe 3 ##

Das Spiel soll nun nicht mehr aufhören, wenn der Charakter alle Relikte findet, stattdessen soll
die Welt mit neuen Feldern befüllt und das Spiel dann fortgesetzt werden. Immer wenn der
Charakter alle Relikte gefunden hat, soll weiters der Schwierigkeitsgrad des Spiels ansteigen,
wie genau Sie das ausgestalten wollen, bleibt Ihnen überlassen.

