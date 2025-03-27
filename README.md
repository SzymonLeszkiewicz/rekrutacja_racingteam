#  Rekrutacja Zadanie 2
Zadanie znalezienia podzbioru punktów które otaczają wszystkie inne punkty zostało rozwiązane algorytmem **Graham Scan**.
Algorytm zaczyna od posortowania wszystkich punktów względem punktu startowego. 
Najczęsciej jako ten punkt wybiera się punkt o najmniejszej współrzędnej `y`, w przypadku redundancji wybiera się punkt o 
najmniejszej współrzędnej `x`. W projekcie zadanie to wykonywane jest przez funkcje `findStartPoint`. Sortowanie (`sortPoints`) natomiast polega na porównywaniu kątów pomiędzy punktem
startowym a pozostałymi punktami. W praktyce przy sortowaniu używamy iloczyń wektorowego, który pozwala na porównanie kątów
pomiędzy dwoma wektorami. Ponieważ nie interesują nas rzeczywiste różnice w kątach, a jedynie ich porównanie, nie musimy
wykonywać operacji pierwiastkowania, co znacznie przyspiesza obliczenia. Znak iloczynu wektorowego pozwala nam na określenie
kierunku obrotu. Przy punktach współliniowych wybieramy punkt bliższy punktowi startowemu.

Do wybrania finalnej otoczki używamy stosu, na którym przechowujemy punkty. W przypadku, gdy punkt jest po lewej stronie
otrzymanego odcinka, dodajemy go na stos. W przeciwnym wypadku usuwamy punkty z góry stosu, aż do momentu, gdy punkt będzie
po lewej stronie odcinka. Orientacje zwrotu względem odcinka obliczamy w `getOrientation`, a całośc zaimplementowana jest 
w funkcji `convexHull`. Dzięki zastosowanym optymalizacjom algorytm działa w czasie `O(n log n)`.

Szymon Leszkiewicz