//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Vcl.DBCtrls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
	TADOConnection *ADOConnection1;
	TDataSource *DataSource1;
	TADOTable *ADOTable1;
	TADOQuery *ADOQuery1;
	TDBGrid *DBGrid1;
	TDBNavigator *DBNavigator1;
	TButton *Button1;
	TButton *Button2;
	TEdit *Edit1;
	TAutoIncField *ADOQuery1check_;
	TIntegerField *ADOQuery1id_;
	TWideStringField *ADOQuery1name_;
	TIntegerField *ADOQuery1cost_;
	TWideStringField *ADOQuery1category_;
	TIntegerField *ADOQuery1kolvo_;
	TEdit *Edit2;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TADOQuery *ADOQuery2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall DBGrid1CellClick(TColumn *Column);
	void __fastcall DBGrid1ColEnter(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
