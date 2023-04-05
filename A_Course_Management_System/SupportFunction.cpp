#include"MyLib.h"
// Viet chu tai vi tri (x,y)
void Write(string s, int x, int y, string BG_Color, string Text_Color)
{
	Gotoxy(x, y);
	SetColor(BG_Color, Text_Color);
	cout << s;
	ResetColor();
	return;
}

int Choice(string* s, int sizeOfs, int x, int y, string BG_Color_1, string Text_Color_1, string BG_Color_2, string Text_Color_2)
{
	//Color_1: mau cua text khi duoc chon,
	//Color_2: mau cua nhung text con lai
	// 175 16 ,272
	string Mark = ">> ";
	int your_choice = 0;
	SetColor(BG_Color_1, Text_Color_1);
	Gotoxy(x, y); cout << Mark << s[0];
	SetColor(BG_Color_2, Text_Color_2);
	for (int i = 1;i < sizeOfs;i++)
	{
		Gotoxy(x, y + i); cout << Mark << s[i];
	}

	while (true)
	{
		char c;
		c = _getch();
		if (c == -32) c = _getch();
		switch (c)
		{
		case 72:
		{
			if (your_choice > 0)
			{
				Write(Mark + s[your_choice], x, y + your_choice, BG_Color_2, Text_Color_2);
				your_choice -= 1;
				Write(Mark + s[your_choice], x, y + your_choice, BG_Color_1, Text_Color_1);
			}
			break;
		}
		case 80:
		{
			if (your_choice < sizeOfs - 1)
			{
				Write(Mark + s[your_choice], x, y + your_choice, BG_Color_2, Text_Color_2);
				your_choice += 1;
				Write(Mark + s[your_choice], x, y + your_choice, BG_Color_1, Text_Color_1);
			}
			break;
		}
		case 13:
			ResetColor();
			return your_choice;
		}
	}
	ResetColor();
}

void Draw_Border(int x, int y, int a, int b, string BG_Color, string Text_Color)
{
	// Ve khung bat dau tu (x,y) co chieu ngang a don vi, chieu doc b don vi
	SetColor(BG_Color, Text_Color);
	a--;
	b--;
	Gotoxy(x, y); cout << char(201);
	for (int i = 1;i < a;i++)
	{
		Gotoxy(x + i, y); cout << char(205);
	}
	Gotoxy(x+a, y); cout << char(187);
	for (int i = 1; i < b; i++)
	{
		Gotoxy(x, y + i); cout << char(186);
		Gotoxy(x+a, y + i); cout << char(186);
	}
	Gotoxy(x, y+b); cout << char(200);
	for (int i = 1;i < a;i++)
	{
		Gotoxy(x + i, y+b); cout << char(205);
	}
	Gotoxy(x+a, y+b); cout << char(188);
	ResetColor();
}

void Draw_Space_Rectangle(int x, int y, int a, int b, string Color)
{
	SetColor(Color, Color);
	for (int i = 0;i < b;i++)
	{
		Gotoxy(x, y+i);
		for (int j = 0;j < a;j++)
		{
			cout << " ";
		}
	}
	ResetColor();
}

void Transition() 
{
	Draw_Border(0, 0, 71, 19, Default_BG_Color, Default_Text_Color);
	Draw_Space_Rectangle(1, 1, 69, 17,"white");
}

bool Check_If_String_Is_Existed(string link, string s)
{
	fstream file(link, ios::in);
	string temp;
	while (getline(file, temp))
	{
		if (temp == s)
		{
			file.close();
			return true;
		}
	}
	file.close();
	return false;
}

void Sort_File(string link)
{
	fstream file(link, ios::in);
	string temp;
	int cnt = 0;
	while (getline(file, temp))
	{
		cnt++;                           //dem so luong dong
	}
	file.close();

	file.open(link, ios::in);
	string* list = new string[cnt];
	for (int i = 0; i<cnt;i++) // dua du lieu tu file -> list
	{
		getline(file, list[i]);
	}
	for (int i = 0;i < cnt;i++) // sap xep tang dan
	{
		for (int j = i + 1;j < cnt;j++)
		{
			if (strcmp(list[i].c_str(), list[j].c_str()) > 0)
			{
				temp = list[i]; list[i] = list[j]; list[j] = temp;
			}
		}
	}
	file.close();
	file.open(link, ios::out);
	for (int i = 0;i < cnt;i++)
	{
		file << (list[i] + '\n');
	}
	file.close();
	delete[] list;
	return;
}

int View_Board(string* s, int sizeOfs, int x, int y, string BG_Color, string Text_Color)
{
	char c = 0;
	int page = 0;
	for (int i = 0; i < 7 && i < sizeOfs;i++)
	{
		Write(s[i + page], x, y + i + page);
	}

	while (true)
	{
		c = _getch();
		if (c == -32)c = _getch();
		
		switch (c)
		{
			case 1:
			{
				page++;
				if (page * 7 >= sizeOfs) page--;

				for (int i = 0; i < 7 && i < sizeOfs;i++)
				{
					Write(s[i + page], x, y + i + page);
				}
				break;
			}

		}

	}

}