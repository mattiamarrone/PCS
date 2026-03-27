# include <iostream>

int main()
{
double ad[4] = {0.0, 1.1, 2.2, 3.3};
float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
int ai[3] = {0, 1, 2};
int x = 1;
float y = 1.1;
// --- Stampa indirizzi array ad (double) ---
std::cout << "Indirizzi array ad (double, 8 byte ciascuno):\n";
for (int i = 0; i < 4; ++i) {
    std::cout << "ad[" << i << "]: " << &ad[i] << "\n";
}

// --- Stampa indirizzi array af (float) ---
std::cout << "\nIndirizzi array af (float, 4 byte ciascuno):\n";
for (int i = 0; i < 8; ++i) {
    std::cout << "af[" << i << "]: " << &af[i] << "\n";
}

// --- Stampa indirizzi array ai (int) ---
std::cout << "\nIndirizzi array ai (int, 4 byte ciascuno):\n";
for (int i = 0; i < 3; ++i) {
    std::cout << "ai[" << i << "]: " << &ai[i] << "\n";
}

// --- Stampa indirizzi variabili scalari ---
std::cout << "\nIndirizzi variabili scalari:\n";
std::cout << "Indirizzo di x (int):   " << &x << "\n";
std::cout << "Indirizzo di y (float): " << &y << "\n";
std::cout << "-------------------------------------\n";
(&y)[1] = 0;




return 0;
}
