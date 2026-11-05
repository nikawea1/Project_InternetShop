//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
	String login1 = "admin";
    String password1 = "11";







	if(Edit1->Text != "" && Edit2->Text != "")
	{
		Form1->ADOQuery1->SQL->Text = "select * from пользователи where user_=" + QuotedStr(Edit1->Text);
		Form1->ADOQuery1->Open();
		if(Form1->ADOQuery1->RecordCount == 1 &&
			Form1->ADOQuery1->Fields->FieldByName("user_")->AsString == Edit1->Text)
		{
			if(Form1->ADOQuery1->Fields->FieldByName("password_")->AsString == Edit2->Text)
			{
				Form1->ADOQuery1->SQL->Text = "select * from пользователи where user_=" + QuotedStr(Edit1->Text);
				Form1->ADOQuery1->Open();
				Form1->Show();
				Form2->Hide();
				Form1->Width = 1300;
				Form1->Height = 1300;



				Form1->DBGrid2->ReadOnly = true;
				Form1->DBNavigator1->Visible = false;
				Form1->DBNavigator2->Visible = false;


				Form1->LabeledEdit1->Visible = false;
				Form1->LabeledEdit2->Visible = false;
				Form1->LabeledEdit3->Visible = false;
				Form1->Button12->Visible = false;
				Form1->Button13->Visible = false;
				Form1->Button14->Visible = false;

				 Form1->Label3->Visible = false;
                Form1->Button17->Visible = false;
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


					Form1->Edit2->Text = Form2->Edit1->Text;
					Form1->Edit2->Visible = false;







			}
			else
			  MessageDlg("Ќеверный пароль.",
				 mtError, TMsgDlgButtons() << mbOK, 0);
		}
		else if(Edit1->Text == login1 && Edit2->Text == password1)
		{
		Form1->Show();
		Form2->Hide();

		Form1->Edit2->Visible = false;



				Form1->Width = 2100;
				Form1->Height = 1300;

				Form1->Edit2->Text = Form2->Edit1->Text;


        Form1->ADOQuery1->SQL->Text = "SELECT * FROM пользователи";
		Form1->DBGrid1->Visible = true;
		Form1->DBGrid1->Enabled = true;
		Form1->ADOQuery1->Open();

		}
		else
			MessageDlg("ѕользователь с таким именем не существует. ¬ведите повторно им€.",
				 mtError, TMsgDlgButtons() << mbOK, 0);

	}
	else
		MessageDlg("«аполните все пол€ данными.",
				 mtError, TMsgDlgButtons() << mbOK, 0);


}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button2Click(TObject *Sender)
{
	Form3->Show();
	Form2->Hide();
}
//---------------------------------------------------------------------------


void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
	Form1->Close();
	Form3->Close();
	Form4->Close();
	Form5->Close();
	Form6->Close();
}
//---------------------------------------------------------------------------



void __fastcall TForm2::Edit2KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN)
		Button1Click(Button1);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if (Key == VK_RETURN)
	{
		Edit2->SetFocus();
		Key = 0;
	}
}
//---------------------------------------------------------------------------

