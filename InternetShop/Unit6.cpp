//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit6.h"


#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "DbConfig.h"



#include <Vcl.Dialogs.hpp>
#include <Variant.hpp>
#include <ComObj.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm6 *Form6;
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
	: TForm(Owner)
{
	try {
		ADOConnection1->Connected = false;
		ADOConnection1->ConnectionString = GetDatabaseConnectionString();
		ADOConnection1->Connected = true;
		ADOQuery1->Open();
	}
	catch (Exception &e) {
		ShowMessage("Ошибка подключения отчетов к БД: " + e.Message);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm6::DateTimePicker1Change(TObject *Sender)
{








TDateTime selectedDateTime = DateTimePicker1->DateTime;
String selectedDate = DateToStr(selectedDateTime);


ADOQuery1->SQL->Text = "SELECT * FROM заказы WHERE date_ LIKE :selectedDate + '%' ORDER BY date_ ASC";
ADOQuery1->Parameters->ParamByName("selectedDate")->Value = selectedDate;
ADOQuery1->Open();

DBGrid1->DataSource = DataSource1;
DataSource1->DataSet = ADOQuery1;
	ADOQuery1->Open();











}
//---------------------------------------------------------------------------
void __fastcall TForm6::FormCreate(TObject *Sender)
{

}
//---------------------------------------------------------------------------

void __fastcall TForm6::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form1->Close();
	Form2->Close();
	Form3->Close();
	Form4->Close();
    Form5->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm6::Button2Click(TObject *Sender)
{



TDateTime selectedDateTime = DateTimePicker1->DateTime;
String selectedDate = DateToStr(selectedDateTime);


ADOQuery1->SQL->Text = "SELECT * FROM заказы WHERE date_ LIKE :selectedDate + '%' ORDER BY date_ ASC";
ADOQuery1->Parameters->ParamByName("selectedDate")->Value = selectedDate;
ADOQuery1->Open();

DBGrid1->DataSource = DataSource1;
DataSource1->DataSet = ADOQuery1;
	ADOQuery1->Open();




}
//---------------------------------------------------------------------------


Variant Workbook;
Variant Worksheet;
TDBGrid* DBGrid1;
String excelFilePath = "output.xlsx";


    String userName;



void __fastcall TForm6::Button6Click(TObject *Sender)
{
        ADOQuery1->SQL->Text = "SELECT * FROM заказы";
		ADOQuery1->Open();
        DataSource1->DataSet = ADOQuery1;
		DBGrid1->DataSource = DataSource1;

}
//---------------------------------------------------------------------------



void __fastcall TForm6::Button5Click(TObject *Sender)
{
    try
    {
        if (ADOQuery1->IsEmpty())
        {
            ShowMessage("Нет данных для экспорта!");
            return;
        }

        Variant wordApp = CreateOleObject("Word.Application");
        wordApp.OlePropertySet("Visible", true);

        Variant wordDocs = wordApp.OlePropertyGet("Documents");
        Variant wordDoc = wordDocs.OleFunction("Add");
        wordDoc.OleProcedure("Activate");

        Variant wordParagraphs = wordDoc.OlePropertyGet("Paragraphs");

        Variant titlePara = wordParagraphs.OleFunction("Add");
        titlePara.OlePropertyGet("Range").OlePropertySet("Text",
            "Отчет заказов за " + DateToStr(DateTimePicker1->Date));
        titlePara.OlePropertySet("Alignment", 2);
        Variant titleFont = titlePara.OlePropertyGet("Range").OlePropertyGet("Font");
        titleFont.OlePropertySet("Size", 15);
        titleFont.OlePropertySet("Bold", false);
        titleFont.OlePropertySet("Name", WideString("Times New Roman"));

        wordParagraphs.OleProcedure("Add");
        wordParagraphs.OleProcedure("Add");
        Variant tablePara = wordParagraphs.OleFunction("Item", 3);
        Variant tableRange = tablePara.OlePropertyGet("Range");
        tablePara.OlePropertySet("Alignment", 1);

        Variant wordTable = wordDoc.OlePropertyGet("Tables").OleFunction("Add",
            tableRange, ADOQuery1->RecordCount + 1, 10);

        wordTable.OlePropertySet("PreferredWidthType", 3);
        wordTable.OlePropertySet("PreferredWidth", 100);

        const int colCount = 10;
        UnicodeString headers[colCount] = {
            "Пользователь", "Чек", "ID товара", "Название",
            "Цена", "Количество", "Адрес", "Оплата", "Дата", "Время"
        };

        for (int col = 1; col <= colCount; col++)
        {
            Variant cell = wordTable.OleFunction("Cell", 1, col);
            cell.OlePropertyGet("Range").OlePropertySet("Text", headers[col-1]);

            Variant font = cell.OlePropertyGet("Range").OlePropertyGet("Font");
            font.OlePropertySet("Bold", true);
            font.OlePropertySet("Size", 10);
            font.OlePropertySet("Name", WideString("Arial"));

            cell.OlePropertySet("VerticalAlignment", 1);
        }

        int row = 2;
        ADOQuery1->First();
        while (!ADOQuery1->Eof)
        {
            for (int col = 1; col <= colCount; col++)
            {
                Variant cell = wordTable.OleFunction("Cell", row, col);
                Variant fieldValue;

                switch(col) {
                    case 1: fieldValue = ADOQuery1->FieldByName("user_")->AsString; break;
                    case 2: fieldValue = ADOQuery1->FieldByName("check_")->AsString; break;
                    case 3: fieldValue = ADOQuery1->FieldByName("id_")->AsString; break;
                    case 4: fieldValue = ADOQuery1->FieldByName("name_")->AsString; break;
                    case 5: fieldValue = ADOQuery1->FieldByName("cost_")->AsString; break;
                    case 6: fieldValue = ADOQuery1->FieldByName("kolvo_")->AsString; break;
                    case 7: fieldValue = ADOQuery1->FieldByName("adress_")->AsString; break;
                    case 8: fieldValue = ADOQuery1->FieldByName("pay_")->AsString; break;
                    case 9: fieldValue = ADOQuery1->FieldByName("date_")->AsString; break;
                    case 10: fieldValue = ADOQuery1->FieldByName("time_")->AsString; break;
                }

                cell.OlePropertyGet("Range").OlePropertySet("Text", fieldValue);

                Variant dataFont = cell.OlePropertyGet("Range").OlePropertyGet("Font");
                dataFont.OlePropertySet("Size", 9);
                dataFont.OlePropertySet("Name", WideString("Arial"));
                dataFont.OlePropertySet("Bold", false);
            }
            row++;
            ADOQuery1->Next();
        }

        Variant borders = wordTable.OlePropertyGet("Borders");
        borders.OlePropertySet("InsideLineStyle", 1);
        borders.OlePropertySet("OutsideLineStyle", 1);

        wordTable.OleFunction("AutoFitBehavior", 1);

        String savePath = ExtractFilePath(Application->ExeName) +
                         "Заказы_за_" + FormatDateTime("yyyy-mm-dd", DateTimePicker1->Date) + ".docx";
        if (FileExists(savePath)) DeleteFile(savePath);

        wordDoc.OleProcedure("SaveAs", savePath);
        ShowMessage("Документ успешно сохранен:\n" + savePath);

        wordApp.OleProcedure("Quit");
    }
    catch(Exception &e)
    {
    }
}
//---------------------------------------------------------------------------






void __fastcall TForm6::Button3Click(TObject *Sender)
{
	if (ADOQuery1->IsEmpty())
	{
		ShowMessage("Нет записей для удаления.");
		return;
	}
	if (MessageBox(0, L"Вы уверены, что хотите удалить все отфильтрованные заказы?", L"Подтверждение", MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		TDateTime selectedDateTime = DateTimePicker1->DateTime;
		String selectedDate = DateToStr(selectedDateTime);
		ADOQuery1->SQL->Text = "DELETE FROM заказы WHERE date_ LIKE :selectedDate + '%'";
        ADOQuery1->Parameters->ParamByName("selectedDate")->Value = selectedDate;
        ADOQuery1->ExecSQL();
        ADOQuery1->Close();
        ADOQuery1->SQL->Text = "SELECT * FROM заказы WHERE date_ LIKE :selectedDate + '%' ORDER BY date_ ASC";
        ADOQuery1->Parameters->ParamByName("selectedDate")->Value = selectedDate;
        ADOQuery1->Open();
        DataSource1->DataSet = ADOQuery1;
        DBGrid1->DataSource = DataSource1;
        ShowMessage("Данные заказы успешно удалены.");
	}
}
//---------------------------------------------------------------------------







void __fastcall TForm6::Button1Click(TObject *Sender)
{
    if (ADOQuery1->IsEmpty())
    {
        ShowMessage(L"Нет записей для удаления.");
        return;
    }

        ADOQuery1->Delete();
        TDateTime selectedDateTime = DateTimePicker1->DateTime;
        String selectedDate = DateToStr(selectedDateTime);
        ADOQuery1->Close();
        ADOQuery1->SQL->Text = "SELECT * FROM заказы WHERE date_ LIKE :selectedDate + '%' ORDER BY date_ ASC";
        ADOQuery1->Parameters->ParamByName("selectedDate")->Value = selectedDate;
        ADOQuery1->Open();
        DataSource1->DataSet = ADOQuery1;
        DBGrid1->DataSource = DataSource1;

}
//---------------------------------------------------------------------------








void __fastcall TForm6::Button4Click(TObject *Sender)
{
    if (ADOQuery1->IsEmpty())
    {
        ShowMessage("Нет данных для экспорта!");
        return;
    }

    Variant excel = CreateOleObject("Excel.Application");
    excel.OlePropertySet("Visible", true);

    Variant workbooks = excel.OlePropertyGet("Workbooks");
    Variant workbook = workbooks.OleFunction("Add");
    Variant sheet = workbook.OlePropertyGet("Worksheets", 1);

    Variant headerRange = sheet.OlePropertyGet("Range", "A1:J1");
    headerRange.OleProcedure("Merge");

    headerRange.OlePropertySet("Value", "Список заказов за " + DateToStr(DateTimePicker1->Date));

    headerRange.OlePropertyGet("Font").OlePropertySet("Bold", true);
    headerRange.OlePropertyGet("Font").OlePropertySet("Size", 12);
    headerRange.OlePropertySet("HorizontalAlignment", 3);
    headerRange.OlePropertyGet("Interior").OlePropertySet("Color", 0xCCCCCC);

    const int colCount = 10;
    UnicodeString headers[colCount] = {
        "Пользователь", "Чек", "ID товара", "Название",
        "Цена", "Количество", "Адрес", "Оплата", "Дата", "Время"
    };

    for (int col = 0; col < colCount; col++)
    {
        Variant cell = sheet.OlePropertyGet("Cells", 2, col+1);
        cell.OlePropertySet("Value", headers[col]);
        cell.OlePropertyGet("Font").OlePropertySet("Bold", true);
    }

    int row = 3;
    ADOQuery1->First();
    while (!ADOQuery1->Eof)
    {
        sheet.OlePropertyGet("Cells", row, 1).OlePropertySet("Value", ADOQuery1->FieldByName("user_")->AsString);
        sheet.OlePropertyGet("Cells", row, 2).OlePropertySet("Value", ADOQuery1->FieldByName("check_")->AsString);
        sheet.OlePropertyGet("Cells", row, 3).OlePropertySet("Value", ADOQuery1->FieldByName("id_")->AsString);
        sheet.OlePropertyGet("Cells", row, 4).OlePropertySet("Value", ADOQuery1->FieldByName("name_")->AsString);
        sheet.OlePropertyGet("Cells", row, 5).OlePropertySet("Value", ADOQuery1->FieldByName("cost_")->AsFloat);
        sheet.OlePropertyGet("Cells", row, 6).OlePropertySet("Value", ADOQuery1->FieldByName("kolvo_")->AsInteger);
        sheet.OlePropertyGet("Cells", row, 7).OlePropertySet("Value", ADOQuery1->FieldByName("adress_")->AsString);
        sheet.OlePropertyGet("Cells", row, 8).OlePropertySet("Value", ADOQuery1->FieldByName("pay_")->AsString);
        sheet.OlePropertyGet("Cells", row, 9).OlePropertySet("Value", ADOQuery1->FieldByName("date_")->AsDateTime);
        sheet.OlePropertyGet("Cells", row, 10).OlePropertySet("Value", ADOQuery1->FieldByName("time_")->AsString);

        row++;
        ADOQuery1->Next();
    }

    Variant dataRange = sheet.OlePropertyGet("Range", "A2:J" + IntToStr(row-1));
    dataRange.OlePropertyGet("Columns").OleFunction("AutoFit");

    dataRange.OlePropertyGet("Borders").OlePropertySet("LineStyle", 1);

    String savePath = ExtractFilePath(Application->ExeName) +
                     "Заказы_за_" + FormatDateTime("yyyy-mm-dd", DateTimePicker1->Date) + ".xlsx";
    if (FileExists(savePath)) DeleteFile(savePath);

    workbook.OleProcedure("SaveAs", savePath, 51);
    ShowMessage("Данные успешно экспортированы в файл:\n" + savePath);

    workbook.OleProcedure("Close", false);
    excel.OleProcedure("Quit");
}
//---------------------------------------------------------------------------

