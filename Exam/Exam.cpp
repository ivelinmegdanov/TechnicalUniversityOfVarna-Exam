#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

struct Device // ��������� �� ����������
{
	char device[50]; // ��� ����������
	char problem[50]; // ������� ������ �������
	int id; // ������ �����
};

struct Service // ��������� �� �������
{
	int id; // ����� �� ���������
	int dayOfTheMonth; // ��� �� ������
	char name[50]; // ��� �� ������
	Device device[1]; // ��������� �� ����������
	char nameTehnician[50]; // ��� �� ��������� ������
	char repaired[50]; // �������� ������
	double price; // ����
	int daysRequiredToRepair; // ��� ������� � �������
	char status[20]; // ������ �� ���������
};

#define serviceCount 100 // ���������� �� ���� �������� � ������ service

// ����������� �� �������
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
	setlocale(LC_ALL, "Bulgarian"); // ��������� �� �� �������� ��������.

	int choice = -1; // �����
	int lastDate = 0; // ���������� �������� ����;

	Service newService[serviceCount]; // ���������� �� ����� �� ���������.
	int counter = 0; // �����
	// ���� �� �� �������� � readFromFile �� ������� ������.
	readFile(newService, counter, lastDate); // ������� ���������� ��������� �� �������� ����

	while (choice != 0) // ����� ����� �� �� ����� ������ ������ �� � 0
	{
		system("CLS"); // �������� ���������.

		// ���� �� �� �������� � writeToFile �� ������� ���������
		writeFile(newService, counter); // ���������� ���������

		choice = menu();

		switch (choice) // �������� �� �������������� �����.
		{
		case 0: // ����� 0
			system("CLS"); // �������� ���������.
			char ch;
			cout << "�������� �� ����� �� ��������� ����������? (y = ��)" << endl; // ������� ������� ����� �� ���������
			cin >> ch;
			if (ch != 'y') // �������� ���� ������ �� � ����� �� 'y'
			{
				choice = -1; // ������ �� ������ �� �������� -1 �� �� �� �� �������� ����������
			}
			else
			{
				system("CLS"); // �������� ���������.
				cout << "��������.." << endl; // ������� ������� ����� �� ���������
			}
			break;
		case 1: // ����� 1
			input(newService, counter, lastDate); // ������� �� ��������� input
			system("pause"); // ������� ���������� ������ �� �� ������ ����� �����
			break;
		case 2: // ����� 2
			outputMenu(newService, 0, counter); // ������� �� ��������� outputMenu
			system("pause"); // ������� ���������� ������ �� �� ������ ����� �����
			break;
		case 3: // ����� 3
			edit(newService, counter); // ������� �� ��������� edit
			system("pause"); // ������� ���������� ������ �� �� ������ ����� �����
			break;
		case 4: // ����� 4
			service(newService, counter); // ������� �� ��������� service
			system("pause"); // ������� ���������� ������ �� �� ������ ����� �����
			break;
		case 5: // ����� 5
			odit(newService, counter); // ������� �� ��������� odit
			system("pause"); // ������� ���������� ������ �� �� ������ ����� �����
			break;
		default: // ����� ���� �����
			cout << "���� ������ ����� � ������!" << endl; // ������� ������� ����� �� ���������
			system("pause"); // ������� ���������� ������ �� �� ������ ����� �����
			break;
		}
	}
}

void input(Service service[], int& count, int& lastDate)
{
	int choice = -1, counter; // ����������� �� ����������
	system("CLS"); // �������� ���������.
	while (choice != 0) // ����� ����� �� �� ����� ������ ������ �� � 0
	{
		// ������� �� ���� �� ���������
		cout << "��������� �� ����������!" << endl;
		cout << "[1] ��������� �� 1 ����������\n[2] ��������� �� ����� ���� ����������\n[0] �����" << endl;

		cin >> choice; // ������� �� �����

		switch (choice) // �������� �� �������������� �����
		{
		case 0:
			return; // ������ �� ���������
			break;
		case 1:
			counter = 1;
			choice = 0; // ������ ����� ����� �� 0 �� �� �� ������ �� ������
			break;
		case 2:
			cout << "����� ���������� �� �� �������?: "; // ������� �� �������� ���������
			cin >> counter; // ������� �� ���� �� ���������� ����� �� �� �������
			choice = 0; // ������ ����� ����� �� 0 �� �� �� ������ �� ������
			break;
		default:
			system("CLS"); // �������� ���������.
			cout << "���� ������ ����� � ������!" << endl; // ������� �� �������� ���������
			system("pause"); // ������� ���������� ������ �� �� ������ ����� �����
			break;
		}
	}

	system("CLS"); // �������� ���������.
	for (int i = count; i < count + counter; i++) // ����� �� ����� ����� ������� �� count ����� � ������� �� �������� ��������� ������� �� count + counter ����� � ���� �� �������� ����� �� �� �������
	{
		cout << "--- ��������� �� " << i + 1 << " �������! ---" << endl; // ������� �� �������� ���������
		service[i].id = i + 1; // ������ �� ��������� �� ������� �����������
		bool invalidDate = true;
		while (invalidDate) // ����� ����� ��������� ���� ���������� ���� � �����
		{
			cout << "�������� ��� �� ������ "; cin >> service[i].dayOfTheMonth; // ������� �� ����
			if (service[i].dayOfTheMonth < 1 || service[i].dayOfTheMonth > 31 || service[i].dayOfTheMonth < lastDate) // ��������� ���� ������ � �������
			{
				cout << "���������� ���� � ���� ������ ��� � ���������!" << endl; // ������� �� �������� ���������
			}
			else
				invalidDate = false; // ����� ������������ invalidDate �� � ����� �� false ��� ����� �� �� ������ �� ������
		}
		lastDate = service[i].dayOfTheMonth; // ������� �������� ���������� ����
		cin.ignore();
		cout << "�������� ��� �� ������ "; cin.getline(service[i].name, 50); // ������� �� ��� �� ������
		cout << "�������� ��� �� ������������ "; cin.getline(service[i].device->device, 50); // ������� �� ��� �� ����������
		bool invalidDeviceId = true;
		while (invalidDeviceId) // ����� ����� ��������� ���� ��������� ����� �� ���������� � �����
		{
			cout << "�������� ����� �� ������������ "; cin >> service[i].device->id; // ������� �� ����� �� ����������
			bool holder = false;
			for (int j = 0; j < count + counter; j++) // ����� ����� ��������� ���� ������ �������
			{
				if (service[i].device->id == service[j].device->id && i != j) // ��������� ���� ���� ���������� ����� ����� �� ����������
				{
					cout << "���� ��� ����� ����� �� �������!" << endl; // ������� �� ��������� �������� ���������
					holder = true;
					break;
				}
			}
			if (!holder)
				invalidDeviceId = false; // ����� ������������ invalidDeviceId �� � ����� �� false ��� ����� �� �� ������ �� ������
		}
		cin.ignore(); // �������� ������ ��������
		cout << "�������� ������� �� ������������ (������ �������) " << endl;
		string device = deviceProblem();
		strcpy_s(service[i].device->problem, device.c_str());; // ������� �� ������� � ������������
		service[i].price = 0;  // ������� �� �������� �� ������ �� ������������

		string holderStatus = "������ �������";
		strcpy_s(service[i].status, holderStatus.c_str()); // ������� �� �������� �� ������� �� ������������ �� ������������

		string holderNameTehnician = "����";
		strcpy_s(service[i].nameTehnician, holderNameTehnician.c_str()); // ������� �� �������� �� ����� �� ������� �� ������������

		string holderRepaired = "����";
		strcpy_s(service[i].repaired, holderRepaired.c_str()); // ������� �� �������� �� ������� �������� �� ������������ �� ������������

		service[i].daysRequiredToRepair = 0; // ������� �� �������� �� ����� ����� �� �������� �� ������������
	}

	count += counter; // ��������� �� ����� ���� �� ������������
}

void outputMenu(Service service[], int start, int count)
{
	Service holder[serviceCount]; // ��� ����� �� ���������
	int serviceCounter = 0;
	int choice = -1;
	int max = 0;
	while (choice != 0)
	{
		system("CLS"); // �������� ���������.

		// ������� �� ���� � �����.
		cout << "[1] ��������� �� ������ ����������\n[2] ��������� �� ������ ���������� � ���������� ������� �� ������\n[3] ��������� �� ������ ������� �������\n[0] �����" << endl;
		cout << "�������� ����� �����: ";
		cin >> choice;

		switch (choice) // �������� �� �������������� �����
		{
		case 0:
			break;
		case 1:
			output(service, start, count); // ������� �� ������� output
			choice = 0;
			break;
		case 2:
			for (int i = 0; i < count; i++) // ����� ����� ������� �� 0 � ����� �� count
			{
				if (service[i].daysRequiredToRepair > max) // ��������� ����� � ���- ������� ������� �� ������
					max = service[i].daysRequiredToRepair; // ������� � ���������� ���- ������� ������� �� ������
			}

			for (int i = 0; i < count; i++) // ����� ����� ������� �� 0 � ����� �� count
			{
				if (service[i].daysRequiredToRepair == max) // ��������� ��� ���������� � ���- ����� ������� �� ������
				{
					holder[serviceCounter] = service[i]; // ������� ������������ � ���- ����� ������� �� ������ � �����
					serviceCounter++; // ����� �� ������
				}
			}
			output(holder, 0, serviceCounter); // ������� �� ��������� output
			choice = 0;
			break;
		case 3:
			for (int i = 0; i < count; i++) // ����� ����� ������� �� 0 � ����� �� count
			{
				if (service[i].status[0] == '�') // ��������� ���� ������� � ������ �������
				{
					holder[serviceCounter] = service[i]; // ������� ������������ ����� ������� �� � ������ ������� � �����
					serviceCounter++; // ����� �� ������
				}
			}
			output(holder, 0, serviceCounter); // ������� �� ��������� output
			choice = 0;
			break;
		default:
			cout << "���� ������ ����� � ������!" << endl; // ������� �������� ��������� �� ���������
			system("pause");
			break;
		}
	}
}

void output(Service service[], int start, int count)
{
	system("CLS"); // �������� ���������.
	for (int i = start; i < count; i++) // ����� ����� ������� ������ �������
	{
		// �������� �� �������� ��������� �� ���������
		cout << "--- ������� ---" << endl;
		cout << "����� �� ���������: " << service[i].id << endl;
		cout << "��� �� ������: " << service[i].dayOfTheMonth << endl;
		cout << "��� �� ������: " << service[i].name << endl;
		cout << "��� �� ����������: " << service[i].device->device << endl;
		cout << "����� �� ������������: " << service[i].device->id << endl;
		cout << "������� �� ������������ (������ �������): " << service[i].device->problem << endl;
		cout << "��� �� ������: " << service[i].nameTehnician << endl;
		cout << "�������� ������: " << service[i].repaired << endl;
		cout << "����: " << service[i].price << "��." << endl;
		cout << "��� ����� �� ��������: " << service[i].daysRequiredToRepair << endl;
		cout << "������: " << service[i].status << endl;
		cout << endl;
	}
}

void edit(Service service[], int count)
{
	system("CLS"); // �������� ���������.

	int orderNumber, holder;
	bool found = false;
	cout << "�������� �� ����� �� ����������!" << endl;
	cout << "�������� ����� �� �������: ";
	cin >> orderNumber;

	for (int i = 0; i < count; i++) // ����� ����� ������� �� 0 � ����� �� count
	{
		if (orderNumber == service[i].id) // ��������� ���� ��� ����� �������� ����� � ������
		{
			found = true; // ������ �� ������ ������������ found ����� �� true
			holder = i;
		}
	}

	if (!found) // ��� �� � �������
	{
		system("CLS"); // �������� ���������.
		cout << "���� �������� ������� � ����� " << orderNumber << endl; // ������� �������� ��������� �� ���������
	}
	else
	{
		system("CLS"); // �������� ���������.
		int choice;

		// ������� �� ���� � �����.
		cout << "�������� �� ����� �� ���������� � �������� ����� (" << service[holder].id << ")" << endl;
		cout << "[1] �������� �� �������\n[2] ��������� �� �������� �������" << endl;

		cin >> choice;

		if (choice == 1) // ��� ������ � 1
		{
			cin.ignore(); // �������� ������ ����� � ��� ���
			bool invalidDate = true;
			while (invalidDate) // ������ �� ����� ������ ������ � ���������
			{
				cout << "���� ��� �� ������ �� ��������� (" << service[holder].dayOfTheMonth << "). �������� ��� ��� �� ������ �� ���������: "; cin >> service[holder].dayOfTheMonth; // ������� �� ���� ����
				if (service[holder].dayOfTheMonth < 1 || service[holder].dayOfTheMonth > 31) // ��������� ���� ������ � �������
				{
					cout << "��������� ����!" << endl; // ������� �������� ��������� �� ���������
				}
				else
					invalidDate = false; // ������ ����� �������
			}
			cin.ignore();
			cout << "����� ��� �� ������ (" << service[holder].name << "). �������� ���� ��� �� ������: "; cin.getline(service[holder].name, 50); // ������� �� ���� ��� �� ������
			cout << "���� ��� �� ������������ (" << service[holder].device->device << "). �������� ��� ��� �� ������������: "; cin.getline(service[holder].device->device, 50); // ������� �� ��� ��� �� ������������
			cout << "���� ����� �� ������������ (" << service[holder].device->id << "). �������� ��� ����� �� ������������: "; cin >> service[holder].device->id; // ������� �� ��� ����� �� ������������
			cout << "����� ������� � ������������ (" << service[holder].device->problem << "). �������� ��� ������� � �����������: " << endl;
			string device = deviceProblem();
			strcpy_s(service[holder].device->problem, device.c_str()); // ������� �� ������� � ������������
			cin.ignore();
			cout << "����� ��� �� ������ (" << service[holder].nameTehnician << "). �������� ���� ��� �� ������: "; cin.getline(service[holder].nameTehnician, 50); // ������� �� ���� ��� �� �������� ������
			cout << "����� �������� �� ������������ (" << service[holder].repaired << "). �������� ���� �������� �� ������������: "; cin.getline(service[holder].repaired, 50); // ������� �� ���� �������� �� ������������
			cout << "����� ���� �� ������������ (" << service[holder].price << "). �������� ���a ���� �� ������������: "; cin >> service[holder].price; // ������� �� ���� ���� �� ������������
			cout << "���� ������ �� ������������ (" << service[holder].status << "). �������� ���a ���� �� ������������: " << endl; // ������� �������� ��������� �� ���������
			cout << "[1] ������ �������\n[2] �������� �������\n[3] ����������" << endl;
			int choice2;
			cin >> choice2;
			if (choice2 == 1) 
			{
				string holderStatus = "������ �������";
				strcpy_s(service[holder].status, holderStatus.c_str()); // ������� �� �������� �� ������� �� ������������
			}
			else if (choice2 == 2) 
			{
				string holderStatus = "�������� �������";
				strcpy_s(service[holder].status, holderStatus.c_str()); // ������� �� �������� �� ������� �� ������������
			}
			else if (choice2 == 3) 
			{
				string holderStatus = "����������";
				strcpy_s(service[holder].status, holderStatus.c_str()); // ������� �� �������� �� ������� �� ������������
			}
			else 
				cout << "���� ������ �����! ������� �� ������������ �� ������ �����!" << endl; // ������� �������� ��������� �� ���������
		}
		else if (choice == 2) // ��� ������ � 2
		{
			if (service[holder].status[0] == '�') // ��� ������� ����� �� ������� � ����� �� �
			{
				system("CLS"); // �������� ���������.
				string holderStatus = "�������� �������";
				strcpy_s(service[holder].status, holderStatus.c_str()); // ������� �� ���������

				service[holder].price += 10; // ���������� �� 10 ��.
				cout << "��������� ���� ��������! (��������� �� 10��. ���������)" << endl; // ������� �������� ��������� �� ���������
			}
			else
			{
				system("CLS"); // �������� ���������.
				cout << "���������� ������� � ���� ��������� ��� ���� ��������!" << endl; // ������� �������� ��������� �� ���������
			}
		}
		else 
		{
			system("CLS");
			cout << "��������� �����!" << endl; // ������� �������� ��������� �� ���������
		}
	}
}

void service(Service service[], int count)
{
	system("CLS"); // �������� ���������.

	int deviceNumber, holder;
	bool found = false;

	// ������� �������� ��������� �� ���������
	cout << "�������� ���������� �� ����������!" << endl;
	cout << "�������� �������� ����� �� ������������: ";
	cin >> deviceNumber;

	for (int i = 0; i < count; i++) // ����� ����� ������� �� 0 � ����� �� count
	{
		if (deviceNumber == service[i].device->id) // ��� ������ � ����� �� ���������
		{
			found = true; // �������
			holder = i; // ������� �������
		}
	}

	if (!found)
	{
		system("CLS"); // �������� ���������.
		cout << "���� �������� ���������� � ����� " << deviceNumber << endl; // �� � �������
	}
	else
	{
		if (service[holder].status[0] == '�') // ��� ������� � ����� �� ������ �������
		{
			system("CLS"); // �������� ���������.
			cout << "�������� ���������� �� ���������� � ����� (" << service[holder].id << ")" << endl; // �������� ��������� �� ������� �� ���������

			output(service, holder, holder + 1); // ������� �� ��������� output
			cout << endl;

			double price;
			int day;
			cin.ignore();
			cout << "�������� ��� �� ��������� ������ ��������� ������������: "; cin.getline(service[holder].nameTehnician, 50); // ������� �� ��� �� �������� ������
			cout << "�������� ���������� ������ �� ������������: " << endl;
			string device = deviceRepaired(); // ���� �� ������� � ���� �� ������ ������
			strcpy_s(service[holder].repaired, device.c_str());  // ������� ���������� ������ �� ������������
			cout << "�������� ���� �� ���������� ������ �� ������������: "; cin >> price; // ������� �� ����
			bool invalidDate = true;
			while (invalidDate) // ����� ����� �� ����� ������ ���������� ���� � ��������
			{
				cout << "�������� ���� � ����� � ��������� ������������: "; cin >> day; // ������� �� ����
				if (day < service[holder].dayOfTheMonth || day < 1 || day > 31) // ��������� ���� ������ � ��������
				{
					cout << "��������� ����!" << endl; // �� � �������
				}
				else
					invalidDate = false; // ������ � �������
			}
			service[holder].daysRequiredToRepair = day - service[holder].dayOfTheMonth; // ������� ����� ��������� ����� ����� �� ��������
			service[holder].price += price; // ��������� �� ����
			string holderStatus = "����������"; // ������� �� ������� �� ����������
			strcpy_s(service[holder].status, holderStatus.c_str()); // ������� �� ������� �� ����������
		}
		else
		{
			system("CLS"); // �������� ���������.
			cout << "���������� ������� � ���� ��������� ��� ��������!" << endl; // ������� �� �������� ��������� �� ���������
		}
	}
}

void odit(Service service[], int count)
{
	Service holder[serviceCount];
	int serviceCounter = 0;
	int choice = -1;
	while (choice != 0) // ����� ����� �� ����� ������ �� �� ������ 0
	{
		system("CLS"); // �������� ���������.

		// ������� �� ���� � �����.
		cout << "[1] ��������� �� ��������� �� ��� �� ������\n[2] ��������� �� ��������� �� ����� ��� ����������\n[3] ���������� �� ��������� �� ����� ������\n[0] �����" << endl;
		cout << "�������� ����� �����: ";
		cin >> choice;

		switch (choice) // �������� �� �������������� �����
		{
		case 0:
			return;
			break;
		case 1:
			system("CLS"); // �������� ���������.
			int day;
			cout << "��������� �� ��������� �� ��� �� ������, ��������� �� ������ �����" << endl;
			cout << "�������� ��� �� ������: ";
			cin >> day;

			for (int i = 0; i < count; i++) // ����� ����� ������� �� 0 � ����� �� count
			{
				if (service[i].dayOfTheMonth == day) // ��������� ���� ���������� ��������� ���
				{
					holder[serviceCounter] = service[i]; // ������� ������ ������������ ��������� � ������� ���
					serviceCounter++; // ��������� ���� �� ������������ ������ ����� ���� �� ������
				}
			}

			if (serviceCounter > 0) // ��� ������ � ������ �� 0
			{
				for (int i = 0; i < serviceCounter - 1; i++) // ����� �������� �� 0 �� serviceCounter - 1
				{
					for (int j = 0; j < serviceCounter - i - 1; j++)// ����� �������� �� 0 �� serviceCounter - 1
					{
						if (holder[j].device->id > holder[j + 1].device->id) // ��������� ���� �������� ����� � �� ����� �� ���������
						{
							//  �������� �� � ������ (bubblesort)
							Service temp = holder[j];
							holder[j] = holder[j + 1];
							holder[j + 1] = temp;
						}
					}
				}
				output(holder, 0, serviceCounter); // ������� �� ������� output
			}
			else
				cout << "���� ��������� ������� �� ���� ���!" << endl; // ������� �� �������� ��������� �� ���������
			choice = 0;
			break;
		case 2:
			system("CLS"); // �������� ���������.
			char device[50];
			// ������� �� �������� ��������� �� ���������
			cout << "��������� �� ��������� �� ����� ��� ����������, ����� �� ����������� � ��������� �� ���� � ��������� ���" << endl;
			cout << "�������� ��� ����������: ";
			cin >> device;

			for (int i = 0; i < count; i++) // ����� ����� ������� �� 0 � �� ����� �� count
			{
				if (strcmp(service[i].device->device, device) == 0 && strcmp(service[i].status, "����������") == 0) // ��� ���������� ���������� ���������� � � �����������
				{
					holder[serviceCounter] = service[i]; // ������� �� ��� �����
					serviceCounter++; // ����� �� ������ �� ������ � 1
				}
			}

			if (serviceCounter > 0) // ��� ������ � ������ �� 0
			{
				for (int i = 0; i < serviceCounter - 1; i++)// ����� �������� �� 0 �� serviceCounter - 1
				{
					for (int j = 0; j < serviceCounter - i - 1; j++)// ����� �������� �� 0 �� serviceCounter - 1
					{
						if (holder[j].dayOfTheMonth < holder[j + 1].dayOfTheMonth) // ��� �������� ��� � ��- ����� �� ��������� 
						{
							//  �������� �� � ������ (bubblesort)
							Service temp = holder[j];
							holder[j] = holder[j + 1];
							holder[j + 1] = temp;
						}
					}
				}
				output(holder, 0, serviceCounter); // ������� �� ������� output
			}
			else
				cout << "���� ��������� ������� � ����� ��� ����������, ����� �� � �����������!" << endl; // ������� �� �������� ��������� �� ���������
			choice = 0;
			break;
		case 3:
			system("CLS"); // �������� ���������.
			char name[50];
			// ������� �� �������� ��������� �� ���������
			cout << "��������� �� ��������� �� ����� ������, ��������� �� ������ ����� �� ������������" << endl;
			cout << "�������� ��� �� ������: ";
			cin >> name;

			for (int i = 0; i < count; i++) // ����� �������� �� 0 ������ �� count
			{
				if (strcmp(service[i].name, name) == 0) // ��������� ���� ���������� ��� �� �����
				{
					holder[serviceCounter] = service[i]; // ������� ����������� � �����
					serviceCounter++; // ������ �� ������ �� ����� � 1
				}
			}

			if (serviceCounter > 0) // ��� ������ � ��- ����� �� 0
			{
				for (int i = 0; i < serviceCounter - 1; i++)// ����� �������� �� 0 �� serviceCounter - 1
				{
					for (int j = 0; j < serviceCounter - i - 1; j++)// ����� �������� �� 0 �� serviceCounter - 1
					{
						if (holder[j].device->id > holder[j + 1].device->id) // ��������� ���� ��������� id �� ������ � ��- ������ �� ����������
						{
							//  �������� �� � ������ (bubblesort)
							Service temp = holder[j];
							holder[j] = holder[j + 1];
							holder[j + 1] = temp;
						}
					}
				}
				output(holder, 0, serviceCounter); // ������� �� ������� output
			}
			else
				cout << "���� ��������� ������� �� ���� ���!" << endl; // ������� �� �������� ��������� �� ���������
			choice = 0;
			break;
		default:
			cout << "���� ������ ����� � ������!" << endl; // ������� �� �������� ��������� �� ���������
			system("pause");
			break;
		}
	}
}

void writeFile(Service service[], int count)
{
	ofstream f1;
	f1.open("f1.dat", ios::out); // ������ �� ���� � ��� f1.dat
	if (f1.is_open()) // �������� ���� ����� � ������� �������
	{
		for (int i = 0; i < count; i++) // ����� ����� ������� �� 0 � ����� �� count
		{
			// �������� �� �������� ��������� �� ����������� � �����
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
		f1.close(); // ��������� �� �����
	}
	else // ��� �� � ������� ������� �����
		cout << "��������� �������� �� �����!" << endl; // ������� �� ��������� �������� ���������
}

void readFile(Service service[], int& count, int& lastDate)
{
	// ��������� �� ����� ���� ���� ��� �����
	ifstream myFile("f1.dat");
	myFile.unsetf(ios_base::skipws);
	unsigned line_count = std::count(
		std::istream_iterator<char>(myFile),
		std::istream_iterator<char>(),
		'\n');

	fstream f1;
	f1.open("f1.dat", ios::in); // ������ �� ���� � ��� f1.dat

	if (f1.is_open())  // �������� ���� ����� � ������� �������
	{
		for (int i = 0; i < line_count / 11; i++) // ����� ����� ������� �� 0 � ����� �� ���� �� ������ �� ��������� ��������� � �����
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
		f1.close(); // ��������� �� �����
	}
	else // ��� �� � ������� ������� �����
		cout << "��������� �������� �� �����!" << endl; // ������� �� ��������� �������� ���������
}

void writeToFile(Service service[], int count) 
{
	fstream file;
	file.open("f2.dat", ios::binary | ios::out);//������ �� �����
	if (file.is_open())
	{
		file.write((char*)service, sizeof(Service));//�������� �� ������� �� �����
		file.close();//������� �� �����
	}
	else
		cout << endl << "������ ��� ���������� �� �����";
}

void readFromFile(Service service[], int& count, int& lastDate) 
{
	fstream file;
	file.open("f2.dat", ios::binary | ios::in);//������ �� ����
	if (file.is_open())
	{
		file.seekg(0L, ios::end);//����� �� ��������� � ���� �� �����
		long pos = (long)file.tellg();//������ �� ������� �� ���������
		file.seekg(0L, ios::beg);//����� �� ��������� � �������� �� �����
		file.close();//������� �� �����
		int n = pos / (sizeof(Service));
		file.open("f2.dat", ios::binary | ios::in);//������ �� ����
		file.read((char*)service, n * (sizeof(Service)));//���� �� �� �����
		file.close();//������� �� �����
	}
	else
		cout << endl << "������ ��� ���������� �� �����";
}

string deviceProblem()
{
	int choice;
	string holder;
	while (true) // �������� �����
	{
		// ������� �� ���� � �����.
		cout << "[1] ������� � �������" << endl;
		cout << "[2] �� �� �������" << endl;
		cout << "[3] ������ ����������" << endl;
		cout << "[4] ���� ����" << endl;
		cout << "[5] ������������ ������" << endl;
		cout << "[6] ������" << endl;
		cout << "[7] ������� � ��������" << endl;
		cout << "[8] �������� ���� �������" << endl;

		cin >> choice;

		switch (choice) // �������� �� �������������� �����
		{
		case 1:
			return "������� � �������";
			break;
		case 2:
			return "�� �� �������";
			break;
		case 3:
			return "������ ����������";
			break;
		case 4:
			return "���� ����";
			break;
		case 5:
			return "������������ ������";
			break;
		case 6:
			return "������";
			break;
		case 7:
			return "������� � ��������";
			break;
		case 8:
			cout << "�������� ����� �������:" << endl;
			cin >> holder;
			return holder;
			break;
		default:
			cout << "���� ������ ����� � ������!" << endl;
			system("pause");
			break;
		}
	}
}

string deviceRepaired() 
{
	int choice;
	string holder;
	while (true) // �������� �����
	{
		// ������� �� ���� � �����.
		cout << "[1] ����� �� �������" << endl;
		cout << "[2] �������� �� �����������" << endl;
		cout << "[3] ��������" << endl;
		cout << "[4] ������� ����������" << endl;
		cout << "[5] �������������" << endl;
		cout << "[6] �������� �� ����������" << endl;
		cout << "[7] ������� ������" << endl;
		cout << "[8] �������� ���� ��������" << endl;

		cin >> choice;

		switch (choice) // �������� �� �������������� �����
		{
		case 1:
			return "����� �� �������";
			break;
		case 2:
			return "�������� �� �����������";
			break;
		case 3:
			return "��������";
			break;
		case 4:
			return "������� ����������";
			break;
		case 5:
			return "�������������";
			break;
		case 6:
			return "�������� �� ����������";
			break;
		case 7:
			return "������� ������";
			break;
		case 8:
			cout << "�������� ����������� ��������:" << endl;
			cin >> holder;
			return holder;
			break;
		default:
			cout << "���� ������ ����� � ������!" << endl;
			system("pause");
			break;
		}
	}
}

int menu() 
{
	int choice;

	// ������� �� ���� � �����.
	cout << "[0] ����� �� ����������\n[1] ��������� �� ����������\n[2] ��������� �� ����������\n[3] �������� �� ����� �� ����������\n[4] �������� ���������� �� ������������\n[5] ����" << endl;
	cout << "�������� �����: ";

	cin >> choice; // ������� �� ����� �� ������.

	return choice;
}