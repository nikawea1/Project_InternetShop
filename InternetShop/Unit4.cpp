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
#include <string>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
	try {
		ADOConnection1->Connected = false;
		ADOConnection1->ConnectionString = GetDatabaseConnectionString();
		ADOConnection1->Connected = true;
		ADOQuery1->Open();
	}
	catch (Exception &e) {
		ShowMessage("Ошибка подключения корзины к БД: " + e.Message);
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm4::Button1Click(TObject *Sender)
{
    ADOQuery1->Close();
    ADOQuery1->SQL->Text = "DELETE FROM корзина";
    ADOQuery1->ExecSQL();
    ADOQuery1->SQL->Text = "SELECT * FROM корзина";
    ADOQuery1->Open();
    float totalCost = 0.0;
    if (ADOQuery1->Active)
    {
        ADOQuery1->First();
        while (!ADOQuery1->Eof)
        {
            totalCost += ADOQuery1->FieldByName("cost_")->AsFloat * ADOQuery1->FieldByName("kolvo_")->AsInteger;
            ADOQuery1->Next();
        }
    }
	Edit1->Text = FormatFloat("0.00", totalCost);
}
//---------------------------------------------------------------------------

int totalCouriers = 3;
int availableCouriers = totalCouriers;








TDateTime currentDateTime = Now();
TDateTime currentDate = StrToDateTime(FormatDateTime("dd.mm.yyyy", currentDateTime));;
String currentTime = FormatDateTime("hh:nn:ss", currentDateTime);




void __fastcall TForm4::Button2Click(TObject *Sender)
{
    ADOQuery1->Close();
    ADOQuery1->SQL->Text = "SELECT * FROM корзина";
    ADOQuery1->Open();

    if (ADOQuery1->IsEmpty())
    {
        ShowMessage("Корзина пуста. Нельзя оформить заказ.");
        return;
    }





	if (Edit2->Text.IsEmpty())
	{
		ShowMessage("Пожалуйста, введите адрес доставки.");
		return;
	}

	if (!RadioButton1->Checked && !RadioButton2->Checked)
	{
		ShowMessage("Пожалуйста, выберите способ оплаты.");
		return;
	}



	String address = Edit2->Text.Trim();

	bool containsLetter = false;
	for (int i = 1; i <= address.Length(); ++i)
	{
		wchar_t ch = address[i];
		if ((ch >= L'A' && ch <= L'Z') || (ch >= L'a' && ch <= L'z') ||
			(ch >= L'А' && ch <= L'Я') || (ch >= L'а' && ch <= L'я'))
		{
			containsLetter = true;
			break;
		}
	}

	if (!containsLetter)
	{
		ShowMessage("Пожалуйста, введите корректный адрес доставки.");
		return;
	}



	Edit2->Clear();
	RadioButton1->Checked = false;
	RadioButton2->Checked = false;

	int deliveryTime = 30 + (rand() % 91);

	if (availableCouriers > 0) {
		availableCouriers--;
		ShowMessage("Заказ оформлен!\nПримерное время доставки: " + IntToStr(deliveryTime) +
					" минут.\nКурьеров доступно: " + IntToStr(availableCouriers));
	} else {
		ShowMessage("Все курьеры заняты. Пожалуйста, подождите.");
	}







	String address1 = Edit2->Text;
	if (address.IsEmpty())
	{
		ShowMessage("Пожалуйста, введите адрес доставки.");
		return;
	}

	String paymentMethod;
	if (RadioButton1->Checked)
		paymentMethod = "Наличными";
	else
		paymentMethod = "Картой";







String userName = Form1->Edit2->Text.Trim();

ADOQuery1->First();
while (!ADOQuery1->Eof)
{
    ADOQuery2->SQL->Text = "INSERT INTO заказы (user_, check_, id_, name_, cost_, kolvo_, adress_, pay_, date_, time_) "
                         "VALUES (:user_, :check_, :id_, :name_, :cost_, :kolvo_, :adress_, :pay_, :date_, :time_)";
    ADOQuery2->Parameters->ParamByName("user_")->Value = userName;
    ADOQuery2->Parameters->ParamByName("check_")->Value = ADOQuery1->FieldByName("check_")->Value;
    ADOQuery2->Parameters->ParamByName("id_")->Value = ADOQuery1->FieldByName("id_")->Value;
    ADOQuery2->Parameters->ParamByName("name_")->Value = ADOQuery1->FieldByName("name_")->Value;
    ADOQuery2->Parameters->ParamByName("cost_")->Value = ADOQuery1->FieldByName("cost_")->Value;
    ADOQuery2->Parameters->ParamByName("kolvo_")->Value = ADOQuery1->FieldByName("kolvo_")->Value;
    ADOQuery2->Parameters->ParamByName("adress_")->Value = address;
    ADOQuery2->Parameters->ParamByName("pay_")->Value = paymentMethod;
    ADOQuery2->Parameters->ParamByName("date_")->Value = currentDate;
    ADOQuery2->Parameters->ParamByName("time_")->Value = currentTime;
    ADOQuery2->ExecSQL();

    ADOQuery1->Next();
}

 ADOQuery1->Open();



}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form2->Close();
	Form3->Close();
	Form5->Close();
    Form6->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::DBGrid1CellClick(TColumn *Column)
{
	ADOQuery2->Active  = false;
	ADOQuery2->SQL->Text = "select sum(kolvo_*cost_) from корзина";
	ADOQuery2->Open();

	if (!ADOQuery2->IsEmpty()) {
	int totalCost = ADOQuery2->Fields->Fields[0]->AsInteger;
	Edit1->Text = FormatFloat("0.00", totalCost);
	} else {
	ShowMessage("Корзина пуста");
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm4::DBGrid1ColEnter(TObject *Sender)
{
	if (DBGrid1->SelectedField->FieldName != "kolvo_")
		DBGrid1->Options = DBGrid1->Options >> dgEditing;
	else
		DBGrid1->Options = DBGrid1->Options << dgEditing;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormCreate(TObject *Sender)
{


	srand(time(NULL));
}
//---------------------------------------------------------------------------



