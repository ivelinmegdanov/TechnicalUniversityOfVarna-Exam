#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

struct Device // структура за устройство
{
	char device[50]; // тип устройство
	char problem[50]; // проблем според клиента
	int id; // сериен номер
};

struct Service // структура за сервиза
{
	int id; // номер на поръчката
	int dayOfTheMonth; // ден от месеца
	char name[50]; // име на клиент
	Device device[1]; // структура за устройство
	char nameTehnician[50]; // име на сервизния техник
	char repaired[50]; // извършен ремонт
	double price; // цена
	int daysRequiredToRepair; // дни престой в сервиза
	char status[20]; // статус на поръчката
};

#define serviceCount 100 // дефиниране на броя елементи в масива service

// деклариране на функции
void input(Service service[], int& count, int& lastDate);
void outputMenu(Service service[], int start, int count);
void output(Service service[], int start, int count);
void edit(Service service[], int count);
void service(Service service[], int count);
void odit(Service service[], int count);
void writeFile(Service service[], int count);
void readFile(Service service[], int& count, int& lastDate);
void writeToFile(Service service[], int count);
void readFromFile(Service service[], int& count, int& lastDate);
string deviceProblem();
string deviceRepaired();
int menu();

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Bulgarian"); // Позволява да се използва кирилица.

	int choice = -1; // избор
	int lastDate = 0; // последната въведена дата;

	Service newService[serviceCount]; // дефинитане на масив от структури.
	int counter = 0; // брояч
	// може да се използва и readFromFile за бинарно четене.
	readFile(newService, counter, lastDate); // зарежда запазените структури от предишни пъти

	while (choice != 0) // цикъл който ще се върти докато избора не е 0
	{
		system("CLS"); // Изчиства конзолата.

		// може да се използва и writeToFile за бинарно записване
		writeFile(newService, counter); // запаметява промените

		choice = menu();

		switch (choice) // Оператор за многовариантен избор.
		{
		case 0: // избор 0
			system("CLS"); // Изчиства конзолата.
			char ch;
			cout << "Наистина ли искаш да прекратиш програмата? (y = да)" << endl; // Извежда дадения текст на конзолата
			cin >> ch;
			if (ch != 'y') // проверка дали избора не е равен на 'y'
			{
				choice = -1; // избора се задава на стойност -1 за да не се прекрати програмата
			}
			else
			{
				system("CLS"); // Изчиства конзолата.
				cout << "Излизане.." << endl; // Извежда дадения текст на конзолата
			}
			break;
		case 1: // избор 1
			input(newService, counter, lastDate); // извиква се функцията input
			system("pause"); // Паузира програмата докато не се натине някой бутон
			break;
		case 2: // избор 2
			outputMenu(newService, 0, counter); // извиква се функцията outputMenu
			system("pause"); // Паузира програмата докато не се натине някой бутон
			break;
		case 3: // избор 3
			edit(newService, counter); // извиква се функцията edit
			system("pause"); // Паузира програмата докато не се натине някой бутон
			break;
		case 4: // избор 4
			service(newService, counter); // извиква се функцията service
			system("pause"); // Паузира програмата докато не се натине някой бутон
			break;
		case 5: // избор 5
			odit(newService, counter); // извиква се функцията odit
			system("pause"); // Паузира програмата докато не се натине някой бутон
			break;
		default: // всеки друг избор
			cout << "Няма такава опция в менюто!" << endl; // извежда дадения текст на конзолата
			system("pause"); // Паузира програмата докато не се натине някой бутон
			break;
		}
	}
}

void input(Service service[], int& count, int& lastDate)
{
	int choice = -1, counter; // деклариране на променливи
	system("CLS"); // Изчиства конзолата.
	while (choice != 0) // цикъл който ще се върти докато избора не е 0
	{
		// извежда се меню на конзолата
		cout << "Въвеждане на устройства!" << endl;
		cout << "[1] Въвеждане на 1 устройство\n[2] Въвеждане на даден брой устройства\n[0] Назад" << endl;

		cin >> choice; // въвежда се избор

		switch (choice) // оператор за многовариантен избор
		{
		case 0:
			return; // излиза от функцията
			break;
		case 1:
			counter = 1;
			choice = 0; // избора става равен на 0 за да се излезе от цикъла
			break;
		case 2:
			cout << "Колко устройства да се въведът?: "; // извежда се следното съобщение
			cin >> counter; // въвежда се броя на елементите които да се въведът
			choice = 0; // избора става равен на 0 за да се излезе от цикъла
			break;
		default:
			system("CLS"); // Изчиства конзолата.
			cout << "Няма такава опция в менюто!" << endl; // извежда се следното съобщение
			system("pause"); // Паузира програмата докато не се натине някой бутон
			break;
		}
	}

	system("CLS"); // Изчиства конзолата.
	for (int i = count; i < count + counter; i++) // върти се цикъл който започва от count което е индекса на последно въведения елемент до count + counter което е броя на елементи които да се въведът
	{
		cout << "--- Въвеждане на " << i + 1 << " поръчка! ---" << endl; // извежда се следното съобщение
		service[i].id = i + 1; // номера на поръчката се въвежда автоматично
		bool invalidDate = true;
		while (invalidDate) // цикъл който проверява дали въведената дата е вярна
		{
			cout << "Въведете ден от месеца "; cin >> service[i].dayOfTheMonth; // въвежда се дата
			if (service[i].dayOfTheMonth < 1 || service[i].dayOfTheMonth > 31 || service[i].dayOfTheMonth < lastDate) // проверява дали датата е валидна
			{
				cout << "Въведената дата е вече минала или е невалидна!" << endl; // извежда се следното съобщение
			}
			else
				invalidDate = false; // прави променливата invalidDate да е равна на false при което ще се излезе от цикъла
		}
		lastDate = service[i].dayOfTheMonth; // записва последно въведената дата
		cin.ignore();
		cout << "Въведете име на клиент "; cin.getline(service[i].name, 50); // въвежда се име на клиент
		cout << "Въведете тип на устройството "; cin.getline(service[i].device->device, 50); // въвежда се тип на устройство
		bool invalidDeviceId = true;
		while (invalidDeviceId) // цикъл който проверява дали въведения номер на устройство е верен
		{
			cout << "Въведете номер на устройството "; cin >> service[i].device->id; // въвежда се номер на устройство
			bool holder = false;
			for (int j = 0; j < count + counter; j++) // цикъл който преминава през всички поръчки
			{
				if (service[i].device->id == service[j].device->id && i != j) // проверява дали вече съществува такъв номер на устройство
				{
					cout << "Вече има такъв номер на поръчка!" << endl; // извежда на конзолата следното съобщение
					holder = true;
					break;
				}
			}
			if (!holder)
				invalidDeviceId = false; // прави променливата invalidDeviceId да е равна на false при което ще се излезе от цикъла
		}
		cin.ignore(); // пропуска празни елементи
		cout << "Въведете проблем на устройството (според клиента) " << endl;
		string device = deviceProblem();
		strcpy_s(service[i].device->problem, device.c_str());; // въвежда се проблем с устройството
		service[i].price = 0;  // въвежда се стойност за цената по подразбиране

		string holderStatus = "приета поръчка";
		strcpy_s(service[i].status, holderStatus.c_str()); // въвежда се стойност за статуса на устройството по подразбиране

		string holderNameTehnician = "няма";
		strcpy_s(service[i].nameTehnician, holderNameTehnician.c_str()); // въвежда се стойност за името на техника по подразбиране

		string holderRepaired = "няма";
		strcpy_s(service[i].repaired, holderRepaired.c_str()); // въвежда се стойност за ремонта извършен по устройството по подразбиране

		service[i].daysRequiredToRepair = 0; // въвежда се стойност за дните нужни за поправла по подразбиране
	}

	count += counter; // увеличава се общия брой на устройствата
}

void outputMenu(Service service[], int start, int count)
{
	Service holder[serviceCount]; // нов масив от структура
	int serviceCounter = 0;
	int choice = -1;
	int max = 0;
	while (choice != 0)
	{
		system("CLS"); // Изчиства конзолата.

		// Извежда се меню с опции.
		cout << "[1] Извеждане на всички устройства\n[2] Извеждане на всички устройства с максимален престой за ремонт\n[3] Извеждане на всички активни поръчки\n[0] Назад" << endl;
		cout << "Въведете вашия избор: ";
		cin >> choice;

		switch (choice) // оператор за многовариантен избор
		{
		case 0:
			break;
		case 1:
			output(service, start, count); // извиква се функция output
			choice = 0;
			break;
		case 2:
			for (int i = 0; i < count; i++) // цикъл който започва от 0 и стига до count
			{
				if (service[i].daysRequiredToRepair > max) // проверява колко е най- големия престой за ремонт
					max = service[i].daysRequiredToRepair; // записва в променлива най- големия престой за ремонт
			}

			for (int i = 0; i < count; i++) // цикъл който започва от 0 и стига до count
			{
				if (service[i].daysRequiredToRepair == max) // проверява кои устройства с най- голям престой за ремонт
				{
					holder[serviceCounter] = service[i]; // записва устройствата с най- голям престой за ремонт в масив
					serviceCounter++; // брояч за масива
				}
			}
			output(holder, 0, serviceCounter); // извиква се функцията output
			choice = 0;
			break;
		case 3:
			for (int i = 0; i < count; i++) // цикъл който започва от 0 и стига до count
			{
				if (service[i].status[0] == 'п') // Проверява дали статуса е приета поръчка
				{
					holder[serviceCounter] = service[i]; // записва устройствата които статуса им е приета поръчка в масив
					serviceCounter++; // брояч за масива
				}
			}
			output(holder, 0, serviceCounter); // извиква се функцията output
			choice = 0;
			break;
		default:
			cout << "Няма такава опция в менюто!" << endl; // изкарва следното съобщение на конзолата
			system("pause");
			break;
		}
	}
}

void output(Service service[], int start, int count)
{
	system("CLS"); // Изчиства конзолата.
	for (int i = start; i < count; i++) // цикъл който обхожда всички поръчки
	{
		// Извеждат се следните съобщения на конзолата
		cout << "--- Поръчка ---" << endl;
		cout << "Номер на поръчката: " << service[i].id << endl;
		cout << "Ден от месеца: " << service[i].dayOfTheMonth << endl;
		cout << "Име на клиент: " << service[i].name << endl;
		cout << "Тип на устройство: " << service[i].device->device << endl;
		cout << "Номер на устройството: " << service[i].device->id << endl;
		cout << "Проблем на устройството (според клиента): " << service[i].device->problem << endl;
		cout << "Име на техник: " << service[i].nameTehnician << endl;
		cout << "Извършен ремонт: " << service[i].repaired << endl;
		cout << "Цена: " << service[i].price << "лв." << endl;
		cout << "Дни нужни за поправка: " << service[i].daysRequiredToRepair << endl;
		cout << "Статус: " << service[i].status << endl;
		cout << endl;
	}
}

void edit(Service service[], int count)
{
	system("CLS"); // Изчиства конзолата.

	int orderNumber, holder;
	bool found = false;
	cout << "Корекция на данни за устройство!" << endl;
	cout << "Въведете номер на поръчка: ";
	cin >> orderNumber;

	for (int i = 0; i < count; i++) // цикъл който започва от 0 и стига до count
	{
		if (orderNumber == service[i].id) // проверява дали има такъв поръчков номер в масива
		{
			found = true; // когато се намери променливата found става на true
			holder = i;
		}
	}

	if (!found) // ако не е намерен
	{
		system("CLS"); // Изчиства конзолата.
		cout << "Няма намерена поръчка с номер " << orderNumber << endl; // изкарва следното съобщение на конзолата
	}
	else
	{
		system("CLS"); // Изчиства конзолата.
		int choice;

		// Извежда се меню с опции.
		cout << "Корекция на данни за устройство с поръчков номер (" << service[holder].id << ")" << endl;
		cout << "[1] Корекция на данните\n[2] Отказване на сервизна поръчка" << endl;

		cin >> choice;

		if (choice == 1) // ако избора е 1
		{
			cin.ignore(); // игнорира празно място и нов ред
			bool invalidDate = true;
			while (invalidDate) // цикъла се върти докато датата е невалидна
			{
				cout << "Стар ден от месеца за поръчката (" << service[holder].dayOfTheMonth << "). Въведете нов ден от месеца за поръчката: "; cin >> service[holder].dayOfTheMonth; // въвежда се нова дата
				if (service[holder].dayOfTheMonth < 1 || service[holder].dayOfTheMonth > 31) // проверява дали датата е валидна
				{
					cout << "Невалидна дата!" << endl; // изкарва следното съобщение на конзолата
				}
				else
					invalidDate = false; // датата става валидна
			}
			cin.ignore();
			cout << "Старо име на клиент (" << service[holder].name << "). Въведете ново име на клиент: "; cin.getline(service[holder].name, 50); // въвежда се ново име на клиент
			cout << "Стар тип на устройството (" << service[holder].device->device << "). Въведете нов тип на устройството: "; cin.getline(service[holder].device->device, 50); // въвежда се нов тип на устройството
			cout << "Стар номер на устройството (" << service[holder].device->id << "). Въведете нов номер на устройството: "; cin >> service[holder].device->id; // въвежда се нов номер на устройството
			cout << "Старт проблем с усторйството (" << service[holder].device->problem << "). Въведете нов проблем с устройстово: " << endl;
			string device = deviceProblem();
			strcpy_s(service[holder].device->problem, device.c_str()); // въвежда се проблем с устройството
			cin.ignore();
			cout << "Старо име на техник (" << service[holder].nameTehnician << "). Въведете ново име на техник: "; cin.getline(service[holder].nameTehnician, 50); // въвежда се ново име на сервизен техник
			cout << "Стара поправка на устройството (" << service[holder].repaired << "). Въведете нова поправка на устройството: "; cin.getline(service[holder].repaired, 50); // въвежда се нова поправка на устройството
			cout << "Стара цена на устройството (" << service[holder].price << "). Въведете новa цена на устройството: "; cin >> service[holder].price; // въвежда се нова цена на устройството
			cout << "Стар статус на устройството (" << service[holder].status << "). Въведете новa цена на устройството: " << endl; // извежда следното съобщение на конзолата
			cout << "[1] приета поръчка\n[2] отказана поръчка\n[3] ремонтиран" << endl;
			int choice2;
			cin >> choice2;
			if (choice2 == 1) 
			{
				string holderStatus = "приета поръчка";
				strcpy_s(service[holder].status, holderStatus.c_str()); // въвежда се стойност за статуса на устройството
			}
			else if (choice2 == 2) 
			{
				string holderStatus = "отказана поръчка";
				strcpy_s(service[holder].status, holderStatus.c_str()); // въвежда се стойност за статуса на устройството
			}
			else if (choice2 == 3) 
			{
				string holderStatus = "ремонтиран";
				strcpy_s(service[holder].status, holderStatus.c_str()); // въвежда се стойност за статуса на устройството
			}
			else 
				cout << "Няма такава опция! Статуса на устройството си остава същия!" << endl; // извежда следното съобщение на конзолата
		}
		else if (choice == 2) // ако избора е 2
		{
			if (service[holder].status[0] == 'п') // ако първата буква на статуса е равна на п
			{
				system("CLS"); // Изчиства конзолата.
				string holderStatus = "отказана поръчка";
				strcpy_s(service[holder].status, holderStatus.c_str()); // отказва се опръчката

				service[holder].price += 10; // начисляват се 10 лв.
				cout << "Поръчката беше отказана! (Начислени са 10лв. неустойка)" << endl; // изкарва следното съобщение на конзолата
			}
			else
			{
				system("CLS"); // Изчиства конзолата.
				cout << "Сервизната поръчка е била извършена или вече отказана!" << endl; // изкарва следното съобщение на конзолата
			}
		}
		else 
		{
			system("CLS");
			cout << "Невалиден избор!" << endl; // изкарва следното съобщение на конзолата
		}
	}
}

void service(Service service[], int count)
{
	system("CLS"); // Изчиства конзолата.

	int deviceNumber, holder;
	bool found = false;

	// изкарва следните съобщения на конзолата
	cout << "Сервизно обслужване на устройство!" << endl;
	cout << "Въведете серийния номер на устройството: ";
	cin >> deviceNumber;

	for (int i = 0; i < count; i++) // цикъл който започва от 0 и стига до count
	{
		if (deviceNumber == service[i].device->id) // ако номера е равен на въведения
		{
			found = true; // намерен
			holder = i; // запазва индекса
		}
	}

	if (!found)
	{
		system("CLS"); // Изчиства конзолата.
		cout << "Няма намерено устройство с номер " << deviceNumber << endl; // не е намерен
	}
	else
	{
		if (service[holder].status[0] == 'п') // ако статуса е равен на приера поръчка
		{
			system("CLS"); // Изчиства конзолата.
			cout << "Сервизно обслужване на устройство с номер (" << service[holder].id << ")" << endl; // следното съобщение се изкарва на конзолата

			output(service, holder, holder + 1); // извиква се функцията output
			cout << endl;

			double price;
			int day;
			cin.ignore();
			cout << "Въведете име на сервизния техник обслужващ устройството: "; cin.getline(service[holder].nameTehnician, 50); // въвежда се име на сервизен техник
			cout << "Въведете извършения ремонт по устройството: " << endl;
			string device = deviceRepaired(); // вика се функция с меню за готови избори
			strcpy_s(service[holder].repaired, device.c_str());  // въвежда извършения ремонт по устройството
			cout << "Въведете цена за извършения ремонт по устройството: "; cin >> price; // въвежда се цена
			bool invalidDate = true;
			while (invalidDate) // цикъл който се върти докато въведената дата е коректра
			{
				cout << "Въведете деня в който е поправено устройството: "; cin >> day; // въвежда се дата
				if (day < service[holder].dayOfTheMonth || day < 1 || day > 31) // проверява дали датата е коректна
				{
					cout << "Невалидна дата!" << endl; // не е валидна
				}
				else
					invalidDate = false; // датата е валидна
			}
			service[holder].daysRequiredToRepair = day - service[holder].dayOfTheMonth; // формула която изчислява дните нужни за поправка
			service[holder].price += price; // начислява се цена
			string holderStatus = "ремонтиран"; // статуса се променя на ремонтиран
			strcpy_s(service[holder].status, holderStatus.c_str()); // статуса се променя на ремонтиран
		}
		else
		{
			system("CLS"); // Изчиства конзолата.
			cout << "Сервизната поръчка е била извършена или отказана!" << endl; // изкарва се следното съобщение на конзолата
		}
	}
}

void odit(Service service[], int count)
{
	Service holder[serviceCount];
	int serviceCounter = 0;
	int choice = -1;
	while (choice != 0) // цикъл който се върти докато не се избере 0
	{
		system("CLS"); // Изчиства конзолата.

		// Извежда се меню с опции.
		cout << "[1] Извеждане на поръчките за ден от месеца\n[2] Извеждане на поръчките за даден тип устройство\n[3] Извееждане на поръчките за даден клиент\n[0] Назад" << endl;
		cout << "Въведете вашия избор: ";
		cin >> choice;

		switch (choice) // оператор за многовариантен избор
		{
		case 0:
			return;
			break;
		case 1:
			system("CLS"); // Изчиства конзолата.
			int day;
			cout << "Извеждане на поръчките за ден от месеца, сортирани по сериен номер" << endl;
			cout << "Въведете ден от месеца: ";
			cin >> day;

			for (int i = 0; i < count; i++) // цикъл който започва от 0 и стига до count
			{
				if (service[i].dayOfTheMonth == day) // проверява дали съществува въведения ден
				{
					holder[serviceCounter] = service[i]; // запазва всички съществуващи структури с дадения ден
					serviceCounter++; // увеличава броя на променливата пазеща общия брой на масива
				}
			}

			if (serviceCounter > 0) // ако брояча е повече от 0
			{
				for (int i = 0; i < serviceCounter - 1; i++) // цикъл започващ от 0 до serviceCounter - 1
				{
					for (int j = 0; j < serviceCounter - i - 1; j++)// цикъл започващ от 0 до serviceCounter - 1
					{
						if (holder[j].device->id > holder[j + 1].device->id) // проверява дали сегашния номер е по голям от следващия
						{
							//  разменят се в масива (bubblesort)
							Service temp = holder[j];
							holder[j] = holder[j + 1];
							holder[j + 1] = temp;
						}
					}
				}
				output(holder, 0, serviceCounter); // извиква се функция output
			}
			else
				cout << "Няма направени поръчки на този ден!" << endl; // извежда се следното съобщение на конзолата
			choice = 0;
			break;
		case 2:
			system("CLS"); // Изчиства конзолата.
			char device[50];
			// извежда се следните съобщения на конзолата
			cout << "Извеждане на поръчките за даден тип устройства, които са ремонтирани и сортирани по дата в намаляващ ред" << endl;
			cout << "Въведете тип устройство: ";
			cin >> device;

			for (int i = 0; i < count; i++) // цикъл който започва от 0 и се върти до count
			{
				if (strcmp(service[i].device->device, device) == 0 && strcmp(service[i].status, "ремонтиран") == 0) // ако въведеното устройство съществува и е ремонтирано
				{
					holder[serviceCounter] = service[i]; // запазва се във масив
					serviceCounter++; // вдига се брояча на масива с 1
				}
			}

			if (serviceCounter > 0) // ако брояча е повече от 0
			{
				for (int i = 0; i < serviceCounter - 1; i++)// цикъл започващ от 0 до serviceCounter - 1
				{
					for (int j = 0; j < serviceCounter - i - 1; j++)// цикъл започващ от 0 до serviceCounter - 1
					{
						if (holder[j].dayOfTheMonth < holder[j + 1].dayOfTheMonth) // ако сегашния ден е по- малък по следващия 
						{
							//  разменят се в масива (bubblesort)
							Service temp = holder[j];
							holder[j] = holder[j + 1];
							holder[j + 1] = temp;
						}
					}
				}
				output(holder, 0, serviceCounter); // извиква се функция output
			}
			else
				cout << "Няма направени поръчки с такъв тип устройство, което да е ремонтирано!" << endl; // извежда се следното съобщение на конзолата
			choice = 0;
			break;
		case 3:
			system("CLS"); // Изчиства конзолата.
			char name[50];
			// извежда се следните съобщения на конзолата
			cout << "Извеждане на поръчките за даден клиент, сортирани по сериен номер на устройствата" << endl;
			cout << "Въведете име на клиент: ";
			cin >> name;

			for (int i = 0; i < count; i++) // цикъл започващ от 0 стигащ до count
			{
				if (strcmp(service[i].name, name) == 0) // проверява дали въведеното име се среща
				{
					holder[serviceCounter] = service[i]; // запазва структурата в масив
					serviceCounter++; // брояча на масива се вдига с 1
				}
			}

			if (serviceCounter > 0) // ако брояча е по- голям от 0
			{
				for (int i = 0; i < serviceCounter - 1; i++)// цикъл започващ от 0 до serviceCounter - 1
				{
					for (int j = 0; j < serviceCounter - i - 1; j++)// цикъл започващ от 0 до serviceCounter - 1
					{
						if (holder[j].device->id > holder[j + 1].device->id) // проверява дали сегашното id на масива е по- голямо от следващото
						{
							//  разменят се в масива (bubblesort)
							Service temp = holder[j];
							holder[j] = holder[j + 1];
							holder[j + 1] = temp;
						}
					}
				}
				output(holder, 0, serviceCounter); // извиква се функция output
			}
			else
				cout << "Няма направени поръчки на това име!" << endl; // извежда се следното съобщение на конзолата
			choice = 0;
			break;
		default:
			cout << "Няма такава опция в менюто!" << endl; // извежда се следното съобщение на конзолата
			system("pause");
			break;
		}
	}
}

void writeFile(Service service[], int count)
{
	ofstream f1;
	f1.open("f1.dat", ios::out); // отваря се файл с име f1.dat
	if (f1.is_open()) // проверка дали файла е отворен успешно
	{
		for (int i = 0; i < count; i++) // цикъл който започва от 0 и стига до count
		{
			// записват се следните стойности от структурата в файла
			f1 << service[i].id << endl;
			f1 << service[i].dayOfTheMonth << endl;
			f1 << service[i].name << endl;
			f1 << service[i].device->device << endl;
			f1 << service[i].device->problem << endl;
			f1 << service[i].device->id << endl;
			f1 << service[i].nameTehnician << endl;
			f1 << service[i].repaired << endl;
			f1 << service[i].price << endl;
			f1 << service[i].daysRequiredToRepair << endl;
			f1 << service[i].status << endl;
		}
		f1.close(); // затваряне на файла
	}
	else // ако не е отворен успешно файла
		cout << "Неуспошно отваряне на файла!" << endl; // изкарва на конзолата следното съобщение
}

void readFile(Service service[], int& count, int& lastDate)
{
	// проверява се колко нови реда има файла
	ifstream myFile("f1.dat");
	myFile.unsetf(ios_base::skipws);
	unsigned line_count = std::count(
		std::istream_iterator<char>(myFile),
		std::istream_iterator<char>(),
		'\n');

	fstream f1;
	f1.open("f1.dat", ios::in); // отваря се файл с име f1.dat

	if (f1.is_open())  // проверка дали файла е отворен успешно
	{
		for (int i = 0; i < line_count / 11; i++) // цикъл който започва от 0 и стига до броя на масива от структури запаметен в файла
		{
			f1 >> service[i].id;
			f1 >> service[i].dayOfTheMonth;
			f1.ignore();
			f1.getline(service[i].name, 50);
			f1.getline(service[i].device->device, 50);
			f1.getline(service[i].device->problem, 50);
			f1 >> service[i].device->id;
			f1.ignore();
			f1.getline(service[i].nameTehnician, 50);
			f1.getline(service[i].repaired, 50);
			f1 >> service[i].price;
			f1 >> service[i].daysRequiredToRepair;
			f1.ignore();
			f1.getline(service[i].status, 50);

			if (lastDate < service[i].dayOfTheMonth)
				lastDate = service[i].dayOfTheMonth;
		}

		count = line_count / 11;
		f1.close(); // затваряне на файла
	}
	else // ако не е отворен успешно файла
		cout << "Неуспошно отваряне на файла!" << endl; // изкарва на конзолата следното съобщение
}

void writeToFile(Service service[], int count) 
{
	fstream file;
	file.open("f2.dat", ios::binary | ios::out);//отваря се файла
	if (file.is_open())
	{
		file.write((char*)service, sizeof(Service));//записват се данните от файла
		file.close();//затваре са файла
	}
	else
		cout << endl << "Грешка при отварянето на файла";
}

void readFromFile(Service service[], int& count, int& lastDate) 
{
	fstream file;
	file.open("f2.dat", ios::binary | ios::in);//отваря се файл
	if (file.is_open())
	{
		file.seekg(0L, ios::end);//слага се селектора в края на файла
		long pos = (long)file.tellg();//намира се размера до селектора
		file.seekg(0L, ios::beg);//слага се селектора в началото на файла
		file.close();//затваря се файла
		int n = pos / (sizeof(Service));
		file.open("f2.dat", ios::binary | ios::in);//отваря се файл
		file.read((char*)service, n * (sizeof(Service)));//чете се от файла
		file.close();//затваря се файла
	}
	else
		cout << endl << "Грешка при отварянето на файла";
}

string deviceProblem()
{
	int choice;
	string holder;
	while (true) // безкраен цикъл
	{
		// Извежда се меню с опции.
		cout << "[1] Проблем с дисплея" << endl;
		cout << "[2] Не се зарежда" << endl;
		cout << "[3] Трябва почистване" << endl;
		cout << "[4] Няма звук" << endl;
		cout << "[5] Устройството забива" << endl;
		cout << "[6] Шчупен" << endl;
		cout << "[7] Проблем с камерата" << endl;
		cout << "[8] Въведете свой проблем" << endl;

		cin >> choice;

		switch (choice) // оператор за многовариантен избор
		{
		case 1:
			return "Проблем с дисплея";
			break;
		case 2:
			return "Не се зарежда";
			break;
		case 3:
			return "Трябва почистване";
			break;
		case 4:
			return "Няма звук";
			break;
		case 5:
			return "Устройството забива";
			break;
		case 6:
			return "Шчупен";
			break;
		case 7:
			return "Проблем с камерата";
			break;
		case 8:
			cout << "Въведете вашия проблем:" << endl;
			cin >> holder;
			return holder;
			break;
		default:
			cout << "Няма такава опция в менюто!" << endl;
			system("pause");
			break;
		}
	}
}

string deviceRepaired() 
{
	int choice;
	string holder;
	while (true) // безкраен цикъл
	{
		// Извежда се меню с опции.
		cout << "[1] Смяна на дисплея" << endl;
		cout << "[2] Поправка на зареждането" << endl;
		cout << "[3] Почистен" << endl;
		cout << "[4] Сменени говорители" << endl;
		cout << "[5] Преинсталация" << endl;
		cout << "[6] Поправка на драскотини" << endl;
		cout << "[7] Сменена камера" << endl;
		cout << "[8] Въведете своя поправка" << endl;

		cin >> choice;

		switch (choice) // оператор за многовариантен избор
		{
		case 1:
			return "Смяна на дисплея";
			break;
		case 2:
			return "Поправка на зареждането";
			break;
		case 3:
			return "Почистен";
			break;
		case 4:
			return "Сменени говорители";
			break;
		case 5:
			return "Преинсталация";
			break;
		case 6:
			return "Поправка на драскотини";
			break;
		case 7:
			return "Сменена камера";
			break;
		case 8:
			cout << "Въведете извършената поправка:" << endl;
			cin >> holder;
			return holder;
			break;
		default:
			cout << "Няма такава опция в менюто!" << endl;
			system("pause");
			break;
		}
	}
}

int menu() 
{
	int choice;

	// Извежда се меню с опции.
	cout << "[0] Изход от програмата\n[1] Въвеждане на устройства\n[2] Извеждане на устройства\n[3] Корекция на данни за устройство\n[4] Сервизно обслужване на устройството\n[5] Одит" << endl;
	cout << "Въведете число: ";

	cin >> choice; // Въвежда се опция от менюто.

	return choice;
}