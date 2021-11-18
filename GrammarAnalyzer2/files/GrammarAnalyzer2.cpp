#include"Menafcts.cpp"

int main() {
    initMap();
    //printMap(M);
    while (true) {
        bool res = scanner();
        if (res == true) {
            cout << "文法符合规范" << endl;
        }
        else {
            cout << "文法不符合规范" << endl;
        }
    }
    return 0;
}