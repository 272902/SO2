
# Systemy operacyjne 2 - Projekt 1
## 1. Instrukcja uruchomienia projektu
  Kompilator C++20 (np. g++)  
   ### Kompilacja:  
    g++ -std=c++20 -o philosophers main.cpp -pthread  
   ### Uruchomienie projektu:  
    ./philosophers <liczba_filozofów>  
  Domyślnie program uruchomi się z 5 filozofami. Można podać inną liczbę jako argument.
## 2. Opis problemu
  Program implementuje **problem filozofów** przy użyciu wielowątkowości. Ilustruje on synchronizacje oraz pokazuje związane z nią kłopoty, oraz techniki rozwiązania ich. Problem ten polega na pięciu filozofach siedzących przy stole. Każdy filozof ma swój talerz, lecz pomiędzy każdym filozowem znajduje się jeden widelec. Aby jeść filozof musi użyć obu widelców po swojej prawej oraz lewej stronie. Filozof najpierw myśli, później robi się głodny, a następnie je. Istnieje sytuacja w istnieje **zagrożenie zakleszczenia** - gdy każdy filozof weźmie lewy widelec i będzie czekał na prawy, lub każdy weźmie prawy i będzie czekał na lewy. 

## 3. Wątki
W tym projekcie implementowane jest **n** wątków, w zależności od danego argumentu programu. Każdy wątek oznacza jednego filozofa. Każdy filozof działa w pętli nieskończonej. Myśli, staje się głodny, próbuje podnieść widelce, je i zwalnia zasoby.

## 4. Sekcje krytyczne i ich rozwiązanie
### Sekcje krytyczne:
- Dostęp do widelców (mutexy leftFork, rightFork)
- Dostęp do konsoli (mutex mo)
- Kontrola liczby jednocześnie jedzących filozofów (semafor table)
### Rozwiązanie problemów współbieżności:
#### Zakleszczenie (Deadlock)
- Filozofowie podnoszą widełki w określonej kolejności (najpierw prawą, potem lewą dla parzystych, odwrotnie dla nieparzystych), co zapobiega cyklom.
- Semafor ogranicza liczbę filozofów, którzy mogą jednocześnie próbować podnieść widełki, co minimalizuje ryzyko zakleszczenia.
#### Zagłodzenie (Starvation)
Dzięki semaforowi ograniczającemu liczbę jedzących filozofów zapewniamy, że filozofowie nie czekają w nieskończoność na dostęp do zasobów.
### Warunki wyścigu (Race Conditions)
Dostęp do widelców, oraz wyświetlanie w konsoli są chronione przez mutexy.
