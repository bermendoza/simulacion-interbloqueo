#include <iostream>
#include <vector>

using namespace std;

int numProcesos = 5;
int numRecursos = 3;

vector<vector<int>> asignado = {
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};

vector<vector<int>> maximo = {
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};

vector<int> disponible = {3, 3, 2};

bool detectarInterbloqueo() {
    vector<int> trabajo = disponible;
    vector<bool> finalizado(numProcesos, false);

    while (true) {
        bool progreso = false;

        for (int i = 0; i < numProcesos; i++) {
            if (!finalizado[i]) {
                bool posible = true;
                for (int j = 0; j < numRecursos; j++) {
                    if ((maximo[i][j] - asignado[i][j]) > trabajo[j]) {
                        posible = false;
                        break;
                    }
                }

                if (posible) {
                    for (int j = 0; j < numRecursos; j++)
                        trabajo[j] += asignado[i][j];
                    finalizado[i] = true;
                    progreso = true;
                }
            }
        }

        if (!progreso) break;
    }

    for (bool fin : finalizado) {
        if (!fin) return true;
    }

    return false;
}

int main() {
    if (detectarInterbloqueo()) {
        cout << "⚠️ Interbloqueo detectado en el sistema." << endl;
    } else {
        cout << "✅ No hay interbloqueo." << endl;
    }

    return 0;
}
