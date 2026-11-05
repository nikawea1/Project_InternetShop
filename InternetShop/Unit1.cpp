//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
#include "DbConfig.h"


#include <jpeg.hpp>

#include <string>



//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	String connStr = GetDatabaseConnectionString();
	try {
		ADOConnection1->Connected = false;
		ADOConnection1->ConnectionString = connStr;
		ADOConnection1->Connected = true;

		ADOConnection2->Connected = false;
		ADOConnection2->ConnectionString = connStr;
		ADOConnection2->Connected = true;

		ADOQuery1->SQL->Text = "SELECT * FROM пользователи";
		ADOQuery1->Open();

		ADOQuery2->SQL->Text = "SELECT * FROM каталог_товаров";
		ADOQuery2->Open();
	}
	catch (Exception &e) {
		ShowMessage("Ошибка подключения к БД: " + e.Message);
	}
}



bool isDarkTheme = false;


void TForm1::ApplyTheme()
{

      if (isDarkTheme)
	{
		Form1->Color = TColor(0x008D4B49);
        Form1->Font->Color = clWhite;
        Button1->Font->Color = clWhite;
		Button2->Font->Color = clWhite;
		DBGrid1->Color = TColor(0x00444444);
        DBGrid2->Color = TColor(0x00444444);
        LabeledEdit1->Color = TColor(0x00444444);
		LabeledEdit1->Font->Color = clWhite;
        LabeledEdit2->Color = TColor(0x00444444);
		LabeledEdit2->Font->Color = clWhite;
        LabeledEdit3->Color = TColor(0x00444444);
		LabeledEdit3->Font->Color = clWhite;
		ToggleSwitch1->Color = TColor(0x00444444);
        ToggleSwitch1->Font->Color = clWhite;
		Label1->Color = TColor(0x00444444);
        Label1->Font->Color = clWhite;
	}
    else
	{
		Form1->Color = TColor(0xF5DEAD);
        Form1->Font->Color = clBlack;
		Button1->Font->Color = clBlack;
		Button2->Font->Color = clBlack;
		DBGrid1->Color = clWhite;
		DBGrid1->Font->Color = clBlack;
		DBGrid2->Color = clWhite;
		DBGrid2->Font->Color = clBlack;
		LabeledEdit1->Color = clWhite;
		LabeledEdit1->Font->Color = clBlack;
		LabeledEdit2->Color = clWhite;
		LabeledEdit2->Font->Color = clBlack;
		LabeledEdit3->Color = clWhite;
		LabeledEdit3->Font->Color = clBlack;
		ToggleSwitch1->Color = clWhite;
		ToggleSwitch1->Font->Color = clBlack;
		Label1->Color = clWhite;
		Label1->Font->Color = clBlack;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	Form1->Hide();
	Form2->Show();
	Timer1->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Form2->Show();
	Form1->Hide();


	Form4->ADOQuery1->Close();
	Form4->ADOQuery1->SQL->Text = "DELETE FROM корзина";
	Form4->ADOQuery1->ExecSQL();



	Form1->Edit2->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DBGrid2CellClick(TColumn *Column)
{
    if (!ADOQuery2->Active || ADOQuery2->IsEmpty()) return;

    String name = ADOQuery2->FieldByName("name_")->AsString;
    String category = ADOQuery2->FieldByName("category_")->AsString;
    float cost = ADOQuery2->FieldByName("cost_")->AsFloat;
    String rawImage = ADOQuery2->FieldByName("foto_")->AsString;
    String imagePath = GetImagePath(rawImage);
    String inf = ADOQuery2->FieldByName("inf_")->AsString;
    Form5->Label1->Caption = "Название: " + name;
    Form5->Label2->Caption = "Категория: " + category;
    Form5->Label3->Caption = "Цена: " + FloatToStrF(cost, ffFixed, 8, 2) + " BYN";
    Form5->Label4->Caption = "Характеристики: " + inf;
    try {
        if (FileExists(imagePath)) {
            Form5->Image1->Picture->LoadFromFile(imagePath);
        } else {
            Form5->Image1->Picture->Bitmap = nullptr;
            ShowMessage("Файл изображения не найден:\n" + rawImage);
        }
    }
    catch (...) {
        ShowMessage("Ошибка при загрузке изображения.");
        Form5->Image1->Picture->Bitmap = nullptr;
    }
    if (Form5->Visible) {
        Form5->Hide();
        Sleep(50);
    }
	Form5->Show();



}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Form4->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form2->Close();
	Form3->Close();
	Form4->Close();
	Form5->Close();
	Form6->Close();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button6Click(TObject *Sender)
{
	ADOQuery2->SQL->Text = "SELECT * FROM каталог_товаров ORDER BY cost_";
	ADOQuery2->Open();
	DBGrid2->DataSource->DataSet = ADOQuery2;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button7Click(TObject *Sender)
{
	ADOQuery2->SQL->Text = "SELECT * FROM каталог_товаров ORDER BY category_";
	ADOQuery2->Open();
	DBGrid2->DataSource->DataSet = ADOQuery2;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button8Click(TObject *Sender)
{
	ADOQuery2->SQL->Text = "SELECT * FROM каталог_товаров";
	ADOQuery2->Open();
	DBGrid2->DataSource->DataSet = ADOQuery2;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button9Click(TObject *Sender)
{

	float totalCost = 0.0;

	if (ADOQuery2->Active)
    {
		ADOQuery2->First();
		while (!ADOQuery2->Eof)
        {
			totalCost += ADOQuery2->FieldByName("cost_")->AsFloat;
			ADOQuery2->Next();
        }
    }

    ShowMessage("Общая стоимость: " + FormatFloat("0.00", totalCost));
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button10Click(TObject *Sender)
{
	ADOQuery2->Prior();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button11Click(TObject *Sender)
{
    ADOQuery2->Next();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{
	if(LabeledEdit1->Text != "" && LabeledEdit2->Text != "" && LabeledEdit3->Text != "")
	{
		ADOQuery2->Insert();
		ADOQuery2->Fields->FieldByName("name_")->AsString = LabeledEdit1->Text;
		ADOQuery2->Fields->FieldByName("cost_")->AsFloat = StrToFloat(LabeledEdit2->Text);
		ADOQuery2->Fields->FieldByName("category_")->AsString = LabeledEdit3->Text;
		ADOQuery2->Post();

	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button13Click(TObject *Sender)
{
	 TLocateOptions Options;
	 if(ADOQuery2->Locate("name_", LabeledEdit1->Text, Options))
	 ADOQuery2->Delete();
	 else ShowMessage("Эта запись пустая");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button14Click(TObject *Sender)
{
	ADOQuery2->Open();
	ADOQuery2->Edit();

	if (ADOQuery2->Locate("name_", LabeledEdit1->Text, TLocateOptions()))
	{
		ADOQuery2->Edit();
		ADOQuery2->Fields->FieldByName("cost_")->AsString = LabeledEdit2->Text;
		ADOQuery2->Fields->FieldByName("category_")->AsString = LabeledEdit3->Text;
		ADOQuery2->Post();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button15Click(TObject *Sender)
{
	ADOQuery2->Active = False;
	ADOQuery2->SQL->Text = "Select * from каталог_товаров where cost_ between :p1 and :p2";
	ADOQuery2->Parameters->ParamByName("p1")->Value = StrToFloat(LabeledEdit4->Text);
	ADOQuery2->Parameters->ParamByName("p2")->Value = StrToFloat(LabeledEdit5->Text);
	ADOQuery2->Active = True;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
	String searchText = Edit1->Text.Trim();
	if (searchText != "")
	{
		ADOQuery2->Close();
		ADOQuery2->SQL->Text = "SELECT * FROM каталог_товаров WHERE name_ LIKE :name";
		ADOQuery2->Parameters->ParamByName("name")->Value = searchText + "%";
		ADOQuery2->Open();
		DBGrid2->DataSource->DataSet = ADOQuery2;
	}
	else
	{
		ADOQuery2->Close();
		ADOQuery2->SQL->Text = "SELECT * FROM каталог_товаров";
		ADOQuery2->Open();
		DBGrid2->DataSource->DataSet = ADOQuery2;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
	ADOQuery1->SQL->Text = "SELECT * FROM пользователи";
}
//---------------------------------------------------------------------------


int currentId = 1;
void __fastcall TForm1::DBGrid2DblClick(TObject *Sender)
{

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button16Click(TObject *Sender)
{

    if (Form1->DBGrid2->DataSource->DataSet->IsEmpty()) {
        ShowMessage("Не выбран товар!");
        return;
    }

    Form1->ADOQuery2->Open();

    int id = Form1->ADOQuery2->FieldByName("id_")->AsInteger;
    String name = Form1->ADOQuery2->FieldByName("name_")->AsString;
    float cost = Form1->ADOQuery2->FieldByName("cost_")->AsFloat;
    String category = Form1->ADOQuery2->FieldByName("category_")->AsString;
    int kolvo = 1;

    Form4->Show();

    Form4->ADOQuery1->Open();

    bool itemExists = false;
    Form4->ADOQuery1->First();
    while (!Form4->ADOQuery1->Eof) {
        if (Form4->ADOQuery1->FieldByName("id_")->AsInteger == id) {
            itemExists = true;
            break;
        }
        Form4->ADOQuery1->Next();
    }

    if (itemExists) {
        Form4->ADOQuery1->Edit();
        int currentKolvo = Form4->ADOQuery1->FieldByName("kolvo_")->AsInteger;
        Form4->ADOQuery1->FieldByName("kolvo_")->AsInteger = currentKolvo + 1;
        Form4->ADOQuery1->Post();
    } else {
        int check = Form4->ADOQuery1->RecordCount + 1;

        Form4->ADOQuery1->SQL->Text =
            "INSERT INTO корзина (check_, id_, name_, cost_, category_, kolvo_) "
            "VALUES (:check, :id, :name, :cost, :category, :kolvo)";

        Form4->ADOQuery1->Parameters->ParamByName("check")->Value = check;
        Form4->ADOQuery1->Parameters->ParamByName("id")->Value = id;
        Form4->ADOQuery1->Parameters->ParamByName("name")->Value = name;
        Form4->ADOQuery1->Parameters->ParamByName("cost")->Value = cost;
        Form4->ADOQuery1->Parameters->ParamByName("category")->Value = category;
        Form4->ADOQuery1->Parameters->ParamByName("kolvo")->Value = 1;

        Form4->ADOQuery1->ExecSQL();
    }

    float totalCost = 0.0;
    Form4->ADOQuery1->Close();
    Form4->ADOQuery1->SQL->Text = "SELECT * FROM корзина";
    Form4->ADOQuery1->Open();

    if (Form4->ADOQuery1->Active) {
        Form4->ADOQuery1->First();
        while (!Form4->ADOQuery1->Eof) {
            totalCost += Form4->ADOQuery1->FieldByName("cost_")->AsFloat *
                       Form4->ADOQuery1->FieldByName("kolvo_")->AsInteger;
            Form4->ADOQuery1->Next();
        }
    }

    Form4->Edit1->Text = FormatFloat("0.00", totalCost);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button17Click(TObject *Sender)
{
    Form6->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button18Click(TObject *Sender)
{
ADOQuery2->SQL->Text = "SELECT * FROM каталог_товаров ORDER BY cost_ DESC";
ADOQuery2->Open();
DBGrid2->DataSource->DataSet = ADOQuery2;


   				for (int i = 0; i < Form1->DBGrid2->Columns->Count; i++)
					{
						if (Form1->DBGrid2->Columns->Items[i]->FieldName == "kolvo_")
						{
							Form1->DBGrid2->Columns->Items[i]->Visible = false;
							break;
						}
					}
					for (int i = 0; i < Form1->DBGrid2->Columns->Count; i++)
					{
						if (Form1->DBGrid2->Columns->Items[i]->FieldName == "foto_")
						{
							Form1->DBGrid2->Columns->Items[i]->Visible = false;
							break;
						}
					}
					for (int i = 0; i < Form1->DBGrid2->Columns->Count; i++)
					{
						if (Form1->DBGrid2->Columns->Items[i]->FieldName == "inf_")
						{
							Form1->DBGrid2->Columns->Items[i]->Visible = false;
							break;
						}
					}








					Form4->DBNavigator1->Visible = false;
					for (int i = 0; i < Form4->DBGrid1->Columns->Count; i++) {
						if (Form4->DBGrid1->Columns->Items[i]->FieldName == "kolvo_") {
							Form4->DBGrid1->Columns->Items[i]->ReadOnly = false;
						}
						else {
							Form4->DBGrid1->Columns->Items[i]->ReadOnly = true;
						}
					}



}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button3Click(TObject *Sender)
{
	ADOQuery2->SQL->Text = "SELECT * FROM каталог_товаров WHERE category_ = :category";
	ADOQuery2->Parameters->ParamByName("category")->Value = Edit1->Text;
	ADOQuery2->Open();
	DBGrid1->DataSource->DataSet = ADOQuery2;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button19Click(TObject *Sender)
{
	ADOQuery1->Open();
	ADOQuery1->Edit();

	if (ADOQuery1->Locate("user_", LabeledEdit6->Text, TLocateOptions()))
	{
		ADOQuery1->Edit();
		ADOQuery1->Fields->FieldByName("password_")->AsString = LabeledEdit7->Text;
		ADOQuery1->Post();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button20Click(TObject *Sender)
{
	 TLocateOptions Options;
	 if(ADOQuery1->Locate("user_", LabeledEdit6->Text, Options))
	 ADOQuery1->Delete();
	 else ShowMessage("Эта запись пустая");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button21Click(TObject *Sender)
{
	if(LabeledEdit6->Text != "" && LabeledEdit7->Text != "")
	{
		ADOQuery1->Insert();
		ADOQuery1->Fields->FieldByName("user_")->AsString = LabeledEdit6->Text;
		ADOQuery1->Fields->FieldByName("password_")->AsString = LabeledEdit7->Text;
		ADOQuery1->Post();

	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit3Change(TObject *Sender)
{
	String searchText1 = Edit3->Text.Trim();
	if (searchText1 != "")
	{
		ADOQuery1->Close();
		ADOQuery1->SQL->Text = "SELECT * FROM пользователи WHERE user_ LIKE :user";
		ADOQuery1->Parameters->ParamByName("user")->Value = searchText1 + "%";
		ADOQuery1->Open();
		DBGrid1->DataSource->DataSet = ADOQuery1;
	}
	else
	{
		ADOQuery1->Close();
		ADOQuery1->SQL->Text = "SELECT * FROM пользователи";
		ADOQuery1->Open();
		DBGrid1->DataSource->DataSet = ADOQuery1;
	}
}
//---------------------------------------------------------------------------










void __fastcall TForm1::ToggleSwitch1Click(TObject *Sender)
{
    isDarkTheme = !isDarkTheme;
    if (isDarkTheme)
    {
		Form1->Color = TColor(0x008D4B49);
        Form1->Font->Color = clWhite;
        Button1->Font->Color = clWhite;
        Button2->Font->Color = clWhite;
        DBGrid1->Color = TColor(0x00444444);
        DBGrid2->Color = TColor(0x00444444);
        LabeledEdit1->Color = TColor(0x00444444);
        LabeledEdit1->Font->Color = clWhite;
		LabeledEdit2->Color = TColor(0x00444444);
		LabeledEdit2->Font->Color = clWhite;
		LabeledEdit3->Color = TColor(0x00444444);
		LabeledEdit3->Font->Color = clWhite;
        ToggleSwitch1->Color = TColor(0x00444444);
        ToggleSwitch1->Font->Color = clWhite;
        Label1->Color = TColor(0x00444444);
        Label1->Font->Color = clWhite;
    }
    else
    {
		Form1->Color = TColor(0xF5DEAD);
		Form1->Font->Color = clBlack;
        Button1->Font->Color = clBlack;
        Button2->Font->Color = clBlack;
        DBGrid1->Color = clWhite;
        DBGrid1->Font->Color = clBlack;
        DBGrid2->Color = clWhite;
        DBGrid2->Font->Color = clBlack;
        LabeledEdit1->Color = clWhite;
        LabeledEdit1->Font->Color = clBlack;
        LabeledEdit2->Color = clWhite;
		LabeledEdit2->Font->Color = clBlack;
		LabeledEdit3->Color = clWhite;
		LabeledEdit3->Font->Color = clBlack;
        ToggleSwitch1->Color = clWhite;
        ToggleSwitch1->Font->Color = clBlack;
        Label1->Color = clWhite;
        Label1->Font->Color = clBlack;
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N2Click(TObject *Sender)
{
    isDarkTheme = false;
    ApplyTheme();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
    isDarkTheme = true;
	ApplyTheme();
}
//---------------------------------------------------------------------------

