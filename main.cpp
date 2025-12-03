#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>

using namespace std;

struct User {
    string login;
    string password;
};

struct Trip {
    string from;
    string to;
    int tariff;
    string genre;
    int temperature;
    int paymentMethod;
    string cardNumber;
    int distance;
    int price;
    int rating;
    int bonusPoints;
};

User users[100];
int user_count = 0;

Trip trips[100];
int trip_count = 0;

void RegisterUser() {
    cout << "\n===== РЕЄСТРАЦІЯ НОВОГО КОРИСТУВАЧА =====\n";

    cout << "Введіть логін: ";
    cin >> users[user_count].login;

    cout << "Введіть пароль: ";
    cin >> users[user_count].password;

    cout << "Користувач зареєстрований!\n";

    user_count++;
}

bool LoginUser() {
    string login, password;

    cout << "\n===== ВХІД ДО СИСТЕМИ =====\n";
    cout << "Логін: ";
    cin >> login;
    cout << "Пароль: ";
    cin >> password;

    for (int i = 0; i < user_count; i++) {
        if (users[i].login == login && users[i].password == password) {
            cout << "\nВхід успішний! Ласкаво просимо, " << login << "!\n";
            return true;
        }
    }

    cout << "Невірний логін або пароль!\n";
    return false;
}

void InputRoute(Trip& t) {
    cin.ignore(10000, '\n');
    cout << "\n===== МАРШРУТ =====\n";
    cout << "Звідки вас забрати?: ";
    getline(cin, t.from);

    cout << "Куди прямуємо?: ";
    getline(cin, t.to);
}

void SelectTariff(Trip& t) {
    cout << "\n===== ВИБІР ТАРИФУ =====\n";
    cout << "1 - Економ (10 грн/км)\n";
    cout << "2 - Стандарт (15 грн/км)\n";
    cout << "3 - Бізнес  (20 грн/км)\n";

    while (true) {
        cout << "Ваш вибір: ";
        cin >> t.tariff;

        if (!cin.fail() && t.tariff >= 1 && t.tariff <= 3)
            break;

        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка вводу!\n";
    }
}
void SelectAtmosphere(Trip& t) {
    int choice;

    cout << "\n===== АТМОСФЕРА =====\n";
    cout << "1 - Вказати свої вподобання\n";
    cout << "2 - Без музики\n";
    cout << "3 - Без різниці\n";

    while (true) {
        cout << "Ваш вибір: ";
        cin >> choice;

        if (!cin.fail() && choice >= 1 && choice <= 3)
            break;

        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка!\n";
    }

    cin.ignore(10000, '\n');

    if (choice == 1) {
        cout << "Що ви хочете слухати?: ";
        getline(cin, t.genre);
    }
    else if (choice == 2) {
        t.genre = "Без музики";
    }
    else {
        t.genre = "Без різниці";
    }
}

void SelectTemperature(Trip& t) {
    while (true) {
        cout << "\nТемпература (16–30°C): ";
        cin >> t.temperature;

        if (!cin.fail() && t.temperature >= 16 && t.temperature <= 30)
            break;

        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Некоректно!\n";
    }
}

void CalculateDistanceAndPrice(Trip& t) {
    srand(time(NULL));
    t.distance = rand() % 20 + 1;

    int pricePerKm = (t.tariff == 1 ? 10 : (t.tariff == 2 ? 15 : 20));
    t.price = t.distance * pricePerKm;

    cout << "\n===== РОЗРАХУНОК =====\n";
    cout << "Маршрут: " << t.from << " до " << t.to << "\n";
    cout << "Відстань: " << t.distance << " км\n";
    cout << "Ціна за км: " << pricePerKm << " грн\n";
    cout << "Орієнтовна сума: " << t.price << " грн\n";
}

bool ConfirmOrder() {
    int choice;

    cout << "\nПідтвердити замовлення?\n";
    cout << "1 - Так\n";
    cout << "2 - Ні\n";
    cout << "Ваш вибір: ";
    cin >> choice;

    return choice == 1;
}

void Payment(Trip& t) {
    cout << "\n===== ОПЛАТА =====\n";
    cout << "1 - Картка\n";
    cout << "2 - Готівка\n";
    cout << "Ваш вибір: ";
    cin >> t.paymentMethod;

    if (t.paymentMethod == 1) {
        while (true) {
            cout << "Введіть номер картки (16 цифр): ";
            cin >> t.cardNumber;

            if (t.cardNumber.size() == 16) {
                cout << "Оплата успішна!\n";
                break;
            }
            cout << "Помилка! Некоректний номер.\n";
        }
    }
    else {
        cout << "Оплата готівкою. Дякуємо!\n";
    }
}

void Rating(Trip& t) {
    while (true) {
        cout << "\nОцініть поїздку (1–5): ";
        cin >> t.rating;

        if (!cin.fail() && t.rating >= 1 && t.rating <= 5)
            break;

        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Помилка! Введіть число від 1 до 5.\n";
    }
}

void AddBonus(Trip& t) {
    t.bonusPoints = 10;
    cout << "\nВи отримали " << t.bonusPoints << " бонусних балів!\n";
}

void AfterAuthFlow() {
    Trip t;

    InputRoute(t);
    SelectTariff(t);
    SelectAtmosphere(t);
    SelectTemperature(t);
    CalculateDistanceAndPrice(t);

    if (!ConfirmOrder()) {
        cout << "\nЗамовлення скасовано. Повернення в меню...\n";
        Sleep(1500);
        return;
    }

    Payment(t);
    Rating(t);
    AddBonus(t);

    trips[trip_count] = t;
    trip_count++;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int choice;

    do {
        cout << "\n========================================\n";
        cout << " АВТОМАТИЗОВАНА СИСТЕМА ВИКЛИКУ ТАКСІ \n";
        cout << "========================================\n";
        cout << "1 - Реєстрація\n";
        cout << "2 - Вхід\n";
        cout << "0 - Вихід\n";
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1:
            RegisterUser();
            AfterAuthFlow();
            break;

        case 2:
            if (LoginUser())
                AfterAuthFlow();
            break;

        case 0:
            cout << "До побачення!\n";
            break;

        default:
            cout << "Помилка! Такого пункту немає.\n";
        }

    } while (choice != 0);

    return 0;
}
